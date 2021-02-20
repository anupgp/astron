#! bin/bash
# read 
# bash to control pbs job submission
# get all the jobs submitted (running & qued)
# get total number of process submitted (running & qued)
# get percentage of job completed
pc=$(qstat -p 241882[] | tail -n1 | awk '{print($4)}');
