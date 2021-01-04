import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
import os
from scipy.signal import find_peaks,argrelextrema
import pandas as pd


# ----------------------------------------------
fpath1 = "/Volumes/Anup_2TB/raw_data/astron/raw/astrocyte/ap1to100dHz30s/run/"
groups = ["ctrl","admglur","adpmca","admglurpmca"]
fprefix = "astrocyte_ap50dHz30s_"
# varnames = ["time","n0ca_cyt","s1glu_ext"]
# varnames = ["time","n0ca_cyt","n0syt45_totalrelrate_glu"]
varnames = ["time","n0ca_cyt","n0syt45_relflag_glu"]
paramname = varnames[2]
ntrials = 10
trial0 = 1
nbatch = 1
ngroup = 4
t0 = 190
t1 = 205
for i in range(0,len(groups)):
    df = pd.DataFrame()
    for j in range(0,ntrials):
        fpath2 = os.path.join(fpath1,groups[i])
        fname =  "".join([fprefix,groups[i],str(j+1),".csv"])
        filename = os.path.join(fpath2,fname)
        print(filename)
        dftemp = pd.read_csv(filename,header=0,usecols=varnames)
        df["".join((paramname,str(j)))] = dftemp[paramname]
        # ------------
    df["time"] = dftemp["time"]
    print(df)
    input()
    fh = plt.figure()
    ah = fh.add_subplot(111)
    ah.plot(df["time"],df.iloc[:,0:-1])
    # ---------
    plt.show()
    
