/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright © 2020 Keith Packard
 * Copyright (c) 2017 embedded brains GmbH. All rights reserved
   Copyright (c) 2011, 2012 ARM Ltd.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _MACHINE_MATH_H_
#define _MACHINE_MATH_H_

#if defined(_HAVE_ATTRIBUTE_ALWAYS_INLINE) && defined(_HAVE_ATTRIBUTE_GNU_INLINE)
#define __declare_arm_macro(type) extern __inline type __attribute((gnu_inline, always_inline))

#ifdef _WANT_MATH_ERRNO
#include <errno.h>
#endif

#if (__ARM_FP & 0x8) && !defined(__SOFTFP__)

/*
 * Double precision routines
 */

__declare_arm_macro(double)
sqrt(double x)
{
	double result;
#ifdef _WANT_MATH_ERRNO
        if (x < 0)
            errno = EDOM;
#endif
#if __ARM_ARCH >= 6
	__asm__("vsqrt.f64 %P0, %P1" : "=w" (result) : "w" (x));
#else
	/* VFP9 Erratum 760019, see GCC sources "gcc/config/arm/vfp.md" */
	__asm__("vsqrt.f64 %P0, %P1" : "=&w" (result) : "w" (x));
#endif
	return result;
}

#if __ARM_ARCH >= 8
__declare_arm_macro(double)
ceil (double x)
{
  double result;
  __asm__ volatile ( "vrintp.f64\t%P0, %P1" : "=w" (result) : "w" (x) );
  return result;
}

__declare_arm_macro(double)
floor (double x)
{
  double result;
  __asm__ volatile ("vrintm.f64\t%P0, %P1" : "=w" (result) : "w" (x));
  return result;
}

__declare_arm_macro(double)
nearbyint (double x)
{
  double result;
  __asm__ volatile ("vrintr.f64\t%P0, %P1" : "=w" (result) : "w" (x));
  return result;
}

__declare_arm_macro(double)
rint (double x)
{
  double result;
  __asm__ volatile ("vrintx.f64\t%P0, %P1" : "=w" (result) : "w" (x));
  return result;
}

__declare_arm_macro(double)
round (double x)
{
  double result;
  __asm__ volatile ("vrinta.f64\t%P0, %P1" : "=w" (result) : "w" (x));
  return result;
}

__declare_arm_macro(double)
trunc (double x)
{
  double result;
  __asm__ volatile ("vrintz.f64\t%P0, %P1" : "=w" (result) : "w" (x));
  return result;
}
#endif /* __ARM_ARCH >= 8 */

#if HAVE_FAST_FMA
__declare_arm_macro(double)
fma (double x, double y, double z)
{
  __asm__("vfma.f64 %P0, %P1, %P2" : "+w" (z) : "w" (x), "w" (y));
  return z;
}
#endif

#endif /* (__ARM_FP & 0x8) && !defined(__SOFTFP__) */

#if (__ARM_FP & 0x4) && !defined(__SOFTFP__)

/*
 * Single precision functions
 */

__declare_arm_macro(float)
sqrtf(float x)
{
	float result;
#ifdef _WANT_MATH_ERRNO
        if (x < 0)
            errno = EDOM;
#endif
#if __ARM_ARCH >= 6
	__asm__("vsqrt.f32 %0, %1" : "=w" (result) : "w" (x));
#else
	/* VFP9 Erratum 760019, see GCC sources "gcc/config/arm/vfp.md" */
	__asm__("vsqrt.f32 %0, %1" : "=&w" (result) : "w" (x));
#endif
	return result;
}

#if __ARM_ARCH >= 8
__declare_arm_macro(float)
ceilf (float x)
{
  float result;
  __asm__ volatile ( "vrintp.f32\t%0, %1" : "=t" (result) : "t" (x) );
  return result;
}

__declare_arm_macro(float)
floorf (float x)
{
  float result;
  __asm__ volatile ( "vrintm.f32\t%0, %1" : "=t" (result) : "t" (x) );
  return result;
}

__declare_arm_macro(float)
nearbyintf (float x)
{
  float result;
  __asm__ volatile ("vrintr.f32\t%0, %1" : "=t" (result) : "t" (x));
  return result;
}

__declare_arm_macro(float)
rintf (float x)
{
  float result;
  __asm__ volatile ("vrintx.f32\t%0, %1" : "=t" (result) : "t" (x));
  return result;
}

__declare_arm_macro(float)
roundf (float x)
{
  float result;
  __asm__ volatile ("vrinta.f32\t%0, %1" : "=t" (result) : "t" (x));
  return result;
}

__declare_arm_macro(float)
truncf (float x)
{
  float result;
  __asm__ volatile ("vrintz.f32\t%0, %1" : "=t" (result) : "t" (x));
  return result;
}
#endif /* __ARM_ARCH >= 8 */

#if HAVE_FAST_FMAF

__declare_arm_macro(float)
fmaf (float x, float y, float z)
{
  __asm__("vfma.f32 %0, %1, %2" : "+t" (z) : "t" (x), "t" (y));
  return z;
}
#endif

#endif /* (__ARM_FP & 0x4) && !defined(__SOFTFP__) */

#undef __declare_arm_macro

#endif /* have attributes */

#endif /* _MACHINE_MATH_H_ */
