#if !defined(__8D98C607_F1D9_4856_98EA_6039F1B3FEDA__)
#define __8D98C607_F1D9_4856_98EA_6039F1B3FEDA__

#include "interface.h"

namespace wxui {
	enum class FrameType : long {
		SDI = 0,
		MDI = 1,
	};

	enum class WindowStyle : long {
	
	};

	class IWindow {
	public:
		virtual void SetIcon(const char*, const size_t&) = 0;
		virtual void SetStyle(const long&) = 0;
		virtual const long& GetStyle() const = 0;
		virtual void Show(const bool&) const = 0;
		virtual void* GetHwnd() const = 0;
		virtual void Center() const = 0;
		virtual void SetSize(const int& cx, const int& cy) const = 0;
		virtual void SetPos(const int& x, const int& y) const = 0;
		virtual void SetTitle(const wchar_t*) const = 0;
	};
	class IMDIChild : public IWindow {
	public:

	};

	class IFrame : public IWindow {
	public:
		virtual const FrameType& GetType() const = 0;
		virtual IMDIChild* CreateMDIChild() const { return nullptr; }
	};

	class IWxui : public Interface<IWxui> {
	public:
		typedef void(*tfCreateChildCb)(void* hwnd, void* route);
		typedef void(*tfCreateFrameCb)(IFrame* frame, void* route);
		typedef void(*tfDestroyFrameCb)(IFrame* frame, void* route);
		typedef void(*tfSystemExitCb)(int rc,void* route);
		class IConfig {
		public:
			virtual void SetFrameType(const FrameType&) = 0;
			virtual void 	EnableAuiManager(const bool&) = 0;
			virtual void RegisterCreateFrameCb(const tfCreateFrameCb&,void*) = 0;
			virtual void RegisterDestroyFrameCb(const tfDestroyFrameCb&, void*) = 0;
			virtual void RegisterCreateChildCb(const tfCreateChildCb&, void*) = 0;
			virtual void RegisterSystemExitCb(const tfSystemExitCb&, void*) = 0;
		};
	public:
		virtual IConfig* ConfigGet() const = 0;
		virtual bool Ready() const = 0;
		virtual void Release() const = 0;
		virtual bool Start() = 0;
		virtual void Stop() = 0;
		virtual void Perform() = 0;
		virtual IFrame* CreateFrame(const FrameType&) = 0;
	};




} // namespace wxui

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 29 Sep 2024 13:32:47 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__8D98C607_F1D9_4856_98EA_6039F1B3FEDA__
