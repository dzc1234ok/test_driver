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

static int test_init(void)
{
	dev_no = MKDEV(TEST_MAJOR, TEST_MINOR);
	ret = register_chrdev_region(dev_no, 1, "test_dirver");
	LOGD(LOG_TAG, "ret = %d\n", ret);
	if (ret) {
		LOGD(LOG_TAG, "ret = %d\n", ret);
		return -EBUSY;
	}
	return 0;
}

static void test_exit(void)
{
	unregister_chrdev_region(dev_no, 1);
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");