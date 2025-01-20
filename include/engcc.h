#if !defined(__34591E11_2706_403E_9EAC_6C87D607B16F__)
#define __34591E11_2706_403E_9EAC_6C87D607B16F__

#include "module.h"

namespace engcc {

	class IEngcc : public IModule {
	public:
		class IBuffer {
		public:
			virtual void Release() const = 0;
			virtual void Set(const void*, const size_t&) = 0;
			virtual bool Get(char**, size_t*) const = 0;
			virtual bool Empty() const = 0;
			virtual const void* Begin() const = 0;
			virtual size_t Size() const = 0;
		};
		class ISource {
		public:
			virtual void Release() const = 0;
		};
		class IBitcode {
		public:
			virtual void Release() const = 0;
		};
		class IDiagnostic {
		public:
			virtual const char* GetDiagnosticString() const = 0;
			virtual bool GetDiagnosticOutput(char**, size_t*) const = 0;
		};
		class IConfig : public IModule::IConfig {
		public:
			virtual void SetCompileArgs(const IBuffer*) = 0;
			virtual void GetCompileArgs(IBuffer**) const = 0;
			virtual void Append_internal_isystem(const char*) = 0;
		};

	public:
		virtual IDiagnostic* GetDiagnostic() const = 0;
		virtual IBuffer* CreateBuffer() const = 0;
		virtual bool CompileCC(const IBuffer* inputCC, IBuffer** outBC, IBuffer** outDiagnostic) const = 0;
		virtual bool GetFunctionAddress(const IBuffer* inputBC, const char* name, void** outFunctionAddress) const = 0;
		virtual void Stop() = 0;
		virtual bool Start() = 0;
		virtual bool Ready() const = 0;
		virtual void Release() const = 0;

	};

}///namespace engcc

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 30 Aug 2024 16:46:06 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__34591E11_2706_403E_9EAC_6C87D607B16F__
