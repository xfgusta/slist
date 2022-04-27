project(
	'slist',
	'c',
	version: '1.0.0',
	license: 'MIT'
)

project_name = meson.project_name()
project_description = 'A simple singly-linked list library'
project_version = meson.project_version()
project_url = 'https://github.com/xfgusta/slist'

soversion_full = '1.0.0'
soversion_short = '1'

inc = include_directories('include')

install_headers('include/slist.h')

slist_sources = ['src/slist.c']

slist_lib = library(
    'slist',
    slist_sources,
    include_directories: inc,
    install: true,
    version: soversion_full,
    soversion: soversion_short
)

slist_dep = declare_dependency(
    include_directories: inc,
    link_with: slist_lib
)

pkg = import('pkgconfig')
pkg.generate(
	libraries: slist_lib,
	version: project_version,
	name: project_name,
	filebase: 'slist',
	description: project_description,
	url: project_url
)