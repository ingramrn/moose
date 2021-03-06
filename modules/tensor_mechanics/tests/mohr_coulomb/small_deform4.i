# apply repeated stretches in z direction, and smaller stretches in the x and y directions
# so that sigma_II = sigma_III,
# which means that lode angle = -30deg.
# The allows yield surface in meridional plane to be mapped out


[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 1
  ny = 1
  nz = 1
  xmin = -0.5
  xmax = 0.5
  ymin = -0.5
  ymax = 0.5
  zmin = -0.5
  zmax = 0.5
[]


[Variables]
  [./disp_x]
  [../]
  [./disp_y]
  [../]
  [./disp_z]
  [../]
[]

[TensorMechanics]
  [./solid]
    disp_x = disp_x
    disp_y = disp_y
    disp_z = disp_z
  [../]
[]


[BCs]
  [./x]
    type = FunctionPresetBC
    variable = disp_x
    boundary = 'front back'
    function = '0.25E-6*x*sin(t)'
  [../]
  [./y]
    type = FunctionPresetBC
    variable = disp_y
    boundary = 'front back'
    function = '0.25E-6*y*sin(t)'
  [../]
  [./z]
    type = FunctionPresetBC
    variable = disp_z
    boundary = 'front back'
    function = '1E-6*z*t'
  [../]
[]

[AuxVariables]
  [./stress_xx]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./stress_xy]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./stress_xz]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./stress_yy]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./stress_yz]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./stress_zz]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./max_ps]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./min_ps]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./mc_int]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./yield_fcn]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./stress_xx]
    type = RankTwoAux
    rank_two_tensor = stress
    variable = stress_xx
    index_i = 0
    index_j = 0
  [../]
  [./stress_xy]
    type = RankTwoAux
    rank_two_tensor = stress
    variable = stress_xy
    index_i = 0
    index_j = 1
  [../]
  [./stress_xz]
    type = RankTwoAux
    rank_two_tensor = stress
    variable = stress_xz
    index_i = 0
    index_j = 2
  [../]
  [./stress_yy]
    type = RankTwoAux
    rank_two_tensor = stress
    variable = stress_yy
    index_i = 1
    index_j = 1
  [../]
  [./stress_yz]
    type = RankTwoAux
    rank_two_tensor = stress
    variable = stress_yz
    index_i = 1
    index_j = 2
  [../]
  [./stress_zz]
    type = RankTwoAux
    rank_two_tensor = stress
    variable = stress_zz
    index_i = 2
    index_j = 2
  [../]
  [./max_ps]
    type = MaterialRealAux
    property = mc_max_principal_stress
    variable = max_ps
  [../]
  [./min_ps]
    type = MaterialRealAux
    property = mc_min_principal_stress
    variable = min_ps
  [../]
  [./mc_int_auxk]
    type = MaterialRealAux
    property = mc_internal
    variable = mc_int
  [../]
  [./yield_fcn_auxk]
    type = MaterialRealAux
    property = mc_yield_function
    variable = yield_fcn
  [../]
[]

[Postprocessors]
  [./s_xx]
    type = PointValue
    point = '0 0 0'
    variable = stress_xx
  [../]
  [./s_xy]
    type = PointValue
    point = '0 0 0'
    variable = stress_xy
  [../]
  [./s_xz]
    type = PointValue
    point = '0 0 0'
    variable = stress_xz
  [../]
  [./s_yy]
    type = PointValue
    point = '0 0 0'
    variable = stress_yy
  [../]
  [./s_yz]
    type = PointValue
    point = '0 0 0'
    variable = stress_yz
  [../]
  [./s_zz]
    type = PointValue
    point = '0 0 0'
    variable = stress_zz
  [../]
  [./max_ps]
    type = PointValue
    point = '0 0 0'
    variable = max_ps
  [../]
  [./min_ps]
    type = PointValue
    point = '0 0 0'
    variable = min_ps
  [../]
  [./internal]
    type = PointValue
    point = '0 0 0'
    variable = mc_int
  [../]
  [./f]
    type = PointValue
    point = '0 0 0'
    variable = yield_fcn
  [../]
[]

[Materials]
  [./mc]
    type = FiniteStrainMohrCoulomb
    block = 0
    disp_x = disp_x
    disp_y = disp_y
    disp_z = disp_z
    fill_method = symmetric_isotropic
    C_ijkl = '0 1E7'
    mc_cohesion = 10
    mc_friction_angle = 50
    mc_dilation_angle = 0
    mc_dilation_angle_residual = 50
    mc_dilation_angle_rate = 3000.0
    mc_tip_smoother = 4
    mc_edge_smoother = 20
    yield_function_tolerance = 1E-8
    ep_plastic_tolerance = 1E-9
    internal_constraint_tolerance = 1E-9
    debug_fspb = 1
  [../]
[]


[Executioner]
  end_time = 30
  dt = 1
  type = Transient
[]


[Outputs]
  file_base = small_deform4
  output_initial = true
  exodus = false
  [./console]
    type = Console
    perf_log = true
    linear_residuals = false
  [../]
  [./csv]
    type = CSV
    interval = 1
  [../]
[]
