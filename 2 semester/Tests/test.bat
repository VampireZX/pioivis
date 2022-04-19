@echo off
@echo Test %2
@echo Test %2 >> result.txt
copy %2 maze.in.txt > nul
ConsoleApplication1.exe
timer %1 2000 65536 >> result.txt
check %2 %2.a maze.out.txt >> result.txt
if exist maze.in.txt del maze.in.txt
if exist maze.out.txt del maze.out.txt