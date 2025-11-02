obj-m += kurth4cker.o

KERNEL_OBJECT = kurth4cker.ko
SOURCES = kurth4cker.c
KERNEL_VERSION = `uname -r`

all: $(KERNEL_OBJECT) app

$(KERNEL_OBJECT): $(SOURCES)
	make -C /lib/modules/$(KERNEL_VERSION)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(KERNEL_VERSION)/build M=$(PWD) clean

tags:
	make -C /lib/modules/$(KERNEL_VERSION)/build M=$(PWD) tags
