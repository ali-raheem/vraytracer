//module raytrace
  
import math
import vec3

fn colour(r vec3.Ray) vec3.Vec {
    uv := r.make_unit()
    ic := 0.5*(uv.y() + 1.0)
    a := vec3.Vec{1.0, 1.0, 1.0}
    b :=  vec3.Vec{0.5, 0.7, 1.0}
    return a.mul_scalar(1.0 - ic) + b.mul_scalar(ic)
}

fn main() {
    mut nx := 200
    mut ny := 100
    println('P3')
    println('$nx $ny')
    println('255')
    llc := vec3.Vec{-2, -1, -1}
    hor := vec3.Vec{4, 0, 0}
    vert := vec3.Vec{0, 2, 0}
    origin := vec3.Vec{0, 0, 0}
    for j := f32(ny - 1); j >= 0; j -- {
        for i := f32(0); i < nx; i++ {
            u := i/nx
            v := j/ny
            r := vec3.Ray{origin, llc + hor.mul_scalar(u) + vert.mul_scalar(v)}
            c := colour(r)
            d := c.mul_scalar(255.99).to_rgb()
           println(d)
        }  
    }
}
