add_library(waffine WaffineForm.cpp WaffineForm.hpp NoiseSymbol.cpp NoiseSymbol.h)

add_executable(waffine_test main.cpp)
target_link_libraries(waffine_test waffine)