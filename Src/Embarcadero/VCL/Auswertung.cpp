//---------------------------------------------------------------------------
<<<<<<< HEAD

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("MainForm.cpp", frmMain);
//---------------------------------------------------------------------------
=======
#if defined BUILD_WITH_VCL || BUILD_WITH_FMX
#include <windows.h>
#include <tchar.h>


#if defined BUILD_WITH_VCL
	#include <vcl.h>
#elif defined BUILD_WITH_FMX
	#include <fmx.h>
#endif

#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("MainForm.cpp", frmMain);
//---------------------------------------------------------------------------


>>>>>>> old-project/main
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    try
    {
         Application->Initialize();
         Application->MainFormOnTaskBar = true;
         Application->CreateForm(__classid(TfrmMain), &frmMain);
<<<<<<< HEAD
       Application->Run();
=======
         Application->Run();
>>>>>>> old-project/main
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    catch (...)
    {
         try
         {
             throw Exception("");
         }
         catch (Exception &exception)
         {
             Application->ShowException(&exception);
         }
    }
    return 0;
}
//---------------------------------------------------------------------------
<<<<<<< HEAD
=======
#else

#endif
>>>>>>> old-project/main
