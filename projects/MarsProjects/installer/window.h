#if !defined(__423F9751_F2F7_498F_B6E9_E43369DD0B1E__)
#define __423F9751_F2F7_498F_B6E9_E43369DD0B1E__

class Window : public ui::WindowImplBase {
public:
	Window();
	virtual ~Window();
protected:
	std::wstring GetSkinFolder() override final;
	std::wstring GetSkinFile() override final;
	std::wstring GetWindowClassName() const override final;
	void InitWindow() override final;
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
private:
	void OnSwitchSlogan() const;
	void OnInstallPackage();
	bool OnBtnSystemClose(ui::EventArgs*);
	HWND hwnd_ = nullptr;
	ui::TabBox* homepage_tab_box_ = nullptr;
	ui::Progress* install_progress_down_ = nullptr;
	ui::Button* btn_system_close_ = nullptr;
	ui::Label* label_install_tip_ = nullptr;
	ui::Label* label_down_percentage_ = nullptr;
	stl::Threads threads_;
	std::atomic_bool open_ = false;
	std::atomic_bool force_close_ = false;
	void InstallProc();
	std::vector<DWORD> performs_;
	std::atomic_uint64_t install_progress_total_ = 0;
	std::atomic_uint64_t install_progress_current_ = 0;
	stl::container::queue<std::tuple<size_t/*total*/, size_t/*current*/>> install_progress_observe_;
};

extern const wchar_t kClassName[];
extern const UINT NOTIFY_DOWNLOAD_PROGRESS; 
//extern const std::string install_package;
/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 13 Oct 2024 11:05:08 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__423F9751_F2F7_498F_B6E9_E43369DD0B1E__