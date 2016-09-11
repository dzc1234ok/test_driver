#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>

#include "log.h"

#define LOG_TAG "test_driver "

#define TEST_MAJOR 100
#define TEST_MINOR 0
static dev_t dev_no;
static int ret;

static struct class *test_driver_class = NULL;
static struct device *test_driver_device = NULL;


static int test_init(void)
{
	dev_no = MKDEV(TEST_MAJOR, TEST_MINOR);
	ret = register_chrdev_region(dev_no, 1, "test_driver");
	LOGD(LOG_TAG, "ret = %d\n", ret);
	if (ret) {
		LOGD(LOG_TAG, "ret = %d\n", ret);
		return -EBUSY;
	}
	test_driver_class = class_create(THIS_MODULE, "test_driver_class");
	if (!test_driver_class) {
		LOGD(LOG_TAG, "class_create failed!\n");
		return -1;
	}
	test_driver_device = device_create(test_driver_class, NULL, dev_no,
										NULL, "test_dev");
	if(!test_driver_device) {
		LOGD(LOG_TAG, "device_create failed!\n");
		return -1;
	}

	return 0;
}

static void test_exit(void)
{
	unregister_chrdev_region(dev_no, 1);
	device_unregister(test_driver_device);
	class_destroy(test_driver_class);
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nick");
