#include <float.h>
#include <math.h>
#include "vector.h"

/* It is dangerous to compare two double numbers using == operator. */
/* Because double always has an erro. */
/* In many cases, it is appropriate that you compare the difference with DBL_EPSILON. */
gboolean
double_eq (double a, double b) {
/*  return fabs (a - b) < DBL_EPSILON; */
  return fabs (a - b) < 0.000000001;
}

vector3 *
vector3_new (double x, double y, double z) {
  vector3 *v;

  v = g_new (vector3, 1);
  v->x = x;
  v->y = y;
  v->z = z;
  return v;
}

void
vector3_free (vector3 *v) {
  g_free(v);
}

void
vector3_assign (vector3 *v, double x, double y, double z) {
  v->x = x;
  v->y = y;
  v->z = z;
}

void
vector3_copy (vector3 *dst, vector3 *src) {
  dst->x = src->x;
  dst->y = src->y;
  dst->z = src->z;
}

gboolean
vector3_eq0 (vector3 *v, double x, double y, double z) {
  return double_eq (v->x, x) && double_eq (v->y, y) && double_eq (v->z, z);
}

gboolean
vector3_eq (vector3 *v1, vector3 *v2) {
  return double_eq (v1->x, v2->x) && double_eq (v1->y, v2->y) && double_eq (v1->z, v2->z);
}

double
vector3_norm (vector3 *v) {
  return sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
}

vector3 *
vector3_scalar_multiple_n (double k, vector3 *v) {
  return vector3_new (k*v->x, k*v->y, k*v->z);
}

vector3 *
vector3_scalar_multiple_c (double k, vector3 *v1, vector3 *v2) {
  v2->x = k*v1->x;
  v2->y = k*v1->y;
  v2->z = k*v1->z;
}

void
vector3_scalar_multiple_a (double k, vector3 *v) {
  v->x = k*v->x;
  v->y = k*v->y;
  v->z = k*v->z;
}

vector3 *
vector3_add_n (vector3 *v1, vector3 *v2) {
  return vector3_new (v1->x+v2->x, v1->y+v2->y, v1->z+v2->z);
}

void
vector3_add_c (vector3 *v1, vector3 *v2, vector3 *v3) {
  v3->x = v1->x + v2->x;
  v3->y = v1->y + v2->y;
  v3->z = v1->z + v2->z;
}

void
vector3_add_a (vector3 *v1, vector3 *v2) {
  v1->x = v1->x + v2->x;
  v1->y = v1->y + v2->y;
  v1->z = v1->z + v2->z;
}

vector3 *
vector3_sub_n (vector3 *v1, vector3 *v2) {
  return vector3_new (v1->x-v2->x, v1->y-v2->y, v1->z-v2->z);
}

void
vector3_sub_c (vector3 *v1, vector3 *v2, vector3 *v3) {
  v3->x = v1->x - v2->x;
  v3->y = v1->y - v2->y;
  v3->z = v1->z - v2->z;
}

void
vector3_sub_a (vector3 *v1, vector3 *v2) {
  v1->x = v1->x - v2->x;
  v1->y = v1->y - v2->y;
  v1->z = v1->z - v2->z;
}

double
vector3_inner_product (vector3 *v1, vector3 *v2) {
  return v1->x*v2->x + v1->y*v2->y + v1->z*v2->z;
}

vector3 *
vector3_cross_product_n (vector3 *v1, vector3 *v2) {
  return vector3_new (
    v1->y*v2->z - v1->z*v2->y,
    v1->z*v2->x - v1->x*v2->z,
    v1->x*v2->y - v1->y*v2->x );
}

void
vector3_cross_product_c (vector3 *v1, vector3 *v2, vector3 *v3){
  v3->x = v1->y*v2->z - v1->z*v2->y;
  v3->y = v1->z*v2->x - v1->x*v2->z;
  v3->z = v1->x*v2->y - v1->y*v2->x;
}

void
vector3_cross_product_a (vector3 *v1, vector3 *v2) {
  double x,y,z;

  x = v1->y*v2->z - v1->z*v2->y;
  y = v1->z*v2->x - v1->x*v2->z;
  z = v1->x*v2->y - v1->y*v2->x;
  v1->x = x;
  v1->y = y;
  v1->z = z;
}

/* hat operator makes a unit vector. */
vector3 *
vector3_hat_n (vector3 *v) {
  double norm = vector3_norm (v);

  return vector3_new (v->x/norm, v->y/norm, v->z/norm);
}

void
vector3_hat_a (vector3 *v) {
  double norm = vector3_norm (v);

  v->x = v->x/norm;
  v->y = v->y/norm;
  v->z = v->z/norm;
}

void
vector3_hat_c (vector3 *v1, vector3 *v2) {
  double norm = vector3_norm (v1);

  v2->x = v1->x/norm;
  v2->y = v1->y/norm;
  v2->z = v1->z/norm;
}

vector3 *
vector3_projection_n (vector3 *v1, vector3 *v2) {
  double inner_product_12, inner_product_22;

  inner_product_12 = vector3_inner_product (v1, v2);
  inner_product_22 = vector3_inner_product (v2, v2);
  return vector3_scalar_multiple_n (inner_product_12 / inner_product_22, v2);
}

void
vector3_projection_c (vector3 *v1, vector3 *v2, vector3 *v3) {
  double inner_product_12, inner_product_22;

  inner_product_12 = vector3_inner_product (v1, v2);
  inner_product_22 = vector3_inner_product (v2, v2);
  vector3_scalar_multiple_c (inner_product_12 / inner_product_22, v2, v3);
}

void
vector3_projection_a (vector3 *v1, vector3 *v2) {
  double inner_product_12, inner_product_22;

  inner_product_12 = vector3_inner_product (v1, v2);
  inner_product_22 = vector3_inner_product (v2, v2);
  vector3_scalar_multiple_c (inner_product_12 / inner_product_22, v2, v1);
}

vector3 *
vector3_rejection_n (vector3 *v1, vector3 *v2) {
  vector3 v;

  vector3_projection_c (v1, v2, &v);
  return vector3_sub_n (v1, &v);  
}

void
vector3_rejection_c (vector3 *v1, vector3 *v2, vector3 *v3) {
  vector3 v;

  vector3_projection_c (v1, v2, &v);
  vector3_sub_c (v1, &v, v3);  
}

void
vector3_rejection_a (vector3 *v1, vector3 *v2) {
  vector3 v;

  vector3_projection_c (v1, v2, &v);
  vector3_sub_a (v1, &v);  
}

/* **_x_* => Rotation around the x axis. */
/* Angles from y axis to z axis are positive. */
/* The angles are measured with digrees. */

vector3 *
vector3_rot_x_n (double theta, vector3 *v) {
  theta *= M_PI/180;
  return vector3_new (v->x, v->y*cos(theta) - v->z*sin(theta), v->y*sin(theta) + v->z*cos(theta));
}

void
vector3_rot_x_c (double theta, vector3 *v1, vector3 *v2) {
  theta *= M_PI/180;
  v2->x = v1->x;
  v2->y = v1->y*cos(theta) - v1->z*sin(theta);
  v2->z = v1->y*sin(theta) + v1->z*cos(theta);
}

void
vector3_rot_x_a (double theta, vector3 *v) {
  double y, z;

  theta *= M_PI/180;
  y = v->y;
  z = v->z;
  v->y = y*cos(theta) - z*sin(theta);
  v->z = y*sin(theta) + z*cos(theta);
}

/* Rotation around the y axis. */
vector3 *
vector3_rot_y_n (double theta, vector3 *v) {
  theta *= M_PI/180;
  return vector3_new (v->z*sin(theta) + v->x*cos(theta), v->y, v->z*cos(theta) - v->x*sin(theta));
}

void
vector3_rot_y_c (double theta, vector3 *v1, vector3 *v2) {
  theta *= M_PI/180;
  v2->x = v1->z*sin(theta) + v1->x*cos(theta);
  v2->y = v1->y;
  v2->z = v1->z*cos(theta) - v1->x*sin(theta);
}

void
vector3_rot_y_a (double theta, vector3 *v) {
  double z, x;

  theta *= M_PI/180;
  z = v->z;
  x = v->x;
  v->z = z*cos(theta) - x*sin(theta);
  v->x = z*sin(theta) + x*cos(theta);
}

/* Rotation around the z axis. */
vector3 *
vector3_rot_z_n (double theta, vector3 *v) {
  theta *= M_PI/180;
  return vector3_new (v->x*cos(theta) - v->y*sin(theta), v->x*sin(theta) + v->y*cos(theta), v->z);
}

void
vector3_rot_z_c (double theta, vector3 *v1, vector3 *v2) {
  theta *= M_PI/180;
  v2->x = v1->x*cos(theta) - v1->y*sin(theta);
  v2->y = v1->x*sin(theta) + v1->y*cos(theta);
  v2->z = v1->z;
}

void
vector3_rot_z_a (double theta, vector3 *v) {
  double x, y;

  theta *= M_PI/180;
  x = v->x;
  y = v->y;
  v->x = x*cos(theta) - y*sin(theta);
  v->y = x*sin(theta) + y*cos(theta);
}


matrix3 *
matrix3_new (double a11, double a12, double a13,
  double a21, double a22, double a23,
  double a31, double a32, double a33 ) {

  matrix3 *m;

  m = g_new (matrix3, 1);
  m->a11 = a11;
  m->a12 = a12;
  m->a13 = a13;
  m->a21 = a21;
  m->a22 = a22;
  m->a23 = a23;
  m->a31 = a31;
  m->a32 = a32;
  m->a33 = a33;
  return m;
}

void
matrix3_free (matrix3 *m) {
  g_free(m);
}

void
matrix3_assign (matrix3 *m, double a11, double a12, double a13,
  double a21, double a22, double a23,
  double a31, double a32, double a33 ) {
  m->a11 = a11;
  m->a12 = a12;
  m->a13 = a13;
  m->a21 = a21;
  m->a22 = a22;
  m->a23 = a23;
  m->a31 = a31;
  m->a32 = a32;
  m->a33 = a33;
}

void
matrix3_copy (matrix3 *dst, matrix3 *src) {
  dst->a11 = src->a11;
  dst->a12 = src->a12;
  dst->a13 = src->a13;
  dst->a21 = src->a21;
  dst->a22 = src->a22;
  dst->a23 = src->a23;
  dst->a31 = src->a31;
  dst->a32 = src->a32;
  dst->a33 = src->a33;
}

gboolean
matrix3_eq0 (matrix3 *m, double a11, double a12, double a13,
  double a21, double a22, double a23,
  double a31, double a32, double a33 ){
  if (! double_eq (m->a11, a11))
    return FALSE;
  if (! double_eq (m->a12, a12))
    return FALSE;
  if (! double_eq (m->a13, a13))
    return FALSE;
  if (! double_eq (m->a21, a21))
    return FALSE;
  if (! double_eq (m->a22, a22))
    return FALSE;
  if (! double_eq (m->a23, a23))
    return FALSE;
  if (! double_eq (m->a31, a31))
    return FALSE;
  if (! double_eq (m->a32, a32))
    return FALSE;
  if (! double_eq (m->a33, a33))
    return FALSE;
  return TRUE;
}

gboolean
matrix3_eq (matrix3 *m1, matrix3 *m2) {
  if (! double_eq (m1->a11, m2->a11))
    return FALSE;
  if (! double_eq (m1->a12, m2->a12))
    return FALSE;
  if (! double_eq (m1->a13, m2->a13))
    return FALSE;
  if (! double_eq (m1->a21, m2->a21))
    return FALSE;
  if (! double_eq (m1->a22, m2->a22))
    return FALSE;
  if (! double_eq (m1->a23, m2->a23))
    return FALSE;
  if (! double_eq (m1->a31, m2->a31))
    return FALSE;
  if (! double_eq (m1->a32, m2->a32))
    return FALSE;
  if (! double_eq (m1->a33, m2->a33))
    return FALSE;
  return TRUE;
}

matrix3 *
matrix3_scalar_multiple_n (double k, matrix3 *m) {
  return matrix3_new (k*m->a11, k*m->a12, k*m->a13,
            k*m->a21, k*m->a22, k*m->a23,
            k*m->a31, k*m->a32, k*m->a33);
}

void
matrix3_scalar_multiple_c (double k, matrix3 *m1, matrix3 *m2) {
  m2->a11 = k*m1->a11;
  m2->a12 = k*m1->a12;
  m2->a13 = k*m1->a13;
  m2->a21 = k*m1->a21;
  m2->a22 = k*m1->a22;
  m2->a23 = k*m1->a23;
  m2->a31 = k*m1->a31;
  m2->a32 = k*m1->a32;
  m2->a33 = k*m1->a33;
}

void
matrix3_scalar_multiple_a (double k, matrix3 *m) {
  m->a11 = k*m->a11;
  m->a12 = k*m->a12;
  m->a13 = k*m->a13;
  m->a21 = k*m->a21;
  m->a22 = k*m->a22;
  m->a23 = k*m->a23;
  m->a31 = k*m->a31;
  m->a32 = k*m->a32;
  m->a33 = k*m->a33;
}

matrix3 *
matrix3_add_n (matrix3 *m1, matrix3 *m2) {
  return matrix3_new (m1->a11+m2->a11, m1->a12+m2->a12, m1->a13+m2->a13,
            m1->a21+m2->a21, m1->a22+m2->a22, m1->a23+m2->a23,
            m1->a31+m2->a31, m1->a32+m2->a32, m1->a33+m2->a33);
}

void
matrix3_add_c (matrix3 *m1, matrix3 *m2, matrix3 *m3) {
  m3->a11 = m1->a11 + m2->a11;
  m3->a12 = m1->a12 + m2->a12;
  m3->a13 = m1->a13 + m2->a13;
  m3->a21 = m1->a21 + m2->a21;
  m3->a22 = m1->a22 + m2->a22;
  m3->a23 = m1->a23 + m2->a23;
  m3->a31 = m1->a31 + m2->a31;
  m3->a32 = m1->a32 + m2->a32;
  m3->a33 = m1->a33 + m2->a33;
}

void
matrix3_add_a (matrix3 *m1, matrix3 *m2) {
  m1->a11 = m1->a11 + m2->a11;
  m1->a12 = m1->a12 + m2->a12;
  m1->a13 = m1->a13 + m2->a13;
  m1->a21 = m1->a21 + m2->a21;
  m1->a22 = m1->a22 + m2->a22;
  m1->a23 = m1->a23 + m2->a23;
  m1->a31 = m1->a31 + m2->a31;
  m1->a32 = m1->a32 + m2->a32;
  m1->a33 = m1->a33 + m2->a33;
}

matrix3 *
matrix3_sub_n (matrix3 *m1, matrix3 *m2) {
  return matrix3_new (m1->a11-m2->a11, m1->a12-m2->a12, m1->a13-m2->a13,
            m1->a21-m2->a21, m1->a22-m2->a22, m1->a23-m2->a23,
            m1->a31-m2->a31, m1->a32-m2->a32, m1->a33-m2->a33);
}

void
matrix3_sub_c (matrix3 *m1, matrix3 *m2, matrix3 *m3) {
  m3->a11 = m1->a11 - m2->a11;
  m3->a12 = m1->a12 - m2->a12;
  m3->a13 = m1->a13 - m2->a13;
  m3->a21 = m1->a21 - m2->a21;
  m3->a22 = m1->a22 - m2->a22;
  m3->a23 = m1->a23 - m2->a23;
  m3->a31 = m1->a31 - m2->a31;
  m3->a32 = m1->a32 - m2->a32;
  m3->a33 = m1->a33 - m2->a33;
}

void
matrix3_sub_a (matrix3 *m1, matrix3 *m2) {
  m1->a11 = m1->a11 - m2->a11;
  m1->a12 = m1->a12 - m2->a12;
  m1->a13 = m1->a13 - m2->a13;
  m1->a21 = m1->a21 - m2->a21;
  m1->a22 = m1->a22 - m2->a22;
  m1->a23 = m1->a23 - m2->a23;
  m1->a31 = m1->a31 - m2->a31;
  m1->a32 = m1->a32 - m2->a32;
  m1->a33 = m1->a33 - m2->a33;
}

matrix3 *
matrix3_mul_n (matrix3 *m1, matrix3 *m2) {
  return matrix3_new (
            m1->a11*m2->a11 + m1->a12*m2->a21 + m1->a13*m2->a31,
            m1->a11*m2->a12 + m1->a12*m2->a22 + m1->a13*m2->a32,
            m1->a11*m2->a13 + m1->a12*m2->a23 + m1->a13*m2->a33,
            m1->a21*m2->a11 + m1->a22*m2->a21 + m1->a23*m2->a31,
            m1->a21*m2->a12 + m1->a22*m2->a22 + m1->a23*m2->a32,
            m1->a21*m2->a13 + m1->a22*m2->a23 + m1->a23*m2->a33,
            m1->a31*m2->a11 + m1->a32*m2->a21 + m1->a33*m2->a31,
            m1->a31*m2->a12 + m1->a32*m2->a22 + m1->a33*m2->a32,
            m1->a31*m2->a13 + m1->a32*m2->a23 + m1->a33*m2->a33
  );
}

void
matrix3_mul_c (matrix3 *m1, matrix3 *m2, matrix3 *m3) {
  m3->a11 = m1->a11*m2->a11 + m1->a12*m2->a21 + m1->a13*m2->a31;
  m3->a12 = m1->a11*m2->a12 + m1->a12*m2->a22 + m1->a13*m2->a32;
  m3->a13 = m1->a11*m2->a13 + m1->a12*m2->a23 + m1->a13*m2->a33;
  m3->a21 = m1->a21*m2->a11 + m1->a22*m2->a21 + m1->a23*m2->a31;
  m3->a22 = m1->a21*m2->a12 + m1->a22*m2->a22 + m1->a23*m2->a32;
  m3->a23 = m1->a21*m2->a13 + m1->a22*m2->a23 + m1->a23*m2->a33;
  m3->a31 = m1->a31*m2->a11 + m1->a32*m2->a21 + m1->a33*m2->a31;
  m3->a32 = m1->a31*m2->a12 + m1->a32*m2->a22 + m1->a33*m2->a32;
  m3->a33 = m1->a31*m2->a13 + m1->a32*m2->a23 + m1->a33*m2->a33;
}

void
matrix3_mul_a (matrix3 *m1, matrix3 *m2) {
  matrix3 m;

  matrix3_mul_c (m1, m2, &m);
  matrix3_copy (m1, &m);
}


vector3 *
matrix3_vector3_mul_n (matrix3 *m, vector3 *v) {
  return vector3_new (
            m->a11*v->x + m->a12*v->y + m->a13*v->z,
            m->a21*v->x + m->a22*v->y + m->a23*v->z,
            m->a31*v->x + m->a32*v->y + m->a33*v->z
  );
}

void
matrix3_vector3_mul_c (matrix3 *m, vector3 *v1, vector3 *v2) {
  v2->x = m->a11*v1->x + m->a12*v1->y + m->a13*v1->z;
  v2->y = m->a21*v1->x + m->a22*v1->y + m->a23*v1->z;
  v2->z = m->a31*v1->x + m->a32*v1->y + m->a33*v1->z;
}

void
matrix3_vector3_mul_a (matrix3 *m, vector3 *v) {
  vector3 v2;

  matrix3_vector3_mul_c (m, v, &v2);
  vector3_copy (v, &v2);
}

double
matrix3_det (matrix3 *m) {
  return m->a11*m->a22*m->a33 + m->a12*m->a23*m->a31 + m->a13*m->a21*m->a32
         - m->a11*m->a23*m->a32 - m->a12*m->a21*m->a33 - m->a13*m->a22*m->a31;
}

/* show information for debugging */

void
print_v3 (vector3 *v) {
  g_print ("(%f, %f, %f)\n", v->x, v->y, v->z);
}

void
print_m3 (matrix3 *m) {
  g_print ("(%f, %f, %f)\n", m->a11, m->a12, m->a13);
  g_print ("(%f, %f, %f)\n", m->a21, m->a22, m->a23);
  g_print ("(%f, %f, %f)\n", m->a31, m->a32, m->a33);
}

