#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <tusb.h>

#include "comms_def.h"

/**
 * Reads an incoming serial data line over the USB port.
 * @param buff Input character buffer that is written to,
 * @param max_bytes Maximum amount of characters to read.
 * @param timeout_ms Timeout in milliseconds.
 * @return 0 if complete read was successful, -1 if failed, -2 if timed-out. 
*/
int comms_serial_read_line_over_usb(char* buff, size_t max_bytes, uint32_t timeout_ms);

/**
 * Reads n-bytes of serial data over the USB port.
 * @param buff Input character buffer that is written to,
 * @param max_bytes Maximum amount of characters to read.
 * @param timeout_ms Timeout in milliseconds.
 * @return 0 if complete read was successful, -1 if failed, -2 if timed-out. 
*/
int comms_serial_read_n_over_usb(char* buff, size_t max_bytes, uint32_t timeout_ms);

#ifdef __cplusplus
}
#endif