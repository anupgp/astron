import numpy as np
import pandas as pd
from scipy.interpolate import interp1d
from scipy.signal import resample
from matplotlib import pyplot as plt
import matplotlib.font_manager as font_manager

cali2008='/Users/macbookair/goofy/data/suhitalab/astron/cooked/cali2008_astrorelease_sdf.csv'
domercq2006='/Users/macbookair/goofy/data/suhitalab/astron/cooked/domercq2006_astrorelease_atp.csv'
marchaland2008='/Users/macbookair/goofy/data/suhitalab/astron/cooked/marchaland2008_dhpg_release_histogram_noheader.csv'
santello2011a='/Users/macbookair/goofy/data/suhitalab/astron/cooked/santello2011_astrorelease_atp.csv'
santello2011s='/Users/macbookair/goofy/data/suhitalab/astron/cooked/santello2011_astrorelease_sdf.csv'
stimonset=[0.001,5.005,0.033,0.0,0.009]
studynames=list(['cali2008','domercq2006','marchaland2008','santello2011a','santello2011s'])
releasefiles=[cali2008,domercq2006,marchaland2008,santello2011a,santello2011s]
timestart=-1
timestop=4
samplingperiod=50            # new sampling period = 50 ms
# print(timeintervals)
filecount=-1
reldata = pd.DataFrame()
reldata2 = pd.DataFrame()
for relfile in releasefiles:
    # load all data
    filecount=filecount+1
    data=pd.read_csv(relfile,delimiter=' ',skipinitialspace=True,header=None,names=['time','release'],index_col=False,dtype=np.float64)
    # adjust time offset
    data['time'] = data['time']-stimonset[filecount]
    data['study'] = studynames[filecount]
    data['index_col'] = data.index
    data['time'] = data['time']*1000
    print(data.head())
    print(data.index)
    # concatenate data into one df
    reldata=pd.concat([reldata,data],ignore_index=True)
    # interpolate data
    newtime=np.arange(np.ceil(data.iloc[0,0]),np.ceil(data.iloc[-1,0]),50)
    f_interp1d=interp1d(data['time'],data['release'],kind='cubic')
    # print(data['time'],newtime)
    print(np.shape(data['time']),np.shape(newtime))
    data2 = pd.DataFrame(newtime,columns=['time'])
    data2['release']= f_interp1d(newtime)
    data2['study'] = studynames[filecount]
    data2['index_col'] = data2.index
    # concatenate data into one df
    reldata2=pd.concat([reldata2,data2],ignore_index=True)
        
# add study as another index for multiindexing of df 
reldata.set_index(keys=['index_col','study'],append=False,drop=False,inplace=True,verify_integrity=True)
reldata2.set_index(keys=['index_col','study'],append=False,drop=False,inplace=True,verify_integrity=True)
# compute cumulative sum
reldata2['release_cum'] = reldata2['release'].groupby(['study']).cumsum(axis=None)
# for convinient slicing of dataframes
idx=pd.IndexSlice
# reshape dataframe to wide format
# reldata2s=reldata2.loc[idx[reldata2['time']>=0 & idx[reldata2['time']<500 ]],['index_col','study','time']]
# reldata2sw=reldata2s.pivot(index='index_col',columns='study',values=['time'])
# print(reldata2sw)
# summary statistics on  dataframe
avgtime=reldata2.groupby(['time'])['time'].mean().values
avgrel=reldata2.groupby(['time'])['release'].mean().values
stdrel=reldata2.groupby(['time'])['release'].std().values
avgrelcum=reldata2.groupby(['time'])['release_cum'].mean().values
stdrelcum=reldata2.groupby(['time'])['release_cum'].std().values

# print(reldata.loc[idx[:,'cali2008'],['time','release']])
# print(reldata2.loc[idx[reldata2['time']>=-100] & idx[reldata2['time']<=100],:])

# display release rate data
font_path = '/Users/macbookair/.matplotlib/Fonts/Arial.ttf'
fontprop = font_manager.FontProperties(fname=font_path,size=21)
fig=plt.figure()
ax=fig.add_subplot(111)
plotname_relrate='/Users/macbookair/goofy/data/suhitalab/astron/figures/newfigures2019/summary_release_literature.png'
xlim1,xlim2 = (-500,3000)
ylim1,ylim2 = (-10,40)
xticks=[-500,0,1000,2000,3000]
yticks=[-10,10,20,30,40]
greycol=(0.8,0.8,0.8)
ax.fill_between(avgtime,avgrel-stdrel,avgrel+stdrel,edgecolor=greycol,facecolor=greycol,alpha=1)
for study in studynames:
    ax.plot(reldata2.loc[idx[:,study],'time'],reldata2.loc[idx[:,study],'release'],'-o')
ax.plot(avgtime,avgrel,'-',color='black',lineWidth=2)
ax.plot([0,2000],[-4,-4],color='black',linewidth=3)
ax.text(300,-8,'DHPG / ADP / SDF',fontsize=14)
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
ax.set_ylabel('Number of release events',FontProperties=fontprop)
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
legendnames=['Cali et. al, 2008 [SDF-1α]','Domercq et. al, 2006 [ADP]','Marchaland et. al, 2008 [DHPG]',\
             'Santello et. al, 2011 [ADP]','Santello et. al, 2011 [SDF-1α]','Average']
ax.legend(legendnames,frameon=False,loc=(0.5,0.65),mode=None)
# -----------------
fig.savefig(plotname_relrate,dpi=300)
# ----------------
plt.show(block=False)
# input('press any key to exit')
plt.close()

# ----------------------------
# display cum release rate data
# font_path = '/Users/macbookair/.matplotlib/Fonts/Arial.ttf'
# fontprop = font_manager.FontProperties(fname=font_path,size=21)
fig=plt.figure()
ax=fig.add_subplot(111)
plotname_relratecum='/Users/macbookair/goofy/data/suhitalab/astron/figures/newfigures2019/summary_release_cum_literature.png'
xlim1,xlim2 = (-750,2500)
ylim1,ylim2 = (-100,600)
xticks=[0,1000,2000]
yticks=[0,200,400,600]
greycol=(0.8,0.8,0.8)
ax.fill_between(avgtime,avgrelcum-stdrelcum,avgrelcum+stdrelcum,edgecolor=greycol,facecolor=greycol,alpha=1)
for study in studynames:
    ax.plot(reldata2.loc[idx[:,study],'time'],reldata2.loc[idx[:,study],'release_cum'],'-o')
# ax.plot(avgtime,avgrelcum,'-',color='black',lineWidth=2)
ax.plot([0,2000],[-40,-40],color='black',linewidth=3)
ax.plot([-750,2500],[400,400],color='black',linestyle='--',linewidth=1)
ax.text(500,-5,'DHPG / ADP / SDF',fontsize=14)
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
ax.set_ylabel('Cumulative release events',FontProperties=fontprop)
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
legendnames=['Cali et. al, 2008 [SDF-1α]','Domercq et. al, 2006 [ADP]','Marchaland et. al, 2008 [DHPG]',\
             'Santello et. al, 2011 [ADP]','Santello et. al, 2011 [SDF-1α]']
ax.legend(legendnames,frameon=False,loc=(0.03,0.75),mode=None)
# -----------------
fig.savefig(plotname_relratecum,dpi=300)
# ----------------
plt.show(block=False)
# input('press any key to exit')
plt.close()

