/*--------------------------------------------------------------------------*/
/*----------------------------- File test.cpp ------------------------------*/
/*--------------------------------------------------------------------------*/
/** @file
 * Smoke test of the module: that the two Solver it defines,
 * ScenarioReductionSolver and CSSCScenarioReductionSolver, are in the Solver
 * factory, i.e., that the library is there and its static initialization
 * ran. What the heuristics compute is checked by the unit test of the module
 * [see unit_test.cpp]; the reduction of an actual TwoStageStochasticBlock,
 * which needs a Block of a model and a :MILPSolver, is checked in the suites
 * of the umbrella.
 *
 * \author Minh Duc Pham \n
 *         Dipartimento di Informatica \n
 *         Universita' di Pisa \n
 */
/*--------------------------------------------------------------------------*/

#include "Solver.h"

#include <iostream>

using namespace SMSpp_di_unipi_it;

/*--------------------------------------------------------------------------*/

int main( void )
{
 for( const auto & name : { "ScenarioReductionSolver" ,
                            "CSSCScenarioReductionSolver" } ) {
  if( ! Solver::has_Solver( name ) ) {
   std::cerr << name << " is not in the Solver factory" << std::endl;
   return( 1 );
   }
  std::cout << name << " is in the Solver factory" << std::endl;
  }

 return( 0 );
 }

/*--------------------------------------------------------------------------*/
/*--------------------------- End File test.cpp ----------------------------*/
/*--------------------------------------------------------------------------*/
