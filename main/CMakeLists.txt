idf_component_register(
    SRCS
    "main.c"
    "led.c"
    "wifi.c"
    "http.c"

    INCLUDE_DIRS "."
)

spiffs_create_partition_image(www ${CMAKE_SOURCE_DIR}/www FLASH_IN_PROJECT)
