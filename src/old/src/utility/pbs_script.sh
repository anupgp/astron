#!/bin/bash
## Time-stamp: <2017-11-28 18:59:39 anup>
## pbspro script to intitiate a job array in IISER computational neuroscience cluster (rosalind) with credentials: anup@192.168.1.244

#PBS -P "astron"
#PBS -N "astron"
#PBS -p 1000


/bin/hostname
cd $PBS_O_WORKDIR

echo $exeFile
echo $neuronFile
echo $outputFile_ph
echo $outputFile_pf
echo $outputFile_sf
echo $synapseFile
echo $dynparamsFile

${exeFile} -n ${neuronFile} -o ${outputFile_ph}${outputFile_pf}${PBS_ARRAY_INDEX}.${outputFile_sf} -s $synapseFile -d $dynparamsFile


##------------------------------------------------------
##PBS -A "Suhita Nadkarni"
##PBS -q "neurobio"
##PBS -J 1-10:1

##echo $NCPUS
##echo "PBS_JOBDIR = $PBS_JOBDIR"
##echo "PBS_JOBENVIRONMENT = $PBS_JOBENVIRONMENT"
##echo $OMP_NUM_THREADS
##echo $TMPDIR

##PBS -l select=1:ncpus=10:mem=10mb
##PBS -l place=free

##PBS -N "pbs_test"

##PBS -M anupgpillai@gmail.com
##PBS -m abe
