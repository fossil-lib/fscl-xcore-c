if get_option('with_test').enabled()
    test_deps = [
        dependency('fscl-xtest-c'),
        dependency('fscl-xmock-c')
    ]

    test_files = [
        'basic.json', 'invalid.json', 'program.fossil',
        'test_config.ini', 'eco_products.csv']
    foreach file : test_files
        configure_file(input: 'data' / file, output: file, copy: true)
    endforeach

    test_src = ['xunit_runner.c']
    test_cubes = [
        'parser', 'fossil', 'error',
        'datetime', 'console', 'soap',
        'regex', 'stream', 'thread']

    foreach cube : test_cubes
        test_src += ['xtest_' + cube + '.c']
    endforeach

    pizza = executable('xcli', test_src, include_directories: dir, dependencies: [test_deps, fscl_xcore_c_dep])
    test('xunit_tests', pizza)  # Renamed the test target for clarity
endif
