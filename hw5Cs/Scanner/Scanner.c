/*
 * Scanner Linux Kernel Module
 * Author: Anton Leslie
 *
 * This module implements a character device that interacts with user-space applications,
 * allowing them to perform read and write operations with support for custom separator characters.
 * The device is capable of handling any data, including binary data with NUL ('\0') characters,
 * treating them like regular data bytes rather than string terminators.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/ioctl.h>

#define DEVICE_NAME "Scanner"
#define DEFAULT_SEPARATORS ",;:.!?\n"

#define SCANNER_MAGIC 's'
#define SCANNER_SET_SEP _IOW(SCANNER_MAGIC, 0, char *)  // IOCTL command for setting separators

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("BSU CS 452 HW4");
MODULE_AUTHOR("<buff@cs.boisestate.edu>");

static int major;  // Major number for device
static struct cdev my_cdev;  // Character device structure
static dev_t dev_num;  // Device number

// Structure to store per-device instance data
typedef struct scanner_device {
    char *message;  // Buffer for storing data
    int message_len;  // Length of the data in the buffer
    char *separators;  // Buffer for custom separators
} scanner_device;

// Called when the device is opened
static int device_open(struct inode *inode, struct file *file) {
    scanner_device *dev;

    dev = kmalloc(sizeof(scanner_device), GFP_KERNEL);
    if (!dev) {
        printk(KERN_ERR "Scanner: Out of memory\n");
        return -ENOMEM;
    }

    dev->message = kmalloc(1024, GFP_KERNEL);
    if (!dev->message) {
        kfree(dev);
        printk(KERN_ERR "Scanner: Failed to allocate message buffer\n");
        return -ENOMEM;
    }
    dev->message_len = 0;

    dev->separators = kstrdup(DEFAULT_SEPARATORS, GFP_KERNEL);
    if (!dev->separators) {
        kfree(dev->message);
        kfree(dev);
        printk(KERN_ERR "Scanner: Failed to allocate separators buffer\n");
        return -ENOMEM;
    }

    file->private_data = dev;
    printk(KERN_INFO "Scanner: Device opened\n");
    return 0;
}

// Called when the device is closed
static int device_release(struct inode *inode, struct file *file) {
    scanner_device *dev = file->private_data;

    if (dev) {
        kfree(dev->message);
        kfree(dev->separators);
        kfree(dev);
    }

    printk(KERN_INFO "Scanner: Device closed\n");
    return 0;
}

// Handles read requests on the device
static ssize_t device_read(struct file *file, char __user *buffer, size_t length, loff_t *offset) {
    scanner_device *dev = file->private_data;
    int bytes_read = 0;

    if (*offset >= dev->message_len)
        return 0;

    while (length && (*offset < dev->message_len)) {
        if (put_user(dev->message[*offset], buffer++)) {
            return -EFAULT;
        }
        length--;
        bytes_read++;
        (*offset)++;
    }

    printk(KERN_INFO "Scanner: Read %d bytes\n", bytes_read);
    return bytes_read;
}

// Handles write requests on the device
static ssize_t device_write(struct file *file, const char __user *buffer, size_t len, loff_t *offset) {
    scanner_device *dev = file->private_data;

    if (len > 1024) {
        kfree(dev->message);
        dev->message = kmalloc(len, GFP_KERNEL);
        if (!dev->message) {
            printk(KERN_ERR "Scanner: Failed to reallocate message buffer\n");
            return -ENOMEM;
        }
    }

    if (copy_from_user(dev->message, buffer, len)) {
        printk(KERN_ERR "Scanner: Failed to copy data from user space\n");
        return -EFAULT;
    }

    dev->message_len = len;
    printk(KERN_INFO "Scanner: Wrote %zu bytes\n", len);
    return len;
}

// Handles IOCTL commands from user space
static long device_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    scanner_device *dev = file->private_data;

    switch (cmd) {
        case SCANNER_SET_SEP:
            kfree(dev->separators);
            dev->separators = strndup_user((char __user *)arg, 256);
            if (IS_ERR(dev->separators)) {
                printk(KERN_ERR "Scanner: Failed to set separators with error %ld\n", PTR_ERR(dev->separators));
                return PTR_ERR(dev->separators);
            }
            printk(KERN_INFO "Scanner: Separators updated\n");
            return 0;
        default:
            printk(KERN_ERR "Scanner: Unsupported IOCTL command\n");
            return -ENOTTY;
    }
}

// File operations supported by the device
static struct file_operations fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release,
    .unlocked_ioctl = device_ioctl,
    .owner = THIS_MODULE,
};

// Module initialization
static int __init scanner_init(void) {
    int ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        printk(KERN_ALERT "Scanner: Unable to allocate major number\n");
        return ret;
    }
    major = MAJOR(dev_num);

    cdev_init(&my_cdev, &fops);
    my_cdev.owner = THIS_MODULE;
    ret = cdev_add(&my_cdev, dev_num, 1);
    if (ret < 0) {
        unregister_chrdev_region(dev_num, 1);
        printk(KERN_ALERT "Scanner: Failed to register device\n");
        return ret;
    }

    printk(KERN_INFO "Scanner module initialized\n");
    return 0;
}

// Module cleanup
static void __exit scanner_exit(void) {
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_INFO "Scanner module unloaded\n");
}

module_init(scanner_init);
module_exit(scanner_exit);
