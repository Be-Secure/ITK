#ifndef vnl_dll_h_
#define vnl_dll_h_

#define VNL_DLL_DATA

#if defined(WIN32) && !defined(BUILDING_VNL_DLL)
// This is vxl/vnl/dll.h

// if win32 and not buiding the DLL then you need a dllimport 
// Only if you are building a DLL linked application.
# ifdef BUILD_DLL
#  undef VNL_DLL_DATA
#  define VNL_DLL_DATA _declspec(dllimport)
# endif // BUILD_DLL
#endif // WIN32 and !Building_*_dll

#endif // vnl_dll_h_
