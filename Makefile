KERNEL_SRC_DIR := /usr/src/linux-headers-`uname -r`
#EXTRA_CFLAGS = -m32


obj-m := ./cache.o

.PHONY: all clean doc

all:
	make -C $(KERNEL_SRC_DIR) M=$(CURDIR) modules

clean:
	make -C $(KERNEL_SRC_DIR) M=$(CURDIR) clean
	rm -rf ./doc

doc:
	doxygen ./Doxyfile
