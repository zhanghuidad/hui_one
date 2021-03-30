import rospy
from std_msgs.msg import Header
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import PoseStamped
from rm_msgs.msg import GimbalAngle
from detection.msg import cam_chassis, cam_gunpoint
from infocenter.msg import gimbal_control_info


class Cam_Chassis_Sub:
	def __init__(self):
		self.sub = rospy.Subscriber('cam_chassis', cam_chassis, self.callback)
		self.info = None

	def callback(self, data):
		self.info = {'stamp':data.header.stamp,
					 'x':data.x,
					 'y':data.y, 
					 'xmin':data.xmin,
					 'ymin':data.ymin,
					 'xmax':data.xmax,
					 'ymax':data.ymax,
					 'tar_type':data.tar_type,
					 'cam_num':data.cam_num,
					 'tar_num':data.tar_num}

class Cam_Gunpoint_Sub:
	def __init__(self):
		self.sub = rospy.Subscriber('cam_gunpoint', cam_gunpoint, self.callback)
		self.info = None
		self.info = {'stamp':rospy.Time.now(),
					 'x':[],
					 'y':[], 
					 'xmin':[],
					 'ymin':[],
					 'xmax':[],
					 'ymax':[],
					 'tar_num':0}

	def callback(self, data):
		self.info = {'stamp':data.header.stamp,
					 'x':data.x,
					 'y':data.y, 
					 'xmin':data.xmin,
					 'ymin':data.ymin,
					 'xmax':data.xmax,
					 'ymax':data.ymax,
					 'tar_num':data.tar_num}

class Pose_Sub:
	def __init__(self, name):
		if '2' not in name:
			self.sub = rospy.Subscriber(name, PoseStamped, self.callback)
		self.info = None
		self.info = {'stamp':rospy.Time.now(),
					 'pos_x':0,
					 'pos_y':0,
					 'pos_z':0,
					 'ori_x':1,
					 'ori_y':0,
					 'ori_z':0,
					 'ori_w':0}


	def callback(self,data):
		self.info = {'stamp':data.header.stamp,
					 'pos_x':data.pose.position.x,
					 'pos_y':data.pose.position.y,
					 'pos_z':data.pose.position.z,
					 'ori_x':data.pose.orientation.x,
					 'ori_y':data.pose.orientation.y,
					 'ori_z':data.pose.orientation.z,
					 'ori_w':data.pose.orientation.w}

class Laser_Sub:
	def __init__(self):
		self.sub = rospy.Subscriber('scan', LaserScan, self.callback)
		self.info = None

	def callback(self,data):
		self.info = {'stamp':data.header.stamp,
					 'angle_min':data.angle_min,
					 'angle_max':data.angle_max,
					 'angle_increment':data.angle_increment,
					 'time_increment':data.time_increment,
					 'scan_time':data.scan_time,
					 'range_min':data.range_min,
					 'range_max':data.range_max,
					 'ranges':data.ranges,
					 'intensities':data.intensities}


class Gimbal_Sub:
	def __init__(self):
		self.sub = rospy.Subscriber('gimbal', GimbalAngle, self.callback)
		self.info = None

	def callback(self,data):
		# Add Header to Gimbal Msg
		self.info = {'pitch':data.pitch,
					 'yaw':data.yaw,
					 'pitch_rate':data.pitch_rate,
					 'yaw_rate':data.yaw_rate}


class Strategy_Info_Pub:
	def __init__(self):
		raise NotImplementedError

	def __call__(self, result):
		raise NotImplementedError


class Gimbal_Control_Info_Pub:
	def __init__(self):
		self.pub = rospy.Publisher('gimbal_control_info', gimbal_control_info, queue_size=4)

	def __call__(self, result):
		self.pub.publish(header		= Header(stamp=result['stamp']),
						 gim_x		= result['gim_x'],
						 gim_y		= result['gim_y'],
						 rad_x		= result['rad_x'],
						 rad_y		= result['rad_y'],
						 dis		= result['dis'],
						 info_type	= result['info_type'])
