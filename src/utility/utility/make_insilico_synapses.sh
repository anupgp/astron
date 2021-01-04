#! /bin/bash

# This script will stich together atp and glutamate synapses to make one complete insilico synapse input file

filetrim=$(pwd)/bin/utility/filetrim

atp_synapse_complete_file="input/synapse/atp_synapse_all.isf";
glutamate_synapse_complete_file="input/synapse/glutamate_synapse_all.isf";

if [[ ! -f "$atp_synapse_complete_file" ]]; then
    echo "!!! No atp_synapse_complete_file found.";
    exit 0;
fi

if [[ ! -f "$glutamate_synapse_complete_file" ]]; then
    echo "!!! No glutamate_synapse_complete_file found.";
    exit 0;
fi
# create a temporary file to hold input file that is being processed
temp=$(pwd)/input/synapse/temp.isf
rm -f "$temp"
touch "$temp"
# -------------------------------------------------------------------------------------------------
# generate all glutamate synapses
# no.of glutamate synapses
nglu=1;
# glutamate synapse pre neurons
pre_glu=();
for ((i=0;i<$nglu;i++))
do
    pre_glu=(${pre_glu[@]} $i);
done
# pre_glu=(0);
# glutamate synapse post neurons
# post_glu=(0 1 1 0);
post_glu=();
for ((i=0;i<$nglu;i++))
do
    post_glu=(${post_glu[@]} $i);
done
# Output file: glutamate synapse
glusyn_file="input/synapse/glutamate_synapses_all.isf";
rm -f "$glusyn_file"
touch "$glusyn_file"
count=0;
echo "*** Generating glutamate synapses"
while (( $count < "$nglu"))
do
    cat "$glutamate_synapse_complete_file" > "$temp";
    pre="${pre_glu[$count]}";
    post="${post_glu[$count]}";
    echo "pre: $pre, post: $post";
    sed  -i 's/pre *: *[0-9]*,/pre : '$pre',/g' "$temp"
    sed  -i 's/post *: *[0-9]*,/post : '$post',/g' "$temp"
    cat "$temp" >> "$glusyn_file"; 
    sed  -i -e '$a\\' "$glusyn_file";
    count=$((count+1));
done;
$filetrim "$glusyn_file" "$glusyn_file"
# -------------------------------------------------------------------------------------------------
# generate all atp synapses
# no.of atp synapses
natp=1;
# atp synapse pre neurons
# pre_atp=(1 1);
pre_atp=(0);
# atp synapse post neurons
# post_atp=(1 0);
post_atp=(0);
# Output file: atp synapse
atpsyn_file="input/synapse/atp_synapses_all.isf";
rm -f "$atpsyn_file"
touch "$atpsyn_file"
count=0;
echo "*** Generating atp synapses"
while (( $count < "$natp"))
do
    cat "$atp_synapse_complete_file" > "$temp";
    pre="${pre_atp[$count]}";
    post="${post_atp[$count]}";
    echo "pre: $pre, post: $post";
    sed  -i 's/pre *: *[0-9]*,/pre : '$pre',/g' "$temp"
    sed  -i 's/post *: *[0-9]*,/post : '$post',/g' "$temp"
    cat "$temp" >> "$atpsyn_file"; 
    sed  -i -e '$a\\' "$atpsyn_file";
    count=$((count+1));
done;
$filetrim "$atpsyn_file" "$atpsyn_file"
rm $temp
# -------------------------------------------------------------------------------------------------
# generate complete synapse file
synapses_all_file="input/synapse/synapses_all.isf"
rm -f "$synapses_all_file"
touch "$synapses_all_file"
cat "$atpsyn_file" > "$synapses_all_file"
sed  -i -e '$a\\' "$synapses_all_file"
cat "$glusyn_file" >> "$synapses_all_file"
# for pre in "${pre_glu[@]}"
# do
#     echo ""
# done;
