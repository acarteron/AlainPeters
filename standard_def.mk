#### Common variables for Makefiles

## Directories
ROOT=$(shell pwd)
DIR_BIN=bin
DIR_SRC=src
DIR_OBJ=obj
DIR_LIB=lib
DIR_HDR=includes
DIR_DOC=doc
DIR_IN=libAlainPeters

## Compilation
GXX=g++
# Flags for linking
CFLAGS= -ldl -lPocoFoundation -lPocoNet -lPocoJSON -lPocoXML  -lPocoUtil -lPocoMongoDB
# Flags for objects
CFLAGS_OBJ=-I $(ROOT)/$(DIR_HDR) -O2 -Wall -Wextra -std=c++11 
# Flags for libraries objects
CFLAGS_DYNAMIC_LIBS_OBJ=-fPIC
# Flags for libraries linkins
CFLAGS_DYNAMIC_LIBS=-shared -Wl,-soname,libAlainPeters.so

