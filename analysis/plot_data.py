import csv
import os
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt

disk = "/home/anup/data/dhpg100000nM2s"
folder = "output"
groups = ["ctrl"]
fname_prefix = "astrocyte_dhpg100000nM2s"
trial0 = 1
ntrials = 1
varnames = ["time","n0ca_cyt","n0pmca_ca_cyt_flux","n0ip3_cyt","s1glu_ext","s1dhpg_ext"]

# data = np.genfromtxt(filename,dtype=float,skip_header=1,delimiter=',',usecols=(0,1,2,3,4))
fh = plt.figure()
ah = plt.axes()
for igroup in range(0,len(groups)):
    # fprefix = "".join(("astrocyte_ap",str(freqs[ifreq]),"dHz30s"))
    for itrial,ifile in zip(range(0,ntrials),range(trial0,ntrials+trial0)):
        findex =  ifile
        fname = "".join((fname_prefix,groups[igroup],str(findex),".csv"))
        fullname = os.path.join(disk,folder,groups[igroup],fname)
        print(findex," ",fullname)
        df = pd.read_csv(fullname,header=0,usecols=varnames)
    # }
# }
    

# plotting
ah.plot(df["time"],df["n0ca_cyt"])
ah.plot(df["time"],df["s1dhpg_ext"])
# ah.plot(df["time"],df["n0pmca_ca_cyt_flux"])


plt.show()
# input('key a key')
# plt.close('all')



