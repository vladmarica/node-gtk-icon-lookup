{
  "targets": [
    {
      "target_name": "gtk_icon_lookup_native",
      "cflags": [ "-Wall", "-Wextra" ],
      "sources": ["src/native/gtk_icon_napi.c", "src/native/gtk_icon_lookup.c"],
      "include_dirs": [
        "<!@(pkg-config --cflags-only-I gtk+-3.0 | sed s/-I//g)"
      ],
      "libraries": [
        "<!@(pkg-config --libs gtk+-3.0)"
      ]
    }
  ]
}
