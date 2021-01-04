import csv
import numpy as np
import os
from matplotlib import pyplot as plt

# fpath1 = "/home/anup/data/glu1to100000nM2s/dynparam/"
fpath1 = "/home/anup/goofy/codes/astron/dynparams/"
fname = "dynparams_dhpg1000nM50s.isfdp"
dypar = np.genfromtxt(os.path.join(fpath1,fname),dtype=float,skip_header=1,delimiter=',',usecols=(0,1))
fh = plt.figure()
ah = plt.axes()
ah.plot(dypar[:,0],dypar[:,1])
plt.show()
# input('key a key')
# plt.close('all')



