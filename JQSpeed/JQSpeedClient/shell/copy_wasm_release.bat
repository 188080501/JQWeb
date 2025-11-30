cd  %~dp0
cd "..\..\..\build\WebAssembly_Qt_6_7_*_single_threaded-Release\JQSpeed\JQSpeedClient"

ping -n 1 10.0.1.225 >nul
if %errorlevel%==0 (
    scp JQSpeed.wasm jason@10.0.1.225:~/web/JQSpeed
    scp JQSpeed.js jason@10.0.1.225:~/web/JQSpeed
    scp qtloader.js jason@10.0.1.225:~/web/JQSpeed
    scp qtlogo.svg jason@10.0.1.225:~/web/JQSpeed
)

cd  %~dp0
cd "..\web"

ping -n 1 10.0.1.225 >nul
if %errorlevel%==0 (
    scp JQSpeed.html jason@10.0.1.225:~/web/JQSpeed
    scp manifest.json jason@10.0.1.225:~/web/JQSpeed
    scp favicon.ico jason@10.0.1.225:~/web/JQSpeed
)
