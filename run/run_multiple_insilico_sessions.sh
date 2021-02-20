#!/bin/bash

time ./insilico/main/insilico_main  -o ./insilico/outfiles/neuron_only_single_ap.csv  -n ./insilico/infiles/tripartite_cells.isf  -s ./insilico/infiles/tripartite_synapses.isf -e ./insilico/infiles/ext_current_inj_single_ap_10sec.isfc -d ./insilico/infiles/dypar.isfdp&

# time ./insilico/main/insilico_main  -o ./insilico/outfiles/neuron_5hz.csv  -n ./insilico/infiles/tripartite_cells.isf  -s ./insilico/infiles/tripartite_synapses.isf -e ./insilico/infiles/ext_current_inj_poisson_5hz.isfc -d ./insilico/infiles/dypar.isfdp&

# time ./insilico/main/insilico_main  -o ./insilico/outfiles/neuron_10hz.csv  -n ./insilico/infiles/tripartite_cells.isf  -s ./insilico/infiles/tripartite_synapses.isf -e ./insilico/infiles/ext_current_inj_poisson_10hz.isfc -d ./insilico/infiles/dypar.isfdp&

# time ./insilico/main/insilico_main  -o ./insilico/outfiles/neuron_25hz.csv  -n ./insilico/infiles/tripartite_cells.isf  -s ./insilico/infiles/tripartite_synapses.isf -e ./insilico/infiles/ext_current_inj_poisson_25hz.isfc -d ./insilico/infiles/dypar.isfdp&

# time ./insilico/main/insilico_main  -o ./insilico/outfiles/neuron_50hz.csv  -n ./insilico/infiles/tripartite_cells.isf  -s ./insilico/infiles/tripartite_synapses.isf -e ./insilico/infiles/ext_current_inj_poisson_50hz.isfc -d ./insilico/infiles/dypar.isfdp&

