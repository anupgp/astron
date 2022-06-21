#! /bin/bash
# make expdata folder, stimparams folder, and the copy stimparams file
# cheak if datpath & expfolder exists
codepath="/home/anup/goofy/codes/astron"
datapath="/home/anup/data"
execfile="/home/anup/goofy/codes/astron/bin/astron_main"
expgroups="ctrl"
expfolder="dhpg100000nM2s"
trialstart=1
trialstop=400
stimprefix1="dhpg"
stimsuffix1="nM2s"
stimvalues1="100000"

if [[ ! -d $datapath ]]; then
    printf "folder: %s does not exist\n" ${datapath}
    exit 1
fi
mkdir -p $datapath/$expfolder/"stimparams"
cp $codepath/stimparams/stimparams_dhpg100000nM2s.isfdp $datapath/$expfolder/stimparams/
# -----------------
bash run/sim_run_astron_single_machine.sh --codepath $codepath --datapath $datapath --execfile $execfile --expgroups "${expgroups[*]}" --expfolder $expfolder --trialstart $trialstart --trialstop $trialstop --stimprefix1 $stimprefix1 --stimsuffix1 $stimsuffix1 --stimvalues1 $stimvalues1
# ---------------
