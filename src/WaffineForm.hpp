//
// Created by will on 9/23/25.
//

#ifndef WAFFINE_WAFFINEFORM_H
#define WAFFINE_WAFFINEFORM_H
#include <unordered_map>
#include "noise_symbol.h"
#include "../lib/Winterval/src/Winterval.hpp"

// Author: Will Morris
// Credit to https://github.com/ogay/libaffa for cpp implementation tips.
// Credit to https://github.com/vanweric/Affapy for approximation strategies.

/*

We may want to convert to a zonotope, but for now, let's add support for generic affine intervals
Conceptual understanding of difference:
- Center represents center of zonotope
- Noise symbols represent basis lines

Then sum is defined as minkowski sum of these lines.

We can construct with two things.
- Interval [a, b], centered at (a + b) / 2 and with error term (a - b) / 2.
- Center and error term list

Must support:
- Conversion to interval
    - This is how we can print.
- Exact affine operations
    - Affine addition
    - Affine subtraction
    - Constant multiplication, subtraction, addition, division
- Affine approximations for other operations required for Numeric concept.

- Affine form should support a radius operation for error computation
    - this will be introduced as a new noise symbol.

 */

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
    // TODO: from interval
    // TODO: from center, noise symbols.
    WaffineForm(double center, const std::unordered_map<noise_symbol_t, double> &starting_coeffs);
    ~WaffineForm();

    /*
     * Accessors
     */
    Winterval to_interval() const;
    // TODO: to_interval
    // TODO: radius

    /*
     * Operations
     */

    // TODO: affine-affine add
    // TODO: affine-affine sub
    // TODO: affine-affine mult
    // TODO: affine-affine div

    // TODO: scalar multiply
    // TODO: scalar add
    // TODO: scalar divide
    // TODO: scalar subtract

private:

    /**
     * Center point for affine shape.
     */
    double _center;
    /**
     * Map of noise symbols to their coefficients.
     */
    std::unordered_map<noise_symbol_t, double> *_coefficients;
};


#endif //WAFFINE_WAFFINEFORM_H