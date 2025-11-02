export HOSTCC = cc
export CC = cc

obj-m += kurth4cker.o

MODULE = kurth4cker.ko
SOURCES = kurth4cker.c
KERNEL_VERSION = `uname -r`
KERNEL_SOURCE_DIR = /lib/modules/$(KERNEL_VERSION)/build

app_SOURCES = main.c

all: $(MODULE) app

$(MODULE): $(SOURCES)
	make -C $(KERNEL_SOURCE_DIR) M=$(PWD) modules

app: $(app_SOURCES) kurth4cker.h
	$(HOSTCC) $(CFLAGS) $(LDFLAGS) -o $@ $(app_SOURCES) $(LDLIBS)

clean:
	make -C $(KERNEL_SOURCE_DIR) M=$(PWD) clean
	rm -f app

.PHONY: tags
tags:
	make -C $(KERNEL_SOURCE_DIR) M=$(PWD) tags
	ctags -a -R .
