#include "nwpwin.h"
#include "res.h"

class Button : public Window{
public:
	std::string ClassName() override { return "BUTTON"; }
};
class Edit: public Window{
	std::string ClassName() override { return "EDIT"; }
};
class ListBox : public Window {
	std::string ClassName() override { return "LISTBOX"; }
};

class MainWindow : public Window
{
protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
};

int MainWindow::OnCreate(CREATESTRUCT* pcs)
{
	ListBox l;
	l.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, NULL, IDC_LB, 10, 10, 100, 120);
	Edit e;
	e.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, NULL, IDC_EDIT, 120, 10, 80, 30);
	Button b1,b2;
	b1.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 120, 50, 80, 30);
	b1.Create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 120, 90, 80, 30);
	
	EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			DestroyWindow(*this);
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "This is HELP", "Help", MB_OK);
			break;
		case IDC_ADD:
			char tekst[20];
			if (GetDlgItemText(*this, IDC_EDIT, tekst, sizeof(tekst)) != 0) {
				SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)tekst);
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			}
			SetDlgItemText(*this, IDC_EDIT, "");
			break;
		case IDC_REMOVE:
			LRESULT selected = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			if(selected!=LB_ERR)
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, (LPARAM)selected, 0);
			if(SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, 0, 0)==0)
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
			break;
	}
}

void MainWindow::OnDestroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDM_V2));
	MainWindow wnd; 
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)hMenu);	
	// set icons
	HICON hib = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hib));
	HICON his = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(his));

	Application app; 
	return app.Run();
}
