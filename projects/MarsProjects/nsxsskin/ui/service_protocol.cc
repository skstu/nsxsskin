#include "stdafx.h"
using namespace ui;
const LPCTSTR AboutServiceProtocol::kClassName = kClassNameAboutServiceProtocol;
AboutServiceProtocol::AboutServiceProtocol() {
}
AboutServiceProtocol::~AboutServiceProtocol() {
}
std::wstring AboutServiceProtocol::GetSkinFolder() {
	return L"installer";
}
std::wstring AboutServiceProtocol::GetSkinFile() {
	return L"protocol.xml";
}
std::wstring AboutServiceProtocol::GetWindowClassName() const {
	return kClassName;
}
void AboutServiceProtocol::InitWindow() {
}

