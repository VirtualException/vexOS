#ifndef _ASSERT_H
#define _ASSERT_H

void __kassert_fail(const char* assertion, const char* file, unsigned int line, const char* function);

#define assert(expr)							                        \
    ((expr)								                                \
     ? (void)(0)                                                        \
     : __kassert_fail(#expr, __FILE__, __LINE__, __FUNCTION__))

#endif
