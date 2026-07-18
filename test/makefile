##############################################################################
################################ makefile ####################################
##############################################################################
#                                                                            #
#   makefile of test (for ScenarioReductionSolver)                           #
#                                                                            #
#                                Donato Meoli                                #
#                         Dipartimento di Informatica                        #
#                             Universita' di Pisa                            #
#                                                                            #
##############################################################################

# module name
NAME = scenario_reduction_solve

# basic directory
DIR = .

# compiler
CC = clang++

# common flags
COMMON_SW = -std=c++17 -ferror-limit=1 -Wno-enum-compare -DCLANG_1200_0_32_27_PATCH

# debug switches
SW_DEBUG = -g3 -glldb -fno-inline $(COMMON_SW)

# production switches
SW_RELEASE = -O3 $(COMMON_SW) -DNDEBUG

# default target - build in release mode
default: SW = $(SW_RELEASE)
default: $(DIR)/$(NAME)

# debug target - build in debug mode
debug: SW = $(SW_DEBUG)
debug: $(DIR)/$(NAME)

# define & include the necessary modules- - - - - - - - - - - - - - - - - - -

# SMS++
SMS++SDR = ../../SMS++
include $(SMS++SDR)/lib/makefile-inc

# ScenarioReductionSolver
SRSkSDR = ..
include $(SRSkSDR)/makefile-s

# main module (linking phase) - - - - - - - - - - - - - - - - - - - - - - - -

# object files
MOBJ =  $(SRSkOBJ) $(SMS++OBJ)

# libraries
MLIB =  $(SRSkLIB) $(SMS++LIB)

$(DIR)/$(NAME): $(MOBJ) $(DIR)/ScenarioReductionSolve.o
	$(CC) -o $(DIR)/$(NAME) $(DIR)/ScenarioReductionSolve.o $(MOBJ) $(MLIB) $(SW)

# dependencies: every .o from its .cpp + every recursively included .h- - - -

# include directives
MINC =  $(SMS++INC) $(SRSkINC)

# includes
MH =    $(SMS++H) $(SRSkH)

# compile command
$(DIR)/ScenarioReductionSolve.o: $(DIR)/ScenarioReductionSolve.cpp $(MH)
	$(CC) -c $(DIR)/ScenarioReductionSolve.cpp -o $@ $(MINC) $(SW)

# clean target
clean::
	rm -f $(DIR)/*.o $(DIR)/*~
	rm -f $(DIR)/$(NAME)

# phony targets
.PHONY: default debug clean

############################ End of makefile #################################
