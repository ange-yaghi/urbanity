#ifndef URBANITY_MATH_SINGLE_H
#define URBANITY_MATH_SINGLE_H

#include "real.h"

#include <math.h>
#include <random>

#define MATH_CONST extern const __declspec(selectany)

namespace urb {

    namespace math {

        // Vector types
        struct Generic {
            union {
                union {
                    struct {
                        real x, y, z, w;
                    };
                    struct {
                        real qw, qx, qy, qz;
                    };
                };
                real v[4];
            };
        };

        typedef Generic Vector;
        typedef Generic Quaternion;

    } /* namespace math */

} /* namespace urb */

#endif /* URBANITY_MATH_SINGLE_H */
