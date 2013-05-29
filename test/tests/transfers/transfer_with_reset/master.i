[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
[]

[Variables]
  [./u]
  [../]
[]

[AuxVariables]
  [./t]
  [../]
  [./u_from_sub]
  [../]
[]

[Kernels]
  [./diff]
    type = Diffusion
    variable = u
  [../]
  [./td]
    type = TimeDerivative
    variable = u
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = u
    boundary = left
    value = 0
  [../]
  [./right]
    type = DirichletBC
    variable = u
    boundary = right
    value = 1
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 10
  dt = 0.01
  petsc_options = '-snes_mf_operator -ksp_monitor'
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Output]
  output_initial = true
  exodus = true
  perf_log = true
[]

[MultiApps]
  [./sub]
    type = TransientMultiApp
    app_type = MooseTestApp
    execute_on = timestep
    positions = '0 0 0'
    input_files = sub.i
    reset_apps = 0
    reset_time = 0.05
  [../]
[]

[Transfers]
  [./t_from_sub]
    type = MultiAppNearestNodeTransfer
    direction = from_multiapp
    execute_on = timestep
    multi_app = sub
    source_variable = t
    variable = t
  [../]
  [./u_from_sub]
    type = MultiAppNearestNodeTransfer
    direction = from_multiapp
    execute_on = timestep
    multi_app = sub
    source_variable = u
    variable = u_from_sub
  [../]
  [./u_to_sub]
    type = MultiAppNearestNodeTransfer
    direction = to_multiapp
    execute_on = timestep
    multi_app = sub
    source_variable = u
    variable = u_from_master
  [../]
[]
