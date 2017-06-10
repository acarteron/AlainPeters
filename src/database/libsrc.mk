SRCDBS=$(wildcard $(ROOT)/$(DIR_SRC)/database/*.cpp)
DBS_LIB=$(SRCDBS:$(ROOT)/$(DIR_SRC)/database/%.cpp=$(ROOT)/$(DIR_OBJ)/dbs_%.o)

# Compilation from sources (.cpp) to objects (.o)
$(ROOT)/$(DIR_OBJ)/dbs_%.o: $(ROOT)/$(DIR_SRC)/database/%.cpp
	@echo "Compiling lib target ... : $@"
	@$(GXX) $(CFLAGS_DYNAMIC_LIBS_OBJ) $(CFLAGS_OBJ) -c -o $@ $< 

