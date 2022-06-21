import numpy as np
np.random.seed(875431)
import pandas as pd
from scipy import signal
import os
import astron_common_functions as astronfuns
import matplotlib
from matplotlib import pyplot as plt
import matplotlib.font_manager as font_manager
print("matplotlibrc loc: ",matplotlib.matplotlib_fname())
# plt.ion()
font_path = '/home/anup/.matplotlib/fonts/arial.ttf'
fontprop = font_manager.FontProperties(fname=font_path)
import h5py

# =====================================================================================
# load data: Provide the path and filename of the hdf5 file containing the analyzed data
# dir1 = "/home/anup/data/dhpg100000nM2s/analysis/"
# fnameh5py = "dhpg100000nM2s_cacyt_rel_event_features.hdf5"
# figsavepath = dir1 # path to the folder where figures will be saved
# ------------
dir1 = "/home/anup/goofy/data/astron/cooked/new_2020_python/dhpg100000nM2s_cacyt_rel_features"
fnameh5py = "dhpg100000nM2s_cacyt_rel_event_features.hdf5"
figsavepath = "/home/anup/goofy/data/astron/writing/AD_paper/ploscompbio1.3/figures2022/dhpg100000nM2s" # path to the folder where figures will be saved
# ------------
binscacytpk = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"binscacytpk")
binscacytrt = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"binscacytrt")
binscacytdk = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"binscacytdk")
binscacytfw = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"binscacytfw")
hcacytpk = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"hcacytpk")
hcacytrt = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"hcacytrt")
hcacytdk = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"hcacytdk")
hcacytfw = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"hcacytfw")
# ------------
dmaxtcacyt = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"dmaxtcacyt")
dmaxtkrrel = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"dmaxtkrrel")
dmaxtffrel = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"dmaxtffrel")
# ------------
binst = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"binst")
psthca = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"psthca")
psthrel = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"psthrel")
psthkrrel = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"psthkrrel")
psthffrel = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"psthffrel")
tc_bins = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"tc_bins")
tc_nkrrel = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"tc_nkrrel")
tc_nkrdoc = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"tc_nkrdoc")
tc_nkrend = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"tc_nkrend")
tc_nkracd = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"tc_nkracd")
tc_nffrel = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"tc_nffrel")
tc_nffmob = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"tc_nffmob")
tc_nffend = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"tc_nffend")
tc_nffacd = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"tc_nffacd")
# ------------
# fgiure legend labels and colors
grouplabels = ["Control",r"$A\beta$-mGluR",r"$A\beta$-PMCA",r"$A\beta$-mGluR & PMCA"]
plotcolors = np.array([
    [0,0,0],
    [1,0,0],
    [0,0,1],
    [0,1,0]
])
# =========================================================================================================================
# Figures 3D&E
# Timecourse plots of release event features: number of docked/mobile vesicle release-ready/released/endocytosed/reacidified
# ==========================================================================================================================
# datasets = [tc_nkrdoc,tc_nkrrel,tc_nkrend,tc_nkracd]
# # datasets = [tc_nffmob,tc_nffrel,tc_nffend,tc_nffacd]
# ndataset = len(datasets)
# ngroup = 1
# nbatch = 1
# ntrial = 280
# lineavgs = np.array([np.mean(dataset,axis=1)*400 for dataset in datasets])
# linesems = np.array([np.std(dataset,axis=1)/np.sqrt(nbatch)*400 for dataset in datasets])
# # downsample data to reduce plot image filesize
# itc_bins_ds = np.linspace(0,len(tc_bins)-1,150,dtype=int)
# tc_bins_ds = tc_bins[itc_bins_ds]
# lineavgs_ds = lineavgs[:,:,itc_bins_ds]
# linesems_ds = linesems[:,:,itc_bins_ds]
# print(tc_bins_ds.shape,tc_bins[0],tc_bins[-1],lineavgs_ds.shape,linesems.shape)
# labels = ["Releasable","Released","Endocytosed","Reacidified"]
# # --------------
# # fh1,ah11 = plt.subplots(figsize=(2,2),dpi=600,frameon=False,ncols=1,gridspec_kw={"width_ratios":[1]})
# fh1,ah11 = plt.subplots(figsize=(2.2,2.2),dpi=600,frameon=False,ncols=1,nrows=1)
# plotcolors = ["grey","green","orange","red"]
# for iset in range(0,ndataset):
#     for igroup in range(0,1):
#         ph1 = ah11.plot(tc_bins_ds-200,lineavgs_ds[iset][igroup,:],marker='.',markerfacecolor=plotcolors[iset],markeredgecolor=plotcolors[iset],markersize=1,linewidth=0,label=labels[iset])
#         for itc in range(0,len(tc_bins_ds)):
#             # ph1 = ah11.plot(tc_bins[itc]-200,lineavgs[iset][igroup,itc],marker='o',color=plotcolors[iset],markersize=2)
#             error1 = lineavgs_ds[iset][igroup,itc] - linesems_ds[iset][igroup,itc]
#             error2 = lineavgs_ds[iset][igroup,itc] + linesems_ds[iset][igroup,itc]
#             ah11.plot([tc_bins_ds[itc]-200,tc_bins_ds[itc]-200],[error1,error2],linestyle="-",color="black",linewidth=0.5)
#         # }

#     # }
# # }
# # ah11.plot([0,2],[-25,-25],linewidth=1,color="black") # kr
# # ah11.plot([0,2],[-5,-5],linewidth=1,color="black") # ff
# # formatting
# ah11.set_xlim([-1,20])          # kr
# xticks = [0,10,20]         # kr
# # ah11.set_xlim([-1,30])           # ff
# # xticks = [0,15,30]              # ff
# ah11.set_xticks(xticks)
# ah11.set_xticklabels(xticks,fontsize=8,font=fontprop)
# # ah11.get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
# ah11.set_xlabel("Time (s)",fontsize=8,font=fontprop)
# yticks = [0,200,400]            # kr
# ah11.set_ylim([-20,500])        # kr
# # yticks = [0,30,60]              # ff
# # ah11.set_ylim([-5,70])         # ff
# ah11.set_yticks(yticks)
# ah11.set_yticklabels(yticks,fontsize=8,font=fontprop)
# ah11.spines["right"].set_visible(False)
# ah11.spines["top"].set_visible(False)
# # matplotlib.rcParams["mathtext.sf"]
# # yaxislabel = r'#$Ca^{2+}$ events' # cacyt
# # yaxislabel = r'# Full fusion events'
# yaxislabel = r'#Docked vesicles'
# ah11.set_ylabel(yaxislabel,fontsize=8,font=fontprop)
# # plot stim positions
# ah11.plot([0,2],[430,430],linestyle="-",marker="",linewidth=2,color="black") # kr
# ah11.text(0,450,"DHPG (100 $\mu$M)",font=fontprop,fontsize=9) # kr
# # ah11.plot([0,2],[60,60],linestyle="-",marker="",linewidth=2,color="black") # ff
# # ah11.text(0,65,"DHPG (100 $\mu$M)",font=fontprop,fontsize=9) # ff
# fontprop1 = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=7)
# lgnd = ah11.legend(frameon=False,loc=0,bbox_to_anchor=(0.4,0.55),prop=fontprop1,labelspacing=0.08)
# lgnd.legendHandles[0]._legmarker.set_markersize(4)
# lgnd.legendHandles[1]._legmarker.set_markersize(4)
# lgnd.legendHandles[2]._legmarker.set_markersize(4)
# lgnd.legendHandles[3]._legmarker.set_markersize(4)
# fh1.tight_layout()
# # saving figures
# fh1_name = "dhpg100000nM2s_kr_ves_features.svg"
# fh1.savefig(os.path.join(figsavepath,fh1_name))
# plt.show()
# =====================================================================================
# Figures 1H & 3F
# Plot calcium/release psth with experimental data
# =====================================================================================
# # Load experimental data for DHPG-mediated ca2+ events
# folder1 = "/home/anup/goofy/codes/astron/validation_data"
# fname1 = "marchaland2008_dhpg_cacyt_histogram.csv" # validation data psth cacyt
# # fname1 = "marchaland2008_dhpg_release_histogram.csv" # validation data psth release
# dfexp = pd.read_csv(os.path.join(folder1,fname1));   # load validation data set
# # interpolate experimental data to fill make the time bins 50 ms
# tbinsexp = np.arange(-1,5,50e-3)
# expy = np.interp(tbinsexp,dfexp["time"],dfexp["ca_cyt_events"]) # validation psth cacyt
# # expy = np.interp(tbinsexp,dfexp["time"],dfexp["release"]) # validation psth releases
# expy[expy<0] = 0
# expy[tbinsexp>max(dfexp["time"])] = 0
# dfexp2 = pd.DataFrame({"tbins":tbinsexp,"psth":expy})
# # dataset = psthca               # select simulation data for calcium events
# dataset = psthrel               # select simulation data for release events
# ngroup = 1
# nbatch = 6
# ntrial = 400
# toffset = 0.1                  # 0.05, 0.2
# lineavg = np.mean(dataset,axis=1)
# linesem = np.std(dataset,axis=1)/np.sqrt(nbatch)
# # fh1,ah11 = plt.subplots(figsize=(2.2,2.2),dpi=600,frameon=False,ncols=1,gridspec_kw={"width_ratios":[1]})
# fh1,ah11 = plt.subplots(figsize=(2.2,2.2),dpi=600,frameon=False,ncols=1,nrows=1)
# ph11 = ah11.plot(dfexp2["tbins"]+toffset,dfexp2["psth"],color="orange",label="Experiment")
# for igroup in range(0,1):
#     for ibin in range(0,len(binst)-1):
#         error1 = lineavg[igroup,ibin] - linesem[igroup,ibin]
#         error2 = lineavg[igroup,ibin] + linesem[igroup,ibin]
#         if (ibin == 0):
#             ah11.plot([binst[ibin]-200,binst[ibin]-200],[error1,error2],linestyle="-",color="grey",linewidth=1)
#             ph11 = ah11.plot(binst[ibin]-200,lineavg[igroup,ibin],marker='o',linestyle="-",color=plotcolors[igroup,:],markersize=1,label="Model")
#         else:
#             ah11.plot([binst[ibin]-200,binst[ibin]-200],[error1,error2],linestyle="-",color="grey",linewidth=1)
#             ph11 = ah11.plot(binst[ibin]-200,lineavg[igroup,ibin],marker='o',linestyle="-",color=plotcolors[igroup,:],markersize=1)
#         # ph11 = ah11.plot(binst[ibin]-200,lineavg[igroup,ibin],marker='o',linestyle="-",color=plotcolors[igroup,:],markersize=1)
#         # ph11 = ah11.bar(binst[ibin]-200,lineavg[igroup,ibin],color=plotcolors[igroup,:],width=0.045)
#     # }
# # }
# # formatting
# ah11.set_xlim([-0.2,3])
# xticks = [0,1,2,3]
# ah11.set_xticks(xticks)
# ah11.set_xticklabels(xticks,fontsize=6,font=fontprop)
# # ah11.get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
# ah11.set_xlabel("Time (s)",fontsize=6,font=fontprop)
# yticks = [0,25,50]
# ah11.set_ylim([-5,50])
# ah11.set_yticks(yticks)
# ah11.set_yticklabels(yticks,fontsize=8,font=fontprop)
# ah11.spines["right"].set_visible(False)
# ah11.spines["top"].set_visible(False)
# ah11.legend(frameon=False,loc=2,bbox_to_anchor=(0.25,0.75),fontsize=8,labelspacing=0.04)
# # matplotlib.rcParams["mathtext.sf"]
# # yaxislabel = r'#$Ca^{2+}$ events' # cacyt events
# yaxislabel = r'#Release events' # release events
# ah11.set_ylabel(yaxislabel,fontsize=8,font=fontprop)
# # # plot stim positions
# ah11.plot([0,2],[41,41],linestyle="-",marker="",linewidth=2,color="black")
# ah11.text(0,44,"DHPG (100 $\mu$M)",font=fontprop,fontsize=8)
# fh1.tight_layout()
# # saving figures
# fh1_name = "dhpg100000nM2s_psth_rel.svg"
# fh1.savefig(os.path.join(figsavepath,fh1_name))
# plt.show()
# =======================================================================================
# Figures 1D,E,F,& G
# Plot histogram cacyt event features: peak/risetime/decaytime(tau)/fwhm
# ======================================================================================
# ydat = hcacytpk
# xdat = binscacytpk*1e6
# ydat = hcacytrt
# xdat = binscacytrt*1000
# ydat = hcacytfw
# xdat = binscacytfw*1000
# ydat = hcacytdk
# xdat = binscacytdk*1000
# ngroup = 4
# nbatch = 6
# ntrial = 400
# lineavg = np.mean(ydat,axis=1)
# linesem = np.std(ydat,axis=1)/np.sqrt(nbatch)
# print(lineavg)
# fh1,ah11 = plt.subplots(figsize=(2,2),dpi=600,frameon=False,ncols=1,gridspec_kw={"width_ratios":[1]})
# for igroup in range(0,1):
#     # ah11.plot(xdat[0:-1],lineavg[igroup,:],color=plotcolors[igroup,:],markersize=0,linewidth=1)
#     # ah11.bar(xdat[0:-1],lineavg[igroup,:],width=0.4,color="grey")
#     ah11.bar(xdat[0:-1],lineavg[igroup,:],width=20,color="grey")
#     for ix in range(0,len(xdat)-1):
#         # ph11 =  ah11.plot(xdat[ix],lineavg[igroup,ix],marker='o',color=plotcolors[igroup,:],markersize=3)
#         error1 = lineavg[igroup,ix] - linesem[igroup,ix]
#         error2 = lineavg[igroup,ix] + linesem[igroup,ix]
#         ah11.plot([xdat[ix],xdat[ix]],[error1,error2],linestyle="-",color="black",linewidth=1)
#     # }
# # }
# # formatting
# # ---------------
# # ah11.set_xlim([0,15])           # pk
# # xticks = [0,5,10,15]            # pk
# # yticks = [0,25,50]              # pk
# # ah11.set_ylim([0,50])           # pk
# # xaxislabel = r'$Ca^{2+} event \ peak\ (\mu$M)' # pk
# # xaxislabel = r'$Peak \ amplitude\ (\mu$M)' # pk
# # -----------------
# # ah11.set_xlim([-30,260])           # rt
# # xticks = [0,80,160,240]            # rt
# # yticks = [0,100,200]              # rt
# # ah11.set_ylim([-20,200])           # rt
# # xaxislabel = r'$Ca^{2+}$ event risetime (ms)' # rt
# # xaxislabel = r'Risetime (ms)' # rt
# # --------------
# # ah11.set_xlim([0,470])           # fw
# # xticks = [0,150,300,450]            # fw
# # yticks = [0,50,100]              # fw
# # ah11.set_ylim([-5,100])           # fw
# # load the xfrac package
# # xaxislabel = r'$Ca^{2+}$ event full-width $\frac{1}{2}$-max (ms)' # fw
# # xaxislabel = r'FWHM (ms)' # fw
# # --------------
# ah11.set_xlim([0,470])           # dk
# xticks = [0,150,300,450]            # dk
# yticks = [0,75,150]              # dk
# ah11.set_ylim([-5,150])           # dk
# # load the xfrac package
# # xaxislabel = r'$Ca^{2+}$ event decay time (ms)' # dk
# xaxislabel = r'Decay time (ms)' # dk
# # --------------
# ah11.set_xticks(xticks)
# ah11.set_xticklabels(xticks,fontsize=8,font=fontprop)
# ah11.set_xlabel(xaxislabel,fontsize=8,font=fontprop,labelpad=5)
# ah11.set_yticks(yticks)
# ah11.set_yticklabels(yticks,fontsize=8,font=fontprop)
# ah11.spines["right"].set_visible(False)
# ah11.spines["top"].set_visible(False)
# # matplotlib.rcParams["mathtext.sf"]
# yaxislabel = r'Count'
# ah11.set_ylabel(yaxislabel,fontsize=8,font=fontprop)
# # ah11.plot([0,0],[0,ntrial],color="grey",linestyle="--",linewidth=0.5)
# # ah11.plot([2,2],[0,ntrial],color="grey",linestyle="--",linewidth=0.5)
# # saving figures
# # fh1.tight_layout()
# fh1_name = "dhpg100000nM2s_hist_cacyt_dk.svg"
# fh1.savefig(os.path.join(figsavepath,fh1_name))
# plt.show()
# ==============================================================================================
# Figures 1C & 3A
# Raster plot cacyt/release events
# ==============================================================================================
# fh1,ah11 = plt.subplots(figsize=(2,2),dpi=600,frameon=False,ncols=1,gridspec_kw={"width_ratios":[1]})
# fh1,ah11 = plt.subplots(figsize=(2.2,2.2),dpi=600,frameon=False,ncols=1,nrows=1)
# ntrial = 400
# ibatch = 0
# igroup = 0
# tstimstart = 200
# krlabel = False
# fflabel = False
# for itrial in range(0,ntrial):
#     # maxtevent1 = dmaxtcacyt[igroup,ibatch,itrial,:] # cacyt
#     maxtevent1 = dmaxtkrrel[igroup,ibatch,itrial,:] # krrel
#     maxtevent2 = dmaxtffrel[igroup,ibatch,itrial,:] # ffrel
#     maxtevent1 = maxtevent1[maxtevent1>0]
#     maxtevent2 = maxtevent2[maxtevent2>0]
#     maxtevent1 = maxtevent1 - tstimstart
#     maxtevent2 = maxtevent2 - tstimstart
#     for ievent in range(0,len(maxtevent1)):
#         if (not krlabel):
#             ah11.plot([maxtevent1[ievent],maxtevent1[ievent]],np.array([0,1])+itrial,color="orange",linewidth=1,label="KR release")
#             krlabel = True
#         else:
#             ah11.plot([maxtevent1[ievent],maxtevent1[ievent]],np.array([0,1])+itrial,color="orange",linewidth=1)
#     for ievent in range(0,len(maxtevent2)):
#         if (not fflabel):
#             ah11.plot([maxtevent2[ievent],maxtevent2[ievent]],np.array([0,1])+itrial,color="green",linewidth=1,label="FF release")
#             fflabel= True
#         else:
#             ah11.plot([maxtevent2[ievent],maxtevent2[ievent]],np.array([0,1])+itrial,color="green",linewidth=1)
#     # }
# # }
# # # formatting
# # ah11.set_xlim([-0.2,3])
# # xticks = [0,1,2,3]
# ah11.set_xlim([-1,8])
# xticks = [0,4,8]
# ah11.set_xticks(xticks)
# ah11.set_xticklabels(xticks,fontsize=8,font=fontprop)
# # ah11.get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
# ah11.set_xlabel("Time (s)",fontsize=8,font=fontprop)
# yticks = [0,200,400]
# ah11.set_ylim([-20,500])
# ah11.set_yticks(yticks)
# ah11.set_yticklabels(yticks,fontsize=8,font=fontprop)
# ah11.spines["right"].set_visible(False)
# ah11.spines["top"].set_visible(False)
# # matplotlib.rcParams["mathtext.sf"]
# yaxislabel = r'#Trials'
# ah11.set_ylabel(yaxislabel,fontsize=8,font=fontprop)
# ah11.plot([0,0],[0,ntrial],color="grey",linestyle="--",linewidth=0.5)
# ah11.plot([2,2],[0,ntrial],color="grey",linestyle="--",linewidth=0.5)
# # plot stim positions
# ah11.plot([0,2],[425,425],linestyle="-",marker="",linewidth=2,color="black")
# ah11.text(0,440,"DHPG (100 $\mu$M)",font=fontprop,fontsize=9)
# fontprop1 = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=7)
# ah11.legend(frameon=False,loc=1,bbox_to_anchor=(1,0.6),prop=fontprop1,labelspacing=0.06)
# fh1.tight_layout()
# # # saving figures
# fh1_name = "dhpg100000nM2s_raster_dmaxtrel.svg"
# fh1.savefig(os.path.join(figsavepath,fh1_name))
# plt.show()
# ===================================================================================
# # Figures 3B & C
# # Plot kr/ff release psth
# ==================================================================================
# # dataset = psthkrrel
# dataset = psthffrel
# ngroup = 4
# nbatch = 6
# ntrial = 400
# lineavg = np.mean(dataset,axis=1)
# linesem = np.std(dataset,axis=1)/np.sqrt(nbatch)
# # fh1,ah11 = plt.subplots(figsize=(2.2,2.2),dpi=600,frameon=False,ncols=1,gridspec_kw={"width_ratios":[1]})
# fh1,ah11 = plt.subplots(figsize=(2.2,2.2),dpi=600,frameon=False,ncols=1,nrows=1)
# for igroup in range(0,1):
#     for ibin in range(0,len(binst)-1):
#         error1 = lineavg[igroup,ibin] - linesem[igroup,ibin]
#         error2 = lineavg[igroup,ibin] + linesem[igroup,ibin]
#         ph11 = ah11.plot(binst[ibin]-200,lineavg[igroup,ibin],marker='o',linestyle="-",color="green",markersize=1)
#         ah11.plot([binst[ibin]-200,binst[ibin]-200],[error1,error2],linestyle="-",color="black",linewidth=0.5)
#     # }
# # }
# # formatting
# # ah11.set_xlim([-0.5,5])           # kr
# # xticks = [0,2.5,5]              # kr
# # yticks = [0,20,40]              # kr
# # ah11.set_ylim([-3,40])         # kr
# ah11.set_xlim([-0.2,5])           # ff
# xticks = [0,2.5,5]              # ff
# ah11.set_xticks(xticks)
# ah11.set_xticklabels(xticks,fontsize=8,font=fontprop)
# # ah11.get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
# ah11.set_xlabel("Time (s)",fontsize=8,font=fontprop)
# yticks = [0,2,4]              # ff
# ah11.set_ylim([-0.3,4])         # ff
# ah11.set_yticks(yticks)
# ah11.set_yticklabels(yticks,fontsize=8,font=fontprop)
# ah11.spines["right"].set_visible(False)
# ah11.spines["top"].set_visible(False)
# # matplotlib.rcParams["mathtext.sf"]
# # yaxislabel = r'#$Ca^{2+}$ events' # cacyt
# # yaxislabel = r'# Full fusion events'
# yaxislabel = r'#Events (FF)'
# ah11.set_ylabel(yaxislabel,fontsize=8,font=fontprop)
# # plot stim positions
# # ah11.plot([0,2],[32,32],linestyle="-",marker="",linewidth=2,color="black") # kr
# # ah11.text(0,34,"DHPG (100 $\mu$M)",font=fontprop,fontsize=9) # kr
# ah11.plot([0,2],[3,3],linestyle="-",marker="",linewidth=2,color="black") # ff
# ah11.text(0,3.3,"DHPG (100 $\mu$M)",font=fontprop,fontsize=9) # ff
# fontprop1 = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=7)
# ah11.legend(frameon=False,loc=1,bbox_to_anchor=(1,0.6),prop=fontprop1,labelspacing=0.06)
# fh1.tight_layout()
# # saving figures
# fh1_name = "dhpg100000nM2s_psth_ff_release.svg"
# fh1.savefig(os.path.join(figsavepath,fh1_name))
# plt.show()
# -------------------------------------------------------
