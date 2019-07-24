# vRayTracer

Simple raytracer in [vlang](https://vlang.io), learning the language as I go along so plenty of poor design choices, some for educational purposes.. Based on [Ray Tracing in One Weekend](https://github.com/RayTracing/raytracinginoneweekend).

### Current output

![raytrace output](output.png)

Output is ppm but this is converted with imagemagick `convert output.ppm output.png`

### Building & Running

I haven't got vlang modules working yet, move `vec3.v` into your `vlang-path/vlib/vec3` directory and compile with `v raytrace.v`.

Run with `./raytrace > output.ppm`

### Todo

* Code is a complete and utter mess.
* For some reason can't get v to use lib objects, copy vec3.v to v_path/v/vlib/vec3
* Can't get interfaces to work due to Clang error
* Non-deterministic runs!!! - WTF