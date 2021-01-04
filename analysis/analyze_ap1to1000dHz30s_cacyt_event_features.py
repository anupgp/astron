import numpy as np
np.random.seed(875431)
import pandas as pd
import os
import astron_common_functions as astronfuns
from matplotlib import pyplot as plt
import matplotlib.font_manager as font_manager
# plt.ion()
font_path = '/home/anup/.matplotlib/fonts/arial.ttf'
fontprop = font_manager.FontProperties(fname=font_path)
import h5py


# ------------------------------------------
diskname = "/home/anup/data/"
dir1 = "ap1to1000dhz30scarel/run/"
datasavepath = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/ap1to1000dhz30s"
h5pyfname = "ap1to1000dhz30s_cacyt_event_features.hdf5"

groups = ["ctrl","admglur","adpmca","admglurpmca"]
ngroups = len(groups)
allfreqs = [1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000]
# freqs = [4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000]
freqs = [1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000]
# freqs = [1000]
_,ifreqs,_ = np.intersect1d(allfreqs,freqs,return_indices=True)
nfreqs = len(freqs)
# print(nfreqs,freqs,ifreqs)
# input()
trial0 = 1
ntrials = 1000
# varnames=['time','n0ca_cyt','n0syt45_reltime_glu','n0syt45_vkdoc_glu','n0syt45_vfmob_glu']
timecol = "time"
cacol="n0ca_cyt"
varnames = [timecol,cacol]
thres = 300e-9          # 300 nM"
delta = 1*thres          # 300 nM"
tstimstart = 200
tstimstop = 230
cacytpeak = np.zeros((ngroups,nfreqs,ntrials),dtype=np.float16())
cacytrate = np.zeros((ngroups,nfreqs,ntrials),dtype=np.float16())
cacytrt = np.zeros((ngroups,nfreqs,ntrials),dtype=np.float16())
cacytfwhm = np.zeros((ngroups,nfreqs,ntrials),dtype=np.float16())
cacyttau = np.zeros((ngroups,nfreqs,ntrials),dtype=np.float16())
# --------------------------------------------
for igroup in range(0,len(groups)):
    for ifreq in range(0,len(freqs)):
        fprefix = "".join(("astrocyte_ap30s",str(freqs[ifreq]),"dHz"))
        # fprefix = "".join(("astrocyte_ap",str(freqs[ifreq]),"dHz30s"))
        for itrial in range(1,ntrials+1):
            findex =  itrial
            fname = "".join((fprefix,"_",groups[igroup],str(findex),".csv"))
            fullname = os.path.join(diskname,dir1,groups[igroup],fname)
            print(findex," ",fullname)
            df = pd.read_csv(fullname,header=0,usecols=varnames)
            peaks,rts,fwhms,taus,ipeaks,irts,ifwhms,itaus = astronfuns.compute_event_features(df,thres,delta)
            cacytpeaktimes = df[timecol].to_numpy()[ipeaks]
            rate = len(cacytpeaktimes[(cacytpeaktimes>=tstimstart) & (cacytpeaktimes<=tstimstop)])/(tstimstop-tstimstart)
            cacytrate[igroup,ifreq,itrial-1] = rate
            cacytpeak[igroup,ifreq,itrial-1] = np.nanmean(np.array(peaks))
            cacytrt[igroup,ifreq,itrial-1] = np.nanmean(np.array(rts))
            cacytfwhm[igroup,ifreq,itrial-1] = np.nanmean(np.array(fwhms))
            cacyttau[igroup,ifreq,itrial-1] = np.nanmean(np.array(taus))
        # }
    # }
# }

# --------  save data ----------------
with h5py.File(os.path.join(datasavepath,h5pyfname),'w') as h5f:
    # {
    dset1 = h5f.create_dataset("freqs",data=freqs)
    dset2 = h5f.create_dataset("cacytrate",data=cacytrate)
    dset3 = h5f.create_dataset("cacytrt",data=cacytrt)
    dset4 = h5f.create_dataset("cacytfwhm",data=cacytfwhm)
    dset5 = h5f.create_dataset("cacyttau",data=cacyttau)
    dset6 = h5f.create_dataset("cacytpeak",data=cacytpeak)
    # }
