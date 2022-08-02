import numpy as np
np.random.seed(875431)
import pandas as pd
import os
import astron_common_functions as astronfuns
import matplotlib
from matplotlib import pyplot as plt
import matplotlib.font_manager as font_manager
from scipy import stats

# plt.ion()
font_manager.findSystemFonts(fontpaths="/usr/share/fonts/", fontext='ttf')
font_manager.findfont("Arial") # Test if matplotlib can find the font
plt.rcParams['font.family'] = 'Arial'
fontprop = font_manager.FontProperties(family='Arial',weight='normal',style='normal')
# fontprop = font_manager.FontProperties(fname=font_path)
import h5py


# load previously analyzed cacyt event properties data:  oldset(matlab)
dir1 = "/home/anup/goofy/astron/cooked/new_2020_python/ap1to1000dhz30s"
fnameh5py = "ap1to1000dhz30s_cacyt_event_features.hdf5"
figsavepath = "/home/anup/goofy/astron/writing/AD_paper/ploscompbio1.5/figures2022/ap1to1000dhz30s" # path to the folder where figures will be saved
# ----------------------------
freqsall = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"freqs")
cacytrate = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"cacytrate")
cacytrt = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"cacytrt")
cacytfwhm = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"cacytfwhm")
cacyttau = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"cacyttau")
cacytpeak = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"cacytpeak")
# ----------------------------------------------------------------------------
print("freqsall: ",freqsall)
freqs = [4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000]
# freqs = [1000]
_,ifreqsall,_ = np.intersect1d(freqsall,freqs,return_indices=True)
nfreqs = len(freqs)
groups = ["ctrl","admglur","adpmca","admglurpmca"]
grouplabels = ["Control",r"$A\beta$-mGluR",r"$A\beta$-PMCA",r"$A\beta$-mGluR & PMCA"]
plotcolors = ['#000000', '#ff7f0e', '#2ca02c', '#d62728']
ngroups = len(groups)
ntrials = 1000
# ------------------------------------------------------------------------------
# select parameter for plotting and satistics
dataset = cacytpeak*1e6         # calcium peak
# dataset = cacytrate          # calcium event rate
# dataset = cacytrt*1000          # calcium event risetime
# dataset = cacyttau*1000          # calcium event decaytime
# dataset = cacytfwhm*1000          # calcium event decaytime
print(dataset)
dataset[np.where(dataset<=0)] = np.nan
# ------------------
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
# pvals_low = [(elm1,elm2) for elm1 in range(len(low0nan)) for elm2 in range(len(low0nan))]
# get mean values for barplots
avglow = np.array([np.mean(low0nan[elm]) for elm in range(len(low0nan))])
semlow = np.array([np.std(low0nan[elm])/np.sqrt(lowtrials[elm]) for elm in range(len(low0nan))])
avgmid = np.array([np.mean(mid0nan[elm]) for elm in range(len(mid0nan))])
semmid = np.array([np.std(mid0nan[elm])/np.sqrt(midtrials[elm]) for elm in range(len(mid0nan))])
avghigh = np.array([np.mean(high0nan[elm]) for elm in range(len(high0nan))])
semhigh = np.array([np.std(high0nan[elm])/np.sqrt(hightrials[elm]) for elm in range(len(high0nan))])
print(avglow,semlow,pvalslow)
print(avglow,semlow,pvalsmid)
print(avgmid,semmid,pvalshigh)
input()
# ---------------------------------------------------------
# bar graph
# fh1 = plt.figure(figsize=(1.5,2.5),dpi=600,frameon=False)
# ah1 = fh1.add_subplot(111)
fh1,ah1 = plt.subplots(figsize=(2.8,2.5),dpi=600,frameon=False,ncols=1,nrows=1) # with colorbar or y-axis label
# set width of bar
barwidth = 0.21
# Set position of bar on X axis
r0 = np.arange(3)
r1 = [x + barwidth for x in r0]
r2 = [x + barwidth for x in r1]
r3 = [x + barwidth for x in r2]
avgbars = np.concatenate((avglow[:,np.newaxis],avgmid[:,np.newaxis],avghigh[:,np.newaxis]),axis=1)
sembars = np.concatenate((semlow[:,np.newaxis],semmid[:,np.newaxis],semhigh[:,np.newaxis]),axis=1)
print(avgbars)
ah1.bar(r0,avgbars[0,:],width=barwidth,label=grouplabels[0],color=plotcolors[0])
ah1.bar(r1,avgbars[1,:],width=barwidth,label=grouplabels[1],color=plotcolors[1])
ah1.bar(r2,avgbars[2,:],width=barwidth,label=grouplabels[2],color=plotcolors[2])
ah1.bar(r3,avgbars[3,:],width=barwidth,label=grouplabels[3],color=plotcolors[3])
# ------
ah1.plot([r0,r0],[avgbars[0,:]-sembars[0,:],avgbars[0,:]+sembars[0,:]],color="grey",linewidth=1)
ah1.plot([r1,r1],[avgbars[1,:]-sembars[1,:],avgbars[1,:]+sembars[1,:]],color="grey",linewidth=1)
ah1.plot([r2,r2],[avgbars[2,:]-sembars[2,:],avgbars[2,:]+sembars[2,:]],color="grey",linewidth=1)
ah1.plot([r3,r3],[avgbars[3,:]-sembars[3,:],avgbars[3,:]+sembars[3,:]],color="grey",linewidth=1)
# -------------
ylabel = "Calcium Peak ($\mu$M)" # calcium peak
ylim = [1,6]                     # calcium peak
yticks = [1,3,5]                 # calcium peak
ah1.text(-0.03,-0.4,"Stimulation frequency (Hz)",fontsize=12,font=fontprop,rotation=0)
# -------------
# ylabel = "Calcium event rate (Hz)" # calcium rate
# ylim = [0,0.4]                     # calcium rate
# yticks = [0,0.2,0.4]                 # calcium rate
# ah1.text(-0.2,-0.1,"Stimulation frequency (Hz)",fontsize=12,font=fontprop,rotation=0) # calcium rate
# ----------------
# ylabel = "Ca$^{2+}$ event rise time (ms)" # calcium risetime
# ylabel = "Rise time (ms)" # calcium rate
# ylim = [0,200]                     # calcium risetime
# yticks = [0,100,200]                 # calcium risetime
# ah1.text(-0.2,-50,"Stimulation frequency (Hz)",fontsize=12,font=fontprop,rotation=0) # calcium risetime
# ----------------
# ylabel = "Ca$^{2+}$ event rise time (ms)" # calcium decaytime
# ylabel = "Decay time (ms)" # calcium decayttime
# ylim = [0,250]                     # calcium decaytime
# yticks = [0,125,250]                 # calcium decaytime
# ah1.text(-0.2,-60,"Stimulation frequency (Hz)",fontsize=12,font=fontprop,rotation=0) # calcium decaytime
# -----------------
# ylabel = "Ca$^{2+}$ event rise time (ms)" # calcium fwhm
# ylabel = "FWHM (ms)" # calcium fwhm
# ylim = [0,400]                     # calcium fwhm
# yticks = [0,200,400]                 # calcium fwhm
# ah1.text(-0.2,-90,"Stimulation frequency (Hz)",fontsize=12,font=fontprop,rotation=0) # calcium fwhm
# -----------------
# labelfontprop = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=12)
# tickfontprop = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=10)
xticks = [0.3,1.3,2.3]
xticklabels = ["".join((str(min(elm)),"-",str(max(elm)))) for elm in [[0.4,1],[2,10],[20,100]]]
ah1.set_xticks(xticks)
# ah1.set(xticks=xticks,xticklabels=xticklabels)
ah1.tick_params(right=False,bottom=False,top=False)
ah1.set_xticklabels(xticklabels,va="top",fontsize=10,font=fontprop,rotation=0)

ah1.spines["right"].set_visible(False)
ah1.spines["top"].set_visible(False)
ah1.spines["bottom"].set_visible(False)
yticklabels = [str(elm) for elm in yticks]
ah1.set_ylim(ylim)
ah1.set_yticks(yticks,fontsize=8,font=fontprop)
ah1.set_yticklabels(yticklabels,fontsize=10,font=fontprop)
ah1.get_yaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
ah1.set_ylabel(ylabel,fontsize=12,font=fontprop)
# --------------------------------------------
coords = {"low":{"hlines":[(2.8,0,0.2),(3.2,0,0.4),(3.6,0,0.6)],"text":[(0.015,2.77),(0.10,3.17),(0.2,3.7)],"pval":["***","***",""]},
          "mid":{"hlines":[(3.2,1,1.2),(3.7,1,1.4),(4.2,1,1.6)],"text":[(1,3.2),(1.1,3.7),(1.12,4.2)],"pval":["***","***","***"]},
          "high":{"hlines":[(4.5,2,2.2),(4.95,2,2.4),(5.4,2,2.6)],"text":[(2,4.5),(2.11,4.95),(2.2,5.4)],"pval":["***","***","***"]}} # peak

# coords = {"low":{"hlines":[(0.02,0,0.2),(0.1,0,0.4),(0.15,0,0.6)],"text":[(0.016,0.02),(0.11,0.1),(0.22,0.15)],"pval":["","***","***"]},
#           "mid":{"hlines":[(0.08,1,1.2),(0.15,1,1.4),(0.21,1,1.6)],"text":[(1,0.08),(1.1,0.15),(1.2,0.21)],"pval":["***","***","***"]},
#           "high":{"hlines":[(0.15,2,2.2),(0.27,2,2.4),(0.33,2,2.6)],"text":[(2,0.15),(2.12,0.27),(2.18,0.33)],"pval":["***","***","***"]}} # rate

# coords = {"low":{"hlines":[(100,0,0.2),(160,0,0.4),(180,0,0.6)],"text":[(0.016,100),(0.11,160),(0.22,180)],"pval":["","***","***"]},
#           "mid":{"hlines":[(110,1,1.2),(160,1,1.4),(180,1,1.6)],"text":[(1,110),(1.1,160),(1.2,180)],"pval":["","***","***"]},
#           "high":{"hlines":[(110,2,2.2),(160,2,2.4),(180,2,2.6)],"text":[(2,110),(2.12,160),(2.18,180)],"pval":["","***","***"]}} # risetime

# coords = {"low":{"hlines":[(160,0,0.2),(190,0,0.4),(220,0,0.6)],"text":[(0.016,165),(0.10,190),(0.20,220)],"pval":["","***","***"]},
#           "mid":{"hlines":[(160,1,1.2),(190,1,1.4),(220,1,1.6)],"text":[(1,165),(1.1,190),(1.15,220)],"pval":["","***","***"]},
#           "high":{"hlines":[(165,2,2.2),(190,2,2.4),(220,2,2.6)],"text":[(2,170),(2.11,190),(2.17,220)],"pval":["","***","***"]}} # decaytime

# coords = {"low":{"hlines":[(250,0,0.2),(310,0,0.4),(350,0,0.6)],"text":[(0.016,255),(0.10,310),(0.20,350)],"pval":["","***","***"]},
#           "mid":{"hlines":[(260,1,1.2),(310,1,1.4),(350,1,1.6)],"text":[(1,260),(1.1,310),(1.15,350)],"pval":["","***","***"]},
#           "high":{"hlines":[(260,2,2.2),(310,2,2.4),(350,2,2.6)],"text":[(2,260),(2.11,310),(2.17,350)],"pval":["","***","***"]}} # fwhm
# --------------------------------------------
# draw lines for significances for low frequency
ah1.hlines(coords["low"]["hlines"][0][0],coords["low"]["hlines"][0][1],coords["low"]["hlines"][0][2],linewidth=0.5,color="k") # 
ah1.text(coords["low"]["text"][0][0],coords["low"]["text"][0][1],coords["low"]["pval"][0],fontsize=10,font=fontprop)
ah1.hlines(coords["low"]["hlines"][1][0],coords["low"]["hlines"][1][1],coords["low"]["hlines"][1][2],linewidth=0.5,color="k") # 
ah1.text(coords["low"]["text"][1][0],coords["low"]["text"][1][1],coords["low"]["pval"][1],fontsize=10,font=fontprop)
# ah1.hlines(coords["low"]["hlines"][2][0],coords["low"]["hlines"][2][1],coords["low"]["hlines"][2][2],linewidth=0.5,color="k") # 
# ah1.text(coords["low"]["text"][2][0],coords["low"]["text"][2][1],coords["low"]["pval"][2],fontsize=10,font=fontprop)
# draw lines for significances for mid frequency
ah1.hlines(coords["mid"]["hlines"][0][0],coords["mid"]["hlines"][0][1],coords["mid"]["hlines"][0][2],linewidth=0.5,color="k") # 
ah1.text(coords["mid"]["text"][0][0],coords["mid"]["text"][0][1],coords["mid"]["pval"][0],fontsize=10,font=fontprop)
ah1.hlines(coords["mid"]["hlines"][1][0],coords["mid"]["hlines"][1][1],coords["mid"]["hlines"][1][2],linewidth=0.5,color="k") # 
ah1.text(coords["mid"]["text"][1][0],coords["mid"]["text"][1][1],coords["mid"]["pval"][1],fontsize=10,font=fontprop)
ah1.hlines(coords["mid"]["hlines"][2][0],coords["mid"]["hlines"][2][1],coords["mid"]["hlines"][2][2],linewidth=0.5,color="k") # 
ah1.text(coords["mid"]["text"][2][0],coords["mid"]["text"][2][1],coords["mid"]["pval"][2],fontsize=10,font=fontprop)
# draw lines for significances for high frequency
ah1.hlines(coords["high"]["hlines"][0][0],coords["high"]["hlines"][0][1],coords["high"]["hlines"][0][2],linewidth=0.5,color="k") # 
ah1.text(coords["high"]["text"][0][0],coords["high"]["text"][0][1],coords["high"]["pval"][0],fontsize=10,font=fontprop)
ah1.hlines(coords["high"]["hlines"][1][0],coords["high"]["hlines"][1][1],coords["high"]["hlines"][1][2],linewidth=0.5,color="k") # 
ah1.text(coords["high"]["text"][1][0],coords["high"]["text"][1][1],coords["high"]["pval"][1],fontsize=10,font=fontprop)
ah1.hlines(coords["high"]["hlines"][2][0],coords["high"]["hlines"][2][1],coords["high"]["hlines"][2][2],linewidth=0.5,color="k") # 
ah1.text(coords["high"]["text"][2][0],coords["high"]["text"][2][1],coords["high"]["pval"][2],fontsize=10,font=fontprop)
# ---------------------------------------------
# legends
fontprop_legend = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=8)
lh = ah1.legend(frameon=False,loc="center",bbox_to_anchor=(-0.04,0.7,0.1,0.5),prop=fontprop,fontsize=4,labelspacing=0.1,markerscale=0.01,mode='expand',handlelength=0.5)
# lh = ah1.legend(frameon=False,loc="center",bbox_to_anchor=(0.25,0.8,0.1,0.5),prop=fontprop_legend,labelspacing=0.1,markerscale=0.01,handlelength=0.5)
# ---------------------------------------------
# saving figures
fh1.tight_layout()
fh1_name = "ap1to1000dhz30s_cacyt_peak_bar.svg" # calcium peak
# fh1_name = "ap1to1000dhz30s_cacyt_rate_bar.svg" # calcium rate
# fh1_name = "ap1to1000dhz30s_cacyt_risetime_bar.svg" # calcium risetime
# fh1_name = "ap1to1000dhz30s_cacyt_decaytime_bar.svg" # calcium decaytime
# fh1_name = "ap1to1000dhz30s_cacyt_fwhm_bar.svg" # calcium fwhm
fh1.savefig(os.path.join(figsavepath,fh1_name),transparent=True)
fh1_name = "ap1to1000dhz30s_cacyt_peak_bar.png" # calcium peak
# fh1_name = "ap1to1000dhz30s_cacyt_rate_bar.png" # calcium rate
# fh1_name = "ap1to1000dhz30s_cacyt_risetime_bar.png" # calcium risetime
# fh1_name = "ap1to1000dhz30s_cacyt_decaytime_bar.png" # calcium decaytime
# fh1_name = "ap1to1000dhz30s_cacyt_fwhm_bar.png" # calcium fwhm
fh1.savefig(os.path.join(figsavepath,fh1_name))
plt.show()
# ---------------------------------------------------------
# lineavg = np.nanmean(dataset,axis=-1)
# linesem = np.nanstd(dataset,axis=-1)/np.sqrt(ntrials)
# print(lineavg)
# fh1,(ah11,ah12) = plt.subplots(figsize=(4,2),dpi=600,frameon=False,ncols=2,gridspec_kw={"width_ratios":[0.6,0.4]},sharey=True)

# grouplabels = ["Control",r"$A\beta$-mGluR",r"$A\beta$-PMCA",r"$A\beta$-mGluR & PMCA"]
# for igroup in range(0,ngroups):
#     for ifreq in range(0,nfreqs):
#         ph11 = ah11.semilogx(freqs[ifreq]/10,lineavg[igroup,ifreq],marker='o',linestyle="-",color=plotcolors[igroup],markersize=4)
#         error1 = lineavg[igroup,ifreq] - linesem[igroup,ifreq]
#         error2 = lineavg[igroup,ifreq] + linesem[igroup,ifreq]
#         ah11.semilogx([freqs[ifreq]/10,freqs[ifreq]/10],[error1,error2],linestyle="-",color="grey")
#     # }
# # }
# ----------------------------
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
# ah11.text(30,5.1,"High",font=fontprop,fontsize=8)x
# tau
# ah11.plot([0.5,1],[200,200],linestyle="--",color="grey",linewidth=1)
# ah11.plot([2,10],[200,200],linestyle="--",color="grey",linewidth=1)
# ah11.plot([20,100],[200,200],linestyle="--",color="grey",linewidth=1)
# ah11.text(0.55,205,"Low",font=fontprop,fontsize=8)
# ah11.text(3.5,205,"Mid",font=fontprop,fontsize=8)
# ah11.text(30,205,"High",font=fontprop,fontsize=8)
# risetime
# ah11.plot([0.5,1],[210,210],linestyle="--",color="grey",linewidth=1)
# ah11.plot([2,10],[210,210],linestyle="--",color="grey",linewidth=1)
# ah11.plot([20,100],[210,210],linestyle="--",color="grey",linewidth=1)
# ah11.text(0.55,215,"Low",font=fontprop,fontsize=8)
# ah11.text(3.5,215,"Mid",font=fontprop,fontsize=8)
# ah11.text(30,215,"High",font=fontprop,fontsize=8)
# --------------------------------------------------------
