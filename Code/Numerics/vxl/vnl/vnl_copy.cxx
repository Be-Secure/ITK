// This is vxl/vnl/vnl_copy.cxx

/*
  fsm@robots.ox.ac.uk
*/
#ifdef __GNUC__
#pragma implementation
#endif
#include "vnl_copy.h"
#include <vcl_cassert.h>
#include <vcl_complex.h>
#include <vnl/vnl_vector.h>
#include <vnl/vnl_matrix.h>
#include <vnl/vnl_diag_matrix.h>

//-------------------------------------------------------------------

template <class S, class T>
void vnl_copy(S const *src, T *dst, unsigned n)
{
  for (int i=0; i<n; ++i)
    dst[i] = src[i];
}

template <class S, class T>
void vnl_copy(S const &src, T &dst)
{
  assert(src.size() == dst.size());
  vnl_copy(src.begin(), dst.begin(), src.size());
}

//------------------------------------------------------------------------

// C arrays
#define VNL_COPY_INSTANTIATE0(S, T) \
template void vnl_copy(S const *, T *, unsigned );

VNL_COPY_INSTANTIATE0(float, double);
VNL_COPY_INSTANTIATE0(double, float);
VNL_COPY_INSTANTIATE0(double, long double);
VNL_COPY_INSTANTIATE0(long double, double);

#define macro(S, D) \
VCL_DEFINE_SPECIALIZATION \
void vnl_copy(vcl_complex<S> const *src, vcl_complex<D> *dst, unsigned n) \
{ \
  for (int i=0; i<n; ++i) \
    dst[i] = vcl_complex<D>(src[i].real(), src[i].imag()); \
}
macro(float, double);
macro(double, float);
macro(double, long double);
macro(long double, double);
#undef macro

// vnl_* containers
#define VNL_COPY_INSTANTIATE(S, T) \
template void vnl_copy(vnl_vector<S > const &, vnl_vector<T > &); \
template void vnl_copy(vnl_matrix<S > const &, vnl_matrix<T > &); \
template void vnl_copy(vnl_diag_matrix<S > const &, vnl_diag_matrix<T > &);

#define VNL_COPY_INSTANTIATE_twoway(S, T) \
VNL_COPY_INSTANTIATE(S, T); \
VNL_COPY_INSTANTIATE(T, S)

VNL_COPY_INSTANTIATE_twoway(float, double);
VNL_COPY_INSTANTIATE_twoway(double, long double);
VNL_COPY_INSTANTIATE_twoway(vcl_complex<float>, vcl_complex<double>);
VNL_COPY_INSTANTIATE_twoway(vcl_complex<double>, vcl_complex<long double>);
