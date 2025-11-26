#include <comms/serial_usb.h>
#include <pico/time.h>

int comms_serial_read_line_over_usb_blocking(char* buff, size_t max_bytes, uint32_t timeout_ms)
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

        absolute_time_t now = to_us_since_boot(get_absolute_time());
        if (now - begin >= timeout_us)
            return COMMS_TIMEOUT;
    }

    buff[bytes_read] = '\0';
    return COMMS_OK;
}

int comms_serial_read_n_over_usb_blocking(char* buff, size_t max_bytes, uint32_t timeout_ms)
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

            buff[bytes_read++] = c;

            begin = to_us_since_boot(get_absolute_time());
        }

        absolute_time_t now = to_us_since_boot(get_absolute_time());
        if (now - begin >= timeout_us)
            return COMMS_TIMEOUT;
    }

    buff[bytes_read] = '\0';
    return COMMS_OK;
}

int comms_serial_try_read_line_over_usb(char* buff, size_t max_bytes)
{
    int result = COMMS_FAIL;

    if (!tud_connected())
        return COMMS_FAIL;

    size_t bytes_read = 0;
    while (bytes_read < max_bytes - 1)
    {
        tud_task();
        if (!tud_cdc_available())
            return result;
        
        int32_t try_c = tud_cdc_read_char();

        if (try_c < 0)
            return result;

        char c = (char)try_c;

        if (c == '\n' || c == '\r')
        {
            buff[bytes_read] = '\0';
            return COMMS_OK;
        }

        buff[bytes_read++] = c;

        result = COMMS_PARTIAL;
    }

    buff[bytes_read] = '\0';
    return COMMS_OK;
}

int comms_serial_try_read_n_over_usb(char* buff, size_t max_bytes)
{
    int result = COMMS_FAIL;

    if (!tud_connected())
        return COMMS_FAIL;

    size_t bytes_read = 0;
    while (bytes_read < max_bytes - 1)
    {
        tud_task();
        if (!tud_cdc_available())
            return result;

        int32_t try_c = tud_cdc_read_char();

        if (try_c < 0)
            continue;

        char c = (char)try_c;

        buff[bytes_read++] = c;

        result = COMMS_PARTIAL;
    }
    
    buff[bytes_read] = '\0';
    return COMMS_OK;
}

size_t comms_serial_write_line_over_usb_blocking(const char* buff, size_t max_bytes, uint32_t timeout_ms)
{
    size_t n = 0;
    while (buff[n] != '\n' && buff[n] != '\r')
    {
        n++;
    }

    n = n > max_bytes ? max_bytes : n;

    return comms_serial_write_n_over_usb_blocking(buff, n, timeout_ms);
}

size_t comms_serial_write_n_over_usb_blocking(const char* buff, size_t max_bytes, uint32_t timeout_ms)
{
    if (!tud_cdc_connected())
        return 0;

    absolute_time_t timeout_us = (uint64_t)timeout_ms * 1000ULL;
    absolute_time_t begin = to_us_since_boot(get_absolute_time());

    size_t bytes_written = 0;
    while (bytes_written < max_bytes)
    {
        size_t n = tud_cdc_write(buff + bytes_written, max_bytes - bytes_written);

        if (n)
        {
            tud_cdc_write_flush();
            bytes_written += n;

            begin = to_us_since_boot(get_absolute_time());
        }

        absolute_time_t now = to_us_since_boot(get_absolute_time());
        if (now - begin >= timeout_us)
            return bytes_written;
    }
    return bytes_written;
}

size_t comms_serial_try_write_line_over_usb(const char* buff, size_t max_bytes)
{
    size_t n = 0;
    while (buff[n] != '\n' && buff[n] != '\r')
    {
        n++;
    }

    n = n > max_bytes ? max_bytes : n;

    return comms_serial_try_write_n_over_usb(buff, n);
}

size_t comms_serial_try_write_n_over_usb(const char* buff, size_t max_bytes)
{
    if (!tud_cdc_connected())
        return 0;

    size_t bytes_written = 0;
    while (bytes_written < max_bytes)
    {
        size_t n = tud_cdc_write(buff, max_bytes);

        if (!n)
            return bytes_written;

        tud_cdc_write_flush();
    }
    return bytes_written;
}