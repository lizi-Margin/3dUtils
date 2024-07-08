# import i3utils
import py_c3utils as i3utils
import math
half_pi = math.pi/2
v3 = i3utils.Vector3([1,0,0])
v3.rotate_zyx_self(half_pi,half_pi*1.2,half_pi*3.3)
print(v3)
print(v3.get_angle(i3utils.Vector3([1,0,0]),pid_set_zero = 1 ,pid_sign_dim = 2))
