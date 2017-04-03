//                                               -*- C++ -*-
/**
 *  @brief The test file of class Staircase for standard methods
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
#include "openturns/OT.hxx"
#include "openturns/OTtestcode.hxx"

using namespace OT;
using namespace OT::Test;

int main(int argc, char *argv[])
{
  TESTPREAMBLE;
  OStream fullprint(std::cout);
  setRandomGenerator();

  try
  {

    // Instanciate one distribution object
    UnsignedInteger dim = 1;
    NumericalPoint meanPoint(dim, 1.0);
    meanPoint[0] = 0.5;
    NumericalPoint sigma(dim, 1.0);
    sigma[0] = 2.0;
    CorrelationMatrix R = IdentityMatrix(dim);
    Normal distribution1(meanPoint, sigma, R);

    // Instanciate another distribution object
    meanPoint[0] = -1.5;
    sigma[0] = 4.0;
    Normal distribution2(meanPoint, sigma, R);

    // Test for sampling
    UnsignedInteger size = 2000;
    UnsignedInteger nPoints = 20;
    Sample sample1(distribution1.getSample( size ));
    Sample sample2(distribution2.getSample( size ));

    // Construct empirical CDF for each sample
    Sample data1(nPoints, 2), data2(nPoints, 2);
    NumericalPoint cursor1(2);
    NumericalPoint cursor2(2);
    NumericalScalar count1;
    NumericalScalar count2;

    for(UnsignedInteger i = 0; i < nPoints; i++)
    {
      cursor1[0] = 13.*i / nPoints - 6.5;
      count1 = 0;
      cursor2[0] = 24.*i / nPoints - 13.5;
      count2 = 0;

      for(UnsignedInteger j = 0; j < size; j++)
      {
        if(sample1[j][0] < cursor1[0]) count1++;
        if(sample2[j][0] < cursor2[0]) count2++;
      }

      cursor1[1] = count1 / size;
      cursor2[1] = count2 / size;

      data1[i] = cursor1;
      data2[i] = cursor2;
    }

    // Create an empty graph
    Graph myGraph("Some curves", "x1", "x2", true, "bottomright");

    // Create the first staircase
    Staircase myStaircase1(data1, "blue", "solid", "s", "");

    Staircase myStaircase1b(myStaircase1);
    myStaircase1b.setPattern("S");
    myStaircase1b.setColor("green");
    myStaircase1b.setLineStyle("dashed");
    myStaircase1b.setLegend("eCDF1b, pat=S");

    // Then, draw it
    myGraph.add(myStaircase1);
    myGraph.add(myStaircase1b);
    myGraph.draw("Graph_Staircase_a_OT.png");

    // Check that the correct files have been generated by computing their checksum

    // Create the second staircase
    Staircase myStaircase2(data2, "red", "dashed", "S", "eCDF2, pat=S");

    // Add it to the graph and draw everything
    myGraph.add(myStaircase2);
    myGraph.draw("Graph_Staircase_b_OT.png");

  }
  catch (TestFailed & ex)
  {
    std::cerr << ex << std::endl;
    return ExitCode::Error;
  }


  return ExitCode::Success;
}
