/*--------------------------------------------------------------------------*/
/*------------------- File ScenarioReductionSolver.cppm --------------------*/
/*--------------------------------------------------------------------------*/
/** @file
 * Interface of the C++20 module smspp.scenarioreductionsolver, which exports
 * every name that the headers of ScenarioReductionSolver declare at namespace
 * scope, together with the modules it depends on; a translation unit can then
 * write
 *
 *     import smspp.scenarioreductionsolver;
 *
 * in place of the #include of the headers. The macros (e.g., those of the
 * factory in SMSFactory.h) are not exported by a module, so a file that uses
 * them still includes the header that defines them.
 *
 * This file is written by SMS++/cmake/smspp_module_exports.py, which reads
 * the names from the AST of the headers: it is not to be edited by hand.
 *
 * \author Benoît Tran \n
 *         Dipartimento di Informatica \n
 *         Universita' di Pisa \n
 *
 * \copyright &copy; by Benoît Tran
 */
/*--------------------------------------------------------------------------*/
/*------------------------- GLOBAL MODULE FRAGMENT -------------------------*/
/*--------------------------------------------------------------------------*/

module;

#include "CSSCScenarioReductionSolver.h"
#include "ScenarioReductionCommon.h"
#include "ScenarioReductionSolver.h"

/*--------------------------------------------------------------------------*/
/*----------------------------- MODULE PURVIEW -----------------------------*/
/*--------------------------------------------------------------------------*/

export module smspp.scenarioreductionsolver;

export import smspp.twostagestochasticblock;

export namespace SMSpp_di_unipi_it {

 // CSSCScenarioReductionSolver.h
 using SMSpp_di_unipi_it::CSSCScenarioReductionSolver;

 // ScenarioReductionCommon.h
 using SMSpp_di_unipi_it::ProblemHooks;
 using SMSpp_di_unipi_it::ScenarioReductionMetrics;
 using SMSpp_di_unipi_it::ScenarioReductionState;
 using SMSpp_di_unipi_it::SolutionResult;
 using SMSpp_di_unipi_it::get_dbl_config;
 using SMSpp_di_unipi_it::get_int_config;
 using SMSpp_di_unipi_it::get_str_config;
 using SMSpp_di_unipi_it::run_scenario_reduction_test;

 // ScenarioReductionSolver.h
 using SMSpp_di_unipi_it::ScenarioReductionSolver;
}

/*--------------------------------------------------------------------------*/
/*----------------- End File ScenarioReductionSolver.cppm ------------------*/
/*--------------------------------------------------------------------------*/
