/**************************************************************************/
/*!
    @file     tusb_option.h
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
 *  \brief Configure File
 *
 *  \note TBD
 */

/** 
 *  \defgroup Group_TinyUSB_Configure Configuration tusb_option.h
 *  @{
 */

#ifndef _TUSB_TUSB_OPTION_H_
#define _TUSB_TUSB_OPTION_H_

#ifdef __cplusplus
 extern "C" {
#endif

#define TUSB_VERSION_YEAR   00
#define TUSB_VERSION_MONTH  00
#define TUSB_VERSION_WEEK   0
#define TUSB_VERSION_NAME   "alpha"
#define TUSB_VERSION        XSTRING_(TUSB_VERSION_YEAR) "." XSTRING_(TUSB_VERSION_MONTH)

#define MCU_LPC13UXX    1
#define MCU_LPC11UXX    2
#define MCU_LPC43XX     3
#define MCU_LPC18XX     4
#define MCU_LPC175X_6X  5
#define MCU_LPC177X_8X  6

/// define this symbol will make tinyusb look for external configure file
#include "mcu_capacity.h"

#ifdef TUSB_CFG_CONFIG_FILE
  #include TUSB_CFG_CONFIG_FILE
#else
  #include "tusb_config.h"
#endif

//--------------------------------------------------------------------+
// CONTROLLER
//--------------------------------------------------------------------+
#define TUSB_MODE_HOST    0x02
#define TUSB_MODE_DEVICE  0x01
#define TUSB_MODE_NONE    0x00

#define CONTROLLER_HOST_NUMBER (\
    ((TUSB_CFG_CONTROLLER0_MODE & TUSB_MODE_HOST) ? 1 : 0) + \
    ((TUSB_CFG_CONTROLLER1_MODE & TUSB_MODE_HOST) ? 1 : 0))

#define CONTROLLER_DEVICE_NUMBER (\
    ((TUSB_CFG_CONTROLLER0_MODE & TUSB_MODE_DEVICE) ? 1 : 0) + \
    ((TUSB_CFG_CONTROLLER1_MODE & TUSB_MODE_DEVICE) ? 1 : 0))

#define MODE_HOST_SUPPORTED   (CONTROLLER_HOST_NUMBER > 0)
#define MODE_DEVICE_SUPPORTED (CONTROLLER_DEVICE_NUMBER > 0)

#if !MODE_HOST_SUPPORTED && !MODE_DEVICE_SUPPORTED
  #error please configure at least 1 TUSB_CFG_CONTROLLERn_MODE to TUSB_MODE_HOST and/or TUSB_MODE_DEVICE
#endif

//--------------------------------------------------------------------+
// COMMON OPTIONS
//--------------------------------------------------------------------+

// level 3: ATTR_ALWAYS_INLINE is null, ASSERT has text, Error has its String
// level 2: ATTR_ALWAYS_INLINE is attribute, ASSERT has no text, Error has no strings
/// 0: no debug information 3: most debug information provided
#ifndef TUSB_CFG_DEBUG
  #define TUSB_CFG_DEBUG 3
  #warning TUSB_CFG_DEBUG is not defined, default value is 3
#endif

/// USB RAM Section Placement, MCU's usb controller often has limited access to specific RAM region. This will be used to declare internal variables as follow:
/// uint8_t tinyusb_data[10] TUSB_CFG_ATTR_USBRAM;
/// if your mcu's usb controller has no such limit, define TUSB_CFG_ATTR_USBRAM as empty macro.
#ifndef TUSB_CFG_ATTR_USBRAM
 #error TUSB_CFG_ATTR_USBRAM is not defined, please help me know how to place data in accessible RAM for usb controller
#endif

#if TUSB_CFG_OS == TUSB_OS_NONE
  #ifndef TUSB_CFG_OS_TICKS_PER_SECOND
    #error TUSB_CFG_OS_TICKS_PER_SECOND is required to use with OS_NONE
  #endif
#else
  #ifndef TUSB_CFG_OS_TASK_PRIO
    #error TUSB_CFG_OS_TASK_PRIO need to be defined (hint: use the highest if possible)
  #endif
#endif

#ifndef TUSB_CFG_CONFIGURATION_MAX
  #define TUSB_CFG_CONFIGURATION_MAX 1
  #warning TUSB_CFG_CONFIGURATION_MAX is not defined, default value is 1
#endif

//--------------------------------------------------------------------+
// HOST OPTIONS
//--------------------------------------------------------------------+
#if MODE_HOST_SUPPORTED
  #ifndef TUSB_CFG_HOST_DEVICE_MAX
    #define TUSB_CFG_HOST_DEVICE_MAX 1
    #warning TUSB_CFG_HOST_DEVICE_MAX is not defined, default value is 1
  #endif

  //------------- HUB CLASS -------------//
  #if TUSB_CFG_HOST_HUB && (TUSB_CFG_HOST_DEVICE_MAX == 1)
    #error there is no benefit enable hub with max device is 1. Please disable hub or increase TUSB_CFG_HOST_DEVICE_MAX
  #endif

  //------------- HID CLASS -------------//
  #define HOST_CLASS_HID   ( TUSB_CFG_HOST_HID_KEYBOARD + TUSB_CFG_HOST_HID_MOUSE + TUSB_CFG_HOST_HID_GENERIC )
  #if HOST_CLASS_HID
    #define HOST_HCD_XFER_INTERRUPT
  #endif

  #ifndef TUSB_CFG_HOST_ENUM_BUFFER_SIZE
    #define TUSB_CFG_HOST_ENUM_BUFFER_SIZE 256
    #warning TUSB_CFG_HOST_ENUM_BUFFER_SIZE is not defined, default value is 256
  #endif

  //------------- CLASS -------------//
#endif // end TUSB_CFG_HOST

//--------------------------------------------------------------------+
// DEVICE OPTIONS
//--------------------------------------------------------------------+
#if MODE_DEVICE_SUPPORTED

#if defined(CAP_DEVICE_ROMDRIVER) && !TUSB_CFG_DEVICE_USE_ROM_DRIVER
  #error only rom driver for these mcu are supported now
#endif

#define DEVICE_CLASS_HID ( TUSB_CFG_DEVICE_HID_KEYBOARD + TUSB_CFG_DEVICE_HID_MOUSE + TUSB_CFG_DEVICE_HID_GENERIC )


#endif



#define USB_FS_MAX_BULK_PACKET  64
#define USB_HS_MAX_BULK_PACKET  USB_FS_MAX_BULK_PACKET /* Full speed device only */

/* HID In/Out Endpoint Address */
#define    HID_KEYBOARD_EP_IN       ENDPOINT_IN_LOGICAL_TO_PHYSICAL(1)
#define    HID_MOUSE_EP_IN          ENDPOINT_IN_LOGICAL_TO_PHYSICAL(4)

/* CDC Endpoint Address */
#define  CDC_NOTIFICATION_EP                ENDPOINT_IN_LOGICAL_TO_PHYSICAL(2)
#define  CDC_DATA_EP_OUT                    ENDPOINT_OUT_LOGICAL_TO_PHYSICAL(3)
#define  CDC_DATA_EP_IN                     ENDPOINT_IN_LOGICAL_TO_PHYSICAL(3)

#define  CDC_NOTIFICATION_EP_MAXPACKETSIZE  8
#define  CDC_DATA_EP_MAXPACKET_SIZE         16



#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_TUSB_OPTION_H_ */

/** @} */
