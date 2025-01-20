#include "stdafx.h"

#define ENABLE_TEST 0

#if ENABLE_TEST
const std::string test_data = R"({
    "total": 294038173,
    "root": "%appdata%\\MarsProjects",
    "dependency": [

    ],
    "items": [
        {
"enable":true,
            "from": "http://10.100.3.248/installer/items/chromium_130.0.6723.44.7z",
            "to": "/chromium/130.0.6723.44/130.0.6723.44.7z"
        },
        {
"enable":true,
            "from": "http://10.100.3.248/installer/items/chromium_130.0.6723.59.7z",
            "to": "/chromium/130.0.6723.59/130.0.6723.59.7z"
        },
        {
"enable":true,
            "from": "http://10.100.3.248/installer/items/electron-client-v1.0.7z",
            "to": "/electron-client-v1.0.7z"
        },
        {
"enable":true,
            "from": "http://10.100.3.248/installer/items/server.7z",
            "to": "/server.7z"
        },
        {
"enable":true,
            "from": "http://10.100.3.248/installer/items/route.7z",
            "to": "/route.7z"
        }
    ],
    "startup":[
        {
"enable":true,
            "path":"/electron-client-v1.0.exe",
            "args":""
        },
        {
"enable":true,
            "path":"/perform.exe",
            "args":"--type=service"
        }
    ],
    "shortcut":[
        {
"enable":false,
            "logo":"",
            "src":"",
            "dst":""
        }

    ]
})";

static void test(Config::Installer&);
#endif
Config::Config() {
#if ENABLE_TEST
	test(installer_);
#endif
}

Config::~Config() {

}
bool Config::operator<<(const std::string& input) {
	return (installer_ << input);
}
#if ENABLE_TEST
void test(Config::Installer& installer_) {
	do {
		rapidjson::Document doc;
		if (doc.Parse(test_data.data(), test_data.size()).HasParseError())
			break;
		if (!doc.IsObject() || doc.ObjectEmpty())
			break;

		//!@ root 
		if (doc.HasMember("root") && doc["root"].IsString()) {
			installer_.root_ = shared::Win::Env::ParserEnvironmentStringsW(shared::IConv::UTF8ToWString(doc["root"].GetString()));
			if (!shared::Win::AccessW(installer_.root_)) {
				if (!shared::Win::CreateDirectoryW(installer_.root_))
					break;
			}
		}
		//!@ total
		if (doc.HasMember("total") && doc["total"].IsUint64()) {
			installer_.total_ = doc["total"].GetUint64();
		}

		do {//!@ shortcut
			if (!doc.HasMember("shortcut"))
				break;
			if (!doc["shortcut"].IsArray())
				break;
			if (doc["shortcut"].Empty())
				break;

			for (auto it = doc["shortcut"].Begin(); it != doc["shortcut"].End(); ++it) {
				Config::Installer::Shortcut shortcut;
				do {
					auto& obj = *it;
					if (!obj.IsObject())
						break;
					if (obj.HasMember("enable") && obj["enable"].IsBool()) {
						shortcut.enable = obj["enable"].GetBool();
						if (!shortcut.enable)
							break;
					}
					if (!obj.HasMember("logo") || !obj["logo"].IsString())
						break;
					if (!obj.HasMember("src") || !obj["src"].IsString())
						break;
					if (!obj.HasMember("dst") || !obj["dst"].IsString())
						break;
					shortcut.logo = shared::IConv::UTF8ToWString(obj["logo"].GetString());
					shortcut.src = shared::IConv::UTF8ToWString(obj["src"].GetString());
					shortcut.dst = shared::IConv::UTF8ToWString(obj["dst"].GetString());

					if (!shortcut.logo.empty())
						shortcut.logo = shared::Win::PathFixedW(installer_.root_ + L"\\" + shortcut.logo);

					if (!shortcut.src.empty())
						shortcut.src = shared::Win::PathFixedW(installer_.root_ + L"\\" + shortcut.src);
					if (!shortcut.dst.empty()) {
						PWSTR path = NULL;
						HRESULT hr = SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &path);
						if (SUCCEEDED(hr) && path) {
							std::wstring wstrPath(path);
							shortcut.dst = shared::Win::PathFixedW(wstrPath + L"\\" + shortcut.dst + L".lnk");
						}
						if (path) {
							CoTaskMemFree(path);
						}
					}

					installer_.shortcuts_.emplace_back(shortcut);
				} while (0);
			}
		} while (0);


		do {//!@ items
			if (!doc.HasMember("items"))
				break;
			if (!doc["items"].IsArray())
				break;
			if (doc["items"].Empty())
				break;

			for (auto it = doc["items"].Begin(); it != doc["items"].End(); ++it) {
				Config::Installer::Item item;
				do {
					auto& obj = *it;
					if (!obj.IsObject())
						break;
					if (obj.HasMember("enable") && obj["enable"].IsBool()) {
						item.enable = obj["enable"].GetBool();
						if (!item.enable)
							break;
					}
					if (!obj.HasMember("from") || !obj["from"].IsString())
						break;
					if (!obj.HasMember("to") || !obj["to"].IsString())
						break;
					item.from = shared::Win::UrlFixedW(shared::IConv::UTF8ToWString(obj["from"].GetString()));
					item.to = shared::IConv::UTF8ToWString(obj["to"].GetString());

					if (!item.from.empty())
						item.from = shared::Win::PathFixedW(installer_.root_ + L"\\" + item.from);

					item.from = shared::Win::UrlFixedW(shared::IConv::UTF8ToWString(obj["from"].GetString()));
					item.to = shared::Win::PathFixedW(installer_.root_ + L"\\" + shared::IConv::UTF8ToWString(obj["to"].GetString()));

					installer_.items_.emplace_back(item);
				} while (0);
			}
		} while (0);


		do {//!@ startup
			if (!doc.HasMember("startup"))
				break;
			if (!doc["startup"].IsArray())
				break;
			if (doc["startup"].Empty())
				break;

			for (auto it = doc["startup"].Begin(); it != doc["startup"].End(); ++it) {
				Config::Installer::Startup startup;
				do {
					auto& obj = *it;
					if (!obj.IsObject())
						break;
					if (obj.HasMember("enable") && obj["enable"].IsBool()) {
						startup.enable = obj["enable"].GetBool();
						if (!startup.enable)
							break;
					}
					if (!obj.HasMember("path") || !obj["path"].IsString())
						break;
					if (obj.HasMember("args") && obj["args"].IsString()) {
						startup.args = shared::IConv::UTF8ToWString(obj["args"].GetString());
					}
					startup.path = shared::Win::PathFixedW(installer_.root_ + L"\\" + shared::IConv::UTF8ToWString(obj["path"].GetString()));

					installer_.starts_.emplace_back(startup);
				} while (0);
			}
		} while (0);

		auto sss = 0;
	} while (0);
}
#endif
void Config::UpdateInstallerTotal(const size_t& total) {
	std::lock_guard<std::mutex> lock{ *mtx_ };
	installer_.total_ = total;
}
const chromium::Installer& Config::GetInstaller() const{
	std::lock_guard<std::mutex> lock{ *mtx_ };
	return installer_;
}
///////////////////////////////////////////////////////////
static Config* __gspConfig = nullptr;

Config* Config::Get() {
	if (!__gspConfig)
		__gspConfig = new Config();
	return __gspConfig;
}
void Config::Destroy() {
	SK_DELETE_PTR(__gspConfig);
}