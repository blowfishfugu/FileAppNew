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

#define NK_INCLUDE_FIXED_TYPES
//#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#ifdef NK_IMPLEMENTATION
#undef NK_IMPLEMENTATION
#endif
#include <nuklear.h>

#include "nuk_controls.h"
//#include <MyForm.h> //->MyFramework_Selection
#include "NukForm.h" //->TProcess, ->nuklear
#include "nuk_d3dapp.h"

#include "MyStream.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

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
	mainForm.title = "Auswertung";

	auto dualRow = [](struct nk_context* ctx)
	{
		nk_layout_row_dynamic(ctx, 25, 20);
	};

	nk::TEdit* edit = mainForm.AddField<nk::TEdit>("path");
	edit->applyLayout = dualRow;
	edit->text = "hello"; 
	edit->cursorpos = edit->text.length();
	
	nk::TEdit* edit2 = mainForm.AddField<nk::TEdit>("second");
	edit2->text = "hello2";
	//edit2->applyLayout = singleRow;
	edit2->cursorpos = edit2->text.length();
#ifndef NDEBUG
	for (int tst = 0; tst < 1000; ++tst)
#else
	for (int tst = 0; tst < 200000; ++tst)
#endif
	{
		nk::TLabel* lbl=mainForm.AddField<nk::TLabel>("",std::to_string(tst) );
		mainForm.AddField<nk::TEdit>("");
	}

	nk::TStatusBar* statusBar = mainForm.AddField<nk::TStatusBar>(viewport.Width, viewport.Height, "testStatus");
	statusBar->text = "statustext";
	
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