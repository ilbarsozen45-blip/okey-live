.PHONY: all bootloader kernel modules iso clean

all: bootloader kernel modules

bootloader:
	$(MAKE) -C bootloader

kernel:
	$(MAKE) -C kernel

modules:
	$(MAKE) -C lib
	$(MAKE) -C drivers
	$(MAKE) -C fs
	$(MAKE) -C ui
	$(MAKE) -C apps

iso: all
	bash scripts/build_iso.sh

clean:
	$(MAKE) -C bootloader clean
	$(MAKE) -C kernel clean
	$(MAKE) -C lib clean
	$(MAKE) -C drivers clean
	$(MAKE) -C fs clean
	$(MAKE) -C ui clean
	$(MAKE) -C apps clean
	rm -rf out iso_root/ILBARSDOWS.iso
