# --------------------------------------------------------------------------- #
#    CMake file for ScenarioReductionSolver/test                              #
#                                                                             #
#    In this file we define the unit tests for this library.                  #
#    Tests that should be supported by ctest executable must be added         #
#    with the add_test() command.                                             #
#                                                                             #
#                                Donato Meoli                                 #
#                         Dipartimento di Informatica                         #
#                             Universita' di Pisa                             #
# --------------------------------------------------------------------------- #

# The classes of the modules register themselves in the factories from
# static objects, which nothing here names: a shared library is kept by
# what its module asks of the linker, while an archive has to be taken
# whole [see SMSppModule.cmake of SMS++].
smspp_keep_modules()

# ----- ScenarioReductionSolver_test ---------------------------------------- #

# Smoke test: the two Solver of the module are in the factory.
add_executable(${modName}_test test.cpp)
target_link_libraries(${modName}_test PRIVATE ${modNamespace}::${modName})

smspp_copy_runtime(${modName}_test)

add_test(NAME ${modName}_test
         COMMAND ${modName}_test)

# ----- ScenarioReductionSolver_unit_test ----------------------------------- #

# The heuristics on synthetic scenario sets whose reduction is known.
add_executable(${modName}_unit_test unit_test.cpp)
target_link_libraries(${modName}_unit_test PRIVATE ${modNamespace}::${modName})

smspp_copy_runtime(${modName}_unit_test)

add_test(NAME ${modName}_unit_test
         COMMAND ${modName}_unit_test)

# ----- the label of this module's tests ------------------------------------ #

# The label lets the module CI select exactly the tests exercising this module
# with `ctest -L <module>` (see tests/cmake/TestLabels.cmake in the umbrella
# for the system-tests counterpart): without it these tests are built and
# never run.
set_tests_properties(${modName}_test ${modName}_unit_test
                     PROPERTIES LABELS "${modName}")

# --------------------------------------------------------------------------- #
