/* dgeqr2.f -- translated by f2c (version of 4 June 1993  1:43:59).
   You must link the resulting object file with the libraries:
        -lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;

/*<       SUBROUTINE DGEQR2( M, N, A, LDA, TAU, WORK, INFO ) >*/
/* Subroutine */ int dgeqr2_(integer *m, integer *n, doublereal *a, integer *
        lda, doublereal *tau, doublereal *work, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i, k;
    extern /* Subroutine */ int dlarf_(char *, integer *, integer *,
            doublereal *, integer *, doublereal *, doublereal *, integer *,
            doublereal *, ftnlen), dlarfg_(integer *, doublereal *,
            doublereal *, integer *, doublereal *), xerbla_(char *, integer *,
             ftnlen);
    static doublereal aii;


/*  -- LAPACK routine (version 2.0) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd., */
/*     Courant Institute, Argonne National Lab, and Rice University */
/*     February 29, 1992 */

/*     .. Scalar Arguments .. */
/*<       INTEGER            INFO, LDA, M, N >*/
/*     .. */
/*     .. Array Arguments .. */
/*<       DOUBLE PRECISION   A( LDA, * ), TAU( * ), WORK( * ) >*/
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGEQR2 computes a QR factorization of a real m by n matrix A: */
/*  A = Q * R. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A.  M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A.  N >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the m by n matrix A. */
/*          On exit, the elements on and above the diagonal of the array
*/
/*          contain the min(m,n) by n upper trapezoidal matrix R (R is */
/*          upper triangular if m >= n); the elements below the diagonal,
*/
/*          with the array TAU, represent the orthogonal matrix Q as a */
/*          product of elementary reflectors (see Further Details). */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,M). */

/*  TAU     (output) DOUBLE PRECISION array, dimension (min(M,N)) */
/*          The scalar factors of the elementary reflectors (see Further
*/
/*          Details). */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (N) */

/*  INFO    (output) INTEGER */
/*          = 0: successful exit */
/*          < 0: if INFO = -i, the i-th argument had an illegal value */

/*  Further Details */
/*  =============== */

/*  The matrix Q is represented as a product of elementary reflectors */

/*     Q = H(1) H(2) . . . H(k), where k = min(m,n). */

/*  Each H(i) has the form */

/*     H(i) = I - tau * v * v' */

/*  where tau is a real scalar, and v is a real vector with */
/*  v(1:i-1) = 0 and v(i) = 1; v(i+1:m) is stored on exit in A(i+1:m,i),
*/
/*  and tau in TAU(i). */

/*  =====================================================================
*/

/*     .. Parameters .. */
/*<       DOUBLE PRECISION   ONE >*/
/*<       PARAMETER          ( ONE = 1.0D+0 ) >*/
/*     .. */
/*     .. Local Scalars .. */
/*<       INTEGER            I, K >*/
/*<       DOUBLE PRECISION   AII >*/
/*     .. */
/*     .. External Subroutines .. */
/*<       EXTERNAL           DLARF, DLARFG, XERBLA >*/
/*     .. */
/*     .. Intrinsic Functions .. */
/*<       INTRINSIC          MAX, MIN >*/
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

/*<       INFO = 0 >*/
    /* Parameter adjustments */
    --work;
    --tau;
    a_dim1 = *lda;
    a_offset = a_dim1 + 1;
    a -= a_offset;

    /* Function Body */
    *info = 0;
/*<       IF( M.LT.0 ) THEN >*/
    if (*m < 0) {
/*<          INFO = -1 >*/
        *info = -1;
/*<       ELSE IF( N.LT.0 ) THEN >*/
    } else if (*n < 0) {
/*<          INFO = -2 >*/
        *info = -2;
/*<       ELSE IF( LDA.LT.MAX( 1, M ) ) THEN >*/
    } else if (*lda < max(1,*m)) {
/*<          INFO = -4 >*/
        *info = -4;
/*<       END IF >*/
    }
/*<       IF( INFO.NE.0 ) THEN >*/
    if (*info != 0) {
/*<          CALL XERBLA( 'DGEQR2', -INFO ) >*/
        i__1 = -(*info);
        xerbla_("DGEQR2", &i__1, 6L);
/*<          RETURN >*/
        return 0;
/*<       END IF >*/
    }

/*<       K = MIN( M, N ) >*/
    k = min(*m,*n);

/*<       DO 10 I = 1, K >*/
    i__1 = k;
    for (i = 1; i <= i__1; ++i) {

/*        Generate elementary reflector H(i) to annihilate A(i+1:m,i)
*/

/*<    >*/
        i__2 = *m - i + 1;
/* Computing MIN */
        i__3 = i + 1;
        dlarfg_(&i__2, &a[i + i * a_dim1], &a[min(i__3,*m) + i * a_dim1], &
                c__1, &tau[i]);
/*<          IF( I.LT.N ) THEN >*/
        if (i < *n) {

/*           Apply H(i) to A(i:m,i+1:n) from the left */

/*<             AII = A( I, I ) >*/
            aii = a[i + i * a_dim1];
/*<             A( I, I ) = ONE >*/
            a[i + i * a_dim1] = 1.;
/*<    >*/
            i__2 = *m - i + 1;
            i__3 = *n - i;
            dlarf_("Left", &i__2, &i__3, &a[i + i * a_dim1], &c__1, &tau[i], &
                    a[i + (i + 1) * a_dim1], lda, &work[1], 4L);
/*<             A( I, I ) = AII >*/
            a[i + i * a_dim1] = aii;
/*<          END IF >*/
        }
/*<    10 CONTINUE >*/
/* L10: */
    }
/*<       RETURN >*/
    return 0;

/*     End of DGEQR2 */

/*<       END >*/
} /* dgeqr2_ */

