#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <tusb.h>

#include "comms_def.h"

/**
 * Initializes the USB serial communications.
 * @return 0 (COMMS_OK) if successful, -1 (COMMS_FAIL) if failed.
*/
int comms_serial_usb_init(void);

/**
 * Waits until a full incoming serial data line is read over the USB port.
 * @param buff Input character buffer that is written to.
 * @param max_bytes Maximum amount of characters to read.
 * @param timeout_ms Timeout in milliseconds.
 * @return 0 if complete read was successful, -1 if failed, -2 if timed-out. 
*/
int comms_serial_read_line_over_usb_blocking(char* buff, size_t max_bytes, uint32_t timeout_ms);

/**
 * Waits until n-bytes of serial data is read over the USB port.
 * @param buff Input character buffer that is written to.
 * @param max_bytes Maximum amount of characters to read.
 * @param timeout_ms Timeout in milliseconds.
 * @return 0 if complete read was successful, -1 if failed, -2 if timed-out. 
*/
int comms_serial_read_n_over_usb_blocking(char* buff, size_t max_bytes, uint32_t timeout_ms);

/**
 * Attempts to read a full line over the USB port.
 * @param buff Input character buffer that is written to.
 * @param max_bytes Maximum amount of characters to read.
 * @return 0 (COMMS_OK) if complete read was successful,
 * -1 (COMMS_FAIL) if failed or no data available to read,
 * -3 (COMMS_PARTIAL) if only some of the data was read.
*/
int comms_serial_try_read_line_over_usb(char* buff, size_t max_bytes);

/**
 * Attempts to read n-bytes over the USB port.
 * @param buff Input character buffer that is written to.
 * @param max_bytes Maximum amount of characters to read.
 * @return 0 (COMMS_OK) if complete read was successful,
 * -1 (COMMS_FAIL) if failed or no data available to read,
 * -3 (COMMS_PARTIAL) if only some of the data was read.
*/
int comms_serial_try_read_n_over_usb(char* buff, size_t max_bytes);

/**
 * Waits until it can write a full line over the USB port.
 * @param buff Output buffer that is read from.
 * @param max_bytes Maximum amount of characters to write.
 * @param timeout_ms Timeout in milliseconds.
 * @return The amount of bytes successfully written.
*/
size_t comms_serial_write_line_over_usb_blocking(const char* buff, size_t max_bytes, uint32_t timeout_ms);

/**
 * Waits until it can write n-bytes over the USB port.
 * @param buff Output buffer that is read from.
 * @param max_bytes Maximum amount of characters to write.
 * @param timeout_ms Timeout in milliseconds.
 * @return The amount of bytes successfully written.
*/
size_t comms_serial_write_n_over_usb_blocking(const char* buff, size_t max_bytes, uint32_t timeout_ms);

/**
 * Attempts to write a full line over the USB port.
 * @param buff Output buffer that is read from.
 * @param max_bytes Maximum amount of characters to write.
 * @return The amount of bytes successfully written.
*/
size_t comms_serial_try_write_line_over_usb(const char* buff, size_t max_bytes);

/**
 * Attempts to write n-bytes over the USB port.
 * @param buff Output buffer that is read from.
 * @param max_bytes Maximum amount of characters to write.
 * @return The amount of bytes successfully written.
*/
size_t comms_serial_try_write_n_over_usb(const char* buff, size_t max_bytes);

#ifdef __cplusplus
}
#endif