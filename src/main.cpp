#include <iostream>
#include <ostream>

#include "WaffineForm.hpp"

void test_to_interval() {
    // Construct an affine form centered at 0 with two noise symbols -- one with coeff 1, other with coeff 0.5.
    auto value = std::unordered_map<noise_symbol_t, double>();
    value.insert(std::pair(new_noise_symbol(), 1));
    value.insert(std::pair(new_noise_symbol(), -0.5));
    std::cout << WaffineForm(0, value).to_interval() << std::endl;
}

int main() {
    test_to_interval();
    return 0;
}
