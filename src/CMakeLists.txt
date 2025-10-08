add_library(waffine WaffineForm.cpp WaffineForm.hpp noise_symbol.cpp noise_symbol.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../out)

add_executable(waffine_main main.cpp)
target_link_libraries(waffine_main winterval)