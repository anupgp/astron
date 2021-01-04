import numpy as np

np.random.seed(875431)
import pandas as pd
import os
import astron_common_functions as astronfuns
from matplotlib import pyplot as plt
# plt.ion()
import h5py


# load previously analyzed cacyt event properties data:  oldset(matlab)
dir1 = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/ap1to1000dhz30s"
fnamecacytprop = "frap30scarel_eventproperties_cacyt.mat"
dfwhmscacyt = astronfuns.loadh5pydata(os.path.join(dir1,fnamecacytprop),"dfwhmscacyt")
drtscacyt = astronfuns.loadh5pydata(os.path.join(dir1,fnamecacytprop),"drtscacyt")
dtauscacyt = astronfuns.loadh5pydata(os.path.join(dir1,fnamecacytprop),"dtauscacyt")
dnspkcacyt = astronfuns.loadh5pydata(os.path.join(dir1,fnamecacytprop),"dnspkcacyt")
dmaxtcacyt = astronfuns.loadh5pydata(os.path.join(dir1,fnamecacytprop),"dmaxtcacyt")
dmaxycacyt = astronfuns.loadh5pydata(os.path.join(dir1,fnamecacytprop),"dmaxycacyt")
# allfreqs = [np.int(item) for item in loadh5pydata(os.path.join(dir1,fnameves),"stimfreqs")[:,0]*10]
print(dfwhmscacyt.shape)
print(drtscacyt.shape)
print(dtauscacyt.shape)
print(dnspkcacyt.shape)
print(dmaxtcacyt.shape)
print(dmaxycacyt.shape)
# --------------------------------
# load previously analyzed cacyt event properties data: newset (python)
# ---------------------------------
input("Loading data completed! Press a key to continue......")
allfreqs = [1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000]
freqs = [1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000]
_,ifreqs,_ = np.intersect1d(allfreqs,freqs,return_indices=True)
groups = ["ctrl","admglur","adpmca","admglurpmca"]
tstart = 200
tstop=230
trial0 = 0
ntrials = 1000
ngroups = len(groups)
nfreqs = len(freqs)
# ------------------
# calculate cacytrate
cacytrate = np.zeros((ngroups,nfreqs,ntrials),dtype=np.float)
for igroup in range(0,ngroups):
    for ifreq in range(0,nfreqs):
        for itrial in range(trial0,ntrials):
            maxtcacyt = dmaxtcacyt[igroup,ifreq,:,itrial]
            mask = (maxtcacyt>=tstart) & (maxtcacyt<tstop)
            cacytrate[igroup,ifreq,itrial] = len(mask[mask==True])/(tstop-tstart)
            # print(maxtcacyt[mask])
            # print(len(mask[mask==True]))
        # }
    # }
# }
# -------------------------------
# calculate cacytFWHM
cacytfwhm = np.zeros((ngroups,nfreqs,ntrials),dtype=np.float)
for igroup in range(0,ngroups):
    for ifreq in range(0,nfreqs):
        for itrial in range(trial0,ntrials):
            maxtcacyt = dmaxtcacyt[igroup,ifreq,:,itrial]
            mask = (maxtcacyt>=tstart) & (maxtcacyt<tstop)
            fwhm = 0
            if(len(mask[mask==True])>0):
                fwhm = dfwhmscacyt[igroup,ifreq,mask,itrial].mean()
            cacytfwhm[igroup,ifreq,itrial] = fwhm
        # }
    # }
# }





