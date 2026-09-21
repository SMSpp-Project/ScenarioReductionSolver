# test

A tester for `ScenarioReductionSolver` and `CSSCScenarioReductionSolver`.

It reads a `TwoStageStochasticBlock` out of a netCDF file, with its scenario
set and the `AbstractPath` that say which the here-and-now `Variable` are,
reduces the scenarios to the `K` representatives one method picks, solves the
reduced problem and reports the in-sample gap against the value the whole set
gives.

Nothing here knows of any concrete Block: what the first-stage `Variable` are
and how the data of a scenario maps onto the model is read from the file
itself, through the `AbstractPath` mechanism, hence the same tester runs on
whichever Block wrote that file. Writing one is necessarily the business of
that Block, and is done by the generator of its own test suite.

    ./ScenarioReductionSolver_test -i <tssb.nc4> -m <method> -r <K>
                                   -c <BlockSolverConfig>

with `-m` one of `baseline`, `dupacova`, `bestfit`, `firstfit` and `cssc`. The
`makefile` builds the executable including this module and the core SMS++
library.


## Authors

- **Minh Duc Pham**  
  Dipartimento di Informatica  
  Università di Pisa


## License

This code is provided free of charge under the [GNU Lesser General Public
License version 3.0](https://opensource.org/licenses/lgpl-3.0.html) -
see the [LICENSE](LICENSE) file for details.
