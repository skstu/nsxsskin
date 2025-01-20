#include "stdafx.h"

Window::Window() {
}

Window::~Window() {
}
std::wstring Window::GetSkinFolder() {
	return L"installer";
}
std::wstring Window::GetSkinFile() {
	return L"installer.xml";
}
std::wstring Window::GetWindowClassName() const {
	return kClassName;
}
void Window::InitWindow() {
	SetIcon(IDI_MAIN);
	hwnd_ = GetHWND();
	AddMessageFilter(this);
	label_install_tip_ = dynamic_cast<ui::Label*>(FindControl(L"0C257D26A627"));
	btn_system_close_ = dynamic_cast<ui::Button*>(FindControl(L"0BA894CC18C3"));
	btn_system_close_->AttachClick(nbase::Bind(&Window::OnBtnSystemClose, this, std::placeholders::_1));
	homepage_tab_box_ = dynamic_cast<ui::TabBox*>(FindControl(L"66EAA910"));
	install_progress_down_ = dynamic_cast<ui::Progress*>(FindControl(L"7DEBFEA26674"));
	label_down_percentage_ = dynamic_cast<ui::Label*>(FindControl(L"ADE6E3352974"));
	install_progress_down_->AttachAllEvents(
		[](ui::EventArgs* args)->bool {
			if (args->Type == ui::EventType::kEventNotify) {
				//((ui::Progress*)args->pSender)->SetValue(0);
			}
			return true;
		});
	/* Post repeat task to update progress value 200 milliseconds once */
/* Using ToWeakCallback to protect closure when if [ControlForm] was destoryed */
	nbase::ThreadManager::PostRepeatedTask(kThreadGlobalMisc, ToWeakCallback([this]() {
		//nbase::TimeDelta time_delta = nbase::TimeDelta::FromMicroseconds(nbase::Time::Now().ToInternalValue());
		nbase::ThreadManager::PostTask(kThreadUI, nbase::Bind(&Window::OnSwitchSlogan, this));
		}), nbase::TimeDelta::FromMilliseconds(HOMEPAGE_SWITCH_SLOGAN_INTERVAL));
	nbase::ThreadManager::PostRepeatedTask(kThreadGlobalMisc, ToWeakCallback([this]() {
		//nbase::TimeDelta time_delta = nbase::TimeDelta::FromMicroseconds(nbase::Time::Now().ToInternalValue());
		nbase::ThreadManager::PostTask(kThreadUI, nbase::Bind(&Window::OnInstallPackage, this));
		}), nbase::TimeDelta::FromMilliseconds(200));
	open_.store(true);
	threads_.emplace_back([this]() {InstallProc(); });
}
LRESULT Window::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	open_.store(false);
	for (auto& t : threads_)
		t.join();
	threads_.clear();
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}
LRESULT Window::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	if (uMsg == NOTIFY_DOWNLOAD_PROGRESS) {
		long current = LOWORD(lParam);
		long total = HIWORD(lParam);

		install_progress_current_ += current;

		//nbase::ThreadManager::PostTask(kThreadUI, nbase::Bind(&Window::OnInstallPackage, this));
		//SetInstallProgress
		//nbase::ThreadManager::PostTask(kThreadUI, nbase::Bind(&Window::SetInstallProgress, this,total, install_progress_current_.load()));
		DWORD pid = static_cast<DWORD>(wParam);
		bHandled = TRUE;
	}
	return __super::MessageHandler(uMsg, wParam, lParam, bHandled);
}
void Window::OnSwitchSlogan() const {
	do {
		if (!homepage_tab_box_)
			break;
		const auto count = homepage_tab_box_->GetCount();
		if (count <= 1)
			break;
		const auto cur = homepage_tab_box_->GetCurSel();
		homepage_tab_box_->SelectItem((cur < count - 1) ? (cur + 1) : 0);
	} while (0);
}
void Window::OnInstallPackage() {
	ui::Progress* _this = install_progress_down_;

	do {
		if (!_this ||
			install_progress_total_.load() <= 0 ||
			install_progress_current_.load() <= 0) {
			_this->SetValue(0);
			break;
		}
		double r = (install_progress_current_.load() * 1.0) / (install_progress_total_.load() * 1.0);
		if (label_down_percentage_) {
			label_down_percentage_->SetText(stl::Conv::U8StringToWString(fmt::format("{:.2f}", r * 100.0)).c_str());
		}
		_this->SetValue(static_cast<double>(_this->GetMaxValue() * r));
	} while (0);
}
bool Window::OnBtnSystemClose(ui::EventArgs* args) {
	nim_comp::ShowMsgBox(GetHWND(),
		[&](nim_comp::MsgBoxRet ret) {
			if (ret == nim_comp::MB_YES) {
				//std::exit(-1);
				force_close_.store(true);
				Window::Close();
			}
		},
		L"确定退出安装吗？", false, L"火星办公", false, L"是", false, L"否", false);
	return true;
}

void Window::InstallProc() {
	const chromium::Installer& installerObj = Config::Get()->GetInstaller();

	std::wstring root = installerObj.root_;
	std::wstring f7za, fLuanch, fPerform;
	do {//!@ 释放依赖项
		const std::wstring deps = shared::Win::PathFixedW(installerObj.root_ + L"\\");
		shared::Win::CreateDirectoryW(deps);
		std::string buffer_7za = shared::Win::Resource::Load(GetModuleHandleW(NULL), IDR_7ZA, "DLL");
		f7za = shared::Win::PathFixedW(deps + L"\\7za.dll");
		stl::File::WriteFile(f7za, buffer_7za);
	} while (0);

	do {
		if (!shared::Win::AccessW(f7za))
			break;
		if (installerObj.items_.empty())
			break;
		//!@ 正在准备 . . . 
		//! 
		//! 
		size_t items_total = Config::Get()->GetInstaller().GetItemsTotal(
			[&](const chromium::Installer::Item& item) -> size_t {
				size_t result = 0;
				do {
					if (item.from.empty())
						break;
					httpparser::HttpUrlFields urlfield;
					if (!httpparser::Method::parse_http_url(shared::IConv::WStringToUTF8(item.from), urlfield))
						break;
					std::string url_host = urlfield[httpparser::EnHttpUrlFieldType::UF_HOST];
					std::string url_path = urlfield[httpparser::EnHttpUrlFieldType::UF_PATH];
					int url_port = atoi(urlfield[httpparser::EnHttpUrlFieldType::UF_PORT].c_str());
					if (!url_port)
						url_port = 80;
					try {
						httplib::Client cli(url_host, url_port);
						auto res = cli.Head(url_path);
						if (res && res->status == 200) {
							auto it = res->headers.find("Content-Length");
							if (it != res->headers.end()) {
								result += std::stoull(it->second);
							}
						}
					}
					catch (const std::exception& e) {
						std::cerr << "HTTP request failed: " << e.what() << std::endl;
					}
				} while (0);
				return result;
			});

		Config::Get()->UpdateInstallerTotal(items_total);

		const size_t total = installerObj.total_;
		install_progress_total_.store(total);
		root = installerObj.root_;
		size_t download_total = 0;

		for (const auto& item : installerObj.items_) {
			httpparser::HttpUrlFields urlfield;
			if (!httpparser::Method::parse_http_url(shared::IConv::WStringToUTF8(item.from), urlfield))
				break;
			std::string url_host = urlfield[httpparser::EnHttpUrlFieldType::UF_HOST];
			std::string url_path = urlfield[httpparser::EnHttpUrlFieldType::UF_PATH];
			int url_port = atoi(urlfield[httpparser::EnHttpUrlFieldType::UF_PORT].c_str());
			if (!url_port)
				url_port = 80;

			httplib::Client cli(url_host, url_port);
			std::string body;
			uint64_t current_prev = 0;
			auto res = cli.Get(url_path, httplib::Headers(),
				[&](const httplib::Response& response) {
					//EXPECT_EQ(StatusCode::OK_200, response.status);
					return true; // return 'false' if you want to cancel the request.
				},
				[&](const char* data, size_t data_length) {
					body.append(data, data_length);
					return true; // return 'false' if you want to cancel the request.
				},
				[&](uint64_t current, uint64_t total)->bool {
					install_progress_current_ += (current - current_prev);
					download_total += (current - current_prev);
					current_prev = current;
					return !force_close_.load();
				});

			if (res && res->status == httplib::StatusCode::OK_200) {
				shared::Win::CreateDirectoryW(shared::Win::GetPathByPathnameW(item.to));
				stl::File::WriteFile(item.to, body);
			}
		}

		do {
			bool success = download_total == total;
			for (const auto& item : installerObj.items_) {
				if (!shared::Win::AccessW(item.to)) {
					success = false;
					break;
				}
			}
			if (success || force_close_.load())
				break;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		} while (1);

		do {//!@ 安装之前需要清理的目录
#if 0
			do {//!@ 准备环境
				std::set<std::wstring> clean_proc_name_s;
				for (const auto& name : Config::Get()->GetInstaller().clean_.pros) {
					clean_proc_name_s.emplace(name.name);
				}
				if (clean_proc_name_s.empty())
					break;
				std::set<DWORD> kills;

				shared::Win::Process::Enum([&](
					const HANDLE& handle,
					const HANDLE& handle_token,
					const DWORD& pid,
					const std::string& account,
					const std::string& domain,
					const std::string& image,
					const std::string& image_path,
					bool& __break) {
						do {
							if (image_path.empty() || image.empty() || pid <= 4)
								break;
							if (clean_proc_name_s.find(shared::IConv::UTF8ToWString(image)) != clean_proc_name_s.end()) {
								kills.emplace(pid);
							}
						} while (0);
					});

				if (kills.empty())
					break;
				for (const auto& k : kills) {
					shared::Win::Process::Terminate(k);
				}

			} while (0);
#endif

			std::wstring ready_root = stl::String::LowerW(installerObj.root_);
			for (auto it = ready_root.begin(); it != ready_root.end();) {
				if (*it == L'\\' || *it == '/')
					it = ready_root.erase(it);
				else
					++it;
			}

			if (installerObj.clean_.pros_clear_all || !installerObj.clean_.pros.empty()) {
				shared::Win::Process::Enum([&](
					const HANDLE& handle,
					const HANDLE& handle_token,
					const DWORD& pid,
					const std::string& account,
					const std::string& domain,
					const std::string& image,
					const std::string& image_path,
					bool& __break) {
						do {
							if (image_path.empty() || image.empty() || pid <= 4)
								break;

							std::wstring dir = stl::Path::PathnameToPath(shared::IConv::UTF8ToWString(image_path));
							dir = stl::String::LowerW(dir);
							for (auto it = dir.begin(); it != dir.end();) {
								if (*it == L'\\' || *it == '/')
									it = dir.erase(it);
								else
									++it;
							}
							if (dir.find(ready_root) == std::string::npos)
								break;
							shared::Win::Process::Terminate(pid);
						} while (0);
					});
			}
			for (const auto& file : installerObj.clean_.files) {//!@ 清理文件
				if (!stl::File::Exists(file.path))
					continue;
				stl::File::Remove(file.path);
			}
			for (const auto& dir : installerObj.clean_.dirs) {//!@ 清理目录
				if (!stl::Directory::ExistsW(dir.path))
					continue;
				stl::Directory::RemoveAllW(dir.path);
				auto sss = 0;
			}
		} while (0);

		do {//!@ final install
			if (force_close_.load())
				break;
			if (installerObj.items_.empty())
				break;
			for (const auto& item : installerObj.items_) {
				auto signal = new stl::Signal();
				nbase::ThreadManager::PostTask(kThreadUI,
					[this, signal]() {
						label_install_tip_->SetText(L"正在安装...");
						install_progress_down_->SetValue(0);
						signal->notify();
					});
				signal->wait_for_event(std::chrono::milliseconds(0));
				SK_RELEASE_PTR(signal);
				//install_progress_->SetValue(0.0);
				//SendNotify(install_progress_,ui::EventType::kEventNotify, 666, 999);
				std::string pak = stl::File::ReadFile(item.to);
				if (pak.empty())
					continue;
				if (shared::FileType::_7Z != shared::Win::GetFileTypeByMemory(pak))
					continue;
				//!@ 注意平铺
				//! 
				//! 
				Zipcc::bit7zUnCompress(shared::IConv::WStringToUTF8(f7za), pak,
					shared::Win::GetPathByPathnameA(shared::IConv::WStringToUTF8(item.to)),
					[](size_t total, size_t current, void* route)->bool {
						((Window*)route)->install_progress_total_.store(total);
						((Window*)route)->install_progress_current_.store(current);
						return !((Window*)route)->force_close_.load();
					}, this);

				stl::File::Remove(item.to);
			}

			for (auto& s : installerObj.shortcuts_) {
				if (!s.enable)
					continue;
				shared::Win::CreateShortcutW(s.src, s.dst, s.logo);
			}

			for (auto& p : installerObj.starts_) {
				if (!p.enable)
					continue;
				DWORD createPid = 0;
				shared::Win::Process::CreateW(p.path, p.args, createPid, false, true, 0);
			}
#if !_DEBUG
			std::exit(666);
#endif
			std::this_thread::sleep_for(std::chrono::seconds(3));
			PostMessageW(WM_CLOSE, 0, 0);
		} while (0);

	} while (0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
const wchar_t kClassName[] = L"XSInstallProgram";
const UINT NOTIFY_DOWNLOAD_PROGRESS = RegisterWindowMessageW(L"NOTIFY_DOWNLOAD_PROGRESS");
//const std::string install_package = shared::Win::Resource::Load(GetModuleHandleW(NULL), IDR_PACKAGE, "PACKAGE");