#include <comms/serial_usb.h>

#include <stdio.h>
#include <pico/stdlib.h>

int main()
{
    stdio_init_all();

    char buff[128];
    while (1)
    {
        int result = comms_serial_read_line_over_usb_blocking(buff, sizeof(buff), 3000);
        if (result == COMMS_TIMEOUT)
        {
            printf("timed out\n");
        }
        else if (result == COMMS_OK)
            printf("%s\n", buff);
    }

    return 0;
}