/* test program that test vector3.c */

#include <gtk/gtk.h>
#include "trans.h"
#include "vector.h"

int
main (int argc, char **argv) {
  vector3 *t;
  matrix3 *m;
  gboolean success;

  m = matrix3_new (
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0
      );
  t = vector3_new (1.0, 0.0, 0.0);

  init_matrix (t, m);
  success = matrix3_eq0 (m,
              0.0, 1.0, 0.0,
              0.0, 0.0, 1.0,
             -1.0, 0.0, 0.0
            );
  if (! success) {
    g_print ("Matrix initialize error.\n");
    print_m3 (m);
  }
 
  vector3_assign (t, 1.0, 1.0, 1.0);
  init_matrix (t, m);
  success = matrix3_eq0 (m,
             -1.0/sqrt(3.0), 1.0/sqrt(3.0), 0.0,
             -1.0/3.0, -1.0/3.0, 2.0/3.0,
             -1.0/sqrt(3.0), -1.0/sqrt(3.0), -1.0/sqrt(3.0)
            );
  if (! success) {
    g_print ("Matrix initialize error.\n");
    print_m3 (m);
  }




 vector3_free (t);
  matrix3_free (m);
}
