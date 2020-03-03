obj-m := cdev_test.o

SRC := $(shell pwd)

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC)/src

modules_install:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC)/src modules_install

clean:
	find . -name '*.o' -delete
	rm -f *.o *~ core .depend .*.cmd *.ko *.mod.c
	rm -f Module.markers Module.symvers modules.order
	rm -rf .tmp_versions Modules.symvers
