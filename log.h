#ifndef _LOG_H
#define _LOG_H

#define LOGD(LOG_TAG, fmt, arg...) printk(KERN_WARNING LOG_TAG fmt, ##arg)

#endif