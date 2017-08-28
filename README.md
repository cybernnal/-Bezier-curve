# Bezier-curve

Build with `cmake . ; make -j`

Lauch with `./bezier`

Use `-i` or `--iterations` to set precision of the curve, 1 give a segment, 15000 look like a real curve, higher is `i` slower is the execution. (default: 100)

Use `-r n` or `--random n` to put n point randomly on the screen. Careful lot of point may cause trouble (more than 1000).

Use `-s u` or `--sleep u` to set the sleep delay in microseconds after a mouse input (`-r` is impacted, use `-s 1` for no delay)

Left click on the windows for put points

Start animation with `s`
