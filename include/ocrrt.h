#if !defined(__7A7BB97B_6A41_4F6A_B9D9_9026F5CF6F8F__)
#define __7A7BB97B_6A41_4F6A_B9D9_9026F5CF6F8F__

#include "module.h"

namespace ocrrt {
	class IOcrrt : public IModule {
	public:
		class IStream {
		public:
			virtual void SetData(const void*, const size_t&) = 0;
			virtual void* GetBuffer() const = 0;
			virtual size_t GetSize() const = 0;
			virtual void Release() const = 0;
			virtual bool Empty() const = 0;
		};

		class IRegion {
		public:
			virtual long X() const = 0;
			virtual long Y() const = 0;
			virtual long CX() const = 0;
			virtual long CY() const = 0;
			virtual void X(const long&) = 0;
			virtual void Y(const long&) = 0;
			virtual void CX(const long&) = 0;
			virtual void CY(const long&) = 0;
			virtual void Release() const = 0;
		};

		class IRegionArray {
		public:
			virtual IRegion* Next(const size_t&) const = 0;
			virtual size_t Total() const = 0;
			virtual void Push(IRegion*) = 0;
			virtual void Release() const = 0;
		};

		class IStreamArray {
		public:
			virtual IStream* Next(const size_t&) const = 0;
			virtual size_t Total() const = 0;
			virtual void Push(IStream*) = 0;
			virtual void Release() const = 0;
		};

		class IResult {
		public:
			virtual void Release() const = 0;
		};

		class IConfig : public IModule::IConfig {
		public:
		};

	public:
		virtual void Stop() = 0;
		virtual bool Start() = 0;
		virtual bool Ready() const = 0;
		virtual void Release() const = 0;
		virtual IStream* CreateStream() const = 0;
		virtual IRegion* CreateRegion() const = 0;
		virtual IRegionArray* CreateRegionArray() const = 0;
		//virtual bool RecognizeSpecifiedRangeAsText(const IRegion*, IRegion***) const = 0;
	};

}///namespace cvpp

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 16 Aug 2024 14:44:20 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__7A7BB97B_6A41_4F6A_B9D9_9026F5CF6F8F__

