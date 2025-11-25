include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# Windows compatibility
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../out/tests)

# NOTE: due to static state, ordering of these test cases is important!
add_executable(test_caffeine test_affine_binop.cpp
        test_affine_unop.cpp
        test_affine_scalar.cpp
        test_affine_serialization.cpp
        test_affine_equals.cpp)
target_link_libraries(test_caffeine caffeine winterval GTest::gtest_main)
include(GoogleTest)

