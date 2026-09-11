# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

### Changed

### Fixed

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
