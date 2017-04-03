//                                               -*- C++ -*-
/**
 *  @brief Factory for Trapezoidal distribution
 *
 *  Copyright 2005-2017 Airbus-EDF-IMACS-Phimeca
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef OPENTURNS_TRAPEZOIDALFACTORY_HXX
#define OPENTURNS_TRAPEZOIDALFACTORY_HXX

#include "openturns/OTprivate.hxx"
#include "openturns/DistributionFactoryImplementation.hxx"
#include "openturns/Trapezoidal.hxx"
#include "openturns/OptimizationAlgorithm.hxx"

BEGIN_NAMESPACE_OPENTURNS

/**
 * @class TrapezoidalFactory
 */
class OT_API TrapezoidalFactory
  : public DistributionFactoryImplementation
{
  CLASSNAME;
public:

  /** Default constructor */
  TrapezoidalFactory();

  /** Virtual constructor */
  TrapezoidalFactory * clone() const;

  /* Here is the interface that all derived class must implement */
  using DistributionFactoryImplementation::build;

  Implementation build( const Sample & sample ) const;
  Implementation build(const NumericalPoint & parameters) const;
  Implementation build() const;
  Trapezoidal buildAsTrapezoidal( const Sample & sample ) const;
  Trapezoidal buildAsTrapezoidal(const NumericalPoint & parameters) const;
  Trapezoidal buildAsTrapezoidal() const;

  /** Optimization solver accessor */
  OptimizationAlgorithm getOptimizationAlgorithm() const;
  void setOptimizationAlgorithm(const OptimizationAlgorithm & solver);

  // @deprecated
  OptimizationAlgorithm getOptimizationSolver() const;
  void setOptimizationSolver(const OptimizationAlgorithm & solver);

protected:
  /** Likelihood constraint accessor */
  Function getLogLikelihoodInequalityConstraint() const;

  /** likelihood estimate */
  NumericalPoint computeLogLikelihoodInequalityConstraint( const NumericalPoint & x ) const;

  /** only used to pass data to be used in computeLogLikeliHood */
  mutable Sample sample_;

  /**   OptimizationAlgorithm   */
  mutable OptimizationAlgorithm solver_;

}; /* class TrapezoidalFactory */

END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_TRAPEZOIDALFACTORY_HXX */
