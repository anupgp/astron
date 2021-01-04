import numpy as np
import pandas as pd
from scipy.interpolate import interp1d
from scipy.signal import resample
from matplotlib import pyplot as plt
import matplotlib.font_manager as font_manager

marchaland2008ca='/Users/macbookair/goofy/data/suhitalab/astron/cooked/marchaland2008_dhpg_cacyt_histogram.csv'
marchaland2008rel='/Users/macbookair/goofy/data/suhitalab/astron/cooked/marchaland2008_dhpg_release_histogram_noheader.csv'
dataca=pd.read_csv(marchaland2008ca,delimiter=',',skipinitialspace=True,header=None,skiprows=1,names=['time','caevents'],index_col=False,dtype=np.float64)
datarel=pd.read_csv(marchaland2008rel,delimiter=' ',skipinitialspace=True,header=None,names=['time','relevents'],index_col=False,dtype=np.float64)
# display release rate data
font_path = '/Users/macbookair/.matplotlib/Fonts/Arial.ttf'
fontprop = font_manager.FontProperties(fname=font_path,size=21)
fig=plt.figure()
ax=fig.add_subplot(111)
plotname_carel='/Users/macbookair/goofy/data/suhitalab/astron/figures/newfigures2019/marchaland2008_carelease.png'
xlim1,xlim2 = (-750,2500)
ylim1,ylim2 = (-10,40)
xticks=[0,1000,2000]
yticks=[0,10,20,30,40]
ax.plot(dataca['time']*1000,dataca['caevents'],'-o')
ax.plot(datarel['time']*1000,datarel['relevents'],'-o')
ax.plot([0,2000],[-3,-3],color='black',linewidth=3)
ax.text(400,-8,'DHPG / ADP / SDF',fontsize=14)
# plot asthetics here
ax.spines["right"].set_visible(False)
ax.spines["top"].set_visible(False)
ax.spines["bottom"].set_linewidth(2)
ax.spines["left"].set_linewidth(2)
ax.set_xlim(xlim1,xlim2)
ax.set_ylim(ylim1,ylim2)
plt.xticks(FontProperties=fontprop)
plt.yticks(FontProperties=fontprop)
ax.set_xlabel('Time (msec) ',fontproperties=fontprop)
ax.set_ylabel('Number of events',FontProperties=fontprop)
ax.tick_params(axis='both',length=6,direction='out',width=2,which='major')
ax.tick_params(axis='both',length=3,direction='out',width=2,which='minor')
ax.yaxis.set_label_coords(-0.15,0.5)
plt.subplots_adjust(left=0.18)
ax.xaxis.set_label_coords(0.5,-0.17)
plt.subplots_adjust(bottom=0.2)
ax.set_xticks(xticks)
ax.set_xticklabels(xticks)
ax.set_yticks(yticks)
ax.set_yticklabels(yticks)
legendnames=['Calcium events','Release events']
ax.legend(legendnames,frameon=False,loc=(0.6,0.75),mode=None)
# ----------------
fig.savefig(plotname_carel,dpi=300)
# -----------------
plt.show(block=False)
# input('press any key to exit')
plt.close()


