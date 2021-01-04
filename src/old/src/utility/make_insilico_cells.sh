#! /bin/bash
# This bash script will take an insilico a single cell file and generate a multiple cell insilico file

sig_fname=$1
mul_fname=$2
numcells=$3

if [[ ! -f "$sig_fname" ]]; then
    echo "!!! The given file could not be found.";
    exit 0;
fi

if [[ -f "$mul_fname" ]]; then
    echo "!!! Deleting the output file that already exists!";
    rm $mul_fname
fi

for ((i=1;i<=numcells;i++))
do
    cat $sig_fname >> $mul_fname;
    # sed -i -e '$a\' $mul_fname
    echo "" >> $mul_fname
    echo "\"================================================================================\"" >> $mul_fname
done
