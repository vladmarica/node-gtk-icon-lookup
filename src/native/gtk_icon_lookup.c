#include <gtk/gtk.h>
#include <stdlib.h>
#include "gtk_icon_lookup.h"

const char *get_icon_filename(const char *icon_name, int32_t icon_size) {
  GtkIconTheme *theme = gtk_icon_theme_get_default();
  GtkIconInfo *icon_info = gtk_icon_theme_lookup_icon(theme, icon_name, icon_size, GTK_ICON_LOOKUP_GENERIC_FALLBACK);
  
  if (icon_info == NULL) {
    return NULL;
  }

  return gtk_icon_info_get_filename(icon_info);
}
