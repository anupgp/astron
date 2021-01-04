import numpy as np
np.random.seed(875431)
import pandas as pd
import os
import astron_common_functions as astronfuns
from matplotlib import pyplot as plt
import matplotlib.font_manager as font_manager
# plt.ion()
font_path = '/home/anup/.matplotlib/fonts/arial.ttf'
fontprop = font_manager.FontProperties(fname=font_path)
import h5py

dir1 = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/cacyt10to1000000nM50s"
fnameh5py = "cacyt10to1000000nM50s_pmca_features.hdf5"
cacytsall = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"cacyts")
pmcapeak = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"pmcapeak")
pmcasteady = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"pmcasteady")

cacyts = [10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000] # cacyt/dhpg
_,icacytsall,_ = np.intersect1d(cacytsall,cacyts,return_indices=True)
ncacyts = len(cacyts)
# groups = ["ctrl","admglur","adpmca","admglurpmca"]
groups = ["ctrl","adpmca"]
ngroups = len(groups)
ntrials = 100
# ------------------------------------------------------------------------------
# plotting
# -------------
dataset = pmcasteady
lineavg = np.nanmean(dataset,axis=-1)
linesem = np.nanstd(dataset,axis=-1)/np.sqrt(ntrials)
print(lineavg)
print(linesem)
plotcolors = np.array([
    [0,0,0],
    [1,0,0],
    [0,0,1],
    [0,1,0]
])
fh1,(ah11,ah12) = plt.subplots(figsize=(4,2),dpi=600,frameon=False,ncols=2,gridspec_kw={"width_ratios":[0.6,0.4]},sharey=True)

# grouplabels = ["Control",r"$A\beta$-mGluR",r"$A\beta$-PMCA",r"$A\beta$-mGluR & PMCA"]
grouplabels = ["Control",r"$A\beta$-PMCA"]
for igroup in range(0,ngroups):
    for icacyt in range(0,ncacyts):
        ph11 = ah11.semilogx(cacyts[icacyt]/1000,lineavg[igroup,icacyt],marker='o',linestyle="-",color=plotcolors[igroup,:],markersize=4)
        # error1 = lineavg[igroup,icacyt] - linesem[igroup,icacyt]
        # error2 = lineavg[igroup,icacyt] + linesem[igroup,icacyt]
        # ah11.semilogx([cacyts[icacyt]/100,cacyts[icacyt]/1000],[error1,error2],linestyle="-",color="grey")
    # }
# }

plt.show()
