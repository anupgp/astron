# codes to analyze and plot the temporal correlation between calcium and release events from an astrocytic process

import numpy as np
np.random.seed(875431)
import pandas as pd
import os
import astron_common_functions as astronfuns
from matplotlib import pyplot as plt
# plt.ion()
import h5py

# ---------------------------------------------------------------------------------------------------
def loadh5pydata(fname,dataname):
    with h5py.File(fname,'r') as h5fp:
        print(list(h5fp.keys()))
        data = h5fp[dataname][:]
        return(data)
# --------------------------------------------------------------------------------------------------
dataloadpath = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/ap1to1000dhz30s"
datasavepath = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/ap1to1000dhz30s"
h5pyfname = "ap1to1000dhz30s_cacyt_rel_vdoc_vmob.hdf5"
# dataloadpath = "/run/media/anup/3becd611-cb79-4b80-b941-2edcc0d64cb4"
# dataloadpath = "data/astron/raw/astrocyte/frap30scarel_processed/"
# dir1 = "/home/anup/astron_data/frap30scarel_processed/"
# dname_freqs = "freqs"
# dname_dmaxtcacyt = "dmaxtcacyt"
# dname_dmaxtrel = "dmaxtrel"
# fnameves = "frap30scacytrel_vesdist.mat"
# fnamedmaxtcacyt = "frap30scarel_dmaxtcacyt.mat"
# fnamedmaxtrel = "frap30scarel_dmaxtrel.mat"
# groups = ["ctrl"]
# loaddata
freqsdmaxt = np.array([np.int(item) for item in loadh5pydata(os.path.join(dataloadpath,h5pyfname),"freqs")])
dmaxtcacyt = loadh5pydata(os.path.join(dataloadpath,h5pyfname),"dmaxtcacyt") # releases between 200 - 230
dmaxtrel = loadh5pydata(os.path.join(dataloadpath,h5pyfname),"dmaxtrel")
dvdocrel = loadh5pydata(os.path.join(dataloadpath,h5pyfname),"dvdocrel")
dvmobrel = loadh5pydata(os.path.join(dataloadpath,h5pyfname),"dvmobrel")
# --------------------------------------------------------------------------------------------------
groups = ["ctrl","admglur","adpmca","admglurpmca"]
# groups = ["adpmca","admglurpmca"]
ngroups = len(groups)
# freqs = [4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000]
freqs = [4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000]
_,ifreqsdmaxt,_ = np.intersect1d(freqsdmaxt,freqs,return_indices=True)
print(freqsdmaxt)
print(freqs)
print(ifreqsdmaxt)
nfreqs = len(freqs)
tstart = 185
tstop = 235
trange_corr = [199,211]
filterwidth = 1
trial0 = 1
thres = 300e-9          # 300 nM"
delta = 1*thres          # 300 nM"
corrdt = 0.1
nboot = 1000
nsamples = 1000
nbatch = nboot                     # number of batches
binst =  np.arange(tstart,tstop,corrdt) # edges: histogram counts between edges no histogram size is 1-size of bins
ntrials = 1000
# ---------------------------------------------------------
psthca = np.zeros((ngroups,nfreqs,len(binst)-1,nboot),dtype=np.float16)           # per batch, per freqs, per group
psthrel = np.zeros((ngroups,nfreqs,len(binst)-1,nboot),dtype=np.float16)           # per batch, per freqs, per group
npsthca = np.zeros((ngroups,nfreqs,len(binst)-1,nboot),dtype=np.float16)           # per batch, per freqs, per group
npsthrel = np.zeros((ngroups,nfreqs,len(binst)-1,nboot),dtype=np.float16)           # per batch, per freqs, per group
rjpsth = np.zeros((ngroups,nfreqs,len(binst)-1,len(binst)-1,nboot),dtype=np.float16) # jpsth matrix raw
pjpsth = np.zeros((ngroups,nfreqs,len(binst)-1,len(binst)-1,nboot),dtype=np.float16)
njpsth = np.zeros((ngroups,nfreqs,len(binst)-1,len(binst)-1,nboot),dtype=np.float16)
psthprod = np.zeros((ngroups,nfreqs,len(binst)-1,len(binst)-1,nboot),dtype=np.float16) # product of psths
peakcrosscorr = np.zeros((ngroups,nfreqs,nboot),dtype=np.float16)
vdoc = np.zeros((ngroups,nfreqs,nboot),dtype=np.float16)           # per batch, per freqs, per group
vmob = np.zeros((ngroups,nfreqs,nboot),dtype=np.float16)           # per batch, per freqs, per group
print("ngroup: {}, nfreqs: {}, nboot: {}".format(ngroups,nfreqs,nboot))
input("Press any key to start the analysis")
# -------------------------------------------------------
for igroup in range(0,ngroups):
    for ifreq,ifreqdmaxt in zip(range(0,nfreqs),ifreqsdmaxt):
        for iboot in range(0,nboot):
            docves = np.zeros((nsamples,20),dtype=np.float)
            mobves = np.zeros((nsamples,20),dtype=np.float)
            trials = np.random.choice(np.arange(0,nsamples),nsamples,replace = True)
            print("Running bootstrap  : {}, freq: {}, group: {}, ntrials: {}".format(iboot,freqsdmaxt[ifreq],groups[igroup],ntrials))
            # for itrial,itrialdmaxt in zip(range(0,ntrials),range(0,ntrials)):
            for itrial,itrialdmaxt in zip(range(0,nsamples),trials):
                histca,_ = np.histogram(dmaxtcacyt[igroup,ifreqdmaxt,itrialdmaxt,:],binst)
                histrel,_ = np.histogram(dmaxtrel[igroup,ifreqdmaxt,itrialdmaxt,:],binst)
                psthca[igroup,ifreq,:,iboot] = psthca[igroup,ifreq,:,iboot] + histca
                psthrel[igroup,ifreq,:,iboot] = psthrel[igroup,ifreq,:,iboot] + histrel
                # compute jpsth matrix
                ihistca = np.where(histca>0)[0]
                ihistrel = np.where(histrel>0)[0]
                releases = dmaxtrel[igroup,ifreqdmaxt,itrialdmaxt,:]
                trialdocves = dvdocrel[igroup,ifreqdmaxt,itrialdmaxt,(releases>=199) & (releases<=211)]
                trialmobves = dvmobrel[igroup,ifreqdmaxt,itrialdmaxt,(releases>=199) & (releases<=211)]
                if(len(trialdocves) > 0):
                    docves[itrial,0:len(trialdocves)] = trialdocves
                if(len(trialmobves) > 0):
                    mobves[itrial,0:len(trialmobves)] = trialmobves
                if ((len(ihistca)>0) & (len(ihistrel)>0)):
                    # {
                    for j in range(0,min(len(ihistca),len(ihistrel))):
                        # {
                        rjpsth[igroup,ifreq,ihistca[j],ihistrel[j],iboot] = rjpsth[igroup,ifreq,ihistca[j],ihistrel[j],iboot] + 1 
                        # }
                    # }
                # }
            vdoc[igroup,ifreq,iboot] = docves[docves>0].mean()
            vmob[igroup,ifreq,iboot] = mobves[mobves>0].mean()
            rjpsthsum = rjpsth[igroup,ifreq,:,:,iboot].sum(axis=-1).sum(axis=-1)
            # jpsthp[:,:,ibatch,ifreq,igroup] =  jpsthr[:,:,ibatch,ifreq,igroup]/jpsthrsum
            pjpsth[igroup,ifreq,:,:,iboot] =  rjpsth[igroup,ifreq,:,:,iboot]/rjpsthsum
            # psthnca[:,ibatch,ifreq,igroup] = psthca[:,ibatch,ifreq,igroup]/psthca[:,ibatch,ifreq,igroup].sum(axis=0)
            # psthnrel[:,ibatch,ifreq,igroup] = psthrel[:,ibatch,ifreq,igroup]/psthrel[:,ibatch,ifreq,igroup].sum(axis=0)
            sum_psthca = psthca[igroup,ifreq,:,iboot].sum()
            sum_psthrel = psthrel[igroup,ifreq,:,iboot].sum()
            std_psthca = psthca[igroup,ifreq,:,iboot].std()
            std_psthrel = psthrel[igroup,ifreq,:,iboot].std()
            npsthca[igroup,ifreq,:,iboot] = psthca[igroup,ifreq,:,iboot]/sum_psthca
            npsthrel[igroup,ifreq,:,iboot] = psthrel[igroup,ifreq,:,iboot]/sum_psthrel
            psthprod[igroup,ifreq,:,:,iboot] = np.matmul(psthca[igroup,ifreq,:,iboot].T/sum_psthca,psthrel[igroup,ifreq,:,iboot]/sum_psthrel)
            # psthprod[igroup,ifreq,iboot,:,:] = np.matmul(npsthca[igroup,ifreq,iboot,:].T,npsthrel[igroup,ifreq,iboot,:])
            # jpsthn = (jpsthp - psthprod)/(std_psthca * std_psthrel)
            njpsth[igroup,ifreq,:,:,iboot] = pjpsth[igroup,ifreq,:,:,iboot]/(std_psthca * std_psthrel)
            # njpsth[igroup,ifreq,iboot,:,:] = (pjpsth[igroup,ifreq,iboot,:,:] - psthprod[igroup,ifreq,iboot,:,:])/std_psthca*std_psthrel
            # jpsthn[:,:,ibatch,ifreq,igroup] = (jpsthp[:,:,ibatch,ifreq,igroup] - psthprod[:,:,ibatch,ifreq,igroup])/(std_psthca * std_psthrel)
            # [coinbins,coinvec,corrbins,corrvec] = astronfuns.jpsth2crosscorr(jpsthn[:,:,ibatch,ifreq,igroup],binst,trange_corr) 
            [coinbins,coinvec,corrbins,corrvec] = astronfuns.jpsth2crosscorr(njpsth[igroup,ifreq,:,:,iboot],binst,trange_corr)
            peakcrosscorr[igroup,ifreq,iboot] = abs(np.max(corrvec))
            # }
        # }
    # }
# }

# input("Analysis finished. press any key to save data into hd5py")
# -----------------------------------------------------------------------

    
# --------------------------------- saving data ---------------------------
# save the matrices using h5py
h5pyfname = "ap1to1000dhz30s_cacytrel_cross_corr.hdf5"
with h5py.File(os.path.join(datasavepath,h5pyfname),'w') as h5f:
    # {
    dset1 = h5f.create_dataset("rjpsth",data=rjpsth)
    dset2 = h5f.create_dataset("psthca",data=psthca)
    dset3 = h5f.create_dataset("psthrel",data=psthrel)
    dset4 = h5f.create_dataset("peakcrosscorr",data=peakcrosscorr)
    dset5 = h5f.create_dataset("freqs",data=freqs)
    dset6 = h5f.create_dataset("vdoc",data=vdoc)
    dset7 = h5f.create_dataset("vmob",data=vmob)
    dset8 = h5f.create_dataset("binst",data=binst)
    dset9 = h5f.create_dataset("pjpsth",data=pjpsth)
    dset10 = h5f.create_dataset("njpsth",data=njpsth)
# }


