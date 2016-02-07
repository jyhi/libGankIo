# Gank.io Fetcher
# Copyright (C) 2016 Junde Yi <lmy441900@gmail.com>

HOST = x86_64-w64-mingw32
CC   = ${HOST}-gcc
CXX  = ${HOST}-g++
LD   = ${HOST}-ld

CFLAGS   = -ggdb3 -Wall -std=c99
CXXFLAGS =
LDFLAGS  =
PKGCFG   = $(shell pkg-config --cflags --libs libcurl json-c)

.PHONY: all clean

all: gank-io-fetcher.exe

gank-io-fetcher.exe: gank-io-fetcher.c
	${CC} ${CFLAGS} -o $@ $< ${PKGCFG}

clean:
	rm *.exe
