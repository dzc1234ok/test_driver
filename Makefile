KERNEL_DIR :=/lib/modules/$(shell uname -r)/build
CC :=gcc

all:
	make -C $(KERNEL_DIR) M=$(shell pwd) modules

clean:
	make -C $(KERNEL_DIR) M=$(shell pwd) clean     
#	rm -rf *.ko *.o *.mod.* modules* Module*

obj-m =driver.o