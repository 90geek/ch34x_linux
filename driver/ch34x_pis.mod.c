#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0xc79d2779, "module_layout" },
	{ 0xa2bf42c9, "usb_deregister" },
	{ 0xacc38f46, "usb_register_driver" },
	{ 0xcf765838, "usb_register_dev" },
	{ 0x831d0d8a, "usb_get_dev" },
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0x26c2e0b5, "kmem_cache_alloc_trace" },
	{ 0x8537dfba, "kmalloc_caches" },
	{ 0x26948d96, "copy_user_enhanced_fast_string" },
	{ 0xafb8c6ff, "copy_user_generic_string" },
	{ 0x72a98fdb, "copy_user_generic_unrolled" },
	{ 0x944839cc, "usb_deregister_dev" },
	{ 0x1f5311b0, "usb_autopm_put_interface" },
	{ 0x70fa804b, "usb_autopm_get_interface" },
	{ 0x165b145c, "ex_handler_refcount" },
	{ 0xf4824002, "usb_find_interface" },
	{ 0x6d334118, "__get_user_8" },
	{ 0xb8e7ce2c, "__put_user_8" },
	{ 0xb9daafa, "usb_free_urb" },
	{ 0x3024bcaa, "usb_unanchor_urb" },
	{ 0xb4055ce3, "usb_submit_urb" },
	{ 0x8599c50f, "usb_anchor_urb" },
	{ 0x36cf406c, "usb_alloc_coherent" },
	{ 0xcb64db4d, "usb_alloc_urb" },
	{ 0x47941711, "_raw_spin_lock_irq" },
	{ 0x81b395b3, "down_interruptible" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0x843526fb, "usb_control_msg" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0xb44ad4b3, "_copy_to_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x912bbf55, "usb_bulk_msg" },
	{ 0xeb233a45, "__kmalloc" },
	{ 0x962c8ae1, "usb_kill_anchored_urbs" },
	{ 0x407af304, "usb_wait_anchor_empty_timeout" },
	{ 0x2ab7989d, "mutex_lock" },
	{ 0x37a0cba, "kfree" },
	{ 0x80dad909, "usb_put_dev" },
	{ 0xc5850110, "printk" },
	{ 0xcf2a6966, "up" },
	{ 0x36170606, "usb_free_coherent" },
	{ 0xdbf17652, "_raw_spin_lock" },
	{ 0x409bcb62, "mutex_unlock" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x344fd44f, "pv_ops" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("usb:v1A86p5512d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "C9D864C3C4F21B5E6001ECC");
