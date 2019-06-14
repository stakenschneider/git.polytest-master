#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>	
#include <linux/init.h>	

#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/types.h>

#define SUCCESS 0
#define DEVICE_NAME "chardev"
#define BUF_LEN 80	

 
int device_init(void);
void device_exit(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, char *, size_t, loff_t *);

module_init(device_init);
module_exit(device_exit);

static int Major;
static int Device_Open = 0;	 
				 
static char Message[BUF_LEN];
static char *Message_Ptr;

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};


int device_init(void)
{

        Major = register_chrdev(0, DEVICE_NAME, &fops);

	if (Major < 0) {
	  printk(KERN_ALERT "Registering char device failed with %d\n", Major);
	  return Major;
	}

	printk(KERN_INFO "I was assigned major number %d. To talk to\n", Major);
	printk(KERN_INFO "the driver, create a dev file with\n");
	printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);
	printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
	printk(KERN_INFO "the device file.\n");
	printk(KERN_INFO "Remove the device file and module when done.\n");
	
	return SUCCESS;
}

void device_exit(void)
{
	// Освобождение старшего номера устройства
	unregister_chrdev(Major, DEVICE_NAME);	
	printk(KERN_ALERT "Removing character device /dev/%s c %d 0'.\n", 			DEVICE_NAME, Major);
	return;
}


static int device_open(struct inode *inode, struct file *file)
{
	static int counter = 0;	
	printk(KERN_INFO "Try to open character device /dev/%s c %d 0'.\n", 			DEVICE_NAME, Major);	
	if (Device_Open)
	  return -EBUSY;

	Device_Open++; 
	 sprintf(Message, "I already told you %d times HELLO!\n", counter++);
	Message_Ptr = Message;
	try_module_get(THIS_MODULE);

	return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file)
{
	printk(KERN_ALERT "Try to close character device /dev/%s c %d 0'.\n", 			DEVICE_NAME, Major);
	Device_Open--;	

	module_put(THIS_MODULE);
	return SUCCESS;	
}

static ssize_t device_read(struct file *filp, 
		char *buffer,
		size_t length,
		loff_t * offset)
{
	int bytes_read = 0;
	printk("Try to read character device /dev/%s c %d 0'.\n", DEVICE_NAME, Major);

	if (*Message_Ptr == 0)
		return 0;
	while (length && *Message_Ptr) {
		put_user(*(Message_Ptr++), buffer++);
	  	length--;
	  	bytes_read++;
	}

	printk("Read %d bytes, %d left.\n", bytes_read, length);

	return bytes_read;
}

static ssize_t device_write(struct file *filp, char *buffer, size_t length, loff_t * offset)
{
	int i;
	printk("Try to write (%p, %s, %d).\n", filp, buffer, length);
	for (i = 0; i < length && i < BUF_LEN; i++)
		get_user(Message[i], buffer + i);
	Message_Ptr = Message;
	return i;
}