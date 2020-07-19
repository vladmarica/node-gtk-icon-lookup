GCC_FLAGS=-std=c11 -Wall -Wextra
LIBS=$(shell pkg-config --cflags --libs gtk+-3.0)
all: cli

cli: cli.c gtk_icon_lookup.c
	gcc $(GCC_FLAGS) -o cli.o -c cli.c $(LIBS)
	gcc $(GCC_FLAGS) -o gtk_icon_lookup.o -c gtk_icon_lookup.c $(LIBS)
	gcc $(GCC_FLAGS) -o gtk_icon_lookup_tool cli.o gtk_icon_lookup.o $(LIBS)