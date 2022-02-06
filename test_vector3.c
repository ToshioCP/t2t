/* test program that test vector3.c */

#include <gtk/gtk.h>
#include "vector.h"

int
main (int argc, char **argv) {
  vector3 *v1, *v2, *v3;
  matrix3 *m1, *m2, *m3;

  if (!double_eq (1.234567, 1.234567)) {
    g_print ("double_eq function didn't work.\n");
  }
  v1 = vector3_new (1.0, 2.0, 3.0);
  g_print ("Test error reporting function.\n");
  g_print ("If the following line is '(1.0, 2.0, 3.0)', then the functions vector3_new and print_v3 have worked.\n\n"); 
  print_v3 (v1);
  g_print ("\n");
  if (! vector3_eq0 (v1, 1.0, 2.0, 3.0))
    g_print ("vector3_eq0 didn't work.\n");
  vector3_assign (v1, -1.0, -2.0, -3.0);
  if (! vector3_eq0 (v1, -1.0, -2.0, -3.0))
    g_print ("vector3_assign didn't work.\n");
  v2 = vector3_new (-1.0, -2.0, -3.0);
  if (! vector3_eq (v1, v2))
    g_print ("vector3_assign didn't work.\n");
  vector3_assign (v2, 2.0, 4.0, 8.0);
  vector3_copy (v1, v2);
  if (! vector3_eq0 (v1, 2.0, 4.0, 8.0))
    g_print ("vector3_copy didn't work.\n");
  if (vector3_norm (v1) != sqrt(84.0))
    g_print ("vector3_norm didn't work.\n");

  v3 = vector3_scalar_multiple_n (3.0, v1);
  if (! vector3_eq0 (v3, 6.0, 12.0, 24.0))
    g_print ("vector3_scalar_multiple_n didn't work.\n");
  vector3_scalar_multiple_c (2.0, v1, v3);
  if (! vector3_eq0 (v3, 4.0, 8.0, 16.0))
    g_print ("vector3_scalar_multiple_c didn't work.\n");
  vector3_scalar_multiple_a (-2.0, v1);
  if (! vector3_eq0 (v1, -4.0, -8.0, -16.0))
    g_print ("vector3_scalar_multiple_a didn't work.\n");

  vector3_free (v3);
  vector3_assign (v1, 2.0, 3.0, 4.0);
  vector3_assign (v2, -2.0, 2.0, 5.0);
  v3 = vector3_add_n (v1, v2);
  if (! vector3_eq0 (v3, 0.0, 5.0, 9.0))
    g_print ("vector3_add_n didn't work.\n");
  vector3_assign (v3, 0.0, 0.0, 0.0); /* reset */
  vector3_add_c (v1, v2, v3);
  if (! vector3_eq0 (v3, 0.0, 5.0, 9.0))
    g_print ("vector3_add_c didn't work.\n");
  vector3_add_a (v1, v2);
  if (! vector3_eq0 (v1, 0.0, 5.0, 9.0))
    g_print ("vector3_add_a didn't work.\n");

  vector3_free (v3);
  vector3_assign (v1, 5.0, 2.0, 3.0);
  vector3_assign (v2, 3.0, -1.0, 2.0);
  v3 = vector3_sub_n (v1, v2);
  if (! vector3_eq0 (v3, 2.0, 3.0, 1.0))
    g_print ("vector3_sub_n didn't work.\n");
  vector3_assign (v3, 0.0, 0.0, 0.0); /* reset */
  vector3_sub_c (v1, v2, v3);
  if (! vector3_eq0 (v3, 2.0, 3.0, 1.0))
    g_print ("vector3_sub_c didn't work.\n");
  vector3_sub_a (v1, v2);
  if (! vector3_eq0 (v1, 2.0, 3.0, 1.0))
    g_print ("vector3_sub_a didn't work.\n");

  vector3_assign (v1, 2.0, 6.0, 3.0);
  vector3_assign (v2, 3.0, -2.0, 5.0);
  if (vector3_inner_product (v1, v2) != 6.0-12.0+15.0)
    g_print ("vector3_inner_product didn't work.\n");

  vector3_free (v3);
  v3 = vector3_cross_product_n (v1, v2);
  if (! vector3_eq0 (v3, 36.0, -1.0, -22.0))
    g_print ("vector3_cross_product_n didn't work.\n");
  vector3_assign (v3, 0.0, 0.0, 0.0); /* reset */
  vector3_cross_product_c (v1, v2, v3);
  if (! vector3_eq0 (v3, 36.0, -1.0, -22.0))
    g_print ("vector3_cross_product_c didn't work.\n");
  vector3_cross_product_a (v1, v2);
  if (! vector3_eq0 (v1, 36.0, -1.0, -22.0))
    g_print ("vector3_coss_product_a didn't work.\n");

  vector3_free (v3);
  vector3_assign (v1, -5.0, 0.0, 0.0);
  v3 = vector3_hat_n (v1);
  if (! vector3_eq0 (v3, -1.0, 0.0, 0.0))
    g_print ("vector3_hat_n didn't work.\n");
  vector3_assign (v1, 1.0, 4.0, 8.0);
/* 1^2+4^2+8^2=9^2 */
  vector3_hat_a (v1);
  if (! vector3_eq0 (v1, 1.0/9.0, 4.0/9.0, 8.0/9.0))
    g_print ("vector3_hat_a didn't work.\n");
  vector3_free (v3);

  vector3_assign (v1, -2.0, 3.0, 5.0);
  vector3_assign (v2, 1.0, 1.0, 1.0);
  v3 = vector3_projection_n (v1, v2);
  if (! vector3_eq0 (v3, 2.0, 2.0, 2.0))
    g_print ("vector3_projection_n didn't work.\n");
  vector3_assign (v3, 0.0, 0.0, 0.0); /* reset */
  vector3_projection_c (v1, v2, v3);
  if (! vector3_eq0 (v3, 2.0, 2.0, 2.0))
    g_print ("vector3_projection_c didn't work.\n");
  vector3_projection_a (v1, v2);
  if (! vector3_eq0 (v1, 2.0, 2.0, 2.0))
    g_print ("vector3_projection_a didn't work.\n");
  vector3_free (v3);

  vector3_assign (v1, -2.0, 3.0, 5.0);
  vector3_assign (v2, 1.0, 1.0, 1.0);
  v3 = vector3_rejection_n (v1, v2);
  if (! vector3_eq0 (v3, -4.0, 1.0, 3.0))
    g_print ("vector3_rejection_n didn't work.\n");
  vector3_assign (v3, 0.0, 0.0, 0.0); /* reset */
  vector3_rejection_c (v1, v2, v3);
  if (! vector3_eq0 (v3, -4.0, 1.0, 3.0))
    g_print ("vector3_rejection_c didn't work.\n");
  vector3_rejection_a (v1, v2);
  if (! vector3_eq0 (v1, -4.0, 1.0, 3.0))
    g_print ("vector3_rejection_a didn't work.\n");
  vector3_free (v3);

  vector3_free (v2);
  vector3_assign (v1, 1.0, 2.0, 3.0);
  v2 = vector3_rot_x_n (60.0, v1);
  if (! vector3_eq0 (v2, 1.0, (2.0-3.0*sqrt(3.0))/2.0, (2.0*sqrt(3.0)+3.0)/2.0))
    g_print ("vector3_rot_x_n didn't work.\n");
  vector3_assign (v2, 0.0, 0.0, 0.0); /* reset */
  vector3_rot_x_c (30.0, v1, v2);
  if (! vector3_eq0 (v2, 1.0, (2.0*sqrt(3.0)-3.0)/2.0, (2.0+3.0*sqrt(3.0))/2.0))
    g_print ("vector3_rot_x_c didn't work.\n");
  vector3_rot_x_a (45.0, v1);
  if (! vector3_eq0 (v1, 1.0, (2.0-3.0)/sqrt(2.0), (2.0+3.0)/sqrt(2.0)))
    g_print ("vector3_rot_x_a didn't work.\n");
  vector3_free (v2);

  vector3_assign (v1, 1.0, 2.0, 3.0);
  v2 = vector3_rot_y_n (60.0, v1);
  if (! vector3_eq0 (v2, (3.0*sqrt(3.0)+1.0)/2.0, 2.0, (3.0-1.0*sqrt(3.0))/2.0))
    g_print ("vector3_rot_y_n didn't work.\n");
  vector3_assign (v2, 0.0, 0.0, 0.0); /* reset */
  vector3_rot_y_c (30.0, v1, v2);
  if (! vector3_eq0 (v2, (3.0+1.0*sqrt(3.0))/2.0, 2.0, (3.0*sqrt(3.0)-1.0)/2.0))
    g_print ("vector3_rot_y_c didn't work.\n");
  vector3_rot_y_a (45.0, v1);
  if (! vector3_eq0 (v1, (3.0+1.0)/sqrt(2.0), 2.0, (3.0-1.0)/sqrt(2.0)))
    g_print ("vector3_rot_y_a didn't work.\n");
  vector3_free (v2);

  vector3_assign (v1, 1.0, 2.0, 3.0);
  v2 = vector3_rot_z_n (60.0, v1);
  if (! vector3_eq0 (v2, (1.0-2.0*sqrt(3.0))/2.0, (1.0*sqrt(3.0)+2.0)/2.0, 3.0))
    g_print ("vector3_rot_z_n didn't work.\n");
  vector3_assign (v2, 0.0, 0.0, 0.0); /* reset */
  vector3_rot_z_c (30.0, v1, v2);
  if (! vector3_eq0 (v2, (1.0*sqrt(3.0)-2.0)/2.0, (1.0+2.0*sqrt(3.0))/2.0, 3.0))
    g_print ("vector3_rot_z_c didn't work.\n");
  vector3_rot_z_a (45.0, v1);
  if (! vector3_eq0 (v1, (1.0-2.0)/sqrt(2.0), (1.0+2.0)/sqrt(2.0), 3.0))
    g_print ("vector3_rot_z_a didn't work.\n");
  vector3_free (v1);
  vector3_free (v2);


  m1 = matrix3_new (1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
  if (! matrix3_eq0 (m1, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0))
    g_print ("matrix3_new didn't work.\n");
  if (matrix3_eq0 (m1, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 999.0))
    g_print ("matrix3_eq0 didn't work.\n");
  m2 = matrix3_new (1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
  if (! matrix3_eq (m1, m2))
    g_print ("matrix3_eq didn't work.\n");
  matrix3_assign (m2, 111.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
  if (! matrix3_eq0 (m2, 111.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0))
    g_print ("matrix3_assign didn't work.\n");
  if (matrix3_eq (m1, m2))
    g_print ("matrix3_eq didn't work.\n");
  matrix3_copy (m2, m1);
  if (! matrix3_eq (m1, m2))
    g_print ("matrix3_copy didn't work.\n");

  matrix3_free (m2);
  m2 = matrix3_scalar_multiple_n (2.0, m1);
  if (! matrix3_eq0 (m2, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0))
    g_print ("matrix3_scalar_multiple_n didn't work.\n");
  matrix3_scalar_multiple_c (3.0, m1, m2);
  if (! matrix3_eq0 (m2, 3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 24.0, 27.0))
    g_print ("matrix3_scalar_multiple_c didn't work.\n");
  matrix3_scalar_multiple_a (3.0, m1);
  if (! matrix3_eq (m1, m2))
    g_print ("matrix3_scalar_multiple_a didn't work.\n");

  matrix3_assign (m1, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
  matrix3_assign (m2, -9.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0, -2.0, -1.0);
  m3 = matrix3_add_n (m1, m2);
  if (! matrix3_eq0 (m3, -8.0, -6.0, -4.0, -2.0, 0.0, 2.0, 4.0, 6.0, 8.0))
    g_print ("matrix3_add_n didn't work.\n");
  matrix3_assign (m3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0); /*reset */
  matrix3_add_c (m1, m2, m3);
  if (! matrix3_eq0 (m3, -8.0, -6.0, -4.0, -2.0, 0.0, 2.0, 4.0, 6.0, 8.0))
    g_print ("matrix3_add_c didn't work.\n");
  matrix3_add_a (m1, m2);
  if (! matrix3_eq0 (m1, -8.0, -6.0, -4.0, -2.0, 0.0, 2.0, 4.0, 6.0, 8.0))
    g_print ("matrix3_add_a didn't work.\n");

  matrix3_assign (m1, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
  matrix3_assign (m2, -9.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0, -2.0, -1.0);
  matrix3_free (m3);
  m3 = matrix3_sub_n (m1, m2);
  if (! matrix3_eq0 (m3, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0))
    g_print ("matrix3_sub_n didn't work.\n");
  matrix3_assign (m3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0); /*reset */
  matrix3_sub_c (m1, m2, m3);
  if (! matrix3_eq0 (m3, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0))
    g_print ("matrix3_sub_c didn't work.\n");
  matrix3_sub_a (m1, m2);
  if (! matrix3_eq0 (m1, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0))
    g_print ("matrix3_sub_a didn't work.\n");

  matrix3_assign (m1, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
  matrix3_assign (m2, -9.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0, -2.0, -1.0);
  matrix3_free (m3);
  m3 = matrix3_mul_n (m1, m2);
  if (! matrix3_eq0 (m3, -30.0, -24.0, -18.0, -84.0, -69.0, -54.0, -138.0, -114.0, -90.0))
    g_print ("matrix3_mul_n didn't work.\n");
  matrix3_assign (m3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0); /*reset */
  matrix3_mul_c (m1, m2, m3);
  if (! matrix3_eq0 (m3, -30.0, -24.0, -18.0, -84.0, -69.0, -54.0, -138.0, -114.0, -90.0))
    g_print ("matrix3_mul_c didn't work.\n");
  matrix3_mul_a (m1, m2);
  if (! matrix3_eq0 (m1, -30.0, -24.0, -18.0, -84.0, -69.0, -54.0, -138.0, -114.0, -90.0))
    g_print ("matrix3_mul_a didn't work.\n");

  matrix3_assign (m1, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
  if (matrix3_det (m1) != 0.0)
    g_print ("matrix3_det didn't work.\n");
  matrix3_assign (m1, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
  if (matrix3_det (m1) != 1.0)
    g_print ("matrix3_det didn't work.\n");

  g_print ("Testing print_m3 function.\n");
  g_print ("If the following is (1.0, 2.0, 3.0), (4.0, 5.0, 6.0) and (7.0, 8.0, 9.0), then the function has worked.\n\n");
  matrix3_assign (m1, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
  print_m3 (m1);

  matrix3_free (m1);
  matrix3_free (m2);
  matrix3_free (m3);
}
