code = files(
    'json.c', 'csv.c', 'ini.c', 'lazy.c',
    'fossil.c', 'datetime.c', 'reader.c',
    'regex.c', 'stream.c', 'thread.c',
)

lib = static_library('tscl-xcore-c',
    code,
    include_directories: dir)

tscl_xcore_c_dep = declare_dependency(
    link_with: lib,
    include_directories: dir)
