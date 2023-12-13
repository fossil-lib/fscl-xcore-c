code = files('module.c')

lib = static_library('tscl-c',
    code,
    include_directories: dir)

tscl_c_dep = declare_dependency(
    link_with: lib,
    include_directories: dir)
