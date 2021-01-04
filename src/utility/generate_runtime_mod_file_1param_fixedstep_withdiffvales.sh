#! /bin/bash
# This script generates several dynamic parameters input files for runtime modifications

# Assign filenames to variables
exefile="/home/anup/goofy/codes/astron/bin/utility/generate_runtime_mod_file_1param_fixedstep";
# exefile="/home/anup/goofy/projects/codes/astron/bin/utility/generate_runtime_mod_file_1param_expdecay";
# -----------
# dynfile_pf1="/home/anup/goofy/codes/astron/dynparams/dynparams_dhpg"
dynfile_pf1="/home/anup/goofy/codes/astron/dynparams/dynparams_cacyt"
# dynfile_pf1="/Volumes/Anup_2TB/raw_data/astron/raw/astrocyte/frap30scarel/dypars/dynparams_ap30s"
# dynfile_pf1="/mnt/mount1/data/astron/raw/astrocyte/dr_ip3r/dypars/dynparams_ip360s"
# dynfile_pf1="/mnt/mount1/data/astron/raw/astrocyte/sensor/dypars/dynparams_cacyt10s"
# dynfile_pf1="/mnt/mount1/data/astron/raw/astrocyte/dr_pmca/dypars/dynparams_cacyt50s"
# dynfile_pf1="/Users/macbookair/rawdata/data/astron/raw/astrocyte/uottawa_test/er_refil/dypars/dynparams_caer2s"
# dynfile_pf1="/media/anup/data/data/astron/raw/astrocyte/badhpgcarel/dypars/dynparams_"
# dynfile_pf1="/mnt/mount1/data/astron/raw/astrocyte/fr_mglur/dypars/dynparams_ap30s"
# dynfile_pf1="/mnt/mount1/data/astron/raw/astrocyte/dr_ip3r/dypars/dynparams_ip3120s"
# ---------------
# dynfile_pf2="dHz30s"
# ---------------
dynfile_pf3="nM"
dynfile_pf4="s"
# --------------
# extension name of the dynamic parameters file
dynfile_sf=".isfdp"
# ------------
# dhpg100000nM2s
# colname1="time";
# colname2="dhpg_ext1"
# ap100Hz30s
colname1="time";
# colname2="ap_ext1";
# colname2="ip3_ext0"
# colname2="dhpg0";
colname2="ca_cyt0";
# colname2="dhpg_ext1"
# ------------
tstart=200;
tstop=251;
# tstop=202;
# pulsedur=3;
tstep=50e-6;
# -----------------
# pulseamps=(100000)		# 0.1 mM of DHPG application for 2 sec
pulsedurs=(50)			# 0.1 mM of DHPG application for 2 sec
# pulseamps=(100 200 300 400 500 600 700 800 900 1000);
# pulseamps=(0 1 10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 20000 30000 40000 50000 60000 70000 80000 90000 100000);
# pulsedurs=(2 10 30 60 90 120 180 240);
pulseamps=(10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 20000 30000 40000 50000 60000 70000 80000 90000 100000 200000 300000 400000 500000 600000 700000 800000 900000 1000000);
# pulseamps=(200000 300000 400000 500000 600000 700000 800000 900000 1000000);
# pulseamps=(0)
# freqs=(1 2 3 4 5 6 7 8 9 10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000);
# pulseamp=1;
# pulsedurs=3;
# pulseamps=($(seq 0 10 1000));
# pulseamps=($(seq 1010 10 2000));

for pulseamp in ${pulseamps[@]};
# for freq in ${freqs[@]};
do
    for pulsedur in ${pulsedurs[@]};
    do
	amp=$(echo $pulseamp 10 -9 | awk '{ printf "%.15f", ($1 * ($2 ^ $3)) }') # dhpg100000nM2s
 	# period=$(echo $freq 10 -1 | awk '{ printf "%.15f", 1/($1 * ($2 ^ $3)) }') # ap1tp1000dHz30s
	# tstop=$(($tstart+$pulsedur));
	# echo parameter=$dnfile_pf2 amplitude=$amp tstart=$tstart tstop=$tstop duration=$pulsedur
	# dynfile=$dynfile_pf1$dynfile_pf2${pulsedur}$dynfile_pf3${pulseamp}$dynfile_pf4$dynfile_sf;
	# dynfile=$dynfile_pf1$dynfile_pf2${pulseamp}$dynfile_pf4$dynfile_sf;
	# echo $dynfile
	# $exefile --fname $dynfile --colname1 $colname1 --colname2 $colname2 --ncols 2 --tstart $tstart --tstop $tstop --tstep $tstep --pulse-amp $amp --pulse-on-dur $pulsedur --pulse-period $tstop --sepchar ','
	# dynfile=$dynfile_pf1${pulseperiod}$dynfile_pf2$dynfile_sf;
	# $exefile --fname $dynfile --colname1 $colname1 --colname2 $colname2 --ncols 2 --tstart $tstart --tstop $tstop --tstep 200e-6 --pulse-amp 1 --pulse-on-dur 200e-6 --pulse-period $period --sepchar ','
    # ------------------
	dynfile=$dynfile_pf1${pulseamp}$dynfile_pf3$pulsedur$dynfile_pf4$dynfile_sf; # dhpg100000nM2s
	# dynfile=$dynfile_pf1${freq}$dynfile_pf2$dynfile_sf; # ap1to1000dHz30s
	echo $dynfile
	# echo $period, $freq
	echo $amp, $pulsedur
	$exefile --fname $dynfile --colname1 $colname1 --colname2 $colname2 --ncols 2 --tstart $tstart --tstop $tstop --tstep $tstep --pulse-amp $amp --pulse-on-dur $pulsedur --pulse-period 100 --sepchar ',' # glu1to100000nM2s, cacyt10to1000000nM30s
	# $exefile --fname $dynfile --colname1 $colname1 --colname2 $colname2 --ncols 2 --tstart $tstart --tstop $tstop --tstep $tstep --pulse-amp $pulseamp --pulse-on-dur $tstep --pulse-period $period --sepchar ',' # ap1to1000dHz30s
	# $exefile --fname $dynfile --colname1 $colname1 --colname2 $colname2 --ncols 2 --tstart $tstart --tstop $tstop --tstep $tstep --pulse-amp $amp --pulse-on-dur 100 --pulse-period 1000 --sepchar ','


	# $exefile --fname $dynfile --colname1 $colname1 --colname2 $colname2 --ncols 2 --tstart $tstart --tstop $tstop --tstep 200e-6 --pulse-amp $amp --pulse-on-dur 60 --pulse-period 100 --sepchar ','
	# pulseamp2=$(( pulseamp*1000 ));
	# pulseamp2=$pulseamp;
	# dynfile=$dynfile_pf1${pulseamp2}$dynfile_pf2$dynfile_sf;
	# amp=$(echo $pulseamp 10 -6 | awk '{ printf "%.15f", $1 * ($2 ^ $3) }')
	# amp=$(echo $pulseamp 10 -9 | awk '{ printf "%.15f", $1 * ($2 ^ $3) }')
	# echo $amp
	# $exefile --fname $dynfile --colname1 $colname1 --colname2 $colname2 --ncols 2 --tstart $tstart --tstop $tstop --tstep 50e-6 --pulse-amp $amp --pulse-decaytau 3.5 --sepchar ','
    done
done
