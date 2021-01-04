#! /bin/bash
# This script generates several dynamic parameters input files for runtime modifications

# Assign filenames to variables
exefile="/home/anup/goofy/projects/codes/astron/bin/utility/generate_runtime_mod_file_1param_fixedstep";
# exefile="/home/anup/goofy/projects/codes/astron/bin/utility/generate_runtime_mod_file_1param_expdecay";
# dynfile_pf1="/mnt/mount1/data/astron/raw/astrocyte/dr_mglur/dypars/dynparams_dhpg2s"
# dynfile_pf1="/mnt/mount1/data/astron/raw/astrocyte/dr_ip3r/dypars/dynparams_ip360s"
# dynfile_pf1="/mnt/mount1/data/astron/raw/astrocyte/sensor/dypars/dynparams_cacyt10s"
dynfile_pf1="/mnt/mount1/data/astron/raw/astrocyte/dr_pmca/dypars/dynparams_cacyt100s"
# dynfile_pf1="/mnt/mount1/data/astron/raw/astrocyte/fr_mglur/dypars/dynparams_ap30s"
# dynfile_pf1="/mnt/mount1/data/astron/raw/astrocyte/dr_ip3r/dypars/dynparams_ip3120s"
# dynfile_pf2="dHz"
dynfile_pf2="nM"
dynfile_sf=".isfdp"

colname1="time";
# colname2="ip3_ext0"
colname2="ca_cyt_ext0";
# colname2="ap_ext1";
# colname2="ip3_cyt_ext0";
tstart=50;
# tstop=231;
tstop=100;
tstep=100e-6;

# pulseamps=(100 200 300 400 500 600 700 800 900 1000);
# pulseamps=(0 1 10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 20000 30000 40000 50000 60000 70000 80000 90000 100000);
pulseamps=(0 1 10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 20000 30000 40000 50000 60000 70000 80000 90000 100000 200000 300000 400000 500000 600000 700000 800000 900000 1000000);
# pulseamps=(200000 300000 400000 500000 600000 700000 800000 900000 1000000);
# pulseperiods=(1 2 3 4 5 6 7 8 9 10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000);
# pulseamps=($(seq 0 10 1000));
# pulseamps=($(seq 1010 10 2000));
for pulseamp in ${pulseamps[@]};
# for pulseperiod in ${pulseperiods[@]};
do
    # period=$(echo $pulseperiod 10 -1 | awk '{ printf "%.15f", 1 / ($1 * ($2 ^ $3)) }')
    # echo $period
    # dynfile=$dynfile_pf1${pulseperiod}$dynfile_pf2$dynfile_sf;
    # $exefile --fname $dynfile --colname1 $colname1 --colname2 $colname2 --ncols 2 --tstart $tstart --tstop $tstop --tstep 200e-6 --pulse-amp 1 --pulse-on-dur 200e-6 --pulse-period $period --sepchar ','
    # ------------------
    amp=$(echo $pulseamp 10 -9 | awk '{ printf "%.15f", ($1 * ($2 ^ $3)) }')
    echo $amp
    dynfile=$dynfile_pf1${pulseamp}$dynfile_pf2$dynfile_sf;
    $exefile --fname $dynfile --colname1 $colname1 --colname2 $colname2 --ncols 2 --tstart $tstart --tstop $tstop --tstep $tstep --pulse-amp $amp --pulse-on-dur 100 --pulse-period 1000 --sepchar ','
    # $exefile --fname $dynfile --colname1 $colname1 --colname2 $colname2 --ncols 2 --tstart $tstart --tstop $tstop --tstep 50e-6 --pulse-amp 1 --pulse-on-dur 50e-6 --pulse-period $period --sepchar ','

    # $exefile --fname $dynfile --colname1 $colname1 --colname2 $colname2 --ncols 2 --tstart $tstart --tstop $tstop --tstep 200e-6 --pulse-amp $amp --pulse-on-dur 60 --pulse-period 100 --sepchar ','
    # pulseamp2=$(( pulseamp*1000 ));
    # pulseamp2=$pulseamp;
    # dynfile=$dynfile_pf1${pulseamp2}$dynfile_pf2$dynfile_sf;

    # amp=$(echo $pulseamp 10 -6 | awk '{ printf "%.15f", $1 * ($2 ^ $3) }')
    # amp=$(echo $pulseamp 10 -9 | awk '{ printf "%.15f", $1 * ($2 ^ $3) }')
    # echo $amp
    # $exefile --fname $dynfile --colname1 $colname1 --colname2 $colname2 --ncols 2 --tstart $tstart --tstop $tstop --tstep 50e-6 --pulse-amp $amp --pulse-decaytau 3.5 --sepchar ',' 
done

