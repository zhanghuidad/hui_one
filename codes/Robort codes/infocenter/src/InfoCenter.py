from __future__ import division

import rospy
import numpy as np
import math
import copy
import info_sub_pub as isp
import utils

if __name__ == '__main__':
	cam_trans = []
	for i in range(2):
		cam_trans += [utils.Cam_trans(512,288,i)]
	cam_gun_trans = utils.Cam_gun_trans(512,288)

	rospy.init_node('InfoCenter', anonymous=True)

	cam_chassis_sub = isp.Cam_Chassis_Sub()
	cam_gunpoint_sub = isp.Cam_Gunpoint_Sub()
	pose1_sub = isp.Pose_Sub('amcl_pose')
	pose2_sub = isp.Pose_Sub('amcl_pose2')
	laser_sub = isp.Laser_Sub()
	gimbal_sub = isp.Gimbal_Sub()
	'''
				fresh rate
	chassis		>40 Hz
	gunpoint	>20 Hz
	pose1		~12 Hz
	pose2		~12 Hz
	laser		~10 Hz
	gimbal		140 Hz
	'''
	info_chassis = utils.InfoCopy(cam_chassis_sub, 10)
	info_gunpoint = utils.InfoCopy(cam_gunpoint_sub, 50)
	info_pose1 = utils.InfoCopy(pose1_sub, 7)
	info_pose2 = utils.InfoCopy(pose2_sub, 7)
	info_laser = utils.InfoCopy(laser_sub, 2)
	info_gimbal = utils.InfoCopy(gimbal_sub, 10)
	# Gimbal fresh rate unknown

	#strategy_info_pub = isp.Strategy_Info_Pub()
	gimbal_control_info_pub = isp.Gimbal_Control_Info_Pub()

	
	print('ROS Node Initialized.')
	r = rospy.Rate(100)

	ready = 0
	while ready < 6:
		ready = 0
		ready += info_chassis.check()
		ready += info_gunpoint.check()
		ready += info_pose1.check()
		ready += info_pose2.check()
		ready += info_laser.check()
		ready += info_gimbal.check()
		print(info_chassis.check(),info_pose1.check(),info_pose2.check(),info_laser.check(),info_gimbal.check())
	print('Info Is Ready.')

	ally = utils.Ally([copy.deepcopy(pose1_sub.info),copy.deepcopy(pose2_sub.info)])
	enemy = utils.Enemy(ally, cam_trans, cam_gun_trans)

	update_ally = [0,0]
	update_enemy = 0
	update_strategy = 0
	update_gun = 0

	while not rospy.is_shutdown():

		info_chassis()
		info_gunpoint()
		info_pose1()
		info_pose2()
		info_laser()
		info_gimbal()

		# Update ally pose
		if update_ally[0] != info_pose1.stamp[-1] or update_ally[1] != info_pose2.stamp[-1]:
			update_ally = [info_pose1.stamp[-1],info_pose2.stamp[-1]]

			extract_pose1	= info_pose1.extract_stamp(update_ally[0])
			extract_pose2	= info_pose2.extract_stamp(update_ally[1])

			ally.update_pose([extract_pose1,extract_pose2])

		# Update enemy position
		if update_enemy != info_laser.stamp[-1]:
			update_enemy = info_laser.stamp[-1]

			extract_chassis	= info_chassis.extract_stamp(update_enemy)
			extract_laser	= info_laser.info[-1]

			enemy.update_pose(extract_chassis,extract_laser)

		# Update strategy selection
		#if update_strategy != info_strategy.stamp[-1]:
		#	update_strategy = info_strategy.stamp[-1]

		#	enemy.updage_strategy(0)


		# Update gunpoint aiming
		if update_gun != info_gunpoint.stamp[-1]:
			update_gun = info_gunpoint.stamp[-1]

			extract_gunpoint = info_gunpoint.extract_stamp(update_gun)
			extract_gimbal	 = info_gimbal.extract_stamp(update_gun)

			enemy.update_aim(extract_gunpoint, extract_gimbal)

		enemy.check_status()
		if enemy.Robot_status[0] == 1:
			enemy.selected_index = 0

		# Publish PID

		#strategy_info_pub()
		result = {'stamp':rospy.Time.now(),'gim_x':0.0,'gim_y':0.0,
										   'rad_x':0.0,'rad_y':0.0,
										   'dis':0.0,'info_type':0}
		if enemy.selected_index is not None:
			pos_x = enemy.Robot[enemy.selected_index].rb.rel_pos_x
			pos_y = enemy.Robot[enemy.selected_index].rb.rel_pos_y
			angle = math.atan2(pos_y, pos_x) - ally.info['psi'][0]
			if angle > math.pi:
				angle -= math.pi * 2
			elif angle < -math.pi:
				angle += math.pi * 2
			result['gim_x'] = 0.0
			result['gim_y'] = angle
			result['dis'] = (pos_x**2 + pos_y**2) ** 0.5
			if enemy.Robot[enemy.selected_index].am.rad_x is None:
				result['info_type'] = 1
			else:
				result['rad_x'] = enemy.Robot[enemy.selected_index].am.rad_x
				result['rad_y'] = enemy.Robot[enemy.selected_index].am.rad_y
				result['info_type'] = 2

		#enemy.Robot[0].rb.show()
		#enemy.Robot[0].lb.show()
		#enemy.Robot[0].am.show()
		gimbal_control_info_pub(result)
		r.sleep()
		
		
		
		
		
		
		
		
