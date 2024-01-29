cmake_minimum_required (VERSION 3.22)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

project(logger
  LANGUAGES CXX
  VERSION 1.2.3
  DESCRIPTION "A simple single instance logger"
)
add_library(liblogger
	logger.cc
	logger.hh
)
#configure file
set(LOG_FOLDER "${CMAKE_BINARY_DIR}/../data/logs/")
set(LOG_PREFIX "${CMAKE_PROJECT_NAME}(${CMAKE_PROJECT_VERSION})")
configure_file("logger_config.h.in" "logger_config.h" @ONLY)
#
target_include_directories(liblogger
	PUBLIC
		${CMAKE_CURRENT_BINARY_DIR} #for logger_config.h
		${CMAKE_CURRENT_SOURCE_DIR}
)
set_target_properties(liblogger PROPERTIES CXX_STANDARD 20)
target_compile_options(liblogger PUBLIC -Werror -Wextra -Wpedantic)
