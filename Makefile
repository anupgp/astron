# Time-stamp: <2021-02-17 21:36:39 anup>

CC = g++ 
# CC = /usr/local/Cellar/gcc/9.3.0_1/bin/g++-9	

EXE_DIR := bin/
SRC_DIR := src/
OBJ_DIR := build/
UTIL_SRC_DIR := src/utility/
UTIL_EXE_DIR := bin/utility/
CPP_MAIN_DIR := src/

NEW_INSILICO_PATH := lib/new_insilico
NEW_INSILICO_LIB_PATH := lib/new_insilico/lib/
NEW_INSILICO_LIB_NAME := new_insilico
ODE_STOCH_PATH := lib/stochastic_euler/include

# BOOST_ROOT_PATH := /usr/local/include/boost
# BOOST_LIBS_PATH := /usr/local/opt/boost/lib
# BOOST_ODEINT_PATH := /usr/local/Cellar/boost/1.71.0/include
BOOST_ODEINT_PATH := lib/boost/1.71.0/

# ------------------------
MAIN_EXE := astron_main
# ------------------------
CPP_MAIN_FILE := astron_main.cpp 
# CCFLAGS := -std=c++11 -stdlib=libc++ -Wall -I$(BOOST_ROOT_PATH) -I$(BOOST_ODEINT_PATH) -I$(BOOST_LIBS_PATH) -I$(NEW_INSILICO_PATH) -I$(ODE_STOCH_PATH) -I$(SRC_DIR) -Ofast -v
# CCFLAGS := -std=c++11 -Wall -I$(BOOST_ROOT_PATH) -I$(BOOST_ODEINT_PATH) -I$(BOOST_LIBS_PATH) -I$(NEW_INSILICO_PATH) -I$(ODE_STOCH_PATH) -I$(SRC_DIR) -Ofast -v
CCFLAGS := -std=c++11 -Wall -I$(BOOST_ODEINT_PATH) -I$(NEW_INSILICO_PATH) -I$(ODE_STOCH_PATH) -I$(SRC_DIR) -Ofast -v

#LDFLAGS := -Xlinker -z -Xlinker muldefs
#LDFLAGS	:= -Xlinker -Wl -Xlinker --allow-multiple-definition
LDFLAGS := -L$(NEW_INSILICO_LIB_PATH) -l$(NEW_INSILICO_LIB_NAME)


# Extra cpp files for astron project 
UTILS := filetrim \
	generate_runtime_mod_file_1param_fixedstep \
	generate_runtime_mod_file_1param_poisson \
	generate_runtime_mod_file_1param_expdecay \
	generate_runtime_mod_file_alter_anycolumn_fixedval \
	lineskip \
	generate_inputfiles_one_parameter_sweep \
	generate_inputfiles_two_parameter_sweep \
	generate_inputfiles_three_parameter_sweep

UTILS_SRC := $(foreach F,$(UTILS),$(UTIL_SRC_DIR)$F.cpp)
UTILS_EXE := $(foreach F,$(UTILS),$(UTIL_EXE_DIR)$F)

SRC := $(wildcard $(SRC_DIR)*.cpp)
SRC := $(filter-out $(CPP_MAIN_DIR)$(CPP_MAIN_FILE),$(SRC))
OBJ := $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(SRC)) 
OBJ := $(patsubst %.cpp, %.o, $(OBJ))
# lising sub directories that have to be build (run their own make files)
SUBDIRS = lib/new_insilico

all:	$(SUBDIRS) $(EXE_DIR)$(MAIN_EXE) $(UTILS_EXE)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY:	$(SUBDIRS)
# pattern rule for c++ files in the utility directory
$(UTIL_EXE_DIR)%: $(UTIL_SRC_DIR)%.cpp $(UTIL_SRC_DIR)*.hpp
	@echo "Compiling..."
	# $(CC) -std=c++11 -fopenmp -Wall $< -o $@
	$(CC) -std=c++11 -Wall $< -o $@

$(EXE_DIR)$(MAIN_EXE): $(CPP_MAIN_DIR)$(CPP_MAIN_FILE) $(OBJ)
	@echo "building "$@
	$(CC) $(CCFLAGS) $(LDFLAGS) $^ -o $@ $(LDFLAGS) 

$(OBJ_DIR)astron_main.o:
	@echo compile $<


# pattern rule for c++ files in the src directory
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(SRC_DIR)%.hpp
	@echo "Compiling..."$<
	$(CC) $(CCFLAGS) -c $< -o $@

clean:	
	@rm -f $(EXE_DIR)$(MAIN_EXE)
	@echo "Removed new_insilico/lib/libnewinsilico.a"
	@rm  -f lib/new_insilico/lib/libnew_insilico.a
	@echo "Removed main executable!: astron "

clean_all:	
	@rm -f $(EXE_DIR)$(MAIN_EXE)
	@rm -f $(UTIL_EXE_DIR)*
	@rm -f $(OBJ_DIR)*
	@echo "Cleaning done!"

clean_all_execs:
	# @rm -f $(EXE_DIR)*
	# @rm -f $(UTIL_EXE_DIR)*

print:
	@echo $(NEW_INSILICO_LIB_PATH)
	@echo $(NEW_INSILICO_LIB_NAME)
# --------------------------------------------------------------------------------------------
# GENERATE NEURON/ASTROCYTE INPUT FILES
# Generate pre_neuron input file
# --------------------------------------------------------------------------------------------
PRE_NEURON_INPUT_DIR := input/pre_neuron/

PRE_NEURON_PARTS := na_pre \
	k_pre \
	leak_pre \
	vgcc_pre \
	ip3_degradation_simple \
	ip3_kinase_hill \
	plc_delta_hill \
	p2x2_receptor \
	p2x2_receptor_hill \
	p2y_receptor_hill \
	mglu_receptor_hill \
	calbindin \
	serca_hill \
	pmca \
	er_leak \
	ryanodine_receptor \
	ip3_receptor_yk \
	a1_receptor_hill

PRE_NEURON_PARTS := $(patsubst %, $(PRE_NEURON_INPUT_DIR)%.isf,$(PRE_NEURON_PARTS))

PRE_NEURON_MAIN_FILE :=$(PRE_NEURON_INPUT_DIR)pre_neuron_bare.isf 

PRE_NEURON_COMPLETE_FILE := $(PRE_NEURON_INPUT_DIR)pre_neuron_complete.isf

pre_neuron: $(PRE_NEURON_COMPLETE_FILE) $(PRE_NEURON_PARTS)

$(PRE_NEURON_COMPLETE_FILE): $(PRE_NEURON_PARTS) $(PRE_NEURON_MAIN_FILE)
	@echo "Making the pre_neuron input file...." $(PRE_NEURON_COMPLETE_FILE)
	@./src/utility/stitch_infiles.sh $^ -o $@ --oldchar "," --newchar ";"

clean_pre_neuron: 
	@echo "Removing $(PRE_NEURON_COMPLETE_FILE)"
	@rm $(PRE_NEURON_COMPLETE_FILE)

# ------------------------------------------------------------------------------------------------
# Generate astrocyte input file
# ------------------------------------------------------------------------------------------------

ASTROCYTE_INPUT_DIR := input/astrocyte/

ASTROCYTE_PARTS := \
		na_pre \
		k_pre \
		leak_pre \
		ip3_degradation_simple \
		ip3_kinase_hill \
		plc_delta_hill \
		p2y_receptor_hill \
		serca_hill \
		pmca \
		ca_er_buffer_simple \
		er_leak \
		ip3_receptor_lr \
		mglu_receptor_hill \
		transmitter_release_syt4syt5_glu \
		ca_cyt_buffer_simple
		# cap_ca_entry 
		# calbindin 
		# ryr_receptor_xw 
		# ca_cyt_dye 
		# p2x2_receptor 
		# serca_higg 
		# ip3_receptor_yk 
		# ryanodine_receptor
		# transmitter_release_syt4_glu

# ASTROCYTE_PARTS := transmitter_release_syt1syt7_glu
# ASTROCYTE_PARTS := transmitter_release_hybrid_glu
# ASTROCYTE_PARTS := transmitter_release_syt7_glu

ASTROCYTE_PARTS := $(patsubst %, $(ASTROCYTE_INPUT_DIR)%.isf,$(ASTROCYTE_PARTS))

ASTROCYTE_MAIN_FILE :=$(ASTROCYTE_INPUT_DIR)astrocyte_bare.isf 

ASTROCYTE_COMPLETE_FILE := $(ASTROCYTE_INPUT_DIR)astrocyte_complete.isf

astrocyte: $(ASTROCYTE_COMPLETE_FILE) $(ASTROCYTE_PARTS)

$(ASTROCYTE_COMPLETE_FILE): $(ASTROCYTE_PARTS) $(ASTROCYTE_MAIN_FILE)
	@echo "Making astrocyte_complete input file...." $(ASTROCYTE_COMPLETE_FILE)
	@./src/utility/stitch_infiles.sh $^ -o $@ --oldchar "," --newchar ";"  

clean_astrocyte: 
	@echo "Removing $(ASTROCYTE_COMPLETE_FILE)"
	@rm -f $(ASTROCYTE_COMPLETE_FILE)

# -----------------------------------------------------------------------------------------------
# GENERATE CELLS INPUT FILES
# -----------------------------------------------------------------------------------------------

CELLS_INPUT_DIR := input/

CELLS_PARTS := $(PRE_NEURON_COMPLETE_FILE) \
		$(ASTROCYTE_COMPLETE_FILE)

CELLS_COMPLETE_FILE := $(CELLS_INPUT_DIR)cells_all.isf

cells: $(CELLS_COMPLETE_FILE) $(CELLS_PARTS)

$(CELLS_COMPLETE_FILE): $(CELLS_PARTS)
	@echo "Making cells input file...." $(CELLS_COMPLETE_FILE)
	@./src/utility/stitch_infiles.sh $^ -o $@ --oldchar ";" --newchar ";" 

clean_cells: 
	@echo "Removing $(PRE_NEURON_COMPLETE_FILE) $(ASTROCYTE_COMPLETE_FILE) $(CELLS_COMPLETE_FILE)"
	@rm -f $(PRE_NEURON_COMPLETE_FILE) $(ASTROCYTE_COMPLETE_FILE) $(CELLS_COMPLETE_FILE)

# ===============================================================================================
# GENERATE SYNAPSE INPUT FILES
# ===============================================================================================
SYNAPSE_INPUT_DIR := input/synapse/
# -----------------------------------------------------------------------------------------------
# Generate insilico atp_synapse input file
# -----------------------------------------------------------------------------------------------
ATP_SYNAPSE_PARTS := atp_production atp_degradation_hill adenosine_production_hill adenosine_degradation_hill
ATP_SYNAPSE_PARTS := $(patsubst %, $(SYNAPSE_INPUT_DIR)%.isf,$(ATP_SYNAPSE_PARTS))
ATP_SYNAPSE_MAIN_FILE := $(SYNAPSE_INPUT_DIR)atp_synapse_bare.isf
ATP_SYNAPSE_COMPLETE_FILE := $(SYNAPSE_INPUT_DIR)atp_synapse_complete.isf

atp_synapse: $(ATP_SYNAPSE_COMPLETE_FILE) $(ATP_SYNAPSE_PARTS) 
clean_atp_synapse: 
	@echo "!!!Removing insilico atp synapse file ... $(ATP_SYNAPSE_COMPLETE_FILE)"
	@rm $(ATP_SYNAPSE_COMPLETE_FILE)

$(ATP_SYNAPSE_COMPLETE_FILE): $(ATP_SYNAPSE_PARTS) $(ATP_SYNAPSE_MAIN_FILE)
	@echo "Making insilico atp synapse input file ... "
	@./src/utility/stitch_infiles.sh $^ -o $@ --oldchar "," --newchar ";"  

# -----------------------------------------------------------------------------------------------
# Generate insilico glutamate_synapse input file
# -----------------------------------------------------------------------------------------------
GLU_SYNAPSE_PARTS := glutamate_production glutamate_degradation_simple
GLU_SYNAPSE_PARTS := $(patsubst %, $(SYNAPSE_INPUT_DIR)%.isf,$(GLU_SYNAPSE_PARTS))
GLU_SYNAPSE_MAIN_FILE := $(SYNAPSE_INPUT_DIR)glutamate_synapse_bare.isf
GLU_SYNAPSE_COMPLETE_FILE := $(SYNAPSE_INPUT_DIR)glutamate_synapse_complete.isf

glu_synapse: $(GLU_SYNAPSE_COMPLETE_FILE) $(GLU_SYNAPSE_PARTS) 
clean_glu_synapse: 
	@echo "!!!Removing insilico glutamate synapse file ... $(GLU_SYNAPSE_COMPLETE_FILE)"
	@rm $(GLU_SYNAPSE_COMPLETE_FILE)

$(GLU_SYNAPSE_COMPLETE_FILE): $(GLU_SYNAPSE_PARTS) $(GLU_SYNAPSE_MAIN_FILE)
	@echo "***Making insilico glutamate synapse input file ... "
	@bash ./src/utility/stitch_infiles.sh $^ -o $@ --oldchar "," --newchar ";"  
# ------------------------------------------------------------------------------------------------
# Generate the complete insilico synapse file
# ------------------------------------------------------------------------------------------------
SYNAPSE_COMPLETE_FILE := $(SYNAPSE_INPUT_DIR)synapses.isf
synapses: $(SYNAPSE_COMPLETE_FILE) $(ATP_SYNAPSE_COMPLETE_FILE) $(GLU_SYNAPSE_COMPLETE_FILE)
clean_synapses:
	@echo "!!! Removing all insilico synapse files ... $(ATP_SYNAPSE_COMPLETE_FILE) $(GLU_SYNAPSE_COMPLETE_FILE)" "$(SYNAPSE_COMPLETE_FILE)"
	@rm -f $(SYNAPSE_COMPLETE_FILE) $(ATP_SYNAPSE_COMPLETE_FILE) $(GLU_SYNAPSE_COMPLETE_FILE)
$(SYNAPSE_COMPLETE_FILE): $(ATP_SYNAPSE_COMPLETE_FILE) $(GLU_SYNAPSE_COMPLETE_FILE)
	@echo "*** Making complete insilico synapse file ..."
	@bash ./src/utility/make_insilico_synapses.sh
