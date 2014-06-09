/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

// Moose includes
#include "ConsoleStream.h"

ConsoleStream::ConsoleStream(const OutputWarehouse & output_warehouse) :
    _output_warehouse(output_warehouse)
{
}

ConsoleStream &
ConsoleStream::operator<<(StandardEndLine manip)
{
  manip(Moose::out);
  return *this;
}

void
ConsoleStream::flush()
{
  _oss.flush();
}