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



# load previously analyzed cacyt event properties data:  oldset(matlab)
dir1 = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/ap1to1000dhz30s"
# fnamemat_dmaxtrel = "frap30scarel_dmaxtrel.mat"
# fnamemat_dmaxtkrrel = "frap30scarel_dmaxtkrrel.mat"
# dmaxtrel = astronfuns.loadh5pydata(os.path.join(dir1,fnamemat_dmaxtrel),"dmaxtrel")
# dmaxtkrrel = astronfuns.loadh5pydata(os.path.join(dir1,fnamemat_dmaxtkrrel),"dmaxtrel")
fnameh5py = "ap1to1000dhz30s_cacyt_rel_kr_ff_vdoc_vmob.hdf5"
dmaxtrel = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"dmaxtrel")
dmaxtkrrel = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"dmaxtkrrel")
dmaxtffrel = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"dmaxtffrel")
# ---------------------
freqsdmaxt = [1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000]
freqs = [4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000]
_,ifreqsdmaxt,_ = np.intersect1d(freqsdmaxt,freqs,return_indices=True)
nfreqs = len(freqs)
groups = ["ctrl","admglur","adpmca","admglurpmca"]
ngroups = len(groups)
ntrials = 1000
tstimstart = 200
tstimstop = 230
relrate = np.zeros((ngroups,nfreqs,ntrials),dtype=np.float16())
krrelrate = np.zeros((ngroups,nfreqs,ntrials),dtype=np.float16())
ffrelrate = np.zeros((ngroups,nfreqs,ntrials),dtype=np.float16())
# ---------------------
for igroup in range(0,ngroups):
    for ifreq,ifreqdmaxt in zip(range(0,nfreqs),ifreqsdmaxt):
        for itrial in range(0,ntrials):
            reltimes = dmaxtrel[igroup,ifreq,itrial,:]
            reltimes = reltimes[(reltimes >= tstimstart) & (reltimes <= tstimstop)]
            relrate[igroup,ifreq,itrial]  = len(reltimes)/(tstimstop-tstimstart)
            # ----------------
            krreltimes = dmaxtkrrel[igroup,ifreq,itrial,:]
            krreltimes = krreltimes[(krreltimes >= tstimstart) & (krreltimes <= tstimstop)]
            krrelrate[igroup,ifreq,itrial]  = len(krreltimes[krreltimes>0])/(tstimstop-tstimstart)
            # ----------------
            ffreltimes = dmaxtffrel[igroup,ifreq,itrial,:]
            ffreltimes = ffreltimes[(ffreltimes >= tstimstart) & (ffreltimes <= tstimstop)]
            ffrelrate[igroup,ifreq,itrial]  = len(ffreltimes[ffreltimes>0])/(tstimstop-tstimstart)
        # }
    # }
# }
# ----------------------------------------------------------------------------
# plotting
dataset = ffrelrate
# -------------
lineavg = dataset.mean(axis=-1)
linesem = dataset.std(axis=-1)/np.sqrt(ntrials)

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

# ah11.plot([0.5,1],[0.11,0.11],linestyle="--",color="grey",linewidth=1)
# ah11.plot([2,10],[0.11,0.11],linestyle="--",color="grey",linewidth=1)
# ah11.plot([20,100],[0.11,0.11],linestyle="--",color="grey",linewidth=1)
# ah11.text(0.55,0.12,"Low",font=fontprop,fontsize=8)
# ah11.text(3.5,0.12,"Mid",font=fontprop,fontsize=8)
# ah11.text(30,0.12,"High",font=fontprop,fontsize=8)

ah11.plot([0.5,1],[0.07,0.07],linestyle="--",color="grey",linewidth=1)
ah11.plot([2,10],[0.07,0.07],linestyle="--",color="grey",linewidth=1)
ah11.plot([20,100],[0.07,0.07],linestyle="--",color="grey",linewidth=1)
ah11.text(0.55,0.075,"Low",font=fontprop,fontsize=8)
ah11.text(3.5,0.075,"Mid",font=fontprop,fontsize=8)
ah11.text(30,0.075,"High",font=fontprop,fontsize=8)
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
avgsynl = dataset[:,ilfreqs,:].mean(-2).mean(-1) # [igroup,ifreq,itime,iset]
avgsynm = dataset[:,imfreqs,:].mean(-2).mean(-1)
avgsynh = dataset[:,ihfreqs,:].mean(-2).mean(-1)
semsynl = dataset[:,ilfreqs,:].mean(-2).std(-1)/np.sqrt(ntrials)
semsynm = dataset[:,imfreqs,:].mean(-2).std(-1)/np.sqrt(ntrials)
semsynh = dataset[:,ihfreqs,:].mean(-2).std(-1)/np.sqrt(ntrials)
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
# xticks = [item for item in np.array([1,10,100]) if len(np.where(freqs>item)[0]) > 0]
xticks = [1,10,100]
[ah.set_xticks(xticks) for ah in [ah11]]
[ah.set_xticklabels([1,10,100],fontsize=8,font=fontprop) for ah in [ah11]]
# ah11.get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
[ah.set_xlabel("Stimulation frequency (Hz)",fontsize=8,font=fontprop) for ah in [ah11]]
# -------------
# yticks = [0,0.05,0.1]
# [ah.set_ylim([0.0,0.12]) for ah in [ah11]]
yticks = [0,0.04,0.08]
[ah.set_ylim([0.0,0.08]) for ah in [ah11]]
[ah.set_yticks(yticks) for ah in [ah11]]
[ah.set_yticklabels(yticks,fontsize=8,font=fontprop) for ah in [ah11]]
[ah.spines["right"].set_visible(False) for ah in [ah11]]
[ah.spines["top"].set_visible(False) for ah in [ah11]]
[ah.set_ylabel("Full fusion release rate (Hz)",fontsize=8,font=fontprop) for ah in [ah11]]
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
fh1_name = "ap1to1000dhz30s_ffrelease_line_bar.svg"
fh1.savefig(os.path.join(figsavepath,fh1_name))

plt.show()
