#include <stdio.h> 
#include <unistd.h>
#include <string.h>
#include <sys/types.h> // this was added to allow pid_t, maybe remove when copying to VM?
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_LINE 80 /* The maximum length command */

int main(void) {
    char *args[MAX_LINE/2 + 1]; /* command line arguments */ 
    char inputArray[MAX_LINE/2 + 1];
    int should_run = 1; /* flag to determine when to exit program */
    char exitArr[] = "exit\n";
    char history[MAX_LINE/2 + 1];
    char *fileNameArr[MAX_LINE/2 +1];
    history[0]= 0;
    int pipeArr[2];
    int s;
    char *argsTwo[MAX_LINE/2 + 1];

    pid_t pid;
    
    
    while (should_run){ 
        printf("mysh:~$ "); 
        fflush(stdout);
        int i=0;
        int waitCheck = 0;
        int explanationCheck=0;
        int outText = 0;
        int historyCheck=0;
        int pipeCheck = 0;
        int counter =0;
        

        // we dont use scanf since we dont have to specify amount of characters, i.e we could eneter more than MAX_LINE
        // we should use fgets to get stndin into array

       fgets(inputArray, MAX_LINE/2 +1, stdin);
           //printf("input: %s\n", inputArray);

       
       

        //check if we have "!!"
          char findTwo = '!';

    const char *ptrTwo = strchr(inputArray, findTwo);
        if(ptrTwo) {
            int index = ptrTwo - inputArray;
            //printf("index is : %d\n", index-1);
            //printf("array value now: %c\n", inputArray[index]);

            if(inputArray[index]== '!'){
         //printf("inside & check passed\n");
            inputArray[index]='\0';
            explanationCheck = 1;
            //printf("found a !\n");

            if(!history || !*history){
                printf("No commands in history.\n");
            }
            else{
               
                printf("%s\n", history);
            }
            
        
     }
                }
                







            //might delete and change char *tokens =strok(inputArray, " \n");

         
         


        //remove the newline that fgets put at the end of the array
        //inputArray[strlen(inputArray-1)] = '\0';

//check if user inputed '&'
        char find = '&';

    const char *ptr = strchr(inputArray, find);
        if(ptr) {
            int index = ptr - inputArray;
            //printf("index is : %d\n", index-1);
            //printf("array value now: %c\n", inputArray[index]);

            if(inputArray[index]== '&'){
         //printf("inside & check passed\n");
         
         inputArray[index]='\0';
         waitCheck = 1;
     }
                }




         char findThree = '>';

    const char *ptrThree = strchr(inputArray, findThree);
        if(ptrThree) {
            int index = ptrThree - inputArray;
            //printf("index is : %d\n", index-1);
            //printf("array value now: %c\n", inputArray[index]);

            if(inputArray[index]== '>'){
         //printf("inside & check passed\n");
         //printf("found a : >\n");
         //inputArray[index]='\0';
         outText = 1;
     }
                }



                char findFour = '<';

    const char *ptrFour = strchr(inputArray, findFour);
        if(ptrFour) {
            int index = ptrFour - inputArray;
            //printf("index is : %d\n", index-1);
            //printf("array value now: %c\n", inputArray[index]);

            if(inputArray[index]== '<'){
         
         //printf("found a : <\n");
         //inputArray[index]='\0';
         outText = 2;
     }
                }













        //check if user inputs "exit" to exit the shell
        if(strcmp(inputArray, exitArr)==0){
            //printf("in exit if statement now\n");
            should_run = 0;
            break;
        }

        if(explanationCheck==0){
             strcpy(history, inputArray);
         }





         char findFive = '>';

    const char *ptrFive = strchr(history, findFive);
        if(ptrFive) {
            int index = ptrFive - history;
            //printf("index is : %d\n", index-1);
            //printf("array value now: %c\n", inputArray[index]);

            if(history[index]== '>'){
        
         //printf("found a : >\n");
         //inputArray[index]='\0';
         historyCheck = 1;
     }
                }


         char findSix = '|';

    const char *ptrSix = strchr(inputArray, findSix);
        if(ptrSix) {
            int index = ptrSix - inputArray;
            //printf("index is : %d\n", index-1);
            //printf("array value now: %c\n", inputArray[index]);

            if(inputArray[index]== '|'){
       
         //printf("found a : | \n");
         //inputArray[index]='\0';
         pipeCheck = 1;
     }
                }

       

            
    //now we want to break inputArray into tokens
    //char* tokens = strtok(inputArray, " ");

    //we have now put string tokens into inputArray
    //we will now xfer those tokens into our main arguement array args

    
    
    if(explanationCheck==0){
        char *tokens = strtok(inputArray, " \n");
    
    

    while(tokens != NULL){

       

            args[i] = tokens;
           
            tokens = strtok(NULL, " \n");
        
            i++;

        
        
        

    }
   
    args[i] = NULL;
    }

//added to change tokenize with history array

    if(explanationCheck==1 || historyCheck==1){
        char *tokens = strtok(history, " \n");
    
    

    while(tokens != NULL){

       

            args[i] = tokens;
           
            tokens = strtok(NULL, " \n");
        
            i++;


    }
   
    args[i] = NULL;
    }


    while(args[++counter]!='\0');

    

    



 
    //printf("%s\n", args[0]);
   // printf("%s\n", args[1]);
    //printf("%s\n", args[2]);
     //printf("%s\n", args[3]);

     
     //printf("history: %s\n", history[0]);

    if(outText==1 || outText ==2 || historyCheck ==1){

        fileNameArr[0] = args[2];
     //printf("FIleNAMEARR : %s\n", fileNameArr[0]);
        args[1] = NULL;
        args[2] = NULL;

        
    }


 
    
  

     
     
    if(pipeCheck==0){


 pid = fork();
    if(pid < 0){
        printf("fork() failed \n");
        return 1;
    }
    else if(pid == 0){
        //printf("inside child with id: %d \n", pid);
            
            if(outText==1){
        int redirect = open(fileNameArr[0], O_CREAT | O_WRONLY, 0777);
        dup2(redirect,STDOUT_FILENO);
        close(redirect);
        }
         if(outText==2){
            //printf("outtext is 2 \n");
             int redirect = open(fileNameArr[0],O_RDONLY, 0777);
            dup2(redirect,STDIN_FILENO);
            close(redirect);


        }
           
           int result = execvp(args[0], args);
            //printf("%d\n", result);
       
        
    }
    else{
        //printf("inside parent with id: %d \n", pid);
        if(waitCheck==1){
            continue;
        }
        else{
            wait(NULL);
        }



    }

   
        
    }


    if(pipeCheck ==1){

    //printf("Size: %d\n", counter);
    if(counter <=3){
   // printf("%s\n", args[0]);
    //printf("%s\n", args[1]);
    //printf("%s\n", args[2]);
    argsTwo[0] = args[2];
     //printf("%s\n", argsTwo[0]);
    args[1] = NULL;
    args[2] = NULL;
    argsTwo[1]= NULL;

    }
    else{
        argsTwo[0] = args[3];
        argsTwo[1] = args[4];
        args[2] = NULL;
        args[3] = NULL;
         args[4] = NULL;
         argsTwo[2] = NULL;

    }
    
    




        pipe(pipeArr);
        pid = fork();

        if(pid ==0){
            //printf("inside left\n");
             //close(pipeArr[0]);
            dup2(pipeArr[1],STDOUT_FILENO);
            
            execvp(args[0],args);

        }
        pid = fork();
        if(pid==0){
            //printf("inside right\n");
            close(pipeArr[1]);
            dup2(pipeArr[0],STDIN_FILENO);
            execvp(argsTwo[0],argsTwo);
          
        }
        close(pipeArr[0]);
        close(pipeArr[1]);

        waitpid(-1,&s,0);
        waitpid(-1,&s,0);

    }
    

           //should_run =0;
     
        
        
      
       // should_run =0;
        /** After reading user input, the steps are:  
         * (1) fork a child process using fork()  
         * (2) the child process will invoke execvp()  
         * (3) parent will invoke wait() unless command included & 
         */
    }
    

return 0;
}