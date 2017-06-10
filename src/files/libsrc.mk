SRCFILE=$(wildcard $(ROOT)/$(DIR_SRC)/files/*.cpp)
FIL_LIB=$(SRCFILE:$(ROOT)/$(DIR_SRC)/files/%.cpp=$(ROOT)/$(DIR_OBJ)/file_%.o)

# Compilation from sources (.cpp) to objects (.o)
$(ROOT)/$(DIR_OBJ)/file_%.o: $(ROOT)/$(DIR_SRC)/files/%.cpp
	@echo "Compiling lib target ... : $@"
	@$(GXX) $(CFLAGS_DYNAMIC_LIBS_OBJ) $(CFLAGS_OBJ) -c -o $@ $< 
