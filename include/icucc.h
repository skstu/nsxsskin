#if !defined(__DABF953F_538C_4AF3_9A5A_15FA6401AF80__)
#define __DABF953F_538C_4AF3_9A5A_15FA6401AF80__

#include "module.h"

namespace icucc {
	class IIcucc : public IModule {
	public:
		enum class CharsetType : unsigned long long {
			UNKNOWN = 0,
			UTF8,
			UTF16,
			UTF16LE,
			UTF16BE,
			UTF32,
			UTF32LE,
			UTF32BE,
			ASCII,
			GBK,
			GB18030,
		};
		class IBuffer {
		public:
			virtual void Release() const = 0;
			virtual void Set(const void*, const size_t&) = 0;
			virtual bool Get(char**, size_t*) const = 0;
			virtual bool Empty() const = 0;
			virtual const void* Begin() const = 0;
			virtual size_t Size() const = 0;
		};
		class IConfig : public IModule::IConfig {
		public:
		};

	public:
		virtual IBuffer* CreateBuffer() const = 0;
		virtual void Stop() = 0;
		virtual bool Start() = 0;
		virtual bool Ready() const = 0;
		virtual void Release() const = 0;
		virtual bool Detect(const IBuffer*, IBuffer**) const = 0;
		virtual bool Convert(const IBuffer* input, const CharsetType& from, const CharsetType& to, IBuffer** output)  const = 0;

	};

} // namespace icucc

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 30 Aug 2024 07:38:01 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__DABF953F_538C_4AF3_9A5A_15FA6401AF80__
