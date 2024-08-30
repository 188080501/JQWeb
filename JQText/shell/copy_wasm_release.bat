cd  %~dp0
cd "..\..\build\WebAssembly_Qt_6_7_*_single_threaded-Release\JQText"

ping -n 1 10.0.1.225 >nul
if %errorlevel%==0 (
    scp JQText.wasm jason@10.0.1.225:~/web/JQText
    scp JQText.js jason@10.0.1.225:~/web/JQText
    scp qtloader.js jason@10.0.1.225:~/web/JQText
    scp qtlogo.svg jason@10.0.1.225:~/web/JQText
)

cd  %~dp0
cd "..\web"

ping -n 1 10.0.1.225 >nul
if %errorlevel%==0 (
    scp JQText.html jason@10.0.1.225:~/web/JQText
    scp manifest.json jason@10.0.1.225:~/web/JQText
    scp favicon.ico jason@10.0.1.225:~/web/JQText
)
