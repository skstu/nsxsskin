#if !defined(__7D0E6D3E_2ADA_4BDB_825C_31A2B1F41F8D__)
#define __7D0E6D3E_2ADA_4BDB_825C_31A2B1F41F8D__

#include "module.h"

namespace cvpp {
	class ICvpp : public IModule {
	public:
		//typedef void(*tf)
	public:
		enum class TextRecognizeEngineType : unsigned long long {
			Unknown = 0x00000,
			Rtocr = 0x10000,
			Tesseract = 0x20000,
			OpencvContrib = 0x30000,
		};
		enum class TextRecognizeContentType : unsigned long long {
			Common = 0x0000,
			Sheet = 0x1000,

			Card = 0x2000,
			ChineseIDCard = 0x2110, //!@ 中国居民身份证
			ChineseIDCardFront = 0x2111,
			ChineseIDCardBack = 0x2112,

			Ticket = 0x3000,
			Invoice = 0x3100,
			VATInvoice = 0x3110,        //!@ 增值税电子普通发票
			ElectronicInvoice = 0x3120, //!@ 电子发票（普通发票）

			VerificationCode = 0x4000,
		};

		class IStream {
		public:
			virtual void SetData(const void*, const size_t&) = 0;
			virtual void* GetBuffer() const = 0;
			virtual size_t GetSize() const = 0;
			virtual void Release() const = 0;
			virtual bool Empty() const = 0;
			virtual IStream* Clone() const = 0;
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
			virtual const IStream* Begin() const = 0;
			virtual const IStream* End() const = 0;
			virtual IStream* Next(const size_t&) const = 0;
			virtual size_t Total() const = 0;
			virtual bool Empty() const = 0;
			virtual void Push(IStream*) = 0;
			virtual void Push(const void*, const size_t&) = 0;
			virtual void Release() const = 0;
			virtual IStreamArray* Clone() const = 0;
		};

		class IResult {
		public:
			class ILineArray {
			public:
				class ILine {
				public:
					class IWordArray {
					public:
						class IWord {
						public:
							class IBoundingRect {
							public:
								virtual float X() const = 0;
								virtual float Y() const = 0;
								virtual float CX() const = 0;
								virtual float CY() const = 0;
								virtual bool Empty() const = 0;
								virtual void Release() const = 0;
							};

						public:
							virtual void Release() const = 0;
							virtual const IBoundingRect* GetBoundingRect() const = 0;
							virtual const wchar_t* GetText() const = 0;
							virtual const wchar_t* GetTextWords() const = 0;
						};

					public:
						virtual void Release() const = 0;
						virtual const IWord* Next(const size_t&) const = 0;
						virtual size_t Total() const = 0;
					};

				public:
					virtual void Release() const = 0;
					virtual const wchar_t* GetText() const = 0;
					virtual const wchar_t* GetTextWords() const = 0;
					virtual const IWordArray* GetWords() const = 0;
					virtual const ILineArray::ILine::IWordArray::IWord::IBoundingRect*
						GetTextWordBoundingRect(const size_t& pos) const = 0;
					virtual const ILineArray::ILine::IWordArray::IWord::IBoundingRect*
						GetBoundingRect() const = 0;
				};

			public:
				virtual void Release() const = 0;
				virtual const ILine* Next(const size_t&) const = 0;
				virtual size_t Total() const = 0;
			};

		public:
			virtual void Release() const = 0;
			virtual const IStream* GetStream() const = 0;
			virtual const IStreamArray* GetStreamArray() const = 0;
			virtual const wchar_t* GetText() const = 0;
			virtual const wchar_t* GetTextWords() const = 0;
			virtual const wchar_t* GetTextSortedWords() const = 0;
			virtual ILineArray*
				GetTextSortedLines(const size_t& et_y /*_err_threshold*/) const = 0;
			virtual const ILineArray* GetLines() const = 0;
			virtual const ILineArray::ILine::IWordArray::IWord*
				FindFirstWord(const wchar_t*) const = 0;
			virtual const ILineArray::ILine::IWordArray::IWord::IBoundingRect*
				GetTextWordBoundingRect(const size_t& pos) const = 0;
			virtual bool GetSerializationData(char**, size_t*) const = 0;
		};

		class IElement {
		public:
			enum class ElementType : unsigned long long {
				Unknown = 0,
				Image = 1,
				Text = Image << 1,
			};
		public:
			virtual void Release() const = 0;
			virtual const ElementType& Type() const = 0;
			virtual const wchar_t* GetOcrtext() const = 0;
			virtual const char* toJson() const = 0;
			virtual const char* Key() const = 0;
			virtual const unsigned long& ProcessId() const = 0;
			virtual const wchar_t* ProcessImagePathname() const = 0;
			virtual const wchar_t* GetRootWindowText() const = 0;
			virtual const wchar_t* GetRootClassName() const = 0;
			virtual void* GetWindowHandle() const = 0;
			virtual void* GetRootWindowHandle() const = 0;
			virtual IRegion* GetRegion() const = 0;
		};

		class IElementArray {
		public:
			virtual IElement* Next(const size_t&) const = 0;
			virtual size_t Total() const = 0;
			virtual void Push(IElement*) = 0;
			virtual void Release() const = 0;
		};

		class IConfig : public IModule::IConfig {
		public:
			virtual void
				SetTextRecognizeEngineType(const TextRecognizeEngineType&) = 0;
		};

	public:
		virtual void Stop() = 0;
		virtual bool Start() = 0;
		virtual bool Ready() const = 0;
		virtual void Release() const = 0;
		virtual IStream* CreateStream() const = 0;
		virtual IRegion* CreateRegion() const = 0;
		virtual IRegion* CreateRegion(void* hwnd) const = 0;
		virtual IStreamArray* CreateStreamArray() const = 0;
		virtual IRegionArray* CreateRegionArray() const = 0;
		virtual bool RecognizeTextFromRegion(
			const IRegion*, IResult**,
			const unsigned long long& /*TextRecognizeContentType*/) const = 0;
		virtual bool RecognizeTextFromStreams(
			const IStreamArray*, IResult**,
			const unsigned long long& /*TextRecognizeContentType*/) const = 0;
		virtual bool CaptureElement(const IRegion*, ICvpp::IElementArray** outputElements) const = 0;
		virtual bool CaptureElement(const long& x, const long& y, const IRegion*, ICvpp::IElement** outputElement) const = 0;
		virtual bool CaptureElementCheck(const ICvpp::IElement* inputElement, ICvpp::IElement** outputElement) const = 0;
	};

} // namespace cvpp

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 30 Aug 2024 08:56:43 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__7D0E6D3E_2ADA_4BDB_825C_31A2B1F41F8D__
