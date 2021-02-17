import numpy as np
np.random.seed(875431)
import pandas as pd
import os
import astron_common_functions as astronfuns
from matplotlib import pyplot as plt
import matplotlib.font_manager as font_manager
from matplotlib.transforms import Bbox
from mpl_toolkits.axes_grid1 import make_axes_locatable
import matplotlib
from mpl_toolkits.axes_grid1.inset_locator import InsetPosition
font_path = '/home/anup/.matplotlib/fonts/arial.ttf'
fontprop = font_manager.FontProperties(fname=font_path)
from matplotlib.collections import PatchCollection
from matplotlib.patches import Rectangle

# plt.ion()
import h5py


# -----------------------------
def loadh5pydata(fname,dataname):
    with h5py.File(fname,'r') as h5fp:
        print(list(h5fp.keys()))
        data = h5fp[dataname][:]
        return(data)


# --------------------------------------------------------------------------
# dir1 = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/ap1to1000dhz30s" # with noise
# h5pyfname = "ap1to1000dhz30s_cacyt_rel_synchrony.hdf5" # with noise
# dir1 = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/ap1to1000dhz30s"
# h5pyfname = "ap1to1000dhz30s0noise_cacyt_rel_synchrony.hdf5"
dir1 = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/ap1to1000dhz30s0noise" # no noise
h5pyfname = "ap1to1000dhz30s0noise_cacyt_rel_synchrony.hdf5" # no noise
# -----------------------
groups = ["ctrl","admglur","adpmca","admglurpmca"]
ngroups = len(groups)
freqs = loadh5pydata(os.path.join(dir1,h5pyfname),"freqs")
nfreqs = len(freqs)
tbins = loadh5pydata(os.path.join(dir1,h5pyfname),"tbins")
syncacyt = loadh5pydata(os.path.join(dir1,h5pyfname),"syncacyt")
synrel = loadh5pydata(os.path.join(dir1,h5pyfname),"synrel")
print(syncacyt.shape)
plottbin = 1.7
iplottbin = np.where(tbins>=plottbin)[0][0]
print("freqs: ",freqs)
print("tbins: ",tbins)
print("requested plotbin {}, obtained plotbin {}".format(plottbin, tbins[iplottbin]))
# ----------------------------------------------------------------------------
# plotting
syn = synrel
# avgsynindex = syncacyt[:,:,iplottbin,:].mean(-1) # [igroup,ifreq,tbins,iboot]
# semsynindex = syncacyt[:,:,iplottbin,:].std(-1)
avgsynindex = syn[:,:,:,:].mean(-2).mean(-1) # [igroup,ifreq,tbins,iboot]
semsynindex = syn[:,:,:,:].mean(-2).std(-1)
# avgsynindex = synrel[:,:,iplottbin,:].mean(-1)
# semsynindex = synrel[:,:,iplottbin,:].std(-1)
# avgsynindex = synrel[:,:,:,:].mean(-2).mean(-1)
# semsynindex = synrel[:,:,:,:].mean(-2).std(-1)
# ---------------------------
# Synchrony average line plot
fh1,(ah11,ah12) = plt.subplots(figsize=(4,2),dpi=600,frameon=False,ncols=2,gridspec_kw={"width_ratios":[1,0.7]},sharey=True)
# ah11 = fh1.add_subplot(111)
plotcolors = np.array([
    [0,0,0],
    [1,0,0],
    [0,0,1],
    [0,1,0]
])
grouplabels = ["Control",r"$A\beta$-mGluR",r"$A\beta$-PMCA",r"$A\beta$-mGluR & PMCA"]
for igroup in range(0,ngroups):
    for ifreq in range(0,nfreqs):
        ph11 = ah11.semilogx(freqs[ifreq]/10,avgsynindex[igroup,ifreq],marker='o',linestyle="-",color=plotcolors[igroup,:],markersize=4)
        error1 = avgsynindex[igroup,ifreq]-semsynindex[igroup,ifreq]
        error2 = avgsynindex[igroup,ifreq]+semsynindex[igroup,ifreq]
        ah11.semilogx([freqs[ifreq]/10,freqs[ifreq]/10],[error1,error2],linestyle="-",color="grey")
    # }
# }
ah11.plot([0.5,1],[-0.04,-0.04],linestyle="--",color="grey",linewidth=1)
ah11.plot([2,10],[-0.04,-0.04],linestyle="--",color="grey",linewidth=1)
ah11.plot([20,100],[-0.04,-0.04],linestyle="--",color="grey",linewidth=1)
ah11.text(0.55,-0.08,"Low",font=fontprop,fontsize=8)
ah11.text(3.5,-0.08,"Mid",font=fontprop,fontsize=8)
ah11.text(30,-0.08,"High",font=fontprop,fontsize=8)
# ------------------
# Synchrony bar graph
# fh2 = plt.figure(figsize=(1.5,2.5),dpi=600,frameon=False)
# ah21 = fh2.add_subplot(111)
lfreqs = [4,5,6,7,8,9,10]
mfreqs = [20,30,40,50,60,70,80,90,100]
hfreqs = [200,300,400,500,600,700,800,900,1000]
_,ilfreqs,_ = np.intersect1d(freqs,lfreqs,return_indices=True)
_,imfreqs,_ = np.intersect1d(freqs,mfreqs,return_indices=True)
_,ihfreqs,_ = np.intersect1d(freqs,hfreqs,return_indices=True)
avgsynl = syn[:,ilfreqs,:,:].mean(-3).mean(-2).mean(-1) # [igroup,ifreq,itime,iset]
avgsynm = syn[:,imfreqs,:,:].mean(-3).mean(-2).mean(-1)
avgsynh = syn[:,ihfreqs,:,:].mean(-3).mean(-2).mean(-1)
semsynl = syn[:,ilfreqs,:,:].mean(-3).mean(-2).std(-1)
semsynm = syn[:,imfreqs,:,:].mean(-3).mean(-2).std(-1)
semsynh = syn[:,ihfreqs,:,:].mean(-3).mean(-2).std(-1)
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
yticks = [0,0.25,0.5]            # adjust here for y ticks
[ah.set_ylim([-0.1,0.5]) for ah in [ah11]]
[ah.set_yticks(yticks) for ah in [ah11]]
[ah.spines["right"].set_visible(False) for ah in [ah11]]
[ah.spines["top"].set_visible(False) for ah in [ah11]]
[ah.set_yticklabels(yticks,fontsize=8,font=fontprop) for ah in [ah11]] 
[ah.set_ylabel("Synchrony index",fontsize=8,font=fontprop) for ah in [ah11]]
# ----------------
ah12.set_xticks([0,1.3,2.3])
ah12.tick_params(right=False,bottom=False,top=False)
ah12.set_xticklabels(["Low","Mid","High"],va="bottom",fontsize=8,font=fontprop,rotation=45)
[ah.spines["right"].set_visible(False) for ah in [ah12]]
[ah.spines["top"].set_visible(False) for ah in [ah12]]
[ah.spines["bottom"].set_visible(False) for ah in [ah12]]
# [ah.set_ylim([-0.01,0.5]) for ah in [ah12]]
# [ah.set_yticks([0,0.25,0.5]) for ah in [ah12]]
# [ah.set_yticklabels([0,0.25,0.5],fontsize=8,font=fontprop) for ah in [ah12]]
# ------------------
# Synchrony colormaps
fh3,(ah31,ah32,ah33,ah34,ah35) = plt.subplots(figsize=(4,12),dpi=600,frameon=False,ncols=5,gridspec_kw={"width_ratios":[1,1,1,1,0.3]})
fh3.subplots_adjust(hspace=0,wspace=0.5)
# ah35 = fh3.add_subplot(155,position=Bbox([[0.8,0.2],[0.83,0.7]]),frameon=False) # [[xmin,ymin],[xmax,ymax]]
# print(ah35.get_position())
# create an axes on the right side of ax. The width of cax will be 5%
# of ax and the padding between cax and ax will be fixed at 0.05 inch.
# divider = make_axes_locatable(ah34)
# cax = divider.append_axes("right", size="5%", pad=0.05)

for igroup,ah in zip(range(0,ngroups),[ah31,ah32,ah33,ah34]):
    ph = ah.imshow(syn[igroup,:,:,:].mean(-1).T,origin="lower",interpolation="nearest",cmap="hot",vmin=0,vmax=1)
# }
# add color bar
ip = InsetPosition(ah34, [1.4,0,0.3,1]) 
ah35.set_axes_locator(ip)
cb = fh3.colorbar(ph,cax=ah35,ax=[ah31,ah32,ah33,ah34],orientation="vertical",ticks=[0,0.5,1])
cb.ax.set_ylim([0,1])
cb.ax.set_yticklabels((0.0,0.5,1),fontsize=8,font=fontprop)
cb.set_label("Synchrony index",font=fontprop,fontsize=10)

# --------- formating ---------
# fh3.subplots_adjust(bottom=0.1,left=0.0,right=0.75,top=0.9,hspace=0.2,wspace=-0.6)
xticks = [np.where(freqs>item)[0][0] for item in np.array([4,69,999]) if len(np.where(freqs>item)[0]) > 0]
[ah.set_xlim([0,24]) for ah in [ah31,ah32,ah33,ah34]]
[ah.set_xticks(xticks) for ah in [ah31,ah32,ah33,ah34]]
[ah.set_xticklabels([0.5,7,100],fontsize=8,font=fontprop) for ah in [ah31]]
[ah.set_title(title,fontsize=8,font=fontprop,y=1.1) for ah,title in zip([ah31,ah32,ah33,ah34],["Control",r"$A\beta$-mGluR",r"$A\beta$-PMCA",r"           $A\beta$-mGluR-PMCA"])]
[ah.set_xticklabels([],fontsize=8,font=fontprop) for ah in [ah32,ah33,ah34]]
# [ah.xaxis.set_visible(False) for ah in [ah32,ah33,ah34]]
[ah.set_xlabel("Stimulation frequency (Hz)",fontsize=8,font=fontprop,loc="left") for ah in [ah31]]

# --------------------------
yticks = [np.where(tbins>item)[0][0] for item in np.array([0,2.4,4.9]) if len(np.where(tbins>item)[0]) > 0] # don't adjust here
[ah.set_ylim([0,48]) for ah in [ah31,ah32,ah33,ah34]] # 
[ah.set_yticks(yticks) for ah in [ah31,ah32,ah33,ah34]]
[ah.set_yticklabels([0,2.5,5],fontsize=8,font=fontprop) for ah in [ah31]]
[ah.set_yticklabels([],fontsize=8,font=fontprop) for ah in [ah32,ah33,ah34]]
# [ah.yaxis.set_visible(False) for ah in [ah32,ah33,ah34]]
[ah.set_ylabel("Interevent interval (s)",fontsize=8,font=fontprop) for ah in [ah31]]
# fh3.tight_layout(pad=0)
# ---------------------------------------------------
# saving figures
figsavepath = "/home/anup/goofy/data/suhitalab/astron/figures/new_2020_python/ap1to1000dhz30s0noise"
fh1_name = "ap1to1000dhz30s0noise_synchrony_rel_line_bar.svg"
fh1.savefig(os.path.join(figsavepath,fh1_name))

# fh2_name = "ap1to1000dhz30s_synchrony_cacyt_bars.svg"
# fh2.savefig(os.path.join(figsavepath,fh2_name))

fh3_name = "ap1to1000dhz30s0noise_synchrony_rel_cmap.svg" 
fh3.savefig(os.path.join(figsavepath,fh3_name))
# ---------------------------------------------------
plt.show()
