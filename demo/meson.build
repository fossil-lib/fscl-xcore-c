if get_option('with_demo').enabled()
    demo_apps = [
        'json', 'csv', 'ini', 'lazy', 'fossil', 'datetime',
        'console', 'regex', 'stream', 'thread']

    foreach iter : demo_apps
        executable('demo_' + iter, 'demo_' + iter + '.c', dependencies : [tscl_xcore_c_dep])
    endforeach
endif