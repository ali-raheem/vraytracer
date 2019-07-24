    
#include <stdio.h>  // TODO remove all these includes, define all function signatures and types manually 
#include <stdlib.h>
#include <signal.h>
#include <stdarg.h> // for va_list 
#include <inttypes.h>  // int64_t etc 


#if defined(__linux__) || defined(__OpenBSD__) 
#include <pthread.h> 
#endif 


#ifdef __APPLE__ 
#include <pthread.h> 
#endif 


#ifdef _WIN32 
#include <windows.h>
//#include <WinSock2.h> 
#endif 

//================================== TYPEDEFS ================================*/ 

typedef unsigned char byte;
typedef unsigned int uint;
typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;
typedef uint32_t rune;
typedef float f32;
typedef double f64; 
typedef unsigned char* byteptr;
typedef int* intptr;
typedef void* voidptr;
typedef struct array array;
typedef struct map map;
typedef array array_string; 
typedef array array_int; 
typedef array array_byte; 
typedef array array_uint; 
typedef array array_float; 
typedef array array_f32; 
typedef array array_f64; 
typedef map map_int; 
typedef map map_string; 
#ifndef bool
	typedef int bool;
	#define true 1
	#define false 0
#endif

//============================== HELPER C MACROS =============================*/ 

#define _PUSH(arr, val, tmp, tmp_typ) {tmp_typ tmp = (val); array__push(arr, &tmp);}
#define _PUSH_MANY(arr, val, tmp, tmp_typ) {tmp_typ tmp = (val); array__push_many(arr, tmp.data, tmp.len);}
#define _IN(typ, val, arr) array_##typ##_contains(arr, val) 
#define ALLOC_INIT(type, ...) (type *)memdup((type[]){ __VA_ARGS__ }, sizeof(type)) 

//================================== GLOBALS =================================*/   
//int V_ZERO = 0; 
byteptr g_str_buf; 
int load_so(byteptr);
void reload_so();
void init_consts();
 int g_test_ok = 1; 
 /*================================== FNS =================================*/

typedef struct array array;
typedef array array_int;
typedef array array_string;
typedef array array_byte;
typedef struct string string;
typedef struct ustring ustring;
typedef struct map map;
typedef struct Node Node;
typedef struct Option Option;
typedef struct vec3__Vec vec3__Vec;
typedef struct vec3__RGB vec3__RGB;
typedef struct vec3__Ray vec3__Ray;
struct array {
void* data;
int len;
int cap;
int element_size;
}; 
struct string {
int hash_cache;
byte* str;
int len;
}; 
struct ustring {
string s;
array_int runes;
int len;
}; 
struct map {
int element_size;
Node* root;
array_string _keys;
int key_i;
int size;
}; 
struct Node {
Node* left;
Node* right;
string key;
void* val;
}; 
struct Option {
byte data  [255 ];
string error;
bool ok;
}; 
struct vec3__Vec {
f32 i;
f32 j;
f32 k;
}; 
struct vec3__RGB {
int r;
int g;
int b;
}; 
struct vec3__Ray {
vec3__Vec a;
vec3__Vec b;
}; 

string _STR(const char*, ...);


string _STR_TMP(const char*, ...);

array new_array(int mylen, int cap, int elm_size);
array _make(int len, int cap, int elm_size);
array new_array_from_c_array(int len, int cap, int elm_size, void* c_array);
array new_array_from_c_array_no_alloc(int len, int cap, int elm_size, void* c_array);
array array_repeat(void* val, int nr_repeats, int elm_size);
void array_sort_with_compare(array* a, void* compare);
void array_insert(array* a, int i, void* val);
void array_prepend(array* a, void* val);
void array_delete(array* a, int idx);
void* array__get(array a, int i);
void* array_first(array a);
void* array_last(array a);
array array_left(array s, int n);
array array_right(array s, int n);
array array_slice(array s, int start, int _end);
void array_set(array* a, int idx, void* val);
void array__push(array* arr, void* val);
void array__push_many(array* arr, void* val, int size);
array array_reverse(array a);
string array_int_str(array_int a);
void v_array_free(array a);
string array_string_str(array_string a);
string array_byte_hex(array_byte b);
string tos(byte* s, int len);
string tos_clone(byte* s);
string tos2(byte* s);
string string_clone(string a);
string string_replace(string s, string rep, string with);
int string_int(string s);
i32 string_i32(string s);
i64 string_i64(string s);
f32 string_f32(string s);
f64 string_f64(string s);
u32 string_u32(string s);
u64 string_u64(string s);
bool string_eq(string s, string a);
bool string_ne(string s, string a);
bool string_lt(string s, string a);
bool string_le(string s, string a);
bool string_gt(string s, string a);
bool string_ge(string s, string a);
string string_add(string s, string a);
array_string string_split(string s, string delim);
array_string string_split_single(string s, byte delim);
array_string string_split_into_lines(string s);
string string_left(string s, int n);
string string_right(string s, int n);
string string_substr(string s, int start, int end);
int string_index(string s, string p);
int string_last_index(string s, string p);
int string_index_after(string s, string p, int start);
bool string_contains(string s, string p);
bool string_starts_with(string s, string p);
bool string_ends_with(string s, string p);
string string_to_lower(string s);
string string_to_upper(string s);
string string_find_between(string s, string start, string end);
bool array_string_contains(array_string ar, string val);
bool array_int_contains(array_int ar, int val);
bool is_space(byte c);
bool byte_is_space(byte c);
string string_trim_space(string s);
string string_trim(string s, byte c);
string string_trim_left(string s, string cutset);
string string_trim_right(string s, string cutset);
int compare_strings(string* a, string* b);
int compare_strings_by_len(string* a, string* b);
int compare_lower_strings(string* a, string* b);
void array_string_sort(array_string* s);
void array_string_sort_ignore_case(array_string* s);
void array_string_sort_by_len(array_string* s);
ustring string_ustring(string s);
ustring string_ustring_tmp(string s);
string ustring_substr(ustring u, int start, int end);
string ustring_left(ustring u, int pos);
string ustring_right(ustring u, int pos);
byte string_at(string s, int idx);
string ustring_at(ustring u, int idx);
void v_ustring_free(ustring u);
int abs(int a);
bool byte_is_digit(byte c);
bool byte_is_letter(byte c);
void v_string_free(string s);
string string_all_before(string s, string dot);
string string_all_before_last(string s, string dot);
string string_all_after(string s, string dot);
string array_string_join(array_string a, string del);
string array_string_join_lines(array_string s);
string string_reverse(string s);
string string_limit(string s, int max);
bool byte_is_white(byte c);
int string_hash(string s);
array_byte string_bytes(string s);
void v_exit(int code);
bool isnil(void* v);
void on_panic(int (*f)( int  /*FFF*/ ));
void print_backtrace();
void v_panic(string s);
void println(string s);
void eprintln(string s);
void v_print(string s);
byte* v_malloc(int n);
byte* v_calloc(int n);
void v_free(void* ptr);
void* memdup(void* src, int sz);
string double_str(double d);
string f64_str(f64 d);
string f32_str(f32 d);
string ptr_str(void* ptr);
string int_str(int nn);
string u8_str(u8 nn);
string i64_str(i64 nn);
string bool_str(bool b);
string int_hex(int n);
string i64_hex(i64 n);
bool array_byte_contains(array_byte a, byte val);
string rune_str(rune c);
string byte_str(byte c);
int utf8_char_len(byte b);
string utf32_to_str(u32 code);
string utf32_to_str_no_malloc(u32 code, void* buf);
int string_utf32_code(string _rune);
map new_map(int cap, int elm_size);
Node* new_node(string key, void* val, int element_size);
void map_insert(map* m, Node* n, string key, void* val);
bool Node_find(Node* n, string key, void* out, int element_size);
bool Node_find2(Node* n, string key, int element_size);
void map__set(map* m, string key, void* val);
void map_preorder_keys(map* m, Node* node);
array_string map_keys(map* m);
bool map_get(map m, string key, void* out);
bool map_exists(map m, string key);
void v_map_print(map m);
void v_map_free(map m);
string map_string_str(map_string m);
Option opt_ok(void* data, int size);
Option v_error(string s);
f64 math__abs(f64 a);
f64 math__acos(f64 a);
f64 math__asin(f64 a);
f64 math__atan(f64 a);
f64 math__atan2(f64 a, f64 b);
f64 math__cbrt(f64 a);
int math__ceil(f64 a);
f64 math__cos(f64 a);
f64 math__cosh(f64 a);
f64 math__degrees(f64 radians);
f64 math__exp(f64 a);
array_int math__digits(int n, int base);
f64 math__erf(f64 a);
f64 math__erfc(f64 a);
f64 math__exp2(f64 a);
int math__recursive_product(int n, int* current_number_ptr);
i64 math__factorial(int n);
f64 math__floor(f64 a);
f64 math__fmod(f64 a, f64 b);
f64 math__gamma(f64 a);
i64 math__gcd(i64 a, i64 b);
f64 math__hypot(f64 a, f64 b);
i64 math__lcm(i64 a, i64 b);
f64 math__log(f64 a);
f64 math__log2(f64 a);
f64 math__log10(f64 a);
f64 math__log_gamma(f64 a);
f64 math__log_n(f64 a, f64 b);
f64 math__max(f64 a, f64 b);
f64 math__min(f64 a, f64 b);
f64 math__pow(f64 a, f64 b);
f64 math__radians(f64 degrees);
f64 math__round(f64 f);
f64 math__sin(f64 a);
f64 math__sinh(f64 a);
f64 math__sqrt(f64 a);
f64 math__tan(f64 a);
f64 math__tanh(f64 a);
f64 math__trunc(f64 a);
f32 vec3__Vec_hypotenuse(vec3__Vec v);
f32 vec3__Vec_x(vec3__Vec v);
f32 vec3__Vec_y(vec3__Vec v);
f32 vec3__Vec_z(vec3__Vec v);
f32 vec3__Vec_length(vec3__Vec v);
string vec3__Vec_str(vec3__Vec v);
vec3__Vec vec3__Vec_plus(vec3__Vec a, vec3__Vec b);
vec3__Vec vec3__Vec_minus(vec3__Vec a, vec3__Vec b);
vec3__Vec vec3__Vec_(vec3__Vec a, vec3__Vec b);
vec3__Vec vec3__Vec_mul_scalar(vec3__Vec a, f32 t);
vec3__Vec vec3__Vec_div_scalar(vec3__Vec a, f32 t);
f32 vec3__Vec_dot(vec3__Vec v, vec3__Vec u);
vec3__Vec vec3__Vec_cross(vec3__Vec v, vec3__Vec u);
vec3__Vec vec3__Vec_make_unit(vec3__Vec v);
vec3__RGB vec3__Vec_to_rgb(vec3__Vec v);
string vec3__RGB_str(vec3__RGB c);
vec3__RGB vec3__RGB_mul_scalar(vec3__RGB c, f32 k);
vec3__Vec vec3__Ray_at(vec3__Ray r, f32 t);
string vec3__Ray_str(vec3__Ray r);
vec3__Vec vec3__Ray_make_unit(vec3__Ray r);
bool hit_sphere(vec3__Vec centre, f32 radius, vec3__Ray r);
vec3__Vec colour(vec3__Ray r);
array_int g_ustring_runes; // global
i64 total_m =  0; // global
#define math__E  2.71828182845904523536028747135266249775724709369995957496696763
#define math__Pi  3.14159265358979323846264338327950288419716939937510582097494459
#define math__Phi  1.61803398874989484820458683436563811772030917980576286213544862
#define math__Tau  6.28318530717958647692528676655900576839433879875021164194988918
#define math__Sqrt2  1.41421356237309504880168872420969807856967187537694807317667974
#define math__SqrtE  1.64872127070012814684865078781416357165377610071014801157507931
#define math__SqrtPi  1.77245385090551602729816748334114518279754945612238712821380779
#define math__SqrtTau  2.50662827463100050241576528481104525300698674060993831662992357
#define math__SqrtPhi  1.27201964951406896425242246173749149171560804184009624861664038
#define math__Ln2  0.693147180559945309417232121458176568075500134360255254120680009
f32 math__Log2E;
#define math__Ln10  2.30258509299404568401799145468436420760110148862877297603332790
f32 math__Log10E;
int math__MaxI8;
int math__MinI8;
int math__MaxI16;
int math__MinI16;
int math__MaxI32;
int math__MinI32;
int math__MaxU8;
int math__MaxU16;
int math__MaxU32;
int math__MaxU64;


 array new_array(int mylen, int cap, int elm_size) {
 
array arr= (array) { .len =  mylen , .cap =  cap , .element_size =  elm_size , .data =  v_malloc ( cap * elm_size ) } ;
 
return  arr ;
 
 
 }
 array _make(int len, int cap, int elm_size) {
 
return  new_array ( len , cap , elm_size ) ;
 
 
 }
 array new_array_from_c_array(int len, int cap, int elm_size, void* c_array) {
 
array arr= (array) { .len =  len , .cap =  cap , .element_size =  elm_size , .data =  v_malloc ( cap * elm_size ) } ;
 
 memcpy ( arr .data ,  c_array ,  len * elm_size ) ;
 
return  arr ;
 
 
 }
 array new_array_from_c_array_no_alloc(int len, int cap, int elm_size, void* c_array) {
 
array arr= (array) { .len =  len , .cap =  cap , .element_size =  elm_size , .data =  c_array } ;
 
return  arr ;
 
 
 }
 array array_repeat(void* val, int nr_repeats, int elm_size) {
 
array arr= (array) { .len =  nr_repeats , .cap =  nr_repeats , .element_size =  elm_size , .data =  v_malloc ( nr_repeats * elm_size ) } ;
 
 for (
int i= 0  ;  i < nr_repeats  ;  i ++ ) { 
 
 
 memcpy ( arr .data + i * elm_size ,  val ,  elm_size ) ;
 
 }
 ;
 
return  arr ;
 
 
 }
 void array_sort_with_compare(array* a, void* compare) {
 
 qsort ( a ->data ,  a ->len ,  a ->element_size ,  compare ) ;
 
 
 }
 void array_insert(array* a, int i, void* val) {
 
 if ( i >= a ->len ) {
 
 v_panic ( tos2("array.insert: index larger than length") ) ;
 
 return ;
 
 }
 ;
 
 array__push( a , val ) ;
 
int size= a ->element_size ;
 
 memmove ( a ->data + ( i + 1 ) * size ,  a ->data + i * size ,  ( a ->len - i ) * size ) ;
 
 array_set( a , i , val ) ;
 
 
 }
 void array_prepend(array* a, void* val) {
 
 array_insert( a , 0 , val ) ;
 
 
 }
 void array_delete(array* a, int idx) {
 
int size= a ->element_size ;
 
 memmove ( a ->data + idx * size ,  a ->data + ( idx + 1 ) * size ,  ( a ->len - idx ) * size ) ;
 
 a ->len -- ;
 
 a ->cap -- ;
 
 
 }
 void* array__get(array a, int i) {
 
 if ( i < 0  ||  i >= a .len ) {
 
 v_panic ( _STR("array index out of range: %d/%d", i, a .len) ) ;
 
 }
 ;
 
return  a .data + i * a .element_size ;
 
 
 }
 void* array_first(array a) {
 
 if ( a .len == 0 ) {
 
 v_panic ( tos2("array.first: empty array") ) ;
 
 }
 ;
 
return  a .data + 0 ;
 
 
 }
 void* array_last(array a) {
 
 if ( a .len == 0 ) {
 
 v_panic ( tos2("array.last: empty array") ) ;
 
 }
 ;
 
return  a .data + ( a .len - 1 ) * a .element_size ;
 
 
 }
 array array_left(array s, int n) {
 
 if ( n >= s .len ) {
 
return  s ;
 
 }
 ;
 
return  array_slice( s , 0 , n ) ;
 
 
 }
 array array_right(array s, int n) {
 
 if ( n >= s .len ) {
 
return  s ;
 
 }
 ;
 
return  array_slice( s , n , s .len ) ;
 
 
 }
 array array_slice(array s, int start, int _end) {
 
int end= _end ;
 
 if ( start > end ) {
 
 v_panic ( _STR("invalid slice index: %d > %d", start, end) ) ;
 
 }
 ;
 
 if ( end > s .len ) {
 
 v_panic ( _STR("runtime error: slice bounds out of range (%d >= %d)", end, s .len) ) ;
 
 }
 ;
 
 if ( start < 0 ) {
 
 v_panic ( _STR("runtime error: slice bounds out of range (%d < 0)", start) ) ;
 
 }
 ;
 
int l= end - start ;
 
array res= (array) { .element_size =  s .element_size , .data =  s .data + start * s .element_size , .len =  l , .cap =  l } ;
 
return  res ;
 
 
 }
 void array_set(array* a, int idx, void* val) {
 
 if ( idx < 0  ||  idx >= a ->len ) {
 
 v_panic ( _STR("array index out of range: %d / %d", idx, a ->len) ) ;
 
 }
 ;
 
 memcpy ( a ->data + a ->element_size * idx ,  val ,  a ->element_size ) ;
 
 
 }
 void array__push(array* arr, void* val) {
 
 if ( arr ->len >= arr ->cap - 1 ) {
 
int cap= ( arr ->len + 1 ) * 2 ;
 
 if ( arr ->cap == 0 ) {
 
 arr ->data  =  v_malloc ( cap * arr ->element_size ) ;
 
 }
  else { 
 
 arr ->data  =  realloc ( arr ->data ,  cap * arr ->element_size ) ;
 
 }
 ;
 
 arr ->cap  =  cap ;
 
 }
 ;
 
 memcpy ( arr ->data + arr ->element_size * arr ->len ,  val ,  arr ->element_size ) ;
 
 arr ->len ++ ;
 
 
 }
 void array__push_many(array* arr, void* val, int size) {
 
 if ( arr ->len >= arr ->cap - size ) {
 
int cap= ( arr ->len + size ) * 2 ;
 
 if ( arr ->cap == 0 ) {
 
 arr ->data  =  v_malloc ( cap * arr ->element_size ) ;
 
 }
  else { 
 
 arr ->data  =  realloc ( arr ->data ,  cap * arr ->element_size ) ;
 
 }
 ;
 
 arr ->cap  =  cap ;
 
 }
 ;
 
 memcpy ( arr ->data + arr ->element_size * arr ->len ,  val ,  arr ->element_size * size ) ;
 
 arr ->len  +=  size ;
 
 
 }
 array array_reverse(array a) {
 
array arr= (array) { .len =  a .len , .cap =  a .cap , .element_size =  a .element_size , .data =  v_malloc ( a .cap * a .element_size ) } ;
 
 for (
int i= 0  ;  i < a .len  ;  i ++ ) { 
 
 
 memcpy ( arr .data + i * arr .element_size ,  & /*vvar*/  ( *(void**) array__get( a , a .len - 1 - i) ) ,  arr .element_size ) ;
 
 }
 ;
 
return  arr ;
 
 
 }
 string array_int_str(array_int a) {
 
string res= tos2("[") ;
 
 for (
int i= 0  ;  i < a .len  ;  i ++ ) { 
 
 
int val= ( *(int*) array__get( a , i) ) ;
 
 res = string_add(res,  _STR("%d", val) ) ;
 
 if ( i < a .len - 1 ) {
 
 res = string_add(res,  tos2(", ") ) ;
 
 }
 ;
 
 }
 ;
 
 res = string_add(res,  tos2("]") ) ;
 
return  res ;
 
 
 }
 void v_array_free(array a) {
 
 free ( a .data ) ;
 
 
 }
 string array_string_str(array_string a) {
 
string res= tos2("[") ;
 
 for (
int i= 0  ;  i < a .len  ;  i ++ ) { 
 
 
string val= ( *(string*) array__get( a , i) ) ;
 
 res = string_add(res,  _STR("\"%.*s\"", val.len, val.str) ) ;
 
 if ( i < a .len - 1 ) {
 
 res = string_add(res,  tos2(", ") ) ;
 
 }
 ;
 
 }
 ;
 
 res = string_add(res,  tos2("]") ) ;
 
return  res ;
 
 
 }
 string array_byte_hex(array_byte b) {
 
byte* hex= v_malloc ( b .len * 2 + 1 ) ;
 
byte* ptr= & /*vvar*/  hex [/*ptr*/ 0 ]/*rbyte 1*/ ;
 
 for (
int i= 0  ;  i < b .len  ;  i ++ ) { 
 
 
 ptr  +=  sprintf ( ptr ,  "%02X" ,  ( *(byte*) array__get( b , i) ) ) ;
 
 }
 ;
 
return  (tos2( hex ) ) ;
 
 
 }
 void todo() {
 
 
 }
 string tos(byte* s, int len) {
 
 if ( isnil ( s ) ) {
 
 v_panic ( tos2("tos(): nil string") ) ;
 
 }
 ;
 
return  (string) { .str =  s , .len =  len , .hash_cache = 0 , } ;
 
 
 }
 string tos_clone(byte* s) {
 
 if ( isnil ( s ) ) {
 
 v_panic ( tos2("tos: nil string") ) ;
 
return  (string) { .hash_cache = 0 , .str = 0 , .len = 0 } ;
 
 }
 ;
 
int len= strlen ( s ) ;
 
string res= tos ( s , len ) ;
 
return  string_clone( res ) ;
 
 
 }
 string tos2(byte* s) {
 
 if ( isnil ( s ) ) {
 
 v_panic ( tos2("tos2: nil string") ) ;
 
return  (string) { .hash_cache = 0 , .str = 0 , .len = 0 } ;
 
 }
 ;
 
int len= strlen ( s ) ;
 
string res= tos ( s , len ) ;
 
return  res ;
 
 
 }
 string string_clone(string a) {
 
string b= (string) { .len =  a .len , .str =  v_malloc ( a .len + 1 ) , .hash_cache = 0 , } ;
 
 for (
int i= 0  ;  i < a .len  ;  i ++ ) { 
 
 
 b .str[ i ]/*rbyte 1*/  =  a .str[ i ]/*rbyte 0*/ ;
 
 }
 ;
 
 b .str[ a .len ]/*rbyte 1*/  =  '\0' ;
 
return  b ;
 
 
 }
 string string_replace(string s, string rep, string with) {
 
 if ( s .len == 0  ||  rep .len == 0 ) {
 
return  s ;
 
 }
 ;
 
array_int idxs=new_array_from_c_array(0, 0, sizeof(int), (int[]) {   }) ;
 
 {
 
 }
 
string rem= s ;
 
int rstart= 0 ;
 
 while (1) { 
 
int i= string_index( rem , rep ) ;
 
 if ( i < 0 ) {
 
 break
 ;
 
 }
 ;
 
_PUSH(& idxs , ( rstart + i ), tmp11, int) ;
 
 i  +=  rep .len ;
 
 rstart  +=  i ;
 
 rem  =  string_substr( rem , i , rem .len ) ;
 
 }
 ;
 
 if ( idxs .len == 0 ) {
 
return  s ;
 
 }
 ;
 
int new_len= s .len + idxs .len * ( with .len - rep .len ) ;
 
byte* b= v_malloc ( new_len + 1 ) ;
 
int idx_pos= 0 ;
 
int cur_idx= ( *(int*) array__get( idxs , idx_pos) ) ;
 
int b_i= 0 ;
 
 for (
int i= 0  ;  i < s .len  ;  i ++ ) { 
 
 
 if ( i == cur_idx ) {
 
 for (
int j= 0  ;  j < with .len  ;  j ++ ) { 
 
 
 b [/*ptr*/ b_i ]/*rbyte 1*/  =  with .str[ j ]/*rbyte 0*/ ;
 
 b_i ++ ;
 
 }
 ;
 
 i  +=  rep .len - 1 ;
 
 idx_pos ++ ;
 
 if ( idx_pos < idxs .len ) {
 
 cur_idx  =  ( *(int*) array__get( idxs , idx_pos) ) ;
 
 }
 ;
 
 }
  else { 
 
 b [/*ptr*/ b_i ]/*rbyte 1*/  =  s .str[ i ]/*rbyte 0*/ ;
 
 b_i ++ ;
 
 }
 ;
 
 }
 ;
 
 b [/*ptr*/ new_len ]/*rbyte 1*/  =  '\0' ;
 
return  tos ( b , new_len ) ;
 
 
 }
 int string_int(string s) {
 
return  atoi ( s .str ) ;
 
 
 }
 i32 string_i32(string s) {
 
return  atol ( s .str ) ;
 
 
 }
 i64 string_i64(string s) {
 
return  atoll ( s .str ) ;
 
 
 }
 f32 string_f32(string s) {
 
return  atof ( s .str ) ;
 
 
 }
 f64 string_f64(string s) {
 
return  atof ( s .str ) ;
 
 
 }
 u32 string_u32(string s) {
 
return  strtoul ( s .str ,  0 ,  0 ) ;
 
 
 }
 u64 string_u64(string s) {
 
return  strtoull ( s .str ,  0 ,  0 ) ;
 
 
 }
 bool string_eq(string s, string a) {
 
 if ( isnil ( s .str ) ) {
 
 v_panic ( tos2("string.eq(): nil string") ) ;
 
 }
 ;
 
 if ( s .len != a .len ) {
 
return  0 ;
 
 }
 ;
 
 for (
int i= 0  ;  i < s .len  ;  i ++ ) { 
 
 
 if ( s .str[ i ]/*rbyte 0*/ != a .str[ i ]/*rbyte 0*/ ) {
 
return  0 ;
 
 }
 ;
 
 }
 ;
 
return  1 ;
 
 
 }
 bool string_ne(string s, string a) {
 
return  ! string_eq( s , a ) ;
 
 
 }
 bool string_lt(string s, string a) {
 
 for (
int i= 0  ;  i < s .len  ;  i ++ ) { 
 
 
 if ( i >= a .len  ||  s .str[ i ]/*rbyte 0*/ > a .str[ i ]/*rbyte 0*/ ) {
 
return  0 ;
 
 }
  else  if ( s .str[ i ]/*rbyte 0*/ < a .str[ i ]/*rbyte 0*/ ) {
 
return  1 ;
 
 }
 ;
 
 }
 ;
 
 if ( s .len < a .len ) {
 
return  1 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 bool string_le(string s, string a) {
 
return  string_lt( s , a )  ||  string_eq( s , a ) ;
 
 
 }
 bool string_gt(string s, string a) {
 
return  ! string_le( s , a ) ;
 
 
 }
 bool string_ge(string s, string a) {
 
return  ! string_lt( s , a ) ;
 
 
 }
 string string_add(string s, string a) {
 
int new_len= a .len + s .len ;
 
string res= (string) { .len =  new_len , .str =  v_malloc ( new_len + 1 ) , .hash_cache = 0 , } ;
 
 for (
int j= 0  ;  j < s .len  ;  j ++ ) { 
 
 
 res .str[ j ]/*rbyte 1*/  =  s .str[ j ]/*rbyte 0*/ ;
 
 }
 ;
 
 for (
int j= 0  ;  j < a .len  ;  j ++ ) { 
 
 
 res .str[ s .len + j ]/*rbyte 1*/  =  a .str[ j ]/*rbyte 0*/ ;
 
 }
 ;
 
 res .str[ new_len ]/*rbyte 1*/  =  '\0' ;
 
return  res ;
 
 
 }
 array_string string_split(string s, string delim) {
 
array_string res=new_array_from_c_array(0, 0, sizeof(string), (string[]) {   }) ;
 
 if ( delim .len == 0 ) {
 
_PUSH(& res , ( s ), tmp30, string) ;
 
return  res ;
 
 }
 ;
 
 if ( delim .len == 1 ) {
 
return  string_split_single( s , delim .str[ 0 ]/*rbyte 0*/ ) ;
 
 }
 ;
 
int i= 0 ;
 
int start= 0 ;
 
 while ( i < s .len ) {
 
 
bool a= s .str[ i ]/*rbyte 0*/ == delim .str[ 0 ]/*rbyte 0*/ ;
 
int j= 1 ;
 
 while ( j < delim .len  &&  a ) {
 
 
 a  =  a  &&  s .str[ i + j ]/*rbyte 0*/ == delim .str[ j ]/*rbyte 0*/ ;
 
 j ++ ;
 
 }
 ;
 
bool last= i == s .len - 1 ;
 
 if ( a  ||  last ) {
 
 if ( last ) {
 
 i ++ ;
 
 }
 ;
 
string val= string_substr( s , start , i ) ;
 
 if ( val .len > 0 ) {
 
 if ( string_starts_with( val , delim ) ) {
 
 val  =  string_right( val , delim .len ) ;
 
 }
 ;
 
_PUSH(& res , ( string_trim_space( val ) ), tmp37, string) ;
 
 }
 ;
 
 start  =  i ;
 
 }
 ;
 
 i ++ ;
 
 }
 ;
 
return  res ;
 
 
 }
 array_string string_split_single(string s, byte delim) {
 
array_string res=new_array_from_c_array(0, 0, sizeof(string), (string[]) {   }) ;
 
 if ( ((int)( delim ) ) == 0 ) {
 
_PUSH(& res , ( s ), tmp39, string) ;
 
return  res ;
 
 }
 ;
 
int i= 0 ;
 
int start= 0 ;
 
 while ( i < s .len ) {
 
 
bool a= s .str[ i ]/*rbyte 0*/ == delim ;
 
bool b= i == s .len - 1 ;
 
 if ( a  ||  b ) {
 
 if ( i == s .len - 1 ) {
 
 i ++ ;
 
 }
 ;
 
string val= string_substr( s , start , i ) ;
 
 if ( val .len > 0 ) {
 
_PUSH(& res , ( string_trim_space( val ) ), tmp45, string) ;
 
 }
 ;
 
 start  =  i + 1 ;
 
 }
 ;
 
 i ++ ;
 
 }
 ;
 
return  res ;
 
 
 }
 array_string string_split_into_lines(string s) {
 
array_string res=new_array_from_c_array(0, 0, sizeof(string), (string[]) {   }) ;
 
 if ( s .len == 0 ) {
 
return  res ;
 
 }
 ;
 
int start= 0 ;
 
 for (
int i= 0  ;  i < s .len  ;  i ++ ) { 
 
 
bool last= i == s .len - 1 ;
 
 if ( ((int)( s .str[ i ]/*rbyte 0*/ ) ) == 10  ||  last ) {
 
 if ( last ) {
 
 i ++ ;
 
 }
 ;
 
string line= string_substr( s , start , i ) ;
 
_PUSH(& res , ( line ), tmp51, string) ;
 
 start  =  i + 1 ;
 
 }
 ;
 
 }
 ;
 
return  res ;
 
 
 }
 string string_left(string s, int n) {
 
 if ( n >= s .len ) {
 
return  s ;
 
 }
 ;
 
return  string_substr( s , 0 , n ) ;
 
 
 }
 string string_right(string s, int n) {
 
 if ( n >= s .len ) {
 
return  tos2("") ;
 
 }
 ;
 
return  string_substr( s , n , s .len ) ;
 
 
 }
 string string_substr(string s, int start, int end) {
 
 if ( start >= s .len ) {
 
return  tos2("") ;
 
 }
 ;
 
int len= end - start ;
 
string res= (string) { .len =  len , .str =  v_malloc ( len + 1 ) , .hash_cache = 0 , } ;
 
 for (
int i= 0  ;  i < len  ;  i ++ ) { 
 
 
 res .str [/*ptr*/ i ]/*rbyte 1*/  =  s .str [/*ptr*/ start + i ]/*rbyte 0*/ ;
 
 }
 ;
 
 res .str [/*ptr*/ len ]/*rbyte 1*/  =  '\0' ;
 
return  res ;
 
 
 }
 int string_index(string s, string p) {
 
 if ( p .len > s .len ) {
 
return  - 1 ;
 
 }
 ;
  
 int tmp55 =  0; 

array_int prefix= array_repeat(&tmp55,  p .len , sizeof(int) ) ;
 
int j= 0 ;
 
 for (
int i= 1  ;  i < p .len  ;  i ++ ) { 
 
 
 while ( p .str[ j ]/*rbyte 0*/ != p .str[ i ]/*rbyte 0*/  &&  j > 0 ) {
 
 
 j  =  ( *(int*) array__get( prefix , j - 1) ) ;
 
 }
 ;
 
 if ( p .str[ j ]/*rbyte 0*/ == p .str[ i ]/*rbyte 0*/ ) {
 
 j ++ ;
 
 }
 ;
  
 int tmp61 =  j; 

array_set(&/*q*/ prefix , i , & tmp61) ;
 
 }
 ;
 
 j  =  0 ;
 
 for (
int i= 0  ;  i < s .len  ;  i ++ ) { 
 
 
 while ( p .str[ j ]/*rbyte 0*/ != s .str[ i ]/*rbyte 0*/  &&  j > 0 ) {
 
 
 j  =  ( *(int*) array__get( prefix , j - 1) ) ;
 
 }
 ;
 
 if ( p .str[ j ]/*rbyte 0*/ == s .str[ i ]/*rbyte 0*/ ) {
 
 j ++ ;
 
 }
 ;
 
 if ( j == p .len ) {
 
 v_array_free( prefix ) ;
 
return  i - p .len + 1 ;
 
 }
 ;
 
 }
 ;
 
 v_array_free( prefix ) ;
 
return  - 1 ;
 
 
 }
 int string_last_index(string s, string p) {
 
 if ( p .len > s .len ) {
 
return  - 1 ;
 
 }
 ;
 
int i= s .len - p .len ;
 
 while ( i >= 0 ) {
 
 
int j= 0 ;
 
 while ( j < p .len  &&  s .str[ i + j ]/*rbyte 0*/ == p .str[ j ]/*rbyte 0*/ ) {
 
 
 j ++ ;
 
 }
 ;
 
 if ( j == p .len ) {
 
return  i ;
 
 }
 ;
 
 i -- ;
 
 }
 ;
 
return  - 1 ;
 
 
 }
 int string_index_after(string s, string p, int start) {
 
 if ( p .len > s .len ) {
 
return  - 1 ;
 
 }
 ;
 
int strt= start ;
 
 if ( start < 0 ) {
 
 strt  =  0 ;
 
 }
 ;
 
 if ( start >= s .len ) {
 
return  - 1 ;
 
 }
 ;
 
int i= strt ;
 
 while ( i < s .len ) {
 
 
int j= 0 ;
 
int ii= i ;
 
 while ( j < p .len  &&  s .str[ ii ]/*rbyte 0*/ == p .str[ j ]/*rbyte 0*/ ) {
 
 
 j ++ ;
 
 ii ++ ;
 
 }
 ;
 
 if ( j == p .len ) {
 
return  i ;
 
 }
 ;
 
 i ++ ;
 
 }
 ;
 
return  - 1 ;
 
 
 }
 bool string_contains(string s, string p) {
 
bool res= string_index( s , p ) > 0 - 1 ;
 
return  res ;
 
 
 }
 bool string_starts_with(string s, string p) {
 
bool res= string_index( s , p ) == 0 ;
 
return  res ;
 
 
 }
 bool string_ends_with(string s, string p) {
 
 if ( p .len > s .len ) {
 
return  0 ;
 
 }
 ;
 
bool res= string_last_index( s , p ) == s .len - p .len ;
 
return  res ;
 
 
 }
 string string_to_lower(string s) {
 
byte* b= v_malloc ( s .len ) ;
 
 for (
int i= 0  ;  i < s .len  ;  i ++ ) { 
 
 
 b [/*ptr*/ i ]/*rbyte 1*/  =  tolower ( s .str [/*ptr*/ i ]/*rbyte 0*/ ) ;
 
 }
 ;
 
return  tos ( b , s .len ) ;
 
 
 }
 string string_to_upper(string s) {
 
byte* b= v_malloc ( s .len ) ;
 
 for (
int i= 0  ;  i < s .len  ;  i ++ ) { 
 
 
 b [/*ptr*/ i ]/*rbyte 1*/  =  toupper ( s .str [/*ptr*/ i ]/*rbyte 0*/ ) ;
 
 }
 ;
 
return  tos ( b , s .len ) ;
 
 
 }
 string string_find_between(string s, string start, string end) {
 
int start_pos= string_index( s , start ) ;
 
 if ( start_pos == - 1 ) {
 
return  tos2("") ;
 
 }
 ;
 
string val= string_right( s , start_pos + start .len ) ;
 
int end_pos= string_index( val , end ) ;
 
 if ( end_pos == - 1 ) {
 
return  val ;
 
 }
 ;
 
return  string_left( val , end_pos ) ;
 
 
 }
 bool array_string_contains(array_string ar, string val) {
 
 array_string tmp81 =  ar;
 ;
for (int tmp82 = 0; tmp82 < tmp81 .len; tmp82 ++) {
 string s = ((string *) tmp81.data)[tmp82];
 
 
 if (string_eq( s , val ) ) {
 
return  1 ;
 
 }
 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 bool array_int_contains(array_int ar, int val) {
 
 array_int tmp83 =  ar ;
 ;
for (int i = 0; i < tmp83 .len; i ++) {
 int s = ((int *) tmp83 . data)[i];
 
 
 if ( s == val ) {
 
return  1 ;
 
 }
 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 bool is_space(byte c) {
 
return  isspace ( c ) ;
 
 
 }
 bool byte_is_space(byte c) {
 
return  is_space ( c ) ;
 
 
 }
 string string_trim_space(string s) {
 
 if (string_eq( s , tos2("") ) ) {
 
return  tos2("") ;
 
 }
 ;
 
int i= 0 ;
 
 while ( i < s .len  &&  is_space ( s .str[ i ]/*rbyte 0*/ ) ) {
 
 
 i ++ ;
 
 }
 ;
 
int end= s .len - 1 ;
 
 while ( end >= 0  &&  is_space ( s .str[ end ]/*rbyte 0*/ ) ) {
 
 
 end -- ;
 
 }
 ;
 
string res= string_substr( s , i , end + 1 ) ;
 
return  res ;
 
 
 }
 string string_trim(string s, byte c) {
 
 if (string_eq( s , tos2("") ) ) {
 
return  tos2("") ;
 
 }
 ;
 
int i= 0 ;
 
 while ( i < s .len  &&  c == s .str[ i ]/*rbyte 0*/ ) {
 
 
 i ++ ;
 
 }
 ;
 
string res= string_right( s , i ) ;
 
int end= res .len - 1 ;
 
 while ( end >= 0  &&  c == res .str[ end ]/*rbyte 1*/ ) {
 
 
 end -- ;
 
 }
 ;
 
 res  =  string_left( res , end + 1 ) ;
 
return  res ;
 
 
 }
 string string_trim_left(string s, string cutset) {
 
int start= string_index( s , cutset ) ;
 
 if ( start != 0 ) {
 
return  s ;
 
 }
 ;
 
 while ( start < s .len - 1  &&  s .str[ start ]/*rbyte 0*/ == cutset .str[ 0 ]/*rbyte 0*/ ) {
 
 
 start ++ ;
 
 }
 ;
 
return  string_right( s , start ) ;
 
 
 }
 string string_trim_right(string s, string cutset) {
 
int pos= string_last_index( s , cutset ) ;
 
 if ( pos == - 1 ) {
 
return  s ;
 
 }
 ;
 
return  string_left( s , pos ) ;
 
 
 }
 int compare_strings(string* a, string* b) {
 
 if ( string_lt(* a ,* b ) ) {
 
return  - 1 ;
 
 }
 ;
 
 if ( string_gt(* a ,* b ) ) {
 
return  1 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 int compare_strings_by_len(string* a, string* b) {
 
 if ( a ->len < b ->len ) {
 
return  - 1 ;
 
 }
 ;
 
 if ( a ->len > b ->len ) {
 
return  1 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 int compare_lower_strings(string* a, string* b) {
 
string aa= string_to_lower(* a ) ;
 
string bb= string_to_lower(* b ) ;
 
return  compare_strings (& /*11 EXP:"string*" GOT:"string" */ aa ,& /*11 EXP:"string*" GOT:"string" */ bb ) ;
 
 
 }
 void array_string_sort(array_string* s) {
 
 array_sort_with_compare( s , compare_strings ) ;
 
 
 }
 void array_string_sort_ignore_case(array_string* s) {
 
 array_sort_with_compare( s , compare_lower_strings ) ;
 
 
 }
 void array_string_sort_by_len(array_string* s) {
 
 array_sort_with_compare( s , compare_strings_by_len ) ;
 
 
 }
 ustring string_ustring(string s) {
 
ustring res= (ustring) { .s =  s , .runes =  new_array ( 0 , s .len , sizeof( int) ) , .len = 0 } ;
 
 for (
int i= 0  ;  i < s .len  ;  i ++ ) { 
 
 
int char_len= utf8_char_len ( s .str [/*ptr*/ i ]/*rbyte 0*/ ) ;
 
_PUSH(& res .runes , ( i ), tmp97, int) ;
 
 i  +=  char_len - 1 ;
 
 res .len ++ ;
 
 }
 ;
 
return  res ;
 
 
 }
 ustring string_ustring_tmp(string s) {
 
ustring res= (ustring) { .s =  s , .runes = new_array(0, 1, sizeof(int)) , .len = 0 } ;
 
 res .runes  =  g_ustring_runes ;
 
 res .runes .len  =  s .len ;
 
int j= 0 ;
 
 for (
int i= 0  ;  i < s .len  ;  i ++ ) { 
 
 
int char_len= utf8_char_len ( s .str [/*ptr*/ i ]/*rbyte 0*/ ) ;
  
 int tmp102 =  i; 

array_set(&/*q*/ res .runes , j , & tmp102) ;
 
 j ++ ;
 
 i  +=  char_len - 1 ;
 
 res .len ++ ;
 
 }
 ;
 
return  res ;
 
 
 }
 string ustring_substr(ustring u, int start, int end) {
 
 start  =  ( *(int*) array__get( u .runes , start) ) ;
 
 if ( end >= u .runes .len ) {
 
 end  =  u .s .len ;
 
 }
  else { 
 
 end  =  ( *(int*) array__get( u .runes , end) ) ;
 
 }
 ;
 
return  string_substr( u .s , start , end ) ;
 
 
 }
 string ustring_left(ustring u, int pos) {
 
return  ustring_substr( u , 0 , pos ) ;
 
 
 }
 string ustring_right(ustring u, int pos) {
 
return  ustring_substr( u , pos , u .len ) ;
 
 
 }
 byte string_at(string s, int idx) {
 
 if ( idx < 0  ||  idx >= s .len ) {
 
 v_panic ( _STR("string index out of range: %d / %d", idx, s .len) ) ;
 
 }
 ;
 
return  s .str [/*ptr*/ idx ]/*rbyte 0*/ ;
 
 
 }
 string ustring_at(ustring u, int idx) {
 
return  ustring_substr( u , idx , idx + 1 ) ;
 
 
 }
 void v_ustring_free(ustring u) {
 
 v_array_free( u .runes ) ;
 
 
 }
 int abs(int a) {
 
 if ( a >= 0 ) {
 
return  a ;
 
 }
 ;
 
return  - a ;
 
 
 }
 bool byte_is_digit(byte c) {
 
return  c >= '0'  &&  c <= '9' ;
 
 
 }
 bool byte_is_letter(byte c) {
 
return  ( c >= 'a'  &&  c <= 'z' )  ||  ( c >= 'A'  &&  c <= 'Z' ) ;
 
 
 }
 void v_string_free(string s) {
 
 free ( s .str ) ;
 
 
 }
 string string_all_before(string s, string dot) {
 
int pos= string_index( s , dot ) ;
 
 if ( pos == - 1 ) {
 
return  s ;
 
 }
 ;
 
return  string_left( s , pos ) ;
 
 
 }
 string string_all_before_last(string s, string dot) {
 
int pos= string_last_index( s , dot ) ;
 
 if ( pos == - 1 ) {
 
return  s ;
 
 }
 ;
 
return  string_left( s , pos ) ;
 
 
 }
 string string_all_after(string s, string dot) {
 
int pos= string_last_index( s , dot ) ;
 
 if ( pos == - 1 ) {
 
return  s ;
 
 }
 ;
 
return  string_right( s , pos + dot .len ) ;
 
 
 }
 string array_string_join(array_string a, string del) {
 
 if ( a .len == 0 ) {
 
return  tos2("") ;
 
 }
 ;
 
int len= 0 ;
 
 array_string tmp111 =  a ;
 ;
for (int i = 0; i < tmp111 .len; i ++) {
 string val = ((string *) tmp111 . data)[i];
 
 
 len  +=  val .len + del .len ;
 
 }
 ;
 
 len  -=  del .len ;
 
string res= tos2("") ;
 
 res .len  =  len ;
 
 res .str  =  v_malloc ( res .len + 1 ) ;
 
int idx= 0 ;
 
 array_string tmp114 =  a ;
 ;
for (int i = 0; i < tmp114 .len; i ++) {
 string val = ((string *) tmp114 . data)[i];
 
 
 for (
int j= 0  ;  j < val .len  ;  j ++ ) { 
 
 
byte c= val .str[ j ]/*rbyte 0*/ ;
 
 res .str [/*ptr*/ idx ]/*rbyte 1*/  =  val .str [/*ptr*/ j ]/*rbyte 0*/ ;
 
 idx ++ ;
 
 }
 ;
 
 if ( i != a .len - 1 ) {
 
 for (
int k= 0  ;  k < del .len  ;  k ++ ) { 
 
 
 res .str [/*ptr*/ idx ]/*rbyte 1*/  =  del .str [/*ptr*/ k ]/*rbyte 0*/ ;
 
 idx ++ ;
 
 }
 ;
 
 }
 ;
 
 }
 ;
 
 res .str [/*ptr*/ res .len ]/*rbyte 1*/  =  '\0' ;
 
return  res ;
 
 
 }
 string array_string_join_lines(array_string s) {
 
return  array_string_join( s , tos2("\n") ) ;
 
 
 }
 string string_reverse(string s) {
 
string res= (string) { .len =  s .len , .str =  v_malloc ( s .len ) , .hash_cache = 0 , } ;
 
 for (
int i= s .len - 1  ;  i >= 0  ;  i -- ) { 
 
 
 res .str[ s .len - i - 1 ]/*rbyte 1*/  =  s .str[ i ]/*rbyte 0*/ ;
 
 }
 ;
 
return  res ;
 
 
 }
 string string_limit(string s, int max) {
 
ustring u= string_ustring( s ) ;
 
 if ( u .len <= max ) {
 
return  s ;
 
 }
 ;
 
return  ustring_substr( u , 0 , max ) ;
 
 
 }
 bool byte_is_white(byte c) {
 
int i= ((int)( c ) ) ;
 
return  i == 10  ||  i == 32  ||  i == 9  ||  i == 13  ||  c == '\r' ;
 
 
 }
 int string_hash(string s) {
 
int h= s .hash_cache ;
 
 if ( h == 0  &&  s .len > 0 ) {
 
 string tmp123 =  s;
 ;
for (int tmp124 = 0; tmp124 < tmp123 .len; tmp124 ++) {
 byte c = ((byte *) tmp123.str)[tmp124];
 
 
 h  =  h * 31 + ((int)( c ) ) ;
 
 }
 ;
 
 }
 ;
 
return  h ;
 
 
 }
 array_byte string_bytes(string s) {
 
 if ( s .len == 0 ) {
 
return new_array_from_c_array(0, 0, sizeof(byte), (byte[]) {   }) ;
 
 }
 ;
  
 byte tmp125 =  ((byte)( 0 ) ); 

array_byte buf= array_repeat(&tmp125,  s .len , sizeof(byte) ) ;
 
 memcpy ( buf .data ,  s .str ,  s .len ) ;
 
return  buf ;
 
 
 }
 void v_exit(int code) {
 
 exit ( code ) ;
 
 
 }
 bool isnil(void* v) {
 
return  v == 0 ;
 
 
 }
 void on_panic(int (*f)( int  /*FFF*/ )) {
 
 
 }
 void print_backtrace() {
 
 return ;
 
 #ifdef __APPLE__
 
voidptr buffer  [100 ]= {} ;
 
void* nr_ptrs= backtrace ( buffer ,  100 ) ;
 
 backtrace_symbols_fd ( buffer ,  nr_ptrs ,  1 ) ;
 
 #endif
 ;
 
 
 }
 void v_panic(string s) {
 
printf( "V panic: %.*s\n", s.len, s.str ) ;
 
 print_backtrace ( ) ;
 
 exit ( 1 ) ;
 
 
 }
 void println(string s) {
 
 if ( isnil ( s .str ) ) {
 
 v_panic ( tos2("println(NIL)") ) ;
 
 }
 ;
 
 printf ( "%.*s\n" ,  s .len ,  s .str ) ;
 
 
 }
 void eprintln(string s) {
 
 if ( isnil ( s .str ) ) {
 
 v_panic ( tos2("eprintln(NIL)") ) ;
 
 }
 ;
 
 #ifdef __APPLE__
 
 fprintf ( stderr ,  "%.*s\n" ,  s .len ,  s .str ) ;
 
 ;
 
 #else
 
 println ( s ) ;
 
 #endif
 ;
 
 
 }
 void v_print(string s) {
 
 printf ( "%.*s" ,  s .len ,  s .str ) ;
 
 
 }
 byte* v_malloc(int n) {
 
 if ( n < 0 ) {
 
 v_panic ( tos2("malloc(<0)") ) ;
 
 }
 ;
 
byte* ptr= malloc ( n ) ;
 
 if ( isnil ( ptr ) ) {
 
 v_panic ( _STR("malloc(%d) failed", n) ) ;
 
 }
 ;
 
return  ptr ;
 
 
 }
 byte* v_calloc(int n) {
 
 if ( n < 0 ) {
 
 v_panic ( tos2("calloc(<0)") ) ;
 
 }
 ;
 
return  calloc ( n ,  1 ) ;
 
 
 }
 void v_free(void* ptr) {
 
 free ( ptr ) ;
 
 
 }
 void* memdup(void* src, int sz) {
 
byte* mem= v_malloc ( sz ) ;
 
return  memcpy ( mem ,  src ,  sz ) ;
 
 
 }
 string double_str(double d) {
 
byte* buf= v_malloc ( sizeof( double) * 5 + 1 ) ;
 
 sprintf ( buf ,  "%f" ,  d ) ;
 
return  tos ( buf , strlen ( buf ) ) ;
 
 
 }
 string f64_str(f64 d) {
 
byte* buf= v_malloc ( sizeof( double) * 5 + 1 ) ;
 
 sprintf ( buf ,  "%f" ,  d ) ;
 
return  tos ( buf , strlen ( buf ) ) ;
 
 
 }
 string f32_str(f32 d) {
 
byte* buf= v_malloc ( sizeof( double) * 5 + 1 ) ;
 
 sprintf ( buf ,  "%f" ,  d ) ;
 
return  tos ( buf , strlen ( buf ) ) ;
 
 
 }
 string ptr_str(void* ptr) {
 
byte* buf= v_malloc ( sizeof( double) * 5 + 1 ) ;
 
 sprintf ( buf ,  "%p" ,  ptr ) ;
 
return  tos ( buf , strlen ( buf ) ) ;
 
 
 }
 string int_str(int nn) {
 
int n= nn ;
 
 if ( n == 0 ) {
 
return  tos2("0") ;
 
 }
 ;
 
int max= 16 ;
 
byte* buf= v_malloc ( max ) ;
 
int len= 0 ;
 
bool is_neg= 0 ;
 
 if ( n < 0 ) {
 
 n  =  - n ;
 
 is_neg  =  1 ;
 
 }
 ;
 
 while ( n > 0 ) {
 
 
int d= n % 10 ;
 
 buf [/*ptr*/ max - len - 1 ]/*rbyte 1*/  =  d + ((int)( '0' ) ) ;
 
 len ++ ;
 
 n  =  n / 10 ;
 
 }
 ;
 
 if ( is_neg ) {
 
 buf [/*ptr*/ max - len - 1 ]/*rbyte 1*/  =  '-' ;
 
 len ++ ;
 
 }
 ;
 
return  tos ( buf + max - len , len ) ;
 
 
 }
 string u8_str(u8 nn) {
 
u8 n= nn ;
 
 if ( n == ((u8)( 0 ) ) ) {
 
return  tos2("0") ;
 
 }
 ;
 
int max= 5 ;
 
byte* buf= v_malloc ( max ) ;
 
int len= 0 ;
 
bool is_neg= 0 ;
 
 if ( n < ((u8)( 0 ) ) ) {
 
 n  =  - n ;
 
 is_neg  =  1 ;
 
 }
 ;
 
 while ( n > ((u8)( 0 ) ) ) {
 
 
u8 d= n % ((u8)( 10 ) ) ;
 
 buf [/*ptr*/ max - len - 1 ]/*rbyte 1*/  =  d + ((u8)( '0' ) ) ;
 
 len ++ ;
 
 n  =  n / ((u8)( 10 ) ) ;
 
 }
 ;
 
 if ( is_neg ) {
 
 buf [/*ptr*/ max - len - 1 ]/*rbyte 1*/  =  '-' ;
 
 len ++ ;
 
 }
 ;
 
return  tos ( buf + max - len , len ) ;
 
 
 }
 string i64_str(i64 nn) {
 
i64 n= nn ;
 
 if ( n == ((i64)( 0 ) ) ) {
 
return  tos2("0") ;
 
 }
 ;
 
int max= 32 ;
 
byte* buf= v_malloc ( max ) ;
 
int len= 0 ;
 
bool is_neg= 0 ;
 
 if ( n < ((i64)( 0 ) ) ) {
 
 n  =  - n ;
 
 is_neg  =  1 ;
 
 }
 ;
 
 while ( n > ((i64)( 0 ) ) ) {
 
 
int d= ((int)( n % ((i64)( 10 ) ) ) ) ;
 
 buf [/*ptr*/ max - len - 1 ]/*rbyte 1*/  =  d + ((int)( '0' ) ) ;
 
 len ++ ;
 
 n  =  n / ((i64)( 10 ) ) ;
 
 }
 ;
 
 if ( is_neg ) {
 
 buf [/*ptr*/ max - len - 1 ]/*rbyte 1*/  =  '-' ;
 
 len ++ ;
 
 }
 ;
 
return  tos ( buf + max - len , len ) ;
 
 
 }
 string bool_str(bool b) {
 
 if ( b ) {
 
return  tos2("true") ;
 
 }
 ;
 
return  tos2("false") ;
 
 
 }
 string int_hex(int n) {
 
int len= ( n >= 0 ) ? ( int_str( n ) .len + 3 ) : ( 11 ) ;
 
byte* hex= v_malloc ( len ) ;
 
int count= ((int)( sprintf ( hex ,  "0x%x" ,  n ) ) ) ;
 
return  tos ( hex , count ) ;
 
 
 }
 string i64_hex(i64 n) {
 
int len= ( n >= ((i64)( 0 ) ) ) ? ( i64_str( n ) .len + 3 ) : ( 19 ) ;
 
byte* hex= v_malloc ( len ) ;
 
int count= ((int)( sprintf ( hex ,  "0x%x" ,  n ) ) ) ;
 
return  tos ( hex , count ) ;
 
 
 }
 bool array_byte_contains(array_byte a, byte val) {
 
 array_byte tmp29 =  a;
 ;
for (int tmp30 = 0; tmp30 < tmp29 .len; tmp30 ++) {
 byte aa = ((byte *) tmp29.data)[tmp30];
 
 
 if ( aa == val ) {
 
return  1 ;
 
 }
 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 string rune_str(rune c) {
 
int fst_byte= ((int)( c ) )  >>  8 * 3 & 0xff ;
 
int len= utf8_char_len ( fst_byte ) ;
 
string str= (string) { .len =  len , .str =  v_malloc ( len + 1 ) , .hash_cache = 0 , } ;
 
 for (
int i= 0  ;  i < len  ;  i ++ ) { 
 
 
 str .str [/*ptr*/ i ]/*rbyte 1*/  =  ((int)( c ) )  >>  8 * ( 3 - i ) & 0xff ;
 
 }
 ;
 
 str .str[ len ]/*rbyte 1*/  =  '\0' ;
 
return  str ;
 
 
 }
 string byte_str(byte c) {
 
string str= (string) { .len =  1 , .str =  v_malloc ( 2 ) , .hash_cache = 0 , } ;
 
 str .str [/*ptr*/ 0 ]/*rbyte 1*/  =  c ;
 
 str .str [/*ptr*/ 1 ]/*rbyte 1*/  =  '\0' ;
 
return  str ;
 
 
 }
 int utf8_char_len(byte b) {
 
return  ( ( 0xe5000000  >>  ( ( b  >>  3 ) & 0x1e ) ) & 3 ) + 1 ;
 
 
 }
 string utf32_to_str(u32 code) {
 
int icode= ((int)( code ) ) ;
 
byte* buffer= v_malloc ( 5 ) ;
 
 if ( icode <= 127 ) {
 
 buffer [/*ptr*/ 0 ]/*rbyte 1*/  =  icode ;
 
return  tos ( buffer , 1 ) ;
 
 }
 ;
 
 if ( ( icode <= 2047 ) ) {
 
 buffer [/*ptr*/ 0 ]/*rbyte 1*/  =  192 | ( icode  >>  6 ) ;
 
 buffer [/*ptr*/ 1 ]/*rbyte 1*/  =  128 | ( icode & 63 ) ;
 
return  tos ( buffer , 2 ) ;
 
 }
 ;
 
 if ( ( icode <= 65535 ) ) {
 
 buffer [/*ptr*/ 0 ]/*rbyte 1*/  =  224 | ( icode  >>  12 ) ;
 
 buffer [/*ptr*/ 1 ]/*rbyte 1*/  =  128 | ( ( icode  >>  6 ) & 63 ) ;
 
 buffer [/*ptr*/ 2 ]/*rbyte 1*/  =  128 | ( icode & 63 ) ;
 
return  tos ( buffer , 3 ) ;
 
 }
 ;
 
 if ( ( icode <= 1114111 ) ) {
 
 buffer [/*ptr*/ 0 ]/*rbyte 1*/  =  240 | ( icode  >>  18 ) ;
 
 buffer [/*ptr*/ 1 ]/*rbyte 1*/  =  128 | ( ( icode  >>  12 ) & 63 ) ;
 
 buffer [/*ptr*/ 2 ]/*rbyte 1*/  =  128 | ( ( icode  >>  6 ) & 63 ) ;
 
 buffer [/*ptr*/ 3 ]/*rbyte 1*/  =  128 | ( icode & 63 ) ;
 
return  tos ( buffer , 4 ) ;
 
 }
 ;
 
return  tos2("") ;
 
 
 }
 string utf32_to_str_no_malloc(u32 code, void* buf) {
 
int icode= ((int)( code ) ) ;
 
byteptr buffer= ((byteptr)( buf ) ) ;
 
 if ( icode <= 127 ) {
 
 buffer [/*ptr*/ 0 ]/*rbyteptr 1*/  =  icode ;
 
return  tos (& /*11 EXP:"byte*" GOT:"byteptr" */ buffer , 1 ) ;
 
 }
 ;
 
 if ( ( icode <= 2047 ) ) {
 
 buffer [/*ptr*/ 0 ]/*rbyteptr 1*/  =  192 | ( icode  >>  6 ) ;
 
 buffer [/*ptr*/ 1 ]/*rbyteptr 1*/  =  128 | ( icode & 63 ) ;
 
return  tos (& /*11 EXP:"byte*" GOT:"byteptr" */ buffer , 2 ) ;
 
 }
 ;
 
 if ( ( icode <= 65535 ) ) {
 
 buffer [/*ptr*/ 0 ]/*rbyteptr 1*/  =  224 | ( icode  >>  12 ) ;
 
 buffer [/*ptr*/ 1 ]/*rbyteptr 1*/  =  128 | ( ( icode  >>  6 ) & 63 ) ;
 
 buffer [/*ptr*/ 2 ]/*rbyteptr 1*/  =  128 | ( icode & 63 ) ;
 
return  tos (& /*11 EXP:"byte*" GOT:"byteptr" */ buffer , 3 ) ;
 
 }
 ;
 
 if ( ( icode <= 1114111 ) ) {
 
 buffer [/*ptr*/ 0 ]/*rbyteptr 1*/  =  240 | ( icode  >>  18 ) ;
 
 buffer [/*ptr*/ 1 ]/*rbyteptr 1*/  =  128 | ( ( icode  >>  12 ) & 63 ) ;
 
 buffer [/*ptr*/ 2 ]/*rbyteptr 1*/  =  128 | ( ( icode  >>  6 ) & 63 ) ;
 
 buffer [/*ptr*/ 3 ]/*rbyteptr 1*/  =  128 | ( icode & 63 ) ;
 
return  tos (& /*11 EXP:"byte*" GOT:"byteptr" */ buffer , 4 ) ;
 
 }
 ;
 
return  tos2("") ;
 
 
 }
 int string_utf32_code(string _rune) {
 
 if ( _rune .len == 0 ) {
 
return  0 ;
 
 }
 ;
 
 if ( _rune .len == 1 ) {
 
return  ((int)( _rune .str[ 0 ]/*rbyte 0*/ ) ) ;
 
 }
 ;
 
byte b= ((byte)( ((int)( _rune .str[ 0 ]/*rbyte 0*/ ) ) ) ) ;
 
 b  =  b  <<  _rune .len ;
 
int res= ((int)( b ) ) ;
 
int shift= 6 - _rune .len ;
 
 for (
int i= 1  ;  i < _rune .len  ;  i ++ ) { 
 
 
int c= ((int)( _rune .str[ i ]/*rbyte 0*/ ) ) ;
 
 res  =  res  <<  shift ;
 
 res  |=  c & 63 ;
 
 shift  =  6 ;
 
 }
 ;
 
return  res ;
 
 
 }
 map new_map(int cap, int elm_size) {
 
map res= (map) { .element_size =  elm_size , .root =  0 , ._keys = new_array(0, 1, sizeof(string)) , .key_i = 0 , .size = 0 } ;
 
return  res ;
 
 
 }
 Node* new_node(string key, void* val, int element_size) {
 
Node* new_e= ALLOC_INIT(Node, { .key =  key , .val =  v_malloc ( element_size ) , .left =  0 , .right =  0 } ) ;
 
 memcpy ( new_e ->val ,  val ,  element_size ) ;
 
return  new_e ;
 
 
 }
 void map_insert(map* m, Node* n, string key, void* val) {
 
 if (string_eq( n ->key , key ) ) {
 
 memcpy ( n ->val ,  val ,  m ->element_size ) ;
 
 return ;
 
 }
 ;
 
 if (string_gt( n ->key , key ) ) {
 
 if ( isnil ( n ->left ) ) {
 
 n ->left  =  new_node ( key , val , m ->element_size ) ;
 
 m ->size ++ ;
 
 }
  else { 
 
 map_insert( m , n ->left , key , val ) ;
 
 }
 ;
 
 return ;
 
 }
 ;
 
 if ( isnil ( n ->right ) ) {
 
 n ->right  =  new_node ( key , val , m ->element_size ) ;
 
 m ->size ++ ;
 
 }
  else { 
 
 map_insert( m , n ->right , key , val ) ;
 
 }
 ;
 
 
 }
 bool Node_find(Node* n, string key, void* out, int element_size) {
 
 if (string_eq( n ->key , key ) ) {
 
 memcpy ( out ,  n ->val ,  element_size ) ;
 
return  1 ;
 
 }
  else  if (string_gt( n ->key , key ) ) {
 
 if ( isnil ( n ->left ) ) {
 
return  0 ;
 
 }
  else { 
 
return  Node_find(& /* ? */* n ->left , key , out , element_size ) ;
 
 }
 ;
 
 }
  else { 
 
 if ( isnil ( n ->right ) ) {
 
return  0 ;
 
 }
  else { 
 
return  Node_find(& /* ? */* n ->right , key , out , element_size ) ;
 
 }
 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 bool Node_find2(Node* n, string key, int element_size) {
 
 if (string_eq( n ->key , key ) ) {
 
return  1 ;
 
 }
  else  if (string_gt( n ->key , key ) ) {
 
 if ( isnil ( n ->left ) ) {
 
return  0 ;
 
 }
  else { 
 
return  Node_find2(& /* ? */* n ->left , key , element_size ) ;
 
 }
 ;
 
 }
  else { 
 
 if ( isnil ( n ->right ) ) {
 
return  0 ;
 
 }
  else { 
 
return  Node_find2(& /* ? */* n ->right , key , element_size ) ;
 
 }
 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 void map__set(map* m, string key, void* val) {
 
 if ( isnil ( m ->root ) ) {
 
 m ->root  =  new_node ( key , val , m ->element_size ) ;
 
 m ->size ++ ;
 
 return ;
 
 }
 ;
 
 map_insert( m , m ->root , key , val ) ;
 
 
 }
 void map_preorder_keys(map* m, Node* node) {
  
 string tmp3 =  node ->key; 

array_set(&/*q*/ m ->_keys , m ->key_i , & tmp3) ;
 
 m ->key_i ++ ;
 
 if ( ! isnil ( node ->left ) ) {
 
 map_preorder_keys( m , node ->left ) ;
 
 }
 ;
 
 if ( ! isnil ( node ->right ) ) {
 
 map_preorder_keys( m , node ->right ) ;
 
 }
 ;
 
 
 }
 array_string map_keys(map* m) {
  
 string tmp4 =  tos2(""); 

 m ->_keys  =  array_repeat(&tmp4,  m ->size , sizeof(string) ) ;
 
 m ->key_i  =  0 ;
 
 if ( isnil ( m ->root ) ) {
 
return  m ->_keys ;
 
 }
 ;
 
 map_preorder_keys( m , m ->root ) ;
 
return  m ->_keys ;
 
 
 }
 bool map_get(map m, string key, void* out) {
 
 if ( isnil ( m .root ) ) {
 
return  0 ;
 
 }
 ;
 
return  Node_find(& /* ? */* m .root , key , out , m .element_size ) ;
 
 
 }
 bool map_exists(map m, string key) {
 
return  ! isnil ( m .root )  &&  Node_find2(& /* ? */* m .root , key , m .element_size ) ;
 
 
 }
 void v_map_print(map m) {
 
 println ( tos2("<<<<<<<<") ) ;
 
 println ( tos2(">>>>>>>>>>") ) ;
 
 
 }
 void v_map_free(map m) {
 
 
 }
 string map_string_str(map_string m) {
 
 if ( m .size == 0 ) {
 
return  tos2("{}") ;
 
 }
 ;
 
string s= tos2("{\n") ;
 
 s = string_add(s,  tos2("}") ) ;
 
return  s ;
 
 
 }
 Option opt_ok(void* data, int size) {
 
 if ( size > 255 ) {
 
 v_panic ( _STR("option size too big: %d (max is 255)", size) ) ;
 
 }
 ;
 
Option res= (Option) { .ok =  1 , .error = tos("", 0) , } ;
 
 memcpy ( res .data ,  data ,  size ) ;
 
return  res ;
 
 
 }
 Option v_error(string s) {
 
return  (Option) { .error =  s , .ok = 0 } ;
 
 
 }
 f64 math__abs(f64 a) {
 
 if ( a < 0 ) {
 
return  - a ;
 
 }
 ;
 
return  a ;
 
 
 }
 f64 math__acos(f64 a) {
 
return  acos ( a ) ;
 
 
 }
 f64 math__asin(f64 a) {
 
return  asin ( a ) ;
 
 
 }
 f64 math__atan(f64 a) {
 
return  atan ( a ) ;
 
 
 }
 f64 math__atan2(f64 a, f64 b) {
 
return  atan2 ( a ,  b ) ;
 
 
 }
 f64 math__cbrt(f64 a) {
 
return  cbrt ( a ) ;
 
 
 }
 int math__ceil(f64 a) {
 
return  ceil ( a ) ;
 
 
 }
 f64 math__cos(f64 a) {
 
return  cos ( a ) ;
 
 
 }
 f64 math__cosh(f64 a) {
 
return  cosh ( a ) ;
 
 
 }
 f64 math__degrees(f64 radians) {
 
return  radians * ( 180.0 / math__Pi ) ;
 
 
 }
 f64 math__exp(f64 a) {
 
return  exp ( a ) ;
 
 
 }
 array_int math__digits(int n, int base) {
 
int sign= 1 ;
 
 if ( n < 0 ) {
 
 sign  =  - 1 ;
 
 n  =  - n ;
 
 }
 ;
 
array_int res=new_array_from_c_array(0, 0, sizeof(int), (int[]) {   }) ;
 
 while ( n != 0 ) {
 
 
_PUSH(& res , ( ( n % base ) * sign ), tmp3, int) ;
 
 n  /=  base ;
 
 }
 ;
 
return  res ;
 
 
 }
 f64 math__erf(f64 a) {
 
return  erf ( a ) ;
 
 
 }
 f64 math__erfc(f64 a) {
 
return  erfc ( a ) ;
 
 
 }
 f64 math__exp2(f64 a) {
 
return  exp2 ( a ) ;
 
 
 }
 int math__recursive_product(int n, int* current_number_ptr) {
 
int m= n / 2 ;
 
 if ( ( m == 0 ) ) {
 
return  * current_number_ptr  +=  2 ;
 
 }
 ;
 
 if ( ( n == 2 ) ) {
 
return  ( * current_number_ptr  +=  2 ) * ( * current_number_ptr  +=  2 ) ;
 
 }
 ;
 
return  math__recursive_product ( ( n - m ) ,& /*11 EXP:"int*" GOT:"int" */ * current_number_ptr ) * math__recursive_product ( m ,& /*11 EXP:"int*" GOT:"int" */ * current_number_ptr ) ;
 
 
 }
 i64 math__factorial(int n) {
 
 if ( n < 0 ) {
 
 v_panic ( tos2("factorial: Cannot find factorial of negative number") ) ;
 
 }
 ;
 
 if ( n < 2 ) {
 
return  ((i64)( 1 ) ) ;
 
 }
 ;
 
int r= 1 ;
 
int p= 1 ;
 
int current_number= 1 ;
 
int h= 0 ;
 
int shift= 0 ;
 
int high= 1 ;
 
int len= high ;
 
int log2n= ((int)( math__floor ( math__log2 ( n ) ) ) ) ;
 
 for (
  ;  h != n  ;  ) { 
 
 
 shift  +=  h ;
 
 h  =  n  >>  log2n ;
 
 log2n  -=  1 ;
 
 len  =  high ;
 
 high  =  ( h - 1 ) | 1 ;
 
 len  =  ( high - len ) / 2 ;
 
 if ( ( len > 0 ) ) {
 
 p  *=  math__recursive_product ( len , & /*vvar*/  current_number ) ;
 
 r  *=  p ;
 
 }
 ;
 
 }
 ;
 
return  ((i64)( ( r  <<  shift ) ) ) ;
 
 
 }
 f64 math__floor(f64 a) {
 
return  floor ( a ) ;
 
 
 }
 f64 math__fmod(f64 a, f64 b) {
 
return  fmod ( a ,  b ) ;
 
 
 }
 f64 math__gamma(f64 a) {
 
return  tgamma ( a ) ;
 
 
 }
 i64 math__gcd(i64 a, i64 b) {
 
 if ( a < 0 ) {
 
 a  =  - a ;
 
 }
 ;
 
 if ( b < 0 ) {
 
 b  =  - b ;
 
 }
 ;
 
 while ( b != 0 ) {
 
 
 a  %=  b ;
 
 if ( a == 0 ) {
 
return  b ;
 
 }
 ;
 
 b  %=  a ;
 
 }
 ;
 
return  a ;
 
 
 }
 f64 math__hypot(f64 a, f64 b) {
 
return  hypot ( a ,  b ) ;
 
 
 }
 i64 math__lcm(i64 a, i64 b) {
 
 if ( a == 0 ) {
 
return  a ;
 
 }
 ;
 
i64 res= a * ( b / math__gcd ( b , a ) ) ;
 
 if ( res < 0 ) {
 
return  - res ;
 
 }
 ;
 
return  res ;
 
 
 }
 f64 math__log(f64 a) {
 
return  log ( a ) ;
 
 
 }
 f64 math__log2(f64 a) {
 
return  log2 ( a ) ;
 
 
 }
 f64 math__log10(f64 a) {
 
return  log10 ( a ) ;
 
 
 }
 f64 math__log_gamma(f64 a) {
 
return  lgamma ( a ) ;
 
 
 }
 f64 math__log_n(f64 a, f64 b) {
 
return  log ( a ) / log ( b ) ;
 
 
 }
 f64 math__max(f64 a, f64 b) {
 
 if ( a > b ) {
 
return  a ;
 
 }
 ;
 
return  b ;
 
 
 }
 f64 math__min(f64 a, f64 b) {
 
 if ( a < b ) {
 
return  a ;
 
 }
 ;
 
return  b ;
 
 
 }
 f64 math__pow(f64 a, f64 b) {
 
return  pow ( a ,  b ) ;
 
 
 }
 f64 math__radians(f64 degrees) {
 
return  degrees * ( math__Pi / 180.0 ) ;
 
 
 }
 f64 math__round(f64 f) {
 
return  round ( f ) ;
 
 
 }
 f64 math__sin(f64 a) {
 
return  sin ( a ) ;
 
 
 }
 f64 math__sinh(f64 a) {
 
return  sinh ( a ) ;
 
 
 }
 f64 math__sqrt(f64 a) {
 
return  sqrt ( a ) ;
 
 
 }
 f64 math__tan(f64 a) {
 
return  tan ( a ) ;
 
 
 }
 f64 math__tanh(f64 a) {
 
return  tanh ( a ) ;
 
 
 }
 f64 math__trunc(f64 a) {
 
return  trunc ( a ) ;
 
 
 }
 f32 vec3__Vec_hypotenuse(vec3__Vec v) {
 
return  v .i * v .i + v .j * v .j + v .k * v .k ;
 
 
 }
 f32 vec3__Vec_x(vec3__Vec v) {
 
return  v .i ;
 
 
 }
 f32 vec3__Vec_y(vec3__Vec v) {
 
return  v .j ;
 
 
 }
 f32 vec3__Vec_z(vec3__Vec v) {
 
return  v .k ;
 
 
 }
 f32 vec3__Vec_length(vec3__Vec v) {
 
return  math__sqrt ( vec3__Vec_hypotenuse( v ) ) ;
 
 
 }
 string vec3__Vec_str(vec3__Vec v) {
 
return  _STR("(%f, %f, %f)", v .i, v .j, v .k) ;
 
 
 }
 vec3__Vec vec3__Vec_plus(vec3__Vec a, vec3__Vec b) {
 
return  (vec3__Vec) { a .i + b .i , a .j + b .j , a .k + b .k } ;
 
 
 }
 vec3__Vec vec3__Vec_minus(vec3__Vec a, vec3__Vec b) {
 
return  (vec3__Vec) { a .i - b .i , a .j - b .j , a .k - b .k } ;
 
 
 }
 vec3__Vec vec3__Vec_(vec3__Vec a, vec3__Vec b) {
 
return  (vec3__Vec) { a .i * b .i , a .j * b .j , a .k * b .k } ;
 
 
 }
 vec3__Vec vec3__Vec_mul_scalar(vec3__Vec a, f32 t) {
 
return  (vec3__Vec) { a .i * t , a .j * t , a .k * t } ;
 
 
 }
 vec3__Vec vec3__Vec_div_scalar(vec3__Vec a, f32 t) {
 
return  (vec3__Vec) { a .i / t , a .j / t , a .k / t } ;
 
 
 }
 f32 vec3__Vec_dot(vec3__Vec v, vec3__Vec u) {
 
return  ( v .i * u .i ) + ( v .j * u .j ) + ( v .k * u .k ) ;
 
 
 }
 vec3__Vec vec3__Vec_cross(vec3__Vec v, vec3__Vec u) {
 
return  (vec3__Vec) { .i =  v .j * u .k , .j =  v .k * u .i , .k =  v .i * u .j } ;
 
 
 }
 vec3__Vec vec3__Vec_make_unit(vec3__Vec v) {
 
f32 l= vec3__Vec_length( v ) ;
 
return  vec3__Vec_div_scalar( v , l ) ;
 
 
 }
 vec3__RGB vec3__Vec_to_rgb(vec3__Vec v) {
 
return  (vec3__RGB) { ((int)( vec3__Vec_x( v ) ) ) , ((int)( vec3__Vec_y( v ) ) ) , ((int)( vec3__Vec_z( v ) ) ) } ;
 
 
 }
 string vec3__RGB_str(vec3__RGB c) {
 
return  _STR("%d %d %d", c .r, c .g, c .b) ;
 
 
 }
 vec3__RGB vec3__RGB_mul_scalar(vec3__RGB c, f32 k) {
 
return  (vec3__RGB) { ((int)( ((f32)( c .r ) ) * k ) ) , ((int)( ((f32)( c .g ) ) * k ) ) , ((int)( ((f32)( c .b ) ) * k ) ) } ;
 
 
 }
 vec3__Vec vec3__Ray_at(vec3__Ray r, f32 t) {
 
return vec3__Vec_plus( r .a , vec3__Vec_mul_scalar( r .b , t ) ) ;
 
 
 }
 string vec3__Ray_str(vec3__Ray r) {
 
return  tos2("$(r.a) + $(r.b) * t") ;
 
 
 }
 vec3__Vec vec3__Ray_make_unit(vec3__Ray r) {
 
return  vec3__Vec_make_unit( r .b ) ;
 
 
 }
 bool hit_sphere(vec3__Vec centre, f32 radius, vec3__Ray r) {
 
vec3__Vec oc=vec3__Vec_minus( r .a , centre ) ;
 
f32 a= vec3__Vec_dot( r .b , r .b ) ;
 
f32 b= 2.0 * vec3__Vec_dot( oc , r .b ) ;
 
f32 c= vec3__Vec_dot( oc , oc ) - radius * radius ;
 
f32 discriminant= b * b - 4.0 * a * c ;
 
return  ( discriminant > 0.0 ) ;
 
 
 }
 vec3__Vec colour(vec3__Ray r) {
 
 if ( hit_sphere ( (vec3__Vec) { 0 , 0 , - 1 } , 0.5 , r ) ) {
 
return  (vec3__Vec) { 1 , 0 , 0 } ;
 
 }
 ;
 
vec3__Vec uv= vec3__Ray_make_unit( r ) ;
 
f32 ic= 0.5 * ( vec3__Vec_y( uv ) + 1.0 ) ;
 
vec3__Vec a= (vec3__Vec) { 1.0 , 1.0 , 1.0 } ;
 
vec3__Vec b= (vec3__Vec) { 0.5 , 0.7 , 1.0 } ;
 
return vec3__Vec_plus( vec3__Vec_mul_scalar( a , 1.0 - ic ) , vec3__Vec_mul_scalar( b , ic ) ) ;
 
 
 }
 int main(int argc, char** argv) {
 init_consts();
 
int nx= 200 ;
 
int ny= 100 ;
 
 println ( tos2("P3") ) ;
 
printf( "%d %d\n", nx, ny ) ;
 
 println ( tos2("255") ) ;
 
vec3__Vec llc= (vec3__Vec) { - 2 , - 1 , - 1 } ;
 
vec3__Vec hor= (vec3__Vec) { 4 , 0 , 0 } ;
 
vec3__Vec vert= (vec3__Vec) { 0 , 2 , 0 } ;
 
vec3__Vec origin= (vec3__Vec) { 0 , 0 , 0 } ;
 
 for (
f32 j= ((f32)( ny - 1 ) )  ;  j >= 0  ;  j -- ) { 
 
 
 for (
f32 i= ((f32)( 0 ) )  ;  i < nx  ;  i ++ ) { 
 
 
f32 u= i / nx ;
 
f32 v= j / ny ;
 
vec3__Ray r= (vec3__Ray) { origin ,vec3__Vec_plus(vec3__Vec_plus( llc , vec3__Vec_mul_scalar( hor , u ) ) , vec3__Vec_mul_scalar( vert , v ) ) } ;
 
vec3__Vec c= colour ( r ) ;
 
vec3__RGB d= vec3__Vec_to_rgb( vec3__Vec_mul_scalar( c , 255.99 ) ) ;
 
 println (vec3__RGB_str( d ) ) ;
 
 }
 ;
 
 }
 ;
 
 
 }
 void init_consts() { g_str_buf=malloc(1000); math__Log2E =  1.0 / math__Ln2;
math__Log10E =  1.0 / math__Ln10;
math__MaxI8 =  ( 1  <<  7 ) - 1;
math__MinI8 =  - 1  <<  7;
math__MaxI16 =  ( 1  <<  15 ) - 1;
math__MinI16 =  - 1  <<  15;
math__MaxI32 =  ( 1  <<  31 ) - 1;
math__MinI32 =  - 1  <<  31;
math__MaxU8 =  ( 1  <<  8 ) - 1;
math__MaxU16 =  ( 1  <<  16 ) - 1;
math__MaxU32 =  ( 1  <<  32 ) - 1;
math__MaxU64 =  ( 1  <<  64 ) - 1; }
 
string _STR(const char *fmt, ...) {
	va_list argptr;
	va_start(argptr, fmt);
	size_t len = vsnprintf(0, 0, fmt, argptr) + 1;  
	va_end(argptr);
	byte* buf = malloc(len);  
	va_start(argptr, fmt);
	vsprintf(buf, fmt, argptr);
	va_end(argptr);
#ifdef DEBUG_ALLOC 
	puts("_STR:"); 
	puts(buf); 
#endif 
	return tos2(buf);
}

string _STR_TMP(const char *fmt, ...) {
	va_list argptr;
	va_start(argptr, fmt);
	size_t len = vsnprintf(0, 0, fmt, argptr) + 1;  
	va_end(argptr);
	va_start(argptr, fmt);
	vsprintf(g_str_buf, fmt, argptr);
	va_end(argptr);
#ifdef DEBUG_ALLOC 
	//puts("_STR_TMP:"); 
	//puts(g_str_buf); 
#endif 
	return tos2(g_str_buf);
}


