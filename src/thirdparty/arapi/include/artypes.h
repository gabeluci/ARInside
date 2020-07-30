/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*   ©Copyright  2009 – 2012 BMC Software, Inc.                              */
/*   BMC, BMC Software, the BMC logos and other BMC marks are trademarks or  */
/*   registered trademarks of BMC Software, Inc. in the U.S. and /or         */
/*   certain other countries.                                                */
/*****************************************************************************/

#ifndef ARTYPES_H
#define ARTYPES_H

#ifndef INT_MAX
/*
 * This header depends on the Standard C <limits.h> method of
 * describing the integral sizes - it needs INT_MAX and friends
 * to be defined and useful in C preprocessor arithmetic.
 * If you can't or don't want to include the standard C/C++
 * header, you can still use this file by providing your own
 * definitions for {,U}{INT,LONG,SHRT}_{MIN,MAX}.
 */
#if defined(__cplusplus)
#include <climits>
#else
#include <limits.h>
#endif
#endif  /* INT_MAX */

#include <stddef.h>    /* size_t */

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/*
 * ARLong32 is a 32-bit signed integer on either 32-bit or
 * 64-bit machines.  It replaces "long" in the AR C API.
 * The definition is conditioned on INT_MAX for backward
 * compatibility; codes that use "long" expecting 32 bits
 * are only inconvenienced on machines where a long really
 * isn't 32 bits.
 *
 * ARLONG32_{MAX,MIN} are used analogously to the standard
 * LONG_{MAX,MIN} in parameterizing the machine word size out
 * of the code.
 *
 * ARLONG32_L can be used as a string infix to parameterize
 * word size out of calls to printf/scanf functions.  E.g.,
 *      ARLong32 bob;
 *      sscanf(input, "%"ARLONG32_L"d", &bob);  // either "%d" or "%ld"
 *
 * ARULong32 &c. are just unsigned variants of ARLong32 &c.
 */

#if SHRT_MAX < INT_MAX && INT_MAX < LONG_MAX

typedef int ARLong32;
#define ARLONG32_MAX INT_MAX
#define ARLONG32_MIN INT_MIN
#define ARLONG32_L ""
#define ARL0  /* obsolete */
#define xdr_ARLong32 xdr_int

#else

typedef long ARLong32;
#define ARLONG32_MAX LONG_MAX
#define ARLONG32_MIN LONG_MIN
#define ARLONG32_L "l"
#define ARL0 L  /* obsolete */
#define xdr_ARLong32 xdr_long

#endif  /* SHRT_MAX... */

#if USHRT_MAX < UINT_MAX && UINT_MAX < ULONG_MAX

typedef unsigned int ARULong32;
#define ARULONG32_MAX UINT_MAX
#define ARULONG32_L ""
#define xdr_ARULong32 xdr_u_int

#else

typedef unsigned long ARULong32;
#define ARULONG32_MAX ULONG_MAX
#define ARULONG32_L "l"
#define xdr_ARULong32 xdr_u_long

#endif  /* USHRT_MAX... */

#if USHRT_MAX < UINT_MAX && UINT_MAX < ULONG_MAX || defined(_WIN64)
#define ARSIZE_T_MAX (18446744073709551615ULL)
#else
#define ARSIZE_T_MAX (4294967295U)
#endif

/*
 * An unsigned integer wide enough to store a pointer.
 * Should be uintptr_t, but that type is C99-specific.
 */
typedef size_t ARUIntPtr;
/*
 * A signed integer wide enough to store a pointer.
 * Should be intptr_t, but that type is C99-specific.
 */
typedef ptrdiff_t ARIntPtr;

/*
 * Data structures that are punned with xdr types can harbor alignment
 * surprises.  Consider
 * struct ARByteList {
 *    ARULong32 type;        // offset 0
 *    unsigned  numItems;    // offset 4
 *    unsigned char *bytes;  // offset 8
 * }; // size = 12 (32), 16 (64)
 * vs
 * struct ArByteList {
 *    ARULong32 type;        // offset 0
 *    struct {
 *       u_int bytes_len;    // offset 4 (32), 8 (64)
 *       u_char *bytes_val;  // offset 8 (32), 16 (64)
 *    } bytes;
 * }; // size = 12 (32), 24 (64)
 * In 64-bit compilations, the ARByteList numItems and bytes members don't
 * line up with the ArByteList.bytes bytes_len and bytes_val members.
 * Fix:
 * struct ARByteList {
 *    ARULong32 type;        // offset 0
 *    AR_XDR_STRUCT_PAD32(noval_)       // offset 4
 *    unsigned  numItems;    // offset 4 (32), 8 (64)
 *    unsigned char *bytes;  // offset 8 (32), 16 (64)
 * }; // size = 12 (32), 24 (64)
 * Better solutions would entail repacking the structure.
 */
#if ARULONG32_MAX < ARSIZE_T_MAX
#define AR_XDR_STRUCT_PAD32(noval_) ARULong32 noval_;
#else
#define AR_XDR_STRUCT_PAD32(noval_)
#endif

/*
 * ARL(4) -> 4L
 * ARL(4U) -> 4UL
 * ... but be careful:
 * ARL(-1U) -> -1UL, which means -(unsigned long) 1, not (unsigned long) -1.
 */
#define ARL(z)(z)

#if !defined(ARCC)
#define ARCC(yat,yee)ARCC1(yat,yee)
#define ARCC1(yat,yee)yat##yee
#endif

#if !defined(ARQQ)
#define ARQQ(x)ARQQ1(x)
#define ARQQ1(x)#x
#endif

#if !defined(AR_NELEM)
/*
 * The number of elements in an array, if you know its size.
 * In
 * extern char extarray[];
 * double globalarray[100];
 * static ARLong32 staticarray[200];
 * void foo(char argarray[300]) {
 *    int autoarray[400];
 *    ...
 * }
 * we have
 *    AR_NELEM(globalarray) = 100
 *    AR_NELEM(staticarray) = 200
 *    AR_NELEM(autoarray) = 400
 *       ... because these arrays are defined in the current scope
 * but
 *    AR_NELEM(extarray) = 0
 *       ... because the compiler doesn't know sizes of objects
 *       ... defined externally
 *    AR_NELEM(argarray) = sizeof(char *)
 *       ... because function arguments declared with array types are
 *       ... actually pointers in C/C++
 */
#define AR_NELEM(a) (sizeof(a)/sizeof((a)[0]))
#endif

#ifdef HARD_CHECK_64
#define long DONT_USE_long
#endif

/*
 * Widths for printf &c.
 */
#define ARPWl32 ARLONG32_L  /* print ARLong32, ARULong32 */
#define ARSWl32 ARLONG32_L  /* scan ARLong32, ARULong32 */
#define ARPWtstmp ARPWl32   /* print ARTimestamp */
#define ARSWtstmp ARSWl32   /* scan ARTimestamp */
#define ARPWid ARPWl32      /* print ARInternalId */
#define ARSWid ARSWl32      /* scan ARInternalId */

   /* print/scan size_t */
#if ULONG_MAX < ARSIZE_T_MAX
#define ARPWsz "ll"
#define ARSWsz "ll"
#else
#define ARPWsz "l"
#define ARSWsz "l"
#endif

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif  /* ARTYPES_H */
