#if !defined(__78429EB4_E53F_4CED_88B4_9356FFEA97B0__)
#define __78429EB4_E53F_4CED_88B4_9356FFEA97B0__

#pragma warning(disable: 4251 4275 4871)

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/eventhandler.h>

namespace yaml {

	using tfOnDocumentStartCb = std::function<void(const YAML::Mark&)>;
	using tfOnDocumentEndCb = std::function<void(void)>;
	using tfOnOnNullCb = std::function<void(const YAML::Mark&, YAML::anchor_t)>;
	using tfOnOnAliasCb = std::function<void(const YAML::Mark&, YAML::anchor_t)>;
	using tfOnScalarCb = std::function<void(const YAML::Mark&, const std::string&, YAML::anchor_t, const std::string&)>;
	using tfOnSequenceStartCb = std::function<void(const YAML::Mark&, const std::string&, YAML::anchor_t, YAML::EmitterStyle::value)>;
	using tfOnSequenceEndCb = std::function<void(void)>;
	using tfOnMapStartCb = std::function<void(const YAML::Mark&, const std::string&, YAML::anchor_t, YAML::EmitterStyle::value)>;
	using tfOnMapEndCb = std::function<void(void)>;
	using tfOnAnchorCb = std::function<void(const YAML::Mark&, const std::string&)>;

	class IEventHandler : public YAML::EventHandler {
	protected:
		tfOnDocumentStartCb OnDocumentStartCb_ = nullptr;
		tfOnDocumentEndCb OnDocumentEndCb_ = nullptr;
		tfOnOnNullCb OnNullCb_ = nullptr;
		tfOnOnAliasCb OnAliasCb_ = nullptr;
		tfOnScalarCb OnScalarCb_ = nullptr;
		tfOnSequenceStartCb OnSequenceStartCb_ = nullptr;
		tfOnSequenceEndCb OnSequenceEndCb_ = nullptr;
		tfOnMapStartCb OnMapStartCb_ = nullptr;
		tfOnMapEndCb OnMapEndCb_ = nullptr;
		tfOnAnchorCb OnAnchorCb_ = nullptr;

		std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
	};
	/* example
			doc->RegisterOnDocumentStartCb([](const YAML::Mark& mark) {});
		doc->RegisterOnDocumentEndCb([]() {});
		doc->RegisterOnNullCb([](const YAML::Mark& mark, YAML::anchor_t anchor) {});
		doc->RegisterOnAliasCb([](const YAML::Mark& mark, YAML::anchor_t anchor) {});
		doc->RegisterOnScalarCb([](const YAML::Mark& mark, const std::string& tag,
			YAML::anchor_t anchor, const std::string& value) {});
		doc->RegisterOnSequenceStartCb([](const YAML::Mark& mark, const std::string& tag,
			YAML::anchor_t anchor, YAML::EmitterStyle::value style) {});
		doc->RegisterOnSequenceEndCb([]() {});
		doc->RegisterOnMapStartCb([](const YAML::Mark& mark, const std::string& tag,
			YAML::anchor_t anchor, YAML::EmitterStyle::value style) {});
		doc->RegisterOnMapEndCb([](void) {});
		doc->RegisterOnAnchorCb([](const YAML::Mark& mark, const std::string& anchor_name) {});
	*/
	class IDocument : public IEventHandler {
	public:
		IDocument(const std::string& input) : input_(input) {
		}
		virtual ~IDocument() {
		}
		virtual void Release() const {
			delete this;
		}
	public:
		virtual void OnDocumentStart(const YAML::Mark& mark) override {
			std::lock_guard<std::mutex> lock{ *mtx_ };
			if (OnDocumentStartCb_)
				OnDocumentStartCb_(mark);
		}
		virtual void OnDocumentEnd() override {
			std::lock_guard<std::mutex> lock{ *mtx_ };
			if (OnDocumentEndCb_)
				OnDocumentEndCb_();
		}
		virtual void OnNull(const YAML::Mark& mark, YAML::anchor_t anchor) override {
			std::lock_guard<std::mutex> lock{ *mtx_ };
			if (OnNullCb_)
				OnNullCb_(mark, anchor);
		}
		virtual void OnAlias(const YAML::Mark& mark, YAML::anchor_t anchor) override {
			std::lock_guard<std::mutex> lock{ *mtx_ };
			if (OnAliasCb_)
				OnAliasCb_(mark, anchor);
		}
		virtual void OnScalar(const YAML::Mark& mark, const std::string& tag,
			YAML::anchor_t anchor, const std::string& value) override {
			std::lock_guard<std::mutex> lock{ *mtx_ };
			if (OnScalarCb_)
				OnScalarCb_(mark, tag, anchor, value);
		}
		virtual void OnSequenceStart(const YAML::Mark& mark, const std::string& tag,
			YAML::anchor_t anchor, YAML::EmitterStyle::value style) override {
			std::lock_guard<std::mutex> lock{ *mtx_ };
			if (OnSequenceStartCb_)
				OnSequenceStartCb_(mark, tag, anchor, style);
		}
		virtual void OnSequenceEnd() override {
			std::lock_guard<std::mutex> lock{ *mtx_ };
			if (OnSequenceEndCb_)
				OnSequenceEndCb_();
		}
		virtual void OnMapStart(const YAML::Mark& mark, const std::string& tag,
			YAML::anchor_t anchor, YAML::EmitterStyle::value style) override {
			std::lock_guard<std::mutex> lock{ *mtx_ };
			if (OnMapStartCb_)
				OnMapStartCb_(mark, tag, anchor, style);
		}
		virtual void OnMapEnd() override {
			std::lock_guard<std::mutex> lock{ *mtx_ };
			if (OnMapEndCb_)
				OnMapEndCb_();
		}
		virtual void OnAnchor(const YAML::Mark& mark, const std::string& anchor_name) override {
			std::lock_guard<std::mutex> lock{ *mtx_ };
			if (OnAnchorCb_)
				OnAnchorCb_(mark, anchor_name);
		}
		void RegisterOnDocumentStartCb(const tfOnDocumentStartCb& cb) {
			std::lock_guard<std::mutex> lock{ *mtx_ };
			OnDocumentStartCb_ = cb;
		}
		void RegisterOnDocumentEndCb(const tfOnDocumentEndCb& cb) {
			std::lock_guard<std::mutex> lock{ *mtx_ };
			OnDocumentEndCb_ = cb;
		}
		void RegisterOnNullCb(const tfOnOnNullCb& cb) {
			std::lock_guard<std::mutex> lock{ *mtx_ };
			OnNullCb_ = cb;
		}
		void RegisterOnAliasCb(const tfOnOnAliasCb& cb) {
			std::lock_guard<std::mutex> lock{ *mtx_ };
			OnAliasCb_ = cb;
		}
		void RegisterOnScalarCb(const tfOnScalarCb& cb) {
			std::lock_guard<std::mutex> lock{ *mtx_ };
			OnScalarCb_ = cb;
		}
		void RegisterOnSequenceStartCb(const tfOnSequenceStartCb& cb) {
			std::lock_guard<std::mutex> lock{ *mtx_ };
			OnSequenceStartCb_ = cb;
		}
		void RegisterOnSequenceEndCb(const tfOnSequenceEndCb& cb) {
			std::lock_guard<std::mutex> lock{ *mtx_ };
			OnSequenceEndCb_ = cb;
		}
		void RegisterOnMapStartCb(const tfOnMapStartCb& cb) {
			std::lock_guard<std::mutex> lock{ *mtx_ };
			OnMapStartCb_ = cb;
		}
		void RegisterOnMapEndCb(const tfOnMapEndCb& cb) {
			std::lock_guard<std::mutex> lock{ *mtx_ };
			OnMapEndCb_ = cb;
		}
		void RegisterOnAnchorCb(const tfOnAnchorCb& cb) {
			std::lock_guard<std::mutex> lock{ *mtx_ };
			OnAnchorCb_ = cb;
		}
		virtual bool Parser() {
			bool result = false;
			do {
				if (input_.empty())
					break;
				std::stringstream stream_(input_);
				YAML::Parser* parser = new YAML::Parser(stream_);
				while (parser->HandleNextDocument(*this)) {}
				result = true;
			} while (0);
			return result;
		}
	private:
		const std::string input_;
	};


}///namespace yaml


/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 06 Aug 2024 02:02:10 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__78429EB4_E53F_4CED_88B4_9356FFEA97B0__