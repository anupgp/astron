import numpy as np
np.random.seed(875431)
import pandas as pd
import os
import astron_common_functions as astronfuns
from matplotlib import pyplot as plt
# plt.ion()
import h5py


# diskname = "/run/media/anup/3becd611-cb79-4b80-b941-2edcc0d64cb4"
# dir1 = "data/astron/raw/astrocyte/ap1to1000dhz30scarel/run/"
# diskname = "/home/anup/data/"
# dir1 = "ap1to1000dhz30s/run/"
diskname = "/home/anup/data/"
dir1 = "cacyt10to1000000nM50s/run/"
# datasavepath = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/ap1to1000dhz30s"
# datasavepath = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/ap1to1000dhz30s"
# h5pyfname = "ap1to1000dhz30s_cacyt_rel_kr_ff_vdoc_vmob.hdf5"
datasavepath = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/cacyt10to1000000nM50s"
h5pyfname = "cacyt10to1000000nM50s_pmca_features.hdf5"
# ------------------------------------------
groups = ["ctrl","adpmca"]
# groups = ["ctrl","admglur","adpmca","admglurpmca"]
ngroups = len(groups)
# freqs = [1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000]
# nfreqs = len(freqs)
# stims = [10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000,300000,400000,500000,600000,700000,800000,900000,100000] # cacyt/dhpg
cacyts = [10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000] # cacyt/dhpg
ncacyts = len(cacyts)  
trial0 = 1
ntrials = 100
tstim0 = 200
tstim1 = 250
# varnames=['time','n0ca_cyt','n0syt45_reltime_glu','n0syt45_krreltime_glu','n0syt45_ffreltime_glu','n0syt45_vkdoc_glu','n0syt45_vfmob_glu']
varnames = ['time','n0ca_cyt',"n0pmca_ca_cyt_flux"]
timecol = "time"
cacol="n0ca_cyt"
pmcacol="n0pmca_ca_cyt_flux"
# relcol = "n0syt45_reltime_glu"
# krrelcol = "n0syt45_krreltime_glu"
# ffrelcol = "n0syt45_ffreltime_glu"
# vdoccol = 'n0syt45_vkdoc_glu'
# vmobcol = 'n0syt45_vfmob_glu' 
# thres = 300e-9          # 300 nM"
# delta = 1*thres          # 300 nM"
fname_prefix = "astrocyte_cacyt"
# initialize daqtasets
# dmaxtcacyt = np.zeros((ngroups,nfreqs,ntrials,20),dtype=np.float16)
# dmaxtrel = np.zeros((ngroups,nfreqs,ntrials,20),dtype=np.float16)
# dmaxtkrrel = np.zeros((ngroups,nfreqs,ntrials,20),dtype=np.float16)
# dmaxtffrel = np.zeros((ngroups,nfreqs,ntrials,20),dtype=np.float16)
# dvdocrel = np.zeros((ngroups,nfreqs,ntrials,20),dtype=np.float16)
# dvmobrel = np.zeros((ngroups,nfreqs,ntrials,20),dtype=np.float16)
pmcapeak = np.zeros((ngroups,ncacyts,ntrials),dtype=np.float16)
pmcasteady = np.zeros((ngroups,ncacyts,ntrials),dtype=np.float16)

# run through the data files
for igroup in range(0,len(groups)):
    for icacyt in range(0,len(cacyts)):
        # fprefix = "".join(("astrocyte_ap30s",str(freqs[ifreq]),"dHz"))
        # fprefix = "".join(("astrocyte_ap",str(freqs[ifreq]),"dHz30s"))
        fprefix = "".join((fname_prefix,str(cacyts[icacyt]),"nM50s"))
        for itrial,ifile in zip(range(0,ntrials),range(trial0,ntrials+trial0)):
            # {
            findex =  ifile
            fname = "".join((fprefix,"_",groups[igroup],str(findex),".csv"))
            fullname = os.path.join(diskname,dir1,groups[igroup],fname)
            print(findex," ",fullname)
            df = pd.read_csv(fullname,header=0,usecols=varnames)
            print(df.columns)
            # get event times of  calcium spikes and release
            # timesca = astronfuns.detect_peaks_above_threshold(df[timecol].to_numpy(),df[cacol].to_numpy(),thres,delta,eventval=0)
            # timesrel = df[relcol][df[relcol]>0].to_numpy()
            # timeskrrel = df[krrelcol][df[krrelcol]>0].to_numpy()
            # timesffrel = df[ffrelcol][df[ffrelcol]>0].to_numpy()
            # vdoc = df[vdoccol][df[relcol]>0].to_numpy()
            # vmob = df[vmobcol][df[relcol]>0].to_numpy()
            ypeak,yss = astronfuns.compute_pmca_features(df[timecol],df[pmcacol], tstim0,tstim1)
            # --------------
            # dmaxtcacyt[igroup,ifreq,itrial,0:len(timesca)] = timesca
            # dmaxtrel[igroup,ifreq,itrial,0:len(timesrel)] = timesrel
            # dmaxtkrrel[igroup,ifreq,itrial,0:len(timeskrrel)] = timeskrrel
            # dmaxtffrel[igroup,ifreq,itrial,0:len(timesffrel)] = timesffrel
            # dvdocrel[igroup,ifreq,itrial,0:len(vdoc)] = vdoc
            # dvmobrel[igroup,ifreq,itrial,0:len(vdoc)] = vmob
            pmcapeak[igroup,icacyt,itrial] = ypeak
            pmcasteady[igroup,icacyt,itrial] = yss
            
            # }
        # }
    # }
# }


# --------------------------------- saving data ---------------------------
# save the matrices using h5py

# with h5py.File(os.path.join(datasavepath,h5pyfname),'w') as h5f:
#     # {
#     dset1 = h5f.create_dataset("freqs",data=freqs)
#     dset2 = h5f.create_dataset("dmaxtcacyt",data=dmaxtcacyt)
#     dset3 = h5f.create_dataset("dmaxtrel",data=dmaxtrel)
#     dset4 = h5f.create_dataset("dmaxtkrrel",data=dmaxtkrrel)
#     dset5 = h5f.create_dataset("dmaxtffrel",data=dmaxtffrel)
#     dset6 = h5f.create_dataset("dvdocrel",data=dvdocrel)
#     dset7 = h5f.create_dataset("dvmobrel",data=dvmobrel)
#     # }                

with h5py.File(os.path.join(datasavepath,h5pyfname),'w') as h5f:
    # {
    dset1 = h5f.create_dataset("cacyts",data=cacyts)
    dset2 = h5f.create_dataset("pmcapeak",data=pmcapeak)
    dset3 = h5f.create_dataset("pmcasteady",data=pmcasteady)
    # }
