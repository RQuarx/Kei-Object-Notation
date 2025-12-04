project(
    'Kei Object Notation C++ Parser',
    'cpp',
    default_options: ['cpp_std=c++23', 'warning_level=3'],
    version: '0.0.1',
    license: 'GPL-3.0-or-later',
    license_files: ['COPYING'],
)

versions = meson.project_version().split('.')

args = [
    '-DKONCPP_VERSION_MAJ=' + versions[0],
    '-DKONCPP_VERSION_MIN=' + versions[1],
    '-DKONCPP_VERSION_MIC=' + versions[2],
    '-DKONCPP_NAME="KONCPP"',
]

if host_machine.system() == 'windows'
    args += '-DNOMINMAX'
endif

include_dir = include_directories('include')

subdir('src')
koncpp = shared_library(
    'koncpp',
    source_files,
    include_directories: include_dir,
    cpp_args: args,
    gnu_symbol_visibility: 'hidden',
    install: true,
    install_dir: get_option('libdir'),
)

install_subdir(
    'include/koncpp',
    install_dir: get_option('includedir'),
    strip_directory: true,
)

project_dep = declare_dependency(
    include_directories: include_directories('include'),
    link_with: koncpp,
    compile_args: args,
)

subdir('test')

pkg = import('pkgconfig')

pkg.generate(
    name: 'koncpp',
    filebase: 'koncpp',
    description: 'A Kei Object Notation C++ Parser',
    subdirs: 'koncpp',
    libraries: koncpp,
)