#include <comms/tiny_usb.h>

bool comms_read_serial_over_usb(char* buff, size_t max_bytes)
{
    size_t bytes_read = 0;
    while (bytes_read < max_bytes - 1)
    {
        tud_task();
        int32_t try_c = tud_cdc_read_char();

        if (try_c < 0)
            return 0;
        
        char c = (char)try_c;

        if (c == '\n' || c == '\r')
        {
            buff[bytes_read] = '\0';
            return true;
        }

        buff[bytes_read++] = c;
    }

    buff[bytes_read] = '\0';
    return true;
}