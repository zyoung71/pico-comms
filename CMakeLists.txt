if (NOT TARGET pico-comms)

    add_library(pico-comms STATIC
        src/comms/tiny_usb.c
    )

    target_include_directories(pico-comms PUBLIC
        include
    )
endif()