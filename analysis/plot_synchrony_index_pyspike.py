import numpy as np
import matplotlib.font_manager as font_manager
from matplotlib import pyplot as plt
import os
import pandas as pd

font_path = '/home/anup/.matplotlib/fonts/arial.ttf'
prop = font_manager.FontProperties(fname=font_path,size=20)
print(font_manager.FontProperties())


fpath1 = "/home/anup/astron_data/frap30scarel_processed/"
dir1 =  "synchrony"
ofname_avg="ap1to1000dhz_rel_synchrony_avg.csv"
ofname_sem="ap1to1000dhz_rel_synchrony_sem.csv"

groups = ["ctrl","admglur","adpmca","admglurpmca"]
freqs = np.array([1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000])
synavg = np.loadtxt(os.path.join(fpath1,dir1,ofname_avg),dtype=np.float,delimiter=",")
synsem = np.loadtxt(os.path.join(fpath1,dir1,ofname_sem),dtype=np.float,delimiter=",")

print(synavg)
print(synsem)
# --------------------------------------
fh1 = plt.figure()
ah1 = fh1.add_subplot(111)

plotcolors = np.array([
    [0,0,0],
    [1,0,0],
    [0,0,1],
    [0,1,0]
])

for igroup in range(0,len(groups)):
    for ifreq in range(0,len(freqs)):
        ah1.semilogx(freqs[ifreq]/10,synavg[ifreq,igroup],marker='o',linestyle="-",color=plotcolors[igroup,:])
        error1 = synavg[ifreq,igroup]-synsem[ifreq,igroup]
        error2 = synavg[ifreq,igroup]+synsem[ifreq,igroup]
        ah1.semilogx([freqs[ifreq]/10,freqs[ifreq]/10],[error1,error2],linestyle="-",color=plotcolors[igroup,:])
plt.show()
