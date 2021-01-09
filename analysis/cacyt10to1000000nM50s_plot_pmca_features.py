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
from scipy import interpolate
from scipy.optimize import curve_fit

dir1 = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/cacyt10to1000000nM50s"
fnameh5py = "cacyt10to1000000nM50s_pmca_features.hdf5"
cacytsall = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"cacyts")
pmcapeak = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"pmcapeak")
pmcasteady = astronfuns.loadh5pydata(os.path.join(dir1,fnameh5py),"pmcasteady")

cacyts = np.array([10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000]) * 1e-3 # cacyt/dhpg
_,icacytsall,_ = np.intersect1d(cacytsall,cacyts,return_indices=True)
ncacyts = len(cacyts)
# groups = ["ctrl","admglur","adpmca","admglurpmca"]
groups = ["ctrl","adpmca"]
ngroups = len(groups)
ntrials = 100
# ------------------------------------------------------------------------------
# plotting
# -------------
dataset = -pmcasteady
xvals = cacyts[2:-1]
lineavg = np.mean(dataset[:,2:-1,:],axis=-1)
linesem = np.std(dataset[:,2:-1,:],axis=-1)/np.sqrt(ntrials)

xvals_interp = np.linspace(xvals[0],xvals[-1],3000)
pmcaflux_ctrl = interpolate.interp1d(xvals,lineavg[0,:])(xvals_interp)
pmcaflux_ad = interpolate.interp1d(xvals,lineavg[1,:])(xvals_interp)
pmcaflux = np.concatenate((pmcaflux_ctrl[np.newaxis,:],pmcaflux_ad[np.newaxis,:]),axis=0)

iflux0ctrl = np.where(pmcaflux_ctrl<=0)[0][0]
iflux0ad = np.where(pmcaflux_ad<=0)[0][0]
# ----------------------------------------------------------------------------
# Hill-equation fit
def hill_equation(x,vmax,kd,coeff):
    y = vmax*pow(x,coeff)/(pow(kd,coeff)+pow(x,coeff))
    return(y)
def hill_equation2(x,top,bot,ec50,slope):
    y = (bot + ((top-bot) / (1+(pow((ec50 / x),slope)))))
    return(y)
        
# popt_ctrl,_ = curve_fit(hill_equation2,xvals_interp,pmcaflux[0,:],p0=[0.7,4,3,3],bounds=([0,0,0,0],[50,50,50,50]))
# popt_admglur,_ = curve_fit(hill_equation2,xvals_interp,pmcaflux[1,:],p0=[1,2,2,1],bounds=([0,0,0,0],[10,10,10,10]),method='trf')
popt_ctrl,_ = curve_fit(hill_equation2,xvals_interp,pmcaflux[0,:],p0=[0.7,4,3,3])
popt_admglur,_ = curve_fit(hill_equation2,xvals_interp,pmcaflux[1,:],p0=[1,2,2,1])
# popt_ctrl,_ = curve_fit(hill_equation,xvals_interp,pmcaflux[0,:],p0=[0.7,4,3])
# popt_admglur,_ = curve_fit(hill_equation,xvals_interp,pmcaflux[1,:],p0=[1,2,2])
popts = [popt_ctrl,popt_admglur]
fits = np.array([hill_equation2(xvals_interp,*popt) for popt in popts])
# fits = np.array([hill_equation(xvals_interp,*popt) for popt in popts])
print(np.array(popts)*1e6)
# ----------------------------------------------------------------------------
fh1,ah11 = plt.subplots(figsize=(2,2),dpi=600,frameon=False,ncols=1,gridspec_kw={"width_ratios":[1]})
grouplabels = ["Control",r"$A\beta$-mGluR",r"$A\beta$-PMCA",r"$A\beta$-mGluR & PMCA"]
# plotcolors = np.array([
#     [0,0,0],
#     [1,0,0],
#     [0,0,1],
#     [0,1,0]
# ])

plotcolors = np.array([
    [0,0,0],
    [0,0,1]
])

# grouplabels = ["Control",r"$A\beta$-mGluR",r"$A\beta$-PMCA",r"$A\beta$-mGluR & PMCA"]
grouplabels = ["Control",r"$A\beta$-PMCA"]
for igroup in range(0,ngroups):
    ah11.semilogx(xvals,lineavg[igroup,:]*1e6,marker='o',linestyle="",color=plotcolors[igroup,:],markersize=2,markeredgewidth=0.5,fillstyle="none")
    ah11.semilogx(xvals_interp,fits[igroup,:]*1e6,linestyle="-",color=plotcolors[igroup,:],linewidth=0.4) # 
    # ah11.semilogx(xvals_interp,ip3max[igroup,:],marker='',fillstyle='none',linestyle="-",color=plotcolors[igroup,:],linewidth=0.5)
    # }
ah11.plot([0.02,180],[0,0],linewidth=0.5,color='grey',linestyle="--")
# --------------------------------------------------------------------------------
print("PMCA_flux 0: Ctrl = {}, pmca = {}".format(xvals_interp[iflux0ctrl],xvals_interp[iflux0ad]))
# formatting
ah11.set_xlim([0.02,180])
xticks = [0.1,1,10,100]
ah11.set_xticks(xticks)
ah11.set_xticklabels(xticks,fontsize=8,font=fontprop)
# ah11.get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
xaxislabel = r'$Ca^{2+}\ (\mu M)$' # DHPG
ah11.set_xlabel(xaxislabel,fontsize=8,font=fontprop)
# yticks = [100,150,200]          # cacyt_resp
# ah11.set_ylim([70,230])         # cacyt_resp
# yticks = [0,0.1,0.2]          # cacyt_rate
# ah11.set_ylim([-0.02,0.22])         # cacyt_rate
# ah11.set_yticks(yticks)
# ah11.set_yticklabels(yticks,fontsize=8,font=fontprop)
ah11.spines["right"].set_visible(False)
ah11.spines["top"].set_visible(False)
# matplotlib.rcParams["mathtext.sf"]
# yaxislabel = r'$Ca^{2+}$ response (%)' # cacyt_response
yaxislabel = r'$PMCA\ flux\ (\mu Ms^{-1})$' # cacyt_rate
ah11.set_ylabel(yaxislabel,fontsize=8,font=fontprop)
# saving figures
figsavepath = "/home/anup/goofy/data/suhitalab/astron/figures/new_2020_python/cacyt10to1000000nM50s/"
fh1_name = "cacyt10to1000000nM50s_pmca_flux.svg"
fh1.savefig(os.path.join(figsavepath,fh1_name))
plt.show()
