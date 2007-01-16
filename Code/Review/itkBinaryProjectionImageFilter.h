
#ifndef __itkBinaryProjectionImageFilter_h
#define __itkBinaryProjectionImageFilter_h

#include "itkProjectionImageFilter.h"
#include "itkNumericTraits.h"

namespace itk {
/** \class BinaryProjectionImageFilter
 * \brief Binary projection
 *
 * \author Ga�tan Lehmann. Biologie du D�veloppement et de la Reproduction,
 * INRA de Jouy-en-Josas, France.
 *
 * \sa ProjectionImageFilter
 */


namespace Function {
template <class TInputPixel, class TOutputPixel>
class BinaryAccumulator
{
public:
  BinaryAccumulator( unsigned long size ) {}
  ~BinaryAccumulator(){}

  inline void Init()
    {
    m_IsForeground = false;
    }

  inline TInputPixel operator()( const TInputPixel &input )
    {
    if( input == m_ForegroundValue )
      {
      m_IsForeground = true; 
      }
    }

  inline TOutputPixel GetValue()
    {
    if( m_IsForeground )
      {
      return (TOutputPixel)m_ForegroundValue; 
      }
    else
      {
      return m_BackgroundValue; 
      }
    }

  bool m_IsForeground;

  TInputPixel m_ForegroundValue;

  TOutputPixel m_BackgroundValue;
};
} // end namespace Function


template <class TInputImage, class TOutputImage>
class ITK_EXPORT BinaryProjectionImageFilter :
    public ProjectionImageFilter<TInputImage, TOutputImage, 
      Function::BinaryAccumulator< 
        typename TInputImage::PixelType, 
        typename TOutputImage::PixelType > >
{
public:
  typedef BinaryProjectionImageFilter Self;
  typedef ProjectionImageFilter<TInputImage, TOutputImage, 
    Function::BinaryAccumulator< 
      typename TInputImage::PixelType, 
      typename TOutputImage::PixelType > > Superclass;

  typedef SmartPointer<Self>   Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** Runtime information support. */
  itkTypeMacro(BinaryProjectionImageFilter, ProjectionImageFilter);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Convenient typedefs for simplifying declarations. */
  typedef TInputImage InputImageType;
  typedef TOutputImage OutputImageType;

  /** Image typedef support. */
  typedef typename InputImageType::PixelType InputPixelType;
  typedef typename OutputImageType::PixelType OutputPixelType;

  typedef typename Superclass::AccumulatorType AccumulatorType;

  /** Set the value in the image to consider as "foreground". Defaults to
   * maximum value of PixelType. Subclasses may alias this to
   * DilateValue or ErodeValue.*/
  itkSetMacro(ForegroundValue, InputPixelType);

  /** Get the value in the image considered as "foreground". Defaults to
   * maximum value of PixelType. */
  itkGetConstMacro(ForegroundValue, InputPixelType);

  /** Set the value used as "background".  Any pixel value which is
   * not DilateValue is considered background. BackgroundValue is used
   * for defining boundary conditions. Defaults to
   * NumericTraits<PixelType>::NonpositiveMin(). */
  itkSetMacro(BackgroundValue, OutputPixelType);

  /** Get the value used as "background". Any pixel value which is
   * not DilateValue is considered background. BackgroundValue is used
   * for defining boundary conditions. Defaults to
   * NumericTraits<PixelType>::NonpositiveMin(). */
  itkGetConstMacro(BackgroundValue, OutputPixelType);
  

protected:
  BinaryProjectionImageFilter()
    {
    m_ForegroundValue = NumericTraits<InputPixelType>::max();
    m_BackgroundValue = NumericTraits<OutputPixelType>::NonpositiveMin();
    }
  virtual ~BinaryProjectionImageFilter() {}

  virtual AccumulatorType NewAccumulator( unsigned long size )
    {
    AccumulatorType accumulator( size );
    accumulator.m_ForegroundValue = m_ForegroundValue;
    accumulator.m_BackgroundValue = m_BackgroundValue;
    return accumulator;
    }

  /** Pixel value to dilate */
  InputPixelType m_ForegroundValue;

  /** Pixel value for background */
  OutputPixelType m_BackgroundValue;
  
private:
  BinaryProjectionImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented



}; // end BinaryProjectionImageFilter

} //end namespace itk
#endif
