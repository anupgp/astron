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
    

# ----------------------------------------------
diskname = "/home/anup/data/"
dir1 = "cacyt10to1000000nM50s/run/"
datasavepath = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/cacyt10to1000000nM50s"
h5pyfname = "cacyt10to1000000nM50s_release_features.hdf5"
# ---------------------------
groups = ["ctrl","admglur","adpmca","admglurpmca"]
# groups = ["ctrl"]
cacyts = [10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000] # cacyt/dhpg
ncacyts = len(cacyts)  
trial0 = 1
ntrials = 1
tstim0 = 200
tstim1 = 250
fname_prefix = "astrocyte_cacyt"
varnames1 = ["time","n0ca_cyt","n0ca_er","n0ip3_cyt","s1glu_ext","n0syt45_vkdoc_glu","n0syt45_vkrel_glu","n0syt45_vkend_glu","n0syt45_vkacd_glu"]
varnames2 = ["n0syt45_vfmob_glu","n0syt45_vfrel_glu","n0syt45_vfend_glu","n0syt45_vfacd_glu"]
varnames3 = ["n0syt45_krrelrate_glu","n0syt45_ffrelrate_glu","n0syt45_totalrelrate_glu"]
varnames4 = ["n0syt45_krreltime_glu","n0syt45_ffreltime_glu","n0syt45_reltime_glu"]
varnames5 = ["n0syt45_relflag_glu","n0syt45_krrelflag_glu","n0syt45_ffrelflag_glu"]

varnames = varnames1 + varnames2 + varnames3 + varnames4 + varnames5
print(varnames)

for igroup in range(0,len(groups)):
    for icacyt in range(0,len(cacyts)):
        fprefix = "".join((fname_prefix,str(cacyts[icacyt]),"nM50s"))
        for itrial,ifile in zip(range(0,ntrials),range(trial0,ntrials+trial0)):
            # {
            findex =  ifile
            fname = "".join((fprefix,"_",groups[igroup],str(findex),".csv"))
            fullname = os.path.join(diskname,dir1,groups[igroup],fname)
/            print(findex," ",fullname)
            df = pd.read_csv(fullname,header=0,usecols=varnames)
            print(df.columns)
            fh = plt.figure()
            ah = fh.add_subplot(111)
            ph1 = ah.plot(df["time"],df["n0ca_cyt"],label="ca_cyt")
            ph2 = ah.plot(df["time"],df["n0syt45_totalrelrate_glu"],label="tot_relrate")
            ph3 = ah.plot(df["time"],df["n0syt45_krrelrate_glu"],label="kr_relrate")
            ph4 = ah.plot(df["time"],df["n0syt45_ffrelrate_glu"],label="ff_relrate")
            handles, labels = ah.get_legend_handles_labels()
            fh.legend(handles, labels, loc='upper center')
            plt.show()
