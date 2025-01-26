#if !defined(__729B6A78_384B_4471_A0D7_050524336A2A__)
#define __729B6A78_384B_4471_A0D7_050524336A2A__
constexpr time_t SWITCH_SLOGAN_INTERVAL = 1000 * 2;
constexpr time_t INSTALL_PROGRESS_INTERVAL = static_cast<time_t>(1000 / 10);

namespace ui {
	enum ProcessStatus {
		Unknown = 0,
		Readyed = 1,
		Installing = 2,
		Installed = 3,
		InstallFailed = 4,
	};
	enum PageType {
	First = 0,
	Finished = 1,
	Uninstall = 2,
	Protocol = 3,

	Total = 4,
	};
	enum ThreadId
	{
		kThreadUI,
		kThreadGlobalMisc
	};

	class MiscThread : public nbase::FrameworkThread
	{
	public:
		MiscThread(enum ThreadId thread_id, const char* name)
			: FrameworkThread(name)
			, thread_id_(thread_id) {

		}
		~MiscThread(void) {

		}
	private:
		virtual void Init() override {
			nbase::ThreadManager::RegisterThread(thread_id_);
		}
		virtual void Cleanup() override {
			nbase::ThreadManager::UnregisterThread();
		}
	private:
		enum ThreadId thread_id_;
	};

	class AboutServiceProtocol : public ui::WindowImplBase
	{
	public:
		AboutServiceProtocol();
		~AboutServiceProtocol();
	protected:
		virtual std::wstring GetSkinFolder() override;
		virtual std::wstring GetSkinFile() override;
		virtual std::wstring GetWindowClassName() const override;
		virtual void InitWindow() override;
	public:
		static const LPCTSTR kClassName;
	};

	class Installer : public ui::WindowImplBase {
	public:
		Installer(const ProcessType&);
		virtual ~Installer();
	protected:
		std::wstring GetSkinFolder() override final;
		std::wstring GetSkinFile() override final;
		std::wstring GetWindowClassName() const override final;
		void InitWindow() override final;
		LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
		LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	public:
		std::wstring GetInstallDir() const;
	private:
		bool OnCheckBoxEvent(EventArgs*);
		bool OnBtnSystemClose(EventArgs*);
		bool OnBtnInstallStartup(EventArgs*);
		void OnSwitchSlogan() const;
		void OnInstallProgress();
		bool OnBtnInstallFinished(EventArgs*);
		bool OnBtnServiceProtocol(EventArgs*);
		bool OnBtnSelectInstallDir(EventArgs*);
		bool OnBtnUninstallStartup(EventArgs*);
		bool OnBtnUninstallCancel(EventArgs*);
	private:
		CheckBox* checkbox_poweron_ = nullptr;
		CheckBox* checkbox_startup_ = nullptr;
		CheckBox* checkbox_dsklnk_ = nullptr;
		CheckBox* checkbox_seldir_ = nullptr;
		CheckBox* checkbox_agree_protocol_ = nullptr;
		Button* btn_system_close_ = nullptr;
		Button* btn_install_startup_ = nullptr;
		TabBox* tabbox_root_ = nullptr;
		nbase::WeakCallbackFlag slogan_timer_;
		Progress* progress_ = nullptr;
		Label* progress_text_ = nullptr;
		VBox* progress_control_ = nullptr;
		Label* progress_percentage_ = nullptr;
		Button* btn_install_finished_ = nullptr;
		//Button* btn_license_ = nullptr;
		Button* btn_privacy_agreement_ = nullptr;
		Button* btn_service_protocol_ = nullptr;
		Button* btn_select_folder_ = nullptr;
		stl::tfThreads threads_;
		RichEdit* edit_install_path_ = nullptr;
		RichEdit* edit_service_protocol_ = nullptr;
		Button* btn_uninstall_cancel_ = nullptr;
		Button* btn_uninstall_startup_ = nullptr;
		Label* label_goodbye_ = nullptr;
		std::atomic_bool open_ = false;
		void InstallProc();
		void NotifyMessageProc();
		const ProcessType process_type_;
	};

	class UIFrame final : public  nbase::FrameworkThread {
	public:
		static UIFrame* Get();
		static void Destroy();
	private:
		UIFrame();
		~UIFrame();
	private:
		void Init() override final;
		void Cleanup() override final;
		std::unique_ptr<MiscThread>	misc_thread_;
	public:
		bool Start();
		void Stop();
		void ProcessStatusSet(const ProcessStatus&);
		ProcessStatus ProcessStatusGet() const;
		std::wstring GetInstallDir() const;
		Installer* GetInstaller() const {
			return installer_;
		}
	private:
		std::atomic_bool open_ = false;
		stl::tfThreads threads_;
		void Process();
	public:
		stl::container::map<std::wstring, INT_PTR> nsiscbs_;
		stl::container::queue<std::tuple<std::uint64_t/*current*/, std::uint64_t/*total*/>> nsis_install_progress_;
		stl::container::queue<std::wstring> notify_message_;
	private:
		std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
		ProcessStatus process_status_ = ProcessStatus::Unknown;
		Installer* installer_ = nullptr;
	};
}///namespace ui

/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 20 Jan 2025 09:09:03 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__729B6A78_384B_4471_A0D7_050524336A2A__
