#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "colors.h"
#include "app.h"

#define true 1
#define false 0
#define WELCOME printf(BWHT "\t\t<------Welcome to The TODO Application------>\t\t\n" reset);


const int maxNameLen = 99;
const int maxPassLen = 15; 

int EXIT = false;
const int ESC = 27;
const int ENTER = 13;
const int SPACE = 32;

char *username;
char *password;
char *displayName;

void getPassword(){
    char ch;
    int i = 0;
    while ((ch = getch()) != ENTER) {
        if (ch == 127 || ch == 8) {
            if (i != 0) {
                i--;
                printf("\b \b");
            }
        } else {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
}

void playSound(char *soundLoc, char *duration){
    //("powershell -c (New-Object Media.SoundPlayer '<example.wav>').Play(); Start-Sleep -s <duration>; Exit;")
    char *command = (char *)malloc(512*sizeof(char));
    strcpy(command, "powershell -c (New-Object Media.SoundPlayer '");
    strcat(command, soundLoc);
    strcat(command, "').Play(); Start-Sleep -s ");
    strcat(command, duration);
    strcat(command, "; Exit;");
    system(command);
    free(command);
}

void postTodo(char *username){
    WELCOME
    printf(BLU"Provide neccassary details to create a Todo\n"reset);
    char *title, *description, *deadline, *completed = "No";
    title = (char *)malloc(100 * sizeof(char));
    printf(BBLK"Enter Title:"reset" ");
    gets(title);

    description = (char *)malloc(512 * sizeof(char));
    printf(BBLK"Enter Description:"reset" ");
    gets(description);

    deadline = (char *)malloc(10 * sizeof(char));
    printf(BBLK"Enter Deadline (dd/mm/yy):"reset" ");
    gets(deadline);

    int todoPosted = post_todo(username, title, description, deadline, completed);
    system("cls||clear");
    if (todoPosted){
        printf(UYEL"Todo has been created successfully\n\n"reset);
    } else {
        printf(RED"Some Error has been encountered. Please Try Again.\n\n"reset);
    }
    free(title);
    free(description);
    free(deadline);
    free(completed);
}

void showTodos(char *username){
    WELCOME
    SELECT:
        printf(BBLU"Select any of the following options: \n"reset);
        printf(BLU"1. Show All.\n"reset);
        printf(BLU"2. Show not completed.\n"reset);
        printf(BLU"[X] Exit.\n"reset);
    char option = getch();
    system("cls||clear");
    switch(option){
        case '1':
            printf(UCYN"ALL TODOS:\n\n"reset);
            echo_all_todos(username);
            goto SELECT;
        case '2':
            printf(UCYN"NOT COMPLETED TODOS:\n\n"reset);
            echo_todo_by_param(username, "completed", "No");
            goto SELECT;
        case 'X':
        case 'x':
            system("cls||clear");
            WELCOME
            return;
        default:
            system("cls||clear"); 
            printf(URED"Invalid Key Entered. Please Try Again.\n\n"reset);
            showTodos(username);    
    }
}

void markComplete(char *username){
    char *ID = (char *)malloc(5*sizeof(char));
    WELCOME
    printf(UCYN"NOT COMPLETED TODOS:\n\n"reset);
    echo_todo_by_param(username, "completed", "No");
    printf(BBLU"Select any of the following option:-\n"reset);
    printf(BLU"1. Mark all complete\n"reset);
    printf(BLU"2. Select a todo\n"reset);
    printf(BLU"[X] Exit\n"reset);
    char option = getch();
    switch(option){
        case '1':
            mark_all_complete(username);
            system("cls||clear");
            WELCOME
            printf(UBLU"All Todos have been marked complete.\n"reset);
            echo_all_todos(username);
            printf(BLU"[X] Exit\n"reset);
            if (getch()){
                system("cls||clear");
                WELCOME
                break;
            }   
        case '2':
            printf(BWHT"Enter ID: "reset);
            gets(ID);   
            mark_complete_by_id(username, ID);
            system("cls||clear");
            WELCOME
            printf(UBLU"\nTodo has been marks completed successfully\n\n"reset);
            echo_todo_by_param(username, "id", ID);
            printf(BLU"[X] Exit\n"reset);
            if (getch()){
                system("cls||clear");
                WELCOME
                break;
            }
        case 'X':
        case 'x':
            system("cls||clear");
            WELCOME
            break;
        default:
            system("cls||clear");
            printf(URED"Invalid Key Entered. Please Try Again.\n\n"reset);
            markComplete(username);  
    }
}

void deleteTodos(char *username){
    char *ID = (char *)malloc(5*sizeof(char));
    WELCOME
    printf(UCYN"ALL TODOS:\n\n"reset);
    echo_all_todos(username);
    printf(BBLU"Select any of the following options: \n"reset);
    printf(BLU"1. Delete All\n"reset);
    printf(BLU"2. Delete completed todos\n"reset);
    printf(BLU"3. Select By Id\n"reset);
    printf(BLU"[X] Exit\n"reset);
    char option = getch();
    switch(option){
        case '1':
            delete_all_todos(username);
            printf(UBLU"All The Todos Have Been Successfully Deleted.\n\n"reset);
            printf(BLU"[X] Exit\n"reset);
            if (getch()){
                system("cls||clear");
                WELCOME
                break;
            } 
            break;
        case '2':
            delete_todo_by_param(username, "completed", "Yes");
            printf(UBLU"All The Completed Todos Have Been Successfully Deleted.\n\n"reset);
            echo_all_todos(username);
            printf(BLU"[X] Exit\n"reset);
            if (getch()){
                system("cls||clear");
                WELCOME
                break;
            }
            break;
        case '3':
            printf(BWHT"Enter ID: "reset);
            gets(ID);
            delete_todo_by_id(username, ID);
            printf(UBLU"The Selected Todo Has Been Successfully Deleted.\n\n"reset);
            echo_all_todos(username);
            printf(BLU"[X] Exit\n"reset);
            if (getch()){
                system("cls||clear");
                WELCOME
                break;
            }
            break;    
        case 'X':
        case 'x':
            system("cls||clear");
            WELCOME
            break;
        default:
            system("cls||clear");
            printf(URED"Invalid Key Entered. Please Try Again.\n\n"reset);
            deleteTodos(username);  
    }
}

void menu(char *username){
    char option;
    printf("\nSelect " RED "actions" reset" And ENTER corresponding " RED "number " reset ":-\n");
    printf(BLU"1. Add a todo: \n"reset);
    printf(BLU"2. Delete a todo: \n"reset);
    //delete_todo()
    //delete_all()
    printf(BLU"3. Mark a todo as complete: \n"reset);
    printf(BLU"4. Show my todos: \n"reset);
    printf(BLU"[X] Exit \n"reset);
    option = getch();
    system("cls||clear");
    switch (option){
        case 48+1:
            postTodo(username);
            menu(username);  
            break; 
        case 48+2:
            deleteTodos(username);
            menu(username);
            break;
        case 48+3:
            markComplete(username);
            menu(username);
            break;
        case 48+4:
            showTodos(username);
            menu(username);
            break;
        case 'X':
        case 'x':
            EXIT = 0;
            return;
        default:
            printf(URED"Invalid Key Entered. Try Again!\n\n"reset);
            menu(username);
    }
}

int main(){
    system("cls||clear");
    WELCOME
    printf(BCYN "With this TODO App, you can create todos, set deadlines, check completion status and update them.\n\n" reset);
    printf(MAG "If you are an existing user, Enter your original username and password, else just create a new one.\n" reset);
    getUserData: 
        printf(BLKB "USERNAME:" reset " ");
        username = (char *)malloc((maxNameLen+1)  * sizeof(char));
        gets(username);
        printf(BLKB "PASSWORD:" reset " ");
        password = (char *)malloc((maxPassLen+1) * sizeof(char));
        getPassword();
        int userExists = authenticate_user(username, password);
    if (userExists){
        playSound("C:/C_prog/My_Projects/TODO-APP/audio/bonus.wav", "1.5");
        system("cls||clear");
        WELCOME
        printf(UGRN "Welcome back, %s" reset " " UYEL "{*u*}\n" reset, username);
    } else {
        if (search_user(username)){
            playSound("C:/C_prog/My_Projects/TODO-APP/audio/jump_sound.wav", "1.5");
            printf(URED"\nUser already exits, the entered password is wrong.\n\n"reset);
            goto getUserData;   
        }
        playSound("C:/C_prog/My_Projects/TODO-APP/audio/bonus.wav", "1.5");
        system("cls||clear");
        WELCOME
        printf(UGRN "Congratulations, your account is activated" reset " " YEL ":)\n" reset);
        create_todo_table(username);
    }
    while (!EXIT){
        menu(username);
        EXIT = true;
        free(username);
        free(password);
    }
}