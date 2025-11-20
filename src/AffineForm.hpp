//
// Created by will on 9/23/25.
//

#ifndef CAFFEINE_AFFINEFORM_H
#define CAFFEINE_AFFINEFORM_H
#include <unordered_map>
#include <vector>

#include "Winterval/Winterval.hpp"
// Note: cereal root must be in the build path
#include "cereal/archives/json.hpp"
#include "cereal/types/unordered_map.hpp"

// Print time profiling of expensive functions.
// #define AFFINE_TIME_MULT
// #define AFFINE_TIME_SUB
// #define AFFINE_TIME_ABS
// #define AFFINE_TIME_ADD
// #define AFFINE_TIME_POW
// #define AFFINE_TIME_INV
// #define AFFINE_TIME_OTHER

// Author: Will Morris
// Credit to https://github.com/ogay/libaffa for cpp implementation tips.
// Credit to https://github.com/vanweric/Affapy for approximation strategies.

/**
 * Library for high performance affine form computations.
 * Affine forms are a symbolic representation of a
 * Form: x_hat + sum(real coefficient * noise_symbol).
 */
class AffineForm {

// Number of noise symbols a given affine form can accumulate before the symbols are collapsed.
#define MAX_NOISE_SYMBOLS 128

public:
    /**
     * Noise symbols are integers that refer to unique sources of error in affine forms.
     */
    typedef uint32_t noise_symbol_t;

    /*
     * Constructors
     */

    /**
     * Default constructor to initialize empty affine form.
     * Useful for seralization.
     */
    AffineForm();
    /**
     * @param center Real number center for affine form.
     * @param starting_coeffs error coefficients to prime the affine form with
     */
    AffineForm(double center, const std::unordered_map<noise_symbol_t, double> &starting_coeffs);
    /**
     * @param interval Interval to construct center, error points from.
     */
    explicit AffineForm(const Winterval &interval);

    /*
     * Accessors
     */
    std::string to_string() const;
    double center() const;
    double radius() const;
    /**
     *
     * @param symbol Symbol to get coefficient of.
     * @return the coefficient if noise symbol represented in this affine form, NaN otherwise.
     */
    double coeff_of(noise_symbol_t symbol) const;
    Winterval to_interval() const;

    /*
     * Operations
     */

    /*
     * Unary operations
     */
    AffineForm operator-() const;

    AffineForm abs() const;

    /*
     * Binary affine operations
     */
    /**
     * Additive union of error symbols.
     */
    AffineForm operator+(const AffineForm &other) const;
    /**
     * Subtractive union of error symbols.
     */
    AffineForm operator-(const AffineForm &other) const;
    /**
     * Outer product of real values with others' errors. Additional error symbol added to account for loss of precision.
     */
    AffineForm operator*(const AffineForm &right) const;
    /**
     * Product of this affine form and the inverse of the rhs.
     */
    AffineForm operator/(const AffineForm &right) const;

    /**
     * @return The affine form multiplied by itself power times.
     */
    AffineForm pow(uint32_t power) const;

    /*
     * Scalar arithmetic operations
     */
    AffineForm operator*(double other) const;
    AffineForm operator+(double other) const;
    AffineForm operator-(double other) const;
    AffineForm operator/(double other) const;
    /*
     * Scalar comparison operations
     * Note: these will be compared with the interval form of the system, as this reduces to concrete domain.
     */
    bool operator<(double other) const;
    bool operator>(double other) const;
    bool operator<=(double other) const;
    bool operator>=(double other) const;

    /*
     * Serialization helpers.
     */
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive( cereal::make_nvp("center", _center), cereal::make_nvp("noise_symbols", _coefficients) );
    }

    /*
     * Assorted helpers
     */

    /**
     * Return whether two affine forms are exactly equal.
     * This means they have the same noise symbols with the same coefficients.
     *
     * @param other Waffine form to compare against.
     * @return Whether the two forms are exactly equal.
     */
    bool operator==(const AffineForm &other) const;

private:
    /*
     * Noise symbol handling
     */
    static noise_symbol_t max_noise_symbol;

    static noise_symbol_t new_noise_symbol();

    /*
     * Non-affine function approximator helpers.
     */

    /**
     * Construct an affine approximation of this form applied to some non-affine function.
     * Form: (x_hat = alpha * x0 + zeta) + sum over errors (alpha * x_i * epsilon_i) + delta * epsilon_k
     * Generalizes first-order Chebyshev form alpha_x + beta (although we don't always use Chebyshev)
     * Implementation derived from Affapy.
     *
     * @param alpha Scalar multiplier for each error term.
     * @param zeta Constant offset for center term
     * @param delta Coefficient for new error term.
     * @return The affine approximation.
     */
    AffineForm approximate_affine_form(double alpha, double zeta, double delta) const;
    /**
     * @return A new affine form representing the inverse of this form.
     * Approximate with mini-range.
     */
    AffineForm inv() const;

    /*
     * Assorted helpers.
     */

    /**
     * @return A deep copy of this affine form.
     */
    AffineForm clone() const;

    /**
     * Collapse all the error symbols in this affine form to a single, high-magnitude error.
     */
    void collapse();

    /*
     * Fields
     */

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

// AffineForm::noise_symbol_t AffineForm::max_noise_symbol = 0;

// Using reference to remove redundant copy.
// TODO: reflect this change elsewhere.
std::ostream& operator<<(std::ostream& os, AffineForm rhs);


#endif //CAFFEINE_AFFINEFORM_H
