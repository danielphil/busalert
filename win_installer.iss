; Script generated by the Inno Script Studio Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Edinburgh Buses"
#define MyAppVersion "0.1.1"
#define MyAppPublisher "Daniel Phillips"
#define MyAppURL "https://github.com/danielphil/busalert/"
#define MyAppExeName "busalert.exe"
#define VCRedist "vcredist_x86.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{75C3948E-7BD5-4B4D-930F-3ACBB1C4E662}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
LicenseFile=LICENSE
OutputBaseFilename=setup
Compression=lzma
SolidCompression=yes
OutputDir=build\Installer

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "build\output\{#VCRedist}"; DestDir: {tmp}; Flags: deleteafterinstall

Source: "build\output\busalert.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\output\icudt53.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\output\icuin53.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\output\icuuc53.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\output\qt_ca.qm"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\output\qt_cs.qm"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\output\qt_de.qm"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\output\qt_fi.qm"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\output\qt_hu.qm"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\output\qt_it.qm"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\output\qt_ja.qm"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\output\qt_lv.qm"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\output\qt_ru.qm"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\output\qt_sk.qm"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\output\qt_uk.qm"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\output\Qt5Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\output\Qt5Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\output\Qt5Network.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\output\Qt5Svg.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\output\Qt5Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\output\bearer\*"; DestDir: "{app}\bearer"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "build\output\iconengines\*"; DestDir: "{app}\iconengines"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "build\output\imageformats\*"; DestDir: "{app}\imageformats"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "build\output\platforms\*"; DestDir: "{app}\platforms"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: {tmp}\{#VCRedist}; Parameters: "/passive /norestart"; StatusMsg: "Installing MSVC 2013 Runtime..."
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent
