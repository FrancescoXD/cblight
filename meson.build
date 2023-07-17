project('cblight', 'c', version: '0.1', default_options: ['warning_level=everything', 'buildtype=release', 'strip=true'])

sources = files('src/main.c', 'src/cblight.c', 'src/utils.c')
incdir = include_directories('include')

executable('cblight', sources, include_directories: incdir)

