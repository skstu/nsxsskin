#include "stdafx.h"

Launch::Launch() {
}

Launch::~Launch() {
}
bool Launch::Start() {
	MessageBoxW(NULL, __FUNCTIONW__, NULL, MB_TOPMOST);
	return false;
}
void Launch::Stop() {
}
////////////////////////////////////////////////////////////////////////////////////
static Launch* __gpsLaunch = nullptr;
Launch* Launch::Get() {
	if (!__gpsLaunch)
		__gpsLaunch = new Launch();
	return __gpsLaunch;
}
void Launch::Destroy() {
	if (__gpsLaunch)
		__gpsLaunch->Stop();
	SK_DELETE_PTR(__gpsLaunch);
}

