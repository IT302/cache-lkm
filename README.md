# README #

### What is this repository for? ###

* Linux loadable kernel module disables caches on certain Intel processors. 

### How do I get set up? ###

* Run `make` to build.  Make sure you have kernel headers installed on your system.
* Run `sudo  insmod cache.ko` to load module
* Check kernel log to see if caches has been disabled. The module prints the contents of CR0. See Intel Software Developer Manual for the right value.
* Run `sudo rmmod cache`  to enable caches.