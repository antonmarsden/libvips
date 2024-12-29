examples = [
    'annotate-animated',
    'new-from-buffer',
    'progress-cancel',
    'use-vips-func',
    'copy-tiff-tags',
    'my-add',
]

foreach example : examples
    executable(example,
        example + '.c',
        dependencies: libvips_dep,
    )
endforeach

