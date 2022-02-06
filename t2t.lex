%top{
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "t2t_parser.h"

  static int nline = 1;
  static int ncolumn = 1;
  static void get_location (char *text);

  /* Dinamically allocated memories are added to the single list. They will be freed in the finalize function. */
  /* The following variable list is defined in t2t.y. */
  extern GSList *list;
}

%option noyywrap

REAL_NUMBER (0|[1-9][0-9]*)(\.[0-9]+)?
IDENTIFIER [a-zA-Z][a-zA-Z0-9]*
%%
  /* rules */
#.*               ; /* comment. Be careful. Dot symbol (.) matches any character but new line. */
[ ]               ncolumn++;
\t                ncolumn += 8; /* assume that a tab is recognized as 8 spaces. */
\n                nline++; ncolumn = 1;
  /* reserved keywords */
LW                get_location (yytext); return LW; /* set Line Width */
MT                get_location (yytext); return MT; /* Move To */
LT                get_location (yytext); return LT; /* Line To */
FC                get_location (yytext); return FC; /* Foreground Color */
BC                get_location (yytext); return BC; /* Background Color */
ST                get_location (yytext); return ST; /* Set T */
UT                get_location (yytext); return UT; /* Up T */
RT                get_location (yytext); return RT; /* Rotate T */
ZT                get_location (yytext); return ZT; /* Zoom in T */
IC                get_location (yytext); return IC; /* Initialize Coordinate transformation matrix */
LU                get_location (yytext); return LU; /* Look Up */
LR                get_location (yytext); return LR; /* Look Right */
SD                get_location (yytext); return SD; /* Set D */
AD                get_location (yytext); return AD; /* Add D */
DM                get_location (yytext); return DM; /* Display Magnification */
SC                get_location (yytext); return SC; /* Show Code */
HC                get_location (yytext); return HC; /* Hide Code */
SIN               get_location (yytext); return SIN; /* Sine */
COS               get_location (yytext); return COS; /* Cosine */
  /* constant */
{REAL_NUMBER}     get_location (yytext); yylval.NUM = atof (yytext); return NUM;
  /* identifier */
{IDENTIFIER}      { get_location (yytext); yylval.ID = g_strdup(yytext);
                    list = g_slist_prepend (list, yylval.ID);
                    return ID;
                  }
"="               get_location (yytext); return '=';
"+"               get_location (yytext); return '+';
"-"               get_location (yytext); return '-';
"*"               get_location (yytext); return '*';
"/"               get_location (yytext); return '/';
"("               get_location (yytext); return '(';
")"               get_location (yytext); return ')';
","               get_location (yytext); return ',';
.                 ncolumn++;             return YYUNDEF;
%%

static void
get_location (char *text) {
  yylloc.first_line = yylloc.last_line = nline;
  yylloc.first_column = ncolumn;
  yylloc.last_column = (ncolumn += strlen(text)) - 1;
}

static YY_BUFFER_STATE state;

void
init_flex (const char *text) {
  state = yy_scan_string (text);
  nline = ncolumn = 1;
}

void
finalize_flex (void) {
  yy_delete_buffer (state);
}

