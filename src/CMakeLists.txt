add_library(caffeine AffineForm.cpp AffineForm.hpp noise_symbol.cpp noise_symbol.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../out)

add_executable(caffeine_main main.cpp)
target_link_libraries(caffeine_main caffeine winterval)