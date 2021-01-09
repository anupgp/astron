import numpy as np
np.random.seed(875431)
import pandas as pd
import os
import astron_common_functions as astronfuns
from synchrony_index_pinsky_rinzel import synchrony_index, average_synchrony_per_bins
from matplotlib import pyplot as plt
# plt.ion()
import h5py

# ----------------------------
def loadh5pydata(fname,dataname):
    with h5py.File(fname,'r') as h5fp:
        print(list(h5fp.keys()))
        data = h5fp[dataname][:]
        return(data)
# ----------------------------
datasavepath = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/ap1to1000dhz30s"
h5pyfname = "ap1to1000dhz30s_cacyt_rel_synchrony.hdf5"
dir1 = "/home/anup/astron_data/frap30scarel_processed/"
fnameves = "frap30scacytrel_vesdist.mat"
fnamedmaxtcacyt = "frap30scarel_dmaxtcacyt.mat"
fnamedmaxtrel = "frap30scarel_dmaxtrel.mat"
dmaxtcacyt = astronfuns.loadh5pydata(os.path.join(dir1,fnamedmaxtcacyt),"dmaxtcacyt") # releases between 200 - 230
dmaxtrel = astronfuns.loadh5pydata(os.path.join(dir1,fnamedmaxtrel),"dmaxtrel")
allfreqs = [np.int(item) for item in loadh5pydata(os.path.join(dir1,fnameves),"stimfreqs")[:,0]*10]
print(allfreqs)
input("Press a key to continue......")
# -------------------
# datasavepath = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/ap1to1000dhz30s0noise"
# h5pyfname = "ap1to1000dhz30s0noise_cacyt_rel_synchrony.hdf5"
# dir1 = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/ap1to1000dhz30s0noise/"
# fnameh5py = "ap1to1000dhz30s0noise_cacyt_rel_vdoc_vmob.hdf5"
# dmaxtcacyt = loadh5pydata(os.path.join(dir1,fnameh5py),"dmaxtcacyt") # releases between 200 - 230
# dmaxtrel = loadh5pydata(os.path.join(dir1,fnameh5py),"dmaxtrel")
# allfreqs = loadh5pydata(os.path.join(dir1,fnameh5py),"freqs")
# print(allfreqs)
# input("Press a key to continue.................")
# ----------------------------
groups = ["ctrl","admglur","adpmca","admglurpmca"]
# groups = ["ctrl"]
# freqs = [4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000]
freqs = [4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000]
_,ifreqs,_ = np.intersect1d(allfreqs,freqs,return_indices=True)
tstart = 200
tstop=230
nboot = 1000
nsamples = 1000
ngroups = len(groups)
nfreqs = len(freqs)
ntrials = 1000
binwidth = 100e-3
tbins = np.arange(binwidth,(5100e-3),binwidth)
syncacyt = np.zeros((ngroups,nfreqs,len(tbins),nboot),dtype=np.float)
synrel = np.zeros((ngroups,nfreqs,len(tbins),nboot),dtype=np.float)
# --------------------------
for igroup in range(0,ngroups):
    for ifreqind,ifreq in zip(range(0,nfreqs),ifreqs):
        for iboot in range(0,nboot):
            trials = np.random.choice(np.arange(0,nsamples),nsamples,replace = True)
            # print(trials)
            print("Running bootstrap  : {}, freq: {}, group: {}".format(iboot,allfreqs[ifreq],groups[igroup]))
            timescacytbatch = dmaxtcacyt[igroup,ifreq,:,trials] # ap1to1000dhz30s
            timesrelbatch = dmaxtrel[igroup,ifreq,:,trials]     # ap1to1000dhz30s
            # timescacytbatch = dmaxtcacyt[igroup,ifreq,trials,:] # ap1to1000dhz30s0noise
            # timesrelbatch = dmaxtrel[igroup,ifreq,trials,:]     # ap1to1000dhz30s0noise
            # ----------------
            dtscacyt,rscacyt = synchrony_index(timescacytbatch,tstart,tstop)
            dtsrel,rsrel = synchrony_index(timesrelbatch,tstart,tstop)
            # ---------------
            # average synchrony within time bins
            rscacyt = average_synchrony_per_bins(dtscacyt,rscacyt,tbins)
            rsrel = average_synchrony_per_bins(dtsrel,rsrel,tbins)
            syncacyt[igroup,ifreqind,:,iboot] = rscacyt
            synrel[igroup,ifreqind,:,iboot] = rsrel
            # } iboot
    # } ifreq
# } igroup

# --------  save data ----------------
# with h5py.File(os.path.join(datasavepath,h5pyfname),'w') as h5f:
#     # {
#     dset1 = h5f.create_dataset("freqs",data=freqs)
#     dset2 = h5f.create_dataset("tbins",data=tbins)
#     dset3 = h5f.create_dataset("syncacyt",data=syncacyt)
#     dset5 = h5f.create_dataset("synrel",data=synrel)
    # }
