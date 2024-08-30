cd  %~dp0
cd "..\..\build\WebAssembly_Qt_6_7_*_single_threaded-Release\JQRing"

ping -n 1 10.0.1.225 >nul
if %errorlevel%==0 (
    scp JQRing.wasm jason@10.0.1.225:~/web/JQRing
    scp JQRing.js jason@10.0.1.225:~/web/JQRing
    scp qtloader.js jason@10.0.1.225:~/web/JQRing
    scp qtlogo.svg jason@10.0.1.225:~/web/JQRing
)

cd  %~dp0
cd "..\web"

ping -n 1 10.0.1.225 >nul
if %errorlevel%==0 (
    scp JQRing.html jason@10.0.1.225:~/web/JQRing
    scp manifest.json jason@10.0.1.225:~/web/JQRing
    scp favicon.ico jason@10.0.1.225:~/web/JQRing
)
