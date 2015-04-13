KXARCH         := l64
KXVER          := 3
QHOME          := /usr/local/lib/q
CC             := gcc
CXX			   := g++
CFLAGS         := -std=c99 -shared -fPIC -O3
FLAGS          := -DKXVER=3 -m64 -march=native
INCLUDES	   := -I. -I..
