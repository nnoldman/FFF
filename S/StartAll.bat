cd .\bin\Debug
taskkill /f /im appcenter.exe
taskkill /f /im appgame.exe 
start appcenter
start appgame serverID=1
pause
