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
from scipy.signal import find_peaks    

# ----------------------------------------------
diskname = "/run/media/anup/3becd611-cb79-4b80-b941-2edcc0d64cb4/data/"
dir1 = "badhpgcarel/run/"
datasavepath = "/home/anup/goofy/data/suhitalab/astron/cooked/new_2020_python/dgpg10to100000nM2to120s"
h5pyfname = "dhpg10to100000nM2to120s_features.hdf5"
# ---------------------------
groups = ["ctrl","admglur","adpmca","admglurpmca"]
# groups = ["ctrl"]
ngroup = len(groups)
dhpgs = [0,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000] # dhpg
ndhpgs = len(dhpgs)
stimdurs = [2,10,30,60,90,120]
trial0 = 1
ntrial = 100
tstim0 = 200
# tstim1 = 250
fname_prefix = "astrocyte_"
varnames1 = ["time","n0ca_cyt","n0ca_er","n0ip3_cyt","s1glu_ext","n0syt45_vkdoc_glu","n0syt45_vkrel_glu","n0syt45_vkend_glu","n0syt45_vkacd_glu"]
varnames2 = ["n0syt45_vfmob_glu","n0syt45_vfrel_glu","n0syt45_vfend_glu","n0syt45_vfacd_glu"]
varnames3 = ["n0syt45_krrelrate_glu","n0syt45_ffrelrate_glu","n0syt45_totalrelrate_glu"]
varnames4 = ["n0syt45_krreltime_glu","n0syt45_ffreltime_glu","n0syt45_reltime_glu"]

varnames = varnames1 + varnames2 + varnames3 + varnames4
print(varnames)
# --------------------------
cares = np.zeros((ngroup,ntrial,len(stimdurs),len(dhpgs)),dtype=np.float16()) # responsivity
carate = np.zeros((ngroup,ntrial,len(stimdurs),len(dhpgs)),dtype=np.float16()) # cacyt event rate
resting_cacyt = np.zeros((ngroup,ntrial,len(stimdurs),len(dhpgs)),dtype=np.float16()) # cacyt resting
resting_ip3 = np.zeros((ngroup,ntrial,len(stimdurs),len(dhpgs)),dtype=np.float16()) # cacyt resting
resting_caer = np.zeros((ngroup,ntrial,len(stimdurs),len(dhpgs)),dtype=np.float16()) # cacyt resting

# -------------------------
for igroup in range(0,ngroup):
    for idhpg in range(0,len(dhpgs)):
        for istimdur in range(0,len(stimdurs)):
            fprefix = "".join((fname_prefix,str(stimdurs[istimdur]),"s",str(dhpgs[idhpg]),'nM'))
            for itrial,ifile in zip(range(0,ntrial),range(trial0,ntrial+trial0)):
            # {
                findex =  ifile
                fname = "".join((fprefix,"_",groups[igroup],str(findex),".csv"))
                fullname = os.path.join(diskname,dir1,groups[igroup],fname)
                print(findex," ",fullname)
                df = pd.read_csv(fullname,header=0,usecols=varnames)
                # -----------------
                # }
            # }
        # }
    # }
# }


# --------------------------------- saving data ---------------------------
# save the matrices using h5py
# with h5py.File(os.path.join(datasavepath,h5pyfname),'w') as h5f:
#     # {
#     dset1 = h5f.create_dataset("tkr",data=tkr)
# # }
