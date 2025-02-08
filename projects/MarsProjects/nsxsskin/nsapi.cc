#include "stdafx.h"

#if _DEBUG
extern "C" {
	__declspec(dllexport) void OpenUI() {
		Global::Get()->SetInstallerProcessType(ProcessType::Uninstall);
		Global::Get()->SetSkinDir(LR"(C:\Users\k34ub\source\skstu\nsxsskin\tools\MakeInstaller\source\skin\skin\)");
		ui::UIFrame::Get()->Start();
	}
	__declspec(dllexport) void CloseUI() {
		ui::UIFrame::Destroy();
	}
}
#endif

#define NSISAPI extern "C" __declspec(dllexport) void __cdecl 

static UINT_PTR PluginCallback(enum NSPIM msg)
{
	return 0;
}

// 初始化安装程序自定义页面
NSISAPI InitInstallPage(HWND hwndParent, int string_size, TCHAR* variables, stack_t** stacktop, extra_parameters* extra) {
	HANDLE hMutex = CreateMutexW(NULL, FALSE, L"XSInstallerProjectsProcessMutex");
	if (ERROR_ALREADY_EXISTS == GetLastError()) {
		return;
	}
	NSIS_INIT_EXTRA_PARAMETERS(extra);
	//MessageBoxW(NULL, __FUNCTIONW__, NULL, MB_TOPMOST);
	EXDLL_INIT();
	g_hwndParent = hwndParent;
	//"$PLUGINSDIR\" "$PLUGINSDIR\${INSTALL_LICENCE_FILENAME}" "$INSTALL_DEFALT_SETUPPATH\"
	extra->RegisterPluginCallback(g_hInstance, PluginCallback);
	wchar_t resdir[MAX_PATH] = { 0 };
	wchar_t licencefile[MAX_PATH] = { 0 };
	wchar_t defaultInstallDir[MAX_PATH] = { 0 };
	wchar_t product_version[MAX_PATH] = { 0 };
	PopStringW(resdir);
	PopStringW(licencefile);
	PopStringW(defaultInstallDir);
	PopStringW(product_version);
	std::wstring wstrResDir(resdir);
	Global::Get()->SetInstallerProcessType(ProcessType::Install);
	Global::Get()->SetProductVersion(product_version);
	Global::Get()->SetProductInstallDir(shared::Win::PathFixedW(defaultInstallDir));
	Global::Get()->SetProductLicenceFilename(shared::Win::PathFixedW(wstrResDir + L"//" + licencefile));
	Global::Get()->SetProductServiceProtocol(shared::Win::PathFixedW(licencefile));
	Global::Get()->SetSkinDir(shared::Win::PathFixedW(wstrResDir + L"/skin.zip"));
	//MessageBoxW(hwndParent, wstrResDir.c_str(), NULL, MB_TOPMOST);
	//frame->Start();
	//MessageBoxW(hwndParent, wstrResDir.c_str(), NULL, MB_TOPMOST);
	//ui::WindowThread windowThread(wstrResDir);
	//windowThread.RunOnCurrentThreadWithLoop(nbase::MessageLoop::kUIMessageLoop);

	//skin.zip
	//MessageBoxW(NULL, resdir, NULL, MB_TOPMOST);
	//MessageBoxW(NULL, licencefile, NULL, MB_TOPMOST);
	// note if you want parameters from the stack, pop them off in order.
	// i.e. if you are called via exdll::myFunction file.dat read.txt
	// calling popstring() the first time would give you file.dat,
	// and the second time would give you read.txt. 
	// you should empty the stack of your parameters, and ONLY your
	// parameters.

	// do your stuff here
	//{
	//	LPTSTR msgbuf = (LPTSTR)GlobalAlloc(GPTR, (3 + string_size + 1) * sizeof(*msgbuf));
	//	if (msgbuf)
	//	{
	//		wsprintf(msgbuf, TEXT("$0=%s"), getuservariable(INST_0));
	//		MessageBox(g_hwndParent, msgbuf, TEXT("Message from example plugin"), MB_OK);
	//		GlobalFree(msgbuf);
	//	}
	//}
#if 0
	NSMETHOD_INIT(hwndParent);
	CoInitialize(NULL);
	TCHAR resdir[MAX_PATH] = { 0 };
	TCHAR licencefile[MAX_PATH] = { 0 };
	extra->RegisterPluginCallback(g_hInstance, PluginCallback);
	PopString(resdir);
	PopString(licencefile);
	CPaintManagerUI::SetInstance(g_hInstance);
	CPaintManagerUI::SetResourcePath(resdir);
	CPaintManagerUI::SetResourceZip(_T("skin.zip"));
	g_dialog = new CMainDialog();
	g_dialog->SetMode(1);
	g_dialog->Create(NULL, _T("XXXX安装程序"), WS_POPUP, 0, 0, 550, 410);
	g_dialog->CenterWindow();
	g_dialog->SetLicenceFile(licencefile);

	g_dialog->ShowWindow(false);
	PushInt((int)g_dialog->GetHWND());
#endif
}

NSISAPI InitUnInstallPage(HWND hwndParent, int string_size, TCHAR* variables, stack_t** stacktop, extra_parameters* extra)
{
	NSIS_INIT_EXTRA_PARAMETERS(extra);
	//MessageBoxW(NULL, __FUNCTIONW__, NULL, MB_TOPMOST);
	EXDLL_INIT();

	SetProcessDPIAware();

	g_hwndParent = hwndParent;
	//"$PLUGINSDIR\" "$PLUGINSDIR\${INSTALL_LICENCE_FILENAME}" "$INSTALL_DEFALT_SETUPPATH\"
	extra->RegisterPluginCallback(g_hInstance, PluginCallback);
	wchar_t resdir[MAX_PATH] = { 0 };
	wchar_t instDir[MAX_PATH] = { 0 };
	wchar_t rmdirs[MAX_PATH * 10] = { 0 };
	PopStringW(resdir);
	PopStringW(instDir);
	PopStringW(rmdirs);
	std::wstring wstrResDir(resdir);
	Global::Get()->SetInstallerProcessType(ProcessType::Uninstall);
	Global::Get()->SetProductInstallDir(instDir);
	Global::Get()->SetRMDirs(rmdirs);
	const std::wstring skinPath = shared::Win::PathFixedW(wstrResDir + L"/skin.zip");
	Global::Get()->SetSkinDir(skinPath);
#if 0
	NSMETHOD_INIT(hwndParent);
	CoInitialize(NULL);
	TCHAR resdir[MAX_PATH] = { 0 };
	extra->RegisterPluginCallback(g_hInstance, PluginCallback);
	PopString(resdir);
	CPaintManagerUI::SetInstance(g_hInstance);
	CPaintManagerUI::SetResourcePath(resdir);
	CPaintManagerUI::SetResourceZip(_T("skin.zip"));
	g_dialog = new CMainDialog();
	g_dialog->SetMode(2);
	g_dialog->Create(NULL, _T("XXXX卸载程序"), WS_POPUP, 0, 0, 550, 410);
	PushInt((int)g_dialog->GetHWND());
#endif
}

NSISAPI SetWindowTile(HWND hwndParent, int string_size, TCHAR* variables, stack_t** stacktop, extra_parameters* extra)
{
	//MessageBoxW(NULL, __FUNCTIONW__, NULL, MB_TOPMOST);
#if 0
	NSMETHOD_INIT(hwndParent);
	TCHAR title[1024] = { 0 };
	HWND hwnd = (HWND)PopInt();
	PopString(title);
	if (IsWindow(hwnd))
	{
		SetWindowText(hwnd, title);
		// 设置窗口图标
		CDuiString iconfile = CPaintManagerUI::GetResourcePath();

		if (iconfile.Right(1) == _T("\\"))
		{
			iconfile.Append(_T("logo.ico"));
		}
		else
		{
			iconfile.Append(_T("\\logo.ico"));
		}
		if (PathFileExists(iconfile))
		{
			HICON hIcon = (HICON)::LoadImage(NULL, iconfile, IMAGE_ICON,
				(::GetSystemMetrics(SM_CXICON) + 15) & ~15, (::GetSystemMetrics(SM_CYICON) + 15) & ~15,	// 防止高DPI下图标模糊
				LR_LOADFROMFILE);
			DWORD dwError = GetLastError();
			TCHAR buff[1024] = { 0 };
			_itow((int)dwError, buff, 16);
			ASSERT(hIcon);
			::SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

			hIcon = (HICON)::LoadImage(NULL, iconfile, IMAGE_ICON,
				(::GetSystemMetrics(SM_CXICON) + 15) & ~15, (::GetSystemMetrics(SM_CYICON) + 15) & ~15,	// 防止高DPI下图标模糊
				LR_LOADFROMFILE);
			ASSERT(hIcon);
			::SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
			hIcon = (HICON)::LoadImage(NULL, iconfile, IMAGE_ICON,
				(::GetSystemMetrics(SM_CXICON) + 15) & ~15, (::GetSystemMetrics(SM_CYICON) + 15) & ~15,	// 防止高DPI下图标模糊
				LR_LOADFROMFILE);
			ASSERT(hIcon);
			::SendMessage(hwnd, STM_SETICON, IMAGE_ICON, (LPARAM)hIcon);
		}
	}
#endif
}

NSISAPI ShowPage(HWND hwndParent, int string_size, TCHAR* variables, stack_t** stacktop, extra_parameters* extra)
{
	NSIS_INIT_EXTRA_PARAMETERS(extra);
	//MessageBoxW(NULL, __FUNCTIONW__, NULL, MB_TOPMOST);
#if 0
	NSMETHOD_INIT(hwndParent);
	if (g_dialog != NULL) {
		g_dialog->CenterWindow();
		g_dialog->ShowWindow(true);
		if (!g_dialog->GetInitState())
		{
			g_dialog->SetInitState(true);
			CPaintManagerUI::MessageLoop();
		}
	}
#endif
	ui::UIFrame::Get()->Start();
	gpSignalSystemExit->wait_for_event(std::chrono::milliseconds(0));
}

NSISAPI ShowTabPageItem(HWND hwndParent, int string_size, TCHAR* variables, stack_t** stacktop, extra_parameters* extra)
{
	//MessageBoxW(NULL, __FUNCTIONW__, NULL, MB_TOPMOST);
#if 0
	NSMETHOD_INIT(hwndParent);
	HWND hwnd = (HWND)PopInt();
	TCHAR name[512] = { 0 };
	PopString(name);
	int index = PopInt();
	if (g_dialog != NULL)
	{
		g_dialog->ShowTabPageItem(name, index);
	}
#endif
}

NSISAPI BindCallBack(HWND hwndParent, int string_size, TCHAR* variables, stack_t** stacktop, extra_parameters* extra)
{
	NSIS_INIT_EXTRA_PARAMETERS(extra);
	TCHAR control[512] = { 0 };
	INT_PTR cbptr = 0;
	PopStringW(control);
	cbptr = popintptr();

	std::wstring nsisFunname(control);
	if (!nsisFunname.empty()) {
		ui::UIFrame::Get()->nsiscbs_.push(nsisFunname, cbptr);
	}
}

NSISAPI InitMessageBox(HWND hwndParent, int string_size, TCHAR* variables, stack_t** stacktop, extra_parameters* extra)
{
	MessageBoxW(NULL, __FUNCTIONW__, NULL, MB_TOPMOST);
#if 0
	NSMETHOD_INIT(hwndParent);
	if (g_dialog != NULL)
	{
		TCHAR skinfile[MAX_PATH] = { 0 };
		TCHAR btnOK[512] = { 0 };
		TCHAR btnCancel[512] = { 0 };
		PopString(skinfile);
		PopString(btnOK);
		PopString(btnCancel);
		HWND hwnd = g_dialog->InitMessageBox(skinfile, btnOK, btnCancel);
		PushInt((int)hwnd);
	}
#endif
}

NSISAPI ShowMessageBox(HWND hwndParent, int string_size, TCHAR* variables, stack_t** stacktop, extra_parameters* extra)
{
	NSIS_INIT_EXTRA_PARAMETERS(extra);
	wchar_t text[1024] = { 0 };
	PopStringW(text);
	MessageBoxW(hwndParent, text, NULL, MB_TOPMOST);
	//std::wstring strText(text);
	//if (!strText.empty()) {
	//	//ui::UIFrame::Get()->notify_message_.push(strText);
	//	MessageBoxW(hwndParent, strText.c_str(), NULL, MB_TOPMOST);
	//}
#if 0
	NSMETHOD_INIT(hwndParent);
	if (g_dialog != NULL)
	{
		UINT ret = g_dialog->ShowMessageBox();
		PushInt((int)ret);
	}
#endif
}
NSISAPI ExtractFinished(HWND hwndParent, int string_size, TCHAR* variables, stack_t** stacktop, extra_parameters* extra) {
	NSIS_INIT_EXTRA_PARAMETERS(extra);
	wchar_t r8[260] = { 0 };
	wchar_t r9[260] = { 0 };
	PopStringW(r8);
	PopStringW(r9);
	ui::UIFrame::Get()->ProcessStatusSet(ui::ProcessStatus::Installed);
}
NSISAPI SetProgressValue(HWND hwndParent, int string_size, TCHAR* variables, stack_t** stacktop, extra_parameters* extra) {
	NSIS_INIT_EXTRA_PARAMETERS(extra);
	//MessageBoxW(NULL, __FUNCTIONW__, NULL, MB_TOPMOST);
	wchar_t r8[260] = { 0 };
	wchar_t r9[260] = { 0 };

	PopStringW(r8);
	PopStringW(r9);
	std::uint64_t current = std::wcstoull(r8, nullptr, 10);
	std::uint64_t total = std::wcstoull(r9, nullptr, 10);
	if (current > 0 && total > 0 && current < total) {
		ui::UIFrame::Get()->nsis_install_progress_.push(std::make_tuple(current, total));
	}
}
NSISAPI SetControlAttribute(HWND hwndParent, int string_size, TCHAR* variables, stack_t** stacktop, extra_parameters* extra)
{
	NSIS_INIT_EXTRA_PARAMETERS(extra);
	wchar_t fun_name[512] = { 0 };
	wchar_t value[1024] = { 0 };
	PopStringW(fun_name);
	PopStringW(value);

	if (!wcsicmp(L"nsisSetInstallDir", fun_name)) {
		Global::Get()->SetProductInstallDir(value);
	}
	else if (!wcsicmp(L"nsisSetProgramMain", fun_name)) {
		Global::Get()->SetProductProgramMain(value);
	}

}

NSISAPI GetControlAttribute(HWND hwndParent, int string_size, TCHAR* variables, stack_t** stacktop, extra_parameters* extra)
{
	NSIS_INIT_EXTRA_PARAMETERS(extra);
	wchar_t nsisFun[512] = { 0 };
	PopStringW(nsisFun);

	std::wstring str(nsisFun);
	if (!str.compare(L"nsisGetInstallDir")) {
		//std::wstring install_path = Global::Get()->GetProductInstallDir();
		std::wstring install_dir = shared::Win::PathFixedW(ui::UIFrame::Get()->GetInstallDir());
		PushStringW(install_dir.c_str());
		//MessageBoxW(NULL, install_dir.c_str(), NULL, MB_TOPMOST);
	}
}

NSISAPI SetWindowSize(HWND hwndParent, int string_size, TCHAR* variables, stack_t** stacktop, extra_parameters* extra)
{
	//MessageBoxW(NULL, __FUNCTIONW__, NULL, MB_TOPMOST);
#if 0
	NSMETHOD_INIT(hwndParent);
	int hwnd = PopInt();
	int width = PopInt();
	int height = PopInt();
	if (width > -1 && height > -1)
	{
		g_dialog->ResizeClient(width, height);
	}
#endif
}

NSISAPI SelectInstallDir(HWND hwndParent, int string_size, TCHAR* variables, stack_t** stacktop, extra_parameters* extra)
{
	//MessageBoxW(NULL, __FUNCTIONW__, NULL, MB_TOPMOST);
#if 0
	NSMETHOD_INIT(hwndParent);
	TCHAR title[512] = { 0 };
	int hwnd = PopInt();
	PopString(title);
	{
		BROWSEINFO bi;
		memset(&bi, 0, sizeof(BROWSEINFO));
		bi.hwndOwner = g_dialog->GetHWND();
		bi.lpszTitle = title;
		bi.ulFlags = 0x0040;

		TCHAR szFolderPath[MAX_PATH] = { 0 };
		LPITEMIDLIST idl = SHBrowseForFolder(&bi);
		if (idl == NULL) {
			PushString(szFolderPath);
			return;
		}

		SHGetPathFromIDList(idl, szFolderPath);
		PushString(szFolderPath);
	}
#endif
}

NSISAPI ExitDUISetup(HWND hwndParent, int string_size, TCHAR* variables, stack_t** stacktop, extra_parameters* extra)
{
	MessageBoxW(NULL, __FUNCTIONW__, NULL, MB_TOPMOST);
#if 0
	ExitProcess(0);
#endif
}