/*****************************************/
/* Written by andrew.wilkins@csiro.au    */
/* Please contact me if you make changes */
/*****************************************/

//  saturation as a function of effective saturation, and its derivs wrt effective saturation
//
#include "RichardsSat.h"

template<>
InputParameters validParams<RichardsSat>()
{
  InputParameters params = validParams<GeneralUserObject>();
  params.addRequiredRangeCheckedParam<Real>("s_res", "s_res >= 0 & s_res < 1", "Residual fluid saturation for the phase.  0 <= s_res < 1.");
  params.addRequiredRangeCheckedParam<Real>("sum_s_res", "sum_s_res < 1", "Sum of s_res over all phases.  s_res <= sum_s_res < 1.  It is up to you to ensure the sum is done correctly.");
  params.addClassDescription("User object yielding saturation for a phase as a function of effective saturation of that phase");
  return params;
}

RichardsSat::RichardsSat(const std::string & name, InputParameters parameters) :
  GeneralUserObject(name, parameters),
  _s_res(getParam<Real>("s_res")),
  _sum_s_res(getParam<Real>("sum_s_res"))
{
  if (_sum_s_res < _s_res)
    mooseError("sum_s_res set to " << _sum_s_res << " but it must obey s_res <= sum_s_res < 1");
}

void
RichardsSat::initialize()
{}

void
RichardsSat::execute()
{}

void RichardsSat::finalize()
{}


Real
RichardsSat::sat(Real seff) const
{
  return _s_res + seff*(1.0 - _sum_s_res);
}

Real
RichardsSat::dsat(Real /*seff*/) const
{
  return 1.0 - _sum_s_res;
}

Real
RichardsSat::d2sat(Real /*seff*/) const
{
  return 0.0;
}

