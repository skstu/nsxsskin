#include "stdafx.h"
using namespace ui;
const std::wstring test_content = LR"(Microsoft 软件许可条款 
Applies To Microsoft Security Essentials这些许可条款是 Microsoft Corporation（或您所在地的其中一个关联公司）与您之间达成的协议。 请阅读本条款。 本条款适用于上述软件，包括您用来接收该软件的媒体（如果有）。 本条款也适用于 Microsoft 为该软件提供的任何后续版本（包括任何更新或补充）、更新、补充、基于 Internet 的服务和支持服务，除非上述条款附带有其他条款。 如果确实附带其他条款，则附加条款应适用。使用该软件，即表示您接受这些条款。如果您不接受这些条款，请不要使用该软件。如下所述，安装或使用该软件也表示您同意在验证、自动下载和安装某些更新期间传输某些标准计算机信息以便获取基于 Internet 的服务。如果您遵守这些许可条款，将拥有以下权利。1.安装和使用权利。家庭使用。 如果您是家庭用户，则可以在您的个人设备上安装和使用任意数量的本软件副本供您的家庭成员使用。小型企业。 如果您经营一家小型企业，则最多可以在企业中的十 (10) 台设备上安装和使用本软件。限制。 本软件不得在政府或学术机构的设备上使用。组件分离。 该软件的各组件是作为一个整体被授予许可的。 您不得分离这些组件并将其安装在不同的设备上。包含的 Microsoft 程序。 该软件包含其他 Microsoft 程序。 您使用这些程序时应遵守这些程序的许可条款。2.基于 Internet 的服务。 Microsoft 随该软件提供基于 Internet 的服务。 可能随时更改或取消这些服务。同意使用基于 Internet 的服务。 下述以及 Microsoft Security Essentials 隐私声明中的软件功能可通过 Internet 连接到 Microsoft 或服务提供商的计算机系统。 在某些情况下，您不会在连接建立时另外收到通知。 在某些情况下，您可以关闭这些功能或不使用它们。 有关这些功能的详细信息，请参阅 http://go.microsoft.com/fwlink/?LinkId=148744。 使用这些功能，即表示您同意传输此信息。Microsoft 不会将这些信息用于识别您的身份或与您联系。1.计算机信息。 以下功能使用 Internet 协议，向相应的系统发送计算机信息，例如您的 Internet 协议地址、操作系统类型、浏览器及您使用的软件的名称和版本、安装该软件的设备的语言代码等。 Microsoft 使用此类信息是为了向您提供基于 Internet 的服务。更新。 默认情况下，该软件将自动下载定义更新。 有关详细信息，请参阅隐私声明，网址为 http://go.microsoft.com/fwlink/?LinkId=148744。恶意软件删除。 该软件会在定期扫描以及您选择此操作时检查并删除存储在设备中严重程度为高的某些恶意软件（以下简称“恶意软件”）。 该软件在您的设备上检查恶意软件时，会向 Microsoft 发送一份报告，其中包含检测到的任何恶意软件或该软件检查恶意软件时发生的错误、与检测相关的特定信息、该软件之前检查恶意软件时已发生的错误以及设备的其他相关信息，我们可以用这些信息对此产品及其他 Microsoft 产品和服务进行改进。 报告中不包含任何可用来识别您的身份的信息。可能不需要的软件。 该软件将在您的计算机中搜索严重程度介于低等和中等之间的恶意软件，包括但不限于间谍软件和其他可能不需要的软件（以下简称“可能不需要的软件”）。 只有当您同意时，该软件才会删除或禁用严重程度介于低等和中等之间的可能不需要的软件。 如果其他软件在您的计算机上安装了可能不需要的软件，以此作为您使用其他软件的条件，那么，删除或禁用此可能不需要的软件可能会导致计算机上的其他软件停止工作，并且可能会导致您违反计算机上其他软件的使用许可。 在授权删除此可能不需要的软件之前，您应该先阅读针对其他软件的许可协议。 使用该软件，也可能导致您或系统删除或禁用不属于“可能不需要的软件”的软件。加入 Microsoft 主动保护服务 (MAPS)。 Microsoft 主动保护服务 (MAPS) 反恶意软件社区是一个包含 Microsoft Security Essentials 用户的自愿参加的全球化社区。 在初始安装时，将默认选择用户加入 MAPS，并成为其基本成员。 如果您具备基本成员资格，则在打开该软件时，MAPS 可以向 Microsoft 报告关于恶意软件以及其他形式的可能不需要的软件的信息。 如果 MAPS 报告包括有关该软件可能能够删除的恶意软件或可能不需要的软件的详细信息，则 MAPS 将下载最新签名对其进行处理。 MAPS 还能够发现“误报”（某项内容最初被确定为恶意软件，结果却并非如此）并解决这些误报问题。 在某些情况下，可能会无意中将个人信息发送到 Microsoft。 但是，Microsoft 不会将这些信息用于识别您的身份或与您联系。 若要了解有关 MAPS 以及此功能传输至 Microsoft 的信息的详细信息，请参阅隐私声明，网址为 http://go.microsoft.com/fwlink/?LinkId=148744。错误报告。 此软件会自动向 Microsoft 发送错误报告，描述出现错误的软件组件。 该软件不会发送文件或内存转储，除非您选择发送这些内容。 有关错误报告的详细信息，请参阅 http://go.microsoft.com/fwlink/?LinkId=148744。Windows 更新；Microsoft 更新。 该软件会打开 Windows 更新和 Microsoft 更新的自动更新。 若要使该软件中的 Windows 更新和 Microsoft 更新服务正常工作，将需要时常更新或下载 Windows 更新和/或 Microsoft 更新服务，并且无通知地下载并安装。2.使用信息。 我们可能会使用计算机信息、错误报告、CEIP 信息和恶意软件报告来改进我们的软件和服务。 我们还可能与其他各方共享这些信息，例如硬件和软件供应商。 他们可能会使用这些信息改进其产品与 Microsoft 软件的兼容性。3.许可范围。 该软件只是授予许可，并非出售。 本协议只授予您使用该软件的某些权利。 Microsoft 保留所有其他权利。 除非适用的法律赋予您此项限制之外的更多权利，否则您只能在本协议明确许可的范围内使用该软件。 在按规定使用软件时，必须遵守软件中的任何技术限制，这些限制只允许您以特定的方式使用软件。 您不得绕过该软件中的任何技术限制；对该软件进行反向工程、反编译或反汇编；尽管有此项限制，但如果适用法律明确许可上述活动，并仅在适用法律明确许可的范围内从事上述活动则不在此限；制作超过本协议所规定或适用法律（尽管已有本协议的这一限制）所允许数量的软件副本；发布该软件以便他人复制；出租、租赁或出借该软件；向任何第三方转让该软件或本协议；或使用该软件提供商业软件主机服务。4.备份副本。您可以制作该软件的一个备份副本。 您只可以用它来重新安装该软件。5.文档。 任何对您的计算机或内部网络拥有有效访问权限的人都可以为您的内部参考目的而复制和使用文档。6.转移至另一台设备。 您可以卸载该软件，然后安装到另一台设备上进行使用。 不得通过此方法在多台设备之间共享此许可。7.出口限制。 相关软件受美国出口法律法规的管辖。 必须遵守适用于该软件的所有国内和国际出口法律和法规。 这些法律包括对目的地、最终用户和最终用途的各种限制。 8.支持服务。 因为该软件按“原样”提供，所以我们可能不为其提供支持服务。9.完整协议。本协议以及您使用的补充、更新、基于 Internet 的服务和支持服务的有关条款，共同构成了该软件和支持服务的完整协议。10.适用法律。美国如果您是在美国购买了该软件，对本协议的解释以及由于违反本协议而引起的索赔均适用华盛顿州法律，不论法律原则是否有冲突。 其他索赔，包括关于各州消费者保护法、反不正当竞争法和侵权法的索赔，均受用户所在州的法律管辖。美国以外的国家和地区。 如果在任何其他国家/地区获取该软件，将适用该国家/地区的法律。11.法律效力。 本协议规定了部分法律权利。 根据您所在国家/地区的法律规定，您可能享有其他权利。 您还可能享有与您的软件卖方相关的权利。 如果您所在国家/地区的法律不允许本协议改变您所在国家/地区法律赋予您的权利，则本协议将不改变您按照所在国家/地区的法律应享有的权利。 12.免责声明。该软件按“原样”授予许可。您自行承担所有使用风险。Microsoft 不提供任何明示的担保、保证或条件。用户可享有其所在地法律赋予的本协议无法变更的其他消费者权利。在您当地法律允许的范围内，Microsoft 排除有关适销性、针对特定目的的适用性和不侵权的默示保证。仅限澳大利亚： 您享有《澳大利亚消费者法》规定的法定保障，这些条款中的任何规定均无意影响这些权利。补救办法和损害赔偿的限制和排除。您只能因直接损害从 Microsoft 及其供应商处获得退款，且退款金额上限为 5.00 美元。您不能因任何其他损害获得退款，包括后果性的、利润损失、特殊、间接或附带的损害。此限制适用于 与第三方 Internet 站点上或第三方程序中的软件、服务、内容（包括代码）相关的任何情况；以及在适用法律许可的范围内就违约、违反保证、担保或条件、严格责任、过失或其他侵权责任所提起的索赔。即使 Microsoft 知道或应该知道出现损害的可能性，该限制也同样适用。 由于您所在国家/地区可能不允许排除或限制附带的、后果性的或其他损害赔偿责任，上述限制和排除可能不适用于您。)";
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
	label_goodbye_ = dynamic_cast<decltype(label_goodbye_)>(FindControl(L"3BE4ED1D6E27"));
	btn_uninstall_cancel_ = dynamic_cast<decltype(btn_uninstall_cancel_)>(FindControl(L"9457BEB19312"));
	btn_uninstall_startup_ = dynamic_cast<decltype(btn_uninstall_startup_)>(FindControl(L"171E129508A9"));
	btn_uninstall_cancel_->AttachClick(nbase::Bind(&Installer::OnBtnUninstallCancel, this, std::placeholders::_1));
	btn_uninstall_startup_->AttachClick(nbase::Bind(&Installer::OnBtnUninstallStartup, this, std::placeholders::_1));
	//////Install///////////////////////////////////////////////////////////////////////////////////////////////////////
	checkbox_poweron_ = dynamic_cast<decltype(checkbox_poweron_)>(FindControl(L"10B20870BECC"));
	checkbox_startup_ = dynamic_cast<decltype(checkbox_startup_)>(FindControl(L"D5CCAE68E612"));
	checkbox_dsklnk_ = dynamic_cast<decltype(checkbox_dsklnk_)>(FindControl(L"381708398D6C"));
	btn_select_folder_ = dynamic_cast<decltype(btn_select_folder_)>(FindControl(L"00891DC7AC71"));
	edit_install_path_ = dynamic_cast<decltype(edit_install_path_)>(FindControl(L"203DF43449B5"));
	//edit_install_path_->SetText(Global::Get()->GetProductInstallDir());
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
	btn_install_finished_->AttachClick(nbase::Bind(&Installer::OnBtnInstallFinished, this, std::placeholders::_1));
	btn_install_startup_->AttachClick(nbase::Bind(&Installer::OnBtnInstallStartup, this, std::placeholders::_1));
	btn_system_close_->AttachClick(nbase::Bind(&Installer::OnBtnSystemClose, this, std::placeholders::_1));
	checkbox_seldir_->AttachAllEvents(nbase::Bind(&Installer::OnCheckBoxEvent, this, std::placeholders::_1));
	checkbox_agree_protocol_->AttachAllEvents(nbase::Bind(&Installer::OnCheckBoxEvent, this, std::placeholders::_1));
	btn_service_protocol_->AttachClick(nbase::Bind(&Installer::OnBtnServiceProtocol, this, std::placeholders::_1));
	btn_privacy_agreement_->AttachClick(nbase::Bind(&Installer::OnBtnServiceProtocol, this, std::placeholders::_1));
	if (btn_select_folder_)
		btn_select_folder_->AttachClick(nbase::Bind(&Installer::OnBtnSelectInstallDir, this, std::placeholders::_1));
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
		selPath = stl::Path::Normalize(selPath + L"/MarsProjects");
		edit_install_path_->SetText(selPath);
	}
	return true;
}
bool Installer::OnBtnServiceProtocol(EventArgs* args) {
	//nim_comp::WindowsManager::SingletonShow<AboutServiceProtocol>(AboutServiceProtocol::kClassName);
	std::string content = stl::File::ReadFile(Global::Get()->GetProductServiceProtocol());
	std::wstring wcontent = shared::IConv::UTF8ToWString(content);
	edit_service_protocol_->SetText(test_content);
	edit_service_protocol_->SetFocus();
	edit_service_protocol_->HomeUp();
	tabbox_root_->SelectItem(PageType::Protocol);
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


	} while (0);
}
void Installer::InstallProc() {
	do {
		const auto status = UIFrame::Get()->ProcessStatusGet();
		if(ProcessType::Install == Global::Get()->GetInstallerProcessType()){
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
				//!@ 安装完成后 生成安装信息
#if 0
				if (!wcsicmp(L"nsisSetInstallDir", fun_name)) {
					Global::Get()->SetProductInstallDir(value);
				}
				else if (!wcsicmp(L"nsisSetProgramMain", fun_name)) {
					Global::Get()->SetProductProgramMain(value);
				}

				do {
					const std::wstring installerDir = stl::Path::Normalize(Global::Get()->GetProductInstallDir() + L"/installer");
					stl::Directory::Create(installerDir);
					if (!stl::Directory::ExistsW(installerDir))
						break;
					const std::wstring installer_config = stl::Path::Normalize(installerDir + L"/installer.json");
					rapidjson::Document doc(rapidjson::Type::kObjectType);
					doc.AddMember(rapidjson::Value().SetString("", doc.GetAllocator()).Move(),
						rapidjson::Value().SetString("", doc.GetAllocator()).Move(),
						doc.GetAllocator());
				} while (0);
#endif
				tabbox_root_->SelectItem(PageType::Finished);
				progress_control_->SetVisible(false);
				break;
			}
		}
		else if (ProcessType::Uninstall == Global::Get()->GetInstallerProcessType()) {
			if (ProcessStatus::Readyed == status) {
				UIFrame::Get()->ProcessStatusSet(ProcessStatus::Installing);
#if _DEBUG
				UIFrame::Get()->ProcessStatusSet(ProcessStatus::Installed);
#else
				shared::Win::EmptyFolderW(Global::Get()->GetProductInstallDir(),
					[&](const auto& total, const auto& current) {
						if (current > 0 && total>0) {
							UIFrame::Get()->nsis_install_progress_.push(std::make_tuple(current, total));
						}
					}, true, true);
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
				UIFrame::Get()->ProcessStatusSet(ui::ProcessStatus::Installed);
#endif
			}
			else if (ProcessStatus::Installed == status) {
				progress_->SetValue(progress_->GetMaxValue());
				label_goodbye_->SetText(L"感谢使用扇子办公宝，期待下次美好的相遇！");
				progress_control_->SetVisible(false);
				break;
			}

		}
		if (!open_.load())
			break;
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	} while (1);
}
bool Installer::OnBtnInstallFinished(EventArgs* args) {
#if 0
	checkbox_poweron_ = dynamic_cast<decltype(checkbox_poweron_)>(FindControl(L"10B20870BECC"));
	checkbox_startup_ = dynamic_cast<decltype(checkbox_startup_)>(FindControl(L"D5CCAE68E612"));
	checkbox_dsklnk_ = dynamic_cast<decltype(checkbox_dsklnk_)>(FindControl(L"381708398D6C"));
#endif
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
	UIFrame::Get()->ProcessStatusSet(ProcessStatus::Readyed);
	tabbox_root_->SelectItem(PageType::Total);
	progress_control_->SetVisible(true);
#if 0
	//args->pSender->SetEnabled(false);
	//int total = tabbox_root_->GetCount();
	//tabbox_root_->SelectItem(1);
	//StdClosure task = nbase::Bind(&Install::OnSwitchSlogan, this);
	nbase::ThreadManager::PostRepeatedTask(kThreadGlobalMisc, slogan_timer_.ToWeakCallback([this]() {
		//nbase::TimeDelta time_delta = nbase::TimeDelta::FromMicroseconds(nbase::Time::Now().ToInternalValue());
		nbase::ThreadManager::PostTask(kThreadUI, nbase::Bind(&Install::OnSwitchSlogan, this));
		}),
		nbase::TimeDelta::FromMilliseconds(SWITCH_SLOGAN_INTERVAL));

	//nbase::ThreadManager::PostRepeatedTask(kThreadGlobalMisc, ToWeakCallback([this]() {
	//	//nbase::TimeDelta time_delta = nbase::TimeDelta::FromMicroseconds(nbase::Time::Now().ToInternalValue());
	//	//nbase::ThreadManager::PostTask(kThreadUI, nbase::Bind(&Install::OnSwitchSlogan, this));
	//	}), nbase::TimeDelta::FromMilliseconds(SWITCH_SLOGAN_INTERVAL));
#endif
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
	//!@ 隐藏俩按钮
	btn_uninstall_cancel_->SetVisible(false);
	btn_uninstall_startup_->SetVisible(false);
	//!@ 显示进度条
	progress_control_->SetVisible(true);
	shared::Win::Process::TerminateOnDirectory(Global::Get()->GetProductInstallDir());
	UIFrame::Get()->ProcessStatusSet(ui::ProcessStatus::Readyed);
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