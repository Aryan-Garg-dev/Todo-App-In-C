/*FUNCTIONS FOR OPERATIONS WITH DATABASE*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3/sqlite3.h"

sqlite3 *db;

//CALLBACK
static int callback(void *data, int argc, char **argv, char **azColName){
   int i;   
   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

static int searchCallback(void *data, int argc, char **argv, char **azColName){
   int i;   
   int *found = (int *)data; 
   *found = 1; 
    // *found = 1; 
   return 0;
}

//CONNECT
//To connect to a database (db_loc -> filepath to directory where database is located)
int connect_to_database(char *db_loc){
    int rc;
    rc = sqlite3_open(db_loc, &db);
    return !rc;
}

//DISCONNECT
//To disconnect from a database
void disconnect_to_database(){
    sqlite3_close(db);
}

//CREATE
//To create tables in database
int create_table(char *db_loc, char *table_name, int size, char **columns, char **schemas, char **properties){
    char *sql;
    char *table_string;
    int connected = connect_to_database(db_loc);
    if (!connected){
        return 0;
    }
    sql = (char *)malloc(512 * sizeof(char)); 
    strcpy(sql, "CREATE TABLE ");
    strcat(sql, table_name);
    strcat(sql, " (ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,");

    table_string = (char *)malloc(512 * sizeof(char));
    strcpy(table_string, "");
    for (int i = 0; i < size; i++) {
        strcat(table_string, " ");
        strcat(table_string, columns[i]);
        strcat(table_string, " ");
        strcat(table_string, schemas[i]);
        strcat(table_string, " ");
        strcat(table_string, properties[i]);
        if (i != size-1) {
            strcat(table_string, ",");
        }
    }
    strcat(sql, table_string);
    strcat(sql, ");");

    int rc = sqlite3_exec(db, sql, NULL, 0, 0);

    free(sql);
    free(table_string);

    disconnect_to_database();

    if( rc != SQLITE_OK ){
        return 0;
    } else {
        return 1;
    }
}

//INSERT
//To insert value to table (valid for text <date, string, etc>, int)
int insert_values(char *db_loc, char *table_name, int size, char **columns, char **schemas, char **values){
    char *sql;
    char *zErrMsg = 0;
    int connected = connect_to_database(db_loc);
    if (!connected){
        return 0;
    }
    sql = (char *)malloc(512 * sizeof(char)); 
    strcpy(sql, "");
    strcat(sql, "INSERT INTO ");
    strcat(sql, table_name);
    strcat(sql, " (");
    for (int i = 0; i < size; i++){
        strcat(sql, " ");
        strcat(sql, columns[i]);
        if (i != size-1){
            strcat(sql, ",");
        }
    }
    strcat(sql, ") VALUES (");
    for (int i = 0; i < size; i++){
        strcat(sql, " ");
        if (stricmp(schemas[i], "TEXT") == 0){
            strcat(sql, "'");
            strcat(sql, values[i]);
            strcat(sql, "'");
        } else {
            strcat(sql, values[i]);
        }
        if (i != size - 1){
            strcat(sql, ",");
        }
    }
    strcat(sql, ");");
    
    int rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

    free(sql);

    disconnect_to_database();

    if( rc != SQLITE_OK ){
        return 0;
    } else {
        return 1;
    }

}

//SELECT
//IDEAS: store in string to print, store in struct for later use during runtime
int show_all(char *db_loc, char *table_name){
    char *sql;
    char *zErrMsg = 0;
    int connected = connect_to_database(db_loc);
    if (!connected){
        return 0;
    }

    sql = (char *)malloc(100*sizeof(char));
    strcpy(sql, "SELECT * from ");
    strcat(sql, table_name);
    strcat(sql, ";");
    int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    } else {
        return 1;
    }
    free(sql);
    disconnect_to_database();

}

//To get variable amount of items and variable query statement can be passed
int show_items(char *db_loc, char *table_name, int req_data_size, char **req_data, int query_size, char **columns, char **schema, char **values, int show){
    char *sql;
    char *zErrMsg;
    int connected = connect_to_database(db_loc);
    if (!connected){
        return 0;
    }

    sql = (char *)malloc(512*sizeof(char));

    strcpy(sql, "SELECT");
    for (int i = 0; i < req_data_size; i++){
        strcat(sql, " ");
        strcat(sql, req_data[i]);
        if (i != req_data_size-1){
            strcat(sql, ",");
        }
    }

    strcat(sql, " FROM ");
    strcat(sql, table_name);

    if (query_size>0){
        strcat(sql, " WHERE ");
        for (int i = 0; i < query_size; i++){
            strcat(sql, columns[i]);
            strcat(sql, " = ");
            if (stricmp(schema[i], "TEXT")==0){
                strcat(sql, "'");
                strcat(sql, values[i]);
                strcat(sql, "'");
            } else {
                strcat(sql, values[i]);
            }
            if (query_size > 1 && i != query_size-1){
                strcat(sql, " AND ");
            }
        }
    }
    int found = 0; 
    int rc;
    strcat(sql, ";");
    if (show){
        rc = sqlite3_exec(db, sql, callback, &found, &zErrMsg); 
    } else {
        rc = sqlite3_exec(db, sql, searchCallback, &found, &zErrMsg); 
    }

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    } else {
        if (!found) 
            return 0;
        else
            return 1;
    }
    free(sql);
    disconnect_to_database();    
}

//UPDATE
int update_items(char *db_loc, char *table_name, char *property_to_update, char *schema_of_property, char *updated_value, int query_size, char **columns, char **schema, char **values){
    char *sql;
    char *zErrMsg = 0;
    int connected = connect_to_database(db_loc);
    if (!connected){
        return 0;
    }

    sql = (char *)malloc(512*sizeof(char));
    strcpy(sql, "");
    strcat(sql, "UPDATE ");
    strcat(sql, table_name);
    strcat(sql, " SET ");
    strcat(sql, property_to_update);
    strcat(sql, " = ");
    if (stricmp(schema_of_property, "TEXT")==0){
        strcat(sql, "'");
        strcat(sql, updated_value);
        strcat(sql, "'");
    } else {
        strcat(sql, updated_value);
    }
    
    if (query_size>0){
        strcat(sql, " WHERE ");
        for (int i = 0; i < query_size; i++){
            strcat(sql, columns[i]);
            strcat(sql, " = ");
            if (stricmp(schema[i], "TEXT")==0){
                strcat(sql, "'");
                strcat(sql, values[i]);
                strcat(sql, "'");
            } else {
                strcat(sql, values[i]);
            }
            if (query_size > 1 && i != query_size-1){
                strcat(sql, " AND ");
            }
        }
    }

    strcat(sql, ";");

    int rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    } else {
        return 1;
    }
    free(sql);
    disconnect_to_database(); 
}

//DELETE
//To delete all the records present in that table
int delete_all(char *db_loc, char *table_name){
    char *sql;
    char *zErrMsg = 0;
    int connected = connect_to_database(db_loc);
    if (!connected){
        return 0;
    }

    sql = (char *)malloc(100*sizeof(char));
    strcpy(sql, "DELETE FROM ");
    strcat(sql, table_name);
    strcat(sql, " ");
    strcat(sql, "; UPDATE SQLITE_SEQUENCE SET SEQ=0 WHERE NAME = ");
    strcat(sql, "'");
    strcat(sql, table_name);
    strcat(sql, "';");

    int rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    } else {
        return 1;
    }
    free(sql);
    disconnect_to_database();
}

//To delete the records from that table which match the condtion
int delete_items(char *db_loc, char *table_name, int query_size, char **columns, char **schema, char **values){
    char *sql;
    char *zErrMsg = 0;
    int connected = connect_to_database(db_loc);
    if (!connected){
        return 0;
    }

    sql = (char *)malloc(512*sizeof(char));
    strcpy(sql, "DELETE FROM ");
    strcat(sql, table_name);
    
    if (query_size>0){
        strcat(sql, " WHERE");
        for (int i = 0; i < query_size; i++){
            strcat(sql, columns[i]);
            strcat(sql, " = ");
            if (stricmp(schema[i], "TEXT")==0){
                strcat(sql, "'");
                strcat(sql, values[i]);
                strcat(sql, "'");
            } else {
                strcat(sql, values[i]);
            }
            if (query_size > 1 && i != query_size-1){
                strcat(sql, " AND ");
            }
        }
    }
    strcat(sql, ";");


    int rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    } else {
        return 1;
    }

    free(sql);
    disconnect_to_database(); 
}


