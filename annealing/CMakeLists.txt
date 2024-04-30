if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(SOURCE_F anneal.cpp anneal.hpp plane.hpp point.hpp)
add_library(Anneal  ${SOURCE_F} )

