# Makefile for alex scheduler plugin

AUTOMAKE_OPTIONS = foreign

AM_CXXFLAGS = -fexceptions

PLUGIN_FLAGS = -module -avoid-version --export-dynamic

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/src/common

pkglib_LTLIBRARIES = sched_alex.la

sched_alex_la_SOURCES = \
			alex_wrapper.c \
			alex.c	\
			alex.h
sched_alex_la_LDFLAGS = $(PLUGIN_FLAGS)
