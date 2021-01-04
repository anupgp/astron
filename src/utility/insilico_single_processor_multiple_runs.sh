#! /bin/bash

RED=`tput setaf 1`
GREEN=`tput setaf 2`
YELLOW=`tput setaf 3`
NC='\033[0m' # No Color
BELL=`tput bel`

# initialize an empty array to store pids
jobid=();
# Maximum allowed process at any given time
jobmax=7;		   # 36, 7
# initialize all variables to empty strings
# sleep 10
jobName="";
counter_start="1";
counter_stop="1";

neuronFile="";
outputFile="";
synapseFile="";
extcurrentFile="";
dynamicparamsFile="";

neuronFile_pf="";
outputFile_pf="";
synapseFile_pf="";
extcurrentFile_pf="";
dynamicparamsFile_pf="";

neuronFile_sf="";
outputFile_sf="";
synapseFile_sf="";
extcurrentFile_sf="";
dynamicparamsFile_sf="";

neuronFile_p="";
outputFile_p="";
synapseFile_p="";
extcurrentFile_p="";
dynamicparamsFile_p="";
jobName_p="";

# variables to check if a particular option is passed
neuronFileFound=0;
outputFileFound=0;
programFound=0;
synapseFileFound=0;
extcurrentFileFound=0;
dynparamsFileFound=0;

# Loop for all the passed arguments
argCount=0;
optionFound=0;
for var in "$@"
do
    argCount=$((argCount+1));
    if [ $optionFound  -eq  1 ]; then
	# echo "skipping"
	optionFound=0;
	continue 1;
    fi

    case $var in
	"-n")
	    neuronFile="${@:argCount+1:1}";
	    optionFound=1;
	    neuronFileFound=1;
	    # extract prefix from filename with full path
	    neuronFile_pf=$(echo "$neuronFile" | sed -e 's/\.[a-z]*//g')
	    neuronFile_pf=$(echo "$neuronFile_pf" | sed -e 's,^[^ ]*/,,')
	    # extract suffix from filename with full path
	    neuronFile_sf=$(echo "$neuronFile" | sed -e 's/.*\.//')
	    # extract full path from filename with full path
	    neuronFile_p=$(echo "$neuronFile" | sed -e 's/\(.*\)\/.*/\1/')/
	    ;;
	"-o")
	    echo "pooohoi!"
	    outputFile="${@:argCount+1:1}";
	    optionFound=1;
	    outputFileFound=1;
	    # extract prefix from filename with full path
	    outputFile_pf=$(echo "$outputFile" | sed -e 's/\.[a-z]*//g')
	    outputFile_pf=$(echo "$outputFile_pf" | sed -e 's,^[^ ]*/,,')
	    # extract suffix from filename with full path
	    outputFile_sf=$(echo "$outputFile" | sed -e 's/.*\.//')
	    # extract full path from filename with full path
	    outputFile_p=$(echo "$outputFile" | sed -e 's/\(.*\)\/.*/\1/')/
	    ;;
	"-s")
	    synapseFile="${@:argCount+1:1}";
	    optionFound=1;
	    synapseFileFound=1;
	    ;;
	"-e")
	    extcurrentFile="${@:argCount+1:1}";
	    optionFound=1;
	    extcurrentFileFound=1;
	    ;;
	"-d")
	    dynparamsFile="${@:argCount+1:1}";
	    optionFound=1;
	    dynparamsFileFound=1;
	    # extract prefix from filename with full path
	    dynparamsFile_pf=$(echo "$dynparamsFile" | sed -e 's/\.[a-z]*//g')
	    dynparamsFile_pf=$(echo "$dynparamsFile_pf" | sed -e 's,^[^ ]*/,,')
	    # extract suffix from filename with full path
	    dynparamsFile_sf=$(echo "$dynparamsFile" | sed -e 's/.*\.//')
	    # extract full path from filename with full path
	    dynparamsFile_p=$(echo "$dynparamsFile" | sed -e 's/\(.*\)\/.*/\1/')/
	    ;;
	"--exec")
	    jobName="${@:argCount+1:1}";
	    optionFound=1;
	    jobFound=1;
	    # extract prefix from filename with full path
	    jobName_pf=$(echo "$jobName" | sed -e 's/\.[a-z]*//g')
	    jobName_pf=$(echo "$jobName_pf" | sed -e 's,^[^ ]*/,,')
	    ;;
	"--begin")
	    counter_start="${@:argCount+1:1}";
	    optionFound=1;
	    ;;
	"--stop")
	    counter_stop="${@:argCount+1:1}";
	    optionFound=1;
	    ;;
	*)
	    # exit if wrong options are passed
	    printf " ${RED} Usage: ${NC} multiple_runs  ${GREEN}--exec program-name --begin counter-start --stop counter-stop -n neuron-file -o output-file -s synapse-file  -e external-current-file  -d dynamic-params-file\n ${NC}" 
	    exit
	    ;;
    esac
done
# exit if no arguments are passed
case "$#" in
    [0])
	printf " ${RED} Usage: ${GREEN} executable_name counter_start counter_stop n_file_prefix o_file_prefix s_file_prefix e_file_prefix d_file_prefix\n ${NC}" 
	exit;
	;;
esac

echo "----------------------------------------------------------------------------------"
echo     "Job name               = $jobName_pf"
echo     "Counter start          = $counter_start"
echo     "Counter stop           = $counter_stop"
echo     "Neuron file            = $neuronFile_p$neuronFile_pf.$neuronFile_sf"
echo     "Output file            = $outputFile_p$outputFile_pf.$outputFile_sf"
echo     "Synapse file           = $synapseFile"
echo     "External-current file  = $extcurrentFile"
echo     "Dynamic-params file    = $dynparamsFile"

# Stop any running job of the same name
# if (( $( pgrep --exact $jobName_pf | wc -l) >0 )); then
    # echo "Found another job with the same name and killed it!"
    # pkill $jobName_pf;
# fi;

# Exit if no neuron-file or output-file are passed
if [[ "$neuronFileFound" -eq 0 || "$outputFileFound" -eq 0 ]]; then
    printf "Not enough arguments provided\n"
    printf " ${RED} Usage: ${GREEN} executable_name counter_start counter_stop n_file_prefix o_file_prefix s_file_prefix e_file_prefix d_file_prefix\n ${NC}" 
    exit;
fi;

counter=$counter_start;
idx=0;
while [[ "$counter" -le "$counter_stop" ]]; do
    jobcount=$( pgrep $jobName_pf | wc -l);
    if (( $jobcount < $jobmax && $counter <= $counter_stop )); then
	echo $jobcount
	# -------------------------------
	# Run insilico with options: -n -o
	if [[ "$neuronFileFound" -eq 1 && "$outputFileFound" -eq 1 && "$synapseFileFound" -eq 0 && "$dynparamsFileFound" -eq 0 && "$extcurrentFileFound" -eq 0 ]]; then
	    printf "*** Running with insilico options: ${YELLOW} -n -o ${NC}\n";
	    $jobName -n $neuronFile_p$neuronFile_pf$counter.$neuronFile_sf -o $outputFile_p$outputFile_pf$counter.$outputFile_sf&
	fi
	# Run insilico with options: -n -o -e
	if [[ "$neuronFileFound" -eq 1 && "$outputFileFound" -eq 1 && "$synapseFileFound" -eq 0 && "$dynparamsFileFound" -eq 0 && "$extcurrentFileFound" -eq 1 ]]; then
	    printf "*** Running with insilico options: ${YELLOW} -n -o -e ${NC}\n";
	    $jobName -n $neuronFile -o $outputFile_p$outputFile_pf$counter.$outputFile_sf -e $extcurrentFile
	fi
	# Run insilico with options: -n -o -s -e
	if [[ "$neuronFileFound" -eq 1 && "$outputFileFound" -eq 1 && "$synapseFileFound" -eq 1 && "$dynparamsFileFound" -eq 0 && "$extcurrentFileFound" -eq 1 ]]; then
	    printf "*** Running with insilico options: ${YELLOW} -n -o -s -e ${NC}\n";
	    # $jobName -n $neuronFile -o $outputFile_p$outputFile_pf$counter.$outputFile_sf -s $synapseFile -e $extcurrentFile&
	    $jobName -n $neuronFile_p$neuronFile_pf$counter.$neuronFile_sf -o $outputFile_p$outputFile_pf$counter.$outputFile_sf -s $synapseFile -e $extcurrentFile&
	fi
	# Run insilico with options: -n -o -d
	if [[ "$neuronFileFound" -eq 1 && "$outputFileFound" -eq 1 && "$synapseFileFound" -eq 0 && "$dynparamsFileFound" -eq 1 && "$extcurrentFileFound" -eq 0 ]]; then
	    printf "*** Running with insilico options: ${YELLOW} -n -o -d ${NC}\n";
	    $jobName -n $neuronFile -o $outputFile_p$outputFile_pf$counter.$outputFile_sf -d $dynparamsFile&
	    # $jobName -n $neuronFile -o $outputFile_p$outputFile_pf$counter.$outputFile_sf -d $dynparamsFile_p$dynparamsFile_pf$counter.$dynparamsFile_sf&
	fi
	# Run insilico with options: -n -o -s
	if [[ "$neuronFileFound" -eq 1 && "$outputFileFound" -eq 1 && "$synapseFileFound" -eq 1 && "$dynparamsFileFound" -eq 0 && "$extcurrentFileFound" -eq 0 ]]; then
	    printf "*** Running with insilico options: ${YELLOW} -n -o -s ${NC}\n";
	    $jobName -n $neuronFile -o $outputFile_p$outputFile_pf$counter.$outputFile_sf -s $synapseFile
	fi
	# Run insilico with options: -n -o -s -e -d
	if [[ "$neuronFileFound" -eq 1 && "$outputFileFound" -eq 1 && "$synapseFileFound" -eq 1 && "$dynparamsFileFound" -eq 1 && "$extcurrentFileFound" -eq 1 ]]; then
	    printf "*** Running with insilico full options: ${YELLOW} -n -o -s -e -d ${NC}\n";
	    # $jobName -n $neuronFile -o $outputFile_p$outputFile_pf$counter.$outputFile_sf -s $synapseFile -e $extcurrentFile -d $dynparamsFile&
	    $jobName -n $neuronFile -o $outputFile_p$outputFile_pf$counter.$outputFile_sf -s $synapseFile -e $extcurrentFile -d $dynparamsFile_p$dynparamsFile_pf$counter.$dynparamsFile_sf&
	fi
	# Run insilico with options: -n -o -s -d
	echo "run option -n -o -s -d"
	if [[ "$neuronFileFound" -eq 1 && "$outputFileFound" -eq 1 && "$synapseFileFound" -eq 1 && "$dynparamsFileFound" -eq 1 ]]; then
	    printf "*** Running with insilico options: ${YELLOW} -n -o -s -d ${NC}\n";
	    $jobName -n $neuronFile -o $outputFile_p$outputFile_pf$counter.$outputFile_sf -s $synapseFile -d $dynparamsFile&
	    # $jobName -n $neuronFile -o $outputFile_p$outputFile_pf$counter.$outputFile_sf -s $synapseFile -d $dynparamsFile_p$dynparamsFile_pf$counter.$dynparamsFile_sf&
	    # $jobName -n $neuronFile_p$neuronFile_pf$counter.$neuronFile_sf -o $outputFile_p$outputFile_pf$counter.$outputFile_sf -s $synapseFile -d $dynparamsFile&
	fi
	jobid[$idx]=$!;
	printf "insilico run $counter: PID = %d \n" "${jobid[idx]}" 
	idx=$((idx+1));
	let counter=counter+1;
    else
	sleep 1;
    fi;
done

echo -e "${YELLOW}Finished! \n ${NC}"
exit;
