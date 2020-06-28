// module raytrace
import math
import vec3
import rand
import flag
import os

const (
	bounce_depth = 50
	image_width  = 1920
	image_height = 1080
	rays         = 1000
)

fn lambertian_scatter(ray vec3.Ray, rec HitRecord) Reflection {
	target := rec.p + rec.normal + random_point_in_sphere()
	scattered := vec3.Ray{rec.p, target}
	attenuation := rec.mat.albedo
	return Reflection{attenuation, scattered}
}

fn metal_scatter(ray vec3.Ray, rec HitRecord) Reflection {
	reflected := reflect((ray.b).make_unit(), rec.normal)
	scattered := vec3.Ray{rec.p, reflected + random_point_in_sphere().mul_scalar(rec.mat.fuzz)}
	attenuation := rec.mat.albedo
	return Reflection{attenuation, scattered}
}

fn glass_scatter(ray vec3.Ray, rec HitRecord) Reflection {
	reflected := reflect(ray.b, rec.normal)
	mut cosine := f32(0.0)
	mut ni_over_nt := rec.mat.ref_idx
	mut out_normal := rec.normal.mul_scalar(-1.0)
	attenuation := rec.mat.albedo
	rdotn := (ray.b).dot(rec.normal)
	if rdotn <= 0 {
		out_normal = rec.normal
		ni_over_nt = 1.0 / rec.mat.ref_idx
		cosine = -((ray.b).dot(rec.normal)) / ray.b.length()
	} else {
		// Note ni_over_nt, out_normal set default
		cosine = rec.mat.ref_idx * ((ray.b).dot(rec.normal)) / ray.b.length()
	}
	refracted := refract(ray.b, out_normal, ni_over_nt) or {
		return Reflection{attenuation, vec3.Ray{rec.p, reflected}}
	}
	reflect_p := schlick(cosine, rec.mat.ref_idx)
	if reflect_p > rand.f32() {
		return Reflection{attenuation, vec3.Ray{rec.p, reflected}}
	}
	return Reflection{attenuation, vec3.Ray{rec.p, refracted}}
}

fn reflect(v, n vec3.Vec) vec3.Vec {
	return v - n.mul_scalar(2.0 * v.dot(n))
}

fn refract(v, n vec3.Vec, ni_over_nt f32) ?vec3.Vec {
	uv := v.make_unit()
	dt := uv.dot(n)
	discriminant := f32(1.0 - ni_over_nt * ni_over_nt * (1.0 - dt * dt))
	if discriminant > 0 {
		return (uv - n.mul_scalar(dt)).mul_scalar(ni_over_nt) - n.mul_scalar(math.sqrtf(discriminant))
	} else {
		return error('No refractiion')
	}
}

fn schlick(cosine f32, ref_idx f32) f32 {
	r0 := (1.0 - ref_idx) / (1.0 + ref_idx)
	r1 := r0 * r0
	return r1 + (1.0 - r1) * math.powf((1.0 - cosine), 5)
}

struct Material {
	scatter fn(ray vec3.Ray, rec HitRecord) Reflection
	albedo  vec3.Vec
	fuzz    f32
	ref_idx f32
}

struct HitRecord {
mut:
	t      f32
	p      vec3.Vec
	normal vec3.Vec
	mat    Material
}

struct Sphere {
	centre vec3.Vec
	radius f32
	mat    Material
}

// hit Method on Sphere to detect a hit using pythagoras
fn (s Sphere) hit(r vec3.Ray, t_min, t_max f32) ?HitRecord {
	oc := r.a - s.centre
	a := r.b.dot(r.b)
	b := 2.0 * oc.dot(r.b)
	c := oc.dot(oc) - s.radius * s.radius
	discriminant := b * b - 4.0 * a * c
	temp := if discriminant > 0 { (-b - math.sqrtf(discriminant)) / (2.0 * a) } else { (-b + math.sqrtf(discriminant)) /
			(2.0 * a) }
	if temp > t_min && temp < t_max {
		mat := Material{s.mat.scatter, s.mat.albedo, s.mat.fuzz, s.mat.ref_idx}
		return HitRecord{temp, r.at(temp), (r.at(temp) - s.centre).div_scalar(s.radius), mat}
	}
	return error('No hit')
}

// HitList Takes list of Spheres and length of the list
struct HitList {
mut:
	list      []Sphere
	list_size int // FIXME is this needed? HitList.len?
}

// hit Takes light ray and returns option of hit_rec
fn (l HitList) hit(r vec3.Ray, t_min, t_max f32) ?HitRecord {
	mut closest := t_max
	mut hit_some := false
	mut hit_rec := HitRecord{}
	for i := 0; i < l.list_size; i++
	 {
		temp_rec := l.list[i].hit(r, t_min, closest) or {
			continue
		}
		closest = temp_rec.t
		hit_some = true
		hit_rec = temp_rec
	}
	if hit_some {
		return hit_rec
	} else {
		return error('No hit')
	}
}

// colour takes a light ray and hitlist returns colour of light ray
fn colour(r vec3.Ray, h HitList, depth, maxdepth int) vec3.Vec {
	rec := h.hit(r, 0.001, (1 << 31) - 1) or {
		uv := r.make_unit()
		ic := 0.5 * (uv.y() + 1.0)
		a := vec3.Vec{1.0, 1.0, 1.0}
		b := vec3.Vec{0.5, 0.7, 1.0}
		return a.mul_scalar(1.0 - ic) + b.mul_scalar(ic)
	}
	if depth < maxdepth {
		scatterfn := rec.mat.scatter
		ref := scatterfn(r, rec)
		atten := ref.attenuation
		scat := colour(ref.scatter, h, depth + 1, maxdepth)
		return mul(atten, scat)
	} else {
		return vec3.Vec{0, 0, 0}
	}
}

fn mul(a, b vec3.Vec) vec3.Vec {
	return vec3.Vec{a.x() * b.x(), a.y() * b.y(), a.z() * b.z()}
}

struct Reflection {
	attenuation vec3.Vec
	scatter     vec3.Ray
}

struct Camera {
	origin            vec3.Vec
	lower_left_corner vec3.Vec
	horizontal        vec3.Vec
	vertical          vec3.Vec
}

fn (c Camera) get_ray(u, v f32) vec3.Ray {
	return vec3.Ray{c.origin, c.lower_left_corner + c.horizontal.mul_scalar(u) + c.vertical.mul_scalar(v) -
		c.origin}
}

fn random_point_in_sphere() vec3.Vec {
	for {
		p := (vec3.Vec{rand.f32(), rand.f32(), rand.f32()} - vec3.Vec{1, 1, 1}).mul_scalar(2)
		if p.hypotenuse() < 1 {
			return vec3.Vec{p.x(), p.y(), p.z()}
		}
	}
}

fn main() {
	mut fp := flag.new_flag_parser(os.args)
	fp.application('raytrace')
	fp.version('f32:v0.0.47')
	fp.description('Simple raytracer written in V')
	fp.skip_executable()
	help := fp.bool('help', 0, false, 'Show this usage information')
	ns := fp.int('rays', 0, rays, 'The number of rays raytraced for each pixel of the image')
	nx := fp.int('width', 0, image_width, 'The width of the generated image')
	ny := fp.int('height', 0, image_height, 'The height of the generated image')
	bouncedepth := fp.int('bouncedepth', 0, bounce_depth, 'The maximum amount of bounces the rays are allowed to do')
	if help {
		println(fp.usage())
		return
	}
	println('P3')
	println('$nx $ny')
	println('255')
	llc := vec3.Vec{-2, -1, -1}
	hor := vec3.Vec{4, 0, 0}
	vert := vec3.Vec{0, 2, 0}
	origin := vec3.Vec{0, 0, 0}
	cam := Camera{origin, llc, hor, vert}
	lam1 := Material{lambertian_scatter, vec3.Vec{0.8, 0.8, 0}, 1, 0}
	lam2 := Material{lambertian_scatter, vec3.Vec{0.8, 0.3, 0.3}, 1, 0}
	met1 := Material{metal_scatter, vec3.Vec{1.0, 0.83, 0}, 0.1, 0}
	glass1 := Material{glass_scatter, vec3.Vec{1.0, 1.0, 1.0}, 0.0, 1.5}
	mut h := HitList{[]Sphere{len: 4}, 4} // FIXME might need init
	h.list[0] = Sphere{vec3.Vec{0, -100.5, -1}, 100, lam1}
	h.list[1] = Sphere{vec3.Vec{0, 0, -1}, 0.5, lam2}
	h.list[2] = Sphere{vec3.Vec{1, 0, -1}, 0.5, met1}
	h.list[3] = Sphere{vec3.Vec{-1, 0, -1}, 0.5, glass1}
	for j := ny - 1; j >= 0; j--
	 {
		for i := 0; i < nx; i++
		 {
			mut c := vec3.Vec{0, 0, 0}
			for s := 0; s < ns; s++
			 {
				u := (f32(i) + rand.f32()) / f32(nx)
				v := (f32(j) + rand.f32()) / f32(ny)
				r := cam.get_ray(u, v)
				c = c + colour(r, h, 0, bouncedepth)
			}
			c = c.div_scalar(ns)
			c = vec3.Vec{math.sqrtf(c.x()), math.sqrtf(c.y()), math.sqrtf(c.z())}
			d := c.mul_scalar(255.99).to_rgb()
			println(d)
		}
	}
}
