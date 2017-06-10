#!/usr/bin/make -f
include ./standard_def.mk

EXEC=$(ROOT)/$(DIR_BIN)/AlainPeters

all: createdirectories $(EXEC)

createdirectories:
	@mkdir -p $(DIR_OBJ) $(DIR_BIN) $(DIR_LIB)

#ifeq ($(MAKECMDGOALS),all)
-include $(ROOT)/$(DIR_SRC)/src.mk
#endif



.PHONY: clean doc lib

LIBR=$(ROOT)/$(DIR_LIB)/AlainPeters.so

lib:	createdirectories $(LIBR)

ifeq ($(MAKECMDGOALS),lib)
-include $(ROOT)/$(DIR_SRC)/libsrc.mk
endif

doc:
	@echo -n "Generation de la DOC ... "
	@mkdir -p $(DIR_DOC)
	@doxygen 
	@echo "OK."

clean:
	@echo "Cleaning Project"
	@rm -rf $(DIR_OBJ) $(DIR_BIN) $(DIR_DOC)

raz: 
	@echo "Cleaning Project++"
	@rm -rf $(DIR_OBJ) $(DIR_LIB) $(DIR_BIN) $(DIR_DOC) $(DIR_PLO) $(DIR_OUT)
