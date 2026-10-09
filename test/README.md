# test

The testers of the `ScenarioReductionSolver` module, which need nothing but
the module and its dependencies (`TwoStageStochasticBlock`, hence
`StochasticBlock`, and the core SMS++ library).

- `ScenarioReductionSolver_test` is the smoke test: that
  `ScenarioReductionSolver` and `CSSCScenarioReductionSolver` are in the
  Solver factory, i.e., that the library is there and its static
  initialization ran.

- `ScenarioReductionSolver_unit_test` runs the four heuristics of
  `ScenarioReductionSolver` (`baseline`, `dupacova`, `bestfit` and
  `firstfit`) on small `DiscreteScenarioSet` filled in memory, whose
  reduction is known by construction: `K = N`, `K = 1`, identical
  scenarios, non-uniform weights and an invalid `K`. It checks that the `K`
  representatives are distinct scenarios of the set, that every scenario is
  assigned to one of them, that the weight of a representative is the mass
  of the scenarios assigned to it, and the Wasserstein distance where the
  optimum is known.

The reduction of an actual `TwoStageStochasticBlock`, i.e., of the
instances of a model and with `CSSCScenarioReductionSolver`, which needs a
`:MILPSolver`, is tested in the suites of the umbrella: the tester that
reads such an instance, reduces it and solves the reduced problem is
`TSSB_scenred_test` of `tests/TwoStageStochasticBlock`, which the
`batches-scenred` batteries of `tests/UCBlock` and
`tests/CapacitatedFacilityLocationBlock` run on the instances of their
Block.

Both are built by the provided `makefile` (or via CMake from the umbrella,
where each is registered as a separate `ctest` labelled
`ScenarioReductionSolver`). Run them as `./<name>`, with no argument.


## Authors

- **Minh Duc Pham**  
  Dipartimento di Informatica  
  Università di Pisa


## License

This code is provided free of charge under the [GNU Lesser General Public
License version 3.0](https://opensource.org/licenses/lgpl-3.0.html) -
see the [LICENSE](LICENSE) file for details.
