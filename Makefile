# Gank.io Fetcher
# Copyright (C) 2016 Junde Yi <lmy441900@gmail.com>

HOST = x86_64-w64-mingw32
CC   = ${HOST}-gcc
CXX  = ${HOST}-g++
LD   = ${HOST}-ld

CFLAGS   = -municode -ggdb3 -Wall
CXXFLAGS =
LDFLAGS  =
PKGCFG   = $(shell pkg-config --cflags --libs libcurl json-c)

all: gank-io-fetcher.exe

gank-io-fetcher.exe: gank-io-fetcher.c
	${CC} ${CFLAGS} -o $@ $< ${PKGCFG}
