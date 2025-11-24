#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <pico/stdio_usb.h>
#include <tusb.h>

#include <stdbool.h>

/**
 * Reads incoming serial data over the USB port.
 * @param buff Input character buffer that is written to,
 * @param max_bytes Maximum amount of characters to read.
 * @return True if complete read was successful, false if not. 
 *
*/
bool comms_read_serial_over_usb(char* buff, size_t max_bytes);

#ifdef __cplusplus
}
#endif