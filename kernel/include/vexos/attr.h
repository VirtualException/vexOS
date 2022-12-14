#ifndef _ATTR_H
#define _ATTR_H

#define __ms_abi                __attribute__((ms_abi))
#define __aligned(x)            __attribute__((__aligned__(x)))
#define __aligned_largest       __attribute__((__aligned__))
#define __packed                __attribute__((packed))
#define __always_inline         inline __attribute__((always_inline))

#endif