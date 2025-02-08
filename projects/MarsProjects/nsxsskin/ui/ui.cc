#include "stdafx.h"
using namespace ui;

UIFrame::UIFrame() : nbase::FrameworkThread("XSUIFrameThread") {
}
UIFrame::~UIFrame() {
}
void UIFrame::Init() {
	SetProcessDPIAware();

	nbase::ThreadManager::RegisterThread(kThreadUI);

	misc_thread_.reset(new MiscThread(kThreadGlobalMisc, "Global Misc Thread"));
	misc_thread_->Start();

#if _DEBUG
	ui::GlobalManager::Startup(Global::Get()->GetSkinDir(), ui::CreateControlCallback(), false);
#else
	auto skin_dir = Global::Get()->GetSkinDir();
	const std::wstring path = stl::Path::PathnameToPath(skin_dir);
	Zipcc::zipUnCompress(Utfpp::ws_to_u16(skin_dir), Utfpp::ws_to_u16(path));
	ui::GlobalManager::Startup(path + LR"(\skin\)", ui::CreateControlCallback(), false);
#endif

	//ui::GlobalManager::EnableAutomation();

	installer_ = new Installer(Global::Get()->GetInstallerProcessType());
	// 创建一个默认带有阴影的居中窗口
	installer_->Create(NULL, kClassNameInstaller, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0, true);
	installer_->CenterWindow();
	installer_->ShowWindow();
}
void UIFrame::Cleanup() {
	ui::GlobalManager::Shutdown();

	misc_thread_->Stop();
	misc_thread_.reset(nullptr);

	SetThreadWasQuitProperly(true);
	nbase::ThreadManager::UnregisterThread();
}
bool UIFrame::Start() {
	do {
		if (open_.load())
			break;
		open_.store(true);
		threads_.emplace_back([this]() {Process(); });
	} while (0);
	return open_.load();
}
void UIFrame::Stop() {
	do {
		if (!open_.load())
			break;
		open_.store(false);
		for (auto& t : threads_)
			t.join();
		threads_.clear();
	} while (0);
}
void UIFrame::Process() {
	do {
		RunOnCurrentThreadWithLoop(nbase::MessageLoop::kUIMessageLoop);
	} while (0);
}
void UIFrame::ProcessStatusSet(const ProcessStatus& status) {
	std::lock_guard<std::mutex> lock{ *mtx_ };
	process_status_ = status;
}
ProcessStatus UIFrame::ProcessStatusGet() const {
	std::lock_guard<std::mutex> lock{ *mtx_ };
	return process_status_;
}
std::wstring UIFrame::GetInstallDir() const {
	std::wstring result;
	std::lock_guard<std::mutex> lock{ *mtx_ };
	if (installer_) {
		result = installer_->GetInstallDir();
	}
	return result;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
static UIFrame* __gpsUIFrame = nullptr;
UIFrame* UIFrame::Get() {
	if (!__gpsUIFrame)
		__gpsUIFrame = new UIFrame();
	return __gpsUIFrame;
}
void UIFrame::Destroy() {
	if (__gpsUIFrame) {
		__gpsUIFrame->Stop();
	}
	SK_DELETE_PTR(__gpsUIFrame);
}