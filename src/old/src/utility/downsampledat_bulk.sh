#! /bin/bash

exefile="/home/anup/goofy/projects/codes/astron/src/utility/lineskip.sh";

trialstart=1;
trialstop=315;
# treatgroup[0]="ctrl";
# treatgroup[0]="alzpmca";
treatgroup[0]="alzmglur";
# treatgroup[1]="alzheimB";
# treatgroup[2]="alzheimC";
# treatgroup[3]="test100ves";
# expgroup=(100000);
# expgroup=(5000);
# expgroup=(100 200 300 400 500 600 700 800 900 1000);
# expgroup=(0 1 10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 20000 30000 40000 50000 60000 70000 80000 90000 100000); # dhpg
trials=($(seq $trialstart 1 $trialstop));
expgroup=(1 2 3 4 5 6 7 8 9 10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000); # ap
exefile="/home/anup/goofy/projects/codes/astron/bin/utility/lineskip";


for treat in ${treatgroup[@]};
do
    for exp in ${expgroup[@]};
    do
	for trial in ${trials[@]};
	do
	    inputfile="/mnt/mount1/data/astron/raw/astrocyte/fr_mglur/run/${treat}/astrocyte_ap30s"${exp}"dHz_"${treat}${trial}".csv";
	    outputfile="/mnt/mount1/data/astron/raw/astrocyte/fr_mglur/run/${treat}/ds_astrocyte_ap30s"${exp}"dHz_"${treat}${trial}".csv";
	    $exefile ${inputfile} 10 ${outputfile}
	done
    done
done
