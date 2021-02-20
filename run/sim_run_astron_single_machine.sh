#! bin/bash
# Simulation run script single cpu (desktop) / multiple cpr(pbs)
# ----------------
# Assign filenames to variables
# codepath="/home/anup/goofy/codes/astron"; # arg1: codepath
# datapath="/home/anup/data";		  # arg2: datapath
# execfile=$codepath"/bin/astron_main"; # arg3: execfile with path
# expfolder="glu1to100000nM2s"	     # arg4: expfolder
# trialstart=1;			     # arg5: trialstart
# trialstop=1;			     # arg6: trialstop
# expgroups[0]="ctrl";		     # arg7: exp groups
# stimgroupname1="ap10s"	      # arg8: name (prefix) of the stim group1
# stimgroupvalue1=""	      # arg9: value of the stim group1
# ------------------
# print help message
usage() {
    echo "Usage: $0 [-codepath CODEPATH] [-datapath DATAPATH] [-execfile EXECFILE] [-expfolder EXPFOLDER] [-trialstart TRIALSTART] [-trialstop TRIALSTOP] [-expgroups EXPGROUPS: space seperated string of group names] [-stimname1 STIMNAME1] [-stimvalues1 STIMVALUES1: space seperated string of values]" 1>&2
}
# exit with error
exit_abnormal() {
    usage
    exit 1
}
# ------------------
# parse all the arguments
if [[ ! $@ =~ ^\-.+ ]]
then
    echo "No options passed!";
    usage
    exit 1
fi
# -------------------
# decalare an array of options that accepts a single value
declare -a argarrayset1=("codepath" "datapath" "execfile" "trialstart" "trialstop" "stimprefix1" "stimsuffix1" "expfolder")
# copy all passed arguments into an array
argspassed=( "$@" )
for arg in ${argarrayset1[@]}; do
    arglong=--$arg
    for i in "${!argspassed[@]}"; do
    	if [[ ${argspassed[i]} == $arglong ]]; then
	    eval $arg=${argspassed[i+1]}
	fi
    done
done
# -------------------
# declare an array of options that accepts array values
declare -a argarrayset2=("expgroups stimvalues1")
for arg in ${argarrayset2[@]}; do
    arglong=--$arg
    for i in "${!argspassed[@]}"; do
    	if [[ ${argspassed[i]} == $arglong ]]; then
	    read -a arr <<< ${argspassed[i+1]}
	    # for elem in ${arr[@]}; do
	    # 	echo $elem
	    # done
	    eval "declare -a ${arg}=\${arr[@]}"
	fi
    done
done
# check if any of the arguments are empty and print error with usage
for arg in ${argarrayset1[@]}; do
    if [ -z "${!arg}" ]; then
	echo "ERROR: one or more arguments are missing"
	usage
	exit 1
    fi
done
# print all the single value arguments passed
for arg in ${argarrayset1[@]}; do
    printf "%s:\t %s\n" ${arg} ${!arg} 
done
# print all the array arguments passed
printf "%s:\t" "expgroups"
for val in ${expgroups[@]}; do
    printf "%s " $val
done
printf "\n"
printf "%s:\t" "stimvalues1"
for val in ${stimvalues1[@]}; do
    printf "%s " $val
done
echo
# -----------------
# prefixed variables
outputfolder="output"
logfolder="log"
paramfolder="params"
stimparamsfolder="stimparams"
run_script=$codepath"/run/insilico_single_processor_multiple_runs.sh";
# ----------------
## Multiple calls to 'make' command creates the main parameter files 
make -C $codepath/ clean
make -C $codepath/ 
# ------------------
make -C $codepath/ clean_astrocyte
make -C $codepath/ clean_atp_synapse
make -C $codepath/ clean_glu_synapse
make -C $codepath/ clean_synapses
# ------------------
make -C $codepath/ astrocyte
make -C $codepath/ atp_synapse
make -C $codepath/ glu_synapse
make -C $codepath/ synapses
# #-------------------
# # remove any existing cells
# cheak if datpath & expfolder exists
if [[ ! -d $datapath ]]; then
    printf "folder: %s does not exist\n" ${datapath}
    exit 1
fi
if [[ ! -d $datapath/$expfolder ]]; then
    printf "folder: %s does not exist\n" $datapath/$expfolder
fi
# -----------------
# create outputfolder
rm -rf $datapath/$expfolder/$outputfolder
if [[ ! -e $datapath/$expfolder/$outputfolder ]]; then
    printf "Creating folder: %s\n" $datapath/$expfolder/$outputfolder
    mkdir $datapath/$expfolder/$outputfolder
elif
    [[ ! -d $datapath/$expfolder/$outputfolder ]]; then
    echo "WARN: a file exists with the name of $datapath/$expfolder/$outputfolder" 
    exit 1
fi
# -----------------
# create paramfolder
rm -rf $datapath/$expfolder/$paramfolder
if [[ ! -e $datapath/$expfolder/$paramfolder ]]; then
    printf "Creating folder: %s\n" $datapath/$expfolder/$paramfolder
    mkdir $datapath/$expfolder/$paramfolder
elif
    [[ ! -d $datapath/$expfolder/$paramfolder ]]; then
    echo "WARN: a file exists with the name of $datapath/$expfolder/$paramfolder" 
    exit 1
fi
# -----------------
# create logfolder
rm -rf $datapath/$expfolder/$logfolder
if [[ ! -e $datapath/$expfolder/$logfolder ]]; then
    printf "Creating folder: %s\n" $datapath/$expfolder/$logfolder
    mkdir $datapath/$expfolder/$logfolder
elif
    [[ ! -d $datapath/$expfolder/$logfolder ]]; then
    echo "WARN: a file exists with the name of $datapath/$expfolder/$logfolder" 
    exit 1
fi
# -----------------
# create expgroup folders
for expgroup in ${expgroups[@]}; do
    if [[ ! -e $datapath/$expfolder/$outputfolder/$expgroup ]]; then
	printf "Creating folder: %s\n" $datapath/$expfolder/$outputfolder/$expgroup
	mkdir $datapath/$expfolder/$outputfolder/$expgroup
    # elif
    # 	[[ ! -d $datapath/$expfolder/$outputfolder/$expgroup ]]; then
    # 	echo "WARN: a file exists with the name of $datapath/$expfolder/$outputfolder/$expgroup" 
    # 	exit 1
    fi
done		
# -----------------
# create control group parameter file
cp $codepath/input/astrocyte/astrocyte_complete.isf $datapath/$expfolder/$paramfolder/astrocyte_ctrl.isf
# create adpmca group parameter file
cp $datapath/$expfolder/$paramfolder/astrocyte_ctrl.isf $datapath/$expfolder/$paramfolder/astrocyte_adpmca.isf
sed -i "s/^pmca_kb1[ :]*[0-9e.-]*,/pmca_kb1 : 60,/g" $datapath/$expfolder/$paramfolder/astrocyte_adpmca.isf # A-beta modify pmca_kb1
# create admglur group parameter file
cp $datapath/$expfolder/$paramfolder/astrocyte_ctrl.isf $datapath/$expfolder/$paramfolder/astrocyte_admglur.isf
sed -i "s/^mglur_hill_v_max_glu[ :]*[0-9e.-]*,/mglur_hill_v_max_glu : 1.4e-06,/g" $datapath/$expfolder/$paramfolder/astrocyte_admglur.isf # A-beta modify mglur_v_max
sed -i "s/^mglur_hill_k_diss_glu[ :]*[0-9e.-]*,/mglur_hill_k_diss_glu : 3.0e-06,/g" $datapath/$expfolder/$paramfolder/astrocyte_admglur.isf # A-beta modify mglur_k_d
# create admglurpmca group parameter file
cp $datapath/$expfolder/$paramfolder/astrocyte_ctrl.isf $datapath/$expfolder/$paramfolder/astrocyte_admglurpmca.isf
sed -i "s/^pmca_kb1[ :]*[0-9e.-]*,/pmca_kb1 : 60,/g" $datapath/$expfolder/$paramfolder/astrocyte_admglurpmca.isf # A-beta modify: pmca_kb1
sed -i "s/^mglur_hill_v_max_glu[ :]*[0-9e.-]*,/mglur_hill_v_max_glu : 1.4e-06,/g" $datapath/$expfolder/$paramfolder/astrocyte_admglurpmca.isf # A-beta modify mglur_v_max
sed -i "s/^mglur_hill_k_diss_glu[ :]*[0-9e.-]*,/mglur_hill_k_diss_glu : 3.0e-06,/g" $datapath/$expfolder/$paramfolder/astrocyte_admglurpmca.isf # A-beta modify mglur_k_d
# create synapse parameter file
cp $codepath/input/synapse/synapses_complete.isf $datapath/$expfolder/$paramfolder/synapses.isf
# ------------------------
for expgroup in ${expgroups[@]};
do
    for stimvalue1 in ${stimvalues1[@]};
    do
	neuronfile=$datapath/$expfolder/$paramfolder/"astrocyte_"${expgroup}".isf";
	synapsefile=$datapath/$expfolder/$paramfolder/"synapses.isf";
	dynamicparamfile=$datapath/$expfolder/$stimparamsfolder/"stimparams_"${stimprefix1}${stimvalue1}${stimsuffix1}".isfdp";
	outputfile=$datapath/$expfolder/$outputfolder/$expgroup/"astrocyte_"${stimprefix1}${stimvalue1}${stimsuffix1}${expgroup}".csv";
	logfile=$datapath/$expfolder/$logfolder/"astrocyte_"${stimprefix1}${stimvalue1}${stimsuffix1}${expgroup}".log";
	# -------------------------
	# Copy input and dynamic file to the logfile
	cat $neuronfile >> $logfile
	cat $synapsefile >> $logfile
	# --------------------------
	printf "neuronfile = \t\t %s \n" $neuronfile
	printf "synapsefile = \t\t %s \n" $synapsefile
	printf "stimparamfile = \t%s \n" $stimparamfile
	printf "outputfile = \t\t %s \n" $outputfile
	printf "logfile = \t\t %s \n" $logfile
	printf "%s\n" "-----------------------------------------"
	# ==============================
	# Single machine
	echo "**** Going to run the script****"
	# bash $run_script --exec $exefile -n $neuronfile -o $outputfile -s $synapsefile -d $dynparamfile --begin $trialstart --stop $trialstop
	bash $run_script --exec $execfile -n $neuronfile -o $outputfile -s $synapsefile -d $dynamicparamfile --begin $trialstart --stop $trialstop 2>&1 >> $logfile
    done
done
