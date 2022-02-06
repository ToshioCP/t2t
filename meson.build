project('t2t', 'c')

compiler = meson.get_compiler('c')
glibdep = dependency('glib-2.0', version: '>=2.68.0')
mathdep = compiler.find_library('m', required: true)
gtkdep = dependency('gtk4')

gnome=import('gnome')
resources = gnome.compile_resources('resources','t2t.gresource.xml')

flex = find_program('flex')
bison = find_program('bison')
t2tparser = custom_target('t2tparser', input: 't2t.y', output: ['t2t_parser.c', 't2t_parser.h'], command: [bison, '-d', '-o', 't2t_parser.c', '@INPUT@'])
t2tlexer = custom_target('t2tlexer', input: 't2t.lex', output: 't2t_lex.c', command: [flex, '-o', '@OUTPUT@', '@INPUT@'])

sourcefiles=files('main.c', 'vector.c', 'trans.c', 'tfetextview.c')

executable('t2t', sourcefiles, resources, t2tparser, t2tlexer, t2tparser[1], dependencies: [mathdep, gtkdep], export_dynamic: true, install: true)

