# vRayTracer

Simple raytracer in [vlang](https://vlang.io), learning the language as I go along so plenty of poor design choices, some for educational purposes. Based on [Ray Tracing in One Weekend](https://github.com/RayTracing/raytracinginoneweekend).

### Current output

![raytrace output](output.png)

Output is ppm but this is converted with imagemagick `convert output.ppm output.png`

### Building & Running

Compile with `v -o bin/raytrace -prod raytrace.v`
Run with `./raytrace > output.ppm`

### Todo

* Code is a complete and utter mess.
* Use Interfaces once working
* Use None instead of error once working
* Ensure overloading is used everywhere once working //TODO
* Read an JSON input file
* Camera pos/fov
* Focal distance

### Complete

* PPM output
* Fuzz
* Albedo
* Reflection
* Scattering
* Lambertian material
* Metal material
* Dialectric material

