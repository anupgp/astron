import numpy as np
import pandas as pd
import os
from matplotlib import pyplot as plt


def stackplot(ah,t,y,hgap,tshift=0):
    plt.plot(t+tshift,y+hgap)
    return(ah)

diskname = "/home/anup/data/"
dir1 = "ap1to1000dhz30s0noise/run/"
# groups = ["ctrl","admglur","adpmca","admglurpmca"]
groups = ["ctrl"]
ngroups = len(groups)
allfreqs = [1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000]
# freqs = [4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000]
freqs = [1]
_,ifreqs,_ = np.intersect1d(allfreqs,freqs,return_indices=True)
nfreqs = len(freqs)
# print(nfreqs,freqs,ifreqs)
# input()
trial0 = 1
ntrials = 10
varnames=['time','n0ca_cyt','n0syt45_reltime_glu','n0syt45_vkdoc_glu','n0syt45_vfmob_glu']
timecol = "time"
cacol="n0ca_cyt"
relcol = "n0syt45_reltime_glu"
vdoccol = 'n0syt45_vkdoc_glu'
vmobcol = 'n0syt45_vfmob_glu'
trials = np.random.choice(range(trial0,ntrials+trial0),ntrials,replace=False)

fh = plt.figure(figsize=(3,3),frameon=False)
ah = fh.add_subplot(111)

hgap = 1e-09
hgaptrial = 0
tshift = 1
tshifttrial = 0

for igroup in range(0,len(groups)):
    for ifreq in range(0,len(freqs)):
        fprefix = "".join(("astrocyte_ap30s",str(freqs[ifreq]),"dHz"))
        fprefix = "".join(("astrocyte_ap",str(freqs[ifreq]),"dHz30s"))
        for itrial,ifile in zip(range(0,ntrials),trials):
            # {
            findex =  ifile
            fname = "".join((fprefix,"_",groups[igroup],str(findex),".csv"))
            fullname = os.path.join(diskname,dir1,groups[igroup],fname)
            print(findex," ",fullname)
            df = pd.read_csv(fullname,header=0,usecols=varnames)
            hgaptrial = hgaptrial + hgap
            tshifttrial = tshifttrial - tshift
            ah = stackplot(ah,df[timecol].to_numpy(),df[cacol].to_numpy(),hgaptrial,tshifttrial)
        # }
    # }
# }

# formatting
ah.axis('off')
# add scale bars
xbar = 10
xbarpos = 170
ybar = 3e-9
ybarpos = 80.5e-9
xlabel = "".join((str(xbar)," s"))
xlabelxpos = xbarpos
xlabelypos = ybarpos - ybar/3
ylabel = "".join((str(3)," nM"))
ylabelxpos = xbarpos - xbar/1.5
ylabelypos = ybarpos
ah.plot([xbarpos,xbar+xbarpos],[ybarpos,ybarpos],linestyle="-",color="k",linewidth=2)
ah.plot([xbarpos,xbarpos],[ybarpos,ybarpos+ybar],linestyle="-",color="k",linewidth=2)
ah.text(xlabelxpos,xlabelypos,xlabel,rotation = 0,fontsize = 12)
ah.text(ylabelxpos,ylabelypos,ylabel,rotation = 90,fontsize = 12)
# plt.tight_layout(pad=0)
plt.show()

# figsave
figsavepath = "/home/anup/goofy/data/suhitalab/astron/figures/new_2020_python/ap1to1000dhz30s0noise"
figname = "horizontally_stacked_cacyt_traces_ctrl.png"
fh.savefig(os.path.join(figsavepath,figname))
