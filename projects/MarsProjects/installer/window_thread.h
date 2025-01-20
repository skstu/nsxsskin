#if !defined(__6E8E3879_6613_4A27_8F97_2DF2923EEFDB__)
#define __6E8E3879_6613_4A27_8F97_2DF2923EEFDB__

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

class WindowThread : public nbase::FrameworkThread
{
public:
	WindowThread();
	virtual ~WindowThread();

private:
	virtual void Init() override;
	virtual void Cleanup() override;
private:
	std::unique_ptr<MiscThread>	misc_thread_;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 13 Oct 2024 11:11:26 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__6E8E3879_6613_4A27_8F97_2DF2923EEFDB__

