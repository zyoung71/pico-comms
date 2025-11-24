#include <comms/tiny_usb.h>
#include <pico/time.h>

int comms_read_serial_over_usb(char* buff, size_t max_bytes, uint32_t timeout_ms)
{
    if (!tud_cdc_connected())
        return COMMS_FAIL;

    absolute_time_t timeout_us = (uint64_t)timeout_ms * 1000ULL;
    absolute_time_t begin = to_us_since_boot(get_absolute_time());

    size_t bytes_read = 0;
    while (bytes_read < max_bytes - 1)
    {
        tud_task();
        if (tud_cdc_available())
        {
            int32_t try_c = tud_cdc_read_char();

            if (try_c < 0)
                continue;
            
            char c = (char)try_c;

            if (c == '\n' || c == '\r')
            {
                buff[bytes_read] = '\0';
                return COMMS_OK;
            }

            buff[bytes_read++] = c;

            begin = to_us_since_boot(get_absolute_time());
        }

        uint64_t now = to_us_since_boot(get_absolute_time());
        if (now - begin >= timeout_us)
            return COMMS_TIMEOUT;
    }

    buff[bytes_read] = '\0';
    return COMMS_OK;
}