set(SOURCE
    # Pixel sources
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Pixel/BPixel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Pixel/FPixel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Pixel/DPixel.cpp
)

add_library(
    Pixel ${LIBRARY_KEYWORD} ${SOURCE}
)

target_link_libraries(Pixel ag::SIMD)

set_target_properties(
    Pixel PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION}
    PREFIX "ag"
)

target_include_directories(
    Pixel PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

install(
    TARGETS Pixel
    EXPORT agPixelConfig
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    EXPORT agPixelConfig
    NAMESPACE ag::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/agPixel
)

install(
    DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/agPixel
)
