#ifndef __IMODULE_H__
#define __IMODULE_H__

#include "interface.h"

class IModule : public Interface<IModule> {
protected:
	using tfSystemExitCb = void(*)(void);
	using tfOnResponseCb = void(*)(const char*, size_t, void*);
public:
	class IConfig {
	public:
		virtual bool FromJson(const char*, const size_t&) { return false; }
		virtual void SetModulePathname(const char*) { return; }
		virtual const char* GetModulePathname() const { return nullptr; }
	};
public:
	template<typename T>
	inline T* To() const {
		return dynamic_cast<T*>(const_cast<IModule*>(this));
	}
	template<typename T>
	inline auto ToConfig() const {
		return dynamic_cast<T::IConfig*>(ConfigGet());
	}
	virtual void Free(void**) const { return; }
	virtual bool Start() { return false; }
	virtual void Stop() { return; }
	virtual void Perform() { return; }
	virtual bool Ready() const { return false; }
	virtual void Release() const { return; }
	virtual IConfig* ConfigGet() const { return nullptr; }
	virtual void RegisterSystemExitCb(const tfSystemExitCb&) { return; }
	virtual void RegisterOnResponse(const tfOnResponseCb&) { return; }
	virtual bool Request(const char*, size_t, char**, size_t*) { return false; }
	virtual IModule* GetModule(const char* module_key) const { return nullptr; }
};


#endif //__IMODULE_H__