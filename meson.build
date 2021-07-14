project('observable', 'cpp',
  version: 'bddbeed',
  license: 'MIT',
  default_options: ['cpp_std=c++11']
  )

thread_dep=dependency('threads')

includes = include_directories('.')

obervable_src = files(
  'obs/connection.cpp'
  )

observable_lib = library('observable', include_directories: includes, sources: obervable_src, dependencies: [thread_dep])

observable_dep = declare_dependency(include_directories: includes, link_with: observable_lib)
