#if 0
// the netlib qrsl routines seems to have a bug
// for single precision complex scalars, so let's
// try to use the double precision version instead.
//
// hmm that still doesn't work.
#include <vcl_cassert.h>
#include <vcl_iostream.h>
#include <vcl_complex.h>
#include <vnl/vnl_vector.h>
#include <vnl/vnl_matrix.h>
#include <vnl/algo/vnl_qr.txx>
#include <vnl/vnl_copy.h>

VCL_DEFINE_SPECIALIZATION
vnl_vector<vcl_complex<float>> vnl_qr<vcl_complex<float>>::solve(const vnl_vector<vcl_complex<float>>& b) const
{
  assert(false);
  int n = qrdc_out_.columns();
  int p = qrdc_out_.rows();

  vnl_matrix<vcl_complex<double>> DOUBLE_qrdc_out_(qrdc_out_.rows(), qrdc_out_.cols());
  vnl_copy(qrdc_out_, DOUBLE_qrdc_out_);

  vnl_vector<vcl_complex<double>> DOUBLE_qraux_(qraux_.size());
  vnl_copy(qraux_, DOUBLE_qraux_);

  vnl_vector<vcl_complex<double>> DOUBLE_b(b.size());
  vnl_copy(b, DOUBLE_b);

  const vcl_complex<double> * DOUBLE_b_data = DOUBLE_b.data_block();
  vnl_vector<vcl_complex<double>> DOUBLE_QtB(n);
  vnl_vector<vcl_complex<double>> DOUBLE_x(p);

  // see comment above
  int JOB = 100;

  int info = 0;
  vnl_linpack_qrsl(DOUBLE_qrdc_out_.data_block(),
                   n, n, p,
                   DOUBLE_qraux_.data_block(),
                   DOUBLE_b_data, 0, DOUBLE_QtB.data_block(),
                   DOUBLE_x.data_block(),
                   0/*residual*/,
                   0/*Ax*/,
                   JOB,
                   &info);

  if (info > 0)
    cerr << "vnl_qr<T>::solve() : A is rank-deficient by " << info << endl;

  vnl_vector<vcl_complex<float>> x(p);
  vnl_copy(DOUBLE_x, x);

  return x;
}

//: Return residual vector d of M x = b -> d = Q'b
VCL_DEFINE_SPECIALIZATION
vnl_vector<vcl_complex<float>> vnl_qr<vcl_complex<float>>::QtB(const vnl_vector<vcl_complex<float>>& b) const
{
  assert(false);
  int n = qrdc_out_.columns();
  int p = qrdc_out_.rows();

  vnl_matrix<vcl_complex<double>> DOUBLE_qrdc_out_(qrdc_out_.rows(), qrdc_out_.cols());
  vnl_copy(qrdc_out_, DOUBLE_qrdc_out_);

  vnl_vector<vcl_complex<double>> DOUBLE_qraux_(qraux_.size());
  vnl_copy(qraux_, DOUBLE_qraux_);

  vnl_vector<vcl_complex<double>> DOUBLE_b(b.size());
  vnl_copy(b, DOUBLE_b);

  const vcl_complex<double> * DOUBLE_b_data = DOUBLE_b.data_block();
  vnl_vector<vcl_complex<double>> DOUBLE_QtB(n);

  // see comment above
  int JOB = 1000;

  int info = 0;
  vnl_linpack_qrsl(DOUBLE_qrdc_out_.data_block(),
                   n, n, p,
                   DOUBLE_qraux_.data_block(),
                   DOUBLE_b_data,
                   0,                       // A: Qb
                   DOUBLE_QtB.data_block(), // B: Q'b
                   0,                       // C: x
                   0,                       // D: residual
                   0,                       // E: Ax
                   JOB,
                   &info);

  if (info > 0) {
    cerr << "vnl_qr<T>::QtB() -- A is rank-def by " << info << endl;
  }

  vnl_vector<vcl_complex<float>> QtB(n);
  vnl_copy(DOUBLE_QtB, QtB);

  return QtB;
}
#endif

#include <vcl_complex.h>
#include <vnl/algo/vnl_qr.txx>

VNL_QR_INSTANTIATE(vcl_complex<float>);
