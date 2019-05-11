#include <linux/module.h>

static int __init testModuleInit(void){
	printk("Hello World!\n");
	return 0;
}

static void __exit testModuleExit(void){
	printk("Module unloaded. Bye!\n");
}

module_init(testModuleInit);
module_exit(testModuleExit);