if (NOT TARGET pico-comms)

    add_library(pico-comms STATIC
        src/comms/serial_usb.c
    )

    target_include_directories(pico-comms PUBLIC
        include
    )

    target_link_libraries(pico-comms
        pico_stdlib
        pico_stdio_usb
    )

endif()