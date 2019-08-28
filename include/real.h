#ifndef URBANITY_REAL_H
#define URBANITY_REAL_H

#include "math_conf.h"

#include <float.h>

// Define the real parameter based on the configured parameter

namespace urb {

    namespace math {

        // Standard definitions
        typedef float real_f;
        typedef double real_d;

#if URBANITY_PRECISION == URBANITY_PRECISION_FLOAT

        typedef real_f real;

        namespace constants {

            constexpr real REAL_MAX = FLT_MAX;

        } /* namespace constants */

#else /* URBANITY_PRECISION == URBANITY_PRECISION_DOUBLE */

        typedef real_d real;

        namespace constants {

            constexpr real REAL_MAX = DBL_MAX;

        } /* namespace constants */

#endif /* URBANITY_PRECISION */

    } /* namespace math */

} /* namespace urb */

#endif /* URBANITY_REAL_H */

