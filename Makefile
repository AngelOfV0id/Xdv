CC=gcc
SOURCE=xdv.c
TARGET=xdv.exe
VERSION=\"1.2\"
DEFINES=-DVERSION=$(VERSION)
ARCH=-m32
LIBS=-lshell32
CCFLAGS=-O2 $(ARCH) $(LIBS) $(DEFINES)

all:
	$(CC) $(SOURCE) $(CCFLAGS) -o $(TARGET)