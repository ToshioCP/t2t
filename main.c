#include <gtk/gtk.h>
#include "tfetextview.h"
#include "t2t_parser.h"

static GtkWidget *win;
static GtkWidget *tv;
static GtkWidget *da;
static gboolean draw_function_switch = FALSE;

/* The following call-back will be called when the user clicked the close button of the main window. */
gboolean
close_request_cb (GtkWindow* self, gpointer user_data) {
  draw_function_switch = FALSE;
  finalize_runtime ();
  return FALSE; /* continue other signal handlers. */
}

/* Show the filename on the title bar */
static void
show_filename (TfeTextView *tv) {
  GFile *file;
  char *filename;
  char *title;

  file = tfe_text_view_get_file (tv);
  if (G_IS_FILE (file)) {
    filename = g_file_get_basename (file);
    title = g_strdup_printf ("T2t (%s)", filename);
    g_free (filename);
    g_object_unref (file);
  } else
    title = g_strdup ("T2t");
  gtk_window_set_title (GTK_WINDOW (win), title);
  g_free (title);
}

/* button handler */
void
run_cb (GtkWidget *btnr) {
  GtkTextBuffer *tb = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tv));
  GtkTextIter start_iter;
  GtkTextIter end_iter;
  char *contents;
  int stat;
  static gboolean busy = FALSE;
  GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT | GTK_DIALOG_MODAL;
  GtkWidget *dialog;

  /* yyparse() are NOT thread safe. */
  /* The variable busy avoids reentry. */
  if (busy)
    return;
  busy = TRUE;
  gtk_text_buffer_get_bounds (tb, &start_iter, &end_iter);
  contents = gtk_text_buffer_get_text (tb, &start_iter, &end_iter, FALSE);
  draw_function_switch = FALSE; /* stop drawing*/
  stat = parse (contents);
  if (stat) /* No error */ {
    draw_function_switch = TRUE;
    gtk_widget_queue_draw (GTK_WIDGET (da));
  } else {
    dialog = gtk_message_dialog_new (GTK_WINDOW (win), flags, GTK_MESSAGE_WARNING, GTK_BUTTONS_CLOSE, "Parser Error");
    g_signal_connect (dialog, "response", G_CALLBACK (gtk_window_destroy),NULL);
  }
  g_free (contents);
  busy = FALSE;
}

void
open_cb (GtkWidget *btno) {
  tfe_text_view_open (TFE_TEXT_VIEW (tv), GTK_WINDOW (win));
}

void
save_cb (GtkWidget *btns) {
  tfe_text_view_save (TFE_TEXT_VIEW (tv));
}

void
close_cb (GtkWidget *btnc) {
  draw_function_switch = FALSE;
  finalize_runtime ();
  gtk_window_destroy (GTK_WINDOW (win));
}


static void
draw_func (GtkDrawingArea *drawing_area, cairo_t *cr, int width, int height, gpointer user_data) {
  if (! draw_function_switch)
    return;
  if (! run(drawing_area, cr, width, height, user_data))
    draw_function_switch = FALSE; /* stop drawing*/
}

static void
app_activate (GApplication *application) {
  gtk_widget_show (GTK_WIDGET (win));
}

static void
app_startup (GApplication *application) {
  GtkApplication *app = GTK_APPLICATION (application);
  GtkBuilder *build;

  build = gtk_builder_new_from_resource ("/com/github/ToshioCP/t2t/t2t.ui");
  win = GTK_WIDGET (gtk_builder_get_object (build, "win"));
  gtk_window_set_application (GTK_WINDOW (win), app);
  tv = GTK_WIDGET (gtk_builder_get_object (build, "tv"));
  da = GTK_WIDGET (gtk_builder_get_object (build, "da"));
  g_object_unref(build);
  g_signal_connect (win, "close-request", G_CALLBACK (close_request_cb), NULL);
/*  g_signal_connect (GTK_DRAWING_AREA (da), "resize", G_CALLBACK (resize_cb), NULL);*/
  g_signal_connect (tv, "change-file", G_CALLBACK (show_filename), NULL);
  gtk_drawing_area_set_draw_func (GTK_DRAWING_AREA (da), draw_func, NULL, NULL);

GdkDisplay *display;

  display = gtk_widget_get_display (GTK_WIDGET (win));
  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_data (provider, "textview {padding: 10px; font-family: monospace; font-size: 12pt;}", -1);
  gtk_style_context_add_provider_for_display (display, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

/* ----- accelerator -----  */
  int i;

  struct {
    const char *action;
    const char *accels[2];
  } action_accels[] = {
    { "win.run", { "<Control>r", NULL } },
/*    { "win.new", { "<Control>n", NULL } },*/
    { "win.open", { "<Control>o", NULL } },
    { "win.save", { "<Control>s", NULL } },
    { "win.close", { "<Control>w", NULL } },
/*    { "win.saveas", { "<Shift><Control>s", NULL } },*/
/*    { "win.pref", { "<Control>p", NULL } },*/
/*    { "win.quit", { "<Control>q", NULL } },*/
  };

  for (i = 0; i < G_N_ELEMENTS(action_accels); i++)
    gtk_application_set_accels_for_action(GTK_APPLICATION(app), action_accels[i].action, action_accels[i].accels);
}

#define APPLICATION_ID "com.github.ToshioCP.t2t"

int
main (int argc, char **argv) {
  GtkApplication *app;
  int stat;

  if (argc > 1) {
    g_printerr ("T2t: No arguments allowed.\n");
    g_printerr ("Usage; t2t\n");
    return 1;
  }
 
  app = gtk_application_new (APPLICATION_ID, G_APPLICATION_FLAGS_NONE);

  g_signal_connect (app, "startup", G_CALLBACK (app_startup), NULL);
  g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);

  stat =g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);
  return stat;
}

