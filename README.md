# Unix-Shell
The repository aims to create a shell like unix shell including the && and history functionalities. The file can be compiled using: <br>
``` 
gcc shell.c
```
All the normal operations can be performed in this shell. The input is parsed into tokens and execvp system call is used to run the input commands.<br>
History feature of unix shell is also implemented. It can be called using the command:<br>
```
hist
```
Apart from looking at the history, we can also run the commands from history using:<br>
```
hist -n
```
where n represents an integer. hist -1 will run the most recent command.
