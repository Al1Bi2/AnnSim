cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Сначала добавляем свою библиотеку
add_subdirectory(annealing)

message(STATUS ${Anneal_LIBRARIES})
include_directories(annealing)

# Затем добавляем исполняемый файл
add_executable(SimAnn src/SimAnn.cpp)
target_link_libraries(SimAnn PRIVATE sfml-graphics Anneal)
target_compile_features(SimAnn PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET SimAnn
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:SimAnn>
        VERBATIM)
endif()

install(TARGETS SimAnn)