SRCMAIN=$(wildcard $(ROOT)/$(DIR_SRC)/main/*.cpp)
MAIN=$(SRCMAIN:$(ROOT)/$(DIR_SRC)/main/%.cpp=$(ROOT)/$(DIR_OBJ)/main_%.o)

# Compilation from sources (.cpp) to objects (.o)
$(ROOT)/$(DIR_OBJ)/main_%.o: $(ROOT)/$(DIR_SRC)/main/%.cpp
	@echo "Compiling ... : $@"
	@$(GXX) -I $(ROOT)/$(DIR_HDR) -c -o $@ $< $(CFLAGS_OBJ)
