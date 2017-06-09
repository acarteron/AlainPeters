SRCHTM=$(wildcard $(ROOT)/$(DIR_SRC)/html/*.cpp)
HTM=$(SRCHTM:$(ROOT)/$(DIR_SRC)/html/%.cpp=$(ROOT)/$(DIR_OBJ)/htm_%.o)

# Compilation from sources (.cpp) to objects (.o)
$(ROOT)/$(DIR_OBJ)/htm_%.o: $(ROOT)/$(DIR_SRC)/html/%.cpp
	@echo "Compiling html... : $@"
	@$(GXX) $(CFLAGS_OBJ) -c -o $@ $< 

