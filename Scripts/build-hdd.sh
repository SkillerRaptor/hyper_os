#!/bin/sh

sh ./build.sh

printf "\n\e[93m === Starting Building HDD === \e[39m\n"

cd ..
mkdir ./build
rm -f ./build/HyperOS.hdd

dd if=/dev/zero bs=1M count=0 seek=64 of=./build/HyperOS.hdd

parted -s ./build/HyperOS.hdd mklabel msdos
parted -s ./build/HyperOS.hdd mkpart primary 1 100%
parted -s ./build/HyperOS.hdd set 1 boot on

echfs-utils -m -p0 ./build/HyperOS.hdd quick-format 32768
echfs-utils -m -p0 ./build/HyperOS.hdd import ./HyperOS.elf boot/HyperOS.elf
echfs-utils -m -p0 ./build/HyperOS.hdd import ./limine.cfg boot/limine.cfg

limine-install ./limine.bin ./build/HyperOS.hdd

printf "\e[92m === Finished Building HDD === \e[39m\n"