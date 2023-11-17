#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>

struct birthday
{
    int day;
    int month;
    int year;
    struct list_head list;
};
typedef struct birthday bd;
static LIST_HEAD(birthday_list);
void birthday_list_add_tail_bd(int day, int month, int year)
{
    bd *person = (bd *)kmalloc(sizeof(bd), GFP_KERNEL);
    person->day = day;
    person->month = month;
    person->year = year;
    INIT_LIST_HEAD(&person->list);
    list_add_tail(&person->list, &birthday_list);
}
void print_bd(bd *ptr)
{
    printk(KERN_INFO "0x%08lx { %d / %d / %d }", ptr, ptr->year, ptr->month, ptr->day);
}
int simple_init(void)
{
    bd *ptr;
    printk(KERN_INFO "loading Module\n");
    birthday_list_add_tail_bd(10, 10, 2000);
    birthday_list_add_tail_bd(18, 11, 2017);
    birthday_list_add_tail_bd(3, 9, 2014);
    birthday_list_add_tail_bd(28, 4, 2008);
    birthday_list_add_tail_bd(14, 7, 2019);
    list_for_each_entry(ptr, &birthday_list, list)
        print_bd(ptr);
    return 0;
}
void simple_exit(void)
{
    bd *ptr, *temp;
    list_for_each_entry_safe(ptr, temp, &birthday_list, list)
    {
        printk("Removing: \t0x%08lx", ptr);
        print_bd(ptr);
        kfree(ptr);
    }
    kfree(&birthday_list);
    printk(KERN_INFO "Removing Module\n");
}
module_init(simple_init);
module_exit(simple_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("simple module");
MODULE_AUTHOR("SGG");
