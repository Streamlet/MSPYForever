@Echo off
Echo 请输入版本号：
:Input
Set /p Version=
If "%Version%"=="" Goto Input

For /f "tokens=1-4 delims=." %%a In ("%Version%") Do (
    If "%%a"=="" Goto Input
    If "%%b"=="" Goto Input
    If "%%c"=="" Goto Input
    If "%%d"=="" Goto Input
)

For /f "tokens=1-2 delims=." %%a In ("%Version%") Do Set PVersion=%%a.%%b
For /f "tokens=1-3 delims=-/ " %%a In ('Date /T') Do Set DateString=%%a%%b%%c
For /f "tokens=1-2 delims=: " %%a In ('Time /T') Do Set TimeString=%%a%%b

Set ToolsDir=Tools
Set SourceDir=..
Set AppName=MSPYForever
Set ReleaseDir=Release\%AppName%_%Version%_%DateString%%TimeString%

Echo 正在编译...

"%~dp0%ToolsDir%\RCVersion.exe" /FileVersion:%Version:.=,% /ProductVersion:%PVersion:.=,%,0,0 /String:FileVersion=%Version% /String:ProductVersion=%PVersion% "%~dp0%SourceDir%\%AppName%\*.rc"

Set BuildCmd=C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.com
"%BuildCmd%" "%~dp0%SourceDir%\%AppName%.sln" /Rebuild "Release|Win32"
"%BuildCmd%" "%~dp0%SourceDir%\%AppName%.sln" /Rebuild "Release|x64"

Echo 正在组织文件...

Md "%~dp0%ReleaseDir%"

Md "%~dp0%ReleaseDir%\Win32"
Copy "%~dp0%SourceDir%\bin\Win32\Release\%AppName%.exe" "%~dp0%ReleaseDir%\Win32"
"%~dp0%ToolsDir%\xlZip.exe" /z "%~dp0%ReleaseDir%\Win32\*" "%~dp0%ReleaseDir%\%AppName%_%Version%_Win32_ForWin8.zip" /utf8
Md "%~dp0%ReleaseDir%\Win32\Files"
XCopy /E /Y "%~dp0%SourceDir%\Files\*" "%~dp0%ReleaseDir%\Win32\Files\"
RMDir /S /Q "%~dp0%ReleaseDir%\Win32\Files\Windows\System32"
"%~dp0%ToolsDir%\xlZip.exe" /z "%~dp0%ReleaseDir%\Win32\*" "%~dp0%ReleaseDir%\%AppName%_%Version%_Win32_ForWin81Win10Win11.zip" /utf8

Md "%~dp0%ReleaseDir%\x64"
Copy "%~dp0%SourceDir%\bin\x64\Release\%AppName%.exe" "%~dp0%ReleaseDir%\x64"
"%~dp0%ToolsDir%\xlZip.exe" /z "%~dp0%ReleaseDir%\x64\*" "%~dp0%ReleaseDir%\%AppName%_%Version%_x64_ForWin8.zip" /utf8
Md "%~dp0%ReleaseDir%\x64\Files"
XCopy /E /Y "%~dp0%SourceDir%\Files\*" "%~dp0%ReleaseDir%\x64\Files\"
"%~dp0%ToolsDir%\xlZip.exe" /z "%~dp0%ReleaseDir%\x64\*" "%~dp0%ReleaseDir%\%AppName%_%Version%_x64_ForWin81Win10Win11.zip" /utf8


Echo 生成结束

Pause
