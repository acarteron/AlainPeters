SRCDATA=$(wildcard $(ROOT)/$(DIR_SRC)/data/*.cpp)
DATA=$(SRCDATA:$(ROOT)/$(DIR_SRC)/data/%.cpp=$(ROOT)/$(DIR_OBJ)/data_%.o)

# Compilation from sources (.cpp) to objects (.o)
$(ROOT)/$(DIR_OBJ)/data_%.o: $(ROOT)/$(DIR_SRC)/data/%.cpp
	@echo "Compiling data... : $@"
	@$(GXX) $(CFLAGS_OBJ) -c -o $@ $< 

