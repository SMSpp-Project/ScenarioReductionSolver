/*--------------------------------------------------------------------------*/
/*--------------------------- File unit_test.cpp ---------------------------*/
/*--------------------------------------------------------------------------*/
/** @file
 * Unit test of the heuristics of ScenarioReductionSolver (baseline,
 * Dupacova, best-fit and first-fit) on small synthetic DiscreteScenarioSet,
 * whose optimal reduction is known by construction, so that what is checked
 * is the value and not only the shape of the result. It needs nothing but
 * the module and its dependencies: the ScenarioReductionBlock the Solver is
 * attached to comes from StochasticBlock, and the DiscreteScenarioSet is
 * filled in memory.
 *
 * The cases are the edge ones of a reduction of N scenarios to K:
 *
 * - K = N, where every scenario represents itself and the Wasserstein
 *   distance is 0;
 *
 * - K = 1, where Dupacova and the two local searches have to find the
 *   medoid of the set, and the only representative takes all the mass;
 *
 * - identical scenarios, where the distance is 0 whatever is picked and
 *   the K representatives still have to be K distinct indices;
 *
 * - non-uniform weights, where the baseline has to pick the K scenarios
 *   of highest weight and the aggregated weight of a representative is the
 *   sum of those of the scenarios assigned to it;
 *
 * - the invalid K (0 and N + 1), which compute() refuses.
 *
 * \author Donato Meoli \n
 *         Dipartimento di Informatica \n
 *         Universita' di Pisa \n
 *
 * \copyright &copy; by Donato Meoli
 */
/*--------------------------------------------------------------------------*/
/*------------------------------ INCLUDES ----------------------------------*/
/*--------------------------------------------------------------------------*/

#include "DiscreteScenarioSet.h"
#include "ScenarioReductionBlock.h"
#include "ScenarioReductionSolver.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>

/*--------------------------------------------------------------------------*/

using namespace SMSpp_di_unipi_it;

using Algorithm = ScenarioReductionSolver::Algorithm;
using Index = ScenarioGenerator::ScenarioIndex;
using Scenarios = std::vector< std::vector< double > >;

/*--------------------------------------------------------------------------*/

static int failures = 0;

static void check( bool cond , const std::string & what )
{
 std::cout << ( cond ? "  ok   " : "  FAIL " ) << what << std::endl;
 if( ! cond )
  ++failures;
 }

static void check_eq( double a , double b , const std::string & what )
{
 check( std::abs( a - b ) <= 1e-9 , what + " (got " + std::to_string( a ) +
        ", want " + std::to_string( b ) + ")" );
 }

/*--------------------------------------------------------------------------*/

static const std::vector< std::pair< Algorithm , std::string > > algorithms = {
 { Algorithm::Baseline , "baseline" } ,
 { Algorithm::Dupacova , "dupacova" } ,
 { Algorithm::BestFit  , "bestfit"  } ,
 { Algorithm::FirstFit , "firstfit" } };

/*--------------------------------------------------------------------------*/
// a DiscreteScenarioSet filled in memory, its pool being the whole set

static std::unique_ptr< DiscreteScenarioSet > make_dss(
 const Scenarios & scenarios , const std::vector< double > & weights = {} )
{
 auto dss = std::make_unique< DiscreteScenarioSet >();
 dss->load_from_memory( scenarios , weights );
 dss->init_representative_pool();
 return( dss );
 }

/*--------------------------------------------------------------------------*/
// what a reduction returns: the solution the Solver writes in the Block and
// the Wasserstein distance it reports

struct Reduction {
 ScenarioReductionBlockSolution sol;
 double value;
 };

static Reduction reduce( DiscreteScenarioSet * dss , int K , Algorithm a )
{
 ScenarioReductionBlock srb;
 srb.set_scenario_generator( dss );

 ScenarioReductionSolver srs;
 srs.set_nb_reduced( K );
 srs.set_algorithm( a );
 srs.set_Block( &srb );

 const int status = srs.compute();
 if( status != Solver::kOK )
  throw( std::runtime_error( "compute() returned " +
                             std::to_string( status ) ) );
 srs.get_var_solution();

 Reduction r{ srb.get_solution() , srs.get_var_value() };
 srs.set_Block( nullptr );
 return( r );
 }

/*--------------------------------------------------------------------------*/
// the properties every reduction of N scenarios to K has to have: K distinct
// representatives among the N, every scenario assigned to one of them, and
// aggregated weights that sum to 1, each being the sum of the weights of the
// scenarios assigned to that representative

static void check_valid( const Reduction & r ,
                         const std::vector< double > & w ,
                         std::size_t K , const std::string & tag )
{
 const auto N = w.size();
 const auto & s = r.sol;

 check( s.selected_indices.size() == K , tag + ": K representatives" );
 const std::set< Index > sel( s.selected_indices.begin() ,
                              s.selected_indices.end() );
 check( sel.size() == s.selected_indices.size() ,
        tag + ": the representatives are distinct" );
 check( std::all_of( sel.begin() , sel.end() ,
                     [ N ]( Index i ) { return( i < N ); } ) ,
        tag + ": the representatives are scenarios of the set" );

 check( s.assignments.size() == N , tag + ": one assignment per scenario" );
 bool assigned = s.assignments.size() == N;
 for( std::size_t i = 0 ; assigned && i < N ; ++i )
  assigned = sel.count( s.assignments[ i ] ) > 0;
 check( assigned , tag + ": every scenario goes to a representative" );

 check( s.weights.size() == s.selected_indices.size() ,
        tag + ": one weight per representative" );
 if( ! assigned || s.weights.size() != s.selected_indices.size() )
  return;

 double sum = 0;
 bool aggregated = true;
 for( std::size_t k = 0 ; k < s.selected_indices.size() ; ++k ) {
  double mass = 0;
  for( std::size_t i = 0 ; i < N ; ++i )
   if( s.assignments[ i ] == s.selected_indices[ k ] )
    mass += w[ i ];
  aggregated = aggregated && std::abs( mass - s.weights[ k ] ) <= 1e-9;
  sum += s.weights[ k ];
  }
 check_eq( sum , 1 , tag + ": the weights sum to 1" );
 check( aggregated , tag + ": the weight of a representative is the mass "
                           "of its scenarios" );
 }

/*--------------------------------------------------------------------------*/
// K = N: nothing is reduced

static void test_K_equals_N( void )
{
 std::cout << "K = N" << std::endl;
 const Scenarios sc = { { 0 , 0 } , { 1 , 0 } , { 0 , 2 } , { 3 , 3 } ,
                        { 5 , 1 } , { 2 , 7 } };
 const std::vector< double > w( sc.size() , 1.0 / sc.size() );

 for( const auto & [ a , name ] : algorithms ) {
  auto dss = make_dss( sc );
  const auto r = reduce( dss.get() , sc.size() , a );
  check_valid( r , w , sc.size() , name );
  bool self = r.sol.assignments.size() == sc.size();
  for( Index i = 0 ; self && i < sc.size() ; ++i )
   self = r.sol.assignments[ i ] == i;
  check( self , name + ": every scenario represents itself" );
  check_eq( r.value , 0 , name + ": the distance is 0" );
  }
 }

/*--------------------------------------------------------------------------*/
// K = 1: the representative is the medoid, i.e., the scenario minimising the
// sum of the distances to all the others, here the third of the points 0, 1,
// 2, 3 and 10 of the line, at distance 12 / 5 on average

static void test_K_equals_1( void )
{
 std::cout << "K = 1" << std::endl;
 const Scenarios sc = { { 0 } , { 1 } , { 2 } , { 3 } , { 10 } };
 const std::vector< double > w( sc.size() , 1.0 / sc.size() );

 for( const auto & [ a , name ] : algorithms ) {
  auto dss = make_dss( sc );
  const auto r = reduce( dss.get() , 1 , a );
  check_valid( r , w , 1 , name );
  if( r.sol.weights.size() == 1 )
   check_eq( r.sol.weights[ 0 ] , 1 , name + ": the representative takes "
                                             "all the mass" );
  if( a == Algorithm::Baseline )
   continue;  // the K heaviest scenarios, which with equal weights is any
  check( r.sol.selected_indices.size() == 1 &&
         r.sol.selected_indices[ 0 ] == 2 , name + ": the medoid is chosen" );
  check_eq( r.value , 12.0 / 5 , name + ": the distance of the medoid" );
  }
 }

/*--------------------------------------------------------------------------*/
// identical scenarios: every choice is optimal, but it is still a choice of
// K distinct scenarios

static void test_identical_scenarios( void )
{
 std::cout << "identical scenarios" << std::endl;
 const Scenarios sc( 5 , std::vector< double >{ 4 , -1 , 2 } );
 const std::vector< double > w( sc.size() , 1.0 / sc.size() );

 for( const auto & [ a , name ] : algorithms )
  for( int K : { 1 , 2 , 5 } ) {
   auto dss = make_dss( sc );
   const auto tag = name + " K = " + std::to_string( K );
   const auto r = reduce( dss.get() , K , a );
   check_valid( r , w , K , tag );
   check_eq( r.value , 0 , tag + ": the distance is 0" );
   }
 }

/*--------------------------------------------------------------------------*/
// non-uniform weights: two clusters of three points each, the one around 0
// carrying 0.8 of the mass and the one around 10 the remaining 0.2, and
// inside the first one the heaviest point at 0

static void test_nonuniform_weights( void )
{
 std::cout << "non-uniform weights" << std::endl;
 const Scenarios sc = { { 10 } , { 0 } , { 11 } , { 1 } , { 12 } , { -1 } };
 const std::vector< double > w = { 0.05 , 0.5 , 0.1 , 0.15 , 0.05 , 0.15 };

 for( const auto & [ a , name ] : algorithms ) {
  auto dss = make_dss( sc , w );
  const auto r = reduce( dss.get() , 2 , a );
  check_valid( r , w , 2 , name );
  std::set< Index > sel( r.sol.selected_indices.begin() ,
                         r.sol.selected_indices.end() );
  if( a == Algorithm::Baseline ) {
   // the two heaviest, 0 (weight 0.5) and either of 1 and -1 (0.15)
   check( sel.count( 1 ) && ( sel.count( 3 ) || sel.count( 5 ) ) ,
          name + ": the two heaviest scenarios are chosen" );
   continue;
   }
  // one representative per cluster: 0 for the first one, where it is the
  // weighted medoid, and 11 for the second one, where it is the medoid;
  // the distance is then 0.15 + 0.15 + 0.05 + 0.05 = 0.4
  check( sel == std::set< Index >{ 1 , 2 } ,
         name + ": the weighted medoid of each cluster is chosen" );
  check_eq( r.value , 0.4 , name + ": the weighted distance" );
  }
 }

/*--------------------------------------------------------------------------*/
// K out of ( 0 , N ] is refused

static void test_invalid_K( void )
{
 std::cout << "invalid K" << std::endl;
 const Scenarios sc = { { 0 } , { 1 } , { 2 } };

 for( const auto & [ a , name ] : algorithms )
  for( int K : { 0 , 4 } ) {
   auto dss = make_dss( sc );
   ScenarioReductionBlock srb;
   srb.set_scenario_generator( dss.get() );
   ScenarioReductionSolver srs;
   srs.set_nb_reduced( K );
   srs.set_algorithm( a );
   srs.set_Block( &srb );
   bool thrown = false;
   try { srs.compute(); }
   catch( const std::logic_error & ) { thrown = true; }
   check( thrown , name + ": K = " + std::to_string( K ) + " is refused" );
   srs.set_Block( nullptr );
   }
 }

/*--------------------------------------------------------------------------*/

int main( void )
{
 const std::vector< std::pair< void ( * )( void ) , std::string > > tests = {
  { test_K_equals_N , "K = N" } ,
  { test_K_equals_1 , "K = 1" } ,
  { test_identical_scenarios , "identical scenarios" } ,
  { test_nonuniform_weights , "non-uniform weights" } ,
  { test_invalid_K , "invalid K" } };

 for( const auto & [ t , name ] : tests )
  try { t(); }
  catch( const std::exception & e ) {
   check( false , name + " threw: " + e.what() );
   }

 std::cout << ( failures ? "FAILED: " : "PASSED: " ) << failures
           << " failure(s)" << std::endl;
 return( failures == 0 ? 0 : 1 );
 }

/*--------------------------------------------------------------------------*/
/*------------------------- End File unit_test.cpp -------------------------*/
/*--------------------------------------------------------------------------*/
