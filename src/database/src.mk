SRCDBS=$(wildcard $(ROOT)/$(DIR_SRC)/database/*.cpp)
DBS=$(SRCDBS:$(ROOT)/$(DIR_SRC)/database/%.cpp=$(ROOT)/$(DIR_OBJ)/db_%.o)

# Compilation from sources (.cpp) to objects (.o)
$(ROOT)/$(DIR_OBJ)/db_%.o: $(ROOT)/$(DIR_SRC)/database/%.cpp
	@echo "Compiling db... : $@"
	@$(GXX) $(CFLAGS_OBJ) -c -o $@ $< 

