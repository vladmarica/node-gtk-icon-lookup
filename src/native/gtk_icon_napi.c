#include <gtk/gtk.h>
#include <node_api.h>
#include <stdio.h>
#include "gtk_icon_lookup.h"

#define DEFAULT_ICON_LOOKUP_SIZE 32

int32_t get_napi_int(napi_env env, napi_value value) {
  int32_t result; 
  napi_status status = napi_get_value_int32(env, value, &result);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to convert N-API int to C int");
  }

  return result;
}

/*
 * Converts a N-API (JavaScript) string to a null-terminated C string. This function will
 * throw an N-API error on a number of conditions, such as if the given napi_value does not represent
 * a string or if memory allocation fails.
 * 
 * The returned string is allocated on the heap and should be freed when not needed anymore.
 */
char *get_napi_string(napi_env env, napi_value value) {
  size_t string_length;
  napi_status status = napi_get_value_string_utf8(env, value, NULL, 0, &string_length);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed get string length");
    return NULL;
  }

  char *string = (char *) malloc((string_length + 1) * sizeof(char));
  if (string == NULL) {
    napi_throw_error(env, NULL, "Failed to allocate memory for string");
    return NULL;
  }

  status = napi_get_value_string_utf8(env, value, string, string_length + 1, NULL);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed convert N-API string to C string");
    return NULL;
  }

  return string;
}

napi_value _napi_get_icon_filename(napi_env env, napi_callback_info info) {
  size_t argc = 2;
  napi_value args[argc];

  napi_status status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to get callback info");
    return NULL;
  }

  if (argc != 1 && argc != 2) {
    napi_throw_error(env, NULL, "Invalid number of arguments, expected 1 or 2");
    return NULL;
  }

  napi_valuetype icon_name_type;
  napi_typeof(env, args[0], &icon_name_type);
  if (icon_name_type != napi_string) {
    napi_throw_error(env, NULL, "Icon name must be a string");
    return NULL;
  }

  int32_t icon_size = DEFAULT_ICON_LOOKUP_SIZE;

  // If 2 arguments were passed, treat the second as the icon size request.
  if (argc == 2) {
    napi_valuetype icon_size_type;
    napi_typeof(env, args[1], &icon_size_type);

    if (icon_size_type == napi_number) {
      icon_size = get_napi_int(env, args[1]);
    }
    else if (icon_size_type != napi_undefined) {
      napi_throw_error(env, NULL, "Icon size must be a number");
      return NULL;
    }
  }

  char *icon_name = get_napi_string(env, args[0]);
  const char *icon_filename = get_icon_filename(icon_name, icon_size);
  free(icon_name);

  if (icon_filename == NULL) {
    return NULL;
  }

  napi_value icon_filename_napi;
  status = napi_create_string_utf8(env, icon_filename, NAPI_AUTO_LENGTH, &icon_filename_napi);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to convert icon filename to N-API string");
    return NULL;
  }

  return icon_filename_napi;
}

napi_value init(napi_env env, napi_value exports) {
  // Attempt to initialize the GTK environment, throwing an error if it fails
  gboolean gtk_init_result = gtk_init_check(0, NULL);
  if (gtk_init_result == FALSE) {
    napi_throw_error(env, NULL, "Failed to initialize GTK - no windowing system found");
  }

  napi_status status;

  // Create the 'getIconFileName' wrapped native function
  napi_value get_icon_func;
  status = napi_create_function(env, NULL, 0, _napi_get_icon_filename, NULL, &get_icon_func);
  if (status != napi_ok) napi_throw_error(env, NULL, "Failed to wrap native function: _napi_get_icon_filename");

  status = napi_set_named_property(env, exports, "getIconFileName", get_icon_func);
  if (status != napi_ok) napi_throw_error(env, NULL, "Failed to set export property: getIconFileName");

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init);
