#include "stdafx.h"
using namespace shared;
//!@ "SKSTU_ROOT=%appdata%/skstu"
bool Win::Env::Set(const std::string& key_equal_value) {
	bool result = false;
	do{
		if (key_equal_value.empty())
			break;
		if (0 != _putenv(key_equal_value.c_str()))
			break;
		result = true;
	} while (0);
	return result;
}
//!@ "%appdata%/skstu"
bool Win::Env::AppendPath(const std::string& val) {
	bool result = false;
	do {
		if (val.empty())
			break;
		auto insert = Env::Get("path");
		if(!insert.empty()){
			auto last = std::prev(insert.end());
			if (*last == ';')
				insert.pop_back();
		}
		insert.append(";").append(val).append(";");
		insert.insert(0, "path=");
		if (0 != _putenv(insert.c_str()))
			break;
		result = true;
	} while (0);
	return result;
}
std::string Win::Env::Get(const std::string& key){
	std::string result;
	do{
		if (key.empty())
			break;
		char* current_path = std::getenv(key.c_str());
		result = current_path ? current_path : "";
	} while (0);
	return result;
}
bool Win::Env::Set(const std::string& key, const std::vector<std::string>& inputs){
	bool result = false;
	do{
		if (key.empty() || inputs.empty())
			break;

		std::string insert = key + "=";
		for (const auto& in : inputs)
			insert.append(in).append(";");
	
		// Update the PATH environment variable
		if (0 != _putenv(insert.c_str()))
			break;

		result = true;
	} while (0);
	return result;
}
//!@ SKSTU_ROOT
//!@ %appdata%/skstu
bool Win::Env::Set(const std::string& key, const std::string& val) {
	bool result = false;
	do {
		if (key.empty() || val.empty())
			break;

		std::string current_path = Env::Get(key);
		// Create a new PATH string
		std::string new_path = current_path;
		if(!current_path.empty())
			new_path.append(";");
		new_path.append(val);

		std::string inster_env;
		inster_env.append(key).append("=");
		inster_env.append(new_path);
		// Update the PATH environment variable
		if (0 != _putenv(inster_env.c_str()))
			break;
		result = true;
	} while (0);
	return result;
}
bool Win::Env::Get(const std::string& key, std::vector<std::string>& output){
	bool result = false;
	do{
		if (key.empty())
			break;
		std::string current = Env::Get(key);
		if (current.empty())
			break;
		File::ParseA(current, ';', output);
		result = !output.empty();
	} while (0);
	return result;
}

std::wstring Win::Env::ParserEnvironmentStringsW(const std::wstring& inputEnvString) {
	std::wstring result;
	bool success = false;
	do {
		auto f = inputEnvString.find(L'%');
		if(f==std::wstring::npos){
			result = Win::PathFixedW(inputEnvString);
			success = true;
			break;
		}
		result.resize(MAX_PATH, 0x00);
		DWORD dwResult = ::ExpandEnvironmentStringsW(inputEnvString.c_str(), &result[0], result.size());
		if (dwResult <= 0)
			break;
		result.resize(dwResult);
		result = PathFixedW(result);
		success = true;
	} while (0);
	if (!success)
		result.clear();
	return result;
}
std::string Win::Env::ParserEnvironmentStringsA(const std::string& inputEnvString) {
	std::string result;
	bool success = false;
	do {
		auto f = inputEnvString.find('%');
		if (f == std::string::npos) {
			result = Win::PathFixedA(inputEnvString);
			success = true;
			break;
		}
		result.resize(MAX_PATH, 0x00);
		DWORD dwResult = ::ExpandEnvironmentStringsA(inputEnvString.c_str(), &result[0], result.size());
		if (dwResult <= 0)
			break;
		result.resize(dwResult);
		result = PathFixedA(result);
		success = true;
	} while (0);
	if (!success)
		result.clear();
	return result;
}