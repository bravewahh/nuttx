/****************************************************************************
 * graphics/color/nxglib_yuv2rgb.c
 *
 *   Copyright (C) 2008 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <spudmonkey@racsa.co.cr>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/types.h>
#include <debug.h>
#include <fixedmath.h>

#include <nuttx/nxglib.h>

/****************************************************************************
 * Pre-Processor Definitions
 ****************************************************************************/

#define b16_P3441 0x0000581a    /*   0.344147 */
#define b16_P7141 0x0000b6d2    /*   0.714142 */
#define b16_1P402 0x000166ea    /*   1.402008 */
#define b16_1P772 0x0001c5a2    /*   1.722003 */
#define b16_128P0 0x00800000    /* 128.000000 */

/****************************************************************************
 * Private Types
 ****************************************************************************/

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: nxgl_yuv2rgb
 *
 * Description:
 *   Convert 8-bit RGB triplet to 8-bit YUV triplet
 *
 *
 ****************************************************************************/

void nxgl_yuv2rgb(ubyte y, ubyte u, ubyte v, ubyte *r, ubyte *g, ubyte *b)
{
  b16_t vm128 = itob16(v) - b16_128P0;
  b16_t um128 = itob16(u) - b16_128P0;

  /* Per the JFIF specification:
   *
   * R = Y                         + 1.40200 * (V - 128.0)
   * G = Y - 0.34414 * (U - 128.0) - 0.71414 * (V - 128.0)
   * B = Y + 1.77200 * (U - 128.0)
   */

  *r = (ubyte)b16toi(itob16(y) +                             b16muli(b16_1P402, vm128));
  *g = (ubyte)b16toi(itob16(y) - b16muli(b16_P3441, um128) - b16muli(b16_P7141, vm128));
  *b = (ubyte)b16toi(itob16(y) + b16muli(b16_1P772, um128));
}
