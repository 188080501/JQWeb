cd /d "%~dp0" || (
    echo [ERROR] Failed to enter script directory: %~dp0
    exit /b 1
)
cd /d "..\..\..\build\WebAssembly_Qt_6_8_*_single_threaded-Release\JQSpeed\JQSpeedClient" || (
    echo [ERROR] Failed to enter wasm build directory.
    exit /b 1
)

ping -n 1 10.0.1.225 >nul
if %errorlevel%==0 (
    scp JQSpeed.wasm jason@10.0.1.225:~/web/JQSpeed
    scp JQSpeed.js jason@10.0.1.225:~/web/JQSpeed
    scp qtloader.js jason@10.0.1.225:~/web/JQSpeed
    scp qtlogo.svg jason@10.0.1.225:~/web/JQSpeed
)

cd /d "%~dp0" || (
    echo [ERROR] Failed to enter script directory: %~dp0
    exit /b 1
)
cd /d "..\web" || (
    echo [ERROR] Failed to enter web directory.
    exit /b 1
)

ping -n 1 10.0.1.225 >nul
if %errorlevel%==0 (
    scp JQSpeed.html jason@10.0.1.225:~/web/JQSpeed
    scp manifest.json jason@10.0.1.225:~/web/JQSpeed
    scp favicon.ico jason@10.0.1.225:~/web/JQSpeed
)
