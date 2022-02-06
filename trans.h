#ifndef __T2T_TRANS_H__
#define __T2T_TRANS_H__

/* transformation */

#include <gtk/gtk.h>
#include "vector.h"

void
init_matrix (vector3 *t, matrix3 *m);

/* move drone */
matrix3 *
up_drone (matrix3 *m, double h);

matrix3 *
rot_drone (matrix3 *m, double theta);

matrix3 *
zoom_in (matrix3 *m, double d);

/* move camera */

vector3 *
up_camera (vector3 *v, double theta);

vector3 *
right_camera (vector3 *v, double theta);

#endif /* __T2T_TRANS_H__ */

