# CMakeList.txt: проект CMake для SimAnn; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.15)

include(FetchContent)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
  
project ("SimAnn")

include_directories(annealing)
add_subdirectory(annealing)





# Добавьте источник в исполняемый файл этого проекта.
add_executable (SimAnn "SimAnn.cpp" "SimAnn.h")
target_link_libraries(SimAnn PUBLIC Anneal  )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SimAnn PROPERTY CXX_STANDARD 17)
endif()



install(TARGETS SimAnn)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
