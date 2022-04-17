// Credentials.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
* Main Program:     Credentail Database
* Author:           J. Barrett-Fetters
* Date:             April 3, 2022
* Purpose:          This is the Credential database. This database will replace the Credential text file that the Zoo Authentication Program is using.
*                   This program creates the database, table and inserts the data from the original text file. To use this database you will need to download SQLite from SQLite.org
*
* Modification History:
* 16 APRIL 2022
* Add missing comments with in the code
*
*/

#include <iostream>
#include <stdio.h>
#include <sqlite3.h>

using namespace std;

static int createDB(const char* dataBase); // delaring function createDB
static int createTable(const char* table); // delaring function createTable
static int inputData(const char* inputData); // delaring function enter data
static int selectData(const char* selectData); // delaring function to verify data was inputted
static int callback(void* NotUsed, int argc, char** argv, char** azColName);

int main()
{
    const char* dir = "C:\\Database\\Credentials.db"; // Database name and location
    sqlite3* db;
    createDB(dir); // calling to create create database using dir location
    createTable(dir); // calling to create table using the dir location
    inputData(dir); // calling to insert information into the table of the database
    selectData(dir); // calling the select data to verify information was inputted into the table

    return 0;
}

static int createDB(const char* dataBase) // Function to create database
{
    sqlite3* DB;
    int exit = 0; // set exit to 0

    exit = sqlite3_open(dataBase, &DB); // if it cannot open the database create the database

    if (exit)
    {
        cout<< "Can't open database: \n" << sqlite3_errmsg(DB); // error database cannot be opend
        return(0);
    }
    else
    {
        cout << "Opened database successfully! \n"; // output database was open
    }
    sqlite3_close(DB); //close database

   
}

static int createTable(const char* table) //Creating the database tables from the credential file
{
    sqlite3* DB;

    // Creates table
    string sql = "CREATE TABLE IF NOT EXISTS CREDENTIALS ("
        " USER_ID TEXT PRIMARY KEY," // title of the column "USER_ID" and set it to Primary Key
        " HASH_PASSWORD    TEXT NOT NULL," // title of column "HASH_PASSWORD"
        " PASSWORD         TEXT NOT NULL," // title of column "PASSWORD"
        " ROLE             TEXT NOT NULL);"; // title of column "ROLE"

    try
    {
        int exit = 0; // set exit to 0
        exit = sqlite3_open(table, &DB); // if it cannot open the database create the database

        char* messaggeError; //  messaggeError
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError); //Callback error 

        if (exit != SQLITE_OK) // exit does not equal SQLITE_OK, exit = 0, SQLITE_OK = 0
        {
            cout << "ERROR CREATE TABLE  " << endl; // Error Message
            sqlite3_free(messaggeError); //Error Message
        }
        else 
        {
            cout << "Table created Successfully" << endl; // Successful Message
        }
        sqlite3_close(DB); // Close Database
        
    }
    catch (const exception & e)
    {
        cerr << e.what();
    }

    return 0;
}

static int inputData(const char* inputData) // Populating Database with the data from the credential text file
{
    sqlite3* DB;
    char* messaggeError;
    
    int exit = sqlite3_open(inputData, &DB); // if it cannot open the database create the database

    // Inserts Data into the table
    string sql ("INSERT INTO CREDENTIALS(USER_ID,HASH_PASSWORD,PASSWORD,ROLE) VALUES('griffin.keyes','8227b47cadebdf91dc0e495902bc561e','alphabetsoup','zookeeper');"
        "INSERT INTO CREDENTIALS(USER_ID,HASH_PASSWORD,PASSWORD,ROLE) VALUES('rosario.dawson','8c90e3d118685deff1efda4195ea472a','animaldoctor','admin');"
        "INSERT INTO CREDENTIALS(USER_ID,HASH_PASSWORD,PASSWORD,ROLE) VALUES('bernie.gorilla','2034f6e32958647fdff75d265b455ebf','secretpassword','veterinarian');"
        "INSERT INTO CREDENTIALS(USER_ID,HASH_PASSWORD,PASSWORD,ROLE) VALUES('donald.monkey','03be096bd25e196ed167bf63c406a4c0','M0nk3ybusiness','zookeeper');"
        "INSERT INTO CREDENTIALS(USER_ID,HASH_PASSWORD,PASSWORD,ROLE) VALUES('jerome.grizzlybear','3adea92111e6307f8f2aae4721e77900','grizzly1234','veterinarian');"
        "INSERT INTO CREDENTIALS(USER_ID,HASH_PASSWORD,PASSWORD,ROLE) VALUES('bruce.grizzlybear','0d107d09f5bbe40cade3de5c71e9e9b7','letmein','admin');");
        
        
    // Open database, SQL to be evaluated, callback function, First argument to callback, error message written
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) // exit does not equal SQLITE_OK, exit = 0, SQLITE_OK = 0
    {
        cerr << "ERROR INSERT" << endl;
        sqlite3_free(messaggeError);
    }
    else
    { 
        cout << "Records created Successfully!" << endl;
    }
    return 0;
}

static int selectData(const char* selectData) // Test funtion verifying the data populated
{
    sqlite3* DB;
    char* messageError;

    string sql = "SELECT * FROM CREDENTIALS;"; //query to select data from the crednetial databaase

    int exit = sqlite3_open(selectData, &DB);
    /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
    exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);

    if (exit != SQLITE_OK) // exit does not equal SQLITE_OK, exit = 0, SQLITE_OK = 0
    {
        cerr << "Error in select Data function." << endl; //Erroe data not selected
        sqlite3_free(messageError);
    }
    else
        cout << "Records selected Successfully!" << endl;

    return 0;
}

// retrieve contents of database used by selectData()
/* argc: holds the number of results, argv: holds each value in array, azColName: holds each column returned in array, */
static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    for (int i = 0; i < argc; i++) 
    {
        // column name and value
        cout << azColName[i] << ": " << argv[i] << endl;
    }

    cout << endl;

    return 0;
}
