SRCFILE=$(wildcard $(ROOT)/$(DIR_SRC)/files/*.cpp)
FILE=$(SRCFILE:$(ROOT)/$(DIR_SRC)/files/%.cpp=$(ROOT)/$(DIR_OBJ)/file_%.o)

# Compilation from sources (.cpp) to objects (.o)
$(ROOT)/$(DIR_OBJ)/file_%.o: $(ROOT)/$(DIR_SRC)/files/%.cpp
	@echo "Compiling ... : $@"
	@$(GXX) $(CFLAGS_OBJ) -c -o $@ $< 

