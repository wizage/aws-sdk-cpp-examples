# minimal CMakeLists.txt for the AWS SDK for C++

cmake_minimum_required(VERSION 2.8)

# "main" is just an example value.
project(main)

# Locate the AWS SDK for C++ package.
# Requires that you build with:
#   -Daws-sdk-cpp_DIR=/path/to/sdk_build
# or export/set:
#   CMAKE_PREFIX_PATH=/path/to/sdk_build
find_package(aws-sdk-cpp)

# Link to the SDK shared libraries.
add_definitions(-DUSE_IMPORT_EXPORT)

# The executable name and its sourcefiles
add_executable(main main.cpp)

# The libraries used by your executable.
target_link_libraries(main aws-cpp-sdk-firehose)