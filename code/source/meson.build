code = files(
    'parser.c', 'fossil.c', 'error.c',
    'datetime.c', 'console.c', 'soap.c',
    'regex.c', 'stream.c', 'thread.c',
)

lib = static_library('fscl-xcore-c',
    code,
    include_directories: dir)

fscl_xcore_c_dep = declare_dependency(
    link_with: lib,
    include_directories: dir)
