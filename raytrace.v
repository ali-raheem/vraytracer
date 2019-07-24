//module raytrace
  
import math
import vec3
import rand

interface Materialer {
  scatter(ray vec3.Ray, rec HitRecord) Reflection
}

struct Lambertian {
   albedo vec3.Vec
}
       
fn (l Lambertian) scatter(ray vec3.Ray, rec HitRecord) Reflection {
    target := rec.p + rec.normal + random_point_in_sphere()
    scattered := vec3.Ray{rec.p, target}
    attenuation := l.albedo
    return Reflection{attenuation, scattered}
}

  
struct HitRecord {
  mut:
      t f32
      p vec3.Vec
      normal vec3.Vec
      mat Materialer
}

struct Sphere {
  centre vec3.Vec
  radius f32
  mat Materialer
}


fn (s Sphere) hit(r vec3.Ray, t_min f32, t_max f32) ?HitRecord {
    oc := r.a - s.centre
    a := r.b.dot(r.b)
    b := 2.0 * oc.dot(r.b)
    c := oc.dot(oc) - s.radius * s.radius
    discriminant := b * b - 4.0 * a * c
    temp := if (discriminant > 0) {
       (-b - math.sqrt(discriminant))/(2.0 * a)
    } else {
       (-b + math.sqrt(discriminant))/(2.0 * a)
    }
    if (temp > t_min && temp < t_max) {
      return HitRecord{temp, r.at(temp), (r.at(temp) - s.centre).div_scalar(s.radius), s.mat}
    }

    return error('No hit')
}

/*
interface Hitter {
  hit(r vec3.Ray, t_min f32, t_max f32) ?HitRecord
}
*/


struct HitList {
  mut:
    list []Sphere
    list_size int
}

fn (l HitList) hit(r vec3.Ray, t_min f32, t_max f32) ?HitRecord {
  mut closest := t_max
  mut hit_some := false
  mut hit_rec := HitRecord{}
  for i := 0; i < l.list_size; i++ {
    temp_rec := l.list[i].hit(r, t_min, closest) or { continue }
    closest = temp_rec.t
    hit_some = true
    hit_rec = temp_rec
  }
  if(hit_some) {
    return hit_rec
  } else {
   return error ('No hit')
  }
}

fn colour(r vec3.Ray, h HitList, depth int) vec3.Vec {
    rec := h.hit(r, 0.001, (1<<31) - 1) or {
      uv := r.make_unit()
      ic := 0.5*(uv.y() + 1.0)
      a := vec3.Vec{1.0, 1.0, 1.0}
      b :=  vec3.Vec{0.5, 0.7, 1.0}
      return a.mul_scalar(1.0 - ic) + b.mul_scalar(ic)
   }

   if (depth < 50) {
       ref := (rec.mat).scatter(r, rec)
       atten := ref.attenuation
       scat := colour(ref.scatter, h, depth + 1)
                    // TODO why can't I overload here?
       return mul(atten, scat)
   } else {
       return vec3.Vec{0, 0, 0}
   }
}
// TODO remove once overloading working
fn mul( a vec3.Vec, b vec3.Vec) vec3.Vec {
      return vec3.Vec{a.x() * b.x(),  a.y() * b.y(), a.z() * b.z()}
} 


struct Reflection {
    attenuation vec3.Vec
    scatter vec3.Ray
}
  
fn reflect(v vec3.Vec, n vec3.Vec) vec3.Vec {
        return v - n.mul_scalar(2.0 * v.dot(n))
}



struct Camera {
    origin vec3.Vec
    lower_left_corner vec3.Vec
    horizontal vec3.Vec
    vertical vec3.Vec
}

fn (c Camera) get_ray(u f32, v f32) vec3.Ray {
   return vec3.Ray{c.origin, c.lower_left_corner + c.horizontal.mul_scalar(u) + c.vertical.mul_scalar(v) - c.origin}
}

fn randf32() f32 {
   return f32(rand.next(255))/256.0
}

fn random_point_in_sphere() vec3.Vec {
   for {
     p := (vec3.Vec{randf32(), randf32(), randf32()} - vec3.Vec{1, 1, 1}).mul_scalar(2)
     if p.hypotenuse() < 1 {
        return vec3.Vec{p.x(), p.y(), p.z()}
     }
   }
}


       
fn main() {
    nx := 200
    ny := 100
    ns := 100
    println('P3')
    println('$nx $ny')
    println('255')
    llc := vec3.Vec{-2, -1, -1}
    hor := vec3.Vec{4, 0, 0}
    vert := vec3.Vec{0, 2, 0}
    origin := vec3.Vec{0, 0, 0}
    cam := Camera{origin, llc, hor, vert}
    lam := Lambertian{vec3.Vec{0.1, 0.1, 0.1}}
    mut h := HitList{[Sphere{vec3.Vec{0,0,0}, 0, lam}; 4], 4}
    h.list[0] = Sphere{vec3.Vec{0, -100.5, -1}, 100, lam}
    h.list[1] = Sphere{vec3.Vec{0, 0, -1}, 0.5, lam}
    h.list[2] = Sphere{vec3.Vec{0.1, 0, -0.5}, 0.1, lam}
    h.list[3] = Sphere{vec3.Vec{-0.1, 0, -0.5}, 0.1, lam}
    for j := ny - 1; j >= 0; j -- {
        for i := 0; i < nx; i++ {
            mut c := vec3.Vec{0, 0, 0}
            for s := 0; s < ns; s++ {
                u := (f32(i) + randf32())/f32(nx)
                v := (f32(j) + randf32())/f32(ny)
                r := cam.get_ray(u, v)
                c = c + colour(r, h, 0)
            }
            c = c.div_scalar(ns)
            c = vec3.Vec{math.sqrt(c.x()), math.sqrt(c.y()), math.sqrt(c.z())}
            d := c.mul_scalar(255.99).to_rgb()
           println(d)
        }  
    }
}
