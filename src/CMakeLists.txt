add_library(waffine WaffineForm.cpp WaffineForm.hpp noise_symbol.cpp noise_symbol.h)

add_executable(waffine_test main.cpp)
target_link_libraries(waffine_test waffine winterval)