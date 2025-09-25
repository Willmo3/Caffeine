//
// Created by will on 9/23/25.
//

#include "WaffineForm.hpp"

#include <algorithm>
#include <format>
#include <iostream>
#include <numeric>
#include <vector>

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
WaffineForm::WaffineForm(const Winterval& interval): _center((interval.min() + interval.max()) / 2),
    _coefficients(new std::unordered_map<noise_symbol_t, double>) {
    _coefficients->insert(std::pair(new_noise_symbol(), (interval.min() - interval.max()) / 2));
}

WaffineForm::~WaffineForm() {
    delete _coefficients;
}

/*
 * Accessors
 */
std::string WaffineForm::to_string() const {
    std::string retval = std::string();
    retval += "Interval concretization: ";
    retval += "[" + std::to_string(to_interval().min());
    retval += ", ";
    retval += std::to_string(to_interval().max()) + "]\n";
    retval += "Center: " + std::to_string(_center) + "\n";
    retval += "Radius: " + std::to_string(radius()) + "\n";
    retval += "Noise coefficients:";
    for (auto coeff : noise_coefficients()) {
        retval += " " + std::to_string(coeff) + ",";
    }
    retval += "\n";
    return retval;
}

double WaffineForm::center() const {
    return _center;
}

double WaffineForm::radius() const {
    return std::accumulate(_coefficients->begin(), _coefficients->end(), 0.0,
        [](auto sum, auto pair) { return sum + std::abs(pair.second); });
}

std::vector<double> WaffineForm::noise_coefficients() const {
    return std::accumulate(_coefficients->begin(), _coefficients->end(), std::vector<double>(),
        [](auto coeffs, auto pair) { coeffs.push_back(pair.second); return coeffs; });
}

Winterval WaffineForm::to_interval() const {
    // Note: unable to do accumulation because of behavior with unordered maps.
    double error_magnitude = 0;
    for (auto pair : *_coefficients) {
        error_magnitude += std::abs(pair.second);
    }
    return {_center - error_magnitude, _center + error_magnitude};
}
