%code top{
  #include <stdarg.h>
  #include <setjmp.h>
  #include <math.h>
  #include <gtk/gtk.h>
  #include "vector.h"
  #include "trans.h"
  #include "t2t_lex.h"
  #include "t2t_parser.h"

  /* debug mode */
  #define debug 1
  #undef debug

  /* error reporting */
  static jmp_buf buf;

  static void yyerror (char const *s) { /* for syntax error */
    g_print ("%s from line %d, column %d to line %d, column %d\n",s, yylloc.first_line, yylloc.first_column, yylloc.last_line, yylloc.last_column);
    longjmp (buf, 1);
  }
  /* Node type */
  enum {
    N_LW,
    N_MT,
    N_LT,
    N_FC,
    N_BC,
    N_ST,
    N_UT,
    N_RT,
    N_ZT,
    N_IC,
    N_LU,
    N_LR,
    N_SD,
    N_AD,
    N_DM,
    N_SC,
    N_HC,
    N_SIN,
    N_COS,
    N_NUM,
    N_ID,
    N_program,
    N_statement,
    N_let,
    N_var,
    N_expression,
    N_ADD,
    N_SUB,
    N_MUL,
    N_DIV,
    N_UMINUS
  };
#ifdef debug
  char *node_type_table[] = {
    "N_LW",
    "N_MT",
    "N_LT",
    "N_FC",
    "N_BC",
    "N_ST",
    "N_UT",
    "N_RT",
    "N_ZT",
    "N_IC",
    "N_LU",
    "N_LR",
    "N_SD",
    "N_AD",
    "N_DM",
    "N_SC",
    "N_HC",
    "N_SIN",
    "N_COS",
    "N_NUM",
    "N_ID",
    "N_program",
    "N_statement",
    "N_let",
    "N_var",
    "N_expression",
    "N_ADD",
    "N_SUB",
    "N_MUL",
    "N_DIV",
    "N_UMINUS"
  };
#endif
}

%code requires {
  void finalize_runtime (void);
  gboolean parse (char *contents);
  gboolean run(GtkDrawingArea *drawing_area, cairo_t *cr, int width, int height, gpointer user_data);

  /* semantic value type */
  typedef struct _node_t node_t;
  struct _node_t {
    int type;
    union {
      struct {
        node_t *child1, *child2, *child3;
      } child;
      int pt; /* pt is an index of the table and it points a variable */
      double value;
    } content;
  };
}

%code {
  int yylex (void);
  int yyparse (void);
/* The following macro is convenient to get the member of the node. */
  #define child1(n) (n)->content.child.child1
  #define child2(n) (n)->content.child.child2
  #define child3(n) (n)->content.child.child3
  #define pointer(n) (n)->content.pt
  #define value(n) (n)->content.value

  /* start of nodes */
  static node_t *node_top = NULL;
  /* functions to generate trees */
  node_t *tree1 (int type, node_t *child1, node_t *child2, node_t *child3);
  node_t *tree2 (int type, double value);
  node_t *tree3 (int type, char *name, node_t *node_expr);
  node_t *tree4 (int type, char *name);
}

%locations
%define api.value.type union /* YYSTYPE, the type of semantic values, is union of following types */
 /* key words */
%token LW
%token MT
%token LT
%token FC
%token BC
%token ST
%token UT
%token RT
%token ZT
%token IC
%token LU
%token LR
%token SD
%token AD
%token DM
%token SC
%token HC
%token SIN
%token COS
 /* constant */
%token <double> NUM
 /* identirier */
%token <char *> ID
 /* non terminal symbol */
%nterm <node_t *> program
%nterm <node_t *> statement
%nterm <node_t *> expression
 /* assignment symbol */
%right '='
 /* arithmetic symbol */
%left '+' '-'
%left '*' '/'
%precedence UMINUS /* unary minus */
%%

program:
  statement { node_top = $$ = $1; }
| program statement { node_top = $$ = tree1 (N_program, $1, $2, NULL); }
;
statement:
  LW '(' expression ')' { $$ = tree1 (N_LW, $3, NULL, NULL); }
| MT '(' expression ',' expression ',' expression ')' { $$ = tree1 (N_MT, $3, $5, $7); }
| LT '(' expression ',' expression ',' expression ')' { $$ = tree1 (N_LT, $3, $5, $7); }
| FC '(' expression ',' expression ',' expression ')' { $$ = tree1 (N_FC, $3, $5, $7); }
| BC '(' expression ',' expression ',' expression ')' { $$ = tree1 (N_BC, $3, $5, $7); }
| ST '(' expression ',' expression ',' expression ')' { $$ = tree1 (N_ST, $3, $5, $7); }
| UT '(' expression ')' { $$ = tree1 (N_UT, $3, NULL, NULL); }
| RT '(' expression ')' { $$ = tree1 (N_RT, $3, NULL, NULL); }
| ZT '(' expression ')' { $$ = tree1 (N_ZT, $3, NULL, NULL); }
| IC { $$ = tree1 (N_IC, NULL, NULL, NULL); }
| LU '(' expression ')' { $$ = tree1 (N_LU, $3, NULL, NULL); }
| LR '(' expression ')' { $$ = tree1 (N_LR, $3, NULL, NULL); }
| SD '(' expression ')' { $$ = tree1 (N_SD, $3, NULL, NULL); }
| AD '(' expression ')' { $$ = tree1 (N_AD, $3, NULL, NULL); }
| DM '(' expression ')' { $$ = tree1 (N_DM, $3, NULL, NULL); }
| SC { $$ = tree1 (N_SC, NULL, NULL, NULL); }
| HC { $$ = tree1 (N_HC, NULL, NULL, NULL); }
| ID '=' expression { $$ = tree3 (N_let, $1, $3); }
;
expression:
  expression '+' expression { $$ = tree1 (N_ADD, $1, $3, NULL); }
| expression '-' expression { $$ = tree1 (N_SUB, $1, $3, NULL); }
| expression '*' expression { $$ = tree1 (N_MUL, $1, $3, NULL); }
| expression '/' expression { $$ = tree1 (N_DIV, $1, $3, NULL); }
| '-' expression %prec UMINUS { $$ = tree1 (N_UMINUS, $2, NULL, NULL); }
| '(' expression ')' { $$ = $2; }
| ID    { $$ = tree4 (N_var, $1); }
| NUM   { $$ = tree2 (N_NUM, $1); }
| SIN '(' expression ')' { $$ = tree1 (N_SIN, $3, NULL, NULL); }
| COS '(' expression ')' { $$ = tree1 (N_COS, $3, NULL, NULL); }
;

%%

/* Declaration of the runtime error function */
static void runtime_error (char *format, ...);

/* Dynamically allocated memories are added to the single list. They will be freed in the finalize function. */
GSList *list = NULL;

/* Symbols are names of variables.
 * They are stored in a single symbol table. */

#define MAX_TABLE_SIZE 100
 
struct {
  char *name;
  double value;
} table[MAX_TABLE_SIZE];
int tp;

void
init_table (void) {
  tp = 0;
}

/* return the index of the table that points the varible */ 
int
lookup (char *name) {
  int i;

  if (tp == 0)
    return -1;
  for (i=0; i<tp; ++i)
    if (strcmp(name, table[i].name) == 0)
      return i;
  return -1;
}

int
install (char *name) {
  int pt;

  if (tp >= MAX_TABLE_SIZE) {
    runtime_error ("Symbol table overflow.\n");
    return -1;
  } else if ((pt = lookup (name)) >= 0) /* found */ 
    return pt;
  else {
    table[tp++].name = name;
    return tp-1;
  }
}

void
put_value (int pt, double value) {
  if (pt <0 || pt >= tp)
    runtime_error ("Pointer %d points no varable in the table.\n", pt);
  table[pt].value = value;
}

double
get_value (int pt) {
  if (pt <0 || pt >= tp)
    runtime_error ("Pointer %d points no varable in the table.\n", pt);
  return table[pt].value;
}


#ifdef debug
/* Show the symbol table */
void
show_symbol_table (void) {
  int i;
  g_print ("****** Symbol table ******\n");
  g_print ("  Table pointer (tp) = %d.\n", tp);
  g_print ("  ** Contents **\n");
  for (i=0; i<tp; ++i)
    g_print ("name = %s, value = %f\n", table[i].name, table[i].value);
} 
#endif

/* treeX functions */
node_t *create_node (void) {
  list = g_slist_prepend (list, g_malloc (sizeof (node_t)));
  return (node_t *) list->data;
}

node_t *
tree1 (int type, node_t *child1, node_t *child2, node_t *child3) {
  node_t *new_node;

  new_node = create_node ();
  new_node->type = type;
  child1(new_node) = child1;
  child2(new_node) = child2;
  child3(new_node) = child3;
  return new_node;
}

node_t *
tree2 (int type, double value) {
  node_t *new_node;

  new_node = create_node ();
  new_node->type = type;
  value(new_node) = value;
  return new_node;
}

node_t *
tree3 (int type, char *name, node_t *node_expr) {
  node_t *new_node, *node_var;

  new_node = create_node ();
  new_node->type = type;
  node_var = create_node ();
  pointer(node_var) = install (name);
  child1(new_node) = node_var;
  child2(new_node) = node_expr;
  child3(new_node) = NULL;
  return new_node;
}

node_t *
tree4 (int type, char *name) {
  node_t *new_node;

  new_node = create_node ();
  new_node->type = type;
  pointer(new_node) = lookup (name);
  return new_node;
}

/* status of the surface */
static double cur_x = 0.0;
static double cur_y = 0.0;
static double line_width = 2.0;
struct color {
  double red;
  double green;
  double blue;
};
static struct color bc = {0.95, 0.95, 0.95}; /* white */ 
static struct color fc = {0.0, 0.0, 0.0}; /* black */
static double magnification = 72; /* Display magnification; coefficient to enlarge */
/* The following two variable is used to make a decision whether print or not. */
static int first_time = TRUE;
static int print_code = FALSE;

static vector3 _t;
static vector3 *t = &_t; /* vector OO' */
static matrix3 _m;
static matrix3 *m = &_m; /* orthogonal transformation matrix */
static double d; /* the distance between O' and a screen */

/* Three TO Two --- Transform v, which is represented with the grand coordinate O, into (x,y), which is the coordinate with the screen. */
void t2t (vector3 *v, double *x, double *y) {
  vector3 v1, v2;

  vector3_copy (&v1, v);
  vector3_sub_a (&v1, t);
  matrix3_vector3_mul_c (m, &v1, &v2);
  *x = v2.x*d/v2.z;
  *y = v2.y*d/v2.z;
#ifdef debug
g_print ("    v(O)  = (%f, %f, %f)\n", v->x, v->y, v->z);
g_print ("    v(O') = (%f, %f, %f)\n", v2.x, v2.y, v2.z);
g_print ("    v(S)  = (%f, %f)\n", *x, *y);
#endif
}

/* ------ RUNTIME ROUTINE ------ */
/* Analyze the tree node of elements. */

/* Eval analyzes an expression node and returns a value of the expression. */
double
eval (node_t *node) {
  double value = 0.0;

  if (node == NULL)
    runtime_error ("No expression to evaluate.\n");
#ifdef debug
g_print ("eval: node type is %s.\n", node_type_table[node->type]);
#endif
#define calc(op) eval (child1(node)) op eval (child2(node))
  switch (node->type) {
    case N_ADD:
      value = calc (+);
      break;
    case N_SUB:
      value = calc (-);
      break;
    case N_MUL:
      value = calc (*);
      break;
    case N_DIV:
      if (eval (child2(node)) == 0.0)
        runtime_error ("Division by zerp.\n");
      else
        value = calc (/);
      break;
    case N_UMINUS:
      value = -(eval (child1(node)));
      break;
    case N_var:
      value = get_value (pointer(node));
      break;
    case N_NUM:
      value = value(node);
      break;
    case N_SIN:
      value = sin(eval (child1(node)) * M_PI / 180);
      break;
    case N_COS:
      value = cos(eval (child1(node)) * M_PI / 180);
      break;
    default: 
      runtime_error ("Illegal expression.\n");
  }
  return value;
}

/* Execute analyzes the tree node of statements. */
/* Such elements don't generate any values. */
/* t, m and d has been set before this function is called. */

void
execute (node_t *node, cairo_t *cr) {
  vector3 v1, v2, v3;
  double x, angle;

  if (node == NULL)
    runtime_error ("Node is NULL.\n");
#ifdef debug
g_print ("execute: node type is %s.\n", node_type_table[node->type]);
g_print ("----- Current status -----\n");
g_print ("    Current X coordinate is %f.\n", cur_x);
g_print ("    Current Y coordinate is %f.\n", cur_y);
g_print ("    Line width is %f.\n", line_width);
g_print ("    Background color is (%f, %f, %f).\n", bc.red, bc.green, bc.blue);
g_print ("    Foreground color is (%f, %f, %f).\n", fc.red, fc.green, fc.blue);
g_print ("----- Current parameters -----\n");
g_print ("    t = (%f, %f, %f)\n", t->x, t->y, t->z);
g_print ("    m = (%f, %f, %f\n", m->a11, m->a12, m->a13);
g_print ("         %f, %f, %f\n", m->a21, m->a22, m->a23);
g_print ("         %f, %f, %f)\n", m->a31, m->a32, m->a33);
g_print ("    d = %f\n", d);
show_symbol_table();
#endif
  switch (node->type) {
    case N_program:
      execute (child1(node), cr);
      execute (child2(node), cr);
      break;
    case N_LW:
      line_width = eval (child1(node));
      if (first_time && print_code)
        g_print ("LW (%f)\n", line_width);
      break;
    case N_MT:
      v1.x = eval (child1(node));
      v1.y = eval (child2(node));
      v1.z = eval (child3(node));
      t2t (&v1, &cur_x, &cur_y);
      if (first_time && print_code)
        g_print ("MT (%f, %f, %f)  => screen: MT (%f, %f)\n", v1.x, v1.y, v1.z, cur_x, cur_y);
      break;
    case N_LT:
      v1.x = eval (child1(node));
      v1.y = eval (child2(node));
      v1.z = eval (child3(node));
      cairo_move_to (cr, cur_x*magnification, cur_y*magnification); /* Set the new position as the current position. */ 
      t2t (&v1, &cur_x, &cur_y);
      cairo_set_line_width (cr, line_width);
      cairo_set_source_rgb (cr, fc.red, fc.green, fc.blue);
      cairo_line_to (cr, cur_x*magnification, cur_y*magnification);
      cairo_stroke (cr); /* This command clears thhe current path. */
      if (first_time && print_code)
        g_print ("LT (%f, %f, %f)  => screen: LT (%f, %f)\n", v1.x, v1.y, v1.z, cur_x, cur_y);
      break;
    case N_FC:
      fc.red = eval (child1(node));
      fc.green = eval (child2(node));
      fc.blue = eval (child3(node));
      if (first_time && print_code)
        g_print ("FC (%f, %f, %f)\n", fc.red, fc.green, fc.blue);
      break;
    case N_BC:
      bc.red = eval (child1(node));
      bc.green = eval (child2(node));
      bc.blue = eval (child3(node));
      /* This command resets the surface of the cairo device cr. */
      /* So, all the shape in the surface will be cleared. */
      cairo_set_source_rgb (cr, bc.red, bc.green, bc.blue);
      cairo_paint (cr);
      if (first_time && print_code)
        g_print ("BC (%f, %f, %f)\n", bc.red, bc.green, bc.blue);
      break;
    case N_ST:
      t->x = eval (child1(node));
      t->y = eval (child2(node));
      t->z = eval (child3(node));
      if (first_time && print_code)
        g_print ("ST (%f, %f, %f)\n", t->x, t->y, t->z);
      break;
    case N_UT:
      x = eval (child1(node));
      t->z += x;
      if (first_time && print_code)
        g_print ("UT (%f)\n", x);
      break;
    case N_RT:
      angle = eval (child1(node));
      vector3_rot_z_a (angle, t);
      vector3_assign (&v1, m->a11, m->a12, m->a13);
      vector3_assign (&v2, m->a21, m->a22, m->a23);
      vector3_assign (&v3, m->a31, m->a32, m->a33);
      vector3_rot_z_a (angle, &v1);
      vector3_rot_z_a (angle, &v2);
      vector3_rot_z_a (angle, &v3);
      matrix3_assign (m, v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v3.x, v3.y, v3.z);
      if (first_time && print_code)
        g_print ("RT (%f)\n", angle);
      break;
    case N_ZT:
      x = eval (child1(node));
      if (first_time && print_code)
        g_print ("ZT (%f)\n", x);
      if (x <= 0.0)
        break;
      vector3_scalar_multiple_a (1.0/x, t);
      break;
    case N_IC:
      init_matrix (t, m);
      if (first_time && print_code)
        g_print ("IC\n");
      break;
    case N_LU:
      x = eval (child1(node));
      angle = x*M_PI/180;
      /* k' = (cos theta)k+(sin theta)j */
      /* j' = (-sin theta)k+(cos theta)j */
      v1.x = cos(angle)*m->a31 + sin(angle)*m->a21;
      v1.y = cos(angle)*m->a32 + sin(angle)*m->a22;
      v1.z = cos(angle)*m->a33 + sin(angle)*m->a23;
      v2.x = -sin(angle)*m->a31 + cos(angle)*m->a21;
      v2.y = -sin(angle)*m->a32 + cos(angle)*m->a22;
      v2.z = -sin(angle)*m->a33 + cos(angle)*m->a23;
      matrix3_assign (m, m->a11, m->a12, m->a13, v2.x, v2.y, v2.z, v1.x, v1.y, v1.z);
      if (first_time && print_code)
        g_print ("LU (%f)\n", x);
      break;
    case N_LR:
      x = eval (child1(node));
      angle = x*M_PI/180;
      /* k' = (cos theta)k+(sin theta)i */
      /* j' = (-sin theta)k+(cos theta)i */
      v1.x = cos(angle)*m->a31 + sin(angle)*m->a11;
      v1.y = cos(angle)*m->a32 + sin(angle)*m->a12;
      v1.z = cos(angle)*m->a33 + sin(angle)*m->a13;
      v2.x = -sin(angle)*m->a31 + cos(angle)*m->a11;
      v2.y = -sin(angle)*m->a32 + cos(angle)*m->a12;
      v2.z = -sin(angle)*m->a33 + cos(angle)*m->a13;
      matrix3_assign (m, v2.x, v2.y, v2.z, m->a21, m->a22, m->a23, v1.x, v1.y, v1.z);
      if (first_time && print_code)
        g_print ("LR (%f)\n", x);
      break;
    case N_SD:
      d = eval (child1(node));
      if (first_time && print_code)
        g_print ("SD (%f)\n", d);
      break;
    case N_AD:
      x = eval (child1(node));
      d += x;
      if (first_time && print_code)
        g_print ("AD (%f)\n", x);
      break;
    case N_DM:
      magnification = eval (child1(node));
      if (first_time && print_code)
        g_print ("DM (%f)\n", magnification);
      break;
    case N_SC:
      if (first_time && print_code)
        g_print ("SC\n");
      print_code = TRUE;
      break;
    case N_HC:
      if (first_time && print_code)
        g_print ("HC\n");
      print_code = FALSE;
      break;
    case N_let:
      put_value (pointer(child1(node)), eval(child2(node)));
      break;
    default:
      runtime_error ("Unknown statement.\n");
  }
}

void
finalize_runtime (void) {
  if (list != NULL)
    g_slist_free_full (g_steal_pointer (&list), g_free);
}

/* The function parse is called when the run button is pressed. */
/* Parse parses t2t-program and generates tree-style codes. */
/* The codes are executed by an interpreter, which is a funtion named run. */
/* The function run is called by the drawing function. */

/* NOTICE*/
/* init_flex, finalize_flex are called in the function parse. */
/* Memries pointed by lisy (slist) are used in both parsing and running. */
/* So, it is initialized at the beginning of parsing. */
/* And it is finalized at the end of running. */

gboolean
parse (char *contents) {
  int i;

  i = setjmp (buf);
  if (i == 0) {
    if (list != NULL)
      g_slist_free_full (g_steal_pointer (&list), g_free);
    init_table ();
    init_flex (contents);
    yyparse ();
    finalize_flex ();
    first_time = TRUE;
    return TRUE;
  } else {   /* get here by longjmp  */
    if (list != NULL)
      g_slist_free_full (g_steal_pointer (&list), g_free);
    finalize_flex ();
    return FALSE; /* error */
  }
}

static jmp_buf buf_runtime;

gboolean
run(GtkDrawingArea *drawing_area, cairo_t *cr, int width, int height, gpointer user_data) {
  int i;
  cairo_matrix_t matrix;
  vector3 v;

  i = setjmp (buf_runtime);
  if (i == 0) {
    matrix.xx = 1.0; matrix.xy = 0.0; matrix.x0 = (double) width / 2.0;
    matrix.yx = 0.0; matrix.yy = -1.0; matrix.y0 = (double) height / 2.0;
    cairo_transform (cr, &matrix);
    cairo_set_source_rgb (cr, bc.red, bc.green, bc.blue);
    cairo_paint (cr);
    cairo_set_source_rgb (cr, fc.red, fc.green, fc.blue);
    vector3_assign (t, 10.0, 10.0, 10.0);
    init_matrix (t, m);
    d = 3.0;
    vector3_assign (&v, 0.0, 0.0, 0.0);
    t2t (&v, &cur_x, &cur_y);
    cairo_move_to (cr, cur_x, cur_y);
    execute(node_top, cr);
    first_time = FALSE;
    return TRUE;
  } else {
    return FALSE;
  }
}

/* error reporting */
/* format supports only %s, %f and %d */
static void
runtime_error (char *format, ...) {
  va_list args;
  char *f;
  char b[3];
  char *s;
  double v;
  int i;

  va_start (args, format);
  for (f = format; *f; f++) {
    if (*f != '%') {
      b[0] = *f;
      b[1] = '\0';
      g_print ("%s", b);
      continue;
    }
    switch (*++f) {
      case 's':
        s = va_arg(args, char *);
        g_print ("%s", s);
        break;
      case 'f':
        v = va_arg(args, double);
        g_print("%f", v);
        break;
      case 'd':
        i = va_arg(args, int);
        g_print("%d", i);
        break;
      default:
        b[0] = '%';
        b[1] = *f;
        b[2] = '\0';
        g_print ("%s", b);
        break;
    }
  }
  va_end (args);

  longjmp (buf_runtime, 1);
}
