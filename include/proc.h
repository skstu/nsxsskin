#if !defined(__17283FB6_5B5C_4ED7_94B6_E640F4B0F47B__)
#define __17283FB6_5B5C_4ED7_94B6_E640F4B0F47B__

#include "module.h"

namespace proc {
	class IProc : public IModule {
	public:
		class IConfig : public IModule::IConfig {
		public:

		};
	public:
		virtual bool Start() = 0;
		virtual void Stop() = 0;
		virtual bool Ready() const = 0;
		virtual void Release() const = 0;
	};
} // namespace proc

/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 07 Aug 2024 00:11:21 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__17283FB6_5B5C_4ED7_94B6_E640F4B0F47B__
