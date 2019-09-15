#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include <linux/sched/signal.h> 
    
    static int meminfo_proc_show(struct seq_file *m, void *v){
	   int cont = 0;
        struct task_struct *task;
seq_printf(m,"{\"proceso\":[");
        for_each_process(task){
		if (cont>0) {
		seq_printf(m,",");
		seq_printf(m,"\n");
		}
		  struct list_head *list;
		  seq_printf(m,"{\"nombre\":\"%s\",\"PID\":%d,\"UsuarioId\":%d,\"estado\":",task->comm,task->pid,task->cred->uid);
		if(task->state == 0){
			seq_printf(m,"\"EnEjecucion\"}");
		}
		if(task->state == 1){
			seq_printf(m,"\"Listos\"}");
		}
		if(task->state == 2){
			seq_printf(m,"\"Dormido\"}");
		}
		if(task->state == 4){
			seq_printf(m,"\"Zombie\"}");
		}
		if(task->state == 8){
			seq_printf(m,"\"Detenido\"}");
		}
		if(task->state == 32){
			seq_printf(m,"\"Espera Exclusiva\"}");
		}
		
		cont = cont +1;

        }
seq_printf(m,"]}");

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
        .open       = meminfo_proc_open,
        .read       = seq_read,
        .llseek     = seq_lseek,
        .release    = single_release,
    };

    static int __init inicio(void) //Escribe archivo en /proc
    {
	printk(KERN_INFO "Carnet>> 201314367\n");
	printk(KERN_INFO "Nombre>> CARLOS ESTUARDO GOMEZ RODRIGUEZ\n");
	printk(KERN_INFO "debian 10\n");
	proc_create("cpu_201314367", 0, NULL, &meminfo_proc_fops);
        return 0;
    }


    module_init(inicio);
    module_exit(final);

MODULE_AUTHOR("CARLOS_G");
MODULE_DESCRIPTION("201314367");
MODULE_LICENSE("GPL");
