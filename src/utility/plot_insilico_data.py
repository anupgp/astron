import numpy as np
import matplotlib.font_manager as font_manager
from matplotlib import pyplot as plt

font_path = '/Users/macbookair/.matplotlib/Fonts/Arial.ttf'
fontprop = font_manager.FontProperties(fname=font_path,size=20)

pdata_fname = '/Users/macbookair/rawdata/data/astron/raw/astrocyte/dr_mglur/run/ctrl/astrocyte_dhpg30s1000nM_ctrl1.csv'
simdat = np.loadtxt(pdata_fname,delimiter=',',skiprows = 1)

fig = plt.figure()
ax = fig.add_subplot(111)
print(simdat.shape)
plt.plot(simdat[:,0],simdat[:,1:5])
plt.show()

