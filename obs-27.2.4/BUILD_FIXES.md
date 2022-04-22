# OBS Build Fixes

If your default build of OBS fails then you might try the following fixes.

# Windows

Replace the contents of `CI\install-script-win.cmd` with the following content:

```cmd
set CEF_VERSION=4638
if exist dependencies2019.zip (curl -kLO https://cdn-fastly.obsproject.com/downloads/dependencies2019.zip -f --retry 5 -z dependencies2019.zip) else (curl -kLO https://cdn-fastly.obsproject.com/downloads/dependencies2019.zip -f --retry 5 -C -)
if exist vlc.zip (curl -kLO https://cdn-fastly.obsproject.com/downloads/vlc.zip -f --retry 5 -z vlc.zip) else (curl -kLO https://cdn-fastly.obsproject.com/downloads/vlc.zip -f --retry 5 -C -)
if exist cef_binary_%CEF_VERSION%_windows_x86.zip (curl -kLO https://cdn-fastly.obsproject.com/downloads/cef_binary_%CEF_VERSION%_windows_x86.zip -f --retry 5 -z cef_binary_%CEF_VERSION%_windows_x86.zip) else (curl -kLO https://cdn-fastly.obsproject.com/downloads/cef_binary_%CEF_VERSION%_windows_x86.zip -f --retry 5 -C -)
if exist cef_binary_%CEF_VERSION%_windows_x64.zip (curl -kLO https://cdn-fastly.obsproject.com/downloads/cef_binary_%CEF_VERSION%_windows_x64.zip -f --retry 5 -z cef_binary_%CEF_VERSION%_windows_x64.zip) else (curl -kLO https://cdn-fastly.obsproject.com/downloads/cef_binary_%CEF_VERSION%_windows_x64.zip -f --retry 5 -C -)
7z x dependencies2019.zip -odependencies2019
7z x vlc.zip -ovlc
7z x cef_binary_%CEF_VERSION%_windows_x86.zip -oCEF_32
7z x cef_binary_%CEF_VERSION%_windows_x64.zip -oCEF_64
set DepsPath32=%CD%\dependencies2019\win32
set DepsPath64=%CD%\dependencies2019\win64
set VLCPath=%CD%\vlc
set QTDIR32=C:\QtDep\5.15.2\msvc2019
set QTDIR64=C:\QtDep\5.15.2\msvc2019_64
set CEF_32=%CD%\CEF_32
set CEF_64=%CD%\CEF_64
set build_config=RelWithDebInfo
set VIRTUALCAM-GUID=A3FCE0F5-3493-419F-958A-ABA1250EC20B
mkdir build build32 build64
if "%TWITCH-CLIENTID%"=="$(twitch_clientid)" (
cd ./build32
cmake -G "Visual Studio 16 2019" -A Win32 -DCMAKE_SYSTEM_VERSION=10.0 -DCOPIED_DEPENDENCIES=false -DCOPY_DEPENDENCIES=true -DENABLE_VLC=ON -DCOMPILE_D3D12_HOOK=true -DBUILD_BROWSER=true -DCEF_ROOT_DIR="%CEF_32%" -DVIRTUALCAM_GUID="%VIRTUALCAM-GUID%" ..
cd ../build64
cmake -G "Visual Studio 16 2019" -A x64 -DCMAKE_SYSTEM_VERSION=10.0 -DCOPIED_DEPENDENCIES=false -DCOPY_DEPENDENCIES=true -DENABLE_VLC=ON -DCOMPILE_D3D12_HOOK=true -DBUILD_BROWSER=true -DCEF_ROOT_DIR="%CEF_64%" -DVIRTUALCAM_GUID="%VIRTUALCAM-GUID%" ..
) else (
cd ./build32
cmake -G "Visual Studio 16 2019" -A Win32 -DCMAKE_SYSTEM_VERSION=10.0 -DCOPIED_DEPENDENCIES=false -DCOPY_DEPENDENCIES=true -DENABLE_VLC=ON -DCOMPILE_D3D12_HOOK=true -DBUILD_BROWSER=true -DCEF_ROOT_DIR="%CEF_32%" -DTWITCH_CLIENTID="%TWITCH-CLIENTID%" -DTWITCH_HASH="%TWITCH-HASH%" -DRESTREAM_CLIENTID="%RESTREAM-CLIENTID%" -DRESTREAM_HASH="%RESTREAM-HASH%" -DVIRTUALCAM_GUID="%VIRTUALCAM-GUID%" ..
cd ../build64
cmake -G "Visual Studio 16 2019" -A x64 -DCMAKE_SYSTEM_VERSION=10.0 -DCOPIED_DEPENDENCIES=false -DCOPY_DEPENDENCIES=true -DENABLE_VLC=ON -DCOMPILE_D3D12_HOOK=true -DBUILD_BROWSER=true -DCEF_ROOT_DIR="%CEF_64%" -DTWITCH_CLIENTID="%TWITCH-CLIENTID%" -DTWITCH_HASH="%TWITCH-HASH%"  -DRESTREAM_CLIENTID="%RESTREAM-CLIENTID%" -DRESTREAM_HASH="%RESTREAM-HASH%" -DVIRTUALCAM_GUID="%VIRTUALCAM-GUID%" ..
)
cd ..
```

Replace the contents of `CI\install-qt-win.cmd` with the following content:

```cmd
if exist Qt_5.15.2.7z (curl -kLO https://cdn-fastly.obsproject.com/downloads/Qt_5.15.2.7z -f --retry 5 -z Qt_5.15.2.7z) else (curl -kLO https://cdn-fastly.obsproject.com/downloads/Qt_5.15.2.7z -f --retry 5 -C -)
7z x Qt_5.15.2.7z -oQt
xcopy /E Qt\ C:\QtDep\
```

Replace the contents of `CI\before-deploy-win.cmd` with the following content:

```cmd
robocopy .\build32\rundir\Release .\build\ /E /XF .gitignore
robocopy .\build64\rundir\Release .\build\ /E /XC /XN /XO /XF .gitignore
7z a build.zip .\build\*
```