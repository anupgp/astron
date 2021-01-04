#! /bin/bash
# Simulation run script for cpu cluster (multiple processors)
# ----------------
codepath="/home/anup/astron";
pbsdatapath="/storage/nishant1/anup/data/astron/raw/astrocyte";
expdir="dhpg100000nM2s"
mkdir $datapath/$expdir
# ----------------
## Call to make
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
# create control group
cp $codepath/input/astrocyte/astrocyte_all.isf $datapath/$expdir/astrocyte_ctrl.isf
# cp $codepath/input/synapse/atp_synapse_all.isf $datapath/$expdir/atp_synapse_all.isf
# cp $codepath/input/synapse/glutamate_synapse_all.isf $datapath/$expdir/glutamate_synapse_all.isf
cp $codepath/input/synapse/synapses_complete.isf $datapath/$expdir/synapses.isf
#-------------------------
# create other groups
rm $datapath/$expdir/astrocyte_all_adpmca.isf
cp $datapath/$expdir/astrocyte_all_ctrl.isf $datapath/$expdir/astrocyte_adpmca.isf
sed -i "s/^pmca_kb1[ :]*[0-9e.-]*,/pmca_kb1 : 60,/g" $datapath/$expdir/astrocyte_adpmca.isf
#------
rm $datapath/$expdir/astrocyte_all_admglur.isf
cp $datapath/$expdir/astrocyte_all_ctrl.isf $datapath/$expdir/astrocyte_admglur.isf
sed -i "s/^mglur_hill_v_max[ :]*[0-9e.-]*,/mglur_hill_v_max : 1.4e-06,/g" $datapath/$expdir/astrocyte_admglur.isf
sed -i "s/^mglur_hill_k_diss[ :]*[0-9e.-]*,/mglur_hill_k_diss : 3.0e-06,/g" $datapath/$expdir/astrocyte_admglur.isf
#------
rm $datapath/$expdir/astrocyte_all_admglurpmca.isf
cp $datapath/$expdir/astrocyte_all_ctrl.isf $datapath/$expdir/astrocyte_admglurpmca.isf
sed -i "s/^pmca_kb1[ :]*[0-9e.-]*,/pmca_kb1 : 60,/g" $datapath/$expdir/astrocyte_admglurpmca.isf
sed -i "s/^mglur_hill_v_max[ :]*[0-9e.-]*,/mglur_hill_v_max : 1.4e-06,/g" $datapath/$expdir/astrocyte_admglurpmca.isf
sed -i "s/^mglur_hill_k_diss[ :]*[0-9e.-]*,/mglur_hill_k_diss : 3.0e-06,/g" $datapath/$expdir/astrocyte_admglurpmca.isf
# ------------------------
# copy dynamic parameters to exp dir
rm -rf $datapath/$expdir/dynparams
mkdir $datapath/$expdir/dynparams
cp -r $codepath/dynparams $datapath/$expdir/dynparams
# remove run folder & create folders of individual groups
rm -r $datapath/$expdir"/run"
mkdir $datapath/$expdir"/run"
mkdir $datapath/$expdir"/run/ctrl"
mkdir $datapath/$expdir"/run/admglur"
mkdir $datapath/$expdir"/run/adpmca"
mkdir $datapath/$expdir"/run/admglurpmca"
# -------------------------
# Assign filenames to variables
exefile=$codepath"/bin/astron";
pbs_script=$codepath"/src/utility/pbs_script.sh"
# -------------------------
trialstart=1;
trialstop=315;
# trials=($(seq $trialstart 1 $trialstop));
treatgroup[0]="ctrl";
treatgroup[1]="adpmca";
treatgroup[2]="admglur";
treatgroup[3]="adpmcamglur";
# treatgroup[1]="alzheimB";
# treatgroup[2]="alzheimC";
# treatgroup[3]="test100ves";
expgroup=(100000);
# expgroup=(5000);
# expgroup=(100 200 300 400 500 600 700 800 900 1000);
# expgroup=(0 1 10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 20000 30000 40000 50000 60000 70000 80000 90000 100000);
# expgroup=(1 2 3 4 5 6 7 8 9 10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000);
# expgroup=(50000 60000 70000 80000 90000 100000);
# expgroup=(1);
# expgroup=(0 1 10);
# expgroup=(0,01 0,05 0,1);
# expgroup=($(seq 0 10 2000));
for treat in ${treatgroup[@]};
do
    for exp in ${expgroup[@]};
    do
	neuronfile=$datapath/$expdir"/astrocyte_all_"${treat}".isf";
	synapsefile=$datapath/$expdir"/synapses_all.isf";
	dynparamfile=$datapath/$expdir"/dypars/dynparams_dhpg2s"${exp}"nM.isfdp";
	outputfile=$datapath/$expdir"/run/${treat}/astrocyte_dhpg2s"${exp}"nM_"${treat}".csv";
	logPath=$datapath/$expdir"/log/"
	# remove the .extension
	outputfile_pf=$(echo "$outputfile" | sed -e 's/\.[a-z]*//g')
	# get filename without path and without .extension
	outputfile_pf=$(echo "$outputfile_pf" | sed -e 's,^[^ ]*/,,')
	# extract suffix from filename with full path
	outputfile_sf=$(echo "$outputfile" | sed -e 's/.*\.//')
	# extract full path from filename with full path
	outputfile_ph=$(echo "$outputfile" | sed -e 's/\(.*\)\/.*/\1/')/
	logfile=`echo -n $outputfile | sed "s/.csv/.log/g" -`
	# Copy input and dynamic file to the logfile
	cat $neuronfile > $logfile
	cat $synapsefile >> $logfile
	echo "----------------------"
	echo neuronfile = $neuronfile
	echo synapsefile = $synapsefile
	echo dynparamfile = $dynparamfile
	echo outputfile = $outputfile
	echo logfile = $logfile

	# ---------------
	exeFile=$exefile
	neuronFile=$neuronfile
	outputFile_ph=$outputfile_ph
	outputFile_pf=$outputfile_pf
	outputFile_sf=$outputfile_sf
	synapseFile=$synapsefile
	dynparamsFile=$dynparamfile
	# --------------
	qsub -joe -mabe -Manupgp@iiserpune.ac.in -o${logPath} -J${trialstart}-${trialstop}:1 -v exeFile=${exefile},neuronFile=${neuronfile},outputFile_ph=${outputfile_ph},outputFile_pf=${outputfile_pf},outputFile_sf=${outputfile_sf},synapseFile=${synapsefile},dynparamsFile=${dynparamfile} ${pbs_script}
    done
done
