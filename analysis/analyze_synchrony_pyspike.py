import matplotlib.pyplot as plt
import pyspike as spk
import numpy as np
import math
import os

# filename = "/home/anup/goofy/software/PySpike/examples/PySpike_testdata.txt"
fpath1 = "/home/anup/astron_data/frap30scarel_processed/"
dir1 =  "synchrony"
# fpath1 = "/mnt/mount1/data/astron/raw/astrocyte/fr_mglur_rel/run/"
# fpath1 = "/home/anup/goofy/projects/data/astron/cooked/fr_mglur_rel/"
# fpath1 = "/home/anup/goofy/projects/data/astron/cooked/fr_mglur_ca/"
# fpath1 = "/home/anup/goofy/projects/data/astron/cooked/ca_events/"
# fpath2 = "/"
fname1 = "astrocyte_ap30s"
fname2 = "dHz_"
fname3 = "rel_"
# fname3 = "cacyt_"
ifext = ".txt"
groups = ["ctrl","admglur","adpmca","admglurpmca"]
ofname_avg="ap1to1000dhz_rel_synchrony_avg.csv"
ofname_sem="ap1to1000dhz_rel_synchrony_sem.csv"
expids = [1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000]
spike_sync_all = [];
ifname = ""
ofname = ""
col = -1

syndata_avg = np.zeros(shape=(len(expids),len(groups)))
syndata_sem = np.zeros(shape=(len(expids),len(groups)))
syndatanorm_avg = np.zeros(shape=(len(expids),len(groups)))
syndatanorm_sem = np.zeros(shape=(len(expids),len(groups)))

for group in groups:
    col  = col + 1
    row = -1
    for expid in expids:
        ifname = os.path.join(fpath1,dir1,"".join((fname1,str(expid),fname2,fname3,group,ifext)))
        print(ifname)
        # Find Edges from the spike time file
        spktimes = []
        mins = []
        maxs = []
        tstart = 0
        tstop = 0
        numcells = 0
        numevents = 0
        with open(ifname) as spkt_file:
            for aline in spkt_file:
                st_strs = aline.strip()
                st_strs = st_strs.split(" ")
                spkts = []
                for st_str in st_strs:
                    spkts.append(float(st_str))
                spktimes.append(spkts)
                mins.append(min(spkts))
                maxs.append(max(spkts))
                numcells = len(mins)
                tstart = math.floor(min(mins));
                tstop = math.ceil(max(maxs));
        print("start time = ",tstart)
        print("stop time = ",tstop)
        print("Num cell = ",numcells)
        # -----------------------------------
        row = row + 1
        spike_trains = spk.load_spike_trains_from_txt(ifname,edges=(tstart,tstop))
        x = []
        y = []
        if ((tstart<tstop) & (numcells >1)):
            spike_sync_profile = spk.spike_sync_profile(spike_trains)
            x,y = spike_sync_profile.get_plottable_data()
            syndata_avg[row][col] = np.mean(y)
            syndata_sem[row][col] = np.std(y)/math.sqrt(numcells)
        # print("x = ",x)
        # print("y = ",y)
        print("Direct avg = ",spk.spike_sync(spike_trains))
        print("Computed avg = ",syndata_avg[row][col])
        print("Computed sem = ",syndata_sem[row][col])
        # -------------------------------------
print(syndata_avg)
print(syndata_sem)
input()
# fh = plt.figure()
# ah = fh.add_subuplot(111)

# ----------------------
np.savetxt(os.path.join(fpath1,dir1,ofname_avg),syndata_avg,delimiter=",")
np.savetxt(os.path.join(fpath1,dir1,ofname_sem),syndata_sem,delimiter=",")
# ---------------------
# spike_trains = spk.load_spike_trains_from_txt(filename,edges=(200,230))
# spike_sync =  spk.spike_sync(spike_trains)
# avg_spike_sync = np.mean(spike_sync)
# print(avg_spike_sync)

# linecount=0
# rows1=[]
# # fig1 = plt.figure(1)
# with open(filename) as ins1:
#     next(ins1)
#     next(ins1)
#     next(ins1)
#     for line1 in ins1:
#         entries=line1.strip()
#         entries1=entries.split(" ")
#         list1=[]
#         for i in range(len(entries1)):
#             list1.append(float(entries1[i]))
#         rows1.append(list1)
        
# # print(rows1)
# # -------------------------
# # plot a scatter plot
# for i in range(len(rows1)):
#     plt.subplot(1,2,1)
#     plt.vlines(rows1[i], ymin = i, ymax=i+0.5)
# # fig1.show()
# # fig1.show()
# # ------------------------

# # fig_2 = plt.figure(2)
# # isi_profile = spk.isi_profile(spike_trains[0], spike_trains[1])
# # x, y = isi_profile.get_plottable_data()
# spike_profile = spk.spike_sync_profile(spike_trains)
# x, y = spike_profile.get_plottable_data()
# plt.subplot(1,2,2)
# plt.plot(x, y, '--k')
# # plt.plot(spike_trains[0])
# # print("ISI distance: %.8f" % isi_profile.avrg())
# # fig_2.show()
# # input()
# plt.show()
