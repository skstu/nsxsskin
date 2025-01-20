#include "stdafx.h"

WindowThread::WindowThread() : nbase::FrameworkThread("WindowThread") {

}
WindowThread::~WindowThread() {

}
void WindowThread::Init() {
	nbase::ThreadManager::RegisterThread(kThreadUI);

	misc_thread_.reset(new MiscThread(kThreadGlobalMisc, "Global Misc Thread"));
	misc_thread_->Start();

#ifdef _DEBUG
	ui::GlobalManager::Startup(LR"(C:\Users\k34ub\source\skstu\devkit_last\projects\chromium\installer\res\resources\)", ui::CreateControlCallback(), false);
#else
	ui::GlobalManager::OpenResZip(MAKEINTRESOURCE(IDR_THEME), L"THEME", "");
	ui::GlobalManager::Startup(L"resources\\", ui::CreateControlCallback(), false);
#endif

	ui::GlobalManager::EnableAutomation();

	// 创建一个默认带有阴影的居中窗口
	Window* window = new Window();
	window->Create(NULL, kClassName, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
	window->CenterWindow();
	window->ShowWindow();
}

void WindowThread::Cleanup() {
	ui::GlobalManager::Shutdown();

	misc_thread_->Stop();
	misc_thread_.reset(nullptr);

	SetThreadWasQuitProperly(true);
	nbase::ThreadManager::UnregisterThread();
}