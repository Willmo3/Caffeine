//
// Created by will on 9/23/25.
//

#ifndef WAFFINE_WAFFINEFORM_H
#define WAFFINE_WAFFINEFORM_H

/*

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

 */

class WaffineForm {
    // must support:
    // - conversion to interval
    // - exact affine operations
};


#endif //WAFFINE_WAFFINEFORM_H