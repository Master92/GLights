AUTOMAKE_OPTIONS = foreign

CFLAGS=-Wall -I./include `pkg-conf --cflags gtkmm-3.0`
LDFLAGS=-L`pkg-conf --libs gtkmm-3.0`

bin_PROGRAMS = GLights
GLights_SOURCES = main.cpp
