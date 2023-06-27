#ifndef _ATTRIBUTES_H
#define _ATTRIBUTES_H

#define __ms_abi                __attribute__((ms_abi))
#define __sysv_abi              __attribute__((sysv_abi))
#define __interrupt             __attribute__((interrupt))
#define __general_regs_only     __attribute__((target("general-regs-only")))
#define __aligned(x)            __attribute__((__aligned__(x)))
#define __aligned_largest       __attribute__((__aligned__))
#define __packed                __attribute__((packed))
#define __always_inline         inline __attribute__((always_inline))
#define __unused                __attribute__((unused))
#define __fallthrough           __attribute__((fallthrough));
#define __noreturn              __attribute__((noreturn))

#endif