# A script to run the .bat file from a cmd 
cmd.exe /C "$(wslpath -w build.bat)"
# Run the main.exe from cmd
cmd.exe /C "$(wslpath -w main.exe)"
``` 