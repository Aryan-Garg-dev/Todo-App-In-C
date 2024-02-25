#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "commands.h"

char *users_db_loc = "../TODO-APP/database/user.db";
char *users_table = "users";
char *todos_db_loc = "../TODO-APP/database/todos.db";

//Two db's usersData, todosData
int authenticate_user(char *username, char *password){
    char *req_data[] = {"*"};
    char *columns[] = {"username", "password"};
    char *schemas[] = {"text", "text"};
    char *values[] = {username, password};
    int userExists = show_items(users_db_loc, users_table, 1, req_data, 2, columns, schemas, values, 0);
    if (!userExists){
        insert_values(users_db_loc, users_table, 2, columns, schemas, values);
    }
    return userExists;
}

int search_user(char *username){
    char *req_data[] = {"*"};
    char *columns[] = {"username"};
    char *schemas[] = {"text"};
    char *values[] = {username};
    return show_items(users_db_loc, users_table, 1, req_data, 1, columns, schemas, values, 0);
}

void create_todo_table(char *username){
    char *columns[] = {"title", "description", "deadline", "completed"};
    char *schemas[] = {"text", "text", "text", "text"};
    char *properties[] = {"NOT NULL", "", "", "NOT NULL"};
    create_table(todos_db_loc, username, 4, columns, schemas, properties);
}

int post_todo(char *username, char *title, char *description, char *deadline, char *completed){
    char *columns[] = {"title", "description", "deadline", "completed"};
    char *schemas[] = {"text", "text", "text", "text"};
    char *values[] = {title, description, deadline, completed};
    return insert_values(todos_db_loc, username, 4, columns, schemas, values);
}

void echo_all_todos(char *username){
    show_all(todos_db_loc, username);
}

void echo_todo_by_param(char *username, char *param, char *value){
    char *req_data[] = {"*"};
    char *schema[] = {"text"};
    char *columns[] = {param};
    char *values[] = {value};
    show_items(todos_db_loc, username, 1, req_data, 1, columns, schema, values, 1);
}
// param -> title/completed

void mark_all_complete(char *username){
    char *columns[] = {"completed"};
    char *schema[] = {"text"};
    char *value[] = {"No"};
    update_items(todos_db_loc, username, "completed", "text", "Yes", 1, columns, schema, value);
}

void mark_complete_by_id(char *username, char *ID){
    char *columns[] = {"id"};
    char *schema[] = {"int"};
    char *value[] = {ID};
    update_items(todos_db_loc, username, "completed", "text", "Yes", 1, columns, schema, value);
}

void delete_all_todos(char *username){
    delete_all(todos_db_loc, username);
}

void delete_todo_by_param(char *username, char *param, char *value){
    char *columns[] = {param};
    char *schema[] = {"text"};
    char *values[] = {value};
    delete_items(todos_db_loc, username, 1, columns, schema, values);
}

void delete_todo_by_id(char *username, char *ID){
    char *columns[] = {"id"};
    char *schema[] = {"int"};
    char *values[] = {ID};
    delete_items(todos_db_loc, username, 1, columns, schema, values);
}
