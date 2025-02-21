from .py_c3utils import Vector3, Vector2
import numpy as np


def dict_obj(d):
    top = type('new', (object,), d)
    seqs = tuple, list, set, frozenset
    for key, value in d.items():
        if isinstance(value, dict):
            setattr(top, key, dict_obj(value))
        elif isinstance(value, seqs):
            setattr(top, key, type(value)(dict_obj(x) if isinstance(x, dict) else x for x in value))
        else:
            setattr(top, key, value)
    return top 


def get_NED_from_NEU(x,mid=np.array([0,0,5000])):
    if mid != np.array([0,0,5000]) : raise NotImplementedError
    h = x[2]
    z = -(h- mid[2])
    x[2] = z
    return x
    

def NEU_to_self(neu:list,roll,pitch,yaw):
    intent_heading = neu
    intent_heading[2] = -intent_heading[2]  #-------------

    intent_heading = Vector3(intent_heading)
    intent_heading.rev_rotate_zyx_self(roll,pitch,yaw)
    intent_heading = intent_heading.get_list()

    intent_heading[2] = -1* intent_heading[2]   # ----------------------
    return intent_heading


def float2(list):
    for i in range(len(list)):
        list[i] = round(list[i],2)
    return list

    
def has(list,x):
    for i in range(len(list)):
        if list[i] == x:
            return True
    return False


def has_index(dict :dict, index):
    for ind,inf in dict.items():
        if ind == index:
            return True
    return False


def abs_max(num,m):
    if num>m :
        num = m
    if num<-m:
        num = -m
    return num


def no_neg (num):
    if num <0 :
        num = 0
    return num


def abs (x):
    if x < 0:
        return -x
    return x


def pwr(x) :
    return x*x  


def norm(x: float, lower_side: float=-1.0, upper_side: float=1.0):
    if (x > upper_side): x = upper_side
    if (x < lower_side): x = lower_side
    return x