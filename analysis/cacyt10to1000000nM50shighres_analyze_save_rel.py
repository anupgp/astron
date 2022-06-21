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
from scipy.signal import find_peaks    

# ----------------------------------------------
diskname = "/home/anup/data/"
dir1 = "cacyt10to1000000nM50shighres/run/"
datasavepath = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/cacyt10to1000000nM50shighres"
h5pyfname = "cacyt10to1000000nM50shighres_release_features.hdf5"
# ---------------------------
# groups = ["ctrl","admglur","adpmca","admglurpmca"]
groups = ["ctrl"]
ngroup = len(groups)
cacyts = [400,500,600,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000,300000,400000,500000] # cacyt/dhpg
ncacyts = len(cacyts)  
trial0 = 1
ntrial = 1
tstim0 = 200
tstim1 = 200.05
tstim2 = 200.5
tstim3 = 210
# tstim1 = 250
fname_prefix = "astrocyte_cacyt"
varnames1 = ["time","n0ca_cyt","n0ca_er","n0ip3_cyt","s1glu_ext","n0syt45_vkdoc_glu","n0syt45_vkrel_glu","n0syt45_vkend_glu","n0syt45_vkacd_glu"]
varnames2 = ["n0syt45_vfmob_glu","n0syt45_vfrel_glu","n0syt45_vfend_glu","n0syt45_vfacd_glu"]
varnames3 = ["n0syt45_krrelrate_glu","n0syt45_ffrelrate_glu","n0syt45_totalrelrate_glu"]
varnames4 = ["n0syt45_krreltime_glu","n0syt45_ffreltime_glu","n0syt45_reltime_glu"]
varnames5 = ["n0syt45_relflag_glu","n0syt45_krrelflag_glu","n0syt45_ffrelflag_glu"]

varnames = varnames1 + varnames2 + varnames3 + varnames4 + varnames5
print(varnames)
# --------------------------
peakkr = np.zeros((ngroup,ntrial,len(cacyts)),dtype=np.float16())
tpeakkr = np.zeros((ngroup,ntrial,len(cacyts)),dtype=np.float16())
peakff1 = np.zeros((ngroup,ntrial,len(cacyts)),dtype=np.float16())
tpeakff1 = np.zeros((ngroup,ntrial,len(cacyts)),dtype=np.float16())
peakff2 = np.zeros((ngroup,ntrial,len(cacyts)),dtype=np.float16())
tpeakff2 = np.zeros((ngroup,ntrial,len(cacyts)),dtype=np.float16())
krrates = []
ffrates1 = []
ffrates2 = []

# -------------------------
for igroup in range(0,ngroup):
    for icacyt in range(0,len(cacyts)):
        fprefix = "".join((fname_prefix,str(cacyts[icacyt]),"nM50s"))
        for itrial,ifile in zip(range(0,ntrial),range(trial0,ntrial+trial0)):
            # {
            findex =  ifile
            fname = "".join((fprefix,"_",groups[igroup],str(findex),".csv"))
            fullname = os.path.join(diskname,dir1,groups[igroup],fname)
            print(findex," ",fullname)
            df = pd.read_csv(fullname,header=0,usecols=varnames)
            t0 = df[["time"]].to_numpy().reshape((len(df[["time"]])))
            istim0 = np.where(t0>tstim0)[0][0]-1
            istim1 = np.where(t0>tstim1)[0][0]-1
            istim2 = np.where(t0>tstim2)[0][0]-1
            istim3 = np.where(t0>tstim3)[0][0]-1
            # -----------------
            # find peak of kr release rate
            tkr = t0[istim0:istim1]
            tkr = tkr - tkr[0]
            krrate = df[["n0syt45_krrelrate_glu"]].to_numpy().reshape((len(df[["n0syt45_krrelrate_glu"]])))[istim0:istim1]
            krrates.append(krrate)
            ipeaks,_ = find_peaks(krrate)
            if (len(ipeaks)>0):
                peakkr[igroup,itrial,icacyt] = krrate[ipeaks[0]]
                tpeakkr[igroup,itrial,icacyt] = tkr[ipeaks[0]]
            # }
            # find peak of ff fast release rate
            tff1 = t0[istim0:istim2]
            tff1 = tff1 - tff1[0]
            ffrate1 = df[["n0syt45_ffrelrate_glu"]].to_numpy().reshape((len(df[["n0syt45_ffrelrate_glu"]])))[istim0:istim2]
            ffrates1.append(ffrate1) 
            ipeaks1,_ = find_peaks(ffrate1)
            if (len(ipeaks1) > 0):
                peakff1[igroup,itrial,icacyt] = ffrate1[ipeaks1[0]]
                tpeakff1[igroup,itrial,icacyt] = tff1[ipeaks1[0]]
            # }
            # ---------------
            # find peak of ff slow release rate
            tff2 = t0[istim2:istim3]
            tff2 = tff2 - tff2[0]
            ffrate2 = df[["n0syt45_ffrelrate_glu"]].to_numpy().reshape((len(df[["n0syt45_ffrelrate_glu"]])))[istim2:istim3]
            ffrates2.append(ffrate2)
            ipeaks2,_ = find_peaks(ffrate2)
            if (len(ipeaks2) > 0):
                peakff2[igroup,itrial,icacyt] = ffrate2[ipeaks2[0]]
                tpeakff2[igroup,itrial,icacyt] = tff2[ipeaks2[0]]
            # }
        # }
    # }
# }

krrates = np.array(krrates).reshape(ngroup,ntrial,len(cacyts),len(tkr))
ffrates1 = np.array(ffrates1).reshape(ngroup,ntrial,len(cacyts),len(tff1))
ffrates2 = np.array(ffrates2).reshape(ngroup,ntrial,len(cacyts),len(tff2))
# print(peakkr)
# print(peakff1)
# fh = plt.figure()
# ah = fh.add_subplot(111)
# for icacyt in range(0,len(cacyts)):
#     ah.plot(tkr,krrates[icacyt,:])
#     ah.plot(tpeakkr[0,0,icacyt],peakkr[0,0,icacyt],'o',markersize=5)
#     # ah.plot(tff1,ffrates1[icacyt,:])
#     # ah.plot(tpeakff1[0,0,icacyt],peakff1[0,0,icacyt],'o',markersize=5)
#     # ah.plot(tff2,ffrates2[icacyt,:])
#     # ah.plot(tpeakff2[0,0,icacyt],peakff2[0,0,icacyt],'o',markersize=5)
# plt.show()

# --------------------------------- saving data ---------------------------
# save the matrices using h5py
with h5py.File(os.path.join(datasavepath,h5pyfname),'w') as h5f:
    # {
    dset1 = h5f.create_dataset("tkr",data=tkr)
    dset2 = h5f.create_dataset("krrates",data=krrates)
    dset3 = h5f.create_dataset("tpeakkr",data=tpeakkr)
    dset4 = h5f.create_dataset("peakkr",data=peakkr)
    # ---------
    dset5 = h5f.create_dataset("tff1",data=tff1)
    dset6 = h5f.create_dataset("ffrates1",data=ffrates1)
    dset7 = h5f.create_dataset("tpeakff1",data=tpeakff1)
    dset8 = h5f.create_dataset("peakff1",data=peakff1)
    # -------
    dset9 = h5f.create_dataset("cacyts",data=cacyts)
# }
