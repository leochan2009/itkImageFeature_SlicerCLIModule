#include "itkImageFileWriter.h"

#include "itkHessianRecursiveGaussianImageFilter.h"
#include "itkHessian3DToVesselnessMeasureImageFilter.h"
#include "itkPluginUtilities.h"
#include "HessianVesselnessFilterCLP.h"

// Use an anonymous namespace to keep class types and function names
// from colliding when module is used as shared object module.  Every
// thing should be in an anonymous namespace except for the module
// entry point, e.g. main()
//
namespace
{
  
  template <class T>
  int DoIt( int argc, char * argv[], T )
  {
    PARSE_ARGS;
    
    typedef    T InputPixelType;
    typedef    T OutputPixelType;
    
    typedef itk::Image<InputPixelType,  3> InputImageType;
    typedef itk::Image<itk::SymmetricSecondRankTensor< double, 3>,  3> IntermediateImageType;
    typedef itk::Image<OutputPixelType, 3> OutputImageType;
    
    typedef itk::ImageFileReader<InputImageType>  ReaderType;
    typedef itk::ImageFileWriter<OutputImageType> WriterType;
    typedef itk::HessianRecursiveGaussianImageFilter<InputImageType, IntermediateImageType>  Filter1Type;
    typedef itk::Hessian3DToVesselnessMeasureImageFilter<OutputPixelType>  Filter2Type;
    
    typename ReaderType::Pointer reader = ReaderType::New();
    itk::PluginFilterWatcher watchReader(reader, "Read Volume", CLPProcessInformation);
    
    reader->SetFileName( inputVolume.c_str() );
    
    typename Filter1Type::Pointer filter1 = Filter1Type::New();
    typename Filter2Type::Pointer filter2 = Filter2Type::New();
    filter1->SetInput( reader->GetOutput() );
    filter1->SetSigma( sigma );
    itk::PluginFilterWatcher watchFilter1(filter1, "HessianRecursiveGaussian", CLPProcessInformation);
    filter2->SetInput(filter1->GetOutput() );
    filter2->SetAlpha1(alpha1);
    filter2->SetAlpha2(alpha2);
    itk::PluginFilterWatcher watchFilter2(filter1, "Hessian3DToVesselnessMeasure", CLPProcessInformation);
    
    typename WriterType::Pointer writer = WriterType::New();
    itk::PluginFilterWatcher watchWriter(writer,  "Write Volume",  CLPProcessInformation);
    writer->SetFileName( outputVolume.c_str() );
    writer->SetInput( filter2->GetOutput() );
    writer->SetUseCompression(1);
    writer->Update();
    
    return EXIT_SUCCESS;
  }
  
} // end of anonymous namespace

int main( int argc, char * argv[] )
{
  PARSE_ARGS;
  
  itk::ImageIOBase::IOPixelType     pixelType;
  itk::ImageIOBase::IOComponentType componentType;
  
  try
  {
    itk::GetImageType(inputVolume, pixelType, componentType);
    
    // This filter handles all types on input, but only produces
    // signed types
    switch( componentType )
    {
      case itk::ImageIOBase::UCHAR:
        return DoIt( argc, argv, static_cast<unsigned char>(0) );
        break;
      case itk::ImageIOBase::CHAR:
        return DoIt( argc, argv, static_cast<char>(0) );
        break;
      case itk::ImageIOBase::USHORT:
        return DoIt( argc, argv, static_cast<unsigned short>(0) );
        break;
      case itk::ImageIOBase::SHORT:
        return DoIt( argc, argv, static_cast<short>(0) );
        break;
      case itk::ImageIOBase::UINT:
        return DoIt( argc, argv, static_cast<unsigned int>(0) );
        break;
      case itk::ImageIOBase::INT:
        return DoIt( argc, argv, static_cast<int>(0) );
        break;
      case itk::ImageIOBase::ULONG:
        return DoIt( argc, argv, static_cast<unsigned long>(0) );
        break;
      case itk::ImageIOBase::LONG:
        return DoIt( argc, argv, static_cast<long>(0) );
        break;
      case itk::ImageIOBase::FLOAT:
        return DoIt( argc, argv, static_cast<float>(0) );
        break;
      case itk::ImageIOBase::DOUBLE:
        return DoIt( argc, argv, static_cast<double>(0) );
        break;
      case itk::ImageIOBase::UNKNOWNCOMPONENTTYPE:
      default:
        std::cout << "unknown component type" << std::endl;
        break;
    }
  }
  
  catch( itk::ExceptionObject & excep )
  {
    std::cerr << argv[0] << ": exception caught !" << std::endl;
    std::cerr << excep << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
