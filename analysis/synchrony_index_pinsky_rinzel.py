import numpy as np
import cmath
from matplotlib import pyplot as plt


# -------------------------------
def average_synchrony_per_bins(dts,rs,tbins):
    avgrs = np.zeros((len(tbins)),dtype=np.float)
    semrs = np.zeros((len(tbins)),dtype=np.float)
    for i in range(0,len(tbins)-1):
        istart = np.where(dts >= tbins[i])[0] 
        istop = np.where(dts > tbins[i+1])[0]
        if ((len(istart)>0) & (len(istop)>0)):
            istart = istart[0]
            istop = istop[0] - 1
            if (istop > istart):
                # print(istart,istop)
                avgrs[i] = np.mean(rs[istart:istop])
                # }
            # }
        # }
    # ---------------
    return(avgrs)


# ---------------------------------
def synchrony_index(ts,tstart,tstop):
    """Compute synchrony (phase coherence) of spike times \
    Ref: pinsky1995"""
    dts = np.empty((0),dtype = np.float)
    rs = np.empty((0),dtype = np.float)
    # Convert spike times to phases
    for ri in range(0,np.shape(ts)[0]):
        rts = ts[ri,:]         # a row of ts (time stamps)
        rts = rts[(rts >= tstart) & (rts <= tstop)]
        # print(rts)
        # input()
        # remove nan from the row
        # rts = rts[~np.isnan(rts)]
        for ci in range(0,len(rts)-1): # a row has at least two spikes
            tbegin = rts[ci]
            tend = rts[ci+1]
            tss = np.sort(ts[(ts>=tstart) & (ts<=tstop) & (ts>=tbegin) & (ts<tend) ])
            if((len(tss) >= 2) & (tend > tbegin)):
                dt = tend-tbegin
                dts = np.append(dts,dt)
                ph = (tss-tbegin)/dt # convert time into phases
                zph = np.exp(ph * 2 * np.pi * np.complex(0,1))
                r =  np.sqrt(1 - np.var(zph))
                rs = np.append(rs,r)
                print("tss_min: {}, tss_max: {}, dt: {}, syn: {}".format(np.min(tss),np.max(tss),dt,r))
            # ----------------
        # ------------
    # ---------
    idx = np.argsort(dts)
    dts = dts[idx]
    rs = rs[idx]
    # print(dts)
    # print(rs)
    # if (len(dts) > 0):
    #     fh = plt.figure()
    #     ah = fh.add_subplot(111)
    #     ah.plot(dts,rs)
    #     plt.show()
    return(dts,rs)

    

    
