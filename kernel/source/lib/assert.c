#include <vexos/lib/assert.h>
#include <vexos/kprintf.h>

void
__kassert_fail(const char* assertion, const char* file, unsigned int line, const char* function) {

    kprintf(KERN_TLOG "Assertion failed! Caused by \"%s\" at %s:%d, in function %s\n",
                    assertion, file, line, function);

    return;
}