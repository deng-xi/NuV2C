SUBDIRS = v2c
all: v2c

.PHONY: $(SUBDIRS)
.PHONY: clean

$(SUBDIRS):
	$(MAKE) -C $@; cp $@/v2c ../bin/
#	$(MAKE) -C ../cbmc/src; $(MAKE) -C ../hw-cbmc/src; $(MAKE) -C $@; cp $@/v2c ../bin/
# Dependencies

#v2c: verilog

clean: $(patsubst %, %_clean, $(SUBDIRS))

$(patsubst %, %_clean, $(SUBDIRS)):
	#make clean -C ../cbmc/src; \
	#make clean -C ../hw-cbmc/src; \
	if [ -e $(patsubst %_clean, %, $@)/. ] ; then \
	        $(MAKE) $(MAKEARGS) -C $(patsubst %_clean, %, $@) clean ; \
	fi

