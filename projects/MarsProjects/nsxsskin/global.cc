#include "stdafx.h"

const UINT UI_NOTIFY_MESSAGE_BOX = RegisterWindowMessageW(L"UI_NOTIFY_MESSAGE_BOX");
const wchar_t kClassNameInstaller[] = L"XSMarsProjectsInstall";
const wchar_t kClassNameUninstall[] = L"XSMarsProjectsUninstall";
const wchar_t kClassNameAboutServiceProtocol[] = L"XSMarsProjectsAboutServiceProtocol";
HINSTANCE g_hInstance = nullptr;
HWND g_hwndParent = nullptr;
stl::Signal* gpSignalSystemExit = nullptr;
extra_parameters* nsis_extra_parameters = nullptr;

void Global::SetProductName(const std::wstring& value) {
	std::lock_guard<std::mutex> lock{ *mtx_ };
	product_name_ = value;
}
const std::wstring& Global::GetProductName() const {
	std::lock_guard<std::mutex> lock{ *mtx_ };
	return product_name_;
}
void Global::SetProductServiceProtocol(const std::wstring& value) {
	std::lock_guard<std::mutex> lock{ *mtx_ };
	product_service_protocol_ = value;
}
const std::wstring& Global::GetProductServiceProtocol() const {
	std::lock_guard<std::mutex> lock{ *mtx_ };
	return product_service_protocol_;
}
void Global::SetProductInstallDir(const std::wstring& value) {
	std::lock_guard<std::mutex> lock{ *mtx_ };
	product_install_dir_ = value;
}
const std::wstring& Global::GetProductInstallDir() const {
	std::lock_guard<std::mutex> lock{ *mtx_ };
	return product_install_dir_;
}
void Global::SetProductProgramMain(const std::wstring& value) {
	std::lock_guard<std::mutex> lock{ *mtx_ };
	product_program_main_ = value;
}
const std::wstring& Global::GetProductProgramMain() const {
	std::lock_guard<std::mutex> lock{ *mtx_ };
	return product_program_main_;
}
void Global::SetProductLicenceFilename(const std::wstring& value) {
	std::lock_guard<std::mutex> lock{ *mtx_ };
	product_licence_filename_ = value;
}
const std::wstring& Global::GetProductLicenceFilename() const {
	std::lock_guard<std::mutex> lock{ *mtx_ };
	return product_licence_filename_;
}
void Global::SetSkinDir(const std::wstring& value) {
	std::lock_guard<std::mutex> lock{ *mtx_ };
	skin_dir_ = value;
}
const std::wstring& Global::GetSkinDir() const {
	std::lock_guard<std::mutex> lock{ *mtx_ };
	return skin_dir_;
}
const ProcessType& Global::GetInstallerProcessType() const{
	std::lock_guard<std::mutex> lock{ *mtx_ };
	return installer_process_type_;
}
void Global::SetInstallerProcessType(const ProcessType& type){
	std::lock_guard<std::mutex> lock{ *mtx_ };
	installer_process_type_ = type;
}
void Global::SetProductVersion(const std::wstring& ver){
	std::lock_guard<std::mutex> lock{ *mtx_ };
	product_version_ = ver;
}
const std::wstring& Global::GetProductVersion() const{
	std::lock_guard<std::mutex> lock{ *mtx_ };
	return product_version_;
}
const std::vector<std::wstring>& Global::GetRMDirs() const{
	std::lock_guard<std::mutex> lock{ *mtx_ };
	return rmdirs_;
}
void Global::SetRMDirs(const std::wstring& str){
	std::lock_guard<std::mutex> lock{ *mtx_ };
	rmdirs_ = stl::String::WStringSplit(str, L",");
}
/////////////////////////////////////////////////////////////////////////////////////////////

Global::Global() {
	product_install_dir_ = shared::Win::SHGetKnownFolderPathW(FOLDERID_RoamingAppData);
	product_install_dir_ = shared::Win::PathFixedW(product_install_dir_ + L"\\MarsProjects\\");
}
Global::~Global() {
}
static Global* __gspGlobal = nullptr;
Global* Global::Get() {
	if (!__gspGlobal)
		__gspGlobal = new Global();
	return __gspGlobal;
}
void Global::Destroy() {
	SK_DELETE_PTR(__gspGlobal);
}
