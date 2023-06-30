cd  %~dp0
cd "..\..\..\build-JQWeb-WebAssembly_Qt_6_5_*_single_threaded-Release\JQClock"

ping -n 1 10.0.1.225 >nul
if %errorlevel%==0 (
    scp JQClock.wasm jason@10.0.1.225:~/web/JQClock
    scp JQClock.js jason@10.0.1.225:~/web/JQClock
    scp qtloader.js jason@10.0.1.225:~/web/JQClock
    scp qtlogo.svg jason@10.0.1.225:~/web/JQClock
)

cd  %~dp0
cd "..\web"

ping -n 1 10.0.1.225 >nul
if %errorlevel%==0 (
    scp JQClock.html jason@10.0.1.225:~/web/JQClock
    scp manifest.json jason@10.0.1.225:~/web/JQClock
    scp favicon.ico jason@10.0.1.225:~/web/JQClock
)
