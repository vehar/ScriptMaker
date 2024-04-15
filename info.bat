::This batch file prints the current date and time, 
::along with the name of the current Git branch, 
::to a file called log.txt. It then appends 
::the last 10 commit messages and hashes to the same file.


@echo off

echo BUILD DATE: %date% %time% Branch: >> log.txt
git rev-parse --abbrev-ref HEAD >> log.txt
git log -10 --oneline >> log.txt


pause