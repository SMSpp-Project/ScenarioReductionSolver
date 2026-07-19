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

if (BUILD_SHARED_LIBS)
    if (UNIX AND (NOT APPLE))
        add_link_options("-Wl,--no-as-needed")
    endif ()
else ()
    if (MSVC)
        add_link_options("/WHOLEARCHIVE" "/FORCE:MULTIPLE")
    else ()
        if (APPLE)
            add_link_options("-Wl,-all_load")
        else ()
            add_link_options("-Wl,--whole-archive,--allow-multiple-definition")
        endif ()
    endif ()
endif ()

add_executable(${modName}_test test.cpp)

# --------------------------------------------------------------------------- #
#    To test with a specific problem Block (e.g., CFL, UC,...),               #
#    add the corresponding SMS++::Block library below in                      #
#    target_link_libraries().                                                 #
#                                                                             #
#    The Block factory requires the corresponding library to be linked so that#
#    Block::deserialize() can instantiate the correct Block type.             #
#                                                                             #
#    Example:                                                                 #
#    To add support for a new Block FooBlock, include                         #
#                                                                             #
#     ${modNamespace}::FooBlock                                               #
#                                                                             #
#    in the target_link_libraries() list below.                               #
# --------------------------------------------------------------------------- #

target_link_libraries(${modName}_test PRIVATE
    ${modNamespace}::${modName}
    ${modNamespace}::CapacitatedFacilityLocationBlock
    ${modNamespace}::UCBlock
    ${modNamespace}::MILPSolver
)
