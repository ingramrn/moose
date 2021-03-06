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

#ifndef SETUPINTERFACE_H
#define SETUPINTERFACE_H

#include "InputParameters.h"
#include "ExecStore.h"
#include "MooseEnum.h"

// Forward declarations
class SetupInterface;

template<>
InputParameters validParams<SetupInterface>();

class SetupInterface
{
public:
  SetupInterface(InputParameters & params);
  virtual ~SetupInterface();

  /**
   * Gets called at the beginning of the simulation before this object is asked to do its job
   */
  virtual void initialSetup();

  /**
   * Gets called at the beginning of the timestep before this object is asked to do its job
   */
  virtual void timestepSetup();

  /**
   * Gets called just before the Jacobian is computed and before this object is asked to do its job
   */
  virtual void jacobianSetup();

  /**
   * Gets called just before the residual is computed and before this object is asked to do its job
   */
  virtual void residualSetup();

  /**
   * Gets called when the subdomain changes (i.e. in a Jacobian or residual loop) and before this object is asked to do its job
   */
  virtual void subdomainSetup();

  /**
   * Get the execution flag for the object
   */
  virtual const std::vector<ExecFlagType> & execFlags() const;

  /**
   * Returns the available options for the 'execute_on' input parameters
   * @return A MooseEnum with the available 'execute_on' options, the default is 'residual'
   */
  static std::vector<MooseEnum> getExecuteOptions();

protected:
  /// execution flag (when is the object executed/evaluated)
  std::vector<ExecFlagType> _exec_flags;
};

#endif /* SETUPINTERFACE_H */
