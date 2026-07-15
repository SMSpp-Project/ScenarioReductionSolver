##############################################################################
################################ makefile ####################################
##############################################################################
#                                                                            #
#   makefile of ScenarioReductionSolver                                      #
#                                                                            #
#   Note that $(SMS++INC) is assumed to include any -I directive             #
#   corresponding to external libraries needed by SMS++, at least to the     #
#   extent in which they are needed by the parts of SMS++ used by            #
#   ScenarioReductionSolver.                                                 #
#                                                                            #
#   Input:  $(CC)         = compiler command                                 #
#           $(SW)         = compiler options                                 #
#           $(SMS++INC)   = the -I$( core SMS++ directory )                  #
#           $(SMS++OBJ)   = the libSMS++ library itself                      #
#           $(StcBlkINC)  = the -I$( StochasticBlock source directory )      #
#           $(TSSBkINC)   = the -I$( TwoStageStochasticBlock source dir )    #
#           $(SRSkSDR)    = the directory where the source is                #
#                                                                            #
#   Output: $(SRSkOBJ)    = the final object(s) / library                    #
#           $(SRSkH)      = the .h files to include                          #
#           $(SRSkINC)    = the -I$( source directory )                      #
#                                                                            #
#                             Antonio Frangioni                              #
#                        Dipartimento di Informatica                         #
#                            Universita' di Pisa                             #
#                                                                            #
##############################################################################

# macros to be exported - - - - - - - - - - - - - - - - - - - - - - - - - - -

SRSkOBJ = $(SRSkSDR)/obj/ScenarioReductionCommon.o \
	$(SRSkSDR)/obj/ScenarioReductionSolver.o \
	$(SRSkSDR)/obj/CSSCScenarioReductionSolver.o

SRSkINC = -I$(SRSkSDR)/include

SRSkH   = $(SRSkSDR)/include/ScenarioReductionCommon.h \
	$(SRSkSDR)/include/ScenarioReductionSolver.h \
	$(SRSkSDR)/include/CSSCScenarioReductionSolver.h

# clean - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

clean::
	rm -f $(SRSkOBJ) $(SRSkSDR)/*~

# dependencies: every .o from its .cpp + every recursively included .h- - - -

$(SRSkSDR)/obj/ScenarioReductionSolver.o: \
	$(SRSkSDR)/src/ScenarioReductionSolver.cpp \
	$(SRSkSDR)/include/ScenarioReductionSolver.h \
	$(StcBlkH) $(TSSBkH) $(SMS++OBJ)
	$(CC) -c $(SRSkSDR)/src/ScenarioReductionSolver.cpp -o $@ \
	$(SRSkINC) $(StcBlkINC) $(TSSBkINC) $(SMS++INC) $(SW)

$(SRSkSDR)/obj/CSSCScenarioReductionSolver.o: \
	$(SRSkSDR)/src/CSSCScenarioReductionSolver.cpp \
	$(SRSkSDR)/include/CSSCScenarioReductionSolver.h \
	$(StcBlkH) $(TSSBkH) $(SMS++OBJ)
	$(CC) -c $(SRSkSDR)/src/CSSCScenarioReductionSolver.cpp -o $@ \
	$(SRSkINC) $(StcBlkINC) $(TSSBkINC) $(SMS++INC) $(SW)

$(SRSkSDR)/obj/ScenarioReductionCommon.o: \
	$(SRSkSDR)/src/ScenarioReductionCommon.cpp \
	$(SRSkSDR)/include/ScenarioReductionCommon.h \
	$(SRSkSDR)/include/ScenarioReductionSolver.h \
	$(SRSkSDR)/include/CSSCScenarioReductionSolver.h \
	$(StcBlkH) $(TSSBkH) $(SMS++OBJ)
	$(CC) -c $(SRSkSDR)/src/ScenarioReductionCommon.cpp -o $@ \
	$(SRSkINC) $(StcBlkINC) $(TSSBkINC) $(SMS++INC) $(SW)

########################## End of makefile ###################################
