add_library(core STATIC)

target_sources(core PRIVATE
	ApplicationContext.cpp
)

target_include_directories(core PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(core PUBLIC Qt6::Widgets Qt6::Core Qt6::Sql)