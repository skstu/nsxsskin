
# ===================== 外部插件以及宏 =============================
!include "StrFunc.nsh"
!include "WordFunc.nsh"
${StrRep}
${StrStr}
!include "LogicLib.nsh"
!include "nsDialogs.nsh"
!include "x64.nsh"
!include "WinVer.nsh" 

# ===================== 安装包版本 =============================
VIProductVersion             		"${PRODUCT_VERSION}"
VIAddVersionKey "ProductVersion"    "${PRODUCT_VERSION}"
VIAddVersionKey "ProductName"       "${PRODUCT_NAME}"
VIAddVersionKey "CompanyName"       "${PRODUCT_PUBLISHER}"
VIAddVersionKey "FileVersion"       "${PRODUCT_VERSION}"
VIAddVersionKey "InternalName"      "${EXE_NAME}"
VIAddVersionKey "FileDescription"   "${PRODUCT_NAME}"
VIAddVersionKey "LegalCopyright"    "${PRODUCT_LEGAL}"

# 自定义页面
Page custom DUIPage
# 自定义卸载页面
UninstPage custom un.DUIPage

# ======================= DUILIB 自定义页面 =========================
Function DUIPage
	InitPluginsDir   	
	SetOutPath "$PLUGINSDIR"
	File "${INSTALL_LICENCE_FILENAME}"
    File "${INSTALL_RES_PATH}"
	File /oname=logo.ico "${INSTALL_ICO}" 		#此处的目标文件一定是logo.ico，否则控件将找不到文件 
	nsxsskin::InitInstallPage "$PLUGINSDIR\" "$PLUGINSDIR\${INSTALL_LICENCE_FILENAME}" "${INSTALL_DEFALT_SETUPPATH}" "${PRODUCT_VERSION}"
	Call BindUIControls	
	nsxsskin::ShowPage
FunctionEnd

#绑定安装的界面事件 
Function BindUIControls
    #开始安装按钮事件
    GetFunctionAddress $0 OnBtnInstallClick
    nsxsskin::BindCallBack "OnBtnInstallClick" $0

	GetFunctionAddress $0 CreateStartMenuShortcut
    nsxsskin::BindCallBack "CreateStartMenuShortcut" $0
	#创建桌面快捷方式
    GetFunctionAddress $0 CreateDesktopShortcut
    nsxsskin::BindCallBack "CreateDesktopShortcut" $0
	#开机启动
    GetFunctionAddress $0 CreatePowerOn
    nsxsskin::BindCallBack "CreatePowerOn" $0
FunctionEnd

#创建桌面快捷方式
Function CreateDesktopShortcut
	SetShellVarContext all
	Delete "$DESKTOP\${PRODUCT_NAME}.lnk"
	Sleep 10
	CreateShortCut "$DESKTOP\${PRODUCT_NAME}.lnk" "$INSTDIR\ext\client\${EXE_NAME}"
	SetShellVarContext current
FunctionEnd

#开机启动
Function CreatePowerOn
	SetShellVarContext all
	CreateShortCut "$SMSTARTUP\${PRODUCT_NAME}.lnk" "$INSTDIR\ext\client\${EXE_NAME}"
	SetShellVarContext current
FunctionEnd

#创建开始菜单快捷方式
Function CreateStartMenuShortcut
    SetShellVarContext current
    CreateDirectory "$SMPROGRAMS\${PRODUCT_NAME}"	
    WriteINIStr "$SMPROGRAMS\${PRODUCT_NAME}\XXXX公司 网站.url" "InternetShortcut" "URL" "http://www.abc.com/"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk" "$INSTDIR\${EXE_NAME}" "" "" 0 SW_SHOWNORMAL "" "启动${PRODUCT_NAME}"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\卸载 ${PRODUCT_NAME}.lnk" "$INSTDIR\uninst.exe" "" "" 1

    SetShellVarContext all
    CreateDirectory "$SMPROGRAMS\${PRODUCT_NAME}"	
    WriteINIStr "$SMPROGRAMS\${PRODUCT_NAME}\XXXX公司 网站.url" "InternetShortcut" "URL" "http://www.abc.com/"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk" "$INSTDIR\${EXE_NAME}" "" "" 0 SW_SHOWNORMAL "" "启动${PRODUCT_NAME}"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\卸载 ${PRODUCT_NAME}.lnk" "$INSTDIR\uninst.exe" "" "" 1
    SetShellVarContext current  
FunctionEnd

Function ExtractCallback
	Pop $R8
	Pop $R9
	nsxsskin::SetProgressValue "$R8" "$R9"
    ${If} $R8 == $R9
        nsxsskin::ExtractFinished "$R8" "$R9"      
    ${EndIf}
FunctionEnd

Function ExtractFunc
	SetOutPath $INSTDIR

    File "${INSTALL_7Z_PATH}"
    GetFunctionAddress $R9 ExtractCallback
    nsis7zU::ExtractWithCallback "$INSTDIR\${INSTALL_7Z_NAME}" $R9
	Delete "$INSTDIR\${INSTALL_7Z_NAME}"
	
	Sleep 100
FunctionEnd

# 开始安装
Function OnBtnInstallClick
	nsxsskin::GetControlAttribute "nsisGetInstallDir"
    Pop $0
	${If} $0 == ""
        StrCpy "$INSTDIR" "${INSTALL_DEFALT_SETUPPATH}"
	${Else}
		StrCpy $INSTDIR "$0"
    ${EndIf}

	nsxsskin::SetControlAttribute "nsisSetInstallDir" "$INSTDIR\"
	nsxsskin::SetControlAttribute "nsisSetProgramMain" "$INSTDIR\ext\client\${EXE_NAME}"

	Call ExtractFunc
    ; #创建卸载程序
    Call CreateUninstall
funcend:
FunctionEnd

# 生成卸载入口 
Function CreateUninstall
	#写入注册信息 
	SetRegView 32
	WriteRegStr HKLM "Software\${PROJECT_NAME}\${PRODUCT_PATHNAME}" "InstPath" "$INSTDIR"	
	WriteUninstaller "$INSTDIR\uninst.exe"	
	# 添加卸载信息到控制面板
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_PATHNAME}" "DisplayIcon" "$INSTDIR\resources\${INSTALL_ICO}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_PATHNAME}" "DisplayName" "${PRODUCT_NAME}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_PATHNAME}" "UninstallString" "$INSTDIR\uninst.exe"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_PATHNAME}" "Publisher" "${PRODUCT_PUBLISHER}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_PATHNAME}" "DisplayVersion" "${PRODUCT_VERSION}"
FunctionEnd

# 添加一个静默安装的入口
Section "silentInstallSec" SEC01
    MessageBox MB_OK|MB_ICONINFORMATION "Test silent install. you can add your silent install code here."
SectionEnd

#================================= 自定义卸载页面 ==================================

Function un.DUIPage
    InitPluginsDir
	SetOutPath "$PLUGINSDIR"
    File "${INSTALL_RES_PATH}"
	File /oname=logo.ico "${UNINSTALL_ICO}" 		#此处的目标文件一定是logo.ico，否则控件将找不到文件 
	ReadRegStr $0 HKLM "Software\${PROJECT_NAME}\${PRODUCT_PATHNAME}" "InstPath"
	nsxsskin::InitUnInstallPage "$PLUGINSDIR\" "$0" "$APPDATA\${PRODUCT_NAME},"
	Call un.BindUnInstUIControls
	nsxsskin::ShowPage
FunctionEnd

#绑定卸载的事件 
Function un.BindUnInstUIControls
	GetFunctionAddress $0 un.DestroyDesktopShortcut
	nsxsskin::BindCallBack "DestroyDesktopShortcut" $0
	
	GetFunctionAddress $0 un.DestroyPowerOn
	nsxsskin::BindCallBack "DestroyPowerOn" $0
	
	GetFunctionAddress $0 un.DestroyUninstall
	nsxsskin::BindCallBack "DestroyUninstall" $0 
FunctionEnd

Function un.DestroyUninstall
    SetRegView 32
    DeleteRegValue HKLM "Software\${PROJECT_NAME}\${PRODUCT_PATHNAME}" "InstPath" 
    DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_PATHNAME}" 
    Delete "$INSTDIR\uninst.exe"
FunctionEnd

Function un.DestroyDesktopShortcut
	SetShellVarContext all
	Delete "$DESKTOP\${PRODUCT_NAME}.lnk"
	SetShellVarContext current
FunctionEnd

Function un.DestroyPowerOn
	SetShellVarContext all
	Delete "$SMSTARTUP\${PRODUCT_NAME}.lnk"
	SetShellVarContext current
FunctionEnd

# 添加一个静默卸载的入口 
Section "un.silentInstallSec" SEC02
    MessageBox MB_OK|MB_ICONINFORMATION "Test silent install. you can add your silent uninstall code here."
SectionEnd
