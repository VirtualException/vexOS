#include <vexos/lib/assert.h>
#include <vexos/printk.h>

#include <vexos/arch/serial.h>

void
__kassert_fail(const char* assertion, const char* file, unsigned int line, const char* function) {

    printk(KERN_LOG "Assertion failed! \n");
    printk(KERN_LOG "Assertion caused by \"%s\" at %s:%d, in function %s\n",
                    assertion, file, line, function);

    return;
}