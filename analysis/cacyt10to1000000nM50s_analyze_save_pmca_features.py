import numpy as np
np.random.seed(875431)
import pandas as pd
import os
import astron_common_functions as astronfuns
from matplotlib import pyplot as plt
# plt.ion()
import h5py


diskname = "/home/anup/data/"
dir1 = "cacyt10to1000000nM50s/run/"
datasavepath = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/cacyt10to1000000nM50s"
h5pyfname = "cacyt10to1000000nM50s_pmca_features.hdf5"
# ------------------------------------------
groups = ["ctrl","adpmca"]
# groups = ["ctrl","admglur","adpmca","admglurpmca"]
ngroups = len(groups)
# stims = [10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000,300000,400000,500000,600000,700000,800000,900000,100000] # cacyt/dhpg
cacyts = [10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000] # cacyt/dhpg
ncacyts = len(cacyts)  
trial0 = 1
ntrials = 100
tstim0 = 200
tstim1 = 250
varnames = ['time','n0ca_cyt',"n0pmca_ca_cyt_flux"]
timecol = "time"
cacol="n0ca_cyt"
pmcacol="n0pmca_ca_cyt_flux"
fname_prefix = "astrocyte_cacyt"
# initialize daqtasets
pmcapeak = np.zeros((ngroups,ncacyts,ntrials),dtype=np.float16)
pmcasteady = np.zeros((ngroups,ncacyts,ntrials),dtype=np.float16)

# run through the data files
for igroup in range(0,len(groups)):
    for icacyt in range(0,len(cacyts)):
        fprefix = "".join((fname_prefix,str(cacyts[icacyt]),"nM50s"))
        for itrial,ifile in zip(range(0,ntrials),range(trial0,ntrials+trial0)):
            # {
            findex =  ifile
            fname = "".join((fprefix,"_",groups[igroup],str(findex),".csv"))
            fullname = os.path.join(diskname,dir1,groups[igroup],fname)
            print(findex," ",fullname)
            df = pd.read_csv(fullname,header=0,usecols=varnames)
            print(df.columns)
            ypeak,yss = astronfuns.compute_pmca_features(df[timecol],df[pmcacol], tstim0,tstim1)
            # --------------
            pmcapeak[igroup,icacyt,itrial] = ypeak
            pmcasteady[igroup,icacyt,itrial] = yss
            
            # }
        # }
    # }
# }


# --------------------------------- saving data ---------------------------
# save the matrices using h5py

with h5py.File(os.path.join(datasavepath,h5pyfname),'w') as h5f:
    # {
    dset1 = h5f.create_dataset("cacyts",data=cacyts)
    dset2 = h5f.create_dataset("pmcapeak",data=pmcapeak)
    dset3 = h5f.create_dataset("pmcasteady",data=pmcasteady)
    # }
