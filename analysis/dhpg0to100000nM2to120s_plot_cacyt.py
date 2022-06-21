import numpy as np
np.random.seed(875431)
import pandas as pd
from scipy import signal
import os
import astron_common_functions as astronfuns
# ---------------
from matplotlib import pyplot as plt
import matplotlib.font_manager as font_manager
font_manager.findSystemFonts(fontpaths="/usr/share/fonts/", fontext='ttf')
font_manager.findfont("Arial") # Test if matplotlib can find the font
fontprop = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=12)
plt.rcParams['text.usetex'] = False
plt.rcParams['font.family'] = 'Arial'
plt.rcParams['mathtext.fontset'] = 'custom'
plt.rcParams['mathtext.fontset'] = 'custom'
plt.rcParams['mathtext.rm'] = 'Arial'
axislabelsize=10
ticklabelsize=10
legendlabelsize=10
fontprop_axislabel = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=axislabelsize)
fontprop_ticklabel = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=ticklabelsize)
fontprop_annotation = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=6)
fontprop_legend = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=legendlabelsize)
# plt.rcParams['mathtext.it'] = 'Arial'
# -------------------
import h5py
from scipy import interpolate
from scipy.optimize import curve_fit


# load data
dataloadpath = "/home/anup/goofy/astron/cooked/new_2020_python/dhpg0to100000nM2to120s"
fnameh5py = "dhpg10to100000nM2to120s_cacyt_features.hdf5"
figsavepath = "/home/anup/goofy/astron/writing/AD_paper/ploscompbio1.3/figures2022/dhpg0to100000nM2to120s" # path to the folder where figures will be saved

# ------------
groups = astronfuns.loadh5pydata(os.path.join(dataloadpath,fnameh5py),"groups")
dhpgs = np.array(astronfuns.loadh5pydata(os.path.join(dataloadpath,fnameh5py),"dhpgs"))*1e-3
stimdurs = np.array(astronfuns.loadh5pydata(os.path.join(dataloadpath,fnameh5py),"stimdurs"))
cacyt_resp = astronfuns.loadh5pydata(os.path.join(dataloadpath,fnameh5py),"cacyt_resp")
cacyt_rate = astronfuns.loadh5pydata(os.path.join(dataloadpath,fnameh5py),"cacyt_rate")
cacyt_peak = astronfuns.loadh5pydata(os.path.join(dataloadpath,fnameh5py),"cacyt_peak")*1e6
ip3cyt_max = astronfuns.loadh5pydata(os.path.join(dataloadpath,fnameh5py),"ip3cyt_max")*1e6 # ip3cyt_max
# --------------
cacyt_resting = astronfuns.loadh5pydata(os.path.join(dataloadpath,fnameh5py),"cacyt_resting")*1e9 # in nM
ip3cyt_resting = astronfuns.loadh5pydata(os.path.join(dataloadpath,fnameh5py),"ip3cyt_resting")*1e9 # in nM
caer_resting = astronfuns.loadh5pydata(os.path.join(dataloadpath,fnameh5py),"caer_resting")*1e6 # micro M
# ----------------------------------
stimdur = 60                   # 120 
print(stimdurs,stimdur)
istimdur = np.where(stimdurs >= stimdur)[0][0]
ntrials = 100
# # ----------------------------------
# plotting
dataset = cacyt_resp
lineavg = np.mean(dataset[:,:,istimdur,:],axis=1)*100 #  cacyt_resp [ngroup,ntrial,stimdurs,dhpgs]
linesem = np.std(dataset[:,:,istimdur,:],axis=1)/np.sqrt(ntrials)*100 # cacyt_resp
# lineavg = np.mean(dataset[:,:,istimdur,:],axis=1) # [ngroup,ntrial,stimdurs,dhpgs]
# linesem = np.std(dataset[:,:,istimdur,:],axis=1)/np.sqrt(ntrials)
print(lineavg,linesem)
# -------------------------------------------
# # fh1,ah11 = plt.subplots(figsize=(2,2),dpi=600,frameon=False,ncols=1,gridspec_kw={"width_ratios":[1]})
# fh1,ah11 = plt.subplots(figsize=(2.4,2.2),dpi=600,frameon=False,ncols=1,nrows=1)
# grouplabels = ["Control",r"$A\beta$-mGluR",r"$A\beta$-PMCA",r"$A\beta$-mGluR & PMCA"]
# plotcolors = ['#000000', '#ff7f0e', '#2ca02c', '#d62728']
# # ----------------------
# # Hill-equation fit
# def hill_equation(x,vmax,kd,coeff):
#     y = vmax*pow(x,coeff)/(pow(kd,coeff)+pow(x,coeff))
#     return(y)

# # popt_group0,_ = curve_fit(hill_equation,dhpgs[3:-1],lineavg[0,3:-1],p0=[1,1,1])
# # popt_group1,_ = curve_fit(hill_equation,dhpgs[3:-1],lineavg[1,3:-1],p0=[1,1,1])
# # popt_group2,_ = curve_fit(hill_equation,dhpgs[3:-1],lineavg[2,3:-1],p0=[1,1,1])
# # popt_group3,_ = curve_fit(hill_equation,dhpgs[3:-1],lineavg[3,3:-1],p0=[1,1,1])
# # popts = [popt_group0,popt_group1,popt_group2,popt_group3]
# # fits = np.array([hill_equation(dhpgs[3:-1],*popt) for popt in popts])
# # ------------------
# for igroup in range(0,len(groups)):
#     # ah11.semilogx(dhpgs[3:-1],lineavg[igroup,3:-1],linestyle="-",color=plotcolors[igroup,:])
#     for idhpg in range(3,len(dhpgs)-1):
#         error1 = lineavg[igroup,idhpg] - linesem[igroup,idhpg]
#         error2 = lineavg[igroup,idhpg] + linesem[igroup,idhpg]
#         ah11.semilogx([dhpgs[idhpg],dhpgs[idhpg]],[error1,error2],linestyle="-",color="grey")
#         if (idhpg == 3):
#             ah11.semilogx(dhpgs[idhpg],lineavg[igroup,idhpg],marker='o',linestyle="-",color=plotcolors[igroup],markersize=1,label=grouplabels[igroup])
#         else:
#             ah11.semilogx(dhpgs[idhpg],lineavg[igroup,idhpg],marker='o',linestyle="-",color=plotcolors[igroup],markersize=1)
# # formatting
# ah11.set_xlim([0.095,100])
# xticks = [0.1,1,10,100]
# ah11.set_xticks(xticks)
# ah11.set_xticklabels(xticks,fontsize=8,font=fontprop)
# # ah11.get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
# xaxislabel = r'$DHPG\ (\mu M)$' # DHPG
# ah11.set_xlabel(xaxislabel,fontsize=8,font=fontprop)
# yticks = [0,100,200,300]        # cacyt_resp
# ah11.set_ylim([-10,300])       # cacyt_resp
# # yticks = [0,0.1,0.2,0.3]          # cacyt_rate
# # ah11.set_ylim([-0.02,0.3])		  # cacyt_rate
# # yticks = [0,2,4]          # cacyt_peak
# # ah11.set_ylim([-0.5,5.2])   # cacyt_peak
# ah11.set_yticks(yticks)
# ah11.set_yticklabels(yticks,fontsize=8,font=fontprop)
# ah11.spines["right"].set_visible(False)
# ah11.spines["top"].set_visible(False)
# # matplotlib.rcParams["mathtext.sf"]
# yaxislabel = r'$Ca^{2+}$response (%)' # cacyt_response
# # yaxislabel = r'$Ca^{2+}$event rate (Hz)' # cacyt_rate
# # yaxislabel = r'$Ca^{2+}$peak ($\mu$M)' # cacyt_peak
# ah11.set_ylabel(yaxislabel,fontsize=8,font=fontprop)
# # --------------------------------
# # fontprop1 = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=8)
# # lh = ah11.legend(frameon=False,loc="center",bbox_to_anchor=(0.45,0.05,0.1,0.5),prop=fontprop1,labelspacing=0.1,markerscale=0.01,mode='expand',handlelength=0.1)
# fh1.tight_layout()
# # saving figures
# fh1_name = "dhpg0to100000nM2to120s_cacyt_resp.png"
# # fh1.savefig(os.path.join(figsavepath,fh1_name))
# plt.show()
# --------------------------------------------------------
# datasets = [cacyt_resting,ip3cyt_resting,caer_resting] # [igroup,itrial,istimdur,idhpg]
# barsavg = np.array([np.mean(dataset[:,:,istimdur,0], axis=1) for dataset in datasets])
# barssem = np.array([np.std(dataset[:,:,istimdur,0], axis=1)/np.sqrt(ntrials) for dataset in datasets])
# # print(barsavg.shape,barssem.shape)
# print(barsavg)
# print(barssem)
# # # --------------
# # fh1,ah11 = plt.subplots(figsize=(2,2),dpi=600,frameon=False,ncols=1,gridspec_kw={"width_ratios":[1]})
# fh1,ah11 = plt.subplots(figsize=(2.6,2.2),dpi=600,frameon=False,ncols=1,nrows=1)
# grouplabels = ["Control",r"$A\beta$-mGluR",r"$A\beta$-PMCA",r"$A\beta$-mGluR & PMCA"]
# plt.style.use('tableau-colorblind10')
# # cmap = 
# # plotcolors = np.array([
# #     [0,0,0],
# #     [1,0,0],
# #     [0,0,1],
# #     [0,1,0]
# # ])
# # plotcolors = ['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728']
# plotcolors = ['#000000', '#ff7f0e', '#2ca02c', '#d62728']
# # set width of bar
# barwidth = 0.21
# # Set position of bar on X axis
# r0 = np.arange(3)
# r1 = [x + barwidth for x in r0]
# r2 = [x + barwidth for x in r1]
# r3 = [x + barwidth for x in r2]
# # --------
# ph1=ah11.bar(r0,barsavg[:,0],width=barwidth,label=grouplabels[0],color=plotcolors[0])
# ph2=ah11.bar(r1,barsavg[:,1],width=barwidth,label=grouplabels[1],color=plotcolors[1])
# ph3=ah11.bar(r2,barsavg[:,2],width=barwidth,label=grouplabels[2],color=plotcolors[2])
# ph4=ah11.bar(r3,barsavg[:,3],width=barwidth,label=grouplabels[3],color=plotcolors[3])
# # ------
# ah11.plot([r0,r0],[barsavg[:,0]-barssem[:,0],barsavg[:,0]+barssem[:,0]],color="grey",linewidth=1)
# ah11.plot([r1,r1],[barsavg[:,1]-barssem[:,1],barsavg[:,1]+barssem[:,1]],color="grey",linewidth=1)
# ah11.plot([r2,r2],[barsavg[:,2]-barssem[:,2],barsavg[:,2]+barssem[:,2]],color="grey",linewidth=1)
# ah11.plot([r3,r3],[barsavg[:,3]-barssem[:,3],barsavg[:,3]+barssem[:,3]],color="grey",linewidth=1)
# # --------- formating ---------
# # print([matplotlib.colors.to_hex(ph.patches[0].get_facecolor()) for ph in [ph1,ph2,ph3,ph4]])
# # print(plt.rcParams['axes.prop_cycle'].by_key()['color'])
# # input()
# ah11.set_xticks([0.3,1.3,2.3])
# ah11.tick_params(right=False,bottom=False,top=False)
# fontprop_label = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=10)
# # ah11.set_xticklabels([r"$Ca^{2+}cytosol (nM)$",r"$IP3$(nM)",r"$Ca^{2+}$ER($\mu$M)"],va="top",font=fontprop_label,rotation=20)
# ah11.set_xticklabels(["","",""],va="top",fontsize=8,font=fontprop,rotation=0)
# ah11.spines["right"].set_visible(False)
# ah11.spines["top"].set_visible(False)
# ah11.spines["bottom"].set_visible(False)
# yticks = [0,200,400,600]          # bars
# ah11.set_ylim([0,650])   # bars
# ah11.set_yticks(yticks)
# ah11.set_yticklabels(yticks,fontsize=10,font=fontprop)
# ah11.spines["right"].set_visible(False)
# ah11.spines["top"].set_visible(False)
# # # matplotlib.rcParams["mathtext.sf"]
# yaxislabel = r'Resting concentration' # bars
# ah11.set_ylabel(yaxislabel,fontsize=10,font=fontprop)
# fontprop1 = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=9)
# lh = ah11.legend(frameon=False,loc="center",bbox_to_anchor=(-0.01,0.6,0.1,0.5),prop=fontprop1,labelspacing=0.1,markerscale=0.01,mode='expand',handlelength=0.5)
# fh1.tight_layout()
# # saving figures
# fh1_name = "dhpg0to100000nM2to120s_resting_cacyt_ip3_caer.png"
# fh1.savefig(os.path.join(figsavepath,fh1_name))
# plt.show()
# --------------------------------------------------------------
ngroups  = 2
dataset = ip3cyt_max
xvals = dhpgs[2:-1]
lineavg = np.mean(dataset[:,:,istimdur,2:-1],axis=1) #  ip3cyt_max [ngroup,ntrial,stimdurs,dhpgs]
linesem = np.std(dataset[:,:,istimdur,2:-1],axis=1)/np.sqrt(ntrials) # ip3cyt_max
# -------------------
xvals_interp = np.linspace(xvals[0],xvals[-1],5000)
ip3max_ctrl = interpolate.interp1d(xvals,lineavg[0,:])(xvals_interp)
ip3max_admglur = interpolate.interp1d(xvals,lineavg[1,:])(xvals_interp)
ip3max = np.concatenate((ip3max_ctrl[np.newaxis,:],ip3max_admglur[np.newaxis,:]),axis=0)
# ----------------------
# Hill-equation fit
def hill_equation(x,vmax,kd,coeff):
    y = vmax*pow(x,coeff)/(pow(kd,coeff)+pow(x,coeff))
    return(y)
def hill_equation2(x,top,bot,ec50,slope):
    y = (bot + ((top-bot) / (1+(pow((ec50 / x),slope)))))
    return(y)
        
popt_ctrl,_ = curve_fit(hill_equation2,xvals_interp,ip3max[0,:],p0=[0.7,4,3,3],bounds=([0,0,0,0],[50,50,50,50]))
popt_admglur,_ = curve_fit(hill_equation2,xvals_interp,ip3max[1,:],p0=[1,2,2,1],bounds=([0,0,0,0],[10,10,10,10]),method='trf')
popts = [popt_ctrl,popt_admglur]
fits = np.array([hill_equation2(xvals_interp,*popt) for popt in popts])
print(popts, fits.shape,lineavg.shape)
# ----------------------
# fh1,ah11 = plt.subplots(figsize=(2,2),dpi=600,frameon=False,ncols=1,gridspec_kw={"width_ratios":[1]})
fh1,ah11 = plt.subplots(figsize=(2.4,2.2),dpi=600,frameon=False,ncols=1,nrows=1)
# grouplabels = ["Control",r"$A\beta$-mGluR",r"$A\beta$-PMCA",r"$A\beta$-mGluR & PMCA"]
grouplabels = ["Control",r"$A\beta$-mGluR"]
plotcolors = ['#000000', '#ff7f0e']

# ---------------------
for igroup in range(0,ngroups):
    ah11.semilogx(xvals,lineavg[igroup,:],marker='o',linestyle="",color=plotcolors[igroup],markersize=3,markeredgewidth=0.5,fillstyle="none",label=grouplabels[igroup])
    ah11.semilogx(xvals_interp,fits[igroup,:],linestyle="-",color=plotcolors[igroup],linewidth=0.4) # 
    # ah11.semilogx(xvals_interp,ip3max[igroup,:],marker='',fillstyle='none',linestyle="-",color=plotcolors[igroup,:],linewidth=0.5)
    # }

# formatting
ah11.set_xlim([0.2,100])
xticks = [0.1,1.0,10,100]
ah11.set_xticks(xticks)
ah11.set_xticklabels(xticks,fontsize=ticklabelsize,font=fontprop_ticklabel)
# ah11.get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
xaxislabel = 'DHPG ($\mu$M)' # DHPG
ah11.set_xlabel(xaxislabel,font=fontprop_axislabel)
yticks = [0.0,0.5,1.0,1.5]          # cacyt_rate
ah11.set_ylim([-0.1,1.5])         # cacyt_rate
ah11.set_yticks(yticks)
ah11.set_yticklabels(yticks,fontsize=ticklabelsize,font=fontprop_ticklabel)
ah11.spines["right"].set_visible(False)
ah11.spines["top"].set_visible(False)
# matplotlib.rcParams["mathtext.sf"]
# yaxislabel = r'$Ca^{2+}$ response (%)' # cacyt_response
yaxislabel = 'Max IP$_{3}$ ($\mu$M)' # DHPG
# yaxislabel = r'$PMCA\ flux\ (\mu Ms^{-1})$' # cacyt_rate
ah11.set_ylabel(yaxislabel,fontsize=axislabelsize,font=fontprop_axislabel)
ah11.text(14,0.5,"".join(("$\it{k_d}$ = ",str(np.round(popts[0][2],1))," $\mu M$")),font=fontprop_annotation,color=plotcolors[0])
ah11.text(14,1.1,"".join(("$\it{k_d}$ = ",str(np.round(popts[1][2],1))," $\mu M$")),font=fontprop_annotation,color=plotcolors[1])
# lh = ah11.legend(frameon=False,loc="center",bbox_to_anchor=(-0.01,0.6,0.1,0.5),prop=fontprop1,labelspacing=0.1,markerscale=0.01,mode='expand',handlelength=0.5)
lh = ah11.legend(frameon=False,loc="center",bbox_to_anchor=(-0.1,0.7,0.1,0.5),prop=fontprop_legend,labelspacing=0.1,markerscale=1.5,mode='expand',handletextpad=-0.4)
fh1.tight_layout()
# saving figures
fh1_name = "cacyt10to1000000nM50s_ip3cyt_max.svg"
fh1.savefig(os.path.join(figsavepath,fh1_name))
plt.show()
