#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "matrix.h"

// Function which returns the length of a char, useful in the last part of the program to stop if we go further than the end of the word
int len_str(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        i += 1;
    }
    return i;
}

int main(int argc, char *argv[]){

    // Number of arguments must be equal to 2 
    if (argc!=2){
        fprintf(stderr, "Too much or not enough arguments\n");
    }

    FILE* automate; // Declaration of automate as a file
    char buf[256]; // Buffer will be used to save the informations read
    automate=fopen(argv[1],"rb"); // Opening the file which is the second argument of the command - r for reading the file and b because it is a binary file

    if (automate == NULL){
        fprintf(stderr, "Error while opening the file\n");
        exit(EXIT_FAILURE);
    } else {
        printf("File %s correctly read. Please enter your inputs. \n", argv[1]);
    }

    // Recovery of the number of states of the automaton
    int n=0;
    fgets(buf,256,automate); // Reading the first line of the file in order to get the numer of states of the file
    n=atoi(&buf[1]); // Number of states is the second information read on the first line. 
    // We use atoi to get the number of states in all cases, even if the number of states is superior or equal to 10

    // printf("%i\n",n);

    // Creation and filling of the actions matrix
    matrix actions=createMatrix(n,128); // For each state we'll have one line of the matrix dedicated to stock the actions of each caracter
    matrixZeros(actions); // Initialisation of the matrix with zeros
    
    for (int i=0;i<n;i++){ // Realization of the loop for each state
        for (int j=0;j<=127;j++){ // Realization of the loop for each caracter, which is ASCII code is beetween 0 and 127 included
            actions.cells[i][j]=fgetc(automate); // We read one caracter then stocked in the actions matrix as previously explained 
            // All the actions values are situated in the same line so we don't need to change line
        }
    } 

    // printMatrix(actions);

    fgetc(automate); // After the action line, we change line so we must read the caracter corresponding

    char reduced1[n]; // we have n octets who represent the first component of reduced, we initialize a char to stock those datas

    for (int i = 0; i<n; i++){ // for each state, we read the value of the first component of reduced
        reduced1[i]=fgetc(automate);
    }

    fgetc(automate); // After reading the first components of reduced, we change line so we must read the caracter corresponding

    char reduced2[n];  // we have n octets who represent the second component of reduced, we initialize a char to stock those datas

    for (int i = 0; i<n; i++){ // for each state, we read the value of the second component of reduced
        reduced2[i]=fgetc(automate);
    }

    fgetc(automate);  // After reading the second components of reduced, we change line so we must read the caracter corresponding

    char bufShift[3]; // initialization of a buffer to stock a three-octets sequence

    matrix shift = createMatrix(n,128); // Creation of a big matrix to stock all the values of the partiel function 'decale'

    matrixZeros(shift); // Initialization of the matrix with zeros

    fread(bufShift,sizeof(char),3,automate); // we are interested in reading a sequence of three octets, so we read the first three ones

    while ((bufShift[0]!='\255') && (bufShift[1]!='\255') && (bufShift[2]!='\255')){ // Stop condition is a sequence of three '/255', so when we read this sequence, the loop is stop
        int s = bufShift[0]; // first argument of 'decale' 
        int c = bufShift[1]; // second argument of 'decale'
        shift.cells[s][c] = bufShift[2]; // value of 'decale' for (s,c)
        fread(bufShift,sizeof(char),3,automate); // reading of the next three-octets sequence
    }

    // printMatrix(shift);
    
    char bufBranching[3]; // initialization of a buffer to stock a three-octets sequence

    matrix branching=createMatrix(n,128); // Creation of a big matrix to stock all the values of the partiel function 'decale'

    matrixZeros(branching); // Initialization of the matrix with zeros

    fread(bufBranching,sizeof(char),3,automate); // we are interested in reading a sequence of three octets, so we read the first three ones

    while ((bufBranching[0]!='\255') && (bufBranching[1]!='\255') && (bufBranching[2]!='\255')) { // Stop condition is a sequence of three '/255', so when we read this sequence, the loop is stop
        int s = bufBranching[0]; // first argument of 'decale' 
        int A = bufBranching[1]; // second argument of 'decale'
        branching.cells[s][A] = bufBranching[2]; // value of 'decale' for (s,c)
        fread(bufBranching,sizeof(char),3,automate); // reading of the next three-octets sequence
    }

    // printMatrix(branching);

    // Recovery of user's inputs
    char userEntry[256]="";  // initialization of a char in order to stock the input

    char c; // declaration of a char 

    // Getting the information of the entries of the user, which will be stocked in the char c
    fgets(userEntry,256,stdin); 

    sscanf(userEntry,"%c",&c);

    stack states = emptyStack(); // creation of an empty stack which will contain the states

    push(&states,0); // first state is 0

    int a=0; // Variable used to go through the loop

    // We use a variable 'check' in order to stop the loop while it will change to 1 (case Accepted or Rejected)
    int check=0; 

    while (a <= len_str(userEntry) && check != 1){ //Loop will stop at least when the char is entirely viewed
        int b = (int) userEntry[a]; // Character of the the entry
        int actualState = (states.first)->num; // actualState is the highest state of the stack

        if (actions.cells[actualState][b] == 0){ // Case rejected
            check=1;
            printf("Rejected\n");
            printf("Error at position %i\n",a+1); // Print the position of the error
            break;
        } 
        
        else if (actions.cells[actualState][b]==1){ // Case accepted
            check=1;
            printf("Accepted\n");
            break;
        } 
        
        else if (actions.cells[actualState][b]==2){ // Case 'decale'
            int stateToShift=shift.cells[actualState][b]; // Value of 'decale(s,c)'
            push(&states,stateToShift); // Pushing the value to shift on the top of the stack
            a++;
        } 
        
        else if (actions.cells[actualState][b]==3){ // Case 'branchement'
            int firstComponent = reduced1[actualState]; // Getting first component of reduced for the actual state
            int alpha = reduced2[actualState]; // Getting the second component of reduced for the actual state
            
            // Popping (firstComponent) times the stack
            for (int i = 0 ; i < firstComponent ; i++){
                pop(&states);
            }

            int newActualStates = (states.first)->num; // new actual state after the poppings
            int stateToBranch=branching.cells[newActualStates][alpha]; // a new state is to branch, corresponding to the new actual state and Alpha
            push(&states,stateToBranch); //Popping of 'branchement(s',A)
        } 
        
        else { // if we have a problem in action (value not equal to 0, 1, 2 or 3), we should print a message to inform
            printf("Error in action");
        }
    }

    fclose(automate); //Closing of the file

    return 0;
}