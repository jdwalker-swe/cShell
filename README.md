# cShell
this is a simple linux shell written in C.

This program uses stdin to take input from user and tokenizes them into arguements so it can be then be read by linux system calls. Depending on the tokens read by stdin, different calls will be used. For example, if user inputs "ls -l" then execvp() will be called with the arguements passed. 

The program will also search for tokenized symbols like "!" , " | " , " > ", " < ", and " &" which implements the history, pipe, redirection, and foreground calls respectively.
