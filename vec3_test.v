import vec3

fn test_hypotenuse() {
   a := vec3.Vec{3, 4, 5}
   assert a.hypotenuse() == 50
}

fn test_length() {
  a := vec3.Vec{1, 2, 2}
  assert a.length() == 3
}

fn test_rgb() {
  a := vec3.RGB{128, 255, 0}
  assert a.str() == '128 255 0'
}
