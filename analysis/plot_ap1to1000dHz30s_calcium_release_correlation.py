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
dir1 = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/ap1to1000dhz30s"
h5pyfname = "ap1to1000dhz30s_cacytrel_cross_corr.hdf5"
groups = ["ctrl","admglur","adpmca","admglurpmca"]
ngroups = len(groups)
freqs = loadh5pydata(os.path.join(dir1,h5pyfname),"freqs")
binst = loadh5pydata(os.path.join(dir1,h5pyfname),"binst")
# rjpsth = loadh5pydata(os.path.join(dir1,h5pyfname),"rjpsth")
# pjpsth = loadh5pydata(os.path.join(dir1,h5pyfname),"pjpsth")
# njpsth = loadh5pydata(os.path.join(dir1,h5pyfname),"njpsth")
# rjpsthsum = rjpsth.sum(axis=2).sum(axis=2)
# pjpsth = rjpsth/rjpsthsum[:,:,np.newaxis,np.newaxis,:]
# psthca = loadh5pydata(os.path.join(dir1,h5pyfname),"psthca")
# psthrel = loadh5pydata(os.path.join(dir1,h5pyfname),"psthrel")
peakcrosscorr = loadh5pydata(os.path.join(dir1,h5pyfname),"peakcrosscorr")
vdoc = loadh5pydata(os.path.join(dir1,h5pyfname),"vdoc")
vmob = loadh5pydata(os.path.join(dir1,h5pyfname),"vmob")
nfreqs = len(freqs)

# --------------------------------------ploting ------------------------
plotcolors = np.array([
    [0,0,0],
    [1,0,0],
    [0,0,1],
    [0,1,0]
])


fh1 = plt.figure(figsize=(2.2,2),dpi=600,frameon=False)
ah11 = fh1.add_subplot(111)
# --------------------------
peakcorravg = peakcrosscorr.mean(axis=-1)
peakcorrsem = peakcrosscorr.std(axis=-1) # bootstrapping std is sem
vdocavg = vdoc.mean(axis=-1)
vdocsem = vdoc.std(axis=-1)     # bootstrapping std is sem
xavg = vdocavg*100
xsem = vdocsem*100
yavg = peakcorravg
ysem = peakcorrsem
# -----------------------
for igroup in range(0,len(groups)):
    for ifreq in range(0,len(freqs)):
        # ah11.semilogx(freqs[ifreq]/10,avg[igroup,ifreq],marker='o',linestyle="-",color=plotcolors[igroup,:],markersize=4)
        ah11.semilogy(xavg[igroup,ifreq],yavg[igroup,ifreq],marker='o',linestyle="-",color=plotcolors[igroup,:],markersize=4)
        xerror1 = xavg[igroup,ifreq] - xsem[igroup,ifreq]
        xerror2 = xavg[igroup,ifreq] + xsem[igroup,ifreq]
        yerror1 = yavg[igroup,ifreq] - ysem[igroup,ifreq]
        yerror2 = yavg[igroup,ifreq] + ysem[igroup,ifreq]
        # ah11.semilogx([freqs[ifreq]/10,freqs[ifreq]/10],[error1,error2],linestyle="-",color="grey")
        ah11.semilogy([xerror1,xerror2],[yavg[igroup,ifreq],yavg[igroup,ifreq]],linestyle="-",color="grey")
        ah11.semilogy([xavg[igroup,ifreq],xavg[igroup,ifreq]],[yerror1,yerror2],linestyle="-",color="grey")
        # }
    # }

# for igroup in range(0,len(groups)):
#     for ifreq in range(0,len(freqs)):
#         ah3.semilogy(vdocavg[igroup,ifreq],peakcorravg[igroup,ifreq],marker='o',linestyle="-",color=plotcolors[igroup,:])
#         xerror1 = vdocavg[igroup,ifreq]-vdocsem[igroup,ifreq]
#         xerror2 = vdocavg[igroup,ifreq]+vdocsem[igroup,ifreq]
#         yerror1 = peakcorravg[igroup,ifreq]-peakcorrsem[igroup,ifreq]
#         yerror2 = peakcorravg[igroup,ifreq]+peakcorrsem[igroup,ifreq]
#         ah3.semilogy([xerror1,xerror2],[peakcorravg[igroup,ifreq],peakcorravg[igroup,ifreq]],linestyle="-",color=plotcolors[igroup,:])
#         ah3.semilogy([vdocavg[igroup,ifreq],vdocavg[igroup,ifreq]],[yerror1,yerror2],linestyle="-",color=plotcolors[igroup,:])


# [ah.set_xlim([0.35,111]) for ah in [ah11]]
# xticks = [item for item in np.array([1,10,100]) if len(np.where(freqs>item)[0]) > 0]
# xticks = [1,10,100]
# [ah.set_xticks(xticks) for ah in [ah11]]
# [ah.set_xticklabels([1,10,100],fontsize=8,font=fontprop) for ah in [ah11]]
# [ah.set_xlabel("Stimulation frequency (Hz)",fontsize=8,font=fontprop) for ah in [ah11]]
# ah11.get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())

[ah.set_xlim([0,105]) for ah in [ah11]]
xticks = [0,25,50,75,100]
[ah.set_xticks(xticks) for ah in [ah11]]
[ah.set_xticklabels([0,25,50,75,100],fontsize=8,font=fontprop) for ah in [ah11]]
[ah.set_xlabel("Docked vesicles (%)",fontsize=8,font=fontprop) for ah in [ah11]]

from matplotlib.ticker import StrMethodFormatter, NullFormatter, ScalarFormatter
ah11.xaxis.set_major_formatter(StrMethodFormatter('{x:.0f}'))
ah11.xaxis.set_minor_formatter(NullFormatter())
# -------------
import matplotlib.ticker  as mtick
# ah11.yaxis.set_major_formatter(ScalarFormatter(useMathText=True))
ah11.yaxis.set_major_formatter(NullFormatter())
# ah11.yaxis.set_major_formatter(mtick.FormatStrFormatter('%0.1e'))
# ah11.ticklabel_format(style='sci',scilimits=(-5,4),axis='y',useMathText=True)
# yticks = [1e-4,1e-3,1e-2,1e-1,1]
# [ah.set_ylim([1e-4,1]) for ah in [ah11]]
# yticks = [0,25,50,75,100]
# [ah.set_ylim([0,105]) for ah in [ah11]]
# [ah.set_yticks(yticks) for ah in [ah11]]
# [ah.set_yticklabels(yticks,fontsize=8,font=fontprop) for ah in [ah11]]
# [ah.set_ylabel("Docked vesicles (%)",fontsize=8,font=fontprop) for ah in [ah11]]

# yticks = [0,25,50,75,100]
# [ah.set_ylim([0,105]) for ah in [ah11]]
# [ah.set_yticks(yticks) for ah in [ah11]]
# [ah.set_yticklabels(yticks,fontsize=8,font=fontprop) for ah in [ah11]]

yticks = [1e-4,1e-3,1e-2,1e-1,1]
[ah.set_ylim([1e-4,1]) for ah in [ah11]]
[ah.set_yticks(yticks) for ah in [ah11]]
[ah.set_yticklabels(yticks,fontsize=8,font=fontprop) for ah in [ah11]]
[ah.set_ylabel("Peak cross-correlation",fontsize=8,font=fontprop) for ah in [ah11]]

[ah.spines["right"].set_visible(False) for ah in [ah11]]
[ah.spines["top"].set_visible(False) for ah in [ah11]]


# saving figures
figsavepath = "/home/anup/goofy/data/suhitalab/astron/figures/new_2020_python/ap1to1000dhz30s"
fh1_name = "ap1to1000dhz30s_cacytrel_crosscorr_vdoc_line.svg"
fh1.savefig(os.path.join(figsavepath,fh1_name))
# ----------------
# fh2 = plt.figure()
# ah2 = fh2.add_subplot(111)
# vdocavg = vdoc.mean(axis=-1)
# vdocsem = vdoc.std(axis=-1)
# for igroup in range(0,len(groups)):
#     for ifreq in range(0,len(freqs)):
#         ah2.semilogx(freqs[ifreq]/10,vdocavg[igroup,ifreq],marker='o',linestyle="-",color=plotcolors[igroup,:])
#         error1 = vdocavg[igroup,ifreq]-vdocsem[igroup,ifreq]
#         error2 = vdocavg[igroup,ifreq]+vdocsem[igroup,ifreq]
#         ah2.semilogx([freqs[ifreq]/10,freqs[ifreq]/10],[error1,error2],linestyle="-",color=plotcolors[igroup,:])
#         # }
#     # }
    
# fh3 = plt.figure()
# ah3 = fh3.add_subplot(111)
# for igroup in range(0,len(groups)):
#     for ifreq in range(0,len(freqs)):
#         ah3.semilogy(vdocavg[igroup,ifreq],peakcorravg[igroup,ifreq],marker='o',linestyle="-",color=plotcolors[igroup,:])
#         xerror1 = vdocavg[igroup,ifreq]-vdocsem[igroup,ifreq]
#         xerror2 = vdocavg[igroup,ifreq]+vdocsem[igroup,ifreq]
#         yerror1 = peakcorravg[igroup,ifreq]-peakcorrsem[igroup,ifreq]
#         yerror2 = peakcorravg[igroup,ifreq]+peakcorrsem[igroup,ifreq]
#         ah3.semilogy([xerror1,xerror2],[peakcorravg[igroup,ifreq],peakcorravg[igroup,ifreq]],linestyle="-",color=plotcolors[igroup,:])
#         ah3.semilogy([vdocavg[igroup,ifreq],vdocavg[igroup,ifreq]],[yerror1,yerror2],linestyle="-",color=plotcolors[igroup,:])

# ------------------
# JPSTH colormaps
# fh3,(ah31,ah32,ah33,ah34,ah35) = plt.subplots(figsize=(4,12),dpi=600,frameon=False,ncols=5,gridspec_kw={"width_ratios":[1,1,1,1,0.3]})
# fh3,(ah31) = plt.subplots(figsize=(4,4),dpi=600,frameon=False,ncols=1,gridspec_kw={"width_ratios":[1]})
# fh3.subplots_adjust(hspace=0,wspace=0.5)
# ah35 = fh3.add_subplot(155,position=Bbox([[0.8,0.2],[0.83,0.7]]),frameon=False) # [[xmin,ymin],[xmax,ymax]]
# print(ah35.get_position())
# create an axes on the right side of ax. The width of cax will be 5%
# of ax and the padding between cax and ax will be fixed at 0.05 inch.
# divider = make_axes_locatable(ah34)
# cax = divider.append_axes("right", size="5%", pad=0.05)

# for igroup,ah in zip(range(1,2),[ah31]):
#     ph = ah.imshow(rjpsth[igroup,:,:,:,:].mean(0).mean(-1),origin="lower",interpolation="nearest",cmap="hot")
# }
# add color bar
# ip = InsetPosition(ah34, [1.4,0,0.3,1]) 
# ah35.set_axes_locator(ip)
# cb = fh3.colorbar(ph,cax=ah35,ax=[ah31,ah32,ah33,ah34],orientation="vertical",ticks=[0,0.3,0.7])
# cb.ax.set_ylim([0,0.7])
# cb.ax.set_yticklabels((0.0,0.3,0.7),fontsize=8,font=fontprop)
# cb.set_label("Synchrony index",font=fontprop,fontsize=10)

# # --------- formating ---------
# # fh3.subplots_adjust(bottom=0.1,left=0.0,right=0.75,top=0.9,hspace=0.2,wspace=-0.6)
# xticks = [np.where(freqs>item)[0][0] for item in np.array([4,69,999]) if len(np.where(freqs>item)[0]) > 0]
# [ah.set_xlim([0,24]) for ah in [ah31,ah32,ah33,ah34]]
# [ah.set_xticks(xticks) for ah in [ah31,ah32,ah33,ah34]]
# [ah.set_xticklabels([0.5,7,100],fontsize=8,font=fontprop) for ah in [ah31]]
# [ah.set_title(title,fontsize=8,font=fontprop,y=1.1) for ah,title in zip([ah31,ah32,ah33,ah34],["Control",r"$A\beta$-mGluR",r"$A\beta$-PMCA",r"           $A\beta$-mGluR-PMCA"])]
# [ah.set_xticklabels([],fontsize=8,font=fontprop) for ah in [ah32,ah33,ah34]]
# # [ah.xaxis.set_visible(False) for ah in [ah32,ah33,ah34]]
# [ah.set_xlabel("Stimulation frequency (Hz)",fontsize=8,font=fontprop,loc="left") for ah in [ah31]]

# # --------------------------
# yticks = [np.where(tbins>item)[0][0] for item in np.array([0,2.4,4.9]) if len(np.where(tbins>item)[0]) > 0]  
# [ah.set_ylim([0,48]) for ah in [ah31,ah32,ah33,ah34]]
# [ah.set_yticks(yticks) for ah in [ah31,ah32,ah33,ah34]]
# [ah.set_yticklabels([0,2.5,5],fontsize=8,font=fontprop) for ah in [ah31]]
# [ah.set_yticklabels([],fontsize=8,font=fontprop) for ah in [ah32,ah33,ah34]]
# # [ah.yaxis.set_visible(False) for ah in [ah32,ah33,ah34]]
# [ah.set_ylabel("Timeseries length (s)",fontsize=8,font=fontprop) for ah in [ah31]]
# # fh3.tight_layout(pad=0)
# ---------------------------------------------------

plt.show()
