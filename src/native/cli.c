#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include "gtk_icon_lookup.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: gtk_icon_lookup_tool <name>\n");
    return EXIT_FAILURE;
  }
  
  gboolean result = gtk_init_check(0, NULL);
  if (result == FALSE) {
    printf("Failed to initialize GTK - no windowing system available\n");
    return EXIT_FAILURE;
  }

  const char* icon_filename = get_icon_filename(argv[1], 32);
  if (icon_filename != NULL) {
    printf("%s\n", icon_filename);
  }
  else {
    printf("Could not find icon: %s\n", argv[1]);
  }

  return EXIT_SUCCESS;
}
