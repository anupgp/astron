import numpy as np
np.random.seed(875431)
# np.set_printoptions(formatter={'float': lambda x: "{0:0.3f}".format(x)})
import statsmodels.api as sm
from statsmodels.formula.api import ols

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
h5pyfname = "ap1to1000dhz30s_cacyt_rel_synchrony.hdf5" # with noise

# dir1 = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/ap1to1000dhz30s"
# h5pyfname = "ap1to1000dhz30s0noise_cacyt_rel_synchrony.hdf5"

# dir1 = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/ap1to1000dhz30s0noise" # no noise
# h5pyfname = "ap1to1000dhz30s0noise_cacyt_rel_synchrony.hdf5" # no noise

figsavepath = "/home/anup/goofy/astron/writing/AD_paper/ploscompbio1.5/figures2022/ap1to1000dhz30s" # path to the folder where figures will be saved
# -----------------------
ntrials = 1000
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
# syn = syncacyt
syn = synrel[:,:,:,0:ntrials]
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
# fh1,(ah11,ah12) = plt.subplots(figsize=(4,2),dpi=600,frameon=False,ncols=2,gridspec_kw={"width_ratios":[1,0.7]},sharey=True)
fh1,(ah11,ah12) = plt.subplots(figsize=(4,2),dpi=600,frameon=False,ncols=2,gridspec_kw={"width_ratios":[0.6,0.4]})
fh1.subplots_adjust(left=0.13, bottom=0.2, right=0.99, top=0.85, wspace=0.2, hspace=0.2)
grouplabels = ["Control",r"$A\beta$-mGluR",r"$A\beta$-PMCA",r"$A\beta$-mGluR & PMCA"]
plotcolors = ['#000000', '#ff7f0e', '#2ca02c', '#d62728']

for igroup in range(0,ngroups):
    for ifreq in range(0,nfreqs):
        error1 = avgsynindex[igroup,ifreq]-semsynindex[igroup,ifreq]
        error2 = avgsynindex[igroup,ifreq]+semsynindex[igroup,ifreq]
        ah11.semilogx([freqs[ifreq]/10,freqs[ifreq]/10],[error1,error2],linestyle="-",color="grey")
        if (ifreq == 0):
            ph11 = ah11.semilogx(freqs[ifreq]/10,avgsynindex[igroup,ifreq],marker='o',linestyle="-",color=plotcolors[igroup],markersize=2,label=grouplabels[igroup])
        else:
            ph11 = ah11.semilogx(freqs[ifreq]/10,avgsynindex[igroup,ifreq],marker='o',linestyle="-",color=plotcolors[igroup],markersize=2)
    # }
# }

ypos1 = 0.5
ah11.plot([0.5,1],[ypos1,ypos1],linestyle="--",color="grey",linewidth=1)
ah11.plot([2,10],[ypos1,ypos1],linestyle="--",color="grey",linewidth=1)
ah11.plot([20,100],[ypos1,ypos1],linestyle="--",color="grey",linewidth=1)
ah11.text(0.55,ypos1+0.03,"Low",font=fontprop,fontsize=9)
ah11.text(3.5,ypos1+0.03,"Mid",font=fontprop,fontsize=9)
ah11.text(30,ypos1+0.03,"High",font=fontprop,fontsize=9)
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
# --------------------------------
avgsynl = syn[:,ilfreqs,:,:].mean(-3).mean(-2).mean(-1) # [igroup,ifreq,itime,iset]
avgsynm = syn[:,imfreqs,:,:].mean(-3).mean(-2).mean(-1)
avgsynh = syn[:,ihfreqs,:,:].mean(-3).mean(-2).mean(-1)
semsynl = syn[:,ilfreqs,:,:].mean(-3).mean(-2).std(-1)
semsynm = syn[:,imfreqs,:,:].mean(-3).mean(-2).std(-1)
semsynh = syn[:,ihfreqs,:,:].mean(-3).mean(-2).std(-1)
# -----------------------------------
# compute pvalues b/w groups for low, mid and high frequency bands
low = np.nanmean(syn[:,ilfreqs,:],axis=-2).mean(axis=-2)
mid = np.nanmean(syn[:,imfreqs,:],axis=-2).mean(axis=-2)
high = np.nanmean(syn[:,ihfreqs,:],axis=-2).mean(axis=-2)
# remove nan entries from the groups
low0nan = [low[elm,~np.isnan(low[elm,:])] for elm in range(low.shape[0])]
mid0nan = [mid[elm,~np.isnan(mid[elm,:])] for elm in range(mid.shape[0])]
high0nan = [high[elm,~np.isnan(high[elm,:])] for elm in range(high.shape[0])]
# --------------------------------------------
# perform two-way anova
# create dataset for two-way anova
statdf = pd.DataFrame(
    {
        "control_low":syn[0,ilfreqs,:,:].mean(-3).mean(-2).flatten(order="C"),
        "ab-mglur_low":syn[1,ilfreqs,:,:].mean(-3).mean(-2).flatten(order="C"),
        "ab-pmca_low":syn[2,ilfreqs,:,:].mean(-3).mean(-2).flatten(order="C"),
        "ab-mglur-pmca_low":syn[3,ilfreqs,:,:].mean(-3).mean(-2).flatten(order="C"),

        "control_mid":syn[0,imfreqs,:,:].mean(-3).mean(-2).flatten(order="C"),
        "ab-mglur_mid":syn[1,imfreqs,:,:].mean(-3).mean(-2).flatten(order="C"),
        "ab-pmca_mid":syn[2,imfreqs,:,:].mean(-3).mean(-2).flatten(order="C"),
        "ab-mglur-pmca_mid":syn[3,imfreqs,:,:].mean(-3).mean(-2).flatten(order="C"),

        "control_high":syn[0,ihfreqs,:,:].mean(-3).mean(-2).flatten(order="C"),
        "ab-mglur_high":syn[1,ihfreqs,:,:].mean(-3).mean(-2).flatten(order="C"),
        "ab-pmca_high":syn[2,ihfreqs,:,:].mean(-3).mean(-2).flatten(order="C"),
        "ab-mglur-pmca_high":syn[3,ihfreqs,:,:].mean(-3).mean(-2).flatten(order="C")
        })
statdf.columns = statdf.columns.str.split("_",expand=True)
print(statdf.columns)
statdf = pd.DataFrame({"syn":statdf.stack().stack()})
statdf.index.set_names(["id","freq","group"],inplace=True)
statdf = statdf.droplevel("id")
print(statdf)
print(statdf.index)
print(statdf.reset_index())
# print(pd.wide_to_long(statdf,["control","ab-mglur","ab-pmca","ab-mglur-pmca"],j="group",i=))
model_aov2w = ols('syn ~ C(group) + C(freq) + C(group):C(freq)',data=statdf.reset_index()).fit()
model_aov1w_low = ols('syn ~ C(group)',data=statdf[statdf.index.get_level_values("freq") == "low"].reset_index()).fit()
model_aov1w_mid = ols('syn ~ C(group)',data=statdf[statdf.index.get_level_values("freq") == "mid"].reset_index()).fit()
model_aov1w_high = ols('syn ~ C(group)',data=statdf[statdf.index.get_level_values("freq") == "high"].reset_index()).fit()
result_aov2w = sm.stats.anova_lm(model_aov2w,type=2)
result_aov1w_low = sm.stats.anova_lm(model_aov1w_low,type=2)
result_aov1w_mid = sm.stats.anova_lm(model_aov1w_mid,type=2)
result_aov1w_high = sm.stats.anova_lm(model_aov1w_high,type=2)
print(result_aov2w)
print(result_aov1w_low)
print(result_aov1w_mid)
print(result_aov1w_high)
print(stats.shapiro(model_aov1w_low.resid))
print(stats.shapiro(model_aov2w.resid))
meandf = statdf.groupby(["group","freq"]).apply(np.mean,axis=0)
print(stats.kruskal(
    statdf[(statdf.index.get_level_values("group")=="control") & (statdf.index.get_level_values("freq")=="high")]["syn"].values,
    statdf[(statdf.index.get_level_values("group")=="ab-mglur") & (statdf.index.get_level_values("freq")=="high")]["syn"].values,
    statdf[(statdf.index.get_level_values("group")=="ab-pmca") & (statdf.index.get_level_values("freq")=="high")]["syn"].values,
    statdf[(statdf.index.get_level_values("group")=="ab-mglur-pmca") & (statdf.index.get_level_values("freq")=="high")]["syn"].values
))
print(stats.kruskal(
    statdf[(statdf.index.get_level_values("group")=="control") & (statdf.index.get_level_values("freq")=="high")]["syn"].values,
    statdf[(statdf.index.get_level_values("group")=="ab-mglur-pmca") & (statdf.index.get_level_values("freq")=="high")]["syn"].values
    ))
# print(statdf[(statdf.index.get_level_values("group")=="control") & (statdf.index.get_level_values("freq")=="high")]["syn"].values,
#     statdf[(statdf.index.get_level_values("group")=="ab-mglur-pmca") & (statdf.index.get_level_values("freq")=="high")]["syn"].values)
# fh = plt.figure()
# ah = fh.add_subplot(111)
# ah.hist(statdf[(statdf.index.get_level_values("group")=="control") & (statdf.index.get_level_values("freq")=="mid")]["syn"].values,50)
# ah.hist(statdf[(statdf.index.get_level_values("group")=="ab-mglur") & (statdf.index.get_level_values("freq")=="mid")]["syn"].values,50)
# ah.hist(statdf[(statdf.index.get_level_values("group")=="ab-pmca") & (statdf.index.get_level_values("freq")=="mid")]["syn"].values,50)
# ah.hist(statdf[(statdf.index.get_level_values("group")=="ab-mglur-pmca") & (statdf.index.get_level_values("freq")=="mid")]["syn"].values,50)
# plt.show()
# input()
# fh=plt.figure()
# ah = fh.add_subplot(111)
# meandf.unstack().unstack().plot(kind="bar",ax=ah)
# input()
# --------------------------------------------
pvals_low = np.array([stats.ttest_ind(low0nan[elm1],low0nan[elm2])[1] for elm1 in range(len(low0nan)) for elm2 in range(len(low0nan))]).reshape(4,4)
pvals_mid = np.array([stats.ttest_ind(mid0nan[elm1],mid0nan[elm2])[1] for elm1 in range(len(mid0nan)) for elm2 in range(len(mid0nan))]).reshape(4,4)
pvals_high = np.array([stats.ttest_ind(high0nan[elm1],high0nan[elm2])[1] for elm1 in range(len(high0nan)) for elm2 in range(len(high0nan))]).reshape(4,4)

# pvals_low = np.array([stats.ttest_ind(low[elm1],low[elm2]) for elm1 in range(len(low)) for elm2 in range(len(low))])
# pvals_mid = np.array([stats.ttest_ind(mid[elm1],mid[elm2]) for elm1 in range(len(mid)) for elm2 in range(len(mid))])
# pvals_high = np.array([stats.ttest_ind(high[elm1],high[elm2]) for elm1 in range(len(high)) for elm2 in range(len(high))])

# get mean values for barplots
avg_low = np.array([np.mean(low0nan[elm]) for elm in range(len(low0nan))])
sem_low = np.array([np.std(low0nan[elm])/np.sqrt(ntrials) for elm in range(len(low0nan))])
avg_mid = np.array([np.mean(mid0nan[elm]) for elm in range(len(mid0nan))])
sem_mid = np.array([np.std(mid0nan[elm])/np.sqrt(ntrials) for elm in range(len(mid0nan))])
avg_high = np.array([np.mean(high0nan[elm]) for elm in range(len(high0nan))])
sem_high = np.array([np.std(high0nan[elm])/np.sqrt(ntrials) for elm in range(len(high0nan))])
print("pvalues_low:\n",pvals_low)
print(avg_low)
print(sem_low)
print("pvalues_mid:\n",pvals_mid)
print(avg_mid)
print(sem_mid)
print("pvalues_high:\n",pvals_high)
print(avg_high)
print(sem_high)
input()
# ======================================================
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
ah12.bar(r0,avgbars[0,:],width=barwidth,label=grouplabels[0],color=plotcolors[0])
ah12.bar(r1,avgbars[1,:],width=barwidth,label=grouplabels[1],color=plotcolors[1])
ah12.bar(r2,avgbars[2,:],width=barwidth,label=grouplabels[2],color=plotcolors[2])
ah12.bar(r3,avgbars[3,:],width=barwidth,label=grouplabels[3],color=plotcolors[3])
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
# yticks = [0,0.3,0.6]            # adjust here for y ticks
# [ah.set_ylim([-0.03,0.6]) for ah in [ah11,ah12]]
yticks = [0,0.2,0.4]            # adjust here for y ticks
[ah.set_ylim([-0.03,0.4]) for ah in [ah11,ah12]]
[ah.set_yticks(yticks) for ah in [ah11,ah12]]
[ah.spines["right"].set_visible(False) for ah in [ah11]]
[ah.spines["top"].set_visible(False) for ah in [ah11]]
[ah.set_yticklabels(yticks,fontsize=8,font=fontprop) for ah in [ah11,ah12]] 
# [ah.set_ylabel("Ca$^{2+}$ event synchrony index",fontsize=8,font=fontprop) for ah in [ah11]]
[ah.set_ylabel("Release synchrony index",fontsize=8,font=fontprop) for ah in [ah11]]
# -----------------------
fontprop1 = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=9)
lh = ah11.legend(frameon=False,loc="center",bbox_to_anchor=(0.75,0.9,0.1,0.5),prop=fontprop1,labelspacing=0.1,markerscale=0.01,mode=None,handlelength=0.5,ncol=4,columnspacing=1)
# -----------------------
xticks = [0.3,1.3,2.3]
xticklabels = ["".join((str(min(elm)),"-",str(max(elm)))) for elm in [[0.4,1],[2,10],[20,100]]]
ah12.set_xticks(xticks)
ah12.tick_params(right=False,bottom=False,top=False)
ah12.set_xticklabels(xticklabels,va="center",ha="center",fontsize=8,font=fontprop,rotation=0)
[ah.set_xlabel("Stimulation frequency (Hz)",fontsize=8,font=fontprop) for ah in [ah12]]
ah12.xaxis.set_label_coords(0.45, -0.2)
[ah.spines["right"].set_visible(False) for ah in [ah12]]
[ah.spines["top"].set_visible(False) for ah in [ah12]]
[ah.spines["bottom"].set_visible(False) for ah in [ah12]]
# -----------------------
# Synchrony colormaps
fh3,(ah31,ah32,ah33,ah34,ah35) = plt.subplots(figsize=(4,2),dpi=600,frameon=False,ncols=5,gridspec_kw={"width_ratios":[1,1,1,1,0.3]})
fh3.subplots_adjust(left=0.11, bottom=0, right=0.9, top=1, wspace=0.6, hspace=0)
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
cb.ax.set_yticklabels((0.0,0.5,1.0),fontsize=8,font=fontprop)
# cb.set_label("Ca$^{2+}$ event synchrony index",font=fontprop,fontsize=8)
cb.set_label("Release synchrony index",font=fontprop,fontsize=8)

# --------- formating ---------
# fh3.subplots_adjust(bottom=0.1,left=0.0,right=0.75,top=0.9,hspace=0.2,wspace=-0.6)
xticks = [np.where(freqs>item)[0][0] for item in np.array([4,69,999]) if len(np.where(freqs>item)[0]) > 0]
[ah.set_xlim([0,24]) for ah in [ah31,ah32,ah33,ah34]]
[ah.set_xticks(xticks) for ah in [ah31,ah32,ah33,ah34]]
[ah.set_xticklabels([0,10,100],fontsize=8,font=fontprop) for ah in [ah31,ah32,ah33,ah34]]
[ah.set_title(title,fontsize=9,font=fontprop,y=1.1) for ah,title in zip([ah31,ah32,ah33,ah34],["Control",r"$A\beta$-mGluR",r"$A\beta$-PMCA",r"           $A\beta$-mGluR & PMCA"])]
# [ah.set_xticklabels([],fontsize=8,font=fontprop) for ah in [ah32,ah33,ah34]]
# [ah.xaxis.set_visible(False) for ah in [ah32,ah33,ah34]]
[ah.set_xlabel("Stimulation frequency (Hz)",fontsize=8,font=fontprop,loc="left") for ah in [ah31]]

# --------------------------
yticks = [np.where(tbins>item)[0][0] for item in np.array([0,2.4,4.9]) if len(np.where(tbins>item)[0]) > 0] # don't adjust here
[ah.set_ylim([0,48]) for ah in [ah31,ah32,ah33,ah34]] # 
[ah.set_yticks(yticks) for ah in [ah31,ah32,ah33,ah34]]
[ah.set_yticklabels([0.0,2.5,5.0],fontsize=8,font=fontprop) for ah in [ah31,ah32,ah33,ah34]]
# [ah.set_yticklabels([],fontsize=8,font=fontprop) for ah in [ah32,ah33,ah34]]
# [ah.yaxis.set_visible(False) for ah in [ah32,ah33,ah34]]
[ah.set_ylabel("Interevent interval (s)",fontsize=8,font=fontprop) for ah in [ah31]]
# ---------------------------------------------------
# -----------------------
# draw bars for p-values
coords = {"low":{"hlines":[(0.1,0,0.2),(0.18,0,0.4),(0.25,0,0.6)],"text":[(-0.1,0.1),(0.06,0.18),(0.13,0.25)],"pval":["***","***","***"]},
          "mid":{"hlines":[(0.18,1,1.2),(0.25,1,1.4),(0.3,1,1.6)],"text":[(0.9,0.18),(1.1,0.25),(1.15,0.3)],"pval":["***","***","***"]},
          "high":{"hlines":[(0.22,2,2.2),(0.27,2,2.4),(0.33,2,2.6)],"text":[(1.9,0.22),(2.0,0.27),(2.1,0.33)],"pval":["***","***","***"]}} # release syn
# ------------
# coords = {"low":{"hlines":[(0.1,0,0.2),(0.25,0,0.4),(0.4,0,0.6)],"text":[(-0.1,0.1),(0.06,0.25),(0.13,0.4)],"pval":["***","***","***"]},
#           "mid":{"hlines":[(0.18,1,1.2),(0.25,1,1.4),(0.35,1,1.6)],"text":[(0.9,0.18),(1.0,0.25),(1.15,0.35)],"pval":["***","***","***"]},
#           "high":{"hlines":[(0.22,2,2.2),(0.3,2,2.4),(0.37,2,2.6)],"text":[(1.9,0.22),(2.0,0.3),(2.1,0.37)],"pval":["***","***","***"]}} # calcium syn
# --------------------------------------------
# draw lines for significances for low frequency
ah12.hlines(coords["low"]["hlines"][0][0],coords["low"]["hlines"][0][1],coords["low"]["hlines"][0][2],linewidth=0.5,color="k") # 
ah12.text(coords["low"]["text"][0][0],coords["low"]["text"][0][1],coords["low"]["pval"][0],fontsize=10,font=fontprop)
ah12.hlines(coords["low"]["hlines"][1][0],coords["low"]["hlines"][1][1],coords["low"]["hlines"][1][2],linewidth=0.5,color="k") # 
ah12.text(coords["low"]["text"][1][0],coords["low"]["text"][1][1],coords["low"]["pval"][1],fontsize=10,font=fontprop)
ah12.hlines(coords["low"]["hlines"][2][0],coords["low"]["hlines"][2][1],coords["low"]["hlines"][2][2],linewidth=0.5,color="k") # 
ah12.text(coords["low"]["text"][2][0],coords["low"]["text"][2][1],coords["low"]["pval"][2],fontsize=10,font=fontprop)
# draw lines for significances for mid frequency
ah12.hlines(coords["mid"]["hlines"][0][0],coords["mid"]["hlines"][0][1],coords["mid"]["hlines"][0][2],linewidth=0.5,color="k") # 
ah12.text(coords["mid"]["text"][0][0],coords["mid"]["text"][0][1],coords["mid"]["pval"][0],fontsize=10,font=fontprop)
ah12.hlines(coords["mid"]["hlines"][1][0],coords["mid"]["hlines"][1][1],coords["mid"]["hlines"][1][2],linewidth=0.5,color="k") # 
ah12.text(coords["mid"]["text"][1][0],coords["mid"]["text"][1][1],coords["mid"]["pval"][1],fontsize=10,font=fontprop)
ah12.hlines(coords["mid"]["hlines"][2][0],coords["mid"]["hlines"][2][1],coords["mid"]["hlines"][2][2],linewidth=0.5,color="k") # 
ah12.text(coords["mid"]["text"][2][0],coords["mid"]["text"][2][1],coords["mid"]["pval"][2],fontsize=10,font=fontprop)
# draw lines for significances for high frequency
ah12.hlines(coords["high"]["hlines"][0][0],coords["high"]["hlines"][0][1],coords["high"]["hlines"][0][2],linewidth=0.5,color="k") # 
ah12.text(coords["high"]["text"][0][0],coords["high"]["text"][0][1],coords["high"]["pval"][0],fontsize=10,font=fontprop)
ah12.hlines(coords["high"]["hlines"][1][0],coords["high"]["hlines"][1][1],coords["high"]["hlines"][1][2],linewidth=0.5,color="k") # 
ah12.text(coords["high"]["text"][1][0],coords["high"]["text"][1][1],coords["high"]["pval"][1],fontsize=10,font=fontprop)
ah12.hlines(coords["high"]["hlines"][2][0],coords["high"]["hlines"][2][1],coords["high"]["hlines"][2][2],linewidth=0.5,color="k") # 
ah12.text(coords["high"]["text"][2][0],coords["high"]["text"][2][1],coords["high"]["pval"][2],fontsize=10,font=fontprop)
# ---------------------------------------------
fh3.tight_layout(pad=0)
# ---------------------------------------------------
# saving figures
# fh1_name = "ap1to1000dhz30s_synchrony_cacyt_linebar.svg"
fh1_name = "ap1to1000dhz30s_synchrony_release_linebar.svg"
fh1.savefig(os.path.join(figsavepath,fh1_name),transparent=True,dpi=300)
# fh1_name = "ap1to1000dhz30s_synchrony_cacyt_linebar.png"
fh1_name = "ap1to1000dhz30s_synchrony_release_linebar.png"
fh1.savefig(os.path.join(figsavepath,fh1_name),transparent=True,dpi=300)
# fh3_name = "ap1to1000dhz30s_synchrony_cacyt_cmap.svg"
fh3_name = "ap1to1000dhz30s_synchrony_release_cmap.svg"
fh3.savefig(os.path.join(figsavepath,fh3_name),transparent=True,dpi=300)
# fh3_name = "ap1to1000dhz30s_synchrony_cacyt_cmap.png"
fh3_name = "ap1to1000dhz30s_synchrony_release_cmap.png"
fh3.savefig(os.path.join(figsavepath,fh3_name),transparent=True,dpi=300)
plt.show()
# ---------------------------------------------------
