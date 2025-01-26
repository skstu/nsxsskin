#if !defined(__E7629A69_2CAD_4A7A_B113_E55AAF5B45E1__)
#define __E7629A69_2CAD_4A7A_B113_E55AAF5B45E1__

#include <macros.h>
#include <stl.hpp>
#include <fmt/format.h>
#include <rapidjson.h>
#include <rapidxml.h>
#include <log.hpp>
#include <win32.h>
#include <timer.hpp>
#include <libuv.h>
#include <zipcc.h>
#include <utfpp.hpp>

#include "base/base.h"
#include "duilib/UIlib.h"
#include "ui_components/ui_components.h"

#include "pluginapi.h"
#include "global.h"
#include "ui/ui.h"

#include "resource.h"
#if defined(_UNICODE) || defined(UNICODE)
#pragma comment(lib,"pluginapi-x86-unicode.lib")
#else
#pragma comment(lib,"pluginapi-x86-ansi.lib")
#endif
#if defined (_DEBUG)
#pragma comment(lib,"zlibstaticd.lib")
#pragma comment(lib,"base/debug/base.lib")
#pragma comment(lib,"duilib/debug/duilib.lib")
#pragma comment(lib,"ui_components/debug/ui_components.lib")
#else
#pragma comment(lib,"zlibstatic.lib")
#pragma comment(lib,"base/release/base.lib")
#pragma comment(lib,"duilib/release/duilib.lib")
#pragma comment(lib,"ui_components/release/ui_components.lib")
#endif

/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 20 Jan 2025 06:02:42 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__E7629A69_2CAD_4A7A_B113_E55AAF5B45E1__
