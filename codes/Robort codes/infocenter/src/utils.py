from __future__ import division

import rospy
import numpy as np
import copy
import math
import warnings

'''
-------          ----------          -------
\      \        /          \        /      /
 \      \      /            \      /      /
  \      \    /      /\      \    /      /
   \      \  /      /  \      \  /      /
    \      \/      /    \      \/      /
     \            /      \            /
      \          /        \          /
       \        /          \        /
        \      /            \      /
         ------              ------

           --------      --------
           |      |      |      |
           |      |      |      |
           |      --------      |
           |                    |
           |                    |
           |                    |
           |      --------      |
           |      |      |      |
           |      |      |      |
           --------      --------

                 ----------
                /          \
               /            \
              /      /\      \
             /      /  \      \
            /      ------      \
           /                    \
          /      ----------      \
         /      /          \      \
        /      /            \      \
       --------              \------\

          ------------------------
          |                      |
          |                      |
          ---------      ---------
                  |      |
                  |      |
                  |      |
                  |      |
                  |      |
                  |      |
                  --------



          ------------------------
          |                      |
          |                      |
          ---------      ---------
                  |      |
                  |      |
                  |      |
                  |      |
                  |      |
                  |      |
                  --------

           --------      --------
           |      |      |      |
           |      |      |      |
           |      --------      |
           |                    |
           |                    |
           |                    |
           |      --------      |
           |      |      |      |
           |      |      |      |
           --------      --------

           ----------------------
           |                    |
           |     ----------------
           |     |
           |     ----------------
           |                    |
           |     ----------------
           |     |
           |     ----------------
           |                    |
           ----------------------



           ----------------------
           |                    |
           |     ----------------
           |     |
           |     ----------------
           |                    |
           |     ----------------
           |     |
           |     |
           |     |
           -------

           --------      --------
           |      |      |      |
           |      |      |      |
           |      |      |      |
           |      |      |      |
           |      |      |      |
           |      |      |      |
           |      --------      |
            \                  /
             \                /
              ----------------

              ----------------
             /                \
            /     ----------   \
           |     /          \   |
           |    /            ----
           |   |
           |    \            ----
           |     \          /   |
            \     ----------   /
             \                / 
              ----------------

           -------          -----
           |     |        /     /
           |     |       /     /
           |     |      /     /
           |     -------     /
           |                |
           |     -------     \
           |     |      \     \
           |     |       \     \
           |     |        \     \
           -------        -------



                     ----
                    /    \
                   /      \
                  |        |
                  |        |
                  |        |
                  | ------ |
                  |        |
                  |        |
                  |        |
  ------   ------ |        | ------  
 /      \ /      \|        |/      \ 
|        |        | ------ |        |
|        |        |        |        |
| ------ | ------ |        | --------------
|  ----  |  ----  |        |/ ___        / \
|  |  |  |  |  |  |        |  | |       /   \
|\ ---- / \ ---- /          \ ---      /     \
| \    /   \    /            ----------       |
|  ----     ----              ----    |       |
|                                     |       |
|                                     |       |
|                                            /
|                                           /
|                                          /
|                                         /
|                                        /
|                                       /
|                                      /
|                                     |
---------------------------------------


'''

class InfoCopy:
	def __init__(self, sub, limit):
		self.sub = sub
		self.limit = limit

	def __call__(self):
		info_now = copy.deepcopy(self.sub.info)
		if 'stamp' in info_now:
			info_now['stamp'] = info_now['stamp']
		elif 'header' in info_now:
			info_now['stamp'] = info_now['header'].stamp
			info_now.pop('header')
		else:
			info_now['stamp'] = rospy.Time.now()

		info_now['stamp'] = float(str(info_now['stamp'].secs)+'.'+str(info_now['stamp'].nsecs)) 
		if info_now['stamp'] == self.info[-1]['stamp']:
			return None
		else:
			self.info += [info_now]
			self.stamp += [info_now['stamp']]
			if len(self.info) > self.limit:
				self.info = self.info[len(self.info)-self.limit:]
				self.stamp = self.stamp[len(self.stamp)-self.limit:]

	def check(self):
		if self.sub.info is None:
			return 0
		else:
			info_now = copy.deepcopy(self.sub.info)
			if 'stamp' in info_now:
				info_now['stamp'] = info_now['stamp']
			elif 'header' in info_now:
				info_now['stamp'] = info_now['header'].stamp
				info_now.pop('header')
			else:
				info_now['stamp'] = rospy.Time.now()
			info_now['stamp'] = float(str(info_now['stamp'].secs)+'.'+str(info_now['stamp'].nsecs)) 
			self.info = [copy.deepcopy(info_now)]
			self.stamp = [info_now['stamp']]
			return 1

	def extract_stamp(self, stamp):
		stamp_l = copy.deepcopy(self.stamp)
		stamp_l.reverse()
		length = len(stamp_l)
		stamp_l = abs(np.array(stamp_l) - stamp)
		index = length - np.argmin(stamp_l) - 1
		return self.info[index]

class Ally:
	def __init__(self, pose):
		self.info_id = ['pos_x','pos_y','pos_z',
						'ori_x','ori_y','ori_z','ori_w']

		self.info = {}
		for id_ in self.info_id:
			self.info[id_] = [pose[0][id_],pose[1][id_]]
		self.calc_euler()

	def update_pose(self, pose):
		for id_ in self.info_id:
			self.info[id_] = [pose[0][id_],pose[1][id_]]
		self.calc_euler()

	def calc_euler(self):
		phi1, theta1, psi1 = Q2Euler(self.info['ori_x'][0],
									 self.info['ori_y'][0],
									 self.info['ori_z'][0],
									 self.info['ori_w'][0])
		phi2, theta2, psi2 = Q2Euler(self.info['ori_x'][0],
									 self.info['ori_y'][0],
									 self.info['ori_z'][0],
									 self.info['ori_w'][0])
		self.info['phi'] = [phi1,phi2]
		self.info['theta'] = [theta1,theta2]
		self.info['psi'] = [psi1,psi2]
		#print(self.info['phi'],self.info['theta'],self.info['psi'])

def Q2Euler(x,y,z,w):
	phi	  = math.atan2(2*(w*x+y*z),1-2*(x**2+y**2))
	theta = math.asin(2*(w*y-z*x))
	psi	  = math.atan2(2*(w*z+x*y),1-2*(y**2+z**2))
	return phi, theta, psi

class Armour:
	def __init__(self):
		self.pos_x = None
		self.pos_y = None
		self.pixel_x = None
		self.pixel_y = None
		self.rad_x = None
		self.rad_y = None

	def check(self):
		if self.pos_x is not None:
			return True
		elif self.pixel_x is not None:
			return True
		else:
			return False
			
	def show(self):
		instr = ''
		l = ['pos_x','pos_y','pixel_x','pixel_y','rad_x','rad_y']
		l_ = [self.pos_x,self.pos_y,self.pixel_x,self.pixel_y,self.rad_x,self.rad_y]
		for i in range(len(l)):
			instr += l[i] + ' '
			if l_[i] is not None:
				instr += '%.5f '%l_[i]
			else:
				instr += 'None '
		print(instr)

class Lightbar:
	def __init__(self):
		self.pos_x = None
		self.pos_y = None

	def check(self):
		if self.pos_x is not None:
			return True
		elif self.pos_y is not None:
			return True
		else:
			return False

	def show(self):
		instr = ''
		l = ['pos_x','pos_y']
		l_ = [self.pos_x,self.pos_y]
		for i in range(len(l)):
			instr += l[i] + ' '
			if l_[i] is not None:
				instr += '%.5f '%l_[i]
			else:
				instr += 'None '
		print(instr)

class Robot:
	def __init__(self):
		self.rel_pos_x = None
		self.rel_pos_y = None
		self.abs_pos_x = None
		self.abs_pos_y = None

	def check(self):
		if self.rel_pos_x is not None:
			if self.abs_pos_x is None:
				assert False
			return True
		else:
			return False
			
	def show(self):
		instr = ''
		l = ['rel_pos_x','rel_pos_y','abs_pos_x','abs_pos_y']
		l_ = [self.rel_pos_x,self.rel_pos_y,self.abs_pos_x,self.abs_pos_y]
		for i in range(len(l)):
			instr += l[i] + ' '
			if l_[i] is not None:
				instr += '%.5f '%l_[i]
			else:
				instr += 'None '
		print(instr)

class Mix:
	def __init__(self):
		self.Max_keep = 2
		self.am = Armour()
		self.lb = Lightbar()
		self.rb = Robot()
		self.keep = 0
		self.is_active = 0
		self.is_selected = 0

	def check(self):
		if self.am.check() or self.lb.check():
			self.is_active = 1
		else:
			self.is_active = 0
		return self.is_active

	def reinit(self):
		del self.am
		del self.lb
		del self.rb
		self.am = Armour()
		self.lb = Lightbar()
		self.rb = Robot()
		self.keep = 0
		self.is_active = 0
		self.is_selected = 0

class Enemy:
	def __init__(self, ally, trans, gun_trans):
		self.ally = ally
		self.trans = trans
		self.gun_trans = gun_trans

		self.Robot = [Mix(),Mix()]
		self.Robot_status = [self.Robot[0].check(), self.Robot[1].check()]
		self.num_active = self.Robot[0].check() + self.Robot[1].check()
		self.selected_index = None

		self.lb_min_angle = math.pi/18
		self.lb_min_dis = 0.2

		self.am2lb_max_dis = 0.6
		
	def update_pose(self, chassis, laser):
		chassis_trans = {'x':[],
						 'y':[],
						 'rad_x':[],
						 'rad_y':[],
						 'angle':[],
						 'est_dis':[],
						 'real_dis':[],
						 'type':[],
						 'cam_num':[],
						 'index_armour':[],
						 'index_lightbar':[],
						 'count':0}

		c = 0
		for i in range(chassis['tar_num']):
			rad_x, rad_y, angle, est_dis = self.trans[int(chassis['cam_num'][i])](chassis['x'][i],
																				  chassis['y'][i],
																				  chassis['tar_type'][i])
			x, y, real_dis = self.extract_tar_pos(angle, est_dis, laser)
			if chassis['tar_type'][i] == 0:
				if rad_y < -math.pi / 9:
					continue
			elif chassis['tar_type'][i] == 1:
				if rad_y > math.pi / 9:
					continue
			else:
				raise TypeError('Unknown chassis type with type '+str(chassis['tar_type'][i]))
			
			chassis_trans['x']		  += [x]
			chassis_trans['y']		  += [y]
			chassis_trans['rad_x']	  += [rad_x]
			chassis_trans['rad_y']	  += [rad_y]
			chassis_trans['angle']	  += [angle]
			chassis_trans['est_dis']  += [est_dis]
			chassis_trans['real_dis'] += [real_dis]
			chassis_trans['type']	  += [chassis['tar_type'][i]]
			chassis_trans['cam_num']  += [chassis['cam_num'][i]]
			chassis_trans['count']	  += 1
			if chassis['tar_type'][i] == 0:
				chassis_trans['index_armour'] += [c]
			elif chassis['tar_type'][i] == 1:
				chassis_trans['index_lightbar'] += [c]
			assert not math.isnan(chassis_trans['x'][c])
			c += 1
		#for id_ in chassis_trans:
		#	print(id_, chassis_trans[id_])
		# TODO
		# If needed, add filter to chassis basing on ally pos
		self.match_info(chassis_trans)

	def extract_tar_pos(self, angle, dis, laser):

		angle_laser = angle
		if angle_laser > math.pi:
			angle_laser -= math.pi*2
		k = int(round(angle_laser / laser['angle_increment']))
		if k < 0:
			k = len(laser['ranges']) + k

		angle_range = 3
		point_list = [k-i for i in range(-angle_range,angle_range+1)]
		for i in range(len(point_list)):
			if point_list[i] < 0:
				point_list[i] = len(laser['ranges']) + point_list[i]
			elif point_list[i] >= len(laser['ranges']):
				point_list[i] = point_list[i] - len(laser['ranges'])
		#print(laser['ranges'][175:185])
		#print(laser['ranges'], k)
		ranges = np.array(laser['ranges'])[point_list]
		intensities = np.array(laser['intensities'])[point_list].astype('int32')
		#print(ranges)
		#print(laser['ranges'][270:])
		ranges[ranges==float('inf')] = 0
		intensities[intensities==47] = 1
		
		# WARNING
		# Lidar Axis different to Robot Axis?
		# Extract Lidar index may be wrong!
		if (ranges*intensities).max() == 0:
			d = dis
		else:
			ranges = ranges*intensities
			index = ranges.nonzero()
			d = ranges[index].mean()
			assert not math.isnan(d)

		x = d * math.cos(angle+self.ally.info['psi'][0])
		y = d * math.sin(angle+self.ally.info['psi'][0])

		return x, y, d

	def match_info(self, chassis):
		# Match Detected Lightbar
		# DM for Differential Matrix
		# am for armour
		# lb for lightbar
		
		robot = {'absolute_x':[],'absolute_y':[],
				 'rb_x':[],'rb_y':[],'rb_angle':[],'rb_real_dis':[],
				 'am_x':[],'am_y':[],'am_angle':[],'am_real_dis':[],
				 'lb_x':[],'lb_y':[],'lb_angle':[],'lb_real_dis':[],
				 'have_armour':[],'have_lightbar':[],'count':0}
		id_list = {'x','y','angle','real_dis'}
		len_am_ori = len(chassis['index_armour'])
		len_lb_ori = len(chassis['index_lightbar'])

		if len_lb_ori > 1:
			DM_lb_angle = np.array(chassis['angle'])[chassis['index_lightbar']]
			DM_lb_angle = np.concatenate([np.abs(DM_lb_angle-i) for i in DM_lb_angle],axis=0).reshape([len_lb_ori,len_lb_ori])
			max_lb_angle = DM_lb_angle.max()
			sep_lb_angle = np.argmax(DM_lb_angle)
			if max_lb_angle > self.lb_min_angle:
				robot['count'] = 2
				
				lb_1 = chassis['index_lightbar'][int(sep_lb_angle // len_lb_ori)]
				lb_2 = chassis['index_lightbar'][int(sep_lb_angle - int(sep_lb_angle // len_lb_ori)*len_lb_ori)]
				lb_1_list = [lb_1]
				lb_2_list = [lb_2]
				for i in chassis['index_lightbar']:
					if i == lb_1 or i == lb_2:
						continue
					if abs(chassis['angle'][i] - chassis['angle'][lb_1]) > abs(chassis['angle'][i] - chassis['angle'][lb_2]):
						lb_2_list += [i]
					else:
						lb_1_list += [i]
				for id_ in id_list:
					lb_id_ = 'lb_' + id_
					robot[lb_id_] = [np.mean(np.array(chassis[id_])[lb_1_list]),np.mean(np.array(chassis[id_])[lb_2_list])]
				robot['have_lightbar'] += [1]
				robot['have_lightbar'] += [1]
			else:
				robot['count'] = 1
				for id_ in id_list:
					lb_id_ = 'lb_' + id_
					robot[lb_id_] = [np.mean(np.array(chassis[id_])[chassis['index_lightbar']])]
				robot['have_lightbar'] += [1]

		elif len_lb_ori == 1:
			robot['count'] = 1
			for id_ in id_list:
				lb_id_ = 'lb_' + id_
				robot[lb_id_] = [np.mean(np.array(chassis[id_])[chassis['index_lightbar']])]
			robot['have_lightbar'] += [1]

		while len(robot['have_lightbar']) < 2:
			for id_ in id_list:
				robot['lb_'+id_] += [None]
			robot['have_lightbar'] += [0]
		assert len(robot['lb_x']) == 2
		if robot['lb_x'][0] is not None:
			assert not math.isnan(robot['lb_x'][0])
		if robot['lb_x'][1] is not None:
			assert not math.isnan(robot['lb_x'][1]) 

		#print(robot['have_lightbar'])

		# Match Detected Armour with Lightbar -> Robot
		# Case1: 2 Lightbar and Armour
		# Case2: 1 Lightbar and Armour
		# Case3: 0 Lightbar and Armour


		if robot['count'] == 2:# Case 1
			am2lb_list = [[],[]]
			for i in chassis['index_armour']:
				miss_count = 0
				for j in range(2):
					if ((robot['lb_x'][j]-chassis['x'][i])**2+(robot['lb_y'][j]-chassis['y'][i])**2)**0.5 < self.am2lb_max_dis:
						am2lb_list[j] += [i]
					else:
						miss_count += 1
				if miss_count == 2:
					warnings.warn('Ignore a Armour due to no lightbar nearby.')

		elif robot['count'] == 1:# Case 2
			am2lb_list = [[],[]]
			potential_list = []
			for i in chassis['index_armour']:
				if ((robot['lb_x'][0]-chassis['x'][i])**2+(robot['lb_y'][0]-chassis['y'][i])**2)**0.5 < self.am2lb_max_dis:
					am2lb_list[0] += [i]
				else:
					potential_list += [i]

			if len(potential_list) == 1:
				am2lb_list[1] += [potential_list[0]]
			elif len(potential_list) > 1:
				len_ptt = len(potential_list)
				DM_am2lb_x = np.array(chassis['x'])[potential_list]
				DM_am2lb_y = np.array(chassis['y'])[potential_list]
				DM_am2lb_x = np.concatenate([np.abs(DM_am2lb_x-i) for i in DM_am2lb_x],axis=0).reshape([len_ptt,len_ptt])
				DM_am2lb_y = np.concatenate([np.abs(DM_am2lb_y-i) for i in DM_am2lb_y],axis=0).reshape([len_ptt,len_ptt])
				DM_am2lb_dis = (DM_am2lb_x**2+DM_am2lb_y**2)**0.5
				DM_am2lb_dis[DM_am2lb_dis<=self.am2lb_max_dis] = -1
				DM_am2lb_dis[DM_am2lb_dis>self.am2lb_max_dis] = 0
				DM_am2lb_dis = -DM_am2lb_dis
					
				real_list = []
				if len_ptt == 2:
					if DM_am2lb_dis[:,0].sum() == 2:
						real_list = potential_list
				else:
					for i in range(len_ptt):
						if DM_am2lb_dis[:,i].sum() >= len_ptt/2:
							real_list += [potential_list[i]]

				if len(real_list) > 0:
					am2lb_list[1] = real_list

		elif robot['count'] == 0:# Case 3
			am2lb_list = [[],[]]
			if len_am_ori == 1:
				am2lb_list[0] += [chassis['index_armour']]
			elif len_am_ori >= 2:
				DM_am2lb_x = np.array(chassis['x'])[chassis['index_armour']]
				DM_am2lb_y = np.array(chassis['y'])[chassis['index_armour']]
				DM_am2lb_x = np.concatenate([np.abs(DM_am2lb_x-i) for i in DM_am2lb_x],axis=0).reshape([len_am_ori,len_am_ori])
				DM_am2lb_y = np.concatenate([np.abs(DM_am2lb_y-i) for i in DM_am2lb_y],axis=0).reshape([len_am_ori,len_am_ori])
				DM_am2lb_dis = (DM_am2lb_x**2+DM_am2lb_y**2)**0.5
				DM_am2lb_dis[DM_am2lb_dis<=self.am2lb_max_dis] = -1
				DM_am2lb_dis[DM_am2lb_dis>self.am2lb_max_dis] = 0
				DM_am2lb_dis = -DM_am2lb_dis
				if len_am_ori == 2:
					if DM_am2lb_dis[:,0].sum() > 1:
						am2lb_list[0] = chassis['index_armour']
					else:
						am2lb_list[0] = [chassis['index_armour'][0]]
						am2lb_list[1] = [chassis['index_armour'][1]]
				else:
					print(DM_am2lb_dis)
					potential_list = [DM_am2lb_dis[:,i].sum() for i in range(len_am_ori)]
					for i in range(2):
						print(potential_list)
						count = max(potential_list)
						if count > 1:
							center = potential_list.index(count)
							dis_list = list(np.array(DM_am2lb_dis[:,center]))
							print(dis_list)
							am_list = []
							for j in range(len(dis_list)):
								if dis_list[j] > 0:
									am_list += [j]
							am2lb_list[i] = [np.array(chassis['index_armour'])[am_list]]

							for j in am_list.reverse():
								del potential_list[j]
						else:
							break
						if len(potential_list) == 0:
							break

		else:
			raise TypeError('Unknown robot count with num '+str(robot['count']))

		empty_lightbar_count = 0
		for i in range(2):

			if len(am2lb_list[i]) > 0:
				robot['am_x'] += [np.mean(np.array(chassis['x'])[am2lb_list[i]])]
				robot['am_y'] += [np.mean(np.array(chassis['y'])[am2lb_list[i]])]
				robot['am_angle'] += [np.mean(np.array(chassis['angle'])[am2lb_list[i]])]
				dis = (robot['am_x'][i]**2 + robot['am_y'][i]**2)**0.5
				robot['am_real_dis'] += [dis]
				robot['have_armour'] += [1]
			else:
				robot['am_x'] += [None]
				robot['am_y'] += [None]
				robot['am_angle'] += [None]
				robot['am_real_dis'] += [None]
				robot['have_armour'] += [0]
				empty_lightbar_count += 1
		if empty_lightbar_count == 2 and sum(robot['have_lightbar']) == 2:
			warnings.warn('Both lightbars dont match any armours.')
		if robot['count'] < sum(robot['have_armour']):
			robot['count'] = sum(robot['have_armour'])

		for i in range(robot['count']):
			if robot['have_armour'][i] == 1 and robot['have_lightbar'][i] == 1:
				for id_ in id_list:
					robot['rb_'+id_] += [(robot['am_'+id_][i] + robot['lb_'+id_][i]) / 2]
			elif robot['have_armour'][i] == 1 and robot['have_lightbar'][i] == 0:
				for id_ in id_list:
					robot['rb_'+id_] += [robot['am_'+id_][i]]
			elif robot['have_armour'][i] == 0 and robot['have_lightbar'][i] == 1:
				for id_ in id_list:
					robot['rb_'+id_] += [robot['lb_'+id_][i]]
			else:
				raise RuntimeError('Robot saved with no armour and lightbar pos.')
		while len(robot['rb_x']) < 2:
			for id_ in id_list:
				robot['rb_'+id_] += [None]
		for i in range(2):
			if robot['rb_x'][i] is not None:
				robot['absolute_x'] += [robot['rb_x'][i]+self.ally.info['pos_x'][0]]
				robot['absolute_y'] += [robot['rb_y'][i]+self.ally.info['pos_y'][0]]
			else:
				robot['absolute_x'] += [None]
				robot['absolute_y'] += [None]


		# Match Detected Robot with Last Frame
		# Case 1: Two Target Existed in Last Frame
		# Case 2: One Target Existed in Last Frame
		# Case 3: No Target Existed in Last Frame
		# match---- index: 0,1 -> num for self.Robot list
		# 		|
		#		|-- value: 0,1 -> num for robot[''] list
		# 		|
		#		|-- value: -1 -> this target have no match
		match = [-1,-1]
		if self.num_active == 2:
			if robot['count'] == 2:
				M_dis = np.zeros([2,2])
				for i in range(2):
					for j in range(2):
						M_dis[i,j] += (robot['absolute_x'][i]-self.Robot[j].rb.abs_pos_x)**2
						M_dis[i,j] += (robot['absolute_y'][i]-self.Robot[j].rb.abs_pos_y)**2
				if M_dis[0,0] + M_dis[1,1] < M_dis[0,1] + M_dis[1,0]:
					match[0] = 0
					match[1] = 1
				else:
					match[0] = 1
					match[1] = 0

			elif robot['count'] == 1:
				M_dis = []
				for j in range(2):
					M_dis += [(robot['absolute_x'][0]-self.Robot[j].rb.abs_pos_x)**2]
					M_dis += [(robot['absolute_y'][0]-self.Robot[j].rb.abs_pos_y)**2]
				if M_dis[0]< M_dis[1]:
					match[0] = 0
				else:
					match[1] = 0
			elif robot['count'] == 0:
				match = match
			else:
				raise RuntimeError('Wrong robot count num.')

		elif self.num_active == 1:
			j = np.argmax(self.Robot_status)
			if robot['count'] == 2:
				M_dis = []
				for i in range(2):
					M_dis += [(robot['absolute_x'][i]-self.Robot[j].rb.abs_pos_x)**2]
					M_dis += [(robot['absolute_y'][i]-self.Robot[j].rb.abs_pos_y)**2]
				if M_dis[0]< M_dis[1]:
					match[j] = 0
					match[1-j] = 1
				else:
					match[j] = 1
					match[1-j] = 0

			elif robot['count'] == 1:
				match[j] = 0
			elif robot['count'] == 0:
				match = match
			else:
				raise RuntimeError('Wrong robot count num.')

		elif self.num_active == 0:
			if robot['count'] == 2:
				match = [0,1]
			elif robot['count'] == 1:
				match = [0,-1]
			else:
				match = [-1,-1]

		else:
			raise RuntimeError('Wrong saved robot num.')

		for i in range(2):
			if match[i] == -1:
				self.Robot[i].keep += 1
				'''
				if self.Robot[i].keep > self.Robot[i].Max_keep:
					self.Robot[i].reinit()
				'''
			else:
				self.Robot[i].rb.rel_pos_x = robot['rb_x'][match[i]]
				self.Robot[i].rb.rel_pos_y = robot['rb_y'][match[i]]
				self.Robot[i].rb.abs_pos_x = robot['absolute_x'][match[i]]
				self.Robot[i].rb.abs_pos_y = robot['absolute_y'][match[i]]
				assert robot['absolute_x'][match[i]] is not None
				self.Robot[i].am.pos_x = robot['am_x'][match[i]]
				self.Robot[i].am.pos_y = robot['am_y'][match[i]]
				self.Robot[i].lb.pos_x = robot['lb_x'][match[i]]
				self.Robot[i].lb.pos_y = robot['lb_y'][match[i]]
				self.Robot[i].check()

		self.num_active = self.Robot[0].check() + self.Robot[1].check()
		self.Robot_status = [self.Robot[0].check(), self.Robot[1].check()]


	def update_strategy(self, selection):
		self.Robot[0].is_selected = 0
		self.Robot[1].is_selected = 0
		self.selected_index = None
		if selection is not None:
			if self.Robot[selection].check():
				self.Robot[selection].is_selected = 1
				self.selected_index = selection

	def update_aim(self, gunpoint, gimbal):
		#print(gimbal)
		gun_rad_x = math.radians(gimbal['pitch']) + self.ally.info['psi'][0]
		if self.selected_index is not None:
			x = self.Robot[self.selected_index].rb.rel_pos_x
			y = self.Robot[self.selected_index].rb.rel_pos_y

			#print(abs(gun_rad_x-math.atan2(y,x)),gunpoint)
			if abs(gun_rad_x-math.atan2(y,x)) < math.pi / 3 and gunpoint['tar_num'] > 0:
				size_list = [abs(gunpoint['xmax'][i]-gunpoint['xmin'][i])*abs(gunpoint['ymax'][i]-gunpoint['ymin'][i]) for i in range(gunpoint['tar_num'])]
				g_index = np.argmax(size_list)
				pixel_g_x = gunpoint['x'][g_index]
				pixel_g_y = gunpoint['y'][g_index]
				rad_x, rad_y = self.gun_trans(pixel_g_x, pixel_g_y)
				self.Robot[self.selected_index].am.pixel_x = pixel_g_x
				self.Robot[self.selected_index].am.pixel_y = pixel_g_y
				self.Robot[self.selected_index].am.rad_x = rad_x
				self.Robot[self.selected_index].am.rad_y = rad_y
			else:
				self.Robot[self.selected_index].am.pixel_x = None
				self.Robot[self.selected_index].am.pixel_y = None
				self.Robot[self.selected_index].am.rad_x = None
				self.Robot[self.selected_index].am.rad_y = None


	def check_status(self):
		for i in range(2):
			if self.Robot[i].keep > self.Robot[i].Max_keep:
				if self.selected_index == i:
					self.selected_index = None
				self.Robot[i].reinit()
		self.num_active = self.Robot[0].check() + self.Robot[1].check()
		self.Robot_status = [self.Robot[0].check(), self.Robot[1].check()]

class Cam_trans:
	def __init__(self, w, h, cam_num):
		cam_index_folder = '/home/ubuntu/RM2019/src/infocenter/cfg/'
		cam_info = open(cam_index_folder+'c'+str(cam_num)+'.cfg')
		pos_info = open(cam_index_folder+'p'+str(cam_num)+'.cfg')
		cam_lines = []
		for _ in range(4):
			cam_lines += [float(cam_info.readline())]
		cam_info.close()
		pos_lines = []
		for _ in range(4):
			pos_lines += [float(pos_info.readline())]
		pos_info.close()

		self.fx, self.fy, self.cx, self.cy = cam_lines
		# angle_bias1 : from robot physical pos 2 cam physical pos
		# angle_bias2 : from cam physical pos 2 image center
		self.angle_bias1, self.angle_bias2, \
		self.pos_bias_x, self.pos_bias_y = pos_lines
		self.angle_bias1 = math.radians(self.angle_bias1)
		self.angle_bias2 = math.radians(self.angle_bias2)
		self.pos_bias_dis = (self.pos_bias_x**2 + self.pos_bias_y**2)**0.5

		# cam to armour/lightbar height
		self.delta_h = [0.105,0.24]

	def __call__(self, pixel_x, pixel_y, type_):
		# type 0 -> armour
		# type 1 -> lightbar
		type_ = int(type_)
		rad_x = -(pixel_x-self.cx)/self.fx
		rad_y = (pixel_y-self.cy)/self.fy
		est_d = self.delta_h[type_] / math.sin(abs(rad_y))
		body_rad_x, body_est_d = self.estimate_dis(rad_x, est_d)
		if body_rad_x > math.pi:
			body_rad_x -= 2*math.pi
		elif body_rad_x < -math.pi:
			body_rad_x += 2*math.pi
		return rad_x, rad_y, body_rad_x, body_est_d

	def estimate_dis(self, rad, dis):
		rad_cam = self.angle_bias2 + rad

		body_est_d = dis**2 + self.pos_bias_dis**2 - 2*dis*self.pos_bias_dis*abs(math.cos(math.pi-rad_cam))
		body_est_d = body_est_d**0.5

		append_angle = math.asin(dis/body_est_d*math.sin(math.pi-rad_cam))

		return self.angle_bias1+append_angle, body_est_d


class Cam_gun_trans:

	def __init__(self, w, h):
		cam_index_folder = '/home/ubuntu/RM2019/src/infocenter/cfg/'
		cam_info = open(cam_index_folder+'c_gunpoint.cfg')
		lines = []
		for _ in range(4):
			lines += [float(cam_info.readline())]
		cam_info.close()

		self.fx, self.fy, self.cx, self.cy = lines
		#self.dis_bias = pos_info

	def __call__(self, pixel_x, pixel_y):
		rad_x = (pixel_x-self.cx)/self.fx
		rad_y = -(pixel_y-self.cy)/self.fy
		return rad_x, rad_y




