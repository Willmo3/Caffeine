//
// Created by will on 9/23/25.
//

#include "WaffineForm.hpp"

#include <cstring>
#include <format>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

/*
 * Constructors
 */
WaffineForm::WaffineForm(double center, const std::unordered_map<noise_symbol_t, double> &starting_coeffs):
    _center(center), _coefficients(std::unordered_map<noise_symbol_t, double>()) {
    // Initialize this map with the explicitly defined starting values.
    for (auto pair : starting_coeffs) {
        _coefficients.insert(pair);
    }
}

WaffineForm::WaffineForm(const Winterval& interval): _center((interval.min() + interval.max()) / 2),
    _coefficients(std::unordered_map<noise_symbol_t, double>()) {
    _coefficients.insert(std::pair(new_noise_symbol(), (interval.min() - interval.max()) / 2));
}
// Internal clone constructor
WaffineForm WaffineForm::clone() const {
    return { this->_center, std::unordered_map(this->_coefficients) };
}

/*
 * Scalar operators
 */
WaffineForm WaffineForm::operator*(double other) const {
    auto value = clone();
    value._center *= other;
    for (auto pair : _coefficients) {
        value._coefficients[pair.first] *= other;
    }
    return value;
}
WaffineForm WaffineForm::operator+(double other) const {
    auto value = clone();
    value._center += other;
    // Notice: addition does not affect error symbols.
    // effectively, the polytope is simply being translated.
    return value;
}
WaffineForm WaffineForm::operator-(double other) const {
    auto value = clone();
    value._center -= other;
    return value;
}
WaffineForm WaffineForm::operator/(double other) const {
    // Special case: 0. In affine forms, this will set all terms to 0, leading to a unit form.
    if (other == 0) {
        return { 0, std::unordered_map<noise_symbol_t, double>() };
    }
    return operator*(1 / other);
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
    return std::accumulate(_coefficients.begin(), _coefficients.end(), 0.0,
        [](auto sum, auto pair) { return sum + std::abs(pair.second); });
}

std::vector<double> WaffineForm::noise_coefficients() const {
    return std::accumulate(_coefficients.begin(), _coefficients.end(), std::vector<double>(),
        [](auto coeffs, auto pair) { coeffs.push_back(pair.second); return coeffs; });
}

Winterval WaffineForm::to_interval() const {
    // Note: unable to do accumulation because of behavior with unordered maps.
    double error_magnitude = 0;
    for (auto coeff: _coefficients | std::views::values) {
        error_magnitude += std::abs(coeff);
    }
    return {_center - error_magnitude, _center + error_magnitude};
}
