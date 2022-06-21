# ------------------
# JPSTH colormaps
# fh3,(ah31,ah32,ah33,ah34,ah35) = plt.subplots(figsize=(4,12),dpi=600,frameon=False,ncols=5,gridspec_kw={"width_ratios":[1,1,1,1,0.3]})
# fh3,(ah31) = plt.subplots(figsize=(4,4),dpi=600,frameon=False,ncols=1,gridspec_kw={"width_ratios":[1]})
# fh3.subplots_adjust(hspace=0,wspace=0.5)
# ah35 = fh3.add_subplot(155,position=Bbox([[0.8,0.2],[0.83,0.7]]),frameon=False) # [[xmin,ymin],[xmax,ymax]]
# print(ah35.get_position())
# create an axes on the right side of ax. The width of cax will be 5%
# of ax and the padding between cax and ax will be fixed at 0.05 inch.
# divider = make_axes_locatable(ah34)
# cax = divider.append_axes("right", size="5%", pad=0.05)

# for igroup,ah in zip(range(1,2),[ah31]):
#     ph = ah.imshow(rjpsth[igroup,:,:,:,:].mean(0).mean(-1),origin="lower",interpolation="nearest",cmap="hot")
# }
# add color bar
# ip = InsetPosition(ah34, [1.4,0,0.3,1]) 
# ah35.set_axes_locator(ip)
# cb = fh3.colorbar(ph,cax=ah35,ax=[ah31,ah32,ah33,ah34],orientation="vertical",ticks=[0,0.3,0.7])
# cb.ax.set_ylim([0,0.7])
# cb.ax.set_yticklabels((0.0,0.3,0.7),fontsize=8,font=fontprop)
# cb.set_label("Synchrony index",font=fontprop,fontsize=10)

# # --------- formating ---------
# # fh3.subplots_adjust(bottom=0.1,left=0.0,right=0.75,top=0.9,hspace=0.2,wspace=-0.6)
# xticks = [np.where(freqs>item)[0][0] for item in np.array([4,69,999]) if len(np.where(freqs>item)[0]) > 0]
# [ah.set_xlim([0,24]) for ah in [ah31,ah32,ah33,ah34]]
# [ah.set_xticks(xticks) for ah in [ah31,ah32,ah33,ah34]]
# [ah.set_xticklabels([0.5,7,100],fontsize=8,font=fontprop) for ah in [ah31]]
# [ah.set_title(title,fontsize=8,font=fontprop,y=1.1) for ah,title in zip([ah31,ah32,ah33,ah34],["Control",r"$A\beta$-mGluR",r"$A\beta$-PMCA",r"           $A\beta$-mGluR-PMCA"])]
# [ah.set_xticklabels([],fontsize=8,font=fontprop) for ah in [ah32,ah33,ah34]]
# # [ah.xaxis.set_visible(False) for ah in [ah32,ah33,ah34]]
# [ah.set_xlabel("Stimulation frequency (Hz)",fontsize=8,font=fontprop,loc="left") for ah in [ah31]]

# # --------------------------
# yticks = [np.where(tbins>item)[0][0] for item in np.array([0,2.4,4.9]) if len(np.where(tbins>item)[0]) > 0]  
# [ah.set_ylim([0,48]) for ah in [ah31,ah32,ah33,ah34]]
# [ah.set_yticks(yticks) for ah in [ah31,ah32,ah33,ah34]]
# [ah.set_yticklabels([0,2.5,5],fontsize=8,font=fontprop) for ah in [ah31]]
# [ah.set_yticklabels([],fontsize=8,font=fontprop) for ah in [ah32,ah33,ah34]]
# # [ah.yaxis.set_visible(False) for ah in [ah32,ah33,ah34]]
# [ah.set_ylabel("Timeseries length (s)",fontsize=8,font=fontprop) for ah in [ah31]]
# # fh3.tight_layout(pad=0)
# ---------------------------------------------------
