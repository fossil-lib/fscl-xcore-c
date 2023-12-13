if get_option('with_test').enabled()
    test_deps = [
        dependency('tscl-xtest-c')
    ]

    test_src = ['xunit_runner.c']
    test_cubes = ['cases']

    foreach cube : test_cubes
        test_src += ['xtest_' + cube + '.c']
    endforeach

    pizza = executable('xcli', test_src, include_directories: dir, dependencies: [test_deps, tscl_c_dep])
    test('xunit_tests', pizza)  # Renamed the test target for clarity
endif
