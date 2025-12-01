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
 * Waits until a full incoming serial text line is read over the USB port.
 * @param buff Input character buffer that is written to.
 * @param max_bytes Maximum amount of characters to read.
 * @param timeout_ms Timeout in milliseconds.
 * @return 0 (COMMS_OK) if complete read was successful,
 * -1 (COMMS_FAIL) if failed,
 * -2 (COMMS_TIMEOUT) if timed-out.
 */
int comms_serial_read_text_line_over_usb_blocking(char* buff, size_t max_bytes, uint32_t timeout_ms, size_t* bytes_read);

/**
 * Waits until n-bytes of serial text is read over the USB port.
 * @param buff Input character buffer that is written to.
 * @param max_bytes Maximum amount of characters to read.
 * @param timeout_ms Timeout in milliseconds.
 * @return 0 (COMMS_OK) if complete read was successful,
 * -1 (COMMS_FAIL) if failed,
 * -2 (COMMS_TIMEOUT) if timed-out.
 */
int comms_serial_read_text_n_over_usb_blocking(char* buff, size_t max_bytes, uint32_t timeout_ms, size_t* bytes_read);

/**
 * Attempts to read a full line of text over the USB port.
 * @param buff Input character buffer that is written to.
 * @param max_bytes Maximum amount of characters to read.
 * @return 0 (COMMS_OK) if complete read was successful,
 * -1 (COMMS_FAIL) if failed,
 * -3 (COMMS_PARTIAL) if only some of the data was read,
 * -4 (COMMS_NODATA) if no data to read.
 */
int comms_serial_try_read_text_line_over_usb(char* buff, size_t max_bytes, size_t* bytes_read);

/**
 * Attempts to read n-bytes of text over the USB port.
 * @param buff Input character buffer that is written to.
 * @param max_bytes Maximum amount of characters to read.
 * @return 0 (COMMS_OK) if complete read was successful,
 * -1 (COMMS_FAIL) if failed,
 * -3 (COMMS_PARTIAL) if only some of the data was read,
 * -4 (COMMS_NODATA) if no data to read.
 */
int comms_serial_try_read_text_n_over_usb(char* buff, size_t max_bytes, size_t* bytes_read);

/**
 * Waits to read a buffer of n-bytes over the USB port. Note this is for raw data, not text.
 * @param buff Buffer to write to.
 * @param max_bytes Buffer length, or maximum amount of bytes to read.
 * @param timeout_ms Timeout in milliseconds.
 * @return 0 (COMMS_OK) if complete read was successful,
 * -1 (COMMS_FAIL) if failed,
 * -2 (COMMS_TIMEOUT) if timed-out.
 */
int comms_serial_read_buff_over_usb_blocking(void* buff, size_t max_bytes, uint32_t timeout_ms, size_t* bytes_read);

/**
 * Attempts to read a buffer of n-bytes over the USB port. Note this is for raw data, not text.
 * @param buff Buffer to write to.
 * @param max_bytes Buffer length, or maximum amount of bytes to read.
 * @return 0 (COMMS_OK) if complete read was successful,
 * -1 (COMMS_FAIL) if failed or no data to read,
 * -3 (COMMS_PARTIAL) if only some of the expected data was read,
 * -4 (COMMS_NODATA) if no data to read.
 */
int comms_serial_try_read_buff_over_usb(void* buff, size_t max_bytes, size_t* bytes_read);

/**
 * Attempts to read a buffer of n-bytes over the USB port,
 * but only pull the data from the FIFO buffer it sees immediately, and not more.
 * @param buff Buffer to write to.
 * @param max_bytes Buffer length, or maximum number of bytes to write, limited by the FIFO buffer size.
 * @return 0 (COMMS_OK) if all data expected was read,
 * -1 (COMMS_FAIL) if failed,
 * -3 (COMMS_PARTIAL) if only some of the expected data was read,
 * -4 (COMMS_NODATA) if no data is present.
 */
int comms_serial_try_read_buff_over_usb_quick(void* buff, size_t max_bytes, size_t* bytes_read);

/**
 * Waits until it can write a full line of text over the USB port.
 * @param buff Buffer to read from.
 * @param max_bytes Maximum amount of characters to write.
 * @param timeout_ms Timeout in milliseconds.
 * @return The amount of bytes successfully written.
 */
size_t comms_serial_write_text_line_over_usb_blocking(const char* buff, size_t max_bytes, uint32_t timeout_ms);

/**
 * Attempts to write a full line of text over the USB port.
 * @param buff Buffer to read from.
 * @param max_bytes Maximum amount of characters to write.
 * @return The amount of bytes successfully written.
 */
size_t comms_serial_try_write_text_line_over_usb(const char* buff, size_t max_bytes);



/**
 * Waits to write a buffer of n-bytes over the USB port. Note this is for raw data, not text.
 * @param buff Buffer to read from.
 * @param max_bytes Buffer length, or maximum amount of bytes to write.
 * @param timeout_ms Timeout in milliseconds.
 * @return Number of bytes successfully written.
 */
size_t comms_serial_write_buff_over_usb_blocking(const void* buff, size_t max_bytes, uint32_t timeout_ms);

/**
 * Attempts to write a buffer of n-bytes over the USB port. Note this is for raw data, not text.
 * @param buff Buffer to read from.
 * @param max_bytes Buffer length, or maximum amount of bytes to write.
 * @return Number of bytes successfully written.
 */
size_t comms_serial_try_write_buff_over_usb(const void* buff, size_t max_bytes);

/**
 * Waits to write a string over the USB port.
 * @param strbuff String to write.
 * @param timeout_ms Timeout in milliseconds.
 * @return Number of bytes successfully written.
 */
size_t comms_serial_write_str_over_usb_blocking(const char* strbuff, uint32_t timeout_ms);

/**
 * Attempts to write a string over the USB port.
 * @param strbuff String to write.
 * @return Number of bytes successfully written.
 */
size_t comms_serial_try_write_str_over_usb(const char* strbuff);


/**
 * Attempts to write a buffer of n-bytes over the USB port,
 * but only push as much data as the FIFO buffer can hold, and not more.
 * @param buff Buffer to read from.
 * @param max_bytes Buffer length, or maximum number of bytes to write, limited by the FIFO buffer size.
 * @return Number of bytes successfully written.
 */
size_t comms_serial_try_write_buff_over_usb_quick(const void* buff, size_t max_bytes);

#ifdef __cplusplus
}
#endif