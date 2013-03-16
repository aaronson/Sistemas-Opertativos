#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kd.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/ioctl.h>
#include <linux/syscalls.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/tty.h>
#include <linux/vt_kern.h>
#include <linux/console_struct.h>
#include <linux/random.h>
#include <linux/kdev_t.h>
#include <asm/uaccess.h>
#include <linux/miscdevice.h>

#define procfs_name "fibonacci"

static int __init fib_init(void);
static void __exit fib_exit(void);

module_init(fib_init);
module_exit(fib_exit);

int lecturas = 0, n1 = 0, n2 = 0;
static struct proc_dir_entry *procFile;

int procFileRead(char * buf, char **start, off_t off, int count, int *eof, void *data);
static ssize_t device_write(struct file *filp, const char *buffer, size_t length, loff_t *offset);
static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset);

static int major;

static const struct file_operations fops = {
    .owner = THIS_MODULE,
    .read  = device_read,
    .write = device_write
};

static struct miscdevice fibdev = {
    MISC_DYNAMIC_MINOR,
    procfs_name,
    &fops
};


static int __init fib_init(void)
{
	printk(KERN_ALERT "Se carga el modulo Fibonacci\n");
    major = misc_register(&fibdev);
    if (major < 0) {
		printk(KERN_ALERT "No se pudo registrar el driver con major %d\n",major);
        return major;
    }
    procFile = create_proc_entry(procfs_name, 0666, NULL);
    if (procFile == NULL) {
			printk(KERN_ALERT "Error: No se pudo crear /proc/%s\n",procfs_name);
        }
    procFile->read_proc = procFileRead;

    return major;
}

static void __exit fib_exit(void) {
	printk(KERN_ALERT "Se descarga el modulo Fibonacci\n");
    remove_proc_entry(procfs_name, procFile);
    misc_deregister(&fibdev);
}

static ssize_t device_write(struct file *filp, const char *buffer, size_t length, loff_t *offset)
{
    if (length < 3)
        return -EINVAL;
    lecturas++;
    sscanf(buffer, "%d %d", &n1, &n2);
    return length;
}

static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset)
{
    if (length < 1)
        return 0;
    lecturas++;
    return sprintf(buffer, "%d", n1 + n2);
}

int procFileRead(char * buf, char **start, off_t off, int count, int *eof, void *data)
{
    int tam;
    tam = sprintf(buf, "Se hicieron %d lecturas\n", lecturas);
    return tam;
}



MODULE_LICENSE("GPL");
