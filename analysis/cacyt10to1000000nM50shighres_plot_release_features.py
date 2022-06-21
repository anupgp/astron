import numpy as np
np.random.seed(875431)
import pandas as pd
import os
import astron_common_functions as astronfuns
import matplotlib
from matplotlib import pyplot as plt
import matplotlib.font_manager as font_manager
from matplotlib import cm
print("matplotlibrc loc: ",matplotlib.matplotlib_fname())
# plt.ion()
font_path = '/home/anup/.matplotlib/fonts/arial.ttf'
fontprop = font_manager.FontProperties(fname=font_path)
import h5py
from scipy.optimize import curve_fit

# load data
dir1 = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/cacyt10to1000000nM50shighres"
fnameh5py = "cacyt10to1000000nM50shighres_release_features.hdf5"
# ------------
ngroup = 1
ntrial = 1
cacyts = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"cacyts")*1e-3
tkr = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"tkr")*1e3
krrates = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"krrates")
tpeakkr = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"tpeakkr")*1e3
peakkr = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"peakkr")
# --------------
tff1 = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"tff1")*1e3
ffrates1 = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"ffrates1")
tpeakff1 = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"tpeakff1")*1e3
peakff1 = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"peakff1")
# -----------------
# # plot traces of release rates
# fh1,ah1 = plt.subplots(figsize=(2,2),dpi=600,frameon=False,ncols=1,gridspec_kw={"width_ratios":[1]})
# cmap = cm.get_cmap('jet',len(cacyts))
# # norm = matplotlib.colors.BoundaryNorm(np.arange(len(cacyts)+1)+0.5,len(cacyts))
# norm = matplotlib.colors.LogNorm(vmin=cacyts.min(),vmax=cacyts.max())
# sm = plt.cm.ScalarMappable(norm=norm, cmap=cmap)
# for icacyt in range(0,len(cacyts)):
#     # ah1.plot(tkr,krrates[0,0,icacyt,:],color = cmap(icacyt))
#     # ah1.plot(tpeakkr[0,0,icacyt],peakkr[0,0,icacyt],'o',markersize=2,color="grey")
#     ah1.plot(tff1,ffrates1[0,0,icacyt,:],color = cmap(icacyt))
#     ah1.plot(tpeakff1[0,0,icacyt],peakff1[0,0,icacyt],'o',markersize=2,color="grey")
# # }
# ch = fh1.colorbar(sm,ticks=cacyts)
# ch.ax.tick_params(labelsize=8)
# # ah1.text(45,40,'$Ca^{2+}(\mu M)$',rotation=90,font=fontprop,fontsize=8) # kr
# ah1.text(450,0.08,'$Ca^{2+}(\mu M)$',rotation=90,font=fontprop,fontsize=8) # ff1
# print(ch.ax.get_yticklabels)
# # --------- formating ---------
# # xticks = [0,25,50]              # kr
# xticks = [0,250,500]              # ff
# ah1.set_xlim([0,500])
# ah1.set_xticks(xticks)
# ah1.set_xticklabels(xticks,fontsize=8,font=fontprop)
# ah1.set_xlabel("Time (ms)",fontsize=8,font=fontprop,loc="center")
# # --------------------------
# # yticks = [0,60,120]             # kr
# yticks = [0,0.1,0.2]              # ff1
# ah1.set_ylim([0,0.2])           
# ah1.set_yticks(yticks)
# ah1.set_yticklabels(yticks,fontsize=8,font=fontprop)
# ah1.set_ylabel("Syt7 release rate (ves $s^{-1}$)",fontsize=8,font=fontprop)
# # fh3.tight_layout(pad=0)
# ah1.spines["right"].set_visible(False)
# ah1.spines["top"].set_visible(False)
# # ---------------------------------------------------
# # saving figures
# figsavepath = "/home/anup/goofy/data/suhitalab/astron/figures/new_2020_python/cacyt10to1000000nM50shighres"
# fh1_name = "cacyt10to1000000nM50shighres_ffrates1.svg"
# fh1.savefig(os.path.join(figsavepath,fh1_name))
# plt.show()
# ---------------------------------------
# fit peak release rates
def hill_cacyt_release(cacyt,vmax,kd,coeff):
    y = vmax*pow(cacyt,coeff)/(pow(kd,coeff)+pow(cacyt,coeff))
    return(y)
popt_kr,_ = curve_fit(hill_cacyt_release,cacyts,peakkr[0,0,:])
popt_ff1,_ = curve_fit(hill_cacyt_release,cacyts,peakff1[0,0,:])
print("kr fits: ",*popt_kr)
print("ff1 fits: ",*popt_ff1)
peakfit_kr = hill_cacyt_release(cacyts,*popt_kr)
peakfit_ff1 = hill_cacyt_release(cacyts,*popt_ff1)
# --------------------
# # plot release rates with fits
# fh1,ah1 = plt.subplots(figsize=(2,2),dpi=600,frameon=False,ncols=1,gridspec_kw={"width_ratios":[1]})
# # ah1.plot(cacyts,peakfit_kr,linestyle='-',color='grey',linewidth=1)
# ah1.plot(cacyts,peakfit_ff1,linestyle='-',color='grey',linewidth=1) # ff1
# for icacyt in range(0,len(cacyts)):
#     # ah1.plot(cacyts[icacyt],peakkr[0,0,icacyt],'o',markersize=2,color="black") # kr
#     ah1.plot(cacyts[icacyt],peakff1[0,0,icacyt],'o',markersize=2,color="black") # ff1
# # }
# # --------- formating ---------
# # xticks = [0,25,50]              # kr
# xticks = [0,250,500]              # ff
# ah1.set_xlim([-10,510])
# ah1.set_xticks(xticks)
# ah1.set_xticklabels(xticks,fontsize=8,font=fontprop)
# xaxislabel = r'$Ca^{2+}$ concentration ($\mu$M)' # dk
# ah1.set_xlabel(xaxislabel,fontsize=8,font=fontprop,loc="center")
# # --------------------------
# # yticks = [0,60,120]             # kr
# yticks = [0,0.1,0.2]              # ff1
# ah1.set_ylim([-0.01,0.2])           
# ah1.set_yticks(yticks)
# ah1.set_yticklabels(yticks,fontsize=8,font=fontprop)
# ah1.set_ylabel("Syt7 peak release rate (ves $s^{-1}$)",fontsize=8,font=fontprop)
# # fh3.tight_layout(pad=0)
# ah1.spines["right"].set_visible(False)
# ah1.spines["top"].set_visible(False)
# # ---------------------------------------------------
# # saving figures
# figsavepath = "/home/anup/goofy/data/suhitalab/astron/figures/new_2020_python/cacyt10to1000000nM50shighres"
# fh1_name = "cacyt10to1000000nM50shighres_peakrates_withfit_ff1.svg"
# fh1.savefig(os.path.join(figsavepath,fh1_name))
# plt.show()
# -----------------------
# fit time-to-peak release rates
def biexp_cacyt_time2peak(cacyt,a0,a1,tau1,a2,tau2):
    y = a0 + a1*np.exp(-tau1*cacyt) + a2*np.exp(-tau2*cacyt)
    return(y)
popt_kr,_ = curve_fit(biexp_cacyt_time2peak,cacyts,tpeakkr[0,0,:])
popt_ff1,_ = curve_fit(biexp_cacyt_time2peak,cacyts[10:],tpeakff1[0,0,10:])
print("kr time-to-peak fits: ",*popt_kr)
print("ff1 time-to-peak fits: ",*popt_ff1)
time2peakfit_kr = biexp_cacyt_time2peak(cacyts,*popt_kr)
time2peakfit_ff1 = biexp_cacyt_time2peak(cacyts[10:],*popt_ff1)
# plot time to peak release rate
fh1,ah1 = plt.subplots(figsize=(2,2),dpi=600,frameon=False,ncols=1,gridspec_kw={"width_ratios":[1]})
# ah1.plot(cacyts,time2peakfit_kr,linestyle='-',color='grey',linewidth=1) # kr
ah1.plot(cacyts[10:],time2peakfit_ff1,linestyle='--',color='grey',linewidth=1) # ff1
for icacyt in range(10,len(cacyts)):
    # ah1.plot(cacyts[icacyt],tpeakkr[0,0,icacyt],'o',markersize=2,color="black") # kr
    ah1.plot(cacyts[icacyt],tpeakff1[0,0,icacyt],'o',markersize=2,color="black") # ff1
# }
# --------- formating ---------
# xticks = [0,250,500]              # kr
xticks = [0,250,500]              # ff
ah1.set_xlim([-10,510])
ah1.set_xticks(xticks)
ah1.set_xticklabels(xticks,fontsize=8,font=fontprop)
xaxislabel = r'$Ca^{2+}$ concentration ($\mu$M)' # dk
ah1.set_xlabel(xaxislabel,fontsize=8,font=fontprop,loc="center")
# --------------------------
# yticks = [2,4,6,8]             # kr
yticks = [0,100,200]              # ff1
ah1.set_ylim([0,200])           
ah1.set_yticks(yticks)
ah1.set_yticklabels(yticks,fontsize=8,font=fontprop)
ah1.set_ylabel("Syt7 time to peak (ms)",fontsize=8,font=fontprop)
# fh3.tight_layout(pad=0)
ah1.spines["right"].set_visible(False)
ah1.spines["top"].set_visible(False)
# ---------------------------------------------------
# saving figures
figsavepath = "/home/anup/goofy/data/suhitalab/astron/figures/new_2020_python/cacyt10to1000000nM50shighres"
fh1_name = "cacyt10to1000000nM50shighres_time2peak_withfit_ff1.svg"
fh1.savefig(os.path.join(figsavepath,fh1_name))
plt.show()
