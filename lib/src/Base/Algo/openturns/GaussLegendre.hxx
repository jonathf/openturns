//                                               -*- C++ -*-
/**
 *  @brief This class allows to compute integrals of a function over an
 *         interval.
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
#ifndef OPENTURNS_GAUSSLEGENDRE_HXX
#define OPENTURNS_GAUSSLEGENDRE_HXX

#include "openturns/IntegrationAlgorithmImplementation.hxx"
#include "openturns/IntegrationAlgorithm.hxx"
#include "openturns/SpecFunc.hxx"

BEGIN_NAMESPACE_OPENTURNS

/**
 * @class GaussLegendre
 */

class OT_API GaussLegendre
  : public IntegrationAlgorithmImplementation
{

  CLASSNAME;

public:

  /** Default constructor */
  explicit GaussLegendre(const UnsignedInteger dimension = 1);

  /** Parameter constructor */
  explicit GaussLegendre(const Indices & discretization);

  /** Virtual copy constructor */
  virtual GaussLegendre * clone() const;

  /** Compute an approximation of \int_a^b f(x_1,\dots,x_n)dx_1\dotsdx_n, where [a,b] is an nD interval.
   */
  using IntegrationAlgorithmImplementation::integrate;
  NumericalPoint integrate(const NumericalMathFunction & function,
                           const Interval & interval) const;
  NumericalPoint integrateWithNodes(const NumericalMathFunction & function,
                                    const Interval & interval,
                                    NumericalSample & adaptedNodes) const;

  /** Discretization accessor */
  Indices getDiscretization() const;

  /** Nodes accessor */
  NumericalSample getNodes() const;

  /** Weights accessor */
  NumericalPoint getWeights() const;

  /** String converter */
  virtual String __repr__() const;

  /** String converter */
  virtual String __str__(const String & offset = "") const;

private:

  /* Generate nodes and weights */
  void generateNodesAndWeights();

  /* Discretization of the tensorized rule */
  Indices discretization_;

  /* Integration nodes */
  NumericalSample nodes_;

  /* Integration weights */
  NumericalPoint weights_;

} ; /* class GaussLegendre */

END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_GAUSSLEGENDRE_HXX */