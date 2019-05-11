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
	{ 0x7ef7cd24, "module_layout" },
	{ 0x5a34a45c, "__kmalloc" },
	{ 0xa78fb443, "kallsyms_on_each_symbol" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0xe2d5255a, "strcmp" },
	{ 0xea147363, "printk" },
	{ 0x6ae6ff6d, "vmap" },
	{ 0xb4390f9a, "mcount" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x42eee679, "stop_machine" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xcc5005fe, "msleep_interruptible" },
	{ 0xe52947e7, "__phys_addr" },
	{ 0x37a0cba, "kfree" },
	{ 0x94961283, "vunmap" },
	{ 0x236c8c64, "memcpy" },
	{ 0xaffc138f, "__module_address" },
	{ 0xb9db6614, "vmalloc_to_page" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "D251CCC80E96AE553F12502");
