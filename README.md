 # Astron                                                                                                                                                                                                                                                                                     
 ***A biophysical model for Ca<sup2+<\sup>-signaling and gliotransmission from astrocytes at a single compartment level***

This code implements a detailed biophysical model of a single astrocytic compartment/microdomain. The model incorporates multiple molecular components to reproduce mGluR-mediated calcium signaling and calcium-mediated gliotransmitter release from astrocytic microdomains, as observed experimentally. 

Calcium signaling components in the model includes:

 1. Cytosolic Ca<sup>2+</sup> buffer
 2. PMCA pump
 3. ER leak
 4. ER Ca<sup>2+</sup> buffer
 5. SERCA
 6. IP<sub>3</sub> receptor cluster (using Langevin approx. of Li-Rinzel model)
 7. mGluR

Additionally, the model has components involved in the production and degradation of IP<sub>3</sub>, and a very detailed framework for Ca<sup>2+</sup>-mediated gliotransmission that includes
 
 1. Synaptotagmins (*Syt4* & *Syt7*)
 2. Vesicles (docked & mobile)
 3. Vesicle release and recycling  
 
Using the above model of an astrocytic microdomain, we investigated some of the functional consequences of Alzheimer's pathology on astrocytic Ca<sup>2+</sup> signaling and gliotransmission. The study has been submitted to PloS Computational biology for publication and will be linked here once accepted.

The steps to install the model, run the simulations, analyze data and plot figures in the manuscript are below.

## Installation    

### Linux

Ubuntu 20.04.2.0 LTS

Install project dependencies:    
``` bash

$ sudo apt-get install build-essential
$ sudo apt-get install python3.6
```                                                                                                                                                        
Clone the source locally:                                                                                                                                 
                                                                                                                                                           
```bash

$ git clone https://github.com/anupgp/astron
$ cd astron
$ git submodule update --init --recursive
$ make                                                  
```                                                 
## Code organization
The following folders are in the root folder (*astron*)

 - **analysis:** has all the Python codes for data analysis and visualization
  - **bin:** has the main executable (astron_main) and utility folder.
    - **utility:** contains executable files for creating various parameter files for stimulating the astrocytic compartments and other accessory.
   operations
   - **build:** contains all object files.
   - **doc:** extra documentation and/or notes  
   - **include:** currently has nothing 
   - **input:** parameter files for each molecular component in the model  
   - **lib:** Includes all the libraries.
    - **run:** has codes to run the simulation in a Linux machine or an HPC managed through PBSPro software.
   - **src:** source codes.
   -  **stimparams:** stimulation (DHPG or glutamate release) files.
   - **validation_data:** data for model validation

## Usage
Below are the steps to recreate calcium signaling and gliotransmitter release data for validating the model with previous experimental data from astrocytic microdomains (Figures 1 & 3). This is accomplished by stimulating the astrocytic compartment with a single pulse of DHPG (100 μM, 2s). The model is typically run for some time (~200s) until Ca<sup>2+</sup> and IP<sub>3</sub> levels stabilize. 

### Step 1: run simulation   
Edit the launch script (*run/generate_data_dhpg100000nM2s.sh*) to specify paths to the root (*astron*) folder, folder for data storage and path to main executable (*astron_main*).
Leave the rest of the lines unchanged
Run the script as below
```bash
$ bash run/generate_data_dhpg100000nM2s.sh
```
The above command will start independent processes, starting from *trialstart* to *trialstop* in multiples of 7 (#CPUs/threads available). The later can be changed through *jobmax* variable in file: *run/insilico_single_processor_multiple_runs.sh*. The stimulus parameter file (*stimparams_dhpg100000nM2s.isfdp*) is copied to the data folder before the simulation is launched. Visualization of Figure 1 & 3 requires 2400 trials (400 x 6) in total. The data is split into 6 batches for generating plots with mean and standard error. Each simulation trial is for 300s with DHPG (100 μM, 2s) stimulation applied at time 200s. The integration step is set at 50μs and data is written at every 200 steps. The later value can be changed through a function: *newinsilico::set_observe_step_interval* called in file: *src/astron_main.cpp*. Two variables, *tstart* and *tstop* in *astron_main.cpp* file specifies the start and end of the simulation time, respectively. A typical trial lasting 300s takes about 15 minutes to complete. 

### Step2: analyze data
All the analysis codes are in the *analysis* folder. Data obtained from the above simulation is analyzed using file: *dhpg100000nM2s_analyze_save_cacyt_rel.py*. The paths to the raw data and the folder for saving the processed data set need to be correctly specified. The analyzed data is saved in a compressed (HDF5) format and requires several python modules that can be installed with the command below.
```bash
$ python3.6 -m pip install numpy pandas matplotlib h5py scipy 
```
The code needs to be adjusted for the number of trials, batches, simulation start and stop times etc. Finally, the analysis code can be run as below.
```bash
$ python3.6 astron/analysis/dhpg100000nM2s_analyze_save_cacyt_rel.py
```
### Step3: visualization
Once the analysis is completed, the data is visualized by running the below python code
```bash
$ python3.6 astron/analysis/dhpg100000nM2s_plot_cacyt_rel.py
```
The above visualization code is organized in sections that correspond to specific figure panels of figures 1 & 3 in the manuscript.

## License

This work is licensed under the [MIT License](https://opensource.org/licenses/MIT).

<address>

Written by <a href="mailto:anupgpillai@gmail.com">Dr. Anup Pillai</a><br> and <a href="mailto:suhita@iiserpune.ac.in"> Prof. Suhita Nadkarni</a><br>