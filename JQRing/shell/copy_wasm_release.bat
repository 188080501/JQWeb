cd /d "%~dp0" || (
    echo [ERROR] Failed to enter script directory: %~dp0
    exit /b 1
)
cd /d "..\..\build\WebAssembly_Qt_6_8_*_single_threaded-Release\JQRing" || (
    echo [ERROR] Failed to enter wasm build directory.
    exit /b 1
)

ping -n 1 10.0.1.225 >nul
if %errorlevel%==0 (
    scp JQRing.wasm jason@10.0.1.225:~/web/JQRing
    scp JQRing.js jason@10.0.1.225:~/web/JQRing
    scp qtloader.js jason@10.0.1.225:~/web/JQRing
    scp qtlogo.svg jason@10.0.1.225:~/web/JQRing
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
    scp JQRing.html jason@10.0.1.225:~/web/JQRing
    scp manifest.json jason@10.0.1.225:~/web/JQRing
    scp favicon.ico jason@10.0.1.225:~/web/JQRing
)
