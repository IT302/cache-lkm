#include <linux/init.h>
#include <linux/module.h>
#include <linux/smp.h>

// Works on Intel(R) Xeon(R) CPU  X5550
// Developed based on this converstation
// https://stackoverflow.com/questions/21265785/enable-disable-cache-on-intel-64bit-machine-cd-bit-always-set

static void cache_off_impl(void *ignored) {

    printk(KERN_WARNING "cache: disabling   caches.\n");
    __asm__ __volatile__("pushq %%rax\n\t"
                         "movq %%cr0,%%rax\n\t"
                         "orq $0x40000000,%%rax\n\t"
                         "movq %%rax,%%cr0\n\t"
                         "wbinvd\n\t"
                         "popq  %%rax" :);
}

static void cache_on_impl(void *ignored) {
    printk(KERN_WARNING "cache: enabling caches.\n");
    __asm__ __volatile__("pushq %%rax\n\t"
                         "movq %%cr0,%%rax\n\t"
                         "andq $0xffffffffbfffffff,%%rax\n\t"
                         "movq %%rax,%%cr0\n\t"
                         "popq  %%rax" :);

}

static void show_cr0(void *ignored) {
  long  long int cr0;
  __asm__ __volatile__("pushq %%rax\n\t"
                       "movq %%cr0, %%rax\n\t"
                       "movq %%rax, %0\n\t"
                       "popq %%rax"
                       : "=r"(cr0)
                       :
                       :);
  printk(KERN_WARNING "cache: current cache status  cr0=%#018llx\n", cr0);
}

static int cache_off(void) {

  smp_call_function(cache_off_impl, NULL, 1);
  cache_off_impl(NULL);
  show_cr0(NULL); // TODO: call on every core

  return 0;
}

static void cache_on(void) {
  cache_on_impl(NULL);
  smp_call_function(cache_on_impl, NULL, 0);
  show_cr0(NULL); // TODO: call on every core
}

MODULE_AUTHOR("Geoffrey Ndu");
MODULE_LICENSE("GPL");

module_init(cache_off);
module_exit(cache_on);
