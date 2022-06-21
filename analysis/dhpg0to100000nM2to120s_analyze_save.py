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
diskname = "/run/media/anup/3becd611-cb79-4b80-b941-2edcc0d64cb4/data/"
dir1 = "badhpgcarel/run/"
datasavepath = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/dhpg0to100000nM2to120s"
h5pyfname = "dhpg10to100000nM2to120s_cacyt_features.hdf5"
# ---------------------------
groups = ["ctrl","admglur","adpmca","admglurpmca"]
# groups = ["ctrl"]
ngroup = len(groups)
dhpgs = [0,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000] # dhpg
ndhpgs = len(dhpgs)
stimdurs = [2,10,30,60,90,120]
# stimdurs = [120]
trial0 = 1
ntrial = 100
tstim0 = 200
thres = 300e-9
delta = 300e-9
# tstim1 = 250
fname_prefix = "astrocyte_"
# varnames1 = ["time","n0ca_cyt","n0ca_er","n0ip3_cyt","s1glu_ext","n0syt45_vkdoc_glu","n0syt45_vkrel_glu","n0syt45_vkend_glu","n0syt45_vkacd_glu"]
# varnames2 = ["n0syt45_vfmob_glu","n0syt45_vfrel_glu","n0syt45_vfend_glu","n0syt45_vfacd_glu"]
# varnames3 = ["n0syt45_krrelrate_glu","n0syt45_ffrelrate_glu","n0syt45_totalrelrate_glu"]
# varnames4 = ["n0syt45_krreltime_glu","n0syt45_ffreltime_glu","n0syt45_reltime_glu"]
# varnames = varnames1 + varnames2 + varnames3 + varnames4
varnames = ["time","n0ca_cyt","n0ip3_cyt","n0ca_er"]
print(varnames)
# --------------------------
cacyt_resp = np.zeros((ngroup,ntrial,len(stimdurs),len(dhpgs)),dtype=np.float16()) # responsivity
cacyt_rate = np.zeros((ngroup,ntrial,len(stimdurs),len(dhpgs)),dtype=np.float16()) # cacyt event rate
cacyt_peak = np.zeros((ngroup,ntrial,len(stimdurs),len(dhpgs)),dtype=np.float16()) # cacyt event peak
ip3cyt_max = np.zeros((ngroup,ntrial,len(stimdurs),len(dhpgs)),dtype=np.float16()) # ip3cyt max
ip3cyt_avg = np.zeros((ngroup,ntrial,len(stimdurs),len(dhpgs)),dtype=np.float16()) # ip3cyt avg
# ----------------
cacyt_resting = np.zeros((ngroup,ntrial,len(stimdurs),len(dhpgs)),dtype=np.float16()) # cacyt resting
ip3cyt_resting = np.zeros((ngroup,ntrial,len(stimdurs),len(dhpgs)),dtype=np.float16()) # cacyt resting
caer_resting = np.zeros((ngroup,ntrial,len(stimdurs),len(dhpgs)),dtype=np.float16()) # cacyt resting
# ---------------
binst =  np.arange(0,200,0.1) # edges: histogram counts between edges no histogram size is 1-size of bins
cacyt_psth = np.zeros((ngroup,ntrial,len(stimdurs),len(dhpgs),len(binst)-1),dtype=np.float16)           # 
# -------------------------
for igroup in range(0,ngroup):
    for idhpg in range(0,len(dhpgs)):
        for istimdur in range(0,len(stimdurs)):
            fprefix = "".join((fname_prefix,str(stimdurs[istimdur]),"s",str(dhpgs[idhpg]),'nM'))
            for itrial,ifile in zip(range(0,ntrial),range(1,ntrial+1)):
            # {
                tstim1 = tstim0 + stimdurs[istimdur]
                findex =  ifile
                fname = "".join((fprefix,"_",groups[igroup],str(findex),".csv"))
                fullname = os.path.join(diskname,dir1,groups[igroup],fname)
                print(findex," ",fullname)
                df = pd.read_csv(fullname,header=0,usecols=varnames)
                t = df["time"].to_numpy()
                # ---------------
                # fh = plt.figure()
                # ah = fh.add_subplot(111)
                # ah.plot(t,y)
                # plt.show()
                # ----------------
                istim0 = np.where(t>tstim0)[0][0]-1
                istim1 = np.where(t<tstim1)[0][-1]
                cacyt_resting[igroup,itrial,istimdur,idhpg] = df["n0ca_cyt"].to_numpy()[0:istim0].mean()
                ip3cyt_resting[igroup,itrial,istimdur,idhpg] = df["n0ip3_cyt"].to_numpy()[0:istim0].mean()
                caer_resting[igroup,itrial,istimdur,idhpg] = df["n0ca_er"].to_numpy()[0:istim0].mean()
                cacyt0 = cacyt_resting[igroup,itrial,istimdur,idhpg]
                ip3cyt0 = ip3cyt_resting[igroup,itrial,istimdur,idhpg]
                caer0 = caer_resting[igroup,itrial,istimdur,idhpg]
                ip3cyt_max[igroup,itrial,istimdur,idhpg] = df["n0ip3_cyt"].to_numpy()[istim0:istim1].max()
                ip3cyt_avg[igroup,itrial,istimdur,idhpg] = df["n0ip3_cyt"].to_numpy()[istim0:istim1].mean()
                # ----------------
                y = df["n0ca_cyt"].to_numpy()
                df_temp = pd.DataFrame({"time":t,"y":y})
                peaks,rts,fwhms,taus,ipeaks,irts,ifwhms,itaus = astronfuns.compute_event_features(df_temp,thres,delta)
                resp = astronfuns.compute_responsivity(t,y,tstim0,tstim1)
                icacytpeaks = [ipeak for ipeak in ipeaks if ((t[ipeak]>t[istim0]) & (t[ipeak]<t[istim1]))]
                if(len(icacytpeaks)>0):
                    cacytpeaks = y[icacytpeaks]
                    tcacytpeaks = t[icacytpeaks]
                    histca,_ = np.histogram(tcacytpeaks,binst)
                    cacyt_psth[igroup,itrial,istimdur,idhpg,:] = histca 
                    rate = len(cacytpeaks)/(tstim1-tstim0)
                    # ----------------
                    cacyt_rate[igroup,itrial,istimdur,idhpg] = rate
                    cacyt_resp[igroup,itrial,istimdur,idhpg] = resp
                    cacyt_peak[igroup,itrial,istimdur,idhpg] = cacytpeaks.mean()
                    # ---------
                    print("itrial: {}, dhpg: {} nM, stim duration: {} responsivity: {}, rate: {}".format(itrial,dhpgs[idhpg],stimdurs[istimdur],resp,rate))
                    print("Resting ca_cyt: {}, ip3_cyt: {}, ca_er: {}".format(cacyt0,ip3cyt0,caer0))
                    # -----------------
                    # }
                # }
            # }
        # }
    # }
# }


# --------------------------------- saving data ---------------------------
# save the matrices using h5py
with h5py.File(os.path.join(datasavepath,h5pyfname),'w') as h5f:
    dset1 = h5f.create_dataset("groups",data=groups)
    dset2 = h5f.create_dataset("dhpgs",data=dhpgs)
    dset3 = h5f.create_dataset("stimdurs",data=stimdurs)
    dset4 = h5f.create_dataset("cacyt_resp",data=cacyt_resp)
    dset5 = h5f.create_dataset("cacyt_rate",data=cacyt_rate)
    dset6 = h5f.create_dataset("cacyt_peak",data=cacyt_peak)
    dset7 = h5f.create_dataset("cacyt_resting",data=cacyt_resting)
    dset8 = h5f.create_dataset("ip3cyt_resting",data=ip3cyt_resting)
    dset9 = h5f.create_dataset("caer_resting",data=caer_resting)
    dset10 = h5f.create_dataset("cacyt_psth",data=cacyt_psth)
    dset11 = h5f.create_dataset("ip3cyt_max",data=ip3cyt_max)
    dset12 = h5f.create_dataset("ip3cyt_avg",data=ip3cyt_avg)
# }
