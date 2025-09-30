#include <iostream>
#include <ostream>

#include "WaffineForm.hpp"

/*
 * Affine-Affine tests
 */
void test_affine_add() {
    auto base = WaffineForm(Winterval(-2, 3));
    auto next = base + WaffineForm(Winterval(4, 5));
    std::cout << next.to_string() << std::endl;
    // Check error symbol correspondence.
    std::cout << (next + base).to_string() << std::endl;
}
void test_affine_sub() {
    auto base = WaffineForm(Winterval(-2, 3));
    auto next = base - WaffineForm(Winterval(4, 5));
    std::cout << next.to_string() << std::endl;
    // Check error symbol correspondence.
    // Notice: because we track the source of error, when we remove the base interval, we get the negation of next!
    std::cout << (next - base).to_string() << std::endl;
}
void test_affine_mult() {
    auto base = WaffineForm(Winterval(-2, 3));
    std::cout << base.to_string() << std::endl;
    auto other = WaffineForm(Winterval(4, 5));
    std::cout << other.to_string() << std::endl;
    auto next = base * other;
    std::cout << next.to_string() << std::endl;
}
void test_affine_div() {
    auto base = WaffineForm(Winterval(-2, 3));
    std::cout << base.to_string() << std::endl;
    auto other = WaffineForm(Winterval(4, 5));
    std::cout << other.to_string() << std::endl;
    auto next = base / other;
    std::cout << next.to_string() << std::endl;
}

/*
 * Scalar tests
 */
void test_scalar_comparison() {
    auto base = WaffineForm(Winterval(-2, 3));
    std::cout << base.to_string() << std::endl;
    std::cout << (base > -2) << std::endl;
    std::cout << (base >= -2) << std::endl;
    std::cout << (base < 3) << std::endl;
    std::cout << (base <= 3) << std::endl;
}
void test_scalar_mult() {
    auto base = WaffineForm(Winterval(-2, 3));
    std::cout << base.to_string() << std::endl;
    auto next = base * 2;
    std::cout << next.to_string() << std::endl;
}
void test_scalar_div() {
    auto base = WaffineForm(Winterval(-2, 3));
    std::cout << base.to_string() << std::endl;
    auto next = base / 2;
    std::cout << next.to_string() << std::endl;
    auto next_zero = base / 0;
    std::cout << next_zero.to_string() << std::endl;
}
void test_scalar_add() {
    auto base = WaffineForm(Winterval(-2, 3));
    std::cout << base.to_string() << std::endl;
    auto next = base + 2;
    std::cout << next.to_string() << std::endl;
}
void test_scalar_sub() {
    auto base = WaffineForm(Winterval(-2, 3));
    std::cout << base.to_string() << std::endl;
    auto next = base - 2;
    std::cout << next.to_string() << std::endl;
}

void test_from_interval() {
    std::cout << WaffineForm(Winterval(-1, 1)).to_string() << std::endl;
}

void test_to_interval() {
    // Construct an affine form centered at 0 with two noise symbols -- one with coeff 1, other with coeff 0.5.
    auto value = std::unordered_map<noise_symbol_t, double>();
    value.insert(std::pair(new_noise_symbol(), 1));
    value.insert(std::pair(new_noise_symbol(), -0.5));
    std::cout << WaffineForm(0, value).to_interval() << std::endl;
}

void test_radius() {
    auto value = std::unordered_map<noise_symbol_t, double>();
    value.insert(std::pair(new_noise_symbol(), 1));
    value.insert(std::pair(new_noise_symbol(), -1));
    std::cout << WaffineForm(0, value).radius() << std::endl;
}

int main() {
    test_affine_neg();
    return 0;
}