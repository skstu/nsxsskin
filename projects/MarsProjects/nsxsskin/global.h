#if !defined(__63307A18_48E0_4CB6_9D82_985D734EBA2E__)
#define __63307A18_48E0_4CB6_9D82_985D734EBA2E__

extern HINSTANCE g_hInstance;
extern HWND g_hwndParent;
extern const wchar_t kClassNameInstaller[];
extern const wchar_t kClassNameUninstall[];
extern const wchar_t kClassNameAboutServiceProtocol[];
extern stl::Signal* gpSignalSystemExit;
extern extra_parameters* nsis_extra_parameters;
extern const UINT UI_NOTIFY_MESSAGE_BOX;// WM_USER + 1000
#define NSIS_INIT_EXTRA_PARAMETERS(p) \
do{\
if (!nsis_extra_parameters)\
nsis_extra_parameters = p;\
} while (0);\

enum class ProcessType : UINT {
	Install = 0,
	Uninstall = 1,
};

class Global final{
public:
	static Global* Get();
	static void Destroy();
private:
	Global();
	~Global();
public:
	void SetProductName(const std::wstring&);
	const std::wstring& GetProductName() const;
	void SetProductServiceProtocol(const std::wstring&);
	const std::wstring& GetProductServiceProtocol() const;
	void SetProductInstallDir(const std::wstring&);
	const std::wstring& GetProductInstallDir() const;
	void SetProductProgramMain(const std::wstring&);
	const std::wstring& GetProductProgramMain() const;
	void SetProductLicenceFilename(const std::wstring&);
	const std::wstring& GetProductLicenceFilename() const;
	void SetSkinDir(const std::wstring&);
	const std::wstring& GetSkinDir() const;
	const ProcessType& GetInstallerProcessType() const;
	void SetInstallerProcessType(const ProcessType&);
	void SetProductVersion(const std::wstring&);
	const std::wstring& GetProductVersion() const;
	const std::vector<std::wstring>& GetRMDirs() const;
	void SetRMDirs(const std::wstring&);
private:
	std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
	std::wstring product_name_;
	std::wstring product_install_dir_;
	std::wstring product_service_protocol_;
	std::wstring product_program_main_;
	std::wstring product_licence_filename_;
	std::wstring product_version_ = L"1.0.0.1";
	std::wstring skin_dir_;
	std::vector<std::wstring> rmdirs_;
	ProcessType installer_process_type_ = ProcessType::Install;
};

extern Global* __gspGlobal;
/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 20 Jan 2025 08:04:30 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__63307A18_48E0_4CB6_9D82_985D734EBA2E__