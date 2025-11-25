add_library(caffeine AffineForm.cpp AffineForm.hpp)
add_subdirectory(test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../out)

add_executable(caffeine_main main.cpp)
target_link_libraries(caffeine_main caffeine winterval)