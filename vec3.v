module vec3
  
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

pub fn (v Vec) x() f32 {
    return v.i
}
pub fn (v Vec) y() f32 {
    return v.j
}
pub fn (v Vec) z() f32 {
    return v.k
}       
// length Calculate the abs/mangatude of Vec3 as a Vec
pub fn (v Vec) length() f32 {
  return math.sqrt(v.hypotenuse())
}

pub fn (v Vec) str() string {
  return '($v.i, $v.j, $v.k)'
}

pub fn (a Vec) + (b Vec) Vec {
  return Vec {
    a.i + b.i,
    a.j + b.j,
    a.k + b.k
  }
}

pub fn (a Vec) - (b Vec) Vec {
  return Vec {
    a.i - b.i,
    a.j - b.j,
    a.k - b.k
  }
}

pub fn (a Vec) * (b Vec) Vec {
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

// div_scalar Divide Vec by a scalar
pub fn (a Vec) div_scalar(t f32) Vec {
  return Vec {
    a.i / t,
    a.j / t,
    a.k / t
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

// make_unit Return a unit vector in the direction of Vec.
pub fn (v Vec) make_unit() Vec {
  l := v.length()
  return v.div_scalar(l)
}

pub fn (v Vec) to_rgb() RGB {
  return RGB {
    int(v.x()),
      int(v.y()),
      int(v.z())
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

pub fn (c RGB) mul_scalar(k f32) RGB {
    return RGB{
               int(f32(c.r) * k),
               int(f32(c.g) * k),
               int(f32(c.b) * k)
               }
}
       
struct Ray {
  pub:
      a Vec
      b Vec
}

// at Calculate position along Ray at t.
pub fn (r Ray) at(t f32) Vec {
  return r.a + r.b.mul_scalar(t)
}

pub fn (r Ray) str() string {
 return '$(r.a) + $(r.b) * t' 
}

// make_unit Return a unit vector in the direction of Vec.
pub fn (r Ray) make_unit() Vec {
  return r.b.make_unit()
}

