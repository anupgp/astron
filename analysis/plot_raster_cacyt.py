import numpy as np
np.random.seed(875431)
import pandas as pd
import os
import astron_common_functions as astronfuns
from matplotlib import pyplot as plt
from matplotlib import transforms
from mpl_toolkits.mplot3d import axes3d
import matplotlib.font_manager as font_manager
# plt.ion()
font_path = '/home/anup/.matplotlib/fonts/arial.ttf'
fontprop = font_manager.FontProperties(fname=font_path)
import h5py



# --------------------------------
def stackplot_with_features(ah,t,y,peaks,rts,fwhms,taus,ipeaks,irts,ifwhms,itaus,hgap,tshift):
    ah.plot(t+tshift,y+hgap,color="black",linewidth=0.5,marker="",alpha=1)
    # plot tau region
    if (len(ipeaks) > 0):
        i20l = irts[0]
        i80l = irts[1]
        i50l = ifwhms[0]
        i50r = ifwhms[1]
    # }
    for i in range(0,len(ipeaks)):
        # plot peaks
        ah.plot(t[ipeaks[i]]+tshift,y[ipeaks[i]]+hgap,marker="o",markersize=0.3,linestyle="",color="red")
        # plot 20-80 risetime
        # ah.plot([t[i20l[i]]+tshift,t[i80l[i]]+tshift],[y[i20l[i]]+hgap,y[i80l[i]]+hgap],color="green",linewidth=0.8)
        # plot fwhms
        # ah.plot([t[i50l[i]]+tshift,t[i50r[i]]+tshift],[y[i50l[i]]+hgap,y[i50r[i]]+hgap],color="orange",linewidth=0.8)
        # plot taus
        # ah.plot(t[itaus[i]]+tshift,y[itaus[i]]+hgap,marker="o",markersize=0.1,linestyle="",color="blue")
        # ah.plot(t[ipeaks[i]:itaus[i]]+tshift,y[ipeaks[i]:itaus[i]]+hgap,color="blue",linewidth=0.8,marker="")
    # }
    # ah.spines["right"].set_visible(False)
    # ah.spines["top"].set_visible(False)
    # ah.spines["left"].set_visible(False)
    # ah.spines["bottom"].set_visible(False)
    # ah.set_xticks([])
    # ah.set_xticklabels([],fontsize=8,font=fontprop)
    # ah.set_yticks([])
    # ah.set_yticklabels([],fontsize=8,font=fontprop)
    return(ah)
# ------------------------------

def plot3d_with_features(ah,t,y,itrial,peaks,rts,fwhms,taus,ipeaks,irts,ifwhms,itaus):
    z = np.zeros(t.shape)+itrial
    ah.plot3D(t,y,itrial,zdir='x',color="grey",linewidth=0.5,marker="")
    if (len(ipeaks) > 0):
        i20l = irts[0]
        i80l = irts[1]
        i50l = ifwhms[0]
        i50r = ifwhms[1]

    for i in range(0,len(ipeaks)):
        # plot peaks
        ah.plot3D(t[ipeaks[i]],y[ipeaks[i]],itrial,zdir='x',marker="o",markersize=0.1,linestyle="",color="red")
        # plot 20-80 risetime
        ah.plot3D([t[i20l[i]],t[i80l[i]]],[y[i20l[i]],y[i80l[i]]],[itrial,itrial],zdir='x',color="black",linewidth=0.2)
        # plot fwhms
        ah.plot3D([t[i50l[i]],t[i50r[i]]],[y[i50l[i]],y[i50r[i]]],[itrial,itrial],zdir='x',color="black",linewidth=0.2)
        # plot taus
        ah.plot3D(t[itaus[i]],y[itaus[i]],itrial,zdir='x',marker="o",markersize=0.1,linestyle="",color="blue")
    # }

# -------------------------------------
# diskname = "/home/anup/data/"
# dir1 = "ap1to1000dhz30scarel/run/"
disk = "/run/media/anup/3becd611-cb79-4b80-b941-2edcc0d64cb4/"
folder1 = "data/"
# folder2 = "dhpg100000nM2s/run/"
folder2 = "badhpgcarel/run/"


# groups = ["ctrl","admglur","adpmca","admglurpmca"]
groups = ["ctrl"]
ngroups = len(groups)
# allfreqs = [1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000]
# freqs = [4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000]
# freqs = [100]
# _,ifreqs,_ = np.intersect1d(allfreqs,freqs,return_indices=True)
# nfreqs = len(freqs)
# ------------------
dhpgs = [0,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000] # dhpg
ndhpgs = len(dhpgs)
dhpg = 6000
# ----------------
stimdurs = [2,10,30,60,90,120]
nstimdurs = len(stimdurs)
stimdur = 120
# ---------------
# print(nfreqs,freqs,ifreqs)
# input()
trial0 = 1
ntrials = 30
trials = np.sort(np.random.choice(range(trial0,ntrials+trial0),ntrials,replace=False))
# varnames=['time','n0ca_cyt','n0syt45_reltime_glu','n0syt45_vkdoc_glu','n0syt45_vfmob_glu']
timecol = "time"
cacol="n0ca_cyt"
varnames = [timecol,cacol]
thres = 300e-3          # 300 nM"
delta = 1*thres          # 300 nM"

# hgap = -0.07
# hgaptrial = 5
# tshift = -0.17
# tshifttrial = 10
# tstimstart = 200
# tstimstop = 230

# hgap = 0.65
# hgaptrial0 = -0.3
# tshift = -0.4
# tshifttrial0 = 3
# tstimstart = 200
# tstimstop = 202

# fh1,(ah1) = plt.subplots(figsize=(4,4),dpi=600,frameon=False,ncols=1,nrows=1,gridspec_kw={"width_ratios":[1],"height_ratios":[1]},subplot_kw=dict(projection='3d'))
fh1,(ah1) = plt.subplots(figsize=(4,3),dpi=600,frameon=False,ncols=1,nrows=1)
# ahs_raster = [ah1[0],ah1[1],ah1[2],ah1[3]]
ahs_raster = [ah1]
# fh1.subplots_adjust(hspace=0,wspace=0)
# -------------------------
# for igroup in range(0,len(groups)):
#     for ifreq in range(0,len(freqs)):
#         fprefix = "".join(("astrocyte_ap30s",str(freqs[ifreq]),"dHz"))
#         # fprefix = "".join(("astrocyte_ap",str(freqs[ifreq]),"dHz30s"))
#         for itrial,ifile in zip(range(0,ntrials),trials):
#             findex =  ifile
#             fname = "".join((fprefix,"_",groups[igroup],str(findex),".csv"))
#             fullname = os.path.join(diskname,dir1,groups[igroup],fname)
#             print(findex," ",fullname)
#             df = pd.read_csv(fullname,header=0,usecols=varnames)
#             t = df[timecol] - tstimstart
#             y = df[cacol] * 1e6
#             timesca = astronfuns.detect_peaks_above_threshold(t,y,thres,delta,eventval=0)
#             # fh = plt.figure(figsize=(3,3),frameon=False)
#             # ah = fh.add_subplot(111)
#             # ah.plot(df[timecol],df[cacol])
#             # plt.show()
#             peaks,rts,fwhms,taus,ipeaks,irts,ifwhms,itaus = astronfuns.compute_event_features(df,thres,delta)
#             hgaptrial = hgaptrial + hgap
#             tshifttrial = tshifttrial + tshift
#             ahs_raster[igroup] = stackplot_with_features(ahs_raster[igroup],t,y,peaks,rts,fwhms,taus,ipeaks,irts,ifwhms,itaus,hgaptrial,tshifttrial)
#             # _ = plot3d_with_features(ahs_raster[igroup],t,y,itrial,peaks,rts,fwhms,taus,ipeaks,irts,ifwhms,itaus)
#             # (ah,t,y,hgaptrial,tshifttrial)
#             # ah.plot(t,y+itrial)
#         # }
#     # }
# # }
# ------------------------
# for igroup in range(0,len(groups)):
#     fprefix = "astrocyte_dhpg100000nM2s"
#     hgaptrial = hgaptrial0
#     tshifttrial = tshifttrial0
#     for itrial,ifile in zip(range(0,ntrials),trials):
#         findex =  ifile
#         fname = "".join((fprefix,"_",groups[igroup],str(findex),".csv"))
#         fullname = os.path.join(disk,folder1,folder2,groups[igroup],fname)
#         print(findex," ",fullname)
#         df = pd.read_csv(fullname,header=0,usecols=varnames)
#         t = df[timecol][(df[timecol] > (tstimstart-1)) & (df[timecol] < (tstimstop + 1))].to_numpy() -tstimstart
#         y = df[cacol][(df[timecol] > (tstimstart-1)) & (df[timecol] < (tstimstop + 1))].to_numpy() * 1e6
#         # t = df[timecol] - tstimstart
#         # y = df[cacol] * 1e6
#         dftemp = pd.DataFrame({"time":t,cacol:y})
#         timesca = astronfuns.detect_peaks_above_threshold(t,y,thres,delta,eventval=0)
#         # fh = plt.figure(figsize=(3,3),frameon=False)
#         # ah = fh.add_subplot(111)
#         # ah.plot(df[timecol],df[cacol])
#         # plt.show()
#         peaks,rts,fwhms,taus,ipeaks,irts,ifwhms,itaus = astronfuns.compute_event_features(dftemp,thres,delta)
#         hgaptrial = hgaptrial + hgap
#         tshifttrial = tshifttrial + tshift
#         ahs_raster[igroup] = stackplot_with_features(ahs_raster[igroup],t,y,peaks,rts,fwhms,taus,ipeaks,irts,ifwhms,itaus,hgaptrial,tshifttrial)
#         # _ = plot3d_with_features(ahs_raster[igroup],t,y,itrial,peaks,rts,fwhms,taus,ipeaks,irts,ifwhms,itaus)
#         # (ah,t,y,hgaptrial,tshifttrial)
#         # ah.plot(t,y+itrial)
#     # }
# # }
# ---------------------------
hgap = 0.65
hgaptrial0 = -0.7
tshift = -0.55
tshifttrial0 = 7
tstimstart = 200
tstimstop = 320
# ------------------
for igroup in range(0,len(groups)):
    fprefix = "".join(("astrocyte_",str(stimdur),"s",str(dhpg),'nM'))
    hgaptrial = hgaptrial0
    tshifttrial = tshifttrial0
    for itrial,ifile in zip(range(0,ntrials),trials):
        findex =  ifile
        fname = "".join((fprefix,"_",groups[igroup],str(findex),".csv"))
        fullname = os.path.join(disk,folder1,folder2,groups[igroup],fname)
        print(findex," ",fullname)
        df = pd.read_csv(fullname,header=0,usecols=varnames)
        t = df[timecol][(df[timecol] > (tstimstart-1)) & (df[timecol] < (tstimstop + 1))].to_numpy() -tstimstart
        y = df[cacol][(df[timecol] > (tstimstart-1)) & (df[timecol] < (tstimstop + 1))].to_numpy() * 1e6
        # t = df[timecol] - tstimstart
        # y = df[cacol] * 1e6
        dftemp = pd.DataFrame({"time":t,cacol:y})
        timesca = astronfuns.detect_peaks_above_threshold(t,y,thres,delta,eventval=0)
        # fh = plt.figure(figsize=(3,3),frameon=False)
        # ah = fh.add_subplot(111)
        # ah.plot(df[timecol],df[cacol])
        # plt.show()
        peaks,rts,fwhms,taus,ipeaks,irts,ifwhms,itaus = astronfuns.compute_event_features(dftemp,thres,delta)
        hgaptrial = hgaptrial + hgap
        tshifttrial = tshifttrial + tshift
        # downsample data for plotting
        it_ds = np.linspace(0,len(t)-1,5000,dtype=int)
        t_ds = t[it_ds]
        y_ds = y[it_ds]
        tpeaks = t[ipeaks]
        ipeaks_ds = np.array([np.where(t_ds>tpeak)[0][0]-1 for tpeak in tpeaks])
        ahs_raster[igroup] = stackplot_with_features(ahs_raster[igroup],t_ds,y_ds,peaks,rts,fwhms,taus,ipeaks_ds,irts,ifwhms,itaus,hgaptrial,tshifttrial)
        # _ = plot3d_with_features(ahs_raster[igroup],t,y,itrial,peaks,rts,fwhms,taus,ipeaks,irts,ifwhms,itaus)
        # (ah,t,y,hgaptrial,tshifttrial)
        # ah.plot(t,y+itrial)
    # }
# }

# ---------------------------
# [ah.axis('off') for ah in ahs_raster]
# xticks = [0,30]
[ah.set_xlim([-10,140]) for ah in ahs_raster]
[ah.set_xticks([]) for ah in ahs_raster]
[ah.set_xticklabels([],fontsize=8,font=fontprop) for ah in ahs_raster]

yticks = [0,10]
[ah.set_ylim([0,30]) for ah in ahs_raster]
[ah.set_yticks([]) for ah in ahs_raster]
[ah.set_yticklabels([],fontsize=8,font=fontprop) for ah in ahs_raster]

[ah.spines["right"].set_visible(False) for ah in ahs_raster]
[ah.spines["top"].set_visible(False) for ah in ahs_raster]
[ah.spines["left"].set_visible(False) for ah in ahs_raster]
[ah.spines["bottom"].set_visible(False) for ah in ahs_raster]
# plot scale bar
ahs_raster[0].plot([120,130],[15,15],linestyle="-",marker="",linewidth=0.5,color="black")
ahs_raster[0].text(120,13,"10 sec",font=fontprop,fontsize=10)
ahs_raster[0].plot([130,130],[15,19],linestyle="-",marker="",linewidth=0.5,color="black")
ahs_raster[0].text(133,15,"4 $\mu$M",rotation=90,font=fontprop,fontsize=10)
# plot stim positions
# ahs_raster[0].plot([-10,0],[-2,-2],linestyle="-",marker="",linewidth=0.5,color="black")
# ahs_raster[0].plot([0,0],[-2,-1],linestyle="-",marker="",linewidth=0.5,color="black")
# ahs_raster[0].plot([0,120],[-1,-1],linestyle="-",marker="",linewidth=0.5,color="black")
# ahs_raster[0].plot([120,120],[-1,-2],linestyle="-",marker="",linewidth=0.5,color="black")
# ahs_raster[0].plot([120,130],[-2,-2],linestyle="-",marker="",linewidth=0.5,color="black")
# [ah.set_zticks([]) for ah in ahs_raster]
# [ah.set_xticks([]) for ah in ahs_raster]
# [ah.grid(False) for ah in ahs_raster]
# [ah.w_xaxis.set_pane_color((1,1,1)) for ah in ahs_raster]
# [ah.w_yaxis.set_pane_color((1,1,1)) for ah in ahs_raster]
# [ah.w_zaxis.set_pane_color((1,1,1)) for ah in ahs_raster]
# [ah.axis('off') for ah in ahs_raster[1:]]

# [ah.view_init(20,0) for ah in ahs_raster]

# ah.spines["left"].set_visible(False)
# ah.spines["bottom"].set_visible(False)
# ah.set_xticks([])
# ah.set_xticklabels([],fontsize=8,font=fontprop)
# ah.set_yticks([])
# ah.set_yticklabels([],fontsize=8,font=fontprop)

# saving figures
# figsavepath = "/home/anup/goofy/data/suhitalab/astron/figures/new_2020_python/ap1to1000dhz30s"
# figsavepath = "/home/anup/goofy/data/suhitalab/astron/figures/new_2020_python/dhpg100000nM2s"
figsavepath = "/home/anup/goofy/data/suhitalab/astron/figures/new_2020_python/dhpg0to100000nM2to120s"
fh1_name = "".join(("dhpg0to100000nM2to120s_cacyt_stack_plot_",str(dhpg),"nM_",str(stimdur),"s_",groups[0],".svg"))
fh1.savefig(os.path.join(figsavepath,fh1_name),transparent=True)

plt.show()
