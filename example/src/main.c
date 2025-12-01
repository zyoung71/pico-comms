#include <comms/serial_usb.h>

#include <stdio.h>
#include <pico/stdlib.h>

#define USE_PICO_STDIO 0

#if USE_PICO_STDIO
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...)
#endif

int main()
{
    stdio_init_all();
    
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    if (comms_serial_usb_init() == COMMS_OK)
        gpio_put(25, 1);

    char buff[128];
    while (1)
    {
        tud_task();
        int result = 1;
        size_t bytes_read;

        /* Read line blocking */
        //result = comms_serial_read_line_over_usb_blocking(buff, sizeof(buff), 3000, &bytes_read);
        
        /* Read N blocking */
        //result = comms_serial_read_n_over_usb_blocking(buff, sizeof(buff), 3000, &bytes_read);

        /* Read line non-blocking */
        //result = comms_serial_try_read_text_line_over_usb(buff, sizeof(buff), &bytes_read);

        /* Read N non-blocking */
        //result = comms_serial_try_read_n_over_usb(buff, sizeof(buff), &bytes_read);

        switch (result)
        {
            case COMMS_OK: LOG("Buffer:\t%s\n", buff); break;
            case COMMS_FAIL: LOG("Read failed.\n"); break;
            case COMMS_TIMEOUT: LOG("Timed-out.\n"); break;
            case COMMS_PARTIAL: LOG("Partial buffer:\t%s\n", buff); break;
            case COMMS_NODATA: LOG("No data available.\n"); break;
            default: break;
        }

        size_t n = comms_serial_write_str_over_usb_blocking("Test string.", 3000);
        if (n > 0)
            LOG("String successfully written.\n");
        else
            LOG("String not written.\n");
    }

    return 0;
}