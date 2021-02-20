#! bin/bash
# Simulation run script single cpu (desktop) / multiple cpr(pbs)
# ----------------
# Assign filenames to variables
codepath="/home/anup/astron";
pbsdatapath="/storage/nishant1/anup/data/astron/raw/astrocyte";
# ------------------
datapath=$pbsdatapath;
# ------------------
exefile=$codepath"/bin/astron_main";
# exefile=$codepath"/bin/astron_vr";
# exefile=$codepath"/bin/astron_fr_mglur_rel";
# exefile=$codepath"/bin/astron_casensor";
# ------------------
# expdir="dhpg100000nM2s"
# expdir="ap1to100dHz30s0noise"
# expdir="glu0to1000000nM2s"
# expdir="dhpg10to1000000nM50s"
expdir="cacyt10to1000000nM50shighres";
# ----------------
mkdir $datapath/$expdir
#--------------------
resultdir="run"
logdir="log"
run_script=$codepath"/src/utility/pbs_script.sh"
pbspriority=1023;
pbsjcmax=1000
# ----------------
## Call to make
# make executables and library
make -C $codepath/lib/new_insilico/ clean
make -C $codepath/lib/new_insilico/
make -C $codepath/ clean_all
make -C $codepath/
# ------------------
make -C $codepath/ clean_astrocyte
make -C $codepath/ clean_atp_synapse
make -C $codepath/ clean_glu_synapse
make -C $codepath/ clean_synapses

make -C $codepath/ astrocyte
make -C $codepath/ atp_synapse
make -C $codepath/ glu_synapse
make -C $codepath/ synapses
#-------------------
# remove any existing cells
rm -f $datapath/$expdir/astrocyte*.isf
# create cell groups
# create control group
cp $codepath/input/astrocyte/astrocyte_complete.isf $datapath/$expdir/astrocyte_ctrl.isf
# create adpmca group
cp $datapath/$expdir/astrocyte_ctrl.isf $datapath/$expdir/astrocyte_adpmca.isf
sed -i "s/^pmca_kb1[ :]*[0-9e.-]*,/pmca_kb1 : 60,/g" $datapath/$expdir/astrocyte_adpmca.isf
# create admglur group
cp $datapath/$expdir/astrocyte_ctrl.isf $datapath/$expdir/astrocyte_admglur.isf
sed -i "s/^mglur_hill_v_max[ :]*[0-9e.-]*,/mglur_hill_v_max : 1.4e-06,/g" $datapath/$expdir/astrocyte_admglur.isf
sed -i "s/^mglur_hill_k_diss[ :]*[0-9e.-]*,/mglur_hill_k_diss : 3.0e-06,/g" $datapath/$expdir/astrocyte_admglur.isf
# create admglurpmca group
cp $datapath/$expdir/astrocyte_ctrl.isf $datapath/$expdir/astrocyte_admglurpmca.isf
sed -i "s/^pmca_kb1[ :]*[0-9e.-]*,/pmca_kb1 : 60,/g" $datapath/$expdir/astrocyte_admglurpmca.isf
sed -i "s/^mglur_hill_v_max[ :]*[0-9e.-]*,/mglur_hill_v_max : 1.4e-06,/g" $datapath/$expdir/astrocyte_admglurpmca.isf
sed -i "s/^mglur_hill_k_diss[ :]*[0-9e.-]*,/mglur_hill_k_diss : 3.0e-06,/g" $datapath/$expdir/astrocyte_admglurpmca.isf
# create synapses
cp $codepath/input/synapse/synapses_complete.isf $datapath/$expdir/synapses.isf
# -----------------------
# copy dynamic parameters to exp dir
rm -rf $datapath/$expdir/dynparams
mkdir $datapath/$expdir/dynparams
cp -r $codepath/dynparams/*.* $datapath/$expdir/dynparams/
#-------------------------
trialstart=1;
trialstop=10;
treatgroups[0]="ctrl";
treatgroups[1]="admglur";
treatgroups[2]="adpmca";
treatgroups[3]="admglurpmca";
# remove run folder
rm -rf $datapath/$expdir/$resultdir
# create run folder
mkdir $datapath/$expdir/$resultdir
# remove log folder
rm -rf $datapath/$expdir/$logdir
# create log folder
mkdir $datapath/$expdir/$logdir
# create group folders
for group in ${treatgroups[@]};
do
    mkdir $datapath/$expdir/$resultdir/${group}
done;
# dynname1="dhpg" # dhpg100000nM2s
# dynname1="ap" # ap1tp1000dHz30s
# dynname1="glu"		       # glu1to1000000nM2s
dynname1="cacyt"	       # cacyt10to1000000nM30s
# dynname1="dhpg"	       # dhpg10to1000000nM30s
# ----------------
 # expgroups1=(100000); # dhpg100000nM2s
# expgroups1=(1 2 3 4 5 6 7 8 9 10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000); # ap1to1000dHz30s
# expgroups1=(1000)
# expgroups1=(100 200 300 400 500 600 700 800 900 1000);
# expgroups1=(0 1 10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 20000 30000 40000 50000 60000 70000 80000 90000 100000); # cacyt/dhpg
# expgroups2=(2 10 30 60 90 120);
expgroups1=(10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 20000 30000 40000 50000 60000 70000 80000 90000 100000 200000 300000 400000 500000 600000 700000 800000 900000 1000000); # cacyt/dhpg
# expgroup=($(seq 0 10 2000));
#---------------------------
# despatches an individual experiment (treatment x experiment groups) containing N trials
for treat in ${treatgroups[@]};
do
    for exp1 in ${expgroups1[@]};
    do
	neuronfile=$datapath/$expdir"/astrocyte_"${treat}".isf";
	synapsefile=$datapath/$expdir"/synapses.isf";
	# for exp2 in ${expgroups2[@]};
	# do
	# dynparamfile=$datapath/$expdir"/dynparams/dynparams_"${dynname1}${exp1}"nM2s.isfdp"; # dhpg100000nM2s
	# dynparamfile=$datapath/$expdir"/dynparams/dynparams_"${dynname1}${exp1}"dHz30s.isfdp"; # ap1to100dHz30s
	dynparamfile=$datapath/$expdir"/dynparams/dynparams_"${dynname1}${exp1}"nM50s.isfdp"; # glu0to1000000nM2s
	# ------------------
	# outputfile=$datapath/$expdir"/${resultdir}/${treat}/astrocyte_"${dynname1}${exp1}"nM2s_"${treat}".csv";# dhpg100000nM2s
	# outputfile=$datapath/$expdir"/${resultdir}/${treat}/astrocyte_"${dynname1}${exp1}"dHz30s_"${treat}".csv";# ap1to1000dHz30s
	outputfile=$datapath/$expdir"/${resultdir}/${treat}/astrocyte_"${dynname1}${exp1}"nM50s_"${treat}".csv"; # glu0to1000000nM2s
	# -----------------
	logpath=$datapath/$expdir"/log/"
	# logfile_data=$datapath/$expdir"/log/astrocyte_"${dynname1}${exp1}"dHz30s_"${treat}"_data.log";# ap1to1000dHz30s 
	# logfile_pbs=$datapath/$expdir"/log/astrocyte_"${dynname1}${exp1}"dHz30s_"${treat}"_pbs.log";# ap1to1000dHz30s
	logfile_data=$datapath/$expdir"/log/astrocyte_"${dynname1}${exp1}"nM50s_"${treat}"_data.log"; # glu0to1000000nM2s
	logfile_pbs=$datapath/$expdir"/log/astrocyte_"${dynname1}${exp1}"nM50s_"${treat}"_pbs.log"; # glu0to1000000nM2s
	# logfile=`echo -n $outputfile | sed "s/.csv/.log/g"`
	# -----------------
	# Copy input and dynamic file to the logfile
	cat $neuronfile >> $logfile_data
	cat $synapsefile >> $logfile_data
	# --------------------------
	echo -e neuronfile:\\t$neuronfile >> $logfile_data
	echo -e synapsefile:\\t$synapsefile >> $logfile_data
	echo -e dynparamfile:\\t$dynparamfile >> $logfile_data 
	echo -e outputfile:\\t$outputfile >> $logfile_data
	echo -e logfile_data:\\t$logfile_data >> $logfile_data
	echo -e logfile_pbs:\\t$logfile_pbs >> $logfile_data
	# ==============================
	# multiple machines
	# remove the .extension from filenames
	outputfile_pf=$(echo "$outputfile" | sed -e 's/\.[a-z]*//g')
	dynparamfile_pf=$(echo "$dynparamfile" | sed -e 's/\.[a-z]*//g')
	# get filename without path and without .extension
	outputfile_pf=$(echo "$outputfile_pf" | sed -e 's,^[^ ]*/,,')
	dynparamfile_pf=$(echo "$dynparamfile_pf" | sed -e 's,^[^ ]*/,,')
	# extract suffix from filename with full path
	outputfile_sf=$(echo "$outputfile" | sed -e 's/.*\.//')
	dynparamfile_sf=$(echo "$dynparamfile" | sed -e 's/.*\.//')
	# extract full path from filename with full path
	outputfile_ph=$(echo "$outputfile" | sed -e 's/\(.*\)\/.*/\1/')/
	dynparamfile_ph=$(echo "$dynparamfile" | sed -e 's/\(.*\)\/.*/\1/')/ 
	# ---------------------
	exeFile=$exefile
	# ---------------------
	neuronFile=$neuronfile
	# ---------------------
	outputFile_ph=$outputfile_ph
	# outputFile_pf=$outputfile_pf
	outputFile_sf=$outputfile_sf
	# ----------------------
	synapseFile=$synapsefile
	# ---------------------
	dynparamFile=$dynparamfile
	# ---------------------
	dynparamfile_ph=$dynparamfile_ph
	dynparamFile_pf=$dynparamfile_pf
	dynparamFile_sf=$dynparamfile_sf
	# ---------------------
	pbsjobid=$(qsub -joe -mbae -Manupgp@gmail.com -p${pbspriority} -o${logpath} -J${trialstart}-${trialstop}:1 -v exeFile=${exefile},neuronFile=${neuronfile},outputFile_ph=${outputfile_ph},outputFile_pf=${outputfile_pf},outputFile_sf=${outputfile_sf},synapseFile=${synapsefile},dynparamFile=${dynparamfile} ${run_script})
	# pbsjobid=$(qsub -joe -mabe -Manupgp@iiserpune.ac.in -p${pbspriority} -o${logPath} -v exeFile=${exefile},neuronFile=${neuronfile},outputFile_ph=${outputfile_ph},outputFile_pf=${outputfile_pf},outputFile_sf=${outputfile_sf},synapseFile=${synapsefile},dynparamFile=${dynparamfile} ${run_script}) # ! NOT BATCH JOB !
	# pbsjobid=$(qsub -joe -mabe -Manupgp@iiserpune.ac.in -p${pbspriority} -o${logPath} -J${trialstart}-${trialstop}:1 -v exeFile=${exefile},neuronFile=${neuronfile},outputFile_ph=${outputfile_ph},outputFile_pf=${outputfile_pf},outputFile_sf=${outputfile_sf},synapseFile=${synapsefile},dynparamFile_ph=${dynparamfile_ph},dynparamFile_pf=${dynparamfile_pf},dynparamFile_sf=${dynparamfile_sf} ${run_script})
	# -----------------
	# check %pbsjobcompleted and despatch remaining jobs
	# percentdone=0
	# echo Starting pbsjob: $pbsjobid >> $logfile_pbs
	# while [[ "$percentdone" -lt 90 ]]; do
	#     sleep 60
	#     percentdone=`qstat -p $pbsjobid | grep rosalind | awk 'BEGIN{}; {print $4 }; END{}'`
	#     echo pbs_job: $pbsjobid $percentdone% finished >> $logfile_pbs
	# done
	# get num of jobs processes submitted
	# get all the running jobs
	# pbsjrun=$(qstat -uanup | grep "B" | cut -d"." -f1)
	# if [[ -z "$pbsjrun" ]]; then
	#     pbsjcrun=0;
	# else
	#     pbsjcrun=${#pbsjrun[@]};
	# fi;
	# # get all the qued jobs
	# pbsjque=$(qstat -uanup | grep "Q" | cut -d"." -f1)
	# if [[ -z "$pbsjque" ]]; then
	#     pbsjcque=0;
	# else
	#     pbsjcque=${#pbsjque[@]};
	# fi;
	# pbsjctot=$(($pbsjcrun+$pbsjcque));
	# echo $pbsjobid
	# echo $pbsjcrun $pbsjcque $pbsjctot;
	# # if morethan $pbsjcmax in $pbjobq; then wait
	# while [[ "$pbsjctot" -gt "$pbsjcmax" ]]; do
	#     sleep 60;
	# done
	   # ---------------------
    done
done

