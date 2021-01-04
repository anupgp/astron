#! /bin/bash
# This script generates several dynamic parameters input files for runtime modifications

# Assign filenames to variables
exefile="/home/anup/goofy/projects/codes/astron/bin/utility/generate_runtime_mod_file_1param_poisson";
dynfile_pf1="/media/anup/data/data/astron/raw/astrocyte/mutualinfouni/dypars/dynparams_"
dynfile_pf2="ap"
dynfile_pf3="s"
dynfile_pf4="dHz"
dynfile_pf5="trial"
dynfile_sf=".isfdp"
# --------------
colname1="time";
colname2="ap_ext1";
# -------------
dfreq=100; # values in deci Hz
pulseamp=1;
tstart=200;
tstop=210;
tstep=50e-6;
# pulseperiod=$((1/$dfreq));
pulseperiod=$(echo $dfreq 10 -1 | awk '{ printf "%.15f", (1 / ($1 * ($2 ^ $3))) }')
pulsedur=$tstep;
stimdur=$(($tstop-$tstart));
startid=1;
stopid=10000;
trials=($(seq $startid 1 $stopid));

for trial in ${trials[@]};
do
    dynfile=$dynfile_pf1$dynfile_pf2${stimdur}$dynfile_pf3${dfreq}$dynfile_pf4"_"$dynfile_pf5$trial$dynfile_sf;
    echo $dynfile
    echo Pulse period = $pulseperiod;
    echo Pulse duration = $pulsedur;
    echo Stim start = $tstart;
    echo Stim stop = $tstop;
    
    $exefile --fname $dynfile --colname1 $colname1 --colname2 $colname2 --ncols 2 --tstart $tstart --tstop $tstop --tstep $tstep --pulse-amp $pulseamp --pulse-on-dur $pulsedur --pulse-period $pulseperiod --sepchar ','
done

