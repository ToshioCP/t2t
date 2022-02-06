#ifndef __T2T_VECTOR_H__
#define __T2T_VECTOR_H__


#include <gtk/gtk.h>

gboolean
double_eq (double a, double b);

typedef struct _vector3 {
  double x;
  double y;
  double z;
} vector3;

vector3 *
vector3_new (double x, double y, double z);

void
vector3_free (vector3 *v);

void
vector3_assign (vector3 *v, double x, double y, double z);

void
vector3_copy (vector3 *dst, vector3 *src);

gboolean
vector3_eq0 (vector3 *v, double x, double y, double z);

gboolean
vector3_eq (vector3 *v1, vector3 *v2);

double
vector3_norm (vector3 *v);

vector3 *
vector3_scalar_multiple_n (double k, vector3 *v);

vector3 *
vector3_scalar_multiple_c (double k, vector3 *v1, vector3 *v2);

void
vector3_scalar_multiple_a (double k, vector3 *v);

vector3 *
vector3_add_n (vector3 *v1, vector3 *v2);

void
vector3_add_c (vector3 *v1, vector3 *v2, vector3 *v3);

void
vector3_add_a (vector3 *v1, vector3 *v2);

vector3 *
vector3_sub_n (vector3 *v1, vector3 *v2);

void
vector3_sub_c (vector3 *v1, vector3 *v2, vector3 *v3);

void
vector3_sub_a (vector3 *v1, vector3 *v2);

double
vector3_inner_product (vector3 *v1, vector3 *v2);

vector3 *
vector3_cross_product_n (vector3 *v1, vector3 *v2);

void
vector3_cross_product_c (vector3 *v1, vector3 *v2, vector3 *v3);

void
vector3_cross_product_a (vector3 *v1, vector3 *v2);

/* hat operator makes a unit vector. */
vector3 *
vector3_hat_n (vector3 *v);

void
vector3_hat_a (vector3 *v);

void
vector3_hat_c (vector3 *v1, vector3 *v2);

vector3 *
vector3_projection_n (vector3 *v1, vector3 *v2);

void
vector3_projection_c (vector3 *v1, vector3 *v2, vector3 *v3);

void
vector3_projection_a (vector3 *v1, vector3 *v2);

vector3 *
vector3_rejection_n (vector3 *v1, vector3 *v2);

void
vector3_rejection_c (vector3 *v1, vector3 *v2, vector3 *v3);

void
vector3_rejection_a (vector3 *v1, vector3 *v2);

/* **_x_* => Rotation around the x axis. */
/* Angles from y axis to z axis are positive. */
/* The angles are measured with digrees. */

vector3 *
vector3_rot_x_n (double theta, vector3 *v);

void
vector3_rot_x_c (double theta, vector3 *v1, vector3 *v2);

void
vector3_rot_x_a (double theta, vector3 *v);

/* Rotation around the y axis. */
vector3 *
vector3_rot_y_n (double theta, vector3 *v);

void
vector3_rot_y_c (double theta, vector3 *v1, vector3 *v2);

void
vector3_rot_y_a (double theta, vector3 *v);

/* Rotation around the z axis. */
vector3 *
vector3_rot_z_n (double theta, vector3 *v);

void
vector3_rot_z_c (double theta, vector3 *v1, vector3 *v2);

void
vector3_rot_z_a (double theta, vector3 *v);


typedef struct _matrix3 {
  double a11;
  double a12;
  double a13;
  double a21;
  double a22;
  double a23;
  double a31;
  double a32;
  double a33;
} matrix3;

matrix3 *
matrix3_new (double a11, double a12, double a13,
  double a21, double a22, double a23,
  double a31, double a32, double a33 );

void
matrix3_free (matrix3 *m);

void
matrix3_assign (matrix3 *m, double a11, double a12, double a13,
  double a21, double a22, double a23,
  double a31, double a32, double a33 );

void
matrix3_copy (matrix3 *dst, matrix3 *src);

gboolean
matrix3_eq0 (matrix3 *m, double a11, double a12, double a13,
  double a21, double a22, double a23,
  double a31, double a32, double a33 );

gboolean
matrix3_eq (matrix3 *m1, matrix3 *m2);
 
matrix3 *
matrix3_scalar_multiple_n (double k, matrix3 *m);

void
matrix3_scalar_multiple_c (double k, matrix3 *m1, matrix3 *m2);

void
matrix3_scalar_multiple_a (double k, matrix3 *m);

matrix3 *
matrix3_add_n (matrix3 *m1, matrix3 *m2);

void
matrix3_add_c (matrix3 *m1, matrix3 *m2, matrix3 *m3);

void
matrix3_add_a (matrix3 *m1, matrix3 *m2);

matrix3 *
matrix3_sub_n (matrix3 *m1, matrix3 *m2);

void
matrix3_sub_c (matrix3 *m1, matrix3 *m2, matrix3 *m3);

void
matrix3_sub_a (matrix3 *m1, matrix3 *m2);

matrix3 *
matrix3_mul_n (matrix3 *m1, matrix3 *m2);

void
matrix3_mul_c (matrix3 *m1, matrix3 *m2, matrix3 *m3);

void
matrix3_mul_a (matrix3 *m1, matrix3 *m2);

vector3 *
matrix3_vector3_mul_n (matrix3 *m, vector3 *v);

void
matrix3_vector3_mul_c (matrix3 *m, vector3 *v1, vector3 *v2);

void
matrix3_vector3_mul_a (matrix3 *m, vector3 *v);

double
matrix3_det (matrix3 *m);

/* for debugging */
void
print_v3 (vector3 *v);

void
print_m3 (matrix3 *m);

#endif /* __T2T_VECTOR_H__ */
