// main.cpp
#include <sqlite3.h>
#include <iostream>
#include <stdio.h>

static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
  
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
  
    printf("\n");
    return 0;
}

int main()
{
    std::cout << "Sqlite version: " << sqlite3_libversion() << std::endl;
    int exit = 0;
    sqlite3* mydb;
    std::cout << sqlite3_open("test.db", &mydb) << std::endl;
    std::cout << "Database file:" << mydb << std::endl;
    
    std::string sql = "CREATE TABLE IF NOT EXISTS users(name TEXT, password TEXT, security_code TEXT);";
    char* message_error;
    exit = sqlite3_exec(mydb, sql.c_str(), NULL, 0, &message_error);

    std::cout << "Table created" << std::endl;
    
    sql = "INSERT INTO users VALUES('John', 'pword', 'dog';";
    std::string data("CALLBACK FUNCTION");
    int rc = sqlite3_exec(mydb, sql.c_str(), callback, (void*)data.c_str(), NULL);
    if (rc == SQLITE_OK) { std::cout << "OK" << std::endl; }
    std::cout << sqlite3_close(mydb);


    return 0;
}