import numpy as np
np.random.seed(875431)
import seaborn as sns
sns.set(font="Arial")
# sns.set(font_scale=1.4)
import pandas as pd
import os
import astron_common_functions as astronfuns
from matplotlib import pyplot as plt
from matplotlib import transforms
from mpl_toolkits.mplot3d import axes3d
import matplotlib.font_manager as font_manager
from matplotlib import cm
# plt.ion()
font_path = '/home/anup/.matplotlib/fonts/arial.ttf'
fontprop = font_manager.FontProperties(fname=font_path)
import h5py
from scipy import signal
# ------------------------------------
# sns.set_style('white', {'axes.linewidth': 0.5})
# plt.rcParams['xtick.major.size'] = 5
# plt.rcParams['xtick.major.width'] = 2
plt.rcParams['xtick.bottom'] = True
plt.rcParams['ytick.left'] = True
# -------------------------------------
# disk = "/run/media/anup/3becd611-cb79-4b80-b941-2edcc0d64cb4/"
disk = "/mnt/mount1"
folder1 = "data/"
# folder2 = "badhpgcarel/run/" # DHPG stuff
folder2 = "ap1to1000dhz30scarel/run/"
# figsavepath = "/home/anup/goofy/astron/w`riting/AD_paper/ploscompbio1.3/figures2022/dhpg0to100000nM2to120s" # DHPG stuff
figsavepath = "/home/anup/goofy/astron/writing/AD_paper/ploscompbio1.3/figures2022/ap1to1000dhz30s" # AP stuff
# -----------------
groups = ["ctrl","admglur","adpmca","admglurpmca"]
grouplabels = [r"Control",r"A$\beta$-mGluR",r"A$\beta$-PMCA",r"A$\beta$-mGluR-PMCA"]
ngroups = len(groups)
# ------------------
trial0 = 1
ntrials = 100
trials = np.sort(np.random.choice(range(trial0,ntrials+trial0),ntrials,replace=False))
# varnames=['time','n0ca_cyt','n0syt45_reltime_glu','n0syt45_vkdoc_glu','n0syt45_vfmob_glu']
timecol = "time"
cacol="n0ca_cyt"
varnames = [timecol,cacol]
# ---------------------
# DHPG stuff
# dhpgs = [0,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000] # dhpg
# ndhpgs = len(dhpgs)
# dhpg = dhpgs[24]
# stimdurs = [2,10,30,60,90,120]
# stimdur = stimdurs[1]
# tstimstart = 200
# tstimstop = tstimstart + stimdur
# tstart = tstimstart - 2
# tstop = tstimstop + 10
# --------------------
# AP stuff
allfreqs = [1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000]
# freqs = [4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000]
freq = 100
# _,ifreqs,_ = np.intersect1d(allfreqs,freqs,return_indices=True)
# nfreqs = len(freqs)
stimdur = 30
tstimstart = 200
tstimstop = tstimstart + stimdur
tstart = tstimstart - 2
tstop = tstimstop + 30
# --------------------
nresample = 500
sns.color_palette("colorblind")
# ------------------------
# for igroup in range(0,len(groups)):
for igroup in range(0,1):
    dd = []
    fh,ah = plt.subplots(figsize=(2.5,2.2),dpi=600,frameon=False,ncols=1,nrows=1) # with colorbar or y-axis label
    # fh,ah = plt.subplots(figsize=(2.3,2.2),dpi=600,frameon=False,ncols=1,nrows=1) # without colorbar
    # fh,ah = plt.subplots(figsize=(2.4,2.2),dpi=600,frameon=False,ncols=1,nrows=1) # without colorbar, with y-axis label
    # fprefix = "".join(("astrocyte_",str(stimdur),"s",str(dhpg),"nM_")) # DHPG stuff
    fprefix = "".join(("astrocyte_","ap30s",str(int(freq)),"dHz_")) # AP stuff
    for itrial in range(1,ntrials+1):
        fname = "".join((fprefix,"",groups[igroup],str(itrial),".csv")) # DHPG stuff
        fullname = os.path.join(disk,folder1,folder2,groups[igroup],fname)
        print(itrial," ",fullname)
        df = pd.read_csv(fullname,header=0,usecols=varnames)
        t = df[timecol][(df[timecol] > tstart) & (df[timecol] <= (tstop + 0.5))].to_numpy() - tstimstart
        y = df[cacol][(df[timecol] > tstart) & (df[timecol] <= (tstop + 0.5))].to_numpy() * 1e6
        y2,t2 = signal.resample(x=y,t=t,num=nresample)
        # ah.plot(t,y)
        # ah.plot(t2,y2)
        # plt.show()
        dd.append(y2[0:nresample])
        # }
    dd = np.array(dd)
    # sh = sns.heatmap(dd,cmap="hot",vmin=0,vmax=6,ax=ah,square=False,rasterized=True,xticklabels=True,yticklabels=True)
    # sh = sns.heatmap(dd,cmap="hot",vmin=0,vmax=6,ax=ah,square=False,rasterized=False,xticklabels=1,yticklabels=1)
    sh = sns.heatmap(dd,cmap="hot",vmin=0,vmax=6,ax=ah,square=False,rasterized=True)
    # ------------
    # # # formatting
    if (igroup == 3):
        cbarfontprop = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=10)
        sns.set(font_scale=0.5)
        cbar = sh.collections[0].colorbar
        cbar.set_ticks([0,3,6])
        cbar.set_ticklabels(['0', '3', '6'])
        sh.figure.axes[-1].set_ylabel(r'[$Ca^{2+}$] ($\mu$M)', font=cbarfontprop,color="black")
        sh.figure.axes[1].tick_params(axis="both", labelsize=12,color="black")
        cbar.ax.tick_params(labelsize=12,color="black")
        # cbar_axes = ax.figure.axes[-1]
        # sh.figure.axes[-1].yaxis.label.set_size(12)
        # print(sh)
        # print(dir(cbar))
        # print(help(cbar.set_ticklabels))
        # print(help(cbar.set_label))
        # print(help(cbar.set_ticks))
        # ax.tick_params(axis='both', which='major', labelsize=10)
        # input()
        # cbar.set_xticklabels(cbar.get_xmajorticklabels(), fontsize = 12)
        # cbar.set_yticklabels(cbar.get_ymajorticklabels(), fontsize = 12)

        
    if (igroup != 3):
        sh.figure.axes[-1].set_visible(False)
        # plot stim positions
        annotfontprop = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=8)
        istim0 = np.where(t2>0)[0][0]
        istim1 = np.where(t2>stimdur)[0][0]-1
        ah.plot([istim0,istim1],[ntrials+3,ntrials+3],linestyle="-",marker="",linewidth=2,color="black")
        # ah.text(istim0,ntrials+7,"DHPG (100 $\mu$M)",font=annotfontprop)
        ah.text(istim0,ntrials+7,"".join(("Glutamate stim. at ",str(int(freq/10))," Hz")),font=annotfontprop)
    # ----------------
    tticks = [0,15,30]        # 10s
    # tticks = [0,60,120]        # 120s
    xticks =  [np.where(t2<=elm)[0][-1] for elm in tticks if len(np.where(t2<=elm)[0])>0]
    xticklabels = [str(elm) for elm in tticks]
    # sh.set(xticks=xticks,xticklabels=xticklabels)
    yticks = [1,50,99]
    yticklabels = ["0","50","100"]
    print("xticks & labels: ",xticks,xticklabels)
    print("yticks & labels: ",yticks,yticklabels)
    tickfontprop = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=10)
    sh.set(yticks=yticks,yticklabels=yticklabels)
    sh.set_yticklabels(yticklabels,color="black")
    sh.invert_yaxis()
    sh.set_ylim([0,ntrials+10])
    ah.set_xticks(xticks)
    ah.set_xticklabels(xticklabels,font=tickfontprop,color="black",rotation=0)
    ah.set_yticks(yticks)
    # ah.set_yticklabels(yticklabels,font=tickfontprop)
    titlefontprop = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=12)
    # ah.set_title(grouplabels[igroup],font=titlefontprop)
    ah.figure.axes[-1].tick_params(labelsize=10,color="black")
    # --------------------
    # ah.xaxis.set_tick_params(width=10,length=10)
    # ah.yaxis.set_tick_params(width=20,length=10,color='red',direction="out")
    ah.tick_params(axis="both",direction="out",length=3,width=2,colors='k')
    # -------------------
    labelfontprop = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=12)
    xlabel = r'Time (s)'
    ah.set_xlabel(xlabel,font=labelfontprop,color="k")
    ylabel = r'#Trials'
    ah.set_ylabel(ylabel,font=labelfontprop)
    # ah.set_xlim([-5,15])
    ah.spines["right"].set_visible(False)
    ah.spines["top"].set_visible(False)
    # ah.spines["left"].set_visible(True)
    # ah.spines["bottom"].set_visible(True)

    # plot stim positions
    annotfontprop = font_manager.FontProperties(family='Arial',weight='normal',style='normal',size=8)
    istim0 = np.where(t2>0)[0][0]
    istim1 = np.where(t2>stimdur)[0][0]-1
    ah.plot([istim0,istim1],[ntrials+3,ntrials+3],linestyle="-",marker="",linewidth=2,color="black")
    # ah.text(istim0,ntrials+7,"DHPG (100 $\mu$M)",font=annotfontprop)
    # # ------------
    fh.tight_layout()
    fh_name = "".join(("ap",str(int(freq)),"dhz_",groups[igroup],".png"))
    fh.savefig(os.path.join(figsavepath,fh_name),transparent=True,dpi=600)
    fh_name = "".join(("ap",str(int(freq)),"dhz_",groups[igroup],".svg"))
    fh.savefig(os.path.join(figsavepath,fh_name),transparent=True,dpi=600)
# }

plt.show()

