#! /bin/bash

g++ -std=c++11 -Wall -I/mnt/storage/goofy/projects/astron/libs/insilico/include/ -I/mnt/storage/goofy/projects/astron/src/ insilico_main.cpp ../src/presynaptic_neuron.cpp ../src/na_pre.cpp ../src/rk4_counter.cpp -o insilico_main
