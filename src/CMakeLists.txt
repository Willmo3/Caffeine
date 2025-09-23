add_library(waffine WaffineForm.cpp WaffineForm.hpp)

add_executable(waffine_test main.cpp)
target_link_libraries(waffine_test waffine)