#if !defined(__A0A178C2_808D_4E8C_A2E7_435A58AA4DB6__)
#define __A0A178C2_808D_4E8C_A2E7_435A58AA4DB6__
/*
{
    "total": 294038173,
    "root": "%appdata%\\MarsProjects",
    "dependency": [

    ],
    "items": [
        {
            "from": "http://10.100.3.248/installer/items/chromium_130.0.6723.44.7z",
            "to": "/chromium/130.0.6723.44/130.0.6723.44.7z"
        },
        {
            "from": "http://10.100.3.248/installer/items/chromium_130.0.6723.59.7z",
            "to": "/chromium/130.0.6723.59/130.0.6723.59.7z"
        },
        {
            "from": "http://10.100.3.248/installer/items/electron-client-v1.0.7z",
            "to": "/electron-client-v1.0.7z"
        },
        {
            "from": "http://10.100.3.248/installer/items/server.7z",
            "to": "/server.7z"
        },
        {
            "from": "http://10.100.3.248/installer/items/route.7z",
            "to": "/route.7z"
        }
    ],
    "startup":[
        {
            "path":"/electron-client-v1.0.exe",
            "args":""
        },
        {
            "path":"/perform.exe",
            "args":"--type=service"
        }
    ],
    "shortcut":[
        {
            "logo":"",
            "src":"",
            "dst":""
        }

    ]
}
*/
class Config {
public:
 
public:
	static Config* Get();
	static void Destroy();
	bool operator<<(const std::string&);
private:
	Config();
	~Config();
public:
	const chromium::Installer& GetInstaller() const;
 void UpdateInstallerTotal(const size_t&);
private:
 chromium::Installer installer_;
	std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 16 Oct 2024 05:20:18 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__A0A178C2_808D_4E8C_A2E7_435A58AA4DB6__