add_library(controller STATIC)

target_sources(controller PRIVATE
    auth/AuthController.cpp
)

target_include_directories(controller PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(controller PUBLIC Qt6::Widgets Qt6::Core Qt6::Sql)