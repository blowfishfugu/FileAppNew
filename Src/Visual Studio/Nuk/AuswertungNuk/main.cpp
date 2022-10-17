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

/* Covered Controls
	space_layout_child=-5, ///< spacing in a space_layout
	space_layout=-4, ///< layoutcontainer for spacer positioning
x (childs invisible)	groupbox = 2,  ///< container for grouping other display and input fields, value is 2
v	static_row=-3,  ///< layout in units, absolute, non-resizing
v	dynamic_row=-2, ///< layout in percentages, resizing
v	form = -1,     ///< container of drawable components, usually a window
w (todo: nuklear caps length!)	edit = 0,      ///< single-line input field in the framework, value is 0
v	label = 1,     ///< single-line labeling field in the framework, value is 1
v	button = 3,    ///< button to start an action, value is 3
v	listbox = 4,   ///< input field with selectable items in list form, value is 4
v	checkbox = 5,  ///< input field for bool values, value is 5
v	combobox = 6,  ///< control that allows to make a selection from given options or alternatively make an input, value is 6
w (todo: nuklear caps length!)	memo = 7,      ///< multiline input field, value is 7
v	statusbar = 8, ///< display field at the bottom of the window, value is 8
	listview = 9   ///< tableview / list as display field for values in table form, value is 9
*/

void createForm(nk::NKForm& mainForm)
{
	mainForm.title = "Auswertung";

	nk::NKRowDynamic* rowLayout = mainForm.AddField<nk::NKRowDynamic>(30.0f, 2, "");
	rowLayout->ratios = { 0.25f, 0.75f };

	nk::TLabel* edit = rowLayout->AddField<nk::TLabel>("lblDirectory", "Path");
	
	nk::TEdit* edit2 = rowLayout->AddField<nk::TEdit>("edtDirectory");
	edit2->setText("../../../../../Embarcadero/VCL/");

	for (int some = 0; some < 3; ++some) {
		rowLayout->AddField<nk::TLabel>("", std::to_string(some));
	}

	nk::NKRowStatic* staticRow = mainForm.AddField<nk::NKRowStatic>(30.0f,300,1,"");
	staticRow->AddField<nk::TLabel>("lblStaticRows", "More Controls");

	nk::TButton* button= staticRow->AddField<nk::TButton>("btnTest");
	button->text = "Count";
	static int clickCount = 0;
	button->onClick = [&mainForm]() {
		clickCount++;
		nk::Component* comp= mainForm.FindComponent("lblStaticRows");
		nk::TLabel* label = dynamic_cast<nk::TLabel*>(comp);
		if (label)
		{
			label->text = std::string("clicked: ")+ std::to_string(clickCount);
		}
	};

	nk::TListbox* lst=staticRow->AddField<nk::TListbox>("lstBox");
	lst->items = { "item1","item2","item3" };

	nk::TCheckbox* checkBox = staticRow->AddField<nk::TCheckbox>("chkOnOff");
	checkBox->text = "yes/no";
	checkBox->onCheckChanged = [](nk::TCheckbox* sender, int checkstate)
	{
		sender->text = checkstate == 1 ? "yes" : "no";
	};

	nk::TCombobox* comboBox = staticRow->AddField<nk::TCombobox>("cmbTypeList", 300.0f,400.0f );
	comboBox->setText("combo1");
	comboBox->setText("combo2");
	comboBox->setText("lastText");

	nk::TMemo* memo=staticRow
					->AddField<nk::NKRowStatic>(500.0f,200,1,"")
					->AddField<nk::TMemo>("txtBox");
	memo->setText("line1\nline2\nline3");

	nk::TGroupBox* groupBox = staticRow->AddField<nk::TGroupBox>("grpForMemo", 100.0f, 400 );
	groupBox->title = "MemoGroup";
	groupBox->AddField<nk::TCheckbox>("btnTest1", "Action 1");
	groupBox->AddField<nk::TCheckbox>("btnTest2", "Action 2");

	nk::NKSpace* panel = mainForm.AddField<nk::NKSpace>(nk_layout_format::NK_STATIC, 400.0f, "pnlGroup");
	for (int i = 0; i < 4; ++i)
	{
		nk::NKSpaceChild* subArea1 = panel->AddField<nk::NKSpaceChild>(nk_rect(10.0f, 10.0f*i, 100.0f, 30.0f), "");
		std::string name = std::string("txtX") + std::to_string(i);
		subArea1->AddField<nk::TLabel>(name, name );
	}
	nk::NKSpaceChild* subArea2 = panel->AddField<nk::NKSpaceChild>(nk_rect(110.0f, 100.0f, 80.0f, 180.0f), "");
	subArea2->AddField<nk::TLabel>("txtX2", "txtX2");

	nk::TStatusBar* statusBar = mainForm.AddField<nk::TStatusBar>(mainForm.Width, mainForm.Height, "testStatus");
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
	createForm(mainForm);
	
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