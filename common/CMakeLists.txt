add_library(common STATIC)

target_sources(common PRIVATE
    utils/Logger.cpp
    utils/Time.cpp
)

target_include_directories(common PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(common PRIVATE Qt6::Widgets)