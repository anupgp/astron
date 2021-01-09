import numpy as np
np.random.seed(875431)
import pandas as pd
import os
import astron_common_functions as astronfuns
import matplotlib
from matplotlib import pyplot as plt
import matplotlib.font_manager as font_manager
# plt.ion()
font_path = '/home/anup/.matplotlib/fonts/arial.ttf'
fontprop = font_manager.FontProperties(fname=font_path)
import h5py


# load previously analyzed cacyt event properties data:  oldset(matlab)
dir1 = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/ap1to1000dhz30s"
fnameh5py = "ap1to1000dhz30s_cacyt_event_features.hdf5"
freqsall = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"freqs")
cacytrate = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"cacytrate")
cacytrt = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"cacytrt")
cacytfwhm = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"cacytfwhm")
cacyttau = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"cacyttau")
cacytpeak = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"cacytpeak")
# ----------------------------------------------------------------------------
freqs = [4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000]
# freqs = [1000]
_,ifreqsall,_ = np.intersect1d(freqsall,freqs,return_indices=True)
nfreqs = len(freqs)
groups = ["ctrl","admglur","adpmca","admglurpmca"]
ngroups = len(groups)
ntrials = 1000
# ------------------------------------------------------------------------------
# plotting
dataset = cacytrt*1000
print(dataset)
# -------------
lineavg = np.nanmean(dataset,axis=-1)
linesem = np.nanstd(dataset,axis=-1)/np.sqrt(ntrials)
print(lineavg)

plotcolors = np.array([
    [0,0,0],
    [1,0,0],
    [0,0,1],
    [0,1,0]
])

fh1,(ah11,ah12) = plt.subplots(figsize=(4,2),dpi=600,frameon=False,ncols=2,gridspec_kw={"width_ratios":[0.6,0.4]},sharey=True)

grouplabels = ["Control",r"$A\beta$-mGluR",r"$A\beta$-PMCA",r"$A\beta$-mGluR & PMCA"]
for igroup in range(0,ngroups):
    for ifreq in range(0,nfreqs):
        ph11 = ah11.semilogx(freqs[ifreq]/10,lineavg[igroup,ifreq],marker='o',linestyle="-",color=plotcolors[igroup,:],markersize=4)
        error1 = lineavg[igroup,ifreq] - linesem[igroup,ifreq]
        error2 = lineavg[igroup,ifreq] + linesem[igroup,ifreq]
        ah11.semilogx([freqs[ifreq]/10,freqs[ifreq]/10],[error1,error2],linestyle="-",color="grey")
    # }
# }

# cacytrate
# ah11.plot([0.4,1],[0.38,0.38],linestyle="--",color="grey",linewidth=1)
# ah11.plot([2,10],[0.38,0.38],linestyle="--",color="grey",linewidth=1)
# ah11.plot([20,100],[0.38,0.38],linestyle="--",color="grey",linewidth=1)
# ah11.text(0.5,0.41,"Low",font=fontprop,fontsize=8)
# ah11.text(3.6,0.41,"Mid",font=fontprop,fontsize=8)
# ah11.text(32,0.41,"High",font=fontprop,fontsize=8)
# fwhm
# ah11.plot([0.5,1],[205,205],linestyle="--",color="grey",linewidth=1)
# ah11.plot([2,10],[205,205],linestyle="--",color="grey",linewidth=1)
# ah11.plot([20,100],[205,205],linestyle="--",color="grey",linewidth=1)
# ah11.text(0.55,210,"Low",font=fontprop,fontsize=8)
# ah11.text(3.5,210,"Mid",font=fontprop,fontsize=8)
# ah11.text(30,210,"High",font=fontprop,fontsize=8)
# cacytpeak
# ah11.plot([0.5,1],[5,5],linestyle="--",color="grey",linewidth=1)
# ah11.plot([2,10],[5,5],linestyle="--",color="grey",linewidth=1)
# ah11.plot([20,100],[5,5],linestyle="--",color="grey",linewidth=1)
# ah11.text(0.55,5.1,"Low",font=fontprop,fontsize=8)
# ah11.text(3.5,5.1,"Mid",font=fontprop,fontsize=8)
# ah11.text(30,5.1,"High",font=fontprop,fontsize=8)
# tau
# ah11.plot([0.5,1],[200,200],linestyle="--",color="grey",linewidth=1)
# ah11.plot([2,10],[200,200],linestyle="--",color="grey",linewidth=1)
# ah11.plot([20,100],[200,200],linestyle="--",color="grey",linewidth=1)
# ah11.text(0.55,205,"Low",font=fontprop,fontsize=8)
# ah11.text(3.5,205,"Mid",font=fontprop,fontsize=8)
# ah11.text(30,205,"High",font=fontprop,fontsize=8)
# risetime
ah11.plot([0.5,1],[210,210],linestyle="--",color="grey",linewidth=1)
ah11.plot([2,10],[210,210],linestyle="--",color="grey",linewidth=1)
ah11.plot([20,100],[210,210],linestyle="--",color="grey",linewidth=1)
ah11.text(0.55,215,"Low",font=fontprop,fontsize=8)
ah11.text(3.5,215,"Mid",font=fontprop,fontsize=8)
ah11.text(30,215,"High",font=fontprop,fontsize=8)
# ------------------
# bar graph
# fh2 = plt.figure(figsize=(1.5,2.5),dpi=600,frameon=False)
# ah21 = fh2.add_subplot(111)
lfreqs = [4,5,6,7,8,9,10]
mfreqs = [20,30,40,50,60,70,80,90,100]
hfreqs = [200,300,400,500,600,700,800,900,1000]
_,ilfreqs,_ = np.intersect1d(freqs,lfreqs,return_indices=True)
_,imfreqs,_ = np.intersect1d(freqs,mfreqs,return_indices=True)
_,ihfreqs,_ = np.intersect1d(freqs,hfreqs,return_indices=True)
avgsynl = np.nanmean(np.nanmean(dataset[:,ilfreqs,:],axis=-2),axis=-1) # [igroup,ifreq,itime,iset]
avgsynm = np.nanmean(np.nanmean(dataset[:,imfreqs,:],axis=-2),axis=-1) 
avgsynh = np.nanmean(np.nanmean(dataset[:,ihfreqs,:],axis=-2),axis=-1) 
semsynl = np.nanstd(np.nanmean(dataset[:,ilfreqs,:],axis=-2),axis=-1)/np.sqrt(ntrials)
semsynm = np.nanstd(np.nanmean(dataset[:,imfreqs,:],axis=-2),axis=-1)/np.sqrt(ntrials)
semsynh = np.nanstd(np.nanmean(dataset[:,ihfreqs,:],axis=-2),axis=-1)/np.sqrt(ntrials)
# set width of bar
barwidth = 0.21
# Set position of bar on X axis
r0 = np.arange(3)
r1 = [x + barwidth for x in r0]
r2 = [x + barwidth for x in r1]
r3 = [x + barwidth for x in r2]
avgbars = np.concatenate((avgsynl[:,np.newaxis],avgsynm[:,np.newaxis],avgsynh[:,np.newaxis]),axis=1)
sembars = np.concatenate((semsynl[:,np.newaxis],semsynm[:,np.newaxis],semsynh[:,np.newaxis]),axis=1)
print(avgbars)
ah12.bar(r0,avgbars[0,:],width=barwidth,label=grouplabels[0],color=plotcolors[0,:])
ah12.bar(r1,avgbars[1,:],width=barwidth,label=grouplabels[1],color=plotcolors[1,:])
ah12.bar(r2,avgbars[2,:],width=barwidth,label=grouplabels[2],color=plotcolors[2,:])
ah12.bar(r3,avgbars[3,:],width=barwidth,label=grouplabels[3],color=plotcolors[3,:])
# ------
ah12.plot([r0,r0],[avgbars[0,:]-sembars[0,:],avgbars[0,:]+sembars[0,:]],color="grey",linewidth=1)
ah12.plot([r1,r1],[avgbars[1,:]-sembars[1,:],avgbars[1,:]+sembars[1,:]],color="grey",linewidth=1)
ah12.plot([r2,r2],[avgbars[2,:]-sembars[2,:],avgbars[2,:]+sembars[2,:]],color="grey",linewidth=1)
ah12.plot([r3,r3],[avgbars[3,:]-sembars[3,:],avgbars[3,:]+sembars[3,:]],color="grey",linewidth=1)
# --------- formating ---------
[ah.set_xlim([0.5,120]) for ah in [ah11]]
xticks = [item for item in np.array([1,10,100]) if len(np.where(freqs>item)[0]) > 0]
xticks = [1,10,100]
[ah.set_xticks(xticks) for ah in [ah11]]
[ah.set_xticklabels([1,10,100],fontsize=8,font=fontprop) for ah in [ah11]]
ah11.get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
[ah.set_xlabel("Stimulation frequency (Hz)",fontsize=8,font=fontprop) for ah in [ah11]]
# -------------
# cacytrate
# yticks = [0,0.2,0.4]
# [ah.set_ylim([-0.02,0.4]) for ah in [ah11]]
# fwhm
# yticks = [200,250,300]
# [ah.set_ylim([200,310]) for ah in [ah11]]
# [ah.set_yticks(yticks) for ah in [ah11]]
# risetime
yticks = [75,150,225]
[ah.set_ylim([75,225]) for ah in [ah11]]
[ah.set_yticks(yticks) for ah in [ah11]]
# peak
# yticks = [2,3,4,5]
# [ah.set_ylim([1.5,5]) for ah in [ah11]]
# [ah.set_yticks(yticks) for ah in [ah11]]
# tau
# yticks = [100,150,200]
# [ah.set_ylim([100,200]) for ah in [ah11]]
# [ah.set_yticks(yticks) for ah in [ah11]]
# ------------------
[ah.set_yticklabels(yticks,fontsize=8,font=fontprop) for ah in [ah11]]
[ah.spines["right"].set_visible(False) for ah in [ah11]]
[ah.spines["top"].set_visible(False) for ah in [ah11]]
[ah.set_ylabel("Rise time (20-80%)  (ms)",fontsize=8,font=fontprop) for ah in [ah11]]
# ----------------
ah12.set_xticks([0.5,1.3,2.3])
ah12.tick_params(right=False,bottom=False,top=False)
ah12.set_xticklabels(["Low","Mid","High"],va="top",fontsize=8,font=fontprop,rotation=45)
[ah.spines["right"].set_visible(False) for ah in [ah12]]
[ah.spines["top"].set_visible(False) for ah in [ah12]]
[ah.spines["bottom"].set_visible(False) for ah in [ah12]]
# [ah.set_ylim([-0.01,0.5]) for ah in [ah12]]
# [ah.set_yticks([0,0.25,0.5]) for ah in [ah12]]
# [ah.set_yticklabels([0,0.25,0.5],fontsize=8,font=fontprop) for ah in [ah12]]
# ----------------------
# saving figures
figsavepath = "/home/anup/goofy/data/suhitalab/astron/figures/new_2020_python/ap1to1000dhz30s"
fh1_name = "ap1to1000dhz30s_cacyt_risetime_line_bar.svg"
fh1.savefig(os.path.join(figsavepath,fh1_name))

plt.show()
