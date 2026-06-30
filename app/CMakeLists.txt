add_library(app STATIC)

target_sources(app PRIVATE
    AppManager.cpp
    SessionManager.cpp
)

target_include_directories(app PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(app PUBLIC Qt6::Widgets Qt6::Core Qt6::Sql)