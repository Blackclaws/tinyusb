/**************************************************************************/
/*!
    @file     fifo.h
    @author   hathach (tinyusb.org)

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2013, hathach (tinyusb.org)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	  This file is part of the tinyusb stack.
*/
/**************************************************************************/

/** \file
 *  \brief Error Header
 *
 *  \note TBD
 */

/** \ingroup Group_Common
 *
 *  @{
 */

#ifndef _TUSB_FIFO_H_
#define _TUSB_FIFO_H_

#include "common/common.h"

#ifdef __cplusplus
 extern "C" {
#endif

/** \struct fifo_t
 * \brief Simple Circular FIFO
 */
typedef struct _fifo_t
{
           uint8_t* buf          ; ///< buffer pointer
           uint16_t size         ; ///< buffer size
  volatile uint16_t len          ; ///< bytes in fifo
  volatile uint16_t wr_ptr       ; ///< write pointer
  volatile uint16_t rd_ptr       ; ///< read pointer
           bool     overwritable ; ///< allow overwrite data when full
//           IRQn_Type irq         ; ///< TODO (abstract later) interrupt used to lock fifo
} fifo_t;

bool fifo_init(fifo_t* f, uint8_t* buffer, uint16_t size, bool overwritable); //, IRQn_Type irq);
bool fifo_write(fifo_t* f, uint8_t data);
bool fifo_read(fifo_t* f, uint8_t *data);
uint16_t fifo_read_n(fifo_t* f, uint8_t * rx, uint16_t maxlen);
void fifo_clear(fifo_t *f);

static inline bool fifo_is_empty(fifo_t* f)
{
  return (f->len == 0);
}

static inline bool fifo_is_full(fifo_t* f)
{
  return (f->len == f->size);
}

static inline uint16_t fifo_get_length(fifo_t* f)
{
  return f->len;
}

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_FIFO_H_ */
