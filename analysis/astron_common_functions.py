import numpy as np
np.set_printoptions(linewidth=160)
from matplotlib import pyplot as plt

from scipy.signal import find_peaks,peak_widths,argrelextrema
from scipy.signal import find_peaks_cwt
from scipy.signal import butter, lfilter, freqz, detrend
import h5py

# -----------------------------
def loadh5pydata(fname,dataname):
    with h5py.File(fname,'r') as h5fp:
        print(list(h5fp.keys()))
        data = h5fp[dataname][:]
        return(data)
    # --------------------


def butter_lowpass(cutoff,fs,order=5):
    nyq = 0.5 * fs
    normal_cutoff   = cutoff / nyq
    b, a = butter(order,normal_cutoff,btype = 'low', analog = False)
    return (b,a)
# ------------------


def butter_lowpass_filter(t,y,cutoff,order=5):
    # compute fs: sampling frequency
    fs = 1/np.mean(np.diff(t))
    b, a = butter_lowpass(cutoff,fs,order = order)
    yy = lfilter(b,a,y)
    return(yy)
# ---------------



def smooth(y,windowlen=3,window = 'hanning'):
    s = np.concatenate([y[windowlen-1:0:-1],y,y[-2:-windowlen-1:-1]])
    if (window == 'flat'):
        w = np.ones(windowlen,dtype='double')
    else:
        w = eval('np.'+window+'(windowlen)')
        
    yy = np.convolve(w/w.sum(),s,mode='same')[windowlen-1:-windowlen+1]
    return (yy)
# --------------


def temporal_histogram(df,t0,t1,tbin,thres,delta):
    # create histogram from timeseries data after thresholding and counting events
    # dd: 3d-matrix of the form: [time,variable,trials]
    # t0: histogram start time
    # t1: histogram end time
    # tbin: histogram bin width
    # thres: threshold value to detect an event
    # delta: minumum difference from the valley of a former peak and the subsequent peak
    tbins = np.arange(t0,t1+tbin,tbin)
    maxt = np.zeros((df.shape[0]))
    df = df[(df["time"] >= t0) & (df["time"] <= t1)]
    columns = df.columns
    d = df[columns[-1]]
    imax,_ = find_peaks(d,height=thres,prominence=delta)
    imins = argrelextrema(d.to_numpy(),np.less)[0]
    try:
    # imin,_ = find_peaks(d)
        if(len(imax)>0):
            imin = [imins[imins<item][-1] for item in imax]
    except:
        print(imins)
        
    npeaks = len(imax)
    if (len(imax)>0):
        maxt = df["time"].to_numpy()[imax]
        maxy = df[columns[-1]].to_numpy()[imax]
        # ------------------
        # compute histograms
    hmaxt,_ = np.histogram(maxt,tbins)
    # plotting
    # fh = plt.figure()
    # ah = fh.add_subplot(111)
    # ah.plot(df["time"],df[columns[-1]])
    # ah.plot(maxt,maxy,'o',color='r')
    # plt.show()
    # input()
    return(hmaxt)
# ------------------------
def detect_peaks_above_threshold(t,y,thres,delta,eventval):
    yf = smooth(y,windowlen=20,window='hamming')
    events = np.zeros(t.shape)
    imax,_ = find_peaks(y,height=thres,prominence=delta)
    # print(imax)                 
    eventtimes = t[imax]
    output = []
    if (len(imax)>0):
        events[imax] = eventval
        output = events
    if ((len(imax>0)) and (eventval <= 0)):
        output = eventtimes
    # print(imax,eventtimes)
    return(output)

# --------------------------------

def compute_event_features(df,thres,delta):
    # df contains a dataframe with a time column and a single data column    
    # find the max and min values
    columns = df.columns
    if (len(columns) > 2):
        print("Warning: more than 2 columns in the dataframe!")
    t = df[columns[0]].to_numpy()
    y = df[columns[1]].to_numpy()
    # fcut = 1                  # cutoff frequency
    # yf = butter_lowpass_filter(t,y,fcut)
    yf = smooth(y,windowlen=10,window='hamming')
    # smooth data
    # y1 = smooth(y,windowlen=,window='hamming')
    peaks = []
    rts = []
    fwhms = []
    taus = []
    # ---------------
    ipeaks,_ = find_peaks(yf,height=thres,prominence=delta)
    halfwidths,heights,ileft_hw,iright_hw = peak_widths(yf,ipeaks,rel_height=0.5)
    _,_,ileft_rt,_ = peak_widths(yf,ipeaks,rel_height=0.8)
    _,_,iright_rt,_ = peak_widths(yf,ipeaks,rel_height=0.2)
    _,_,_,itau = peak_widths(yf,ipeaks,rel_height=1-(1/np.exp(1)))
    # convert foat to int
    ifwhms = [[int(item) for item in ileft_hw],[int(item) for item in iright_hw]]
    irts = [[int(item) for item in ileft_rt],[int(item) for item in iright_rt]]
    itaus = [int(item) for item in itau]
    peaks = y[ipeaks]
    rts = [t[iright]-t[ileft] for ileft,iright in zip(irts[0],irts[1])]
    fwhms = [t[iright]-t[ileft] for ileft,iright in zip(ifwhms[0],ifwhms[1])]
    taus =  [t[iright]-t[ileft] for ileft,iright in zip(ipeaks,itaus)]
    print("Risetimes: ",rts)
    print("FWHMs: ",fwhms)
    print("Taus: ",taus)
    # input()
    # --------------------------
    # fh = plt.figure()
    # ah = fh.add_subplot(111)
    # ah.plot(t,y)
    # ah.plot(t,yfmax)    
    # for idx in range(0,len(ipeaks)): 
    #     ah.plot(t[ipeaks[idx]],y[ipeaks[idx]],color="green",marker="x")
    #     print([t[int(ileft_hw[idx])],t[int(iright_hw[idx])]],[heights[idx],heights[idx]])
    #     ah.plot([t[int(ileft_hw[idx])],t[int(iright_hw[idx])]],[heights[idx],heights[idx]],color="black")
    #     ah.plot([t[int(ileft_rt[idx])],t[int(iright_rt[idx])]],[y[int(ileft_rt[idx])],y[int(iright_rt[idx])]],color="black")
    #     ah.plot(t[int(itau[idx])],y[int(itau[idx])],color="black",marker="o")
    # # }
    # plt.show()
    # ---------------------    
    return(peaks,rts,fwhms,taus,ipeaks,irts,ifwhms,itaus)

# -----------------------------------

def jpsth2crosscorr(jpsth,bins,tcorrrange=[]):
    # function operates on the jpsth (a square matrix) and the time bounds to compute
    # the cross-correlation matrix,cross-correlation time histogram (ccth), 
    # as well as the coincidence-time histogram (cth)
    # temporal histogram time bins
    # width to compute the cross correlation histograms
    fctm = np.zeros((2*len(jpsth)-1,len(jpsth)));
    ndiag = np.zeros((2*len(jpsth)-1,len(jpsth))); # no.of diagonal elements
    # =======================
    for i,j in zip(np.arange(len(jpsth)-1,-(len(jpsth)+1),-1),np.arange(0,(len(jpsth)*2)-1)):
        # print(i,j)
        diagonal = np.diagonal(jpsth,i)
        # print(diagonal)
        ileft = int(len(jpsth)/2)-int(len(diagonal)/2)
        iright = ileft+len(diagonal)
        # print("ileft ",ileft,"iright ",iright)
        fctm[j,ileft:iright] = diagonal
        ndiag[j,ileft:iright] = len(diagonal)
    # print(fctm)
    # print(ndiag)
      
    # filter the ctm
    # smooth vector with a moving average on the rows
    # fctm = filter(ones(1,filterwidth)/filterwidth,1,fctm,[],1);
    # ---------------------------------
    # cut ctm to the time range in twidth
    dt = np.diff(bins).mean()
    ilef = np.where(bins > tcorrrange[0])[0][0] - 1
    irig = np.where(bins > tcorrrange[1])[0][0] - 1
    ndlef = ndiag[:,ilef]
    ndrig = ndiag[:,irig]
    ileftop = np.where(ndlef > 0)[0][0]
    ilefbot = np.where(ndlef > 0)[0][-1]
    irigtop = np.where(ndrig > 0)[0][0]
    irigbot = np.where(ndrig > 0)[0][-1]
    itop = np.max([irigtop,ileftop])
    ibot = np.min([irigbot,ilefbot])
    icoinvec = np.argmax(ndiag[itop:ibot,ilef:irig].sum(axis=1))
    # -------------------
    corrbins = np.arange(0,ibot-itop,1)-np.floor((ibot-itop)/2)
    corrbins = corrbins*dt
    corrvec = fctm[itop:ibot,ilef:irig].sum(axis=1)
    # corrvec = corrvec/corrvec.sum()
    coinbins = bins[ilef:irig]
    coinvec = fctm[itop+icoinvec,ilef:irig]
    # ----------------
    # fh = plt.figure()
    # ah1 = fh.add_subplot(131)
    # ah2 = fh.add_subplot(132)
    # ah3 = fh.add_subplot(133)
    # ah1.plot(coinbins,coinvec)
    # ah2.plot(corrbins,corrvec)
    # ah3.plot(ndiag[itop:ibot,ilef:irig].sum(axis=1))
    # plt.show()
    # ---------------
    return(coinbins,coinvec,corrbins,corrvec)


# ----------------------------

def compute_pmca_features(t,y,tstim0,tstim1):
    istim0 = np.where(t>=tstim0)[0][0]-1
    istim1 = np.where(t>=tstim1)[0][0]-1
    istim_ss = np.where(t<tstim1-10)[0][-1]
    imax = istim0 + np.argmax(y[istim0:istim1])
    imin = istim0 + np.argmin(y[istim0:istim1])
    if(abs(y[imax]) > abs(y[imin])):
        ipeak = imax
    else:
        ipeak = imin
    # ipeaks,_ = find_peaks(y[istim0:istim1])
    # ipeak =  ipeaks[0] + istim0
    tpeak = t[ipeak]
    ypeak = y[ipeak]
    yss = np.mean(y[istim_ss:istim1])
    # -----------------------
    # plotting to check the measurements
    # fh = plt.figure()
    # ah = fh.add_subplot(111)
    # ah.plot(t,y)
    # ah.plot(tpeak,ypeak,'o')
    # ah.plot([t[istim_ss],t[istim1]],[yss,yss],'-',color='k',linewidth=2)
    # plt.show()
    return(ypeak,yss)
