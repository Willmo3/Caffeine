//
// Created by will on 9/23/25.
//

#ifndef WAFFINE_WAFFINEFORM_H
#define WAFFINE_WAFFINEFORM_H
#include <unordered_map>
#include <vector>

#include "noise_symbol.h"
#include "../lib/Winterval/src/Winterval.hpp"

// Author: Will Morris
// Credit to https://github.com/ogay/libaffa for cpp implementation tips.
// Credit to https://github.com/vanweric/Affapy for approximation strategies.

/**
 * Library for high performance affine form computations.
 * Affine forms are a symbolic representation of a
 * Form: x_hat + sum(real coefficient * noise_symbol).
 */
class WaffineForm {

public:
    /*
     * Constructors
     */
    /**
     * @param center Real number center for affine form.
     * @param starting_coeffs error coefficients to prime the affine form with
     */
    WaffineForm(double center, const std::unordered_map<noise_symbol_t, double> &starting_coeffs);
    /**
     * @param interval Interval to construct center, error points from.
     */
    explicit WaffineForm(const Winterval &interval);

    /*
     * Accessors
     */
    std::string to_string() const;
    double center() const;
    double radius() const;
    std::vector<double> noise_coefficients() const;
    Winterval to_interval() const;

    /*
     * Operations
     */

    // NOTE: do we want to require references for these? Might be worth considering, even though we won't be able to perform nested additions.
    // We might also consider changing the intervals to do this.
    // TODO: affine-affine add
    // TODO: affine-affine sub
    // TODO: affine-affine mult
    // TODO: affine-affine div

    WaffineForm operator*(double other) const;
    WaffineForm operator+(double other) const;
    WaffineForm operator-(double other) const;
    WaffineForm operator/(double other) const;

    // TODO: scalar comparison operators -- needed for CFL checks.
    // When comparing scalars, will need to convert to interval form -- that way, we move from the abstract domain to the concrete scalar domain.

private:
    /**
     * @return A deep copy of this affine form.
     */
    WaffineForm clone() const;
    /**
     * Center point for affine shape.
     */
    double _center;
    /**
     * Map of noise symbols to their coefficients.
     * Note that values will be heap allocated, so this data structure has a fixed size.
     */
    std::unordered_map<noise_symbol_t, double> _coefficients;
};


#endif //WAFFINE_WAFFINEFORM_H