REGIONS = ntscu
.PHONY: all install clean $(REGIONS)

all: $(REGIONS)

$(REGIONS):
	$(MAKE) -f $(CURDIR)/Makefile.$@

install clean:
	$(MAKE) -f $(CURDIR)/Makefile.ntscu $@
