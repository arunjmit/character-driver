#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>

dev_t dev;
struct cdev *cdev_new;


static int my_cdev_open(struct inode *inode, struct file *file) {
	printk(KERN_INFO "My cdev open\n");
	return 0;
}


static int my_cdev_release(struct inode *inode, struct file *file) {
	printk(KERN_INFO "My cdev close\n");
	return 0;
}

static ssize_t my_cdev_read(struct file *file, char __user *data, size_t size, loff_t *offset) {
	printk(KERN_INFO "My cdev read\n");	
	return 0;
}

static ssize_t my_cdev_write(struct file *file, const char __user *data, size_t size, loff_t *offset) {
	printk(KERN_INFO "My cdev write\n");
	return size;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = my_cdev_open,
	.read = my_cdev_read,
	.release = my_cdev_release,
	.write = my_cdev_write,
};


static int __init my_cdev_init(void) {

	int ret;

	printk(KERN_INFO "my cdev init\n");

	ret = alloc_chrdev_region(&dev, 0, 1, "my_cdev");

	if (ret < 0) {
		printk(KERN_ERR "alloc_chardev_region failed\n");
		goto fail_alloc_region;
	}

	printk(KERN_INFO "major:%d, minor:%d\n", MAJOR(dev), MINOR(dev));
	
	cdev_new = cdev_alloc();

	if (!cdev_new) {
		printk(KERN_ERR "cdev_alloc failed\n");
		goto fail_alloc;
       
	}	

	cdev_init(cdev_new, &fops);

	ret = cdev_add(cdev_new, dev, 1);
	if (ret < 0) {
		printk(KERN_ERR "cdev_add failed\n");
		goto fail_add;
	}
	printk(KERN_INFO "my cdev init 3 %d\n", ret);

	return 0;

fail_add:
 fail_alloc:
	unregister_chrdev_region(dev, 1);
	
 fail_alloc_region:

	return -1;
	
}


static void __exit my_cdev_exit (void) {
	printk(KERN_INFO "my cdev exit\n");
	cdev_del(cdev_new);
	unregister_chrdev_region(dev, 1);
}

MODULE_LICENSE("GPL");
module_init(my_cdev_init);
module_exit(my_cdev_exit);
