/*--------------------------------------------------------------------------*/
/*------------------------------ File test.cpp -----------------------------*/
/*--------------------------------------------------------------------------*/
/** @file
 * Smoke test for ScenarioReductionSolver: constructs a ScenarioReductionSolver via the Block
 * factory, checking that the module links correctly and the class is
 * registered. Replace it with real tests exercising the module.
 *
 * \author Minh Duc Pham \n
 *         Dipartimento di Informatica \n
 *         Universita' di Pisa \n
 *
 * \copyright &copy; by Minh Duc Pham
 */
/*--------------------------------------------------------------------------*/
/*------------------------------ INCLUDES ----------------------------------*/
/*--------------------------------------------------------------------------*/

#include <iostream>

#include "ScenarioReductionSolver.h"

/*--------------------------------------------------------------------------*/
/*-------------------------------- USING -----------------------------------*/
/*--------------------------------------------------------------------------*/

using namespace SMSpp_di_unipi_it;

/*--------------------------------------------------------------------------*/
/*-------------------------------- main() ----------------------------------*/
/*--------------------------------------------------------------------------*/

int main( int argc , char ** argv )
{
 // construct a ScenarioReductionSolver via the Block factory: this checks that the
 // class is registered and the library is linked in (whole-archive)
 auto block = Block::new_Block( "ScenarioReductionSolver" );

 if( ! block ) {
  std::cerr << "ScenarioReductionSolver not present in Block factory" << std::endl;
  return( 1 );
  }

 if( ! dynamic_cast< ScenarioReductionSolver * >( block ) ) {
  std::cerr << "factory did not return a ScenarioReductionSolver" << std::endl;
  delete block;
  return( 1 );
  }

 delete block;

 std::cout << "ScenarioReductionSolver: all tests passed" << std::endl;

 return( 0 );
 }

/*--------------------------------------------------------------------------*/
/*---------------------------- End File test.cpp ---------------------------*/
/*--------------------------------------------------------------------------*/
