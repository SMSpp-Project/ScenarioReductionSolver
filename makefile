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
#   Input:  $(CC)        = compiler command                                  #
#           $(SW)        = compiler options                                  #
#           $(SMS++INC)  = the -I$( core SMS++ directory )                   #
#           $(SMS++OBJ)  = the libSMS++ library itself                       #
#              $(SRSkSDR)  = the directory where the source is               #
#                                                                            #
#   Output: $(SRSkOBJ)  = the final object(s) / library                      #
#                   $(SRSkH)    = the .h files to include                    #
#                 $(SRSkINC)  = the -I$( source directory )                  #
#                                                                            #
#                             Antonio Frangioni                              #
#                         Dipartimento di Informatica                        #
#                             Universita' di Pisa                            #
#                                                                            #
##############################################################################

# macros to be exported - - - - - - - - - - - - - - - - - - - - - - - - - - -

SRSkOBJ = $(SRSkSDR)/obj/ScenarioReductionSolver.o

SRSkINC = -I$(SRSkSDR)/include

SRSkH   = $(SRSkSDR)/include/ScenarioReductionSolver.h

# clean - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

clean::
	rm -f $(SRSkOBJ) $(SRSkSDR)/*~

# dependencies: every .o from its .cpp + every recursively included .h- - - -

$(SRSkSDR)/obj/ScenarioReductionSolver.o: $(SRSkSDR)/src/ScenarioReductionSolver.cpp \
	$(SRSkSDR)/include/ScenarioReductionSolver.h $(SMS++H) $(SMS++OBJ)
	$(CC) -c $(SRSkSDR)/src/ScenarioReductionSolver.cpp -o $@ \
	$(SRSkINC) $(SMS++INC) $(SW)

########################## End of makefile ###################################
