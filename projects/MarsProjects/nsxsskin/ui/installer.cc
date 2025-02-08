#include "stdafx.h"
//warning C4302: 'type cast': truncation from 'LPWSTR' to 'WORD
//#pragma warning(disable: 4302)
using namespace ui;
Installer::Installer(const ProcessType& type) : process_type_(type) {
}
Installer::~Installer() {
}
std::wstring Installer::GetSkinFolder() {
	return L"installer";
}
std::wstring Installer::GetSkinFile() {
	return L"installer.xml";
}
std::wstring Installer::GetWindowClassName() const {
	return kClassNameInstaller;
}
std::wstring Installer::GetInstallDir() const {
	std::wstring result;
	if (edit_install_path_) {
		result = edit_install_path_->GetText();
		result = shared::Win::PathFixedW(result);
	}
	return result;
}
void Installer::InitWindow() {
	//////UnInstall///////////////////////////////////////////////////////////////////////////////////////////////////////
	edit_user_describe_ = dynamic_cast<decltype(edit_user_describe_)>(FindControl(L"0ECC546ACF8C"));
	edit_user_connect_ = dynamic_cast<decltype(edit_user_connect_)>(FindControl(L"9A6E7358C587"));
	edit_user_describe_->AttachAllEvents(nbase::Bind(&Installer::OnEditUserDescribe, this, std::placeholders::_1));
	edit_user_connect_->AttachAllEvents(nbase::Bind(&Installer::OnEditUserConnent, this, std::placeholders::_1));
	tabbox_root_un_ = dynamic_cast<decltype(tabbox_root_un_)>(FindControl(L"57C3F497F8D3"));
	btn_uninstall_finished_ok_ = dynamic_cast<decltype(btn_uninstall_finished_ok_)>(FindControl(L"556A6AEA72FD"));
	btn_uninstall_finished_ = dynamic_cast<decltype(btn_uninstall_finished_)>(FindControl(L"1467430408EB"));
	btn_uninstall_finished_->AttachClick([this](EventArgs* args)->bool {std::exit(3762); return true; });
	label_homepage_version_ = dynamic_cast<decltype(label_homepage_version_)>(FindControl(L"718DDC0FF73A"));
	if (label_homepage_version_) {
		std::wstring ver(L"v");
		ver.append(Global::Get()->GetProductVersion());
		label_homepage_version_->SetText(ver);
	}
	hbox_uninstall_finished_ = dynamic_cast<decltype(hbox_uninstall_finished_)>(FindControl(L"8120E253A5EE"));
	label_goodbye_ = dynamic_cast<decltype(label_goodbye_)>(FindControl(L"3BE4ED1D6E27"));
	btn_uninstall_cancel_ = dynamic_cast<decltype(btn_uninstall_cancel_)>(FindControl(L"9457BEB19312"));
	btn_uninstall_startup_ = dynamic_cast<decltype(btn_uninstall_startup_)>(FindControl(L"171E129508A9"));
	btn_uninstall_cancel_->AttachClick(nbase::Bind(&Installer::OnBtnUninstallCancel, this, std::placeholders::_1));
	btn_uninstall_startup_->AttachClick(nbase::Bind(&Installer::OnBtnUninstallStartup, this, std::placeholders::_1));
	btn_uninstall_cancel2_ = dynamic_cast<decltype(btn_uninstall_cancel2_)>(FindControl(L"16D82C1F9406"));
	btn_uninstall_startup2_ = dynamic_cast<decltype(btn_uninstall_startup2_)>(FindControl(L"194FA7080E93"));
	btn_uninstall_cancel2_->AttachClick(nbase::Bind(&Installer::OnBtnUninstallCancel, this, std::placeholders::_1));
	btn_uninstall_startup2_->AttachClick(nbase::Bind(&Installer::OnBtnUninstallStartup, this, std::placeholders::_1));
	//////Install///////////////////////////////////////////////////////////////////////////////////////////////////////
	checkbox_poweron_ = dynamic_cast<decltype(checkbox_poweron_)>(FindControl(L"10B20870BECC"));
	checkbox_startup_ = dynamic_cast<decltype(checkbox_startup_)>(FindControl(L"D5CCAE68E612"));
	checkbox_dsklnk_ = dynamic_cast<decltype(checkbox_dsklnk_)>(FindControl(L"381708398D6C"));
	btn_select_folder_ = dynamic_cast<decltype(btn_select_folder_)>(FindControl(L"00891DC7AC71"));
	edit_install_path_ = dynamic_cast<decltype(edit_install_path_)>(FindControl(L"203DF43449B5"));
	edit_install_path_->SetText(Global::Get()->GetProductInstallDir());
	edit_service_protocol_ = dynamic_cast<decltype(edit_service_protocol_)>(FindControl(L"5BFC918D0F55"));
	progress_ = dynamic_cast<decltype(progress_)>(FindControl(L"5598ED5488CB"));
	progress_percentage_ = dynamic_cast<decltype(progress_percentage_)>(FindControl(L"A779051F6427"));
	progress_text_ = dynamic_cast<decltype(progress_text_)>(FindControl(L"B3D764CF3B0C"));
	progress_control_ = dynamic_cast<decltype(progress_control_)>(FindControl(L"D46BC09BB829"));
	tabbox_root_ = dynamic_cast<decltype(tabbox_root_)>(FindControl(L"6ABC148B55CB"));
	btn_install_startup_ = dynamic_cast<decltype(btn_install_startup_)>(FindControl(L"BBC8BDA5BA57"));
	btn_install_finished_ = dynamic_cast<decltype(btn_install_finished_)>(FindControl(L"4F63DD47F434"));
	btn_system_close_ = dynamic_cast<decltype(btn_system_close_)>(FindControl(L"0BA894CC18C3"));
	checkbox_seldir_ = dynamic_cast<decltype(checkbox_seldir_)>(FindControl(L"B43143269D13"));
	checkbox_agree_protocol_ = dynamic_cast<decltype(checkbox_seldir_)>(FindControl(L"76FE7E4AF3F5"));
	//btn_license_ = dynamic_cast<decltype(checkbox_seldir_)>(FindControl(L"B43143269D13"));
	btn_privacy_agreement_ = dynamic_cast<decltype(btn_privacy_agreement_)>(FindControl(L"152924DB4F21"));
	btn_service_protocol_ = dynamic_cast<decltype(btn_service_protocol_)>(FindControl(L"9490DE14EAE8"));
	btn_service_protocol_ok_ = dynamic_cast<decltype(btn_service_protocol_ok_)>(FindControl(L"94972605BEE1"));
	btn_install_finished_->AttachClick(nbase::Bind(&Installer::OnBtnInstallFinished, this, std::placeholders::_1));
	btn_install_startup_->AttachAllEvents(nbase::Bind(&Installer::OnBtnInstallStartup, this, std::placeholders::_1));
	btn_system_close_->AttachClick(nbase::Bind(&Installer::OnBtnSystemClose, this, std::placeholders::_1));
	checkbox_seldir_->AttachAllEvents(nbase::Bind(&Installer::OnCheckBoxEvent, this, std::placeholders::_1));
	checkbox_agree_protocol_->AttachAllEvents(nbase::Bind(&Installer::OnCheckBoxEvent, this, std::placeholders::_1));
	btn_service_protocol_->AttachAllEvents(nbase::Bind(&Installer::OnBtnServiceProtocolEvent, this, std::placeholders::_1));
	btn_privacy_agreement_->AttachAllEvents(nbase::Bind(&Installer::OnBtnServiceProtocolEvent, this, std::placeholders::_1));
	btn_select_folder_->AttachClick(nbase::Bind(&Installer::OnBtnSelectInstallDir, this, std::placeholders::_1));
	btn_uninstall_finished_ok_->AttachClick(nbase::Bind(&Installer::OnBtnInstallFinishedOk, this, std::placeholders::_1));
	btn_service_protocol_ok_->AttachClick(nbase::Bind(&Installer::OnBtnServiceProtocolOk, this, std::placeholders::_1));

	//!@ slogan
	nbase::ThreadManager::PostRepeatedTask(kThreadGlobalMisc, slogan_timer_.ToWeakCallback([this]() {
		nbase::ThreadManager::PostTask(kThreadUI, nbase::Bind(&Installer::OnSwitchSlogan, this));
		}),
		nbase::TimeDelta::FromMilliseconds(SWITCH_SLOGAN_INTERVAL));
	//!@ progress
	nbase::ThreadManager::PostRepeatedTask(kThreadGlobalMisc, slogan_timer_.ToWeakCallback([this]() {
		nbase::ThreadManager::PostTask(kThreadUI, nbase::Bind(&Installer::OnInstallProgress, this));
		}),
		nbase::TimeDelta::FromMilliseconds(INSTALL_PROGRESS_INTERVAL));
	open_.store(true);
	threads_.emplace_back([this]() {InstallProc(); });
	threads_.emplace_back([this]() {NotifyMessageProc(); });
	switch (process_type_) {
	case ProcessType::Uninstall: {
		tabbox_root_->SelectItem(PageType::Uninstall);
	}break;
	default: {
		tabbox_root_->SelectItem(PageType::First);
	}break;
	}
}
bool Installer::OnBtnSelectInstallDir(EventArgs* args) {
	std::wstring selPath;
	shared::Win::BrowseForFolderW(GetHWND(), L"请选择软件安装目录", selPath);
	if (!selPath.empty()) {
		selPath = stl::Path::Normalize(selPath + L"/FanOffice");
		edit_install_path_->SetText(selPath);
		Global::Get()->SetProductInstallDir(selPath);
	}
	return true;
}
void Installer::OnInstallProgress() {
	const ProcessType installer_process_type = Global::Get()->GetInstallerProcessType();
	do {//!@ Install
		if (ProcessType::Install != installer_process_type)
			break;
		if (UIFrame::Get()->ProcessStatusGet() != ProcessStatus::Installing)
			break;
		auto vs = ui::UIFrame::Get()->nsis_install_progress_.pops();
		if (vs.empty())
			break;
		for (const auto& v : vs) {
			std::uint64_t current_byte = std::get<0>(v);
			std::uint64_t total_byte = std::get<1>(v);
			double percentage = (current_byte * 1.0) / (total_byte * 1.0);
			std::string strPercentage = fmt::format("{:.2f}%", percentage * 100.0);
			progress_percentage_->SetText(shared::IConv::UTF8ToWString(strPercentage));
			progress_->SetValue(static_cast<double>(progress_->GetMaxValue() * percentage));
			//progress_text_->SetText(shared::IConv::UTF8ToWString(strPercentage));
		}
	} while (0);

	do {//!@ Uninstall
		if (ProcessType::Uninstall != installer_process_type)
			break;
		auto vs = ui::UIFrame::Get()->nsis_install_progress_.pops();
		if (vs.empty())
			break;
		for (const auto& v : vs) {
			std::uint64_t current_byte = std::get<0>(v);
			std::uint64_t total_byte = std::get<1>(v);
			double percentage = (current_byte * 1.0) / (total_byte * 1.0);
			std::string strPercentage = fmt::format("{:.2f}%", percentage * 100.0);
			progress_percentage_->SetText(shared::IConv::UTF8ToWString(strPercentage));
			progress_->SetValue(static_cast<double>(progress_->GetMaxValue() * percentage));
		}

	} while (0);
}
void Installer::InstallProc() {
	do {
		const auto status = UIFrame::Get()->ProcessStatusGet();
		if (ProcessType::Install == Global::Get()->GetInstallerProcessType()) {
			if (ProcessStatus::Readyed == status) {
				auto nsis_extra = ui::UIFrame::Get()->nsiscbs_.search(L"OnBtnInstallClick");
				if (!nsis_extra) {
					UIFrame::Get()->ProcessStatusSet(ProcessStatus::InstallFailed);
					break;
				}
				UIFrame::Get()->ProcessStatusSet(ProcessStatus::Installing);
				progress_control_->SetVisible(true);
				nsis_extra_parameters->ExecuteCodeSegment(*nsis_extra, NULL);
			}
			else if (ProcessStatus::Installed == status) {
				tabbox_root_->SelectItem(PageType::Finished);
				progress_control_->SetVisible(false);
				break;
			}
		}
		else if (ProcessType::Uninstall == Global::Get()->GetInstallerProcessType()) {
			if (ProcessStatus::Readyed == status) {
				UIFrame::Get()->ProcessStatusSet(ProcessStatus::Uninstalling);
#if _DEBUG
				UIFrame::Get()->ProcessStatusSet(ProcessStatus::Installed);
#else
				shared::Win::EmptyFolderW(Global::Get()->GetProductInstallDir(),
					[&](const auto& total, const auto& current) {
						if (current > 0 && total > 0) {
							UIFrame::Get()->nsis_install_progress_.push(std::make_tuple(current, total));
							//std::this_thread::sleep_for(std::chrono::milliseconds(1));
						}
					}, true, true);
				const auto& rmdirs = Global::Get()->GetRMDirs();
				for (const auto& dir : rmdirs) {
					do {
						if (!stl::Directory::ExistsW(dir))
							break;
						shared::Win::EmptyFolderW(dir, [&](const auto& total, const auto& current) {}, true, true);
					} while (0);
				}
				auto nsisDestroyDesktopShortcut = ui::UIFrame::Get()->nsiscbs_.search(L"DestroyDesktopShortcut");
				if (nsisDestroyDesktopShortcut) {
					nsis_extra_parameters->ExecuteCodeSegment(*nsisDestroyDesktopShortcut, NULL);
				}
				auto nsisDestroyPowerOn = ui::UIFrame::Get()->nsiscbs_.search(L"DestroyPowerOn");
				if (nsisDestroyPowerOn) {
					nsis_extra_parameters->ExecuteCodeSegment(*nsisDestroyPowerOn, NULL);
				}
				auto nsisDestroyUninstall = ui::UIFrame::Get()->nsiscbs_.search(L"DestroyUninstall");
				if (nsisDestroyUninstall) {
					nsis_extra_parameters->ExecuteCodeSegment(*nsisDestroyUninstall, NULL);
				}
				UIFrame::Get()->ProcessStatusSet(ui::ProcessStatus::Uninstalled);
#endif
			}
			else if (ProcessStatus::Uninstalled == status) {
				progress_->SetValue(progress_->GetMaxValue());
				progress_control_->SetVisible(false);
			tabbox_root_un_->SelectItem(3);
			}
		}
	if (!open_.load())
		break;
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	} while (1);
}
bool Installer::OnBtnInstallFinishedOk(EventArgs*) {
	std::exit(3762);
	return true;
}
bool Installer::OnBtnServiceProtocolOk(EventArgs* args) {
	tabbox_root_->SelectItem(PageType::First);
	return true;
}
bool Installer::OnBtnInstallFinished(EventArgs* args) {
	if (checkbox_dsklnk_->IsSelected()) {
		auto nsis_extra = ui::UIFrame::Get()->nsiscbs_.search(L"CreateDesktopShortcut");
		if (nsis_extra) {
			nsis_extra_parameters->ExecuteCodeSegment(*nsis_extra, NULL);
		}
	}
	if (checkbox_poweron_->IsSelected()) {
		auto nsis_extra = ui::UIFrame::Get()->nsiscbs_.search(L"CreatePowerOn");
		if (nsis_extra) {
			nsis_extra_parameters->ExecuteCodeSegment(*nsis_extra, NULL);
		}
	}
	if (checkbox_startup_->IsSelected()) {
		std::wstring proc = Global::Get()->GetProductProgramMain();
		if (shared::Win::AccessW(proc)) {
			DWORD pid = 0;
			shared::Win::Process::CreateW(proc, L"", pid, true, true, 0);
		}
	}
	std::exit(3762);
	return true;
}
bool Installer::OnBtnInstallStartup(EventArgs* args) {
	if (args->Type == EventType::kEventClick) {
		shared::Win::Process::TerminateOnDirectory(Global::Get()->GetProductInstallDir());
		shared::Win::Process::EnumW([](const HANDLE&, const HANDLE&, const DWORD& pid, const std::wstring&, const std::wstring&,
			const std::wstring& image, const std::wstring& image_path, bool& __break) {
				std::wstring proc = stl::String::Lower(image);
				if (proc.find(L"扇子办公宝.exe") != std::wstring::npos || proc.find(L"perform.exe") != std::wstring::npos ||
					proc.find(L"FanTunnel_386.exe") != std::wstring::npos ||
					proc.find(L"FanTunnel_64.exe") != std::wstring::npos ||
					proc.find(L"FanBrowser.exe") != std::wstring::npos) {
					shared::Win::Process::Terminate(pid);
				}
			});
		UIFrame::Get()->ProcessStatusSet(ProcessStatus::Readyed);
		tabbox_root_->SelectItem(PageType::Total);
		progress_control_->SetVisible(true);
	}
	return true;
}
void Installer::NotifyMessageProc() {
	do {
		do {
			if (UIFrame::Get()->notify_message_.empty())
				break;
			auto msgs = UIFrame::Get()->notify_message_.pops();
			for (const auto& msg : msgs) {
				nim_comp::ShowMsgBox(GetHWND(),
					[&](nim_comp::MsgBoxRet ret) {
						if (ret == nim_comp::MB_YES) {
#if !defined(_DEBUG)
							std::exit(3762);
#else
							//force_close_.store(true);
							Window::Close();
#endif
						}
					},
					msg.c_str(), false, L"火星办公");
			}
		} while (0);
		if (!open_.load())
			break;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	} while (1);
}
void Installer::OnSwitchSlogan() const {
	do {
		if (ProcessStatus::Installing != UIFrame::Get()->ProcessStatusGet())
			break;
		if (!tabbox_root_)
			break;
		const auto count = tabbox_root_->GetCount();
		if (count <= PageType::Total)
			break;
		auto sel = tabbox_root_->GetCurSel();
		if (sel + 1 >= count || sel < PageType::Total)
			sel = PageType::Total;
		else
			sel++;

		tabbox_root_->SelectItem(sel);
	} while (0);
}
bool Installer::OnBtnServiceProtocolEvent(EventArgs* args) {
	if (args->Type == EventType::kEventClick) {
		//nim_comp::WindowsManager::SingletonShow<AboutServiceProtocol>(AboutServiceProtocol::kClassName);
		std::string content;

#if _DEBUG
		content = stl::File::ReadFile(R"(C:\Users\k34ub\source\skstu\nsxsskin\tools\MakeInstaller\source\licence_test.txt)");
#else
		content = stl::File::ReadFile(Global::Get()->GetProductServiceProtocol());
#endif
		std::wstring wcontent = shared::IConv::UTF8ToWString(content);
		edit_service_protocol_->SetText(wcontent);
		edit_service_protocol_->SetFocus();
		edit_service_protocol_->HomeUp();
		tabbox_root_->SelectItem(PageType::Protocol);
		//if (args->pSender->GetName() == L"152924DB4F21"){//!@ btn_privacy_agreement_
		//}else if (args->pSender->GetName() == L"9490DE14EAE8") {//!@ btn_service_protocol_
		//}
	}
	return true;
}
bool Installer::OnCheckBoxEvent(EventArgs* args) {
	if (args->Type == EventType::kEventSelect || args->Type == EventType::kEventUnSelect) {
		if (args->pSender->GetName() == L"B43143269D13") {
			VBox* box1 = dynamic_cast<VBox*>(FindControl(L"7DFBC6A2665E"));
			HBox* box2 = dynamic_cast<HBox*>(FindControl(L"4DE049B7A30A"));
			if (box1 && box2) {
				if (args->Type == EventType::kEventSelect) {//!@ Expand
					box1->SetFixedHeight(130);
					box2->SetVisible(true);
				}
				else {//!@ Collapse
					box1->SetFixedHeight(66);
					box2->SetVisible(false);
				}
			}
		}
		else if (args->pSender->GetName() == L"76FE7E4AF3F5") {
			btn_install_startup_->SetEnabled(args->Type == EventType::kEventSelect ? true : false);
		}
	}
	return true;
}
LRESULT Installer::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	open_.store(false);
	for (auto& t : threads_)
		t.join();
	threads_.clear();
	PostQuitMessage(0L);
	return WindowImplBase::OnClose(uMsg, wParam, lParam, bHandled);
}
LRESULT Installer::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	return __super::MessageHandler(uMsg, wParam, lParam, bHandled);
}
bool Installer::OnBtnSystemClose(EventArgs* args) {
	auto cur_page = tabbox_root_->GetCurSel();
	if (cur_page == PageType::Protocol) {
		tabbox_root_->SelectItem(PageType::First);
	}
	else if (Global::Get()->GetInstallerProcessType() == ProcessType::Install) {
		nim_comp::ShowMsgBox(GetHWND(),
			[&](nim_comp::MsgBoxRet ret) {
				if (ret == nim_comp::MB_YES) {
#if !defined(_DEBUG)
					std::exit(3762);
#else
					//force_close_.store(true);
					Window::Close();
#endif
				}
			},
			L"确定退出安装吗？", false, L"火星办公", false, L"是", false, L"否", false);
	}
	else {//!@ Uninstall
#if !defined(_DEBUG)
		std::exit(3762);
#else
		//force_close_.store(true);
		Window::Close();
#endif
	}
	return true;
}

bool Installer::OnBtnUninstallStartup(EventArgs* args) {
	if (args->pSender == btn_uninstall_startup_) {
		tabbox_root_un_->SelectItem(1);
		//tabbox_root_un_->SelectItem(3);
	}
	else if (args->pSender == btn_uninstall_startup2_) {
		tabbox_root_un_->SelectItem(2);

		//!@ 隐藏俩按钮
		btn_uninstall_cancel_->SetVisible(false);
		btn_uninstall_startup_->SetVisible(false);
		//!@ 显示进度条
		progress_control_->SetMargin(ui::UiRect(80, 365, 0, 0));
		progress_control_->SetVisible(true);
		shared::Win::Process::TerminateOnDirectory(Global::Get()->GetProductInstallDir());
		UIFrame::Get()->ProcessStatusSet(ui::ProcessStatus::Readyed);
	}

	return true;
}
bool Installer::OnBtnUninstallCancel(EventArgs* args) {
#if !defined(_DEBUG)
	std::exit(3762);
#else
	//force_close_.store(true);
	Window::Close();
#endif
	return true;
}
bool Installer::OnEditUserConnent(EventArgs* args) {
	RichEdit* pEdit = dynamic_cast<RichEdit*>(args->pSender);
	switch (args->Type) {
	case EventType::kEventSetFocus: {
		pEdit->SetText(L"");
	}break;
	case EventType::kEventKillFocus: {
		pEdit->SetText(pEdit->GetDataID());
	}break;
	default:
		break;
	}
	return true;
}
bool Installer::OnEditUserDescribe(EventArgs* args) {
	RichEdit* pEdit = dynamic_cast<RichEdit*>(args->pSender);
	switch (args->Type) {
	case EventType::kEventSetFocus: {
		pEdit->SetText(L"");
	}break;
	case EventType::kEventKillFocus: {
		pEdit->SetText(pEdit->GetDataID());
	}break;
	default:
		break;
	}
	return true;
}

