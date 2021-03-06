/*
 * tusb_descriptors.c
 *
 *  Created on: Nov 26, 2012
 *      Author: hathach
 */

/*
 * Software License Agreement (BSD License)
 * Copyright (c) 2012, hathach (tinyusb.org)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the tinyUSB stack
 */

#include "tusb_descriptors.h"

#if TUSB_CFG_DEVICE_HID_KEYBOARD
TUSB_CFG_ATTR_USBRAM ATTR_ALIGNED(4)
uint8_t app_tusb_keyboard_desc_report[] = {
  HID_USAGE_PAGE ( HID_USAGE_PAGE_DESKTOP     ),
  HID_USAGE      ( HID_USAGE_DESKTOP_KEYBOARD ),
  HID_COLLECTION ( HID_COLLECTION_APPLICATION ),
    HID_USAGE_PAGE ( HID_USAGE_PAGE_KEYBOARD ),
      HID_USAGE_MIN    ( 224                                    ),
      HID_USAGE_MAX    ( 231                                    ),
      HID_LOGICAL_MIN  ( 0                                      ),
      HID_LOGICAL_MAX  ( 1                                      ),

      HID_REPORT_COUNT ( 8                                      ), /* 8 bits */
      HID_REPORT_SIZE  ( 1                                      ),
      HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE ), /* maskable modifier key */

      HID_REPORT_COUNT ( 1                                      ),
      HID_REPORT_SIZE  ( 8                                      ),
      HID_INPUT        ( HID_CONSTANT                           ), /* reserved */

    HID_USAGE_PAGE  ( HID_USAGE_PAGE_LED                   ),
      HID_USAGE_MIN    ( 1                                       ),
      HID_USAGE_MAX    ( 5                                       ),
      HID_REPORT_COUNT ( 5                                       ),
      HID_REPORT_SIZE  ( 1                                       ),
      HID_OUTPUT       ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE  ), /* 5-bit Led report */

      HID_REPORT_COUNT ( 1                                       ),
      HID_REPORT_SIZE  ( 3                                       ), /* led padding */
      HID_OUTPUT       ( HID_CONSTANT                            ),

    HID_USAGE_PAGE (HID_USAGE_PAGE_KEYBOARD),
      HID_USAGE_MIN    ( 0                                   ),
      HID_USAGE_MAX    ( 101                                 ),
      HID_LOGICAL_MIN  ( 0                                   ),
      HID_LOGICAL_MAX  ( 101                                 ),

      HID_REPORT_COUNT ( 6                                   ),
      HID_REPORT_SIZE  ( 8                                   ),
      HID_INPUT        ( HID_DATA | HID_ARRAY | HID_ABSOLUTE ), /* keycodes array 6 items */
  HID_COLLECTION_END
};
#endif

#if TUSB_CFG_DEVICE_HID_MOUSE
TUSB_CFG_ATTR_USBRAM ATTR_ALIGNED(4)
uint8_t app_tusb_mouse_desc_report[] = {
  HID_USAGE_PAGE ( HID_USAGE_PAGE_DESKTOP     ),
  HID_USAGE      ( HID_USAGE_DESKTOP_MOUSE    ),
  HID_COLLECTION ( HID_COLLECTION_APPLICATION ),
    HID_USAGE      (HID_USAGE_DESKTOP_POINTER),

    HID_COLLECTION ( HID_COLLECTION_PHYSICAL ),
      HID_USAGE_PAGE  ( HID_USAGE_PAGE_BUTTON ),
        HID_USAGE_MIN    ( 1                                      ),
        HID_USAGE_MAX    ( 3                                      ),
        HID_LOGICAL_MIN  ( 0                                      ),
        HID_LOGICAL_MAX  ( 1                                      ),

        HID_REPORT_COUNT ( 3                                      ), /* Left, Right and Middle mouse*/
        HID_REPORT_SIZE  ( 1                                      ),
        HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE ),

        HID_REPORT_COUNT ( 1                                      ),
        HID_REPORT_SIZE  ( 5                                      ),
        HID_INPUT        ( HID_CONSTANT                           ), /* reserved */

      HID_USAGE_PAGE  ( HID_USAGE_PAGE_DESKTOP ),
        HID_USAGE        ( HID_USAGE_DESKTOP_X                    ),
        HID_USAGE        ( HID_USAGE_DESKTOP_Y                    ),
        HID_LOGICAL_MIN  ( 0x81                                   ), /* -127 */
        HID_LOGICAL_MAX  ( 0x7f                                   ), /* 127  */

        HID_REPORT_COUNT ( 2                                      ), /* X, Y position */
        HID_REPORT_SIZE  ( 8                                      ),
        HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_RELATIVE ), /* relative values */
    HID_COLLECTION_END,

  HID_COLLECTION_END
};
#endif

TUSB_CFG_ATTR_USBRAM ATTR_ALIGNED(4)
tusb_descriptor_device_t app_tusb_desc_device =
{
    .bLength            = sizeof(tusb_descriptor_device_t),
    .bDescriptorType    = TUSB_DESC_TYPE_DEVICE,
    .bcdUSB             = 0x0200,
    .bDeviceClass       = 0x00,
    .bDeviceSubClass    = 0x00,
    .bDeviceProtocol    = 0x00,

    .bMaxPacketSize0    = TUSB_CFG_DEVICE_CONTROL_PACKET_SIZE,

    .idVendor           = TUSB_CFG_DEVICE_VENDORID,
    .idProduct          = TUSB_CFG_PRODUCT_ID,
    .bcdDevice          = 0x0100,

    .iManufacturer      = 0x01,
    .iProduct           = 0x02,
    .iSerialNumber      = 0x03,

    .bNumConfigurations = 0x01 // TODO multiple configurations
};


TUSB_CFG_ATTR_USBRAM ATTR_ALIGNED(4)
app_descriptor_configuration_t app_tusb_desc_configuration =
{
    .configuration =
    {
        .bLength             = sizeof(tusb_descriptor_configuration_t),
        .bDescriptorType     = TUSB_DESC_TYPE_CONFIGURATION,

        .wTotalLength        = sizeof(app_descriptor_configuration_t) - 1, // exclude termination
        .bNumInterfaces      = TOTAL_INTEFACES,

        .bConfigurationValue = 1,
        .iConfiguration      = 0x00,
        .bmAttributes        = TUSB_DESC_CONFIG_ATT_BUS_POWER,
        .bMaxPower           = TUSB_DESC_CONFIG_POWER_MA(100)
    },

    #if IAD_DESC_REQUIRED
    // IAD points to CDC Interfaces
    .CDC_IAD =
    {
        .bLength           = sizeof(tusb_descriptor_interface_association_t),
        .bDescriptorType   = TUSB_DESC_TYPE_INTERFACE_ASSOCIATION,

        .bFirstInterface   = 0,
        .bInterfaceCount   = 2,

        .bFunctionClass    = CDC_COMMUNICATION_INTERFACE_CLASS,
        .bFunctionSubClass = CDC_ABSTRACT_CONTROL_MODEL,
        .bFunctionProtocol = CDC_PROTOCOL_COMMON_AT_COMMANDS,

        .iFunction         = 0
    },
    #endif

    #if TUSB_CFG_DEVICE_CDC
    // USB CDC Serial Interface
    // CDC Control Interface
    .CDC_CCI_Interface =
    {
        .bLength            = sizeof(tusb_descriptor_interface_t),
        .bDescriptorType    = TUSB_DESC_TYPE_INTERFACE,
        .bInterfaceNumber   = INTERFACE_INDEX_CDC,
        .bAlternateSetting  = 0,
        .bNumEndpoints      = 1,
        .bInterfaceClass    = CDC_COMMUNICATION_INTERFACE_CLASS,
        .bInterfaceSubClass = CDC_ABSTRACT_CONTROL_MODEL,
        .bInterfaceProtocol = CDC_PROTOCOL_COMMON_AT_COMMANDS,
        .iInterface         = 0x00
    },

    .CDC_Header =
    {
        .bFunctionLength    = sizeof(CDC_HEADER_DESCRIPTOR),
        .bDescriptorType    = CDC_CS_INTERFACE,
        .bDescriptorSubtype = CDC_HEADER,
        .bcdCDC             = 0x0120
    },

    .CDC_ACM =
    {
        .bFunctionLength    = sizeof(CDC_ABSTRACT_CONTROL_MANAGEMENT_DESCRIPTOR),
        .bDescriptorType    = CDC_CS_INTERFACE,
        .bDescriptorSubtype = CDC_ABSTRACT_CONTROL_MANAGEMENT,
        .bmCapabilities     = 0x06 // Support Send_Break and Set_Line_Coding, Set_Control_Line_State, Get_Line_Coding, and the notification Serial_State
    },

    .CDC_Union =
    {
        .sUnion =
        {
            .bFunctionLength    = sizeof(CDC_UNION_1SLAVE_DESCRIPTOR),
            .bDescriptorType    = CDC_CS_INTERFACE,
            .bDescriptorSubtype = CDC_UNION,
            .bMasterInterface   = 0
        },
        .bSlaveInterfaces[0] = 1
    },

    .CDC_NotificationEndpoint =
    {
        .bLength          = sizeof(tusb_descriptor_endpoint_t),
        .bDescriptorType  = TUSB_DESC_TYPE_ENDPOINT,
        .bEndpointAddress = CDC_NOTIFICATION_EP,
        .bmAttributes     = USB_ENDPOINT_TYPE_INTERRUPT,
        .wMaxPacketSize   = CDC_NOTIFICATION_EP_MAXPACKETSIZE,
        .bInterval        = 0xff // lowest polling rate
    },

    // CDC Data Interface
    .CDC_DCI_Interface =
    {
        .bLength            = sizeof(tusb_descriptor_interface_t),
        .bDescriptorType    = TUSB_DESC_TYPE_INTERFACE,
        .bInterfaceNumber   = INTERFACE_INDEX_CDC+1,
        .bAlternateSetting  = 0x00,
        .bNumEndpoints      = 2,
        .bInterfaceClass    = CDC_DATA_INTERFACE_CLASS,
        .bInterfaceSubClass = 0,
        .bInterfaceProtocol = 0,
        .iInterface         = 0x00
    },

    .CDC_DataOutEndpoint =
    {
        .bLength          = sizeof(tusb_descriptor_endpoint_t),
        .bDescriptorType  = TUSB_DESC_TYPE_ENDPOINT,
        .bEndpointAddress = CDC_DATA_EP_OUT,
        .bmAttributes     = USB_ENDPOINT_TYPE_BULK,
        .wMaxPacketSize   = CDC_DATA_EP_MAXPACKET_SIZE,
        .bInterval        = 0
    },

    .CDC_DataInEndpoint =
    {
        .bLength          = sizeof(tusb_descriptor_endpoint_t),
        .bDescriptorType  = TUSB_DESC_TYPE_ENDPOINT,
        .bEndpointAddress = CDC_DATA_EP_IN,
        .bmAttributes     = USB_ENDPOINT_TYPE_BULK,
        .wMaxPacketSize   = CDC_DATA_EP_MAXPACKET_SIZE,
        .bInterval        = 0
    },
    #endif

    //------------- HID Keyboard -------------//
    #if TUSB_CFG_DEVICE_HID_KEYBOARD
    .keyboard_interface =
    {
        .bLength            = sizeof(tusb_descriptor_interface_t),
        .bDescriptorType    = TUSB_DESC_TYPE_INTERFACE,
        .bInterfaceNumber   = INTERFACE_INDEX_HID_KEYBOARD,
        .bAlternateSetting  = 0x00,
        .bNumEndpoints      = 1,
        .bInterfaceClass    = TUSB_CLASS_HID,
        .bInterfaceSubClass = HID_SUBCLASS_BOOT,
        .bInterfaceProtocol = HID_PROTOCOL_KEYBOARD,
        .iInterface         = 0x00
    },

    .keyboard_hid =
    {
        .bLength           = sizeof(tusb_hid_descriptor_hid_t),
        .bDescriptorType   = HID_DESC_TYPE_HID,
        .bcdHID            = 0x0111,
        .bCountryCode      = HID_Local_NotSupported,
        .bNumDescriptors   = 1,
        .bReportType       = HID_DESC_TYPE_REPORT,
        .wReportLength     = sizeof(app_tusb_keyboard_desc_report)
    },

    .keyboard_endpoint =
    {
        .bLength          = sizeof(tusb_descriptor_endpoint_t),
        .bDescriptorType  = TUSB_DESC_TYPE_ENDPOINT,
        .bEndpointAddress = HID_KEYBOARD_EP_IN, //todo HID_KEYBOARD_EP_IN,
        .bmAttributes     = { .xfer = TUSB_XFER_INTERRUPT },
        .wMaxPacketSize   = { .size = 0x08 },
        .bInterval        = 0x0A
    },
    #endif

    //------------- HID Mouse -------------//
    #if TUSB_CFG_DEVICE_HID_MOUSE
    .mouse_interface =
    {
        .bLength            = sizeof(tusb_descriptor_interface_t),
        .bDescriptorType    = TUSB_DESC_TYPE_INTERFACE,
        .bInterfaceNumber   = INTERFACE_INDEX_HID_MOUSE,
        .bAlternateSetting  = 0x00,
        .bNumEndpoints      = 1,
        .bInterfaceClass    = TUSB_CLASS_HID,
        .bInterfaceSubClass = HID_SUBCLASS_BOOT,
        .bInterfaceProtocol = HID_PROTOCOL_MOUSE,
        .iInterface         = 0x00
    },

    .mouse_hid =
    {
        .bLength           = sizeof(tusb_hid_descriptor_hid_t),
        .bDescriptorType   = HID_DESC_TYPE_HID,
        .bcdHID            = 0x0111,
        .bCountryCode      = HID_Local_NotSupported,
        .bNumDescriptors   = 1,
        .bReportType       = HID_DESC_TYPE_REPORT,
        .wReportLength     = sizeof(app_tusb_mouse_desc_report)
    },

    .mouse_endpoint =
    {
        .bLength          = sizeof(tusb_descriptor_endpoint_t),
        .bDescriptorType  = TUSB_DESC_TYPE_ENDPOINT,
        .bEndpointAddress = HID_MOUSE_EP_IN, // TODO
        .bmAttributes     = { .xfer = TUSB_XFER_INTERRUPT },
        .wMaxPacketSize   = { .size = 0x08 },
        .bInterval        = 0x0A
    },
    #endif

    //------------- Mass Storage -------------//
    #if TUSB_CFG_DEVICE_MSC
    .msc_interface =
    {
        .bLength            = sizeof(tusb_descriptor_interface_t),
        .bDescriptorType    = TUSB_DESC_TYPE_INTERFACE,
        .bInterfaceNumber   = 3,
        .bAlternateSetting  = 0x00,
        .bNumEndpoints      = 2,
        .bInterfaceClass    = TUSB_CLASS_MSC,
        .bInterfaceSubClass = MSC_SUBCLASS_SCSI,
        .bInterfaceProtocol = MSC_PROTOCOL_BOT,
        .iInterface         = 0x00
    },

    .msc_endpoint_in =
    {
        .bLength          = sizeof(tusb_descriptor_endpoint_t),
        .bDescriptorType  = TUSB_DESC_TYPE_ENDPOINT,
        .bEndpointAddress = 0x83,
        .bmAttributes     = { .xfer = TUSB_XFER_BULK },
        .wMaxPacketSize   = 512,
        .bInterval        = 1
    },

    .msc_endpoint_out =
    {
        .bLength          = sizeof(tusb_descriptor_endpoint_t),
        .bDescriptorType  = TUSB_DESC_TYPE_ENDPOINT,
        .bEndpointAddress = 0x03,
        .bmAttributes     = { .xfer = TUSB_XFER_BULK },
        .wMaxPacketSize   = 512,
        .bInterval        = 1
    },
    #endif
};

TUSB_CFG_ATTR_USBRAM ATTR_ALIGNED(4)
app_descriptor_string_t app_tusb_desc_strings =
{
    //------------- index 0 -------------//
    .language = {
        .bLength         = 0x04,
        .bDescriptorType = TUSB_DESC_TYPE_STRING,
        .id              = 0x0409, // US English
    },

    //------------- index 1 -------------//
    .manufacturer = {
        .bLength         = STRING_LEN_BYTE2UNICODE(sizeof(TUSB_CFG_DEVICE_STRING_MANUFACTURER)-1),
        .bDescriptorType = TUSB_DESC_TYPE_STRING,
    },

    //------------- index 2 -------------//
    .product = {
        .bLength         = STRING_LEN_BYTE2UNICODE(sizeof(TUSB_CFG_DEVICE_STRING_PRODUCT)-1),
        .bDescriptorType = TUSB_DESC_TYPE_STRING,
    },

    //------------- index 3 -------------//
    .serial = {
        .bLength         = STRING_LEN_BYTE2UNICODE(sizeof(TUSB_CFG_DEVICE_STRING_SERIAL)-1),
        .bDescriptorType = TUSB_DESC_TYPE_STRING,
    }
};
