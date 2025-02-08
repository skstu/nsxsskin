Unicode true
RequestExecutionLevel admin
!define PROJECT_NAME                "Office"
!define PRODUCT_NAME           		"扇子办公宝"
!define PRODUCT_PATHNAME 			"Office"
!define INSTALL_ROOT_PATH           "C:\Program Files\MarsPanda\Fan"
!define INSTALL_APPEND_PATH         "\Office"
!define INSTALL_DEFALT_SETUPPATH    "${INSTALL_ROOT_PATH}${INSTALL_APPEND_PATH}"
!define EXE_NAME               		"扇子办公宝.exe"
!define PRODUCT_VERSION        		"1.0.9.0"
!define PRODUCT_PUBLISHER      		"四川火星熊猫科技有限公司"
!define PRODUCT_LEGAL          		"© 2025 火星熊猫"
!define INSTALL_OUTPUT_NAME    		"marspanda_office_109_250208_path_1.exe"
#安装包名字
Name "${PRODUCT_NAME}"

!define INSTALL_7Z_PATH 	   		"app.7z"
!define INSTALL_7Z_NAME 	   		"app.7z"
!define INSTALL_RES_PATH       		"skin.zip"
!define INSTALL_LICENCE_FILENAME    "licence.txt"
!define INSTALL_ICO 				"logo.ico"
!define UNINSTALL_ICO 				"uninst.ico"

!include "installer_ui.nsh"

OutFile "..\output\${INSTALL_OUTPUT_NAME}"

InstallDir "${INSTALL_DEFALT_SETUPPATH}"

Icon              "${INSTALL_ICO}"
UninstallIcon     "${UNINSTALL_ICO}"
