import numpy as np
np.random.seed(875431)
import pandas as pd
import os
import astron_common_functions as astronfuns
from matplotlib import pyplot as plt
import matplotlib.font_manager as font_manager
# plt.ion()
import h5py
font_manager.findSystemFonts(fontpaths="/usr/share/fonts/", fontext='ttf')
font_manager.findfont("Arial") # Test if matplotlib can find the font
plt.rcParams['font.family'] = 'Arial'
fontprop = font_manager.FontProperties(family='Arial',weight='normal',style='normal')
# fontprop = font_manager.FontProperties(fname=font_path)

# ==========================================================
# load previously analyzed cacyt event properties data:  oldset(matlab)
dir1 = "/home/anup/goofy/astron/cooked/new_2020_python/ap1to1000dhz30s"
figsavepath = "/home/anup/goofy/astron/writing/AD_paper/ploscompbio1.3/figures2022/ap1to1000dhz30s" # path to the folder where figures will be saved
# --------------------------------
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
grouplabels = ["Control",r"$A\beta$-mGluR",r"$A\beta$-PMCA",r"$A\beta$-mGluR & PMCA"]
plotcolors = ['#000000', '#ff7f0e', '#2ca02c', '#d62728']
ngroups = len(groups)
ntrials = 1000
tstart = -20
tstop = 50
tstimstart = 200
tstimstop = 230
freq = 100
ifreq = np.where(np.array(freqsdmaxt)>freq)[0][0]-1
print("Selected stimulation frequency = {}".format(freqsdmaxt[ifreq]))
histdt = 0.05
binst =  np.arange(tstart,tstop,histdt) # edges: histogram counts between edges no histogram size is 1-size of bins
psthkrrel = np.zeros((ngroups,len(binst)-1),dtype=np.float16)
psthffrel = np.zeros((ngroups,len(binst)-1),dtype=np.float16)
# --------------------------------
fh1,(ah1) = plt.subplots(figsize=(4,2.1),dpi=600,frameon=False,ncols=4,nrows=2,gridspec_kw={"width_ratios":[1,1,1,1],"height_ratios":[0.2,1]})
fh1.subplots_adjust(left=0.15, bottom=0.2, right=0.95, top=0.79, wspace=0.35, hspace=0.2)
# -----------------------
ah15,ah16,ah17,ah18 = ah1[1,0],ah1[1,1],ah1[1,2],ah1[1,3]
for igroup,ah in zip(range(0,ngroups),[ah15,ah16,ah17,ah18]):
    for itrial in range(0,ntrials):
        krreltimes = dmaxtkrrel[igroup,ifreq,itrial,:]
        krreltimes = krreltimes[krreltimes>0]
        krreltimes = krreltimes - tstimstart
        histkrrel,_ = np.histogram(krreltimes,binst)
        psthkrrel[igroup,:] = psthkrrel[igroup,:] + histkrrel
        # tmin = np.min(tmin,np.min(krreltimes))
        # tmax = np.max(tmax,np.max(krreltimes))
        ffreltimes = dmaxtffrel[igroup,ifreq,itrial,:]
        ffreltimes = ffreltimes[ffreltimes>0]
        ffreltimes = ffreltimes - tstimstart
        histffrel,_ = np.histogram(ffreltimes,binst)
        psthffrel[igroup,:] = psthffrel[igroup,:] + histffrel
        # tmin = np.min(tmin,np.min(ffreltimes))
        # tmax = np.max(tmax,np.max(ffreltimes))
        # input()
        for ievent in range(0,len(krreltimes)):
            ah.plot([krreltimes[ievent],krreltimes[ievent]],np.array([0,1])+itrial,color="orange",linewidth=1)
        # }
        for ievent in range(0,len(ffreltimes)):
            ah.plot([ffreltimes[ievent],ffreltimes[ievent]],np.array([0,1])+itrial,color="green",linewidth=1)
        # }
    # }
    # ah.plot([0,0],[0,ntrials],color="grey",linestyle="--",linewidth=0.5)
    # ah.plot([30,30],[0,ntrials],color="grey",linestyle="--",linewidth=0.5)
# }
# remove y axis for all the panels except the first one
[ah.spines["left"].set_visible(False) for ah in [ah16,ah17,ah18]]
# plot histograms
ah11,ah12,ah13,ah14 = ah1[0,0],ah1[0,1],ah1[0,2],ah1[0,3]
labels = ["KR release","FF release"]
for igroup,ah in zip(range(0,ngroups),[ah11,ah12,ah13,ah14]):
    if (igroup == 0):
        ah.plot(binst[0:-1],psthffrel[igroup,:],linestyle="-",linewidth=0.5,color="green",label=labels[0])
        ah.plot(binst[0:-1],psthkrrel[igroup,:],linestyle="-",linewidth=0.5,color="orange",alpha=0.4,label=labels[1])
    else:
        ah.plot(binst[0:-1],psthffrel[igroup,:],linestyle="-",linewidth=0.5,color="green")
        ah.plot(binst[0:-1],psthkrrel[igroup,:],linestyle="-",linewidth=0.5,color="orange",alpha=0.4)
# ----------------------------
# remove y axis for all the panels except the first one
[ah.spines["left"].set_visible(False) for ah in [ah12,ah13,ah14]]
# ---------------------------
[ah.spines["right"].set_visible(False) for ah in [ah11,ah12,ah13,ah14,ah15,ah16,ah17,ah18]]
[ah.spines["top"].set_visible(False) for ah in [ah11,ah12,ah13,ah14,ah15,ah16,ah17,ah18]]

# [ah.spines["left"].set_visible(False) for ah in [ah11,ah12,ah13,ah14]]
# ------------------------------
xticks = [0,30]
[ah.set_xlim([-20,50]) for ah in [ah11,ah12,ah13,ah14,ah15,ah16,ah17,ah18]]
[ah.set_xticks(xticks) for ah in [ah11,ah12,ah13,ah14,ah15,ah16,ah17,ah18]]
[ah.set_xticklabels(xticks,fontsize=9,font=fontprop) for ah in [ah15,ah16,ah17,ah18]]
xpositions = [0.4,0.3,0.1,0.3]
ypos = 1.2
[ah.set_title(title,fontsize=9,font=fontprop,y=ypos,x=xpos,loc="center",rotation=0) for ah,title,xpos in zip([ah11,ah12,ah13,ah14],grouplabels,xpositions)]
[ah.set_xticklabels([],fontsize=9,font=fontprop) for ah in [ah11,ah12,ah13,ah14]]
# [ah.xaxis.set_visible(False) for ah in [ah32,ah33,ah34]]
[ah.set_xlabel("Time (s)",fontsize=10,font=fontprop) for ah in [ah15]]
# --------------------------
yticks1 = [0,250,500,750,1000]
[ah.set_ylim([0,ntrials]) for ah in [ah15,ah16,ah17,ah18]]
[ah.set_yticks(yticks1) for ah in [ah15,ah16,ah17,ah18]]
[ah.set_yticklabels(yticks1,fontsize=9,font=fontprop,rotation=0) for ah in [ah15, ah16,ah17,ah18]]
# [ah.set_yticklabels([],fontsize=8,font=fontprop) for ah in [ah12,ah13,ah14,ah16,ah17,ah18]]

ylim2 = [0,30]
yticks2 = [0,15,30]
[ah.set_ylim(ylim2) for ah in [ah11,ah12,ah13,ah14]]
[ah.set_yticks(yticks2) for ah in [ah11,ah12,ah13,ah14]]
[ah.set_yticklabels(yticks2,fontsize=9,font=fontprop) for ah in [ah11,ah12,ah13,ah14]]

# [ah.yaxis.set_visible(False) for ah in [ah32,ah33,ah34]]
[ah.set_ylabel("# Trials",fontsize=10,font=fontprop) for ah in [ah15]]
[ah.set_ylabel("# Events\n",fontsize=10,font=fontprop) for ah in [ah11]]
# fh1.tight_layout(pad=0)
# ---------------------------------------------------
lh = ah11.legend(frameon=False,loc="upper left",fontsize=9,labelspacing=0.1,bbox_to_anchor=(0.05,3.3,0.1,0.5),handlelength=1,ncol=2)
# # # set the linewidth of each legend object
for legobj in lh.legendHandles:
    legobj.set_linewidth(2.0)
# ------------------------------
# saving figures
fh1_name = "ap1to1000dhz30s_release_raster_plot.svg"
# fh1.savefig(os.path.join(figsavepath,fh1_name),transparent=True,dpi=300)
fh1.savefig(os.path.join(figsavepath,fh1_name))
fh1_name = "ap1to1000dhz30s_release_raster_plot.png"
fh1.savefig(os.path.join(figsavepath,fh1_name),transparent=True,dpi=300)
# plt.show()

