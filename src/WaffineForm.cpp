//
// Created by will on 9/23/25.
//

#include "WaffineForm.hpp"

#include <algorithm>

/*
 * Constructors
 */
WaffineForm::WaffineForm(double center, const std::unordered_map<noise_symbol_t, double> &starting_coeffs):
    _center(center), _coefficients(new std::unordered_map<noise_symbol_t, double>) {
    // Initialize this map with the explicitly defined starting values.
    for (auto pair : starting_coeffs) {
        _coefficients->insert(pair);
    }
}

WaffineForm::~WaffineForm() {
    delete _coefficients;
}
