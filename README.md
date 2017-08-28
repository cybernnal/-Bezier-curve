# Bezier-curve

Build with `cmake . ; make -j`

Lauch with `./bezier`

Use `-i` or `--iterations` to set precision of the curve, 1 give a segment, 15000 look like a real curve, higher is `i` slower is the execution. (default: 100)

Use `-r n` or `--random n` to put n point randomly on the screen. Careful lot of point may cause trouble (more than 1000).

Use `-s u` or `--sleep u` to set the sleep delay in microseconds after a mouse input (`-r` is impacted, use `-s 1` for no delay). (default: 100000)

Left click on the windows for put points

Start animation with `s`

<img width="1821" alt="capture d ecran 2017-08-28 a 19 36 27" src="https://user-images.githubusercontent.com/12376123/29785764-14df62ba-8c29-11e7-9161-dcde5ab1872b.png">
<img width="1844" alt="capture d ecran 2017-08-28 a 19 29 15" src="https://user-images.githubusercontent.com/12376123/29785765-14e4c8ae-8c29-11e7-86f0-73e098683c0a.png">

