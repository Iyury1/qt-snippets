set(TIMER_SOURCES
    CustomTimer.cpp
)

find_package(Qt6 REQUIRED COMPONENTS Core)


add_library(elmc_timer
    ${TIMER_SOURCES}
)

target_include_directories(elmc_timer
    PUBLIC
    ${PROJECT_SOURCE_DIR}/src/interfaces
)

# target_compile_options(elmc_timer
#     PRIVATE
#     -g
# )

target_link_libraries(
	elmc_timer
	PUBLIC
	Qt6::Core
    elmc_logger
)

