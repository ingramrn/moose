/*****************************************/
/* Written by andrew.wilkins@csiro.au    */
/* Please contact me if you make changes */
/*****************************************/

//  This post processor returns d(relperm)/d(Seff)
//
#include "RichardsRelPermPrimeAux.h"

template<>
InputParameters validParams<RichardsRelPermPrimeAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("seff_var", "The variable that represents the effective saturation");
  params.addRequiredParam<UserObjectName>("relperm_UO", "Name of user object that defines the relative permeability.");
  params.addClassDescription("auxillary variable which is d(relative permeability)/dSeff");
  return params;
}

RichardsRelPermPrimeAux::RichardsRelPermPrimeAux(const std::string & name, InputParameters parameters) :
  AuxKernel(name, parameters),
  _seff_var(coupledValue("seff_var")),
  _relperm_UO(getUserObject<RichardsRelPerm>("relperm_UO"))
{}

Real
RichardsRelPermPrimeAux::computeValue()
{
  return _relperm_UO.drelperm(_seff_var[_qp]);
}
