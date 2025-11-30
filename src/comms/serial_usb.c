#include <comms/serial_usb.h>
#include <pico/time.h>

int comms_serial_usb_init(void)
{
    if (!tusb_inited())
    {
        if (tusb_init())
            return 0;
        return -1;
    }
    return 0;
}

int comms_serial_read_text_line_over_usb_blocking(char* buff, size_t max_bytes, uint32_t timeout_ms)
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

int comms_serial_read_text_n_over_usb_blocking(char* buff, size_t max_bytes, uint32_t timeout_ms)
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

int comms_serial_try_read_text_line_over_usb(char* buff, size_t max_bytes)
{
    int result = COMMS_NODATA;

    if (!tud_cdc_connected())
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

int comms_serial_try_read_text_n_over_usb(char* buff, size_t max_bytes)
{
    int result = COMMS_NODATA;

    if (!tud_cdc_connected())
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

size_t comms_serial_write_text_line_over_usb_blocking(const char* buff, size_t max_bytes, uint32_t timeout_ms)
{
    size_t n = 0;
    while (buff[n] != '\n' && buff[n] != '\r' && buff[n] != '\0')
    {
        n++;
    }

    n = n > max_bytes ? max_bytes : n;

    return comms_serial_write_buff_over_usb_blocking(buff, n, timeout_ms);
}

size_t comms_serial_try_write_text_line_over_usb(const char* buff, size_t max_bytes)
{
    size_t n = 0;
    while (buff[n] != '\n' && buff[n] != '\r' && buff[n] != '\0')
    {
        n++;
    }

    n = n > max_bytes ? max_bytes : n;

    return comms_serial_try_write_buff_over_usb(buff, n);
}

int comms_serial_read_buff_over_usb_blocking(void* buff, size_t max_bytes, uint32_t timeout_ms)
{
    if (!tud_cdc_connected())
        return COMMS_FAIL;

    absolute_time_t timeout_us = (uint64_t)timeout_ms * 1000ULL;
    absolute_time_t begin = to_us_since_boot(get_absolute_time());
    
    size_t bytes_read = 0;
    while (bytes_read < max_bytes)
    {
        tud_task();
        uint32_t avail = tud_cdc_available();
        if (avail)
        {
            size_t remaining = max_bytes - bytes_read;
            size_t read_amount = remaining < avail ? remaining : avail;
            
            size_t this_inst_read = tud_cdc_read(buff + bytes_read, read_amount);
            if (this_inst_read)
            {
                bytes_read += this_inst_read;
                begin = to_us_since_boot(get_absolute_time());
            }
        }

        absolute_time_t now = to_us_since_boot(get_absolute_time());
        if (now - begin >= timeout_us)
            return COMMS_TIMEOUT;
    }
    return COMMS_OK;
}

int comms_serial_try_read_buff_over_usb(void* buff, size_t max_bytes)
{
    if (!tud_cdc_connected())
        return COMMS_FAIL;

    int result = COMMS_NODATA;

    size_t bytes_read = 0;
    while (bytes_read < max_bytes)
    {
        tud_task();
        uint32_t avail = tud_cdc_available();
        if (!avail)
            return result;

        size_t remaining = max_bytes - bytes_read;
        size_t read_amount = remaining < avail ? remaining : avail;
        
        size_t this_inst_read = tud_cdc_read(buff + bytes_read, read_amount);
        if (this_inst_read)
        {
            bytes_read += this_inst_read;
            result = COMMS_PARTIAL;
        }
    }
    return COMMS_OK;
}

size_t comms_serial_write_buff_over_usb_blocking(const void* buff, size_t max_bytes, uint32_t timeout_ms)
{
    if (!tud_cdc_connected())
        return 0;

    absolute_time_t timeout_us = (uint64_t)timeout_ms * 1000ULL;
    absolute_time_t begin = to_us_since_boot(get_absolute_time());

    size_t bytes_written = 0;
    while (bytes_written < max_bytes)
    {
        tud_task();
        uint32_t avail = tud_cdc_write_available();
        if (avail)
        {
            size_t remaining = max_bytes - bytes_written;
            size_t write_amount = remaining < avail ? remaining : avail; // limit to available bytes if needed

            size_t this_inst_written = tud_cdc_write(buff + bytes_written, write_amount);
            if (this_inst_written)
            {
                tud_cdc_write_flush();
                bytes_written += this_inst_written;
            }

            begin = to_us_since_boot(get_absolute_time());
        }

        absolute_time_t now = to_us_since_boot(get_absolute_time());
        if (now - begin >= timeout_us)
            return bytes_written;        
    }
    return bytes_written;
}

size_t comms_serial_try_write_buff_over_usb(const void* buff, size_t max_bytes)
{
    if (!tud_cdc_connected())
        return 0;
        
    size_t bytes_written = 0;
    while (bytes_written < max_bytes)
    {
        tud_task();
        uint32_t avail = tud_cdc_write_available();
        if (!avail)
            return bytes_written;

        size_t remaining = max_bytes - bytes_written;
        size_t write_amount = remaining < avail ? remaining : avail;

        size_t this_inst_written = tud_cdc_write(buff + bytes_written, write_amount);
        if (this_inst_written)
        {
            tud_cdc_write_flush();
            bytes_written += this_inst_written;
        }
    }
    return bytes_written;
}

size_t comms_serial_write_str_over_usb_blocking(const char* strbuff, uint32_t timeout_ms)
{
    return comms_serial_write_buff_over_usb_blocking(strbuff, strlen(strbuff), timeout_ms);
}

size_t comms_serial_try_write_str_over_usb(const char* strbuff)
{
    return comms_serial_try_write_buff_over_usb(strbuff, strlen(strbuff));
}

int comms_serial_try_read_buff_over_usb_quick(void* buff, size_t max_bytes)
{
    if (!tud_cdc_connected())
        return COMMS_FAIL;

    tud_task();

    size_t avail = tud_cdc_available();
    if (!avail)
        return COMMS_NODATA;

    size_t bytes_read = tud_cdc_read(buff, max_bytes);

    if (bytes_read == 0)
        return COMMS_FAIL;
    if (bytes_read < max_bytes)
        return COMMS_PARTIAL;
    return COMMS_OK;
}

size_t comms_serial_try_write_buff_over_usb_quick(const void* buff, size_t max_bytes)
{
    if (!tud_cdc_connected())
        return 0;

    tud_task();

    size_t avail = tud_cdc_write_available();
    if (!avail)
        return 0;

    size_t bytes_written = tud_cdc_write(buff, max_bytes);
    if (bytes_written)
        tud_cdc_write_flush();

    return bytes_written;
}