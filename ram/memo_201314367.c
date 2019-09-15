#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/hugetlb.h>
#include <linux/mman.h>
#include <linux/mmzone.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/quicklist.h>
#include <linux/seq_file.h>
#include <linux/swap.h>
#include <linux/vmstat.h>
#include <linux/atomic.h>
#include <linux/vmalloc.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/uaccess.h>

MODULE_AUTHOR("CARLOS_G");
MODULE_DESCRIPTION("201314367");
MODULE_LICENSE("GPL");

struct sysinfo i;
unsigned long committed;
unsigned long allowed;
long cached;
unsigned long pages[NR_LRU_LISTS];
int lru;

static int meminfo_proc_show(struct seq_file *m, void *v)
{

#define K(x) ((x) << (PAGE_SHIFT - 10))
si_meminfo(&i);
for (lru = LRU_BASE; lru < NR_LRU_LISTS; lru++)
pages[lru] = global_numa_state(NR_LRU_BASE + lru);
seq_printf(m,"{\"RAM libre\": %8lu, \"libre\": %lu}\n",
		i.freeram*4,
		((i.freeram*100)/i.totalram));
#undef K
return 0;

}

static void __exit final(void) //Salida de modulo
{

}

static int meminfo_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, meminfo_proc_show, NULL);
}

static const struct file_operations meminfo_proc_fops = {
	.open		= meminfo_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init proc_meminfo_init(void)
{
	printk(KERN_INFO "CARNET>> 201314367\n");
	printk(KERN_INFO "NOMBRE>> CARLOS ESTUARDO GOMEZ RODRIGUEZ\n");
	printk(KERN_INFO "debian 10\n");
	proc_create("memo_201314367", 0, NULL, &meminfo_proc_fops);
	return 0;
}
fs_initcall(proc_meminfo_init);
module_exit(final);
