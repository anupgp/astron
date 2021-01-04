#! /bin/bash
counter=0
#n_runs=100
program_name=$1
n_runs=$2
output_file_prefix=$3
#file_name="gillespie_ampar/gillespie_ampar_run"
while [ $counter -lt $n_runs ]; do
   filename=$output_file_prefix"_"$counter
   echo $filename
   echo $counter
   $program_name $filename
   #$program_name > $filename
   let counter=counter+1
done

