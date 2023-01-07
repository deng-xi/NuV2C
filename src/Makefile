SUBDIRS = NuV2C
all: NuV2C

.PHONY: $(SUBDIRS)
.PHONY: clean

$(SUBDIRS):
	$(MAKE) -C ../cbmc/src;
	$(MAKE) -C ../hw-cbmc/src;
	$(MAKE) -C $@; mv $@/NuV2C ../bin/NuV2C
	
# Dependencies

#v2c: verilog

clean: $(patsubst %, %_clean, $(SUBDIRS))

$(patsubst %, %_clean, $(SUBDIRS)):
	#make clean -C ../cbmc/src; \
	#make clean -C ../hw-cbmc/src; \
	if [ -e $(patsubst %_clean, %, $@)/. ] ; then \
	        $(MAKE) $(MAKEARGS) -C $(patsubst %_clean, %, $@) clean ; \
	fi

