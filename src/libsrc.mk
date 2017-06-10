SRC_LIB=$(wildcard $(ROOT)/$(DIR_SRC)/*.cpp)
OBJ_LIB=$(SRC:$(ROOT)/$(DIR_SRC)/%.cpp=$(ROOT)/$(DIR_OBJ)/%.o)

-include $(ROOT)/$(DIR_SRC)/files/libsrc.mk
-include $(ROOT)/$(DIR_SRC)/data/libsrc.mk
-include $(ROOT)/$(DIR_SRC)/database/libsrc.mk

# Compilation of the program
$(LIBR): $(DBS_LIB) $(FIL_LIB) $(OBJ_LIB) $(DATA_LIB)  #$(DYNAMIC_LIBS:%=$(ROOT)/$(DIR_SRC)/$(DIR_IN)/%.so)
	@echo "Linking lib ..... : $@"
	@$(GXX) $(CFLAGS_DYNAMIC_LIBS) -o $@ $^ $(CFLAGS) 

# Compilation from sources (.cpp) to objects (.o)
$(ROOT)/$(DIR_OBJ)/%.o: $(ROOT)/$(DIR_SRC)/%.cpp
	@echo "Compiling lib target ... : $@"
	@$(GXX) $(CFLAGS_OBJ) $(CFLAGS_DYNAMIC_LIBS_OBJ)  -c -o $@ $<
