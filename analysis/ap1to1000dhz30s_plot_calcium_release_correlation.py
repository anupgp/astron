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
from matplotlib.collections import PatchCollection
from matplotlib.patches import Rectangle
# plt.ion()
import h5py
from scipy import stats
# --------------
font_manager.findSystemFonts(fontpaths="/usr/share/fonts/", fontext='ttf')
font_manager.findfont("Arial") # Test if matplotlib can find the font
plt.rcParams['font.family'] = 'Arial'
fontprop = font_manager.FontProperties(family='Arial',weight='normal',style='normal')

# =============================================================================
def loadh5pydata(fname,dataname):
    with h5py.File(fname,'r') as h5fp:
        print(list(h5fp.keys()))
        data = h5fp[dataname][:]
        return(data)
# --------------------------------------------------------------------------
dir1 = "/home/anup/goofy/astron/cooked/new_2020_python/ap1to1000dhz30s" # with noise
h5pyfname = "ap1to1000dhz30s_cacytrel_cross_corr.hdf5"
figsavepath = "/home/anup/goofy/astron/writing/AD_paper/ploscompbio1.3/figures2022/ap1to1000dhz30s" # path to the folder where figures will be saved
# --------------------------------------------------------------
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
# ----------------------------------------------------------------
# normalize both vdoc and vmob
vdoc = vdoc*100
# vmob = vmob/(vmob[:,:,0][:,:,np.newaxis])*100
# ---------------------------------------------------------------
avgcorr = peakcrosscorr.mean(axis=-1)[:,:]
semcorr = peakcrosscorr.std(axis=-1)[:,:] # bootstrapping std is sem
avgvdoc = vdoc.mean(axis=-1)
semvdoc = vdoc.std(axis=-1)     # bootstrapping std is sem
avgvmob = vmob.mean(axis=-1)
semvmob = vmob.std(axis=-1)     # bootstrapping std is sem
print(freqs)
print(avgcorr)
# print(semcorr)
print(avgvdoc)
# print(semvdoc)
print(avgvmob)
# print(semvmob)
# ---------------------ploting ------------------------
# plot peak-cross correlation
fh1,(ah11,ah12,ah13) = plt.subplots(figsize=(3,5),dpi=600,frameon=False,ncols=1,nrows=3,gridspec_kw={"height_ratios":[0.33,0.33,0.33],"width_ratios":[1]})
fh1.subplots_adjust(left=0.2, bottom=0.1, right=0.95, top=0.9, wspace=0, hspace=0.7)
grouplabels = ["Control",r"$A\beta$-mGluR",r"$A\beta$-PMCA",r"$A\beta$-mGluR & PMCA"]
plotcolors = ['#000000', '#ff7f0e', '#2ca02c', '#d62728']
# --------------------------
for igroup in range(0,ngroups):
    for ifreq in range(0,nfreqs):
        error1 = avgcorr[igroup,ifreq]-semcorr[igroup,ifreq]
        error2 = avgcorr[igroup,ifreq]+semcorr[igroup,ifreq]
        ah11.semilogx([freqs[ifreq]/10,freqs[ifreq]/10],[error1,error2],linestyle="-",color="grey")
        if (ifreq == 0):
            ph11 = ah11.loglog(freqs[ifreq]/10,avgcorr[igroup,ifreq],marker='o',linestyle="-",color=plotcolors[igroup],markersize=2,label=grouplabels[igroup])
        else:
            ph11 = ah11.loglog(freqs[ifreq]/10,avgcorr[igroup,ifreq],marker='o',linestyle="-",color=plotcolors[igroup],markersize=2)
    # }
# }
# -----------------------
for igroup in range(0,ngroups):
    for ifreq in range(0,nfreqs):
        error1 = avgvdoc[igroup,ifreq]-semvdoc[igroup,ifreq]
        error2 = avgvdoc[igroup,ifreq]+semvdoc[igroup,ifreq]
        ah12.semilogx([freqs[ifreq]/10,freqs[ifreq]/10],[error1,error2],linestyle="-",color="grey")
        if (ifreq == 0):
            ph12 = ah12.semilogx(freqs[ifreq]/10,avgvdoc[igroup,ifreq],marker='o',linestyle="-",color=plotcolors[igroup],markersize=2,label=grouplabels[igroup])
        else:
            ph12 = ah12.semilogx(freqs[ifreq]/10,avgvdoc[igroup,ifreq],marker='o',linestyle="-",color=plotcolors[igroup],markersize=2)
    # }
# }
# ------------------------
for igroup in range(0,ngroups):
    for ifreq in range(0,nfreqs):
        xval =  avgcorr[igroup,ifreq]
        yval =  avgvdoc[igroup,ifreq]
        xerror1 = avgcorr[igroup,ifreq]-semcorr[igroup,ifreq]
        xerror2 = avgcorr[igroup,ifreq]+semcorr[igroup,ifreq]
        yerror1 = avgvdoc[igroup,ifreq]-semvdoc[igroup,ifreq]
        yerror2 = avgvdoc[igroup,ifreq]+semvdoc[igroup,ifreq]
        ah13.semilogx([xerror1,xerror2],[yval,yval],linestyle="-",color="grey")
        ah13.semilogx([xval,xval],[yerror1,yerror2],linestyle="-",color="grey")
        if (ifreq == 0):
            ph13 = ah13.semilogx(xval,yval,marker='o',linestyle="-",color=plotcolors[igroup],markersize=2,label=grouplabels[igroup])
        else:
            ph13 = ah13.semilogx(xval,yval,marker='o',linestyle="-",color=plotcolors[igroup],markersize=2)
    # }
# }
# ------------------------
[ah.set_xlim([0.3,115]) for ah in [ah11,ah12]]        # peakcrosscorr
xticks = [1,10,100]             # peakcrosscorr
[ah.set_xticks(xticks) for ah in [ah11,ah12]]
[ah.set_xticklabels(xticks,fontsize=8,font=fontprop) for ah in [ah11,ah12]]
[ah.set_xlabel("Stimulation frequency (Hz)",fontsize=8,font=fontprop) for ah in [ah11,ah12]] # peakcrosscorr
# ah11.set_xlabel("Docked vesicles (%)",fontsize=8,font=fontprop) # vdoc

# -----------------
# ah11.get_yaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
# from matplotlib.ticker import ScalarFormatter
# ah11.yaxis.set_major_formatter(ScalarFormatter(useMathText=True,useOffset=True)) 
# # ah11.ticklabel_format(axis='y',style="sci")
ah11_yticks = [1e-4,1e-2,1e0]
ah11_ylims = [0.5e-4,1]
ah11_ylabel = "Peak cross-correlation"

ah12_yticks = [0,50,100]
ah12_ylims = [0,110]
ah12_ylabel = "% Docked vesicles"

# ---------------------
[ah.set_ylim(ylim) for ah,ylim in zip([ah11,ah12,ah13],[ah11_ylims,ah12_ylims,ah12_ylims])] 
[ah.set_yticks(yticks) for ah,yticks in zip([ah11,ah12,ah13],[ah11_yticks,ah12_yticks,ah12_yticks])] 
[ah.set_ylabel(ylabel,fontsize=8,font=fontprop) for ah,ylabel in zip([ah11,ah12,ah13],[ah11_ylabel,ah12_ylabel,ah12_ylabel])]
for label in ah11.yaxis.get_ticklabels():
    label.set_horizontalalignment('left')
ah11.yaxis.set_tick_params(pad=20)
ah11.yaxis.set_tick_params(labelsize=8)
# ------------------------
ah13.set_xlabel(ah11_ylabel,font=fontprop,fontsize=8)
# for label in ah13.yaxis.get_ticklabels():
#     label.set_horizontalalignment('left')
# ah13.yaxis.set_tick_params(pad=20)
ah13.xaxis.set_tick_params(labelsize=8)
# -----------------------
[ah.spines["right"].set_visible(False) for ah in [ah11,ah12,ah13]]
[ah.spines["top"].set_visible(False) for ah in [ah11,ah12,ah13]]
# -----------------------
fontprop1 = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=8)
lh = ah11.legend(frameon=False,loc="center",bbox_to_anchor=(0.45,0.95,0.1,0.5),prop=fontprop1,labelspacing=0.1,markerscale=0.01,mode=None,handlelength=0.5,ncol=2,columnspacing=1)
# -----------------------
# saving figures
fh1_name = "ap1to1000dhz30s_cacytrel_crosscorr.svg"
fh1.savefig(os.path.join(figsavepath,fh1_name))
fh1_name = "ap1to1000dhz30s_cacytrel_crosscorr.png"
fh1.savefig(os.path.join(figsavepath,fh1_name))
# plt.show()


