#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>

#include "log.h"

#define LOG_TAG "test_driver "

static int test_open(struct inode *, struct file *);

#define TEST_MAJOR 100
#define TEST_MINOR 0


static int ret;

static struct test_dev {
    dev_t dev_num;
    struct cdev *cdevp;
} test_dev;

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = NULL,
    .read = NULL,
    .write = NULL,
    .unlocked_ioctl = NULL
};


static struct class *test_driver_class = NULL;
static struct device *test_driver_device = NULL;


static int test_init(void)
{
    test_dev.dev_num = MKDEV(TEST_MAJOR, TEST_MINOR);
    test_dev.cdevp = cdev_alloc();
    ret = register_chrdev_region(test_dev.dev_num, 1, "test_driver");
    LOGD(LOG_TAG, "ret = %d\n", ret);
    if (ret) {
        LOGD(LOG_TAG, "ret = %d\n", ret);
        return -EBUSY;
    }
    cdev_init(test_dev.cdevp, &fops);
    cdev_add(test_dev.cdevp, test_dev.dev_num, 1);
    test_driver_class = class_create(THIS_MODULE, "test_driver_class");
    if (!test_driver_class) {
        LOGD(LOG_TAG, "class_create failed!\n");
        return -1;
    }
    test_driver_device = device_create(test_driver_class, NULL, test_dev.dev_num, 
                                        NULL, "test_dev");
    if(!test_driver_device) {
        LOGD(LOG_TAG, "device_create failed!\n");
        return -1;
    }

	return 0;
}

static void test_exit(void)
{
    cdev_del(test_dev.cdevp);
    unregister_chrdev_region(test_dev.dev_num, 1);
    device_unregister(test_driver_device);
    class_destroy(test_driver_class);
}

static int test_open(struct inode *ip, struct file *fp)
{
    
    return 0;
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nick");
