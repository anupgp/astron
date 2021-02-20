#! /bin/bash
# Time-stamp: <2017-10-24 10:53:48 anup>
# This is a bash script that can be to dispatch a single insilico process for cluster

# initialize all variables to empty strings
jobName="";
jobNum="";

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
jobnumFound=0;
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
	"--jobnum")
	    jobNum="${@:argCount+1:1}";
	    optionFound=1;
	    jobnumFound=1;
	    ;;
	"--exec")
	    jobName="${@:argCount+1:1}";
	    optionFound=1;
	    jobFound=1;
	    # extract prefix from filename with full path
	    jobName_pf=$(echo "$jobName" | sed -e 's/\.[a-z]*//g')
	    jobName_pf=$(echo "$jobName_pf" | sed -e 's,^[^ ]*/,,')
	    ;;
	*)
	    # exit if wrong options are passed
	    printf " ${RED} Usage: ${NC} multiple_runs  ${GREEN}--exec program-name --jobnum job-number -n neuron-file -o output-file -s synapse-file  -e external-current-file  -d dynamic-params-file\n ${NC}" 
	    exit
	    ;;
    esac
done
# exit if no arguments are passed
case "$#" in
    [0])
	printf " ${RED} Usage: ${GREEN} executable_name jobnum n_file_prefix o_file_prefix s_file_prefix e_file_prefix d_file_prefix\n ${NC}" 
	exit;
	;;
esac

echo "----------------------------------------------------------------------------------"
echo     "Job name               = $jobName_pf"
echo     "Job number             = $jobNum"
echo     "Neuron file            = $neuronFile_p$neuronFile_pf.$neuronFile_sf"
echo     "Output file            = $outputFile_p$outputFile_pf.$outputFile_sf"
echo     "Synapse file           = $synapseFile"
echo     "External-current file  = $extcurrentFile"
echo     "Dynamic-params file    = $dynparamsFile"

# Exit if no neuron-file or output-file are passed
if [[ "$neuronFileFound" -eq 0 || "$outputFileFound" -eq 0 ]]; then
    printf "Not enough arguments provided\n"
    printf " ${RED} Usage: ${GREEN} executable_name jobnum n_file_prefix o_file_prefix s_file_prefix e_file_prefix d_file_prefix\n ${NC}" 
    exit;
fi;

# -------------------------------
# Run insilico with options: -n -o
if [[ "$neuronFileFound" -eq 1 && "$outputFileFound" -eq 1 && "$synapseFileFound" -eq 0 && "$dynparamsFileFound" -eq 0 && "$extcurrentFileFound" -eq 0 ]]; then
    printf "*** Running with insilico options: ${YELLOW} -n -o ${NC}\n";
    $jobName -n $neuronFile -o $outputFile_p$outputFile_pf$jobNum.$outputFile_sf&
fi
# Run insilico with options: -n -o -e
if [[ "$neuronFileFound" -eq 1 && "$outputFileFound" -eq 1 && "$synapseFileFound" -eq 0 && "$dynparamsFileFound" -eq 0 && "$extcurrentFileFound" -eq 1 ]]; then
    printf "*** Running with insilico options: ${YELLOW} -n -o -e ${NC}\n";
    $jobName -n $neuronFile -o $outputFile_p$outputFile_pf$jobNum.$outputFile_sf -e $extcurrentFile
fi
# Run insilico with options: -n -o -s -e
if [[ "$neuronFileFound" -eq 1 && "$outputFileFound" -eq 1 && "$synapseFileFound" -eq 1 && "$dynparamsFileFound" -eq 0 && "$extcurrentFileFound" -eq 1 ]]; then
    printf "*** Running with insilico options: ${YELLOW} -n -o -s -e ${NC}\n";
    $jobName -n $neuronFile -o $outputFile_p$outputFile_pf$jobNum.$outputFile_sf -s $synapseFile -e $extcurrentFile&
fi
# Run insilico with options: -n -o -d
if [[ "$neuronFileFound" -eq 1 && "$outputFileFound" -eq 1 && "$synapseFileFound" -eq 0 && "$dynparamsFileFound" -eq 1 && "$extcurrentFileFound" -eq 0 ]]; then
    printf "*** Running with insilico options: ${YELLOW} -n -o -d ${NC}\n";
    $jobName -n $neuronFile -o $outputFile_p$outputFile_pf$jobNum.$outputFile_sf -d $dynparamsFile&
fi
# Run insilico with options: -n -o -s
if [[ "$neuronFileFound" -eq 1 && "$outputFileFound" -eq 1 && "$synapseFileFound" -eq 1 && "$dynparamsFileFound" -eq 0 && "$extcurrentFileFound" -eq 0 ]]; then
    printf "*** Running with insilico options: ${YELLOW} -n -o -s ${NC}\n";
    $jobName -n $neuronFile -o $outputFile_p$outputFile_pf$jobNum.$outputFile_sf -s $synapseFile
fi
# Run insilico with options: -n -o -s -e -d
if [[ "$neuronFileFound" -eq 1 && "$outputFileFound" -eq 1 && "$synapseFileFound" -eq 1 && "$dynparamsFileFound" -eq 1 && "$extcurrentFileFound" -eq 1 ]]; then
    printf "*** Running with insilico full options: ${YELLOW} -n -o -s -e -d ${NC}\n";
    $jobName -n $neuronFile -o $outputFile_p$outputFile_pf$jobNum.$outputFile_sf -s $synapseFile -e $extcurrentFile -d $dynparamsFile&
fi
# Run insilico with options: -n -o -s -d
if [[ "$neuronFileFound" -eq 1 && "$outputFileFound" -eq 1 && "$synapseFileFound" -eq 1 && "$dynparamsFileFound" -eq 1 ]]; then
    printf "*** Running with insilico options: ${YELLOW} -n -o -s -d ${NC}\n";
    $jobName -n $neuronFile -o $outputFile_p$outputFile_pf$jobNum.$outputFile_sf -s $synapseFile -d $dynparamsFile&
fi

echo -e "${YELLOW}Finished! \n ${NC}"
exit;
