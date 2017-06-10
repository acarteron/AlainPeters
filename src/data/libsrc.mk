SRCDATA=$(wildcard $(ROOT)/$(DIR_SRC)/data/*.cpp)
DATA_LIB=$(SRCDATA:$(ROOT)/$(DIR_SRC)/data/%.cpp=$(ROOT)/$(DIR_OBJ)/data_%.o)

# Compilation from sources (.cpp) to objects (.o)
$(ROOT)/$(DIR_OBJ)/data_%.o: $(ROOT)/$(DIR_SRC)/data/%.cpp
	@echo "Compiling lib target ... : $@"
	@$(GXX) $(CFLAGS_DYNAMIC_LIBS_OBJ) $(CFLAGS_OBJ) -c -o $@ $< 
