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

# Since we are using the block factory, objects from linked libraries
# may wrongly appear unused, and by default the linker does not include them,
# so we have to force the linking.
if (BUILD_SHARED_LIBS)
    if (UNIX AND (NOT APPLE))
        add_link_options("-Wl,--no-as-needed")
    endif ()
else ()
    if (MSVC)
        add_link_options("/WHOLEARCHIVE" "/FORCE:MULTIPLE")
    else () # Unix
        if (APPLE)
            add_link_options("-Wl,-all_load")
        else ()
            add_link_options("-Wl,--whole-archive,--allow-multiple-definition")
        endif ()
    endif ()
endif ()

# ----- ScenarioReductionSolver_test ---------------------------------------- #

# Generic scenario-reduction test: reads a serialized TwoStageStochasticBlock,
# runs a reduction algorithm and solves the reduced problem. Problem-specific
# Blocks and a MILP solver are linked when available, so the Block factory can
# deserialize (CFL, UC, ...) instances and solve the reduced problem.
add_executable(${modName}_test test.cpp)

target_link_libraries(${modName}_test PRIVATE ${modNamespace}::${modName})

if (TARGET ${modNamespace}::CapacitatedFacilityLocationBlock)
    target_link_libraries(${modName}_test PRIVATE
                          ${modNamespace}::CapacitatedFacilityLocationBlock)
endif ()

if (TARGET ${modNamespace}::UCBlock)
    target_link_libraries(${modName}_test PRIVATE ${modNamespace}::UCBlock)
endif ()

if (TARGET ${modNamespace}::MILPSolver)
    target_link_libraries(${modName}_test PRIVATE ${modNamespace}::MILPSolver)
endif ()

if (WIN32 AND BUILD_SHARED_LIBS AND NOT DEFINED ENV{CONDA_BUILD})
    # On Windows with shared libraries enabled copies all runtime DLL
    # dependencies next to the executable in the build directory
    # (POST_BUILD), using CMake's TARGET_RUNTIME_DLLS generator expression
    add_custom_command(TARGET ${modName}_test POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:${modName}_test>
            $<TARGET_FILE_DIR:${modName}_test>
            COMMAND_EXPAND_LISTS
            COMMENT "Copying runtime DLLs next to ${modName}_test.exe")
endif ()

# --------------------------------------------------------------------------- #
