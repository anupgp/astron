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
    

# ----------------------------------------------
# diskname = "/run/media/anup/3becd611-cb79-4b80-b941-2edcc0d64cb4"
# dir1 = "data/astron/raw/astrocyte"
# dir2="dhpg100000nM2s/run"
# datasavepath = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/dhpg100000nM2s_cacyt_rel_features"
# h5pyfname = "dhpg100000nM2s_cacyt_rel_event_features.hdf5"
# --------------------------------------------
diskname = "/home/anup/data"
dir1 = "dhpg100000nM2s"
dir2="output"
datasavepath = "/home/anup/data/dhpg100000nM2s/analysis/"
h5pyfname = "dhpg100000nM2s_cacyt_rel_event_features.hdf5"
# ---------------------------------------

# groups = ["ctrl","admglur","adpmca","admglurpmca"]
groups = ["ctrl"]
fprefix = "astrocyte_dhpg100000nM2s_"
varnames1 = ["time","n0ca_cyt","n0ca_er","n0ip3_cyt","s1glu_ext","n0syt45_vkdoc_glu","n0syt45_vkrel_glu","n0syt45_vkend_glu","n0syt45_vkacd_glu"]
varnames2 = ["n0syt45_vfmob_glu","n0syt45_vfrel_glu","n0syt45_vfend_glu","n0syt45_vfacd_glu"]
varnames3 = ["n0syt45_krrelrate_glu","n0syt45_ffrelrate_glu","n0syt45_totalrelrate_glu"]
varnames4 = ["n0syt45_krreltime_glu","n0syt45_ffreltime_glu","n0syt45_reltime_glu"]
varnames5 = ["n0syt45_relflag_glu","n0syt45_krrelflag_glu","n0syt45_ffrelflag_glu"]

varnames = varnames1 + varnames2 + varnames3 + varnames4 + varnames5
print(varnames)
fpath = os.path.join(diskname,dir1,dir2)
ntrial = 400                    # 400
trial0 = 1                      # 1
nbatch = 6                      # 6
ngroup = len(groups)
t0 = 190                        # analyze start time
t1 = 205                        # analyze stop time
tbin = 50e-3                    # 50 micro sec"
thres = 300e-9                  # 300 nM"
delta = 1*thres                 # 300 nM"
ts0 = 200                       # stim start
ts1 = 202                       # stim stop

# calcium event features
# cacytpeak = np.zeros((ngroup,nbatch,ntrial),dtype=np.float16())
# cacytrt = np.zeros((ngroup,nbatch,ntrial),dtype=np.float16())

# histogram of calcium event features: peak and risetimes, taus, fwhm
binscacytpk = np.arange(0,15e-6,0.5e-6)
binscacytrt = np.arange(0,500e-3,10e-3)
binscacytdk = np.arange(0,500e-3,30e-3)
binscacytfw = np.arange(0,500e-3,30e-3)
hcacytpk = np.zeros((ngroup,nbatch,len(binscacytpk)-1),dtype=np.float16) # per batch, per freqs, per group
hcacytrt = np.zeros((ngroup,nbatch,len(binscacytrt)-1),dtype=np.float16) # per batch, per freqs, per group
hcacytdk = np.zeros((ngroup,nbatch,len(binscacytdk)-1),dtype=np.float16) # per batch, per freqs, per group
hcacytfw = np.zeros((ngroup,nbatch,len(binscacytfw)-1),dtype=np.float16) # per batch, per freqs, per group


dmaxtcacyt = np.zeros((ngroup,nbatch,ntrial,12),dtype=np.float16)
dmaxtkrrel = np.zeros((ngroup,nbatch,ntrial,12),dtype=np.float16)
dmaxtffrel = np.zeros((ngroup,nbatch,ntrial,12),dtype=np.float16)

# temporal histograms of calcium and release events
deltat = 0.05                   # 50ms
binst =  np.arange(t0,t1,deltat) # edges: histogram counts between edges no histogram size is 1-size of bins
psthca = np.zeros((ngroup,nbatch,len(binst)-1),dtype=np.float16) # per batch, per freqs, per group
psthrel = np.zeros((ngroup,nbatch,len(binst)-1),dtype=np.float16) # per batch, per freqs, per group
psthkrrel = np.zeros((ngroup,nbatch,len(binst)-1),dtype=np.float16) # per batch, per freqs, per group
psthffrel = np.zeros((ngroup,nbatch,len(binst)-1),dtype=np.float16) # per batch, per freqs, per group

# timecourse of release variables
tc_delta = 50e-3
tc_starttime = 190
tc_stoptime = 232
tc_bins = np.arange(tc_starttime,tc_stoptime,tc_delta)
ntc_bins = len(tc_bins)
tc_nkrrel = np.zeros((ngroup,nbatch,ntc_bins),dtype=np.float16())
tc_nkrdoc = np.zeros((ngroup,nbatch,ntc_bins),dtype=np.float16())
tc_nkrend = np.zeros((ngroup,nbatch,ntc_bins),dtype=np.float16())
tc_nkracd = np.zeros((ngroup,nbatch,ntc_bins),dtype=np.float16())
tc_nffrel = np.zeros((ngroup,nbatch,ntc_bins),dtype=np.float16())
tc_nffmob = np.zeros((ngroup,nbatch,ntc_bins),dtype=np.float16())
tc_nffend = np.zeros((ngroup,nbatch,ntc_bins),dtype=np.float16())
tc_nffacd = np.zeros((ngroup,nbatch,ntc_bins),dtype=np.float16())
# --------------------------------------------
for igroup in range(0,ngroup):
    for ibatch in range(0,nbatch):
        nkrdoc = np.zeros((ntc_bins),dtype=np.float16())
        nkrrel = np.zeros((ntc_bins),dtype=np.float16())
        nkrend = np.zeros((ntc_bins),dtype=np.float16())
        nkracd = np.zeros((ntc_bins),dtype=np.float16())
        # ------------
        nffmob = np.zeros((ntc_bins),dtype=np.float16())
        nffrel = np.zeros((ntc_bins),dtype=np.float16())
        nffend = np.zeros((ntc_bins),dtype=np.float16())
        nffacd = np.zeros((ntc_bins),dtype=np.float16())
        fprefix = "astrocyte_dhpg100000nM2s"
        # fprefix = "".join(("astrocyte_ap",str(freqs[ifreq]),"dHz30s"))
        for ifile,itrial in zip(range(1+(ibatch*ntrial),ntrial+1+(ibatch*ntrial)),range(0,ntrial)):
            fname = "".join((fprefix,"",groups[igroup],str(ifile),".csv"))
            fullname = os.path.join(diskname,dir1,dir2,groups[igroup],fname)
            print(ifile," ",fullname)
            df = pd.read_csv(fullname,header=0,usecols=varnames)
            print(df.columns)
            # --------------------
            # histogram cacyt features
            peaks,rts,fwhms,taus,ipeaks,irts,ifwhms,itaus = astronfuns.compute_event_features(df[["time","n0ca_cyt"]],thres,delta)
            histpk,_ = np.histogram(peaks,binscacytpk)
            histrt,_ = np.histogram(rts,binscacytrt)
            histdk,_ = np.histogram(taus,binscacytdk)
            histfw,_ = np.histogram(fwhms,binscacytfw)
            hcacytpk[igroup,ibatch,:]  = hcacytpk[igroup,ibatch,:] + histpk
            hcacytrt[igroup,ibatch,:]  = hcacytrt[igroup,ibatch,:] + histrt
            hcacytdk[igroup,ibatch,:]  = hcacytdk[igroup,ibatch,:] + histdk
            hcacytfw[igroup,ibatch,:]  = hcacytfw[igroup,ibatch,:] + histfw
            # --------------------
            # computer psths
            timesca =  df["time"].to_numpy()[ipeaks]
            thistca,_ = np.histogram(timesca,binst)
            timesrel = df["n0syt45_reltime_glu"].to_numpy()[df["n0syt45_relflag_glu"]>0]
            thistrel,_ = np.histogram(timesrel,binst)
            timeskrrel = df["n0syt45_krreltime_glu"].to_numpy()[df["n0syt45_krrelflag_glu"]>0]
            thistkrrel,_ = np.histogram(timeskrrel,binst)
            timesffrel = df["n0syt45_ffreltime_glu"].to_numpy()[df["n0syt45_ffrelflag_glu"]>0]
            thistffrel,_ = np.histogram(timesffrel,binst)
            psthca[igroup,ibatch,:] = psthca[igroup,ibatch,:] + thistca
            psthrel[igroup,ibatch,:] = psthrel[igroup,ibatch,:] + thistrel
            psthkrrel[igroup,ibatch,:] = psthkrrel[igroup,ibatch,:] + thistkrrel
            psthffrel[igroup,ibatch,:] = psthffrel[igroup,ibatch,:] + thistffrel
            # -------------------
            dmaxtcacyt[igroup,ibatch,itrial,0:len(timesca)] = timesca
            dmaxtkrrel[igroup,ibatch,itrial,0:len(timeskrrel)] = timeskrrel
            dmaxtffrel[igroup,ibatch,itrial,0:len(timesffrel)] = timesffrel
            # -------------------
            # compute time courses
            t = df["time"].to_numpy()
            itc_bins = np.array([np.where(t>item)[0][0]-1 for item in tc_bins])
            nkrdoc = nkrdoc + df["n0syt45_vkdoc_glu"].to_numpy()[itc_bins]
            nkrrel = nkrrel + df["n0syt45_vkrel_glu"].to_numpy()[itc_bins]
            nkrend = nkrend + df["n0syt45_vkend_glu"].to_numpy()[itc_bins]
            nkracd = nkracd + df["n0syt45_vkacd_glu"].to_numpy()[itc_bins]
            nffmob = nffmob + df["n0syt45_vfmob_glu"].to_numpy()[itc_bins]
            nffrel = nffrel + df["n0syt45_vfrel_glu"].to_numpy()[itc_bins]
            nffend = nffend + df["n0syt45_vfend_glu"].to_numpy()[itc_bins]
            nffacd = nffacd + df["n0syt45_vfacd_glu"].to_numpy()[itc_bins]
            # print(nkrdoc)
            # print(timesca,timesrel)
            # input()
        # }
        tc_nkrdoc[igroup,ibatch,:] = nkrdoc/ntrial
        tc_nkrrel[igroup,ibatch,:] = nkrrel/ntrial
        tc_nkrend[igroup,ibatch,:] = nkrend/ntrial
        tc_nkracd[igroup,ibatch,:] = nkracd/ntrial
        tc_nffmob[igroup,ibatch,:] = nffmob/ntrial
        tc_nffrel[igroup,ibatch,:] = nffrel/ntrial
        tc_nffend[igroup,ibatch,:] = nffend/ntrial
        tc_nffacd[igroup,ibatch,:] = nffacd/ntrial
        # input()
    # }
# }

# --------------------------------- saving data ---------------------------
# save the matrices using h5py
with h5py.File(os.path.join(datasavepath,h5pyfname),'w') as h5f:
    # {
    dset1 = h5f.create_dataset("binscacytpk",data=binscacytpk)
    dset2 = h5f.create_dataset("binscacytrt",data=binscacytrt)
    dset3 = h5f.create_dataset("hcacytpk",data=hcacytpk)
    dset4 = h5f.create_dataset("hcacytrt",data=hcacytrt)
    dset5 = h5f.create_dataset("binst",data=binst)
    dset6 = h5f.create_dataset("psthca",data=psthca)
    dset7 = h5f.create_dataset("psthrel",data=psthrel)
    dset8 = h5f.create_dataset("psthkrrel",data=psthkrrel)
    dset9 = h5f.create_dataset("psthffrel",data=psthffrel)
    dset10 = h5f.create_dataset("tc_bins",data=tc_bins)
    dset11 = h5f.create_dataset("tc_nkrrel",data=tc_nkrrel)
    dset12 = h5f.create_dataset("tc_nkrdoc",data=tc_nkrdoc)
    dset13 = h5f.create_dataset("tc_nkrend",data=tc_nkrend)
    dset14 = h5f.create_dataset("tc_nkracd",data=tc_nkracd)
    dset15 = h5f.create_dataset("tc_nffrel",data=tc_nffrel)
    dset16 = h5f.create_dataset("tc_nffmob",data=tc_nffmob)
    dset17 = h5f.create_dataset("tc_nffend",data=tc_nffend)
    dset18 = h5f.create_dataset("tc_nffacd",data=tc_nffacd)
    dset19 = h5f.create_dataset("binscacytdk",data=binscacytdk)
    dset20 = h5f.create_dataset("hcacytdk",data=hcacytdk)
    dset21 = h5f.create_dataset("binscacytfw",data=binscacytfw)
    dset22 = h5f.create_dataset("hcacytfw",data=hcacytfw)
    dset23 = h5f.create_dataset("dmaxtcacyt",data=dmaxtcacyt)
    dset24 = h5f.create_dataset("dmaxtkrrel",data=dmaxtkrrel)
    dset25 = h5f.create_dataset("dmaxtffrel",data=dmaxtffrel)
# }



