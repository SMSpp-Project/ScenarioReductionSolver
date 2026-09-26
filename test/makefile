##############################################################################
################################ makefile ####################################
##############################################################################
#                                                                            #
#   makefile of the ScenarioReductionSolver tests                            #
#                                                                            #
#                                Donato Meoli                                #
#                         Dipartimento di Informatica                        #
#                             Universita' di Pisa                            #
#                                                                            #
##############################################################################

# the executables built here
NAMES = ScenarioReductionSolver_test ScenarioReductionSolver_unit_test

# basic directory
DIR = .

# compiler
CC = clang++

# common flags
COMMON_SW = -std=c++20 -ferror-limit=1 -Wno-enum-compare

# debug switches
SW_DEBUG = -g3 -glldb -fno-inline $(COMMON_SW)

# production switches
SW_RELEASE = -O3 $(COMMON_SW) -DNDEBUG

# default target - build in release mode
default: SW = $(SW_RELEASE)
default: $(addprefix $(DIR)/,$(NAMES))

# debug target - build in debug mode
debug: SW = $(SW_DEBUG)
debug: $(addprefix $(DIR)/,$(NAMES))

# define & include the necessary modules- - - - - - - - - - - - - - - - - - -

# SMS++
SMS++SDR = ../../SMS++
include $(SMS++SDR)/lib/makefile-inc

# ScenarioReductionSolver (brings TwoStageStochasticBlock and StochasticBlock
# in input)
SRSkSDR = ..
include $(SRSkSDR)/makefile-s

# main module (linking phase) - - - - - - - - - - - - - - - - - - - - - - - -

# object files
MOBJ =  $(SRSkOBJ) $(SMS++OBJ)

# libraries
MLIB =  $(SRSkLIB) $(SMS++LIB)

$(DIR)/ScenarioReductionSolver_test: $(MOBJ) $(DIR)/test.o
	$(CC) -o $@ $(DIR)/test.o $(MOBJ) $(MLIB) $(SW)

$(DIR)/ScenarioReductionSolver_unit_test: $(MOBJ) $(DIR)/unit_test.o
	$(CC) -o $@ $(DIR)/unit_test.o $(MOBJ) $(MLIB) $(SW)

# dependencies: every .o from its .cpp + every recursively included .h- - - -

# include directives
MINC =  $(SMS++INC) $(SRSkINC)

# includes
MH =    $(SMS++H) $(SRSkH)

# compile command
$(DIR)/%.o: $(DIR)/%.cpp $(MH)
	$(CC) -c $< -o $@ $(MINC) $(SW)

# clean target
clean::
	rm -f $(DIR)/*.o $(DIR)/*~ $(addprefix $(DIR)/,$(NAMES))

# phony targets
.PHONY: default debug clean

############################ End of makefile #################################
