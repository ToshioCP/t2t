#include <math.h>
#include "trans.h"
#include "vector.h"


/* transformation */

#include <gtk/gtk.h>
#include <math.h>

/* get the orthogonal matrix from the vector t */

void
init_matrix (vector3 *t, matrix3 *m) {
  /* m: inverse (or transposed) matrix of the change-of-basis matrix */
  vector3 c, i, j, k;

  /* c is the third vector of the basis on the ground. */
  /* c = (0,0,1) */
  vector3_assign (&c, 0.0, 0.0, 1.0);

  /* k = -hat(t) = -(1/|t|)t */
  vector3_hat_c (t, &k);
  vector3_scalar_multiple_a (-1.0, &k);

  /* j = hat(rejection(c,t)) */
  vector3_rejection_c (&c, t, &j);
  vector3_hat_a (&c);

  /* i = - j x k */
  vector3_cross_product_c (&j, &k, &i);
  vector3_scalar_multiple_a (-1.0, &i);

  matrix3_assign (m,
   i.x, i.y, i.z,
   j.x, j.y, j.z,
   k.x, k.y, k.z
  );
}

/* move drone */
/* move t */
/*
vector3 *
up_drone (vector3 *v, double h) {
  v->z += h;
}

vector3 *
rot_drone (vector3 *v, double theta) {
  double x2, y2;

  x2 = v->x*cos(theta)-v->y*sin(theta);
  y2 = v->x*sin(theta)+v->y*cos(theta);
  v->x = x2;
  v->y = y2;
}

vector3 *
zoom_in (vector3 *v, double d) {
  double r;

  r = d / sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
  v->x *= r;
  v->y *= r;
  v->z *= r;
}
*/
/* move camera */
/* move m */
/*
matrix3 *
up_camera (matrix3 *m, double theta) {
  double b11,b12,b13,b21,b22,b23,b31,b32,b33;

  b11 = m->a11;
  b12 = m->a12*cos(theta) + m->a13*sin(theta);
  b13 = -m->a12*sin(theta) + m->a13*cos(theta);
  b21 = m->a21;
  b22 = m->a22*cos(theta) + m->a23*sin(theta);
  b23 = -m->a22*sin(theta) + m->a23*cos(theta);
  b31 ~ m->a31;
  b32 = m->a32*cos(theta) + m->a33*sin(theta);
  b33 = -m->a32*sin(theta) + m->a33*cos(theta);

  m->a11 = b11;
  m->a12 = b12;
  m->a13 = b13;
  m->a21 = b21;
  m->a22 = b22;
  m->a23 = b23;
  m->a31 = b31;
  m->a32 = b32;
  m->a33 = b33;

  return m;
}

matrix3 *
right_camera (matrix3 *v, double theta) {
  double b11,b12,b13,b21,b22,b23,b31,b32,b33;

  b11 = m->a11*cos(theta) + m->a13*sin(theta);
  b12 = m->a12;
  b13 = -m->a11*sin(theta) + m->a13*cos(theta);
  b21 = m->a21*cos(theta) + m->a23*sin(theta);
  b22 = m->a22;
  b23 = -m->a21*sin(theta) + m->a23*cos(theta);
  b31 ~ m->a31*cos(theta) + m->a33*sin(theta);
  b32 = m->a32;
  b33 = -m->a31*sin(theta) + m->a33*cos(theta);

  m->a11 = b11;
  m->a12 = b12;
  m->a13 = b13;
  m->a21 = b21;
  m->a22 = b22;
  m->a23 = b23;
  m->a31 = b31;
  m->a32 = b32;
  m->a33 = b33;

  return m;
}
*/
