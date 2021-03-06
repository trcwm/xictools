
/*========================================================================*
 *                                                                        *
 *  Distributed by Whiteley Research Inc., Sunnyvale, California, USA     *
 *                       http://wrcad.com                                 *
 *  Copyright (C) 2017 Whiteley Research Inc., all rights reserved.       *
 *  Author: Stephen R. Whiteley, except as indicated.                     *
 *                                                                        *
 *  As fully as possible recognizing licensing terms and conditions       *
 *  imposed by earlier work from which this work was derived, if any,     *
 *  this work is released under the Apache License, Version 2.0 (the      *
 *  "License").  You may not use this file except in compliance with      *
 *  the License, and compliance with inherited licenses which are         *
 *  specified in a sub-header below this one if applicable.  A copy       *
 *  of the License is provided with this distribution, or you may         *
 *  obtain a copy of the License at                                       *
 *                                                                        *
 *        http://www.apache.org/licenses/LICENSE-2.0                      *
 *                                                                        *
 *  See the License for the specific language governing permissions       *
 *  and limitations under the License.                                    *
 *                                                                        *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,      *
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES      *
 *   OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-        *
 *   INFRINGEMENT.  IN NO EVENT SHALL WHITELEY RESEARCH INCORPORATED      *
 *   OR STEPHEN R. WHITELEY BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER     *
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,      *
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE       *
 *   USE OR OTHER DEALINGS IN THE SOFTWARE.                               *
 *                                                                        *
 *========================================================================*
 *               XicTools Integrated Circuit Design System                *
 *                                                                        *
 * Sparse Matrix Package
 *                                                                        *
 *========================================================================*
 $Id:$
 *========================================================================*/

//======= Original Header ================================================
//
//  MACRO DEFINITIONS for Sparse.
//
//  Author:                     Advising professor:
//      Kenneth S. Kundert          Alberto Sangiovanni-Vincentelli
//      UC Berkeley
//
// This file contains common type definitions and macros for the
// sparse matrix routines.  These definitions are of no interest to
// the user.

//  Revision and copyright information.
//
//  Copyright (c) 1985,86,87,88,89,90
//  by Kenneth S. Kundert and the University of California.
//
//  Permission to use, copy, modify, and distribute this software and
//  its documentation for any purpose and without fee is hereby granted,
//  provided that the copyright notices appear in all copies and
//  supporting documentation and that the authors and the University of
//  California are properly credited.  The authors and the University of
//  California make no representations as to the suitability of this
//  software for any purpose.  It is provided `as is', without express
//  or implied warranty.
//========================================================================

// For fabs.
#include <math.h>

//   MACRO DEFINITIONS
//
// Macros are distinguished by using solely capital letters in their
// identifiers.  This contrasts with C defined identifiers which are
// strictly lower case, and program variable and procedure names which
// use both upper and lower case.

// Begin macros

#define  NO             0
#define  YES            1
#define  NOT            !
#define  AND            &&
#define  OR             ||

// Macro commands
// Macro functions that return the maximum or minimum independent of type.
#ifndef SPMIN
#define  SPMAX(a,b)         ((a) > (b) ? (a) : (b))
#define  SPMIN(a,b)         ((a) < (b) ? (a) : (b))
#endif

// Macro function that returns the absolute value of a floating point
// number.  The fabs call is faster on modern hardware than the
// conditional
//#define  ABS(a)             ((a) < 0 ? -(a) : (a))
#define  ABS(a)             fabs(a)
#define  LABS(a)            fabsl(a)

// Macro function that returns the square of a number.
#define  SQR(a)             ((a)*(a))

// Macro procedure that swaps two entities.
#define  SWAP(type, a, b)   { type swapx; swapx = a; a = b; b = swapx; }

// Long-double coersion.
#define LDBL(foo) (*(long double*)foo)

// Macro function that returns the approx absolute value of a complex
// number.

#if SP_OPT_COMPLEX
#if SP_OPT_LONG_DBL_SOLVE
#define  E_MAG(ptr) (Complex ? (ABS((ptr)->Real) + ABS((ptr)->Imag)) : \
        (LongDoubles ? LABS(LDBL(ptr)) : ABS(ptr->Real)))
#else
#define  E_MAG(ptr) (Complex ? (ABS((ptr)->Real) + ABS((ptr)->Imag)) : \
        (ABS((ptr)->Real)))
#endif
#else
#if SP_OPT_LONG_DBL_SOLVE
#define  E_MAG(ptr) (LongDoubles ? LABS(LDBl(ptr)) : ABS(ptr->Real)))
#else
#define  E_MAG(ptr) (ABS((ptr)->Real))
#endif
#endif

// Complex assignment statements
#define  CMPLX_ASSIGN(to,from)  \
{   (to).Real = (from).Real;    \
    (to).Imag = (from).Imag;    \
}
#define  CMPLX_CONJ_ASSIGN(to,from)     \
{   (to).Real = (from).Real;            \
    (to).Imag = -(from).Imag;           \
}
#define  CMPLX_NEGATE_ASSIGN(to,from)   \
{   (to).Real = -(from).Real;           \
    (to).Imag = -(from).Imag;           \
}
#define  CMPLX_CONJ_NEGATE_ASSIGN(to,from)      \
{   (to).Real = -(from).Real;                   \
    (to).Imag = (from).Imag;                    \
}
#define  CMPLX_CONJ(a)  (a).Imag = -(a).Imag
#define  CMPLX_NEGATE(a)        \
{   (a).Real = -(a).Real;       \
    (a).Imag = -(a).Imag;       \
}

// Macro that returns the approx magnitude (L-1 norm) of a complex number.
#define  CMPLX_1_NORM(a)        (ABS((a).Real) + ABS((a).Imag))

// Macro that returns the approx magnitude (L-infinity norm) of a complex.
#define  CMPLX_INF_NORM(a)      (MAX (ABS((a).Real),ABS((a).Imag)))

// Macro function that returns the magnitude (L-2 norm) of a complex number.
#define  CMPLX_2_NORM(a)        (sqrt((a).Real*(a).Real + (a).Imag*(a).Imag))

// Macro function that performs complex addition.
#define  CMPLX_ADD(to,from_a,from_b)            \
{   (to).Real = (from_a).Real + (from_b).Real;  \
    (to).Imag = (from_a).Imag + (from_b).Imag;  \
}

// Macro function that performs complex subtraction.
#define  CMPLX_SUBT(to,from_a,from_b)           \
{   (to).Real = (from_a).Real - (from_b).Real;  \
    (to).Imag = (from_a).Imag - (from_b).Imag;  \
}

// Macro function that is equivalent to += operator for complex numbers.
#define  CMPLX_ADD_ASSIGN(to,from)      \
{   (to).Real += (from).Real;           \
    (to).Imag += (from).Imag;           \
}

// Macro function that is equivalent to -= operator for complex numbers.
#define  CMPLX_SUBT_ASSIGN(to,from)     \
{   (to).Real -= (from).Real;           \
    (to).Imag -= (from).Imag;           \
}

// Macro function that multiplies a complex number by a scalar.
#define  SCLR_MULT(to,sclr,cmplx)       \
{   (to).Real = (sclr) * (cmplx).Real;  \
    (to).Imag = (sclr) * (cmplx).Imag;  \
}

// Macro function that multiply-assigns a complex number by a scalar.
#define  SCLR_MULT_ASSIGN(to,sclr)      \
{   (to).Real *= (sclr);                \
    (to).Imag *= (sclr);                \
}

// Macro function that multiplies two complex numbers.
#define  CMPLX_MULT(to,from_a,from_b)           \
{   (to).Real = (from_a).Real * (from_b).Real - \
                (from_a).Imag * (from_b).Imag;  \
    (to).Imag = (from_a).Real * (from_b).Imag + \
                (from_a).Imag * (from_b).Real;  \
}

// Macro function that implements to *= from for complex numbers.
#define  CMPLX_MULT_ASSIGN(to,from)             \
{   spREAL to_real_ = (to).Real;                \
    (to).Real = to_real_ * (from).Real -        \
                (to).Imag * (from).Imag;        \
    (to).Imag = to_real_ * (from).Imag +        \
                (to).Imag * (from).Real;        \
}

// Macro function that multiplies two complex numbers, the first of which is
// conjugated.
#define  CMPLX_CONJ_MULT(to,from_a,from_b)      \
{   (to).Real = (from_a).Real * (from_b).Real + \
                (from_a).Imag * (from_b).Imag;  \
    (to).Imag = (from_a).Real * (from_b).Imag - \
                (from_a).Imag * (from_b).Real;  \
}

// Macro function that multiplies two complex numbers and then adds them
// to another: to = add + mult_a * mult_b.
#define  CMPLX_MULT_ADD(to,mult_a,mult_b,add)                   \
{   (to).Real = (mult_a).Real * (mult_b).Real -                 \
                (mult_a).Imag * (mult_b).Imag + (add).Real;     \
    (to).Imag = (mult_a).Real * (mult_b).Imag +                 \
                (mult_a).Imag * (mult_b).Real + (add).Imag;     \
}

// Macro function that subtracts the product of two complex numbers from
// another.  to = subt - mult_a * mult_b
#define  CMPLX_MULT_SUBT(to,mult_a,mult_b,subt)                 \
{   (to).Real = (subt).Real - (mult_a).Real * (mult_b).Real +   \
                              (mult_a).Imag * (mult_b).Imag;    \
    (to).Imag = (subt).Imag - (mult_a).Real * (mult_b).Imag -   \
                              (mult_a).Imag * (mult_b).Real;    \
}

// Macro function that multiplies two complex numbers and then adds them
// to another. to = add + mult_a* * mult_b where mult_a* represents mult_a
// conjugate.
#define  CMPLX_CONJ_MULT_ADD(to,mult_a,mult_b,add)              \
{   (to).Real = (mult_a).Real * (mult_b).Real +                 \
                (mult_a).Imag * (mult_b).Imag + (add).Real;     \
    (to).Imag = (mult_a).Real * (mult_b).Imag -                 \
                (mult_a).Imag * (mult_b).Real + (add).Imag;     \
}

// Macro function that multiplies two complex numbers and then adds them
// to another: to += mult_a * mult_b.
#define  CMPLX_MULT_ADD_ASSIGN(to,from_a,from_b)        \
{   (to).Real += (from_a).Real * (from_b).Real -        \
                 (from_a).Imag * (from_b).Imag;         \
    (to).Imag += (from_a).Real * (from_b).Imag +        \
                 (from_a).Imag * (from_b).Real;         \
}

// Macro function that multiplies two complex numbers and then
// subtracts them from another.
#define  CMPLX_MULT_SUBT_ASSIGN(to,from_a,from_b)       \
{   (to).Real -= (from_a).Real * (from_b).Real -        \
                 (from_a).Imag * (from_b).Imag;         \
    (to).Imag -= (from_a).Real * (from_b).Imag +        \
                 (from_a).Imag * (from_b).Real;         \
}

// Macro function that multiplies two complex numbers and then adds
// them to the destination.  to += from_a* * from_b where from_a*
// represents from_a conjugate.
#define  CMPLX_CONJ_MULT_ADD_ASSIGN(to,from_a,from_b)   \
{   (to).Real += (from_a).Real * (from_b).Real +        \
                 (from_a).Imag * (from_b).Imag;         \
    (to).Imag += (from_a).Real * (from_b).Imag -        \
                 (from_a).Imag * (from_b).Real;         \
}

// Macro function that multiplies two complex numbers and then
// subtracts them from the destination.  to -= from_a* * from_b where
// from_a* represents from_a conjugate.
#define  CMPLX_CONJ_MULT_SUBT_ASSIGN(to,from_a,from_b)  \
{   (to).Real -= (from_a).Real * (from_b).Real +        \
                 (from_a).Imag * (from_b).Imag;         \
    (to).Imag -= (from_a).Real * (from_b).Imag -        \
                 (from_a).Imag * (from_b).Real;         \
}

//
// Macro functions that provide complex division.
//

// Complex division:  to = num / den
#define CMPLX_DIV(to,num,den)                                           \
{   spREAL  r_, s_;                                                     \
    if (((den).Real >= (den).Imag AND (den).Real > -(den).Imag) OR      \
        ((den).Real < (den).Imag AND (den).Real <= -(den).Imag))        \
    {   r_ = (den).Imag / (den).Real;                                   \
        s_ = (den).Real + r_*(den).Imag;                                \
        (to).Real = ((num).Real + r_*(num).Imag)/s_;                    \
        (to).Imag = ((num).Imag - r_*(num).Real)/s_;                    \
    }                                                                   \
    else                                                                \
    {   r_ = (den).Real / (den).Imag;                                   \
        s_ = (den).Imag + r_*(den).Real;                                \
        (to).Real = (r_*(num).Real + (num).Imag)/s_;                    \
        (to).Imag = (r_*(num).Imag - (num).Real)/s_;                    \
    }                                                                   \
}

// Complex division and assignment:  num /= den
#define CMPLX_DIV_ASSIGN(num,den)                                       \
{   spREAL  r_, s_, t_;                                                 \
    if (((den).Real >= (den).Imag AND (den).Real > -(den).Imag) OR      \
        ((den).Real < (den).Imag AND (den).Real <= -(den).Imag))        \
    {   r_ = (den).Imag / (den).Real;                                   \
        s_ = (den).Real + r_*(den).Imag;                                \
        t_ = ((num).Real + r_*(num).Imag)/s_;                           \
        (num).Imag = ((num).Imag - r_*(num).Real)/s_;                   \
        (num).Real = t_;                                                \
    }                                                                   \
    else                                                                \
    {   r_ = (den).Real / (den).Imag;                                   \
        s_ = (den).Imag + r_*(den).Real;                                \
        t_ = (r_*(num).Real + (num).Imag)/s_;                           \
        (num).Imag = (r_*(num).Imag - (num).Real)/s_;                   \
        (num).Real = t_;                                                \
    }                                                                   \
}

// Complex reciprocation:  to = 1.0 / den
#define CMPLX_RECIPROCAL(to,den)                                        \
{   spREAL  r_;                                                         \
    if (((den).Real >= (den).Imag AND (den).Real > -(den).Imag) OR      \
        ((den).Real < (den).Imag AND (den).Real <= -(den).Imag))        \
    {   r_ = (den).Imag / (den).Real;                                   \
        (to).Imag = -r_*((to).Real = 1.0/((den).Real + r_*(den).Imag)); \
    }                                                                   \
    else                                                                \
    {   r_ = (den).Real / (den).Imag;                                   \
        (to).Real = -r_*((to).Imag = -1.0/((den).Imag + r_*(den).Real));\
    }                                                                   \
}


//  ASSERT and ABORT
//
// Macro used to assert that if the code is working correctly, then a
// condition must be true.  If not, then execution is terminated and
// an error message is issued stating that there is an internal error
// and giving the file and line number.  These assertions are not
// evaluated unless the SP_OPT_DEBUG flag is true.

#if SP_OPT_DEBUG
#define ASSERT(condition) if (NOT(condition)) ABORT()
#else
#define ASSERT(condition)
#endif

#if SP_OPT_DEBUG
#define  ABORT()                                                        \
{   fflush(stdout);                                                     \
    fprintf(stderr, "sparse: panic in file `%s' at line %d.\n",         \
            __FILE__, __LINE__);                                        \
    fflush(stderr);                                                     \
    abort();                                                            \
}
#else
#define  ABORT()
#endif


//  IMAGINARY VECTORS
//
// The imaginary vectors irhs and isolution are only needed when the
// options SP_OPT_COMPLEX and SP_OPT_SEPARATED_COMPLEX_VECTORS are
// set.  The following macro makes it easy to include or exclude these
// vectors as needed.

#if SP_OPT_COMPLEX AND SP_OPT_SEPARATED_COMPLEX_VECTORS
#define IMAG_VECTORS_P  , spREAL *irhs, spREAL *isolution
#define IMAG_RHS_P      , spREAL *irhs
#define IMAG_VECTORS    , irhs, isolution
#define IMAG_RHS        , irhs
#else
#define IMAG_VECTORS_P
#define IMAG_RHS_P
#define IMAG_VECTORS
#define IMAG_RHS
#endif


