import ctypes as C
import random as rand

class Axl_agent(C.Structure):

    _fields_ = [('f', C.c_int),
  	        ('q', C.c_int),
	        ('feat', C.POINTER(C.c_int))]

    def __init__(self, f, q, state = []):

        self.f = f
        self.q = q
        self.feat = (C.c_int * self.f)()

	if state == []:
  	    for i in range(f):
	        self.feat[i] = rand.randint(0, q-1)
        else:
  	    for i in range(f):
	        self.feat[i] = state[i]

