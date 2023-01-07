SRC = ../v2c/v2c_main.cpp NuV2C_parseoptions.cpp NuV2Cexpr.cpp ../v2c/expression_datatype.cpp

OBJ+= $(CBMC)/src/ansi-c/expr2c$(OBJEXT) \
      $(CBMC)/src/ansi-c/c_qualifiers$(OBJEXT) \
      $(CBMC)/src/ansi-c/c_types$(OBJEXT) \
      $(CBMC)/src/big-int/big-int$(LIBEXT) \
      $(CBMC)/src/langapi/langapi$(LIBEXT) \
      $(CBMC)/src/util/util$(LIBEXT) \
			$(HW_CBMC)/src/verilog/verilog$(LIBEXT)
        
include ../config.inc

INCLUDES= -I $(CBMC)/src -I ../
INCLUDES= -I $(CBMC)/src -I $(HW_CBMC)/src

LIBS =

all: NuV2C$(EXEEXT)

###############################################################################

NuV2C$(EXEEXT): $(OBJ)
	$(LINKBIN)

.PHONY: v2c-mac-signed

v2c-mac-signed: v2c$(EXEEXT)
	strip v2c$(EXEEXT) ; codesign -v -s $(OSX_IDENTITY) v2c$(EXEEXT)
