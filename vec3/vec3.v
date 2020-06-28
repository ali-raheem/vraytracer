module vec3

// vec3 module 3 dimentional f64 vector with associated methods
import math

// Vec 3-Vector structure
pub struct Vec {
mut:
	i f64
	j f64
	k f64
}

// hypotenuse Calculate the displacement due to Vec
pub fn (v Vec) hypotenuse() f64 {
	return v.i * v.i + v.j * v.j + v.k * v.k
}

pub fn (v Vec) x() f64 {
	return v.i
}

pub fn (v Vec) y() f64 {
	return v.j
}

pub fn (v Vec) z() f64 {
	return v.k
}

// length Calculate the abs/mangatude of Vec3 as a Vec
pub fn (v Vec) length() f64 {
	return math.sqrt(v.hypotenuse())
}

pub fn (v Vec) str() string {
	return '($v.i, $v.j, $v.k)'
}

pub fn (a Vec) +(b Vec) Vec {
	return Vec{a.i + b.i, a.j + b.j, a.k + b.k}
}

pub fn (a Vec) -(b Vec) Vec {
	return Vec{a.i - b.i, a.j - b.j, a.k - b.k}
}

pub fn (a Vec) *(b Vec) Vec {
	return Vec{a.i * b.i, a.j * b.j, a.k * b.k}
}

// mul_scalar Multiple a vec3 Vec by a scalar
pub fn (a Vec) mul_scalar(t f64) Vec {
	return Vec{a.i * t, a.j * t, a.k * t}
}

// div_scalar Divide Vec by a scalar
pub fn (a Vec) div_scalar(t f64) Vec {
	return Vec{a.i / t, a.j / t, a.k / t}
}

// dot Calculate dot product between two vec3 Vecs
pub fn (v Vec) dot(u Vec) f64 {
	return v.i * u.i + v.j * u.j + v.k * u.k
}

// cross Calculate cross product between two vec3 Vecs
pub fn (v Vec) cross(u Vec) Vec {
	return Vec{
		i: v.j * u.k
		j: v.k * u.i
		k: v.i * u.j
	}
}

// make_unit Return a unit vector in the direction of Vec.
pub fn (v Vec) make_unit() Vec {
	l := v.length()
	return v.div_scalar(l)
}

pub fn (v Vec) to_rgb() RGB {
	return RGB{byte(v.x()), byte(v.y()), byte(v.z())}
}

// RGB structure to hold RED GREEN BLUE
struct RGB {
	r byte
	g byte
	b byte
}

pub fn (c RGB) str() string {
	return '$c.r $c.g $c.b'
}

pub fn (c RGB) mul_scalar(k f64) RGB {
	return RGB{byte(f64(c.r) * k), byte(f64(c.g) * k), byte(f64(c.b) * k)}
}

// Ray strcture holding source and destination Vecs
pub struct Ray {
pub:
	a Vec
	b Vec
}

// at Calculate position along Ray at time t.
pub fn (r Ray) at(t f64) Vec {
	return r.a + r.b.mul_scalar(t)
}

pub fn (r Ray) str() string {
	return '$(r.a) + $(r.b) * t'
}

// make_unit Return a unit vector in the direction of Vec.
pub fn (r Ray) make_unit() Vec {
	return r.b.make_unit()
}
