# --------------------------------------------------------------------------- #
#    CMake file for ScenarioReductionSolver/test                              #
#                                                                             #
#    This file defines the test executable for this library.                  #
#    Tests that should be executed by CTest must be added using the           #
#    add_test() command.                                                      #
#                                                                             #
#                                Donato Meoli                                 #
#                         Dipartimento di Informatica                         #
#                             Universita' di Pisa                             #
# --------------------------------------------------------------------------- #

# Since we are using the Block factory, objects from linked libraries may
# appear unused, so the linker may discard them. Force the linker to keep
# them so that Block::deserialize() can instantiate the correct Block types.
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

# ----- ScenarioReductionSolver_test --------------------------------------- #
#
# Generic scenario-reduction test program. It reads a serialized
# TwoStageStochasticBlock instance, runs a scenario-reduction algorithm,
# and solves the reduced problem.
#
# To support a specific problem Block (e.g., CFL, UC, Investment),
# add the corresponding SMS++::Block library below in
# target_link_libraries().
#
# The Block factory requires the corresponding library to be linked so that
# Block::deserialize() can instantiate the correct Block type.
#
# Example:
#
#     ${modNamespace}::FooBlock
#
# Add it to the target_link_libraries() list below.
add_executable(${modName}_test test.cpp)

target_link_libraries(${modName}_test PRIVATE
    ${modNamespace}::${modName}
    ${modNamespace}::CapacitatedFacilityLocationBlock
    ${modNamespace}::UCBlock
    ${modNamespace}::MILPSolver
)

if (WIN32 AND BUILD_SHARED_LIBS AND NOT DEFINED ENV{CONDA_BUILD})
    # On Windows with shared libraries enabled, copy all runtime DLL
    # dependencies next to the executable in the build directory
    # (POST_BUILD), using CMake's TARGET_RUNTIME_DLLS generator expression.
    add_custom_command(TARGET ${modName}_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:${modName}_test>
        $<TARGET_FILE_DIR:${modName}_test>
        COMMAND_EXPAND_LISTS
        COMMENT "Copying runtime DLLs next to ${modName}_test.exe")
endif ()

# --------------------------------------------------------------------------- #