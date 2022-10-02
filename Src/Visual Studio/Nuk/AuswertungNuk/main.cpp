#if defined BUILD_WITH_NUKLEAR
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>


#include <d3d11.h>

#include <MyStdTypes.h>
#include <MyFramework_Selection.h>

#include <nuk_declare.h>

#include "nuk_controls.h"
//#include <MyForm.h> //->MyFramework_Selection
#include "NukForm.h" //->TProcess, ->nuklear
#include "nuk_d3dapp.h"

#include "MyStream.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

void createForm(nk::NKForm& mainForm, const D3D11_VIEWPORT& viewport)
{
	mainForm.title = "Auswertung";

	nk::NKRowDynamic* rowLayout = mainForm.AddField<nk::NKRowDynamic>(30.0f, 2, "");
	rowLayout->ratios = { 0.25f, 0.75f };

	nk::TLabel* edit = rowLayout->AddField<nk::TLabel>("lblDirectory", "Path");
	
	nk::TEdit* edit2 = rowLayout->AddField<nk::TEdit>("edtDirectory");
	edit2->setText("../../../../../Embarcadero/VCL/");

	for (int some = 0; some < 13; ++some) {
		rowLayout->AddField<nk::TLabel>("", std::to_string(some));
	}

	nk::TStatusBar* statusBar = mainForm.AddField<nk::TStatusBar>(viewport.Width, viewport.Height, "testStatus");
	statusBar->text = "statustext";
}

#ifdef NDEBUG
int WINAPI _tWinMain( _In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPTSTR, _In_ int)
#else
int main(int argc, char** argv)
#endif
{
	Application app;

	TProcess proc;
	app.Init(WINDOW_WIDTH, WINDOW_HEIGHT);

	const D3D11_VIEWPORT& viewport = app.GetViewport();
	
	nk::NKForm mainForm(viewport.Width, viewport.Height, "Demo", 0);
	createForm(mainForm, viewport);
	
	//Form-Created
	try
	{
		//proc.Init({ &mainForm,false });

		app.Run(mainForm);
	}
	catch (std::runtime_error re)
	{
		std::cerr << re.what() << "\n";
	}
	
	app.Release();
	return 0;
}

#endif