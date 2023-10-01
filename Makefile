# MAKE TEMPLATE 06-02-2020 1
# MAKE TEMPLATE 03-11-2021 1.1
# MAKE TEMPLATE 05-22-2021 1.2
# MAKE TEMPLATE 07-07-2021 1.3

# RUN BEFORE autoreconf -ivfm
# RUN BEFORE autoreconf -i

MAKE_TEMPLATE = 1.3;
BUILD_VERSION = 0.1.0

# prefix = /usr/local
# prefix = /usr/local
# mandir = $(prefix)/share/man
# man1dir = $(mandir)/man1

# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -std=c++11
# lib settings
# LDFLAGS = -static -lcppunit -L/usr/local/lib/
# INCLUDES = -I/usr/local/include/cppunit/

# Makefile settings - Can be customized.
APPNAME = streamycpp
EXT = cpp
ROOTDIR  = .
BUILDDIR = ./build
SRCDIR = $(ROOTDIR)/src
OBJDIR = ./build

#debug: CXXFLAGS += -DDEBUG -ggdb

all: streamy streamy.so streamy.a

streamy: streamy.o
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/main.cpp -o $(BUILDDIR)/main.o	
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/main.o $(BUILDDIR)/streamy.o -o $(BUILDDIR)/streamy

streamy.so: streamy.o
	$(CXX) $(CXXFLAGS) --shared $(BUILDDIR)/streamy.o -o $(BUILDDIR)/streamy.so

streamy.a: streamy.o
	ar rvs $(BUILDDIR)/streamy.a $(BUILDDIR)/streamy.o

streamy.o:
	$(CXX) $(CXXFLAGS) -fPIC -c $(SRCDIR)/streamy.cpp -o $(BUILDDIR)/streamy.o	

# delete object files & app executable
.PHONY: clean
clean:
	-rm ./build/*	


# Streamy-cpp Make
# Fri Sep 29 11:01:50 AM CDT 2023
# Version 0.0.1

# CC       = gcc -g
# LEX      = flex -i -I 
# YACC     = bison -d -y

# BUILD=./build

# all: streamy streamy-cpp poc1

# streamy-cpp: streamy-cpp.yy.c
# 	gcc $(BUILD)/streamy-cpp.yy.c -ll -o $(BUILD)/streamy-cpp

# poc1: poc1.yy.c
# 	gcc $(BUILD)/poc1.yy.c -ll -o $(BUILD)/poc1

# poc1.yy.c:
# 	$(LEX) -o $(BUILD)/poc1.yy.c poc1.l

# streamy: streamy.yy.c
# 	gcc $(BUILD)/streamy.yy.c -ll -o $(BUILD)/streamy

# streamy-cpp.yy.c:
# 	flex -o ./build/streamy-cpp.yy.c streamy-cpp.l

# streamy.yy.c:
# 	flex -o $(BUILD)/streamy.yy.c streamy.l

# eof:	eof_rules.l
# 	$(LEX)  eof_rules.l
# 	$(CC)   lex.yy.c -o eof -ll

# .PHONY: clean
# clean:
# 	-rm $(BUILD)/*
