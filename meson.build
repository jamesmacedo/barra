project('barra', 'cpp',
  version: '0.1',
  default_options: ['cpp_std=c++17', 'warning_level=3']
)

fs = import('python')

src = include_directories('core')

cpp_files = run_command('find', '.', '-not', '-path', './build/*', '-name', '*.cpp', '!', '-name', 'barra.cpp').stdout().strip().split('\n')

srcs = files('barra.cpp')
foreach f : cpp_files
  srcs += files(f)
endforeach

xcb = dependency('xcb', required: true)
# xcb_ewmh = dependency('xcb-ewmh', required: true)
# xcb_keysyms = dependency('xcb-keysyms', required: true)
cairo = dependency('cairo', required: true)
svg = dependency('librsvg-2.0', required: true)
dbus = dependency('sdbus-c++', required: true)
opencv = dependency('opencv4', required: true)
# cairo_xcb = dependency('cairo', required: true)

executable('barra', srcs,
  include_directories: [src],
  dependencies: [
    xcb, 
    cairo,
    svg,
    dbus,
    opencv
  ],
  install: false
)
