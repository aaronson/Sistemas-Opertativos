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
	{ 0x58334a4a, "module_layout" },
	{ 0xa37030ed, "remove_proc_entry" },
	{ 0xd4ee26b3, "misc_register" },
	{ 0xb72397d5, "printk" },
	{ 0x94d32a88, "__tracepoint_module_get" },
	{ 0xb4390f9a, "mcount" },
	{ 0x31c3dff4, "module_put" },
	{ 0x4f75bd40, "create_proc_entry" },
	{ 0x4dde9e55, "misc_deregister" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "DFAB99BAE222611BF1AC185");
