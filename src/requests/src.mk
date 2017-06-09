SRCREQ=$(wildcard $(ROOT)/$(DIR_SRC)/requests/*.cpp)
REQ=$(SRCREQ:$(ROOT)/$(DIR_SRC)/requests/%.cpp=$(ROOT)/$(DIR_OBJ)/req_%.o)

# Compilation from sources (.cpp) to objects (.o)
$(ROOT)/$(DIR_OBJ)/req_%.o: $(ROOT)/$(DIR_SRC)/requests/%.cpp
	@echo "Compiling requests... : $@"
	@$(GXX) $(CFLAGS_OBJ) -c -o $@ $< 

