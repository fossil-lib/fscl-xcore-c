if get_option('with_demo').enabled()
    demo_apps = [
        'prog']

    foreach iter : demo_apps
        executable('demo_' + iter, 'demo_' + iter + '.c', dependencies : [trilo_c_dep])
    endforeach
endif