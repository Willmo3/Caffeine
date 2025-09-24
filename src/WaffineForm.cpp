//
// Created by will on 9/23/25.
//

#include "WaffineForm.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ostream>

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

/*
 * Accessors
 */
Winterval WaffineForm::to_interval() const {
    // Note: unable to do accumulation because of behavior with unordered maps.
    double error_magnitude = 0;
    for (auto pair : *_coefficients) {
        error_magnitude += std::abs(pair.second);
    }
    return {_center - error_magnitude, _center + error_magnitude};
}
