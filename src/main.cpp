#include "WaffineForm.hpp"

int main() {
    auto value = std::unordered_map<noise_symbol_t, double>();
    value.insert(std::pair<noise_symbol_t, double>(new_noise_symbol(), 1));
    // new affine form centered at 0 with a single noisesymbol with value 1.
    auto form = WaffineForm(0, value);
    return 0;
}
