#! bin/bash
# Simulation run script single cpu (desktop) / multiple cpr(pbs)
# ----------------
# Assign filenames to variables
# codepath="/Users/macbookair/goofy/codes/astron";
codepath="/home/anup/goofy/codes/astron";
localdatapath="/home/anup/data";
# localdatapath="/media/anup/data/data/astron/raw/astrocyte";
#pbsdatapath="/storage/anup/data/astron/raw/astrocyte";
# ------------------
datapath=$localdatapath;
#datapath=$pbsdatapath;
# ------------------
exefile=$codepath"/bin/astron_main";
# exefile=$codepath"/bin/astron_vr";
# exefile=$codepath"/bin/astron_fr_mglur_rel";
# exefile=$codepath"/bin/astron_casensor";
# ------------------
expdir="glu1to100000nM2s"
#--------------------
resultdir="run"
logdir="log"
run_script=$codepath"/src/utility/insilico_single_processor_multiple_runs.sh";
# ----------------
## Call to make
make -C $codepath/ clean
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
# ------------------------
trialstart=1;
trialstop=1;
treatgroups[0]="ctrl";
# treatgroups[1]="admglur";
# treatgroups[2]="adpmca";
# treatgroups[3]="admglurpmca";
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
# dynname1="ap10s"
# dynname2="_trial"
# dynname1="dhpg2sdhpg"
# dynname2="_trial"
# dynname1="caer2s"
# dynname2="_trial"
# dynname1="cacyt50s"
# dynname2="_trial"
expgroups1=(100000);
#expgroups1=(0);
# expgroup=(5000);
# expgroup=(1 5 10);
# expgroups1=(100 200 300 400 500 600 700 800 900 1000);
# expgroups1=(0 1 10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 20000 30000 40000 50000 60000 70000 80000 90000 100000); # cacyt/dhpg
# expgroups2=(2 10 30 60 90 120);
# expgroups1=(0 1 10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 20000 30000 40000 50000 60000 70000 80000 90000 100000 200000 300000 400000 500000 600000 700000 800000 900000 1000000); # cacyt/dhpg
# expgroup=(200000 300000 400000 500000 600000 700000 800000 900000 1000000); # cacyt/dhpg
# expgroups1=(1 2 3 4 5 6 7 8 9 10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000); # ap
# expgroups1=(1000); # ap
# expgroup=(50000 60000 70000 80000 90000 100000);
# expgroups1=(100);
# expgroup=(1 2 3 4 5 6 7 8 9 10);
# expgroup=(0,01 0,05 0,1);
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
	# dynparamfile=$datapath/$expdir"/dypars/dynparams_"${dynname1}${exp1}"nM.isfdp";  # dr_pmca
	# dynparamfile=$datapath/$expdir"/dypars/dynparams_"${dynname1}${exp1}"dHz"${dynname2}".isfdp";  # mutualinfouni
	# dynparamfile=$datapath/$expdir"/dypars/dynparams_"${dynname1}${exp1}"dHz"${dynname2}".isfdp";  # mutualinforep
	# outputfile=$datapath/$expdir"/${resultdir}/${treat}/astrocyte_"${dynname1}${exp1}"dHz_"${treat}".csv"; 
	# dynparamfile=$datapath/$expdir"/dypars/dynparams_"${dynname}${exp2}"s"${exp1}"nM.isfdp";
	# dynparamfile=$datapath/$expdir"/dypars/dynparams_"${dynname1}${exp1}"nM.isfdp";
	# dynparamfile=$datapath/$expdir"/dypars/dynparams_ap30s"${exp1}"dHz.isfdp";
	dynparamfile=$datapath/$expdir"/dynparam/dynparams_glu"${exp1}"nM2s.isfdp";
	# dynparamfile=$datapath/$expdir"/dypars/dynparams_cacyt10s"${exp}"nM.isfdp";
	# outputfile=$datapath/$expdir"/${resultdir}/${treat}/astrocyte_"${dynname1}${exp1}"nM_"${treat}".csv";
	# outputfile=$datapath/$expdir"/${resultdir}/${treat}/astrocyte_ap30s"${exp1}"dHz_"${treat}".csv";
	outputfile=$datapath/$expdir"/${resultdir}/${treat}/astrocyte_glu"${exp1}"nM2s_"${treat}".csv";
	# outputfile=$datapath/$expdir"/${resultdir}/${treat}/astrocyte_"${dynname1}${exp1}"nM_"${treat}".csv"; # dr_pmca
	# outputfile=$datapath/$expdir"/${resultdir}/${treat}/astrocyte_"${dynmame}${exp2}"s"${exp1}"nM_"${treat}".csv";
	# -----------------
	logfile=`echo -n $outputfile | sed "s/.csv/.log/g"`
	echo $logfile
	logPath=$datapath/$resultdir"/log/"
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
	# ==============================
	# Single machine
	echo "**** Going to run the script****"
	# bash $run_script --exec $exefile -n $neuronfile -o $outputfile -s $synapsefile -d $dynparamfile --begin $trialstart --stop $trialstop
	bash $run_script --exec $exefile -n $neuronfile -o $outputfile -s $synapsefile -d $dynparamfile --begin $trialstart --stop $trialstop >> $logfile 2>&1
	# done
    done
done
