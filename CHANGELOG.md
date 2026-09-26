# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- `ScenarioReductionSolver_unit_test`, the four heuristics on small
  scenario sets whose reduction is known by construction: `K = N`, `K = 1`,
  identical scenarios, non-uniform weights and an invalid `K`

### Changed

- `ScenarioReductionSolver_test` is only the smoke test of the factory, and
  links nothing but the module: the reduction of the instance of a file,
  which needed the Block of the instance and a `:MILPSolver`, is
  `TSSB_scenred_test` of the `TwoStageStochasticBlock` suite of the tests

- the module calls `include(CTest)` as the others do, rather than
  `enable_testing()` right before its tests

- the makefile asks for `-O3 -DNDEBUG` and nothing else, the macro of the
  patch for `boost::any` on macOS having no reason to be there since there is
  no `boost::any` left in the core

- whoever links the module keeps it: the classes of a module register
  themselves in the factory from a static initialiser, and a linker that
  drops what looks unused takes the registration away with it, so the target
  now tells whoever links it to keep the symbol that forces the module in,
  and on ELF, where naming the symbol is not enough, the library as a whole

### Fixed

- the heuristics of `ScenarioReductionSolver` weighed every scenario 1/N
  whatever the probabilities of the `DiscreteScenarioSet`, so that the
  baseline did not pick the heaviest scenarios and the aggregated weights
  of the representatives were not the mass of their scenarios: they now
  read the weights of the pool

- on macOS a program linking the module lost the classes the module
  registers in the factories when the linker dropped the library, as it
  does under `-dead_strip_dylibs`, which conda sets: the target now asks the
  linker for the symbol that forces the module in (`-u`), which ld64,
  unlike the ELF linker, counts as a use of the library

## [0.2.0] - 2026-09-12

### Changed

- the version of the module is the git tag of its repository, or the
  VERSION.txt of a release tarball, and the shared library carries it: its
  SONAME is major.minor while the major is 0, and it is installed with an
  RPATH relative to itself, so that an installed tree keeps working wherever
  it is moved

### Fixed

- the CI moves the submodules of the umbrella it caches to the commits the
  umbrella pins, which `git pull` alone does not do, so it no longer builds
  the sources of whenever the cache was filled, as in every other module

- the test is registered with CTest, carrying the label the module CI selects
  it by, and with no instance to reduce it is the smoke test that the two
  Solver are in the factory

## [0.1.0] - 2026-07-15

### Added

- initial module skeleton generated from ModuleTemplate

- `ScenarioReductionSolver`, heuristic scenario reduction (Baseline, Dupacova,
  BestFit, FirstFit)

- `CSSCScenarioReductionSolver`, scenario reduction via Consistent Scenario
  Subset Clustering

[Unreleased]: https://gitlab.com/smspp/scenarioreductionsolver/-/compare/0.2.0...develop
[0.2.0]: https://gitlab.com/smspp/scenarioreductionsolver/-/compare/0.1.0...0.2.0
[0.1.0]: https://gitlab.com/smspp/scenarioreductionsolver/-/tags/0.1.0
