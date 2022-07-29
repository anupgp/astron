import numpy as np
np.random.seed(875431)
import pandas as pd
import os
import astron_common_functions as astronfuns
from matplotlib import pyplot as plt
import matplotlib.font_manager as font_manager
# plt.ion()
import h5py
from scipy import stats
# --------------
font_manager.findSystemFonts(fontpaths="/usr/share/fonts/", fontext='ttf')
font_manager.findfont("Arial") # Test if matplotlib can find the font
plt.rcParams['font.family'] = 'Arial'
fontprop = font_manager.FontProperties(family='Arial',weight='normal',style='normal')
# ---------------------------------

dir1 = "/home/anup/goofy/astron/cooked/new_2020_python/ap1to1000dhz30s"
figsavepath = "/home/anup/goofy/astron/writing/AD_paper/ploscompbio1.5/figures2022/ap1to1000dhz30s" # path to the folder where figures will be saved

# load previously analyzed cacyt event properties data:  oldset(matlab)
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
dataset = krrelrate
# dataset = ffrelrate
# dataset[np.where(dataset<=0)] = np.nan
# -------------
lineavg = dataset.mean(axis=-1)
linesem = dataset.std(axis=-1)/np.sqrt(ntrials)
# ======================================================
lfreqs = [4,5,6,7,8,9,10]
mfreqs = [20,30,40,50,60,70,80,90,100]
hfreqs = [200,300,400,500,600,700,800,900,1000]
_,ilfreqs,_ = np.intersect1d(freqs,lfreqs,return_indices=True)
_,imfreqs,_ = np.intersect1d(freqs,mfreqs,return_indices=True)
_,ihfreqs,_ = np.intersect1d(freqs,hfreqs,return_indices=True)
# compute pvalues b/w groups for low, mid and high frequency bands
low = np.nanmean(dataset[:,ilfreqs,:],axis=-2)
mid = np.nanmean(dataset[:,imfreqs,:],axis=-2)
high = np.nanmean(dataset[:,ihfreqs,:],axis=-2)
# remove nan entries from the groups
low0nan = [low[elm,~np.isnan(low[elm,:])] for elm in range(low.shape[0])]
mid0nan = [mid[elm,~np.isnan(mid[elm,:])] for elm in range(mid.shape[0])]
high0nan = [high[elm,~np.isnan(high[elm,:])] for elm in range(high.shape[0])]
pvalslow = np.array([stats.ttest_ind(low0nan[elm1],low0nan[elm2])[1] for elm1 in range(len(low0nan)) for elm2 in range(len(low0nan))]).reshape(4,4)
pvalsmid = np.array([stats.ttest_ind(mid0nan[elm1],mid0nan[elm2])[1] for elm1 in range(len(mid0nan)) for elm2 in range(len(mid0nan))]).reshape(4,4)
pvalshigh = np.array([stats.ttest_ind(high0nan[elm1],high0nan[elm2])[1] for elm1 in range(len(high0nan)) for elm2 in range(len(high0nan))]).reshape(4,4)
lowtrials = np.array([len(low0nan[elm1]) for elm1 in range(len(low0nan))])
midtrials = np.array([len(mid0nan[elm1]) for elm1 in range(len(mid0nan))])
hightrials = np.array([len(high0nan[elm1]) for elm1 in range(len(high0nan))])
print(lowtrials,midtrials,hightrials)
# get mean values for barplots
avglow = np.array([np.mean(low0nan[elm]) for elm in range(len(low0nan))])
semlow = np.array([np.std(low0nan[elm])/np.sqrt(lowtrials[elm]) for elm in range(len(low0nan))])
avgmid = np.array([np.mean(mid0nan[elm]) for elm in range(len(mid0nan))])
semmid = np.array([np.std(mid0nan[elm])/np.sqrt(midtrials[elm]) for elm in range(len(mid0nan))])
avghigh = np.array([np.mean(high0nan[elm]) for elm in range(len(high0nan))])
semhigh = np.array([np.std(high0nan[elm])/np.sqrt(hightrials[elm]) for elm in range(len(high0nan))])
avgbars = np.concatenate((avglow[:,np.newaxis],avgmid[:,np.newaxis],avghigh[:,np.newaxis]),axis=1)
sembars = np.concatenate((semlow[:,np.newaxis],semmid[:,np.newaxis],semhigh[:,np.newaxis]),axis=1)
print(avglow,semlow,pvalslow)
print(avglow,semlow,pvalsmid)
print(avgmid,semmid,pvalshigh)
print(avgbars)
print(sembars)

input()
# ======================================================
fh1,(ah11,ah12) = plt.subplots(figsize=(4,2),dpi=600,frameon=False,ncols=2,gridspec_kw={"width_ratios":[0.6,0.4]})
fh1.subplots_adjust(left=0.13, bottom=0.2, right=0.99, top=0.85, wspace=0.2, hspace=0.2)
grouplabels = ["Control",r"$A\beta$-mGluR",r"$A\beta$-PMCA",r"$A\beta$-mGluR & PMCA"]
plotcolors = ['#000000', '#ff7f0e', '#2ca02c', '#d62728']

for igroup in range(0,ngroups):
    for ifreq in range(0,nfreqs):
        error1 = lineavg[igroup,ifreq] - linesem[igroup,ifreq]
        error2 = lineavg[igroup,ifreq] + linesem[igroup,ifreq]
        ah11.semilogx([freqs[ifreq]/10,freqs[ifreq]/10],[error1,error2],linestyle="-",color="grey",linewidth=1)
        if (ifreq == 0):
            ph11 = ah11.semilogx(freqs[ifreq]/10,lineavg[igroup,ifreq],marker='o',linestyle="-",color=plotcolors[igroup],markersize=1,label=grouplabels[igroup])
        else:
            ph11 = ah11.semilogx(freqs[ifreq]/10,lineavg[igroup,ifreq],marker='o',linestyle="-",color=plotcolors[igroup],markersize=1)
    # }
# }

# ah11.plot([0.5,1],[0.11,0.11],linestyle="--",color="grey",linewidth=1)
# ah11.plot([2,10],[0.11,0.11],linestyle="--",color="grey",linewidth=1)
# ah11.plot([20,100],[0.11,0.11],linestyle="--",color="grey",linewidth=1)
# ah11.text(0.55,0.12,"Low",font=fontprop,fontsize=8)
# ah11.text(3.5,0.12,"Mid",font=fontprop,fontsize=8)
# ah11.text(30,0.12,"High",font=fontprop,fontsize=8)

ypos1 = 0.067
ah11.plot([0.5,1],[ypos1,ypos1],linestyle="--",color="grey",linewidth=1)
ah11.plot([2,10],[ypos1,ypos1],linestyle="--",color="grey",linewidth=1)
ah11.plot([20,100],[ypos1,ypos1],linestyle="--",color="grey",linewidth=1)
ah11.text(0.55,ypos1+0.005,"Low",font=fontprop,fontsize=9)
ah11.text(3.5,ypos1+0.005,"Mid",font=fontprop,fontsize=9)
ah11.text(30,ypos1+0.005,"High",font=fontprop,fontsize=9)
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
# avgbars = np.concatenate((avgsynl[:,np.newaxis],avgsynm[:,np.newaxis],avgsynh[:,np.newaxis]),axis=1)
# sembars = np.concatenate((semsynl[:,np.newaxis],semsynm[:,np.newaxis],semsynh[:,np.newaxis]),axis=1)
# print(avgbars)
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
[ah.set_xticklabels([1,10,100],fontsize=9,font=fontprop) for ah in [ah11]]
# ah11.get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
[ah.set_xlabel("Stimulation frequency (Hz)",fontsize=9,font=fontprop) for ah in [ah11]]
# -------------
yticks = [0,0.04,0.08]
[ah.set_ylim([-0.005,0.08]) for ah in [ah11,ah12]]
[ah.set_yticks(yticks) for ah in [ah11,ah12]]
[ah.set_yticklabels(yticks,fontsize=9,font=fontprop) for ah in [ah11,ah12]]
# ------------------
[ah.spines["right"].set_visible(False) for ah in [ah11]]
[ah.spines["top"].set_visible(False) for ah in [ah11]]
# [ah.spines["left"].set_visible(True) for ah in [ah12]]
# [ah.set_ylabel("Full fusion release rate (Hz)",fontsize=9,font=fontprop) for ah in [ah11]]
[ah.set_ylabel("Kiss-and-run release rate (Hz)",fontsize=9,font=fontprop) for ah in [ah11]]
# ----------------
[ah.spines["right"].set_visible(False) for ah in [ah12]]
[ah.spines["top"].set_visible(False) for ah in [ah12]]
[ah.spines["bottom"].set_visible(False) for ah in [ah12]]
# -----------------------
fontprop1 = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=9)
lh = ah11.legend(frameon=False,loc="center",bbox_to_anchor=(0.75,0.9,0.1,0.5),prop=fontprop1,labelspacing=0.1,markerscale=0.01,mode=None,handlelength=0.5,ncol=4,columnspacing=1)
# -----------------------
ah12.set_xticks([0.5,1.3,2.3])
ah12.tick_params(right=False,bottom=False,top=False)
xticks = [0.3,1.3,2.3]
xticklabels = ["".join((str(min(elm)),"-",str(max(elm)))) for elm in [[0.4,1],[2,10],[20,100]]]
ah12.set_xticks(xticks)
ah12.tick_params(right=False,bottom=False,top=False)
ah12.set_xticklabels(xticklabels,va="center",ha="center",fontsize=9,font=fontprop,rotation=0)
[ah.set_xlabel("Stimulation frequency (Hz)",fontsize=9,font=fontprop) for ah in [ah12]]
ah12.xaxis.set_label_coords(0.449, -0.2)
# -----------------------
# draw bars for p-values
# coords = {"low":{"hlines":[(0.01,0,0.2),(0.02,0,0.4),(0.03,0,0.6)],"text":[(0.016,0.01),(0.10,0.02),(0.20,0.03)],"pval":["***","***","***"]},
#           "mid":{"hlines":[(0.01,1,1.2),(0.025,1,1.4),(0.035,1,1.6)],"text":[(0.9,0.01),(1.1,0.025),(1.15,0.035)],"pval":["***","***","***"]},
#           "high":{"hlines":[(0.037,2,2.2),(0.047,2,2.4),(0.057,2,2.6)],"text":[(1.9,0.037),(2.,0.047),(2.1,0.057)],"pval":["***","***","***"]}} # ffrelease
# ------------
coords = {"low":{"hlines":[(0.015,0,0.2),(0.035,0,0.4),(0.045,0,0.6)],"text":[(-0.1,0.015),(0,0.035),(0.1,0.045)],"pval":["***","***","***"]},
          "mid":{"hlines":[(0.035,1,1.2),(0.045,1,1.4),(0.055,1,1.6)],"text":[(0.9,0.035),(1.1,0.045),(1.15,0.055)],"pval":["***","***","***"]},
          "high":{"hlines":[(0.055,2,2.2),(0.065,2,2.4),(0.075,2,2.6)],"text":[(1.9,0.055),(2.,0.065),(2.1,0.075)],"pval":["***","***","***"]}} # krrelease
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
# input()
# fh1.tight_layout(pad=0)
# saving figures
fh1_name = "ap1to1000dhz30s_krrelease_line_bar.svg"
fh1.savefig(os.path.join(figsavepath,fh1_name),transparent=True,dpi=300)
fh1_name = "ap1to1000dhz30s_krrelease_line_bar.png"
fh1.savefig(os.path.join(figsavepath,fh1_name),transparent=True,dpi=300)
# plt.show()
