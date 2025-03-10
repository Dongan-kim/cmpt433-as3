# CMakeList.txt for HAL
#   Build a library (`hal`) which exposes the header files as "hal/*.h"
#   Use header as: #include "hal/button.h"

include_directories(${CMAKE_SOURCE_DIR}/app/include)
file(GLOB MY_SOURCES "src/*.c")

# Create HAL static library
add_library(hal STATIC ${MY_SOURCES})

# Find and link GPIO libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(GPIOD REQUIRED libgpiod)

target_include_directories(hal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${GPIOD_INCLUDE_DIRS})
target_link_libraries(hal PRIVATE ${GPIOD_LIBRARIES} lcd lgpio)
