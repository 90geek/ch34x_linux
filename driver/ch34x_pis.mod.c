#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xee9edca1, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xe99154ca, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x8b114d0e, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0xc2e5e32f, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0x98cf60b3, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0xd4073672, __VMLINUX_SYMBOL_STR(down_interruptible) },
	{ 0x3ba1c4de, __VMLINUX_SYMBOL_STR(usb_register_dev) },
	{ 0xe8170541, __VMLINUX_SYMBOL_STR(usb_get_dev) },
	{ 0xc839c1d4, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xfb578fc5, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x48633762, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0xdfdcd0e4, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xa08b42b6, __VMLINUX_SYMBOL_STR(usb_autopm_put_interface) },
	{ 0x747e967c, __VMLINUX_SYMBOL_STR(usb_deregister_dev) },
	{ 0xc8a80b48, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x58c94034, __VMLINUX_SYMBOL_STR(usb_autopm_get_interface) },
	{ 0xb0fb8a33, __VMLINUX_SYMBOL_STR(usb_find_interface) },
	{ 0x14750036, __VMLINUX_SYMBOL_STR(usb_kill_anchored_urbs) },
	{ 0x4c9ef059, __VMLINUX_SYMBOL_STR(usb_wait_anchor_empty_timeout) },
	{ 0x52b701fd, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xad42a879, __VMLINUX_SYMBOL_STR(usb_put_dev) },
	{ 0x6231bd52, __VMLINUX_SYMBOL_STR(usb_unanchor_urb) },
	{ 0x713eddc, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0xfc281b97, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0xa48f5628, __VMLINUX_SYMBOL_STR(usb_anchor_urb) },
	{ 0xc29e1b01, __VMLINUX_SYMBOL_STR(usb_alloc_coherent) },
	{ 0xf07eaed7, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0x4fcf188b, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xca7b5eeb, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irq) },
	{ 0x3bfa326, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irq) },
	{ 0x675bad55, __VMLINUX_SYMBOL_STR(up) },
	{ 0x310caf24, __VMLINUX_SYMBOL_STR(usb_free_coherent) },
	{ 0xbc36dc6a, __VMLINUX_SYMBOL_STR(_raw_spin_unlock) },
	{ 0x3bf72f7e, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x5397c01e, __VMLINUX_SYMBOL_STR(__copy_user) },
	{ 0x4fb814de, __VMLINUX_SYMBOL_STR(usb_bulk_msg) },
	{ 0xd2b09ce5, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x217012df, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xf5f6ce26, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v1A86p5512d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_INFO(rhelversion, "7.5");
#ifdef RETPOLINE
	MODULE_INFO(retpoline, "Y");
#endif
