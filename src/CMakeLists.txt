cmake_minimum_required(VERSION 3.0.0)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_BUILD_DIR ${PROJECT_SOURCE_DIR}/build)

# pneuser begin
SET(GCC_COVERAGE_COMPILE_FLAGS "-D_FILE_OFFSET_BITS=64")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
add_subdirectory("headers_p")
# pneuser end

#Add any source files that will create a single library
set(syncfs_LIB
    syncfs.cpp
)

if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
	execute_process(
		COMMAND git rev-parse HEAD
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		OUTPUT_VARIABLE GIT_BRANCH
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
else()
	set(GIT_BRANCH "Unknown")
endif()
add_definitions(-DGIT_BRANCH=${GIT_BRANCH})
#set build dir for your library
set(LIBRARY_OUTPUT_PATH ${CMAKE_BUILD_DIR}/lib)
message( STATUS "LIBRARY_OUTPUT_PATH: " ${LIBRARY_OUTPUT_PATH} )

set(LIBRARY_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/lib)
message( STATUS "LIBRARY_INSTALL_PATH: " ${LIBRARY_INSTALL_PATH} )

file(MAKE_DIRECTORY ${LIBRARY_OUTPUT_PATH})

# Tell CMake to create the syncfs shared lib and set it's properties
add_library(syncfs SHARED ${syncfs_LIB})
set_target_properties(syncfs
    PROPERTIES
    VERSION 0.1
    SOVERSION 0
    )

#If your app, links to an external lib -ie Boost
#target_link_libraries( syncfs ${Boost_LIBRARIES} )

# Install
install(TARGETS syncfs
        LIBRARY DESTINATION lib
        )

add_subdirectory(headers)

#pneuser begin
target_include_directories(syncfs PUBLIC headers_p)
#end pneuser
