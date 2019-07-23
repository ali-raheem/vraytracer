module vec3
// vec3 module for 'Raytracer in a weekend'
  
import math

struct Vec {
   mut:
       i f32
       j f32
       k f32
}

// hypotenuse Calculate the displacement due to Vec
pub fn (v Vec) hypotenuse() f32 {
    return v.i * v.i + v.j * v.j + v.k * v.k
}

// length Calculate the abs/mangatude of Vec3 as a Vec
pub fn (v Vec) length() f32 {
  return math.sqrt(v.hypotenuse())
}

pub fn (v Vec) str() string {
  return '($v.i, $v.j, $v.k)'
}

fn (a Vec) + (b Vec) Vec {
  return Vec {
    a.i + b.i,
    a.j + b.j,
    a.k + b.k
  }
}

fn (a Vec) * (b Vec) Vec {
  return Vec {
    a.i * b.i,
    a.j * b.j,
    a.k * b.k
  }
}

// mul_scalar Multiple a vec3 Vec by a scalar
pub fn (a Vec) mul_scalar(t f32) Vec {
  return Vec {
    a.i * t,
    a.j * t,
    a.k * t
  }
}

// dot Calculate dot product between two vec3 Vecs
pub fn (v Vec) dot(u Vec) f32 {
  return v.i * u.i + v.j * u.j + v.k * u.k
}

// cross Calculate cross product between two vec3 Vecs
pub fn (v Vec) cross(u Vec) Vec {
  return Vec {
    i: v.j * u.k,
    j: v.k * u.i,
    k: v.i * u.j
  }
}


struct RGB {
    r int
    g int
    b int
}

pub fn (c RGB) str() string {
    return '$c.r $c.g $c.b'
}

struct Ray {
  a Vec
  b Vec
}

// at Calculate position along Ray at t.
fn (r Ray) at(t f32) Vec {
  return r.a + r.b.mul_scalar(t)
}

fn (r Ray) str() string {
 return '$(r.a) + $(r.b) * t' 
}
