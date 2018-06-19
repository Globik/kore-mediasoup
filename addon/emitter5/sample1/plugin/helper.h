#include <limits.h>
#include <glib.h>
extern gint stop_signal;//=0;
extern volatile gint stop;//=0;

void j_handle_signal(int);
gpointer j_sess_watchdog(gpointer);