#! bin/bash
# Simulation run script single cpu (desktop) / multiple cpr(pbs)
# ----------------
# Assign filenames to variables
codepath="/home/anup/goofy/projects/codes/astron";
localdatapath="/mnt/mount1/data/astron/raw/astrocyte";
pbsdatapath="/storage/anup/data/astron/raw/astrocyte";
# ------------------
datapath=$pbsdatapath;
# ------------------
exefile=$codepath"/bin/astron_calcium";
# ------------------
# expdir="dr_pmca"
expdir="fr_mglur"
datadir="run"
logdir="log"
local_run_script=$codepath"/src/utility/insilico_single_processor_multiple_runs.sh";
pbs_run_script=$codepath"/src/utility/pbs_script.sh"
pbspriority=1000;
# ----------------
## Call to make
make -C $codepath/ clean
make -C $codepath/ 
# ------------------
make -C $codepath/ clean_astrocyte
make -C $codepath/ clean_atp_synapse
make -C $codepath/ clean_glu_synapse
make -C $codepath/ clean_synapse_all

make -C $codepath/ astrocyte
make -C $codepath/ atp_synapse
make -C $codepath/ glu_synapse
make -C $codepath/ synapse_all
#-------------------
# create control group
cp $codepath/input/astrocyte/astrocyte_all.isf $datapath/$expdir/astrocyte_all_ctrl.isf
cp $codepath/input/synapse/atp_synapse_all.isf $datapath/$expdir/atp_synapse_all.isf
cp $codepath/input/synapse/glutamate_synapse_all.isf $datapath/$expdir/glutamate_synapse_all.isf
cp $codepath/input/synapse/synapses_all.isf $datapath/$expdir/synapses_all.isf
#-------------------------
# create other groups
rm -f $datapath/$expdir/astrocyte_all_adpmca.isf
cp $datapath/$expdir/astrocyte_all_ctrl.isf $datapath/$expdir/astrocyte_all_adpmca.isf
sed -i "s/^pmca_kb1[ :]*[0-9e.-]*,/pmca_kb1 : 60,/g" $datapath/$expdir/astrocyte_all_adpmca.isf
# sed -i "s/^pmca_kf3[ :]*[0-9e.-]*,/pmca_kf3 : 50,/g" $datapath/$expdir/astrocyte_all_adpmca.isf
#------
rm -f $datapath/$expdir/astrocyte_all_admglur.isf
cp $datapath/$expdir/astrocyte_all_ctrl.isf $datapath/$expdir/astrocyte_all_admglur.isf
sed -i "s/^mglur_hill_v_max[ :]*[0-9e.-]*,/mglur_hill_v_max : 1.4e-06,/g" $datapath/$expdir/astrocyte_all_admglur.isf
sed -i "s/^mglur_hill_k_diss[ :]*[0-9e.-]*,/mglur_hill_k_diss : 3.0e-06,/g" $datapath/$expdir/astrocyte_all_admglur.isf
#------
rm -f $datapath/$expdir/astrocyte_all_admglurpmca.isf
cp $datapath/$expdir/astrocyte_all_ctrl.isf $datapath/$expdir/astrocyte_all_admglurpmca.isf
sed -i "s/^pmca_kb1[ :]*[0-9e.-]*,/pmca_kb1 : 60,/g" $datapath/$expdir/astrocyte_all_admglurpmca.isf
# sed -i "s/^pmca_kf3[ :]*[0-9e.-]*,/pmca_kf3 : 50,/g" $datapath/$expdir/astrocyte_all_adpmca.isf
# ------------------
sed -i "s/^mglur_hill_v_max[ :]*[0-9e.-]*,/mglur_hill_v_max : 1.4e-06,/g" $datapath/$expdir/astrocyte_all_admglurpmca.isf
sed -i "s/^mglur_hill_k_diss[ :]*[0-9e.-]*,/mglur_hill_k_diss : 3.0e-06,/g" $datapath/$expdir/astrocyte_all_admglurpmca.isf
# ------------------------
# remove run folder & create folders of individual groups
rm -rf $datapath/$expdir/$datadir
mkdir $datapath/$expdir/$datadir
rm -rf $datapath/$expdir/$logdir
mkdir $datapath/$expdir/$logdir
mkdir $datapath/$expdir/$datadir"/ctrl"
mkdir $datapath/$expdir/$datadir"/admglur"
mkdir $datapath/$expdir/$datadir"/adpmca"
mkdir $datapath/$expdir/$datadir"/admglurpmca"
# -------------------------
trialstart=1;
trialstop=10000;
# trialstop=10;
treatgroup[0]="ctrl";
# treatgroup[1]="admglur";
# treatgroup[2]="adpmca";
# treatgroup[3]="admglurpmca";
# expgroup=(100000);
# expgroup=(5000);
expgroup=(1 5 10);
# expgroup=(100 200 300 400 500 600 700 800 900 1000);
# expgroup=(0 1 10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 20000 30000 40000 50000 60000 70000 80000 90000 100000); # cacyt/dhpg
# expgroup=(0 1 10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 20000 30000 40000 50000 60000 70000 80000 90000 100000 200000 300000 400000 500000 600000 700000 800000 900000 1000000); # cacyt/dhpg
# expgroup=(200000 300000 400000 500000 600000 700000 800000 900000 1000000); # cacyt/dhpg
#expgroup=(1 2 3 4 5 6 7 8 9 10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000); # ap
# expgroup=(50000 60000 70000 80000 90000 100000);
# expgroup=(1);
# expgroup=(0 1 10);
# expgroup=(0,01 0,05 0,1);
# expgroup=($(seq 0 10 2000));
#---------------------------
for treat in ${treatgroup[@]};
do
    for exp in ${expgroup[@]};
    do
	neuronfile=$datapath/$expdir"/astrocyte_all_"${treat}".isf";
	synapsefile=$datapath/$expdir"/synapses_all.isf";
	# dynparamfile=$datapath/$expdir"/dypars/dynparams_cacyt100s"${exp}"nM.isfdp";
	# dynparamfile=$datapath/$expdir"/dypars/dynparams_dhpg2s"${exp}"nM.isfdp";
	dynparamfile=$datapath/$expdir"/dypars/dynparams_ap30s"${exp}"dHz.isfdp";
	# outputfile=$datapath/$expdir"/${datadir}/${treat}/astrocyte_dhpg2s"${exp}"nM_"${treat}".csv";
	outputfile=$datapath/$expdir"/${datadir}/${treat}/astrocyte_ap30s"${exp}"dHz_"${treat}".csv";
	logfile=`echo -n $outputfile | sed "s/.csv/.log/g" -`
	logPath=$datapath/$expdir"/log/"
	# -----------------
	# Copy input and dynamic file to the logfile
	cat $neuronfile > $logfile
	cat $synapsefile >> $logfile
	echo "----------------------"
	echo neuronfile = $neuronfile
	echo synapsefile = $synapsefile
	echo dynparamfile = $dynparamfile
	echo outputfile = $outputfile
	echo logfile = $logfile

	# -----------------------
	# Single machine
	# bash $local_run_script --exec $exefile -n $neuronfile -o $outputfile -s $synapsefile -d $dynparamfile --begin $trialstart --stop $trialstop &>> $logfile
	# -----------------------
	# multiple machines
	# remove the .extension from outputfile
	outputfile_pf=$(echo "$outputfile" | sed -e 's/\.[a-z]*//g')
	# get filename without path and without .extension
	outputfile_pf=$(echo "$outputfile_pf" | sed -e 's,^[^ ]*/,,')
	# extract suffix from filename with full path
	outputfile_sf=$(echo "$outputfile" | sed -e 's/.*\.//')
	# extract full path from filename with full path
	outputfile_ph=$(echo "$outputfile" | sed -e 's/\(.*\)\/.*/\1/')/
	# ---------------------
	exeFile=$exefile
	neuronFile=$neuronfile
	outputFile_ph=$outputfile_ph
	outputFile_pf=$outputfile_pf
	outputFile_sf=$outputfile_sf
	synapseFile=$synapsefile
	dynparamsFile=$dynparamfile
	qsub -joe -mabe -Manupgp@iiserpune.ac.in -p${pbspriority} -o${logPath} -J${trialstart}-${trialstop}:1 -v exeFile=${exefile},neuronFile=${neuronfile},outputFile_ph=${outputfile_ph},outputFile_pf=${outputfile_pf},outputFile_sf=${outputfile_sf},synapseFile=${synapsefile},dynparamsFile=${dynparamfile} ${pbs_run_script}
	# ---------------------
    done
done
