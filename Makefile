MODNAME=mod_global_vars.so
MODOBJ=mod_global_vars.o
MODCFLAGS=-Wall -Werror
MODLDFLAGS=

FS_INCLUDES ?=/usr/local/freeswitch/include/freeswitch
FS_MODULES ?=/usr/local/freeswitch/mod

CC=gcc
CFLAGS=-fPIC -g -ggdb -I$(FS_INCLUDES) $(MODCFLAGS)
LDFLAGS=$(MODLDFLAGS)
 
.PHONY: all
all: $(MODNAME)
 
$(MODNAME): $(MODOBJ)
	$(CC) -shared -o $@ $(MODOBJ) $(LDFLAGS)

.c.o: $<
	$(CC) $(CFLAGS) -o $@ -c $<
 
.PHONY: clean
clean:
	rm -f $(MODNAME) $(MODOBJ)
 
.PHONY: install
install: $(MODNAME)
	install $(MODNAME) $(FS_MODULES)
