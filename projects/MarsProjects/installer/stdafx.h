#if !defined(__F782F3C4_D41B_4C5F_A029_03505D3AEC30__)
#define __F782F3C4_D41B_4C5F_A029_03505D3AEC30__

#define PROJECTS_ROOT L"%AppData%\\MarsPlatform\\"

#define HOMEPAGE_SWITCH_SLOGAN_INTERVAL 3000

#include <macros.h>
#include <stl.h>
#include <fmt/format.h>
#include <rapidjson.h>
#include <rapidxml.h>
#include <log.hpp>
#include <win32.h>
#include <timer.hpp>
#include <libuv.h>
#include <chromium.h>
#include <zipcc.h>
#include <httplib.h>
#include <http_parser.hpp>

#include "base/base.h"
#include "duilib/UIlib.h"
#include "ui_components/ui_components.h"
#include "resource.h"

#include "config.h"
#include "window.h"
#include "window_thread.h"

#if _DEBUG
#pragma comment(lib,"zlibstaticd.lib")
#pragma comment(lib,R"(\x64\base_d.lib)")
#pragma comment(lib,R"(\x64\duilib_d.lib)")
#pragma comment(lib,R"(\x64\ui_components_d.lib)")
#else
#pragma comment(lib,R"(\x64\base.lib)")
#pragma comment(lib,R"(\x64\duilib.lib)")
#pragma comment(lib,"zlibstatic.lib")
#pragma comment(lib,R"(\x64\ui_components.lib)")
#endif

/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 12 Oct 2024 20:44:12 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__F782F3C4_D41B_4C5F_A029_03505D3AEC30__
