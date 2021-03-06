[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 2
  ny = 2
  distribution = PARALLEL
[]

[Variables]
  [./u]
  [../]
[]

[Functions]
  [./tif]
    type = ImageFunction
    file_base = stack/test
    file_type = png
    file_range = 00
    threshold = 2.7e4
    upper_value = 1
    lower_value = -1
  [../]
[]

[ICs]
  [./u_ic]
    type = FunctionIC
    function = tif
    variable = u
  [../]
[]

[Problem]
  type = FEProblem
  solve = false
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 1
  dt = 0.1
[]

[Adaptivity]
  max_h_level = 5
  initial_steps = 5
  initial_marker = marker
  [./Indicators]
    [./indicator]
      type = GradientJumpIndicator
      variable = u
    [../]
  [../]
  [./Markers]
    [./marker]
      type = ErrorFractionMarker
      indicator = indicator
      refine = 0.9
    [../]
  [../]
[]

[Outputs]
  output_initial = true
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = false
    linear_residuals = false
  [../]
[]
