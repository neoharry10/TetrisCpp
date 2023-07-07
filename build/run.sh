# A script to run the .bat file from a cmd 
cmd.exe /C "$(wslpath -w build.bat)"