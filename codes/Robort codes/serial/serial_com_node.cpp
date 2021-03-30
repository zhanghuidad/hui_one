/****************************************************************************
 *  Copyright (C) 2018 RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "serial/serial_com_node.h"

namespace rrts {
namespace driver {
namespace serial {
SerialComNode::SerialComNode(std::string module_name)
    : rrts::common::RRTS::RRTS(module_name), fd_(0), is_open_(false), stop_receive_(true), stop_send_(true) {
  SerialPortConfig serial_port_config;
  CHECK(rrts::common::ReadProtoFromTextFile("/home/ubuntu/RM2019/src/serial/config/serial_com_config.prototxt",
                                            &serial_port_config))
  << "Error loading proto file for serial.";
  CHECK(serial_port_config.has_serial_port()) << "Port not set.";
  CHECK(serial_port_config.has_serial_boudrate()) << "Baudrate not set.";
  length_beam_ = serial_port_config.link_beam();
  length_column_ = serial_port_config.link_column();
  baudrate_ = serial_port_config.serial_boudrate();
  port_ = serial_port_config.serial_port();
  
  //uwb_position_.header.frame_id = "uwb";
  //uwb_position_.header.seq = 0;
  
  CHECK(Initialization()) << "Initialization error.";
  is_open_ = true;
  stop_receive_ = false;
  stop_send_ = false;
  is_sim_ = serial_port_config.is_simulator();
  is_debug_ = serial_port_config.is_debug();
  pack_length_ = 0;
  total_length_ = 0;
  free_length_ = UART_BUFF_SIZE;
  odom_pub_ = nh_.advertise<nav_msgs::Odometry>("odom", 100);
  gim_pub_ = nh_.advertise<rm_msgs::GimbalAngle>("gimbal", 30);
  uwb_pose_pub_ = nh_.advertise<rm_msgs::PositionUWB>("uwb_pose", 30);
  game_info_pub_ = nh_.advertise<rm_msgs::GameInfo>("game_info", 30);
  hurt_data_pub_ = nh_.advertise<rm_msgs::HurtData>("hurt_data", 30);
  shoot_data_pub_ = nh_.advertise<rm_msgs::ShootData>("shoot_data", 30);
  rfid_data_pub_ = nh_.advertise<rm_msgs::RFID>("rfid", 30);
  if (is_debug_) {
    fp_ = fopen("debug_com.txt", "w+");
  }
}

bool SerialComNode::Initialization() {
  return SerialInitialization(port_, baudrate_, 0, 8, 1, 'N');
}

bool SerialComNode::SerialInitialization(std::string port,
                                         int baudrate,
                                         int flow_control,
                                         int data_bits,
                                         int stop_bits,
                                         int parity) {
  fd_ = open(port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
  CHECK(fd_ != -1) << "Serial port open failed!";
  CHECK(tcgetattr(fd_, &termios_options_) == 0) << "Get serial attributes error!";
  termios_options_original_ = termios_options_;
  ConfigBaudrate(baudrate);
  termios_options_.c_cflag |= CLOCAL;
  termios_options_.c_cflag |= CREAD;
  termios_options_.c_cflag &= ~CSIZE;
  switch (flow_control) {
    case 0 :termios_options_.c_cflag &= ~CRTSCTS;
      break;
    case 1 :termios_options_.c_cflag |= CRTSCTS;
      break;
    case 2 :termios_options_.c_cflag |= IXON | IXOFF | IXANY;
      break;
    default: termios_options_.c_cflag &= ~CRTSCTS;
      break;
  }
  switch (data_bits) {
    case 5 :termios_options_.c_cflag |= CS5;
      break;
    case 6 :termios_options_.c_cflag |= CS6;
      break;
    case 7 :termios_options_.c_cflag |= CS7;
      break;
    case 8 :termios_options_.c_cflag |= CS8;
      break;
    default: LOG_FATAL << "Unsupported data size";
      return false;
  }
  switch (parity) {
    case 'n':
    case 'N':termios_options_.c_cflag &= ~(PARENB | PARODD);
      termios_options_.c_iflag &= ~INPCK;
      break;
    case 'o':
    case 'O':termios_options_.c_cflag |= (PARODD | PARENB);
      termios_options_.c_iflag |= INPCK;
      break;
    case 'e':
    case 'E':termios_options_.c_cflag |= PARENB;
      termios_options_.c_cflag &= ~PARODD;
      termios_options_.c_iflag |= INPCK;
      break;
    case 's':
    case 'S':termios_options_.c_cflag &= ~PARENB;
      termios_options_.c_cflag &= ~CSTOPB;
      break;
    default: LOG_FATAL << "Unsupported parity";
      return false;
  }
  switch (stop_bits) {
    case 1: termios_options_.c_cflag &= ~CSTOPB;
      break;
    case 2: termios_options_.c_cflag |= CSTOPB;
      break;
    default: LOG_FATAL << "Unsupported stop bits";
      return false;
  }
  termios_options_.c_lflag = 0;
  termios_options_.c_oflag = 0;
  termios_options_.c_oflag &= ~OPOST;
  termios_options_.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
  termios_options_.c_cc[VTIME] = 1;
  termios_options_.c_cc[VMIN] = 60;
  termios_options_.c_iflag = IGNBRK;
  CHECK_EQ(tcsetattr(fd_, TCSANOW, &termios_options_), 0)
    << "Set serial attributes error!";
  LOG_INFO << "Com config success";
  return true;
}

bool SerialComNode::ConfigBaudrate(int baudrate) {
  int i;
  int speed_arr[] = {B921600, B576000, B460800, B230400, B115200, B19200, B9600, B4800, B2400, B1200, B300};
  int name_arr[] = {921600, 576000, 460800, 230400, 115200, 19200, 9600, 4800, 2400, 1200, 300};
  for (i = 0; i < sizeof(speed_arr) / sizeof(int); i++) {
    if (baudrate == name_arr[i]) {
      cfsetispeed(&termios_options_, speed_arr[i]);
      cfsetospeed(&termios_options_, speed_arr[i]);
      return true;
    }
  }
  LOG_ERROR << "Baudrate set error.";
  return false;
}

void SerialComNode::Run() {
  receive_loop_thread_ = new std::thread(boost::bind(&SerialComNode::ReceiveLoop, this));
  if (is_debug_) {
    keyboard_in_ = new std::thread(boost::bind(&SerialComNode::ListenClick, this));
  }
  //sub_cmd_gim_ = nh_.subscribe("enemy_pos", 1, &SerialComNode::GimbalControlCallback, this);
  sub_cmd_gim_ = nh_.subscribe("gimbal_cmd", 1, &SerialComNode::GimbalControlCallback, this);
  sub_cmd_vel_ = nh_.subscribe("cmd_vel", 1, &SerialComNode::ChassisControlCallback, this);
  sub_cmd_shoot_ = nh_.subscribe("shoot_cmd", 1, &SerialComNode::ShootControlCallback, this);
  sub_laser_scan_ = nh_.subscribe<sensor_msgs::LaserScan>("/scan", 1, &SerialComNode::LaserScanCallback, this);
  send_loop_thread_ = new std::thread(boost::bind(&SerialComNode::SendPack, this));
  ros::spin();
}

void SerialComNode::ListenClick() {
  static struct termios oldt, newt;
  while (is_sim_ && ros::ok()) {
    usleep(1000);
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    key_ = getchar();
    if (key_ != 10) {
      valid_key_ = key_;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  }
}

void SerialComNode::ReceiveLoop() {
  while (is_open_ && !stop_receive_ && ros::ok()) {
    read_buff_index_ = 0;
    read_len_ = ReceiveData(fd_, UART_BUFF_SIZE);
    if (read_len_ > 0) {
      while (read_len_--) {
        byte_ = rx_buf_[read_buff_index_++];
        switch (unpack_step_e_) {
          case STEP_HEADER_SOF: {
            if (byte_ == UP_REG_ID) {
              protocol_packet_[index_++] = byte_;
              unpack_step_e_ = STEP_LENGTH_LOW;
            } else {
              index_ = 0;
            }
          }
            break;
          case STEP_LENGTH_LOW: {
            data_length_ = byte_;
            protocol_packet_[index_++] = byte_;
            unpack_step_e_ = STEP_LENGTH_HIGH;
          }
            break;
          case STEP_LENGTH_HIGH: {
            data_length_ |= (byte_ << 8);
            protocol_packet_[index_++] = byte_;
            if (data_length_ < (PROTOCAL_FRAME_MAX_SIZE - HEADER_LEN - CMD_LEN - CRC_LEN)) {
              unpack_step_e_ = STEP_FRAME_SEQ;
            } else {
              LOG_WARNING << "Data length too big";
              unpack_step_e_ = STEP_HEADER_SOF;
              index_ = 0;
            }
          }
            break;
          case STEP_FRAME_SEQ: {
            protocol_packet_[index_++] = byte_;
            unpack_step_e_ = STEP_HEADER_CRC8;
          }
            break;
          case STEP_HEADER_CRC8: {
            protocol_packet_[index_++] = byte_;
            bool crc8_result = VerifyCrcOctCheckSum(protocol_packet_, HEADER_LEN);
            if (!crc8_result) {
              LOG_WARNING << "CRC 8 error";
            }
            if ((index_ == HEADER_LEN) && crc8_result) {
              if (index_ < HEADER_LEN) {
                LOG_WARNING << "CRC 8 index less.";
              }
              unpack_step_e_ = STEP_DATA_CRC16;
            } else {
              unpack_step_e_ = STEP_HEADER_SOF;
              index_ = 0;
            }
          }
            break;
          case STEP_DATA_CRC16: {
            if (index_ < (HEADER_LEN + CMD_LEN + data_length_ + CRC_LEN)) {
              protocol_packet_[index_++] = byte_;
            } else if (index_ > (HEADER_LEN + CMD_LEN + data_length_ + CRC_LEN)) {
              LOG_WARNING << "Index Beyond";
            }
            if (index_ == (HEADER_LEN + CMD_LEN + data_length_ + CRC_LEN)) {
              unpack_step_e_ = STEP_HEADER_SOF;
              index_ = 0;
              if (VerifyCrcHexCheckSum(protocol_packet_, HEADER_LEN + CMD_LEN + data_length_ + CRC_LEN)) {
                DataHandle();
              } else {
                LOG_WARNING << "CRC16 error";
              }
            }
          }
            break;
          default: {
            LOG_WARNING << "Unpack not well";
            unpack_step_e_ = STEP_HEADER_SOF;
            index_ = 0;
          }
            break;
        }
      }
    }
  }
}

int SerialComNode::ReceiveData(int fd, int data_length) {
  int received_length, selected;
  fd_set fs_read;
  struct timeval time;
  static int is_init = 0;
  if (is_init == 0) {
    is_init++;
    FD_ZERO(&fs_read);
    FD_SET(fd, &fs_read);
  }
  FD_ZERO(&fs_read);
  FD_SET(fd, &fs_read);
  time.tv_sec = 0;
  time.tv_usec = 0;
  selected = select(fd + 1, &fs_read, NULL, NULL, &time);
  if (selected > 0) {
    received_length = read(fd, rx_buf_, data_length);
    if (is_debug_) 
    {
      int count = received_length;
    int p = 0;
      while (count--) {
	printf("%2x,", rx_buf_[p]);
	p++;
      }
      printf("\n");
    }
  } else if (selected == 0) {
    received_length = 0;
  } else {
    received_length = 0;
    LOG_ERROR << "Select function error";
  }
  return received_length;
}

void SerialComNode::DataHandle() {
  ros::Time current_time = ros::Time::now();
  geometry_msgs::Quaternion q;
  std::lock_guard<std::mutex> guard(mutex_receive_);
  auto *p_header = (FrameHeader *) protocol_packet_;
  uint16_t data_length = p_header->data_length;
  uint16_t cmd_id = *(uint16_t *) (protocol_packet_ + HEADER_LEN);
  uint8_t *data_addr = protocol_packet_ + HEADER_LEN + CMD_LEN;
  switch (cmd_id) {
    case GAME_INFO_ID: memcpy(&game_information_, data_addr, data_length);
    /*
      uwb_position_.header.stamp = current_time;
      uwb_position_.header.seq++;
      uwb_position_.valid_flag = game_information_.position.valid_flag;
      uwb_position_.x = game_information_.position.x;
      uwb_position_.y = game_information_.position.y;
      uwb_position_.z = game_information_.position.z;
      uwb_position_.yaw = game_information_.position.yaw;
      uwb_pose_pub_.publish(uwb_position_);
      */
    game_info.stage_remain_time = game_information_.stage_remain_time;
    game_info.game_process = game_information_.game_process;
    game_info.remain_hp = game_information_.remain_hp;
    game_info.max_hp = game_information_.max_hp;
    game_info_pub_.publish(game_info);
      LOG_INFO << "Game info OK";
      if (is_debug_) {
        LOG_INFO << "Game remaining blood: " << game_information_.remain_hp;
      }
      if(is_debug_)
      {
	printf("GameInfo: remain_time = %d  process = %d remain_hp = %d max_hp = %d \n",game_info.stage_remain_time,game_info.game_process,game_info.remain_hp,game_info.max_hp);
      }
      break;
    case REAL_BLOOD_DATA_ID: memcpy(&robot_hurt_data_, data_addr, data_length);
      if (is_debug_) {
        LOG_INFO << "Blood change: " << "Which armor is hurt: " << robot_hurt_data_.armor_type << " and the hurt type: "
                << robot_hurt_data_.hurt_type << std::endl;
      }
      hurt_data.hurt_armor_num = robot_hurt_data_.armor_type;
      hurt_data.hurt_type = robot_hurt_data_.hurt_type;
      hurt_data_pub_.publish(hurt_data);
      if(is_debug_)
      {
	printf("HurtData: hurt_type = %d  hurt_armor_num = %d \n",robot_hurt_data_.hurt_type,robot_hurt_data_.armor_type);
      }
      
      break;
    case REAL_SHOOT_DATA_ID: memcpy(&real_shoot_data_, data_addr, data_length);
    shoot_data.bullet_freq = real_shoot_data_.bullet_freq;
    shoot_data.bullet_speed = real_shoot_data_.bullet_speed;
    shoot_data_pub_.publish(shoot_data);
    
    if(is_debug_)
      {
	printf("ShootData: bullet_freq = %d  bullet_speed = %f \n",shoot_data.bullet_freq,shoot_data.bullet_speed);
      }
      
      break;
    case REAL_RFID_DATA_ID: memcpy(&rfid_data_, data_addr, data_length);
    rfid_data.ok = (rfid_data_.card_type== 11) ;//)
    rfid_data.index = rfid_data_.card_idx;
    rfid_data_pub_.publish(rfid_data);
    printf("rfid_data.ok = %d  rfid_data.index  = %d \n",rfid_data.ok,rfid_data.index);
      break;
    case GAME_RESULT_ID: memcpy(&game_result_data_, data_addr, data_length);
      break;
    case GAIN_BUFF_ID: memcpy(&get_buff_data_, data_addr, data_length);
      break;
    case ROBOT_POS_DATA_ID: memcpy(&uwb_position_get, data_addr, data_length);
    uwb_position_.x = uwb_position_get.x;
    uwb_position_.y = uwb_position_get.y;
    uwb_position_.z = uwb_position_get.z;
    uwb_position_.yaw = uwb_position_get.yaw;
    uwb_pose_pub_.publish(uwb_position_);
    //printf("gim_pub_.publish(uwb_position_);%f,%f,%f",uwb_position_.x,uwb_position_.y,uwb_position_.z);
      break;
    case SERVER_TO_USER_ID: memcpy(&student_download_data_, data_addr, data_length);
      break;
    case CHASSIS_DATA_ID: {
      if (is_debug_) {
        LOG_INFO << "Chassis bottom data is received.";
      }
      memcpy(&chassis_information_, data_addr, data_length);
      nav_msgs::Odometry odom;
      odom.header.stamp = current_time;
      odom.header.frame_id = "odom";
      odom.child_frame_id = "base_link";
      double x = chassis_information_.x_position / 1000.0, y = chassis_information_.y_position / 1000.0;
      odom.pose.pose.position.x = x;
      odom.pose.pose.position.y = y;
      odom.pose.pose.position.z = 0.0;
      q = tf::createQuaternionMsgFromYaw(chassis_information_.gyro_angle / 180.0 * M_PI);
      odom.pose.pose.orientation = q;
      odom.twist.twist.linear.x = (double) chassis_information_.x_speed / 1000.0;
      odom.twist.twist.linear.y = (double) chassis_information_.y_speed / 1000.0;
      odom.twist.twist.angular.z = chassis_information_.gyro_palstance / 180.0 * M_PI;
      odom_pub_.publish(odom);
      
      //***************LYH 20190305***************//
      if(first_time_flag==1)
      {
        x0=x;
        y0=y;
        q0=q;
        first_time_flag = 0;

      }
      geometry_msgs::TransformStamped arena_tf;
      arena_tf.header.frame_id = "odom";
      arena_tf.header.stamp = current_time;
      arena_tf.child_frame_id = "arena";
      arena_tf.transform.translation.x = x0;
      arena_tf.transform.translation.y = y0;
      arena_tf.transform.translation.z = 0.0;
      arena_tf.transform.rotation = q0;
      //static_broadcaster.sendTransform(arena_tf);
      tf_broadcaster_.sendTransform(arena_tf);

      //***************LYH 20190305***************//

      geometry_msgs::TransformStamped odom_tf;
      odom_tf.header.frame_id = "odom";
      odom_tf.header.stamp = current_time;
      odom_tf.child_frame_id = "base_link";
      odom_tf.transform.translation.x = x;
      odom_tf.transform.translation.y = y;
      odom_tf.transform.translation.z = 0.0;
      odom_tf.transform.rotation = q;
      tf_broadcaster_.sendTransform(odom_tf);
    }
      break;
    case GIMBAL_DATA_ID: memcpy(&gimbal_information_, data_addr, data_length);
      gim_angle_.pitch = gimbal_information_.pit_relative_angle;
      gim_angle_.yaw = gimbal_information_.yaw_relative_angle;
      gim_angle_.pitch_rate = gimbal_information_.pit_palstance;
      gim_angle_.yaw_rate = gimbal_information_.yaw_palstance;
      gim_pub_.publish(gim_angle_);
      //printf("gim_pub_.publish(gim_angle_);%f,%f",gim_angle_.pitch,gim_angle_.yaw);
      q = tf::createQuaternionMsgFromRollPitchYaw(0.0, gim_angle_.pitch, gim_angle_.yaw);
      arm_tf_.header.frame_id = "base_link";
      arm_tf_.child_frame_id = "gimbal";
      arm_tf_.header.stamp = current_time;
      arm_tf_.transform.rotation = q;
      arm_tf_.transform.translation.x = length_beam_ * cos(gim_angle_.pitch) * cos(gim_angle_.yaw) / 1000;
      arm_tf_.transform.translation.y = length_beam_ * cos(gim_angle_.pitch) * sin(gim_angle_.yaw) / 1000;
      arm_tf_.transform.translation.z = (length_column_ + length_beam_ * sin(gim_angle_.pitch)) / 1000;
      tf_broadcaster_.sendTransform(arm_tf_);
      if (is_debug_) {
        LOG_INFO << "Gimbal info-->" << gimbal_information_.pit_relative_angle;
      }
      break;
    case SHOOT_TASK_DATA_ID: memcpy(&shoot_task_data_, data_addr, data_length);
      if (is_debug_) {
        LOG_INFO << "Shoot task-->" << shoot_task_data_.fric_wheel_run;
      }
      break;
    case INFANTRY_ERR_ID: memcpy(&global_error_data_, data_addr, data_length);
      if (is_debug_) {
        printf("Infantry err-->%d\n", global_error_data_.err_sta);
      }
      for (int i = 0; i < ERROR_LIST_LENGTH; i++) {
        if (global_error_data_.err[i] == 1) {
          //TODO(Krik): make some message to the decision
        }
      }
      break;
    case CONFIG_RESPONSE_ID: memcpy(&config_response_data_, data_addr, data_length);
      if (is_debug_) {
        printf("Config response-->%d\n", config_response_data_.chassis_config);
      }
      break;
    case CALI_RESPONSE_ID: memcpy(&cali_response_data_, data_addr, data_length);
      if (is_debug_) {
        printf("Cali response-->%d\n", cali_response_data_.type);
      }
      break;
    case REMOTE_CTRL_INFO_ID: memcpy(&rc_info_data_, data_addr, data_length);
      if (is_debug_) {
        printf("RC Info-->%d\n", rc_info_data_.ch1);
      }
      break;
    case BOTTOM_VERSION_ID: memcpy(&version_info_data_, data_addr, data_length);
      if (is_debug_) {
        printf("Bottom Version-->%d\n", version_info_data_.num[0]);
      }
      break;
    default:
      break;
  }
}

void SerialComNode::GimbalControlCallback(const rm_msgs::GimbalCtrl &msg) {
  printf("in GimbalControlCallback");
  uint8_t pack[PACK_MAX_SIZE];
  GimbalControl gimbal_control_data;
  gimbal_control_data.ctrl_mode = msg.ctrl_mode;//GIMBAL_POSITION_MODE
  gimbal_control_data.pit_ref = msg.pit_ref;
  gimbal_control_data.yaw_ref = msg.yaw_ref;
  gimbal_control_data.visual_valid = msg.visual_valid;
  int length = sizeof(GimbalControl), pack_length = length + HEADER_LEN + CMD_LEN + CRC_LEN;
  SendDataHandle(GIMBAL_CTRL_ID, (uint8_t *) &gimbal_control_data, pack, length);
  if (pack_length <= free_length_) {
    memcpy(tx_buf_ + total_length_, pack, pack_length);
    printf("gimbal_control_data %d",pack_length);
    free_length_ -= pack_length;
    total_length_ += pack_length;
  } else {
    LOG_WARNING << "Overflow in Gimbal CB";
  }
}

void SerialComNode::ChassisControlCallback(const geometry_msgs::Twist::ConstPtr &vel) {
  static int count = 0, time_ms = 0, compress = 0;
  static double frequency = 0;
  static struct timeval time_last, time_current;
  gettimeofday(&time_current, nullptr);
  if (count == 0) {
    count++;
  } else {
    time_ms = (time_current.tv_sec - time_last.tv_sec) * 1000 + (time_current.tv_usec - time_last.tv_usec) / 1000;
    frequency = 1000.0 / time_ms;
  }
  time_last = time_current;
  compress++;
  if (compress == COMPRESS_TIME) {
    std::unique_lock<std::mutex> lock(mutex_pack_);
    compress = 0;
    uint8_t pack[PACK_MAX_SIZE];
    ChassisControl chassis_control_data;
//TODO(Krik): get the effective command from the decision module
    chassis_control_data.ctrl_mode = AUTO_SEPARATE_GIMBAL;    //AUTO_FOLLOW_GIMBAL

    chassis_control_data.x_speed = vel->linear.x * 1000.0;
    chassis_control_data.y_speed = vel->linear.y * 1000.0;
    chassis_control_data.w_info.x_offset = 0;
    chassis_control_data.w_info.y_offset = 0;
    chassis_control_data.w_info.w_speed = vel->angular.z * 180.0 / M_PI;
    int length = sizeof(ChassisControl), pack_length = length + HEADER_LEN + CMD_LEN + CRC_LEN;
    SendDataHandle(CHASSIS_CTRL_ID, (uint8_t *) &chassis_control_data, pack, length);
    if (pack_length <= free_length_) {
      memcpy(tx_buf_ + total_length_, pack, pack_length);
      free_length_ -= pack_length;
      total_length_ += pack_length;
    } else {
      LOG_WARNING << "Overflow in Chassis CB";
    }
  }
}

void SerialComNode::ShootControlCallback(const rm_msgs::ShootCtrl &msg){
  
  ShootControl shoot_control_data;
  shoot_control_data.shoot_cmd = msg.shoot_cmd;
  shoot_control_data.c_shoot_cmd = msg.c_shoot_cmd;
  shoot_control_data.fric_wheel_run = msg.fric_wheel_run;
  shoot_control_data.fric_wheel_spd = 1230;
  uint8_t pack[PACK_MAX_SIZE];
  int length = sizeof(ShootControl), pack_length = length + HEADER_LEN + CMD_LEN + CRC_LEN;
  SendDataHandle(SHOOT_CTRL_ID, (uint8_t *) &shoot_control_data, pack, length);
  if (pack_length <= free_length_) {
    memcpy(tx_buf_ + total_length_, pack, pack_length);
    free_length_ -= pack_length;
    total_length_ += pack_length;
  } else {
    LOG_WARNING << "Overflow in Shoot CB";
  }
}
void SerialComNode::LaserScanCallback(const sensor_msgs::LaserScan::ConstPtr &msg)
{
  
  static LaserScanPoints laserScanPoints;
  static uint8_t pack[PACK_MAX_SIZE];
  
  int count = msg->scan_time / msg->time_increment;
  int peried = count/(LASER_SCAN_POINTS) + 0.5;
  
  printf("LaserScanCallback count:%d \n",count);
if(count < 300)
{
  printf("laser point not enough :%d",count);
}
for(int sample = 0;sample < LASER_SCAN_POINTS;++sample)
{
  int i = sample*peried;
  for(; i < (sample+1)*peried ; ++i) 
    {
      uint16_t tempdis = msg->ranges[i]*100 + 0.5;
      if(tempdis>29 && tempdis<200)
      {
	laserScanPoints.dis[sample] = tempdis;//cm
	float rad  = msg->angle_min + msg->angle_increment * i;
	laserScanPoints.angle[sample] = rad*180/3.14159 +0.5;//deg //180/3.14159=57.296
	break;
      }
    }
    if(i == (sample+1)*peried)//当前采样区域无有效点
    {
      laserScanPoints.dis[sample] = 65535;
      laserScanPoints.angle[sample] = (msg->angle_min + msg->angle_increment * (i-peried/2))*180/3.14159 +0.5;
    }
}
  int length = sizeof(LaserScanPoints), pack_length = length + HEADER_LEN + CMD_LEN + CRC_LEN;
  SendDataHandle(LASER_SCAN_DATA_ID, (uint8_t *) &laserScanPoints, pack, length);
  if (pack_length <= free_length_) {
    memcpy(tx_buf_ + total_length_, pack, pack_length);
    free_length_ -= pack_length;
    total_length_ += pack_length;
  } else {
    LOG_WARNING << "Overflow in LaserScanCallback";
  }
}

void SerialComNode::SendDataHandle(uint16_t cmd_id,
                                   uint8_t *topack_data,
                                   uint8_t *packed_data,
                                   uint16_t len
) {
  FrameHeader *p_header = (FrameHeader *) packed_data;
  p_header->sof = UP_REG_ID;
  p_header->data_length = len;
  memcpy(packed_data + HEADER_LEN, (uint8_t *) &cmd_id, CMD_LEN);
  AppendCrcOctCheckSum(packed_data, HEADER_LEN);
  memcpy(packed_data + HEADER_LEN + CMD_LEN, topack_data, len);
  AppendCrcHexCheckSum(packed_data, HEADER_LEN + CMD_LEN + CRC_LEN + len);
}

void SerialComNode::SendPack() {
  while (is_open_ && !stop_send_ && ros::ok()) {
    if (total_length_ > 0) {
      mutex_send_.lock();
      SendData(total_length_);
      total_length_ = 0;
      free_length_ = UART_BUFF_SIZE;
      mutex_send_.unlock();
    } else {
      usleep(100);
    }
  }
}

int SerialComNode::SendData(int data_len) {
  int length = 0;
  length = write(fd_, tx_buf_, data_len);
  lseek(fd_, 0, SEEK_CUR);
  std::cout << "Com sending: " << length << std::endl;
    
  if (length == data_len) {
    return length;
  } else {
    LOG_WARNING << "Serial write error";
    return -1;
  }
}

SerialComNode::~SerialComNode() {
  if (receive_loop_thread_ != nullptr) {
    stop_receive_ = true;
    receive_loop_thread_->join();
    delete receive_loop_thread_;
  }
  if (send_loop_thread_ != nullptr) {
    stop_send_ = true;
    send_loop_thread_->join();
    delete send_loop_thread_;
  }
  tcsetattr(fd_, TCSANOW, &termios_options_original_);
  close(fd_);
  is_open_ = false;
  if (is_debug_) {
    fclose(fp_);
  }
}

void SerialComNode::Stop() {
  stop_send_ = true;
  stop_receive_ = true;
}

void SerialComNode::Resume() {
  stop_send_ = false;
  stop_receive_ = false;
}

uint8_t SerialComNode::GetCrcOctCheckSum(uint8_t *message, uint32_t length, uint8_t crc) {
  uint8_t index;
  while (length--) {
    index = crc ^ (*message++);
    crc = kCrcOctTable[index];
  }
  return (crc);
}

bool SerialComNode::VerifyCrcOctCheckSum(uint8_t *message, uint16_t length) {
  uint8_t expected = 0;
  if ((message == 0) || (length <= 2)) {
    LOG_WARNING << "Verify CRC8 false";
    return false;
  }
  expected = GetCrcOctCheckSum(message, length - 1, kCrc8);
  return (expected == message[length - 1]);
}

void SerialComNode::AppendCrcOctCheckSum(uint8_t *message, uint16_t length) {
  uint8_t crc = 0;
  if ((message == 0) || (length <= 2)) {
    LOG_WARNING << "Append CRC8 NULL";
    return;
  };
  crc = GetCrcOctCheckSum(message, length - 1, kCrc8);
  message[length - 1] = crc;
}

uint16_t SerialComNode::GetCrcHexCheckSum(uint8_t *message, uint32_t length, uint16_t crc) {
  uint8_t data;
  if (message == NULL) {
    return 0xFFFF;
  }
  while (length--) {
    data = *message++;
    (crc) = ((uint16_t) (crc) >> 8) ^ kCrcTable[((uint16_t) (crc) ^ (uint16_t) (data)) & 0x00ff];
  }
  return crc;
}

bool SerialComNode::VerifyCrcHexCheckSum(uint8_t *message, uint32_t length) {
  uint16_t expected = 0;
  if ((message == NULL) || (length <= 2)) {
    LOG_WARNING << "Verify CRC16 bad";
    return false;
  }
  expected = GetCrcHexCheckSum(message, length - 2, kCrc);
  return ((expected & 0xff) == message[length - 2] && ((expected >> 8) & 0xff) == message[length - 1]);
}

void SerialComNode::AppendCrcHexCheckSum(uint8_t *message, uint32_t length) {
  uint16_t crc = 0;
  if ((message == NULL) || (length <= 2)) {
    LOG_WARNING << "Append CRC 16 NULL";
    return;
  }
  crc = GetCrcHexCheckSum(message, length - 2, kCrc);
  message[length - 2] = (uint8_t) (crc & 0x00ff);
  message[length - 1] = (uint8_t) ((crc >> 8) & 0x00ff);
}

} //namespace serial
} //namespace driver
} //namespace rrts
MAIN(rrts::driver::serial::SerialComNode, "serial_com_node")
