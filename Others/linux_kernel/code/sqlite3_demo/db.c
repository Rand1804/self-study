#include <stdio.h>
#include <stdlib.h>

#include <sqlite3.h>

#define DATABASE "stu.db"


int main(int argc, const char *argv[]) {
    sqlite3 *db;
    char *errmsg;

    if (sqlite3_open(DATABASE, &db) != SQLITE_OK) {
        printf("sqlite3_open: %s\n", sqlite3_errmsg(&db));
        exit(1);
    }

    printf("Open DATABASE success.\n");

    // create a table
    if (sqlite3_exec(db, 
        "CREATE TABLE stu(id interger, name str, score integer);",
        NULL,NULL, &errmsg) != SQLITE_OK) {
            printf("sqlite3_exec: %s\n", errmsg);
            exit(1);
    }

}