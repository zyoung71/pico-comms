#include <comms/serial_usb.h>

#include <stdio.h>
#include <pico/stdlib.h>

int main()
{
    stdio_init_all();

    char buff[128];
    while (1)
    {
        int result = COMMS_FAIL;
        
        /* Read line blocking */
        //result = comms_serial_read_line_over_usb_blocking(buff, sizeof(buff), 3000);
        
        /* Read N blocking */
        //result = comms_serial_read_n_over_usb_blocking(buff, sizeof(buff), 3000);

        /* Read line non-blocking */
        result = comms_serial_try_read_line_over_usb(buff, sizeof(buff));

        /* Read N non-blocking */
        //result = comms_serial_try_read_n_over_usb(buff, sizeof(buff));

        if (result == COMMS_TIMEOUT)
        {
            printf("timed out\n");
        }
        else if (result == COMMS_OK)
            printf("%s\n", buff);
    }

    return 0;
}