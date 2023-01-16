#include <iostream>
#include <sqlite3.h>
#include <cstdio>


void main_menu_options();
void add_record();
void search_record();
void show_records();
void update_record();
void delete_record();
int create_database();
void create_client_table(sqlite3* &DB);
void insert_client(sqlite3* &DB);

using namespace std;

static int callback(void* data, int argc, char** argv, char** azColName){
    int i;
//    fprintf(stderr, "%s: ", (const char*)data);
    printf("\n");

    for (i = 0; i< argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main() {
//    main_menu_options();
    int exit;
    sqlite3 *DB = nullptr;
    string query = "SELECT * FROM CLIENT;";
    exit = create_database();
    if (exit){
        cout << "Database opened" << endl;
        sqlite3_open("bank_record", &DB);
    }
    else{
        cout << "Error database" << endl;
    }

    cout << "\n";

    create_client_table(DB);

    cout << "\n";

    insert_client(DB);

    cout << "\n" << endl;

    sqlite3_exec(DB, query.c_str(), callback, nullptr, nullptr);

    sqlite3_close(DB);
    return 0;
}

void main_menu_options(){
    // Displays the main menu when the system is initiated.
    bool program_controler = true;
    int option;
    while (program_controler) {
        system("clear");
        printf("\n\t         Bank System Information\n");
        printf("\n\t========================================\n");
        printf("\n\tChoose between the options below:\n");
        printf("\t1. Add record\n");
        printf("\t2. Search record\n");
        printf("\t3. Show records\n");
        printf("\t4. Update record\n");
        printf("\t5. Delete record\n");
        printf("\t6. Quit\n");
        printf("\tOption: ");
        if (!(cin >> option)) {
            cout << "\nInvalid option. Try again." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (option) {
            case 1: {
                add_record();
                break;
            }
            case 2: {
                search_record();
                break;
            }
            case 3: {
                show_records();
                break;
            }
            case 4: {
                update_record();
                break;
            }
            case 5: {
                delete_record();
                break;
            }
            case 6: {
                printf("Have a great day!");
                program_controler = false;
                break;
            }
            default: {
                system("clear");
                printf("\n\tThis is not a proper option.");
                printf("\n\tPress Enter to go back to menu");
                cin.get();
                continue;
            }
        }
    }
}
void add_record(){
    //Client menu.
    //This menu has options regarding the client information. It will allow an employee to add, edit, and delete a
    //client. It is linked to the client table in the database.
    bool program_controler = true;
    string fname, lname, address;
    int age;
    float balance;
    while (program_controler) {
        system("clear");
        printf("\n\t         Adding new client\n");
        printf("\n\t=================================\n");
        printf("\n\tEnter the following information\n");
        printf("\tFirst Name: ");
        getline(cin,fname);
        printf("\n\tLast Name: ");
        getline(cin,lname);
        printf("\n\tAddress: ");
        getline(cin,address);
        printf("\n\tAge: ");
        cin >> age;
        printf("\n\tBalance: ");
        cin >> balance;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        printf("\n\tAccount created successfully!");
        printf("\n\tPress Enter to go back to menu");
        cin.get();
        program_controler = false;
    }
}
void search_record(){
    //Booking menu.
    //This menu has the reservations options. It will allow an employee to create, edit, and delete a
    //reservation. It is linked to the reservation table in the database.
    bool program_controler = true;
    int option;
    while (program_controler) {
        system("clear");
        printf("\n\t           Booking Menu\n");
        printf("\n\t=================================\n");
        printf("\n\tChoose between the options below:\n");
        printf("\t1. Make a new reservation\n");
        printf("\t2. Edit a reservation\n");
        printf("\t3. Cancel a reservation\n");
        printf("\t4. Exit\n");
        printf("\tOption: ");
        if (!(cin >> option)) {
            cout << "\nInvalid option. Try again." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (option) {
            case 1: {
                printf("Making a new reservation");
                break;
            }
            case 2: {
                printf("Editing a reservation");
                break;
            }
            case 3: {
                printf("Canceling a reservation");
                break;
            }
            case 4: {
                program_controler = false;
                break;
            }
            default: {
                printf("\nThis is not a proper option.");
                printf("\nPress Enter to go back to client menu");
                cin.get();
                continue;
            }
        }
    }
}
void show_records(){
    //Flights menu.
    //This menu has the flight options. It will allow an admin to create, edit, and delete a
    //flight. This menu will be protected by password. It is linked to the flight table in the database.
    bool program_controler = true;
    int option;
    while (program_controler) {
        system("clear");
        printf("\n\t           Flight Menu\n");
        printf("\n\t=================================\n");
        printf("\n\tChoose between the options below:\n");
        printf("\t1. Add a new flight\n");
        printf("\t2. Edit an existing flight\n");
        printf("\t3. Delete a flight\n");
        printf("\t4. Exit\n");
        printf("\tOption: ");
        if (!(cin >> option)) {
            cout << "\nInvalid option. Try again." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (option) {
            case 1: {
                printf("Adding a new flight");
                break;
            }
            case 2: {
                printf("Editing an existing flight");
                break;
            }
            case 3: {
                printf("Deleting a flight");
                break;
            }
            case 4: {
                program_controler = false;
                break;
            }
            default: {
                printf("\nThis is not a proper option.");
                printf("\nPress Enter to go back to client menu");
                cin.get();
                continue;
            }
        }
    }
}
void update_record(){}
void delete_record(){}
int create_database(){
    int exit;
    sqlite3* DB;
    exit = sqlite3_open("bank_record", &DB);
    if (exit) {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        return 0;
    }
    else{
        sqlite3_close(DB);
        return -1;
    }
}
void create_client_table(sqlite3* &DB){
    int exit;
    char* messageError;
    const char *sql;
    sql = "CREATE TABLE CLIENT("
          "PERSON_ID INTEGER PRIMARY KEY, "
          "FIRST_NAME          TEXT NOT NULL, "
          "LAST_NAME          TEXT NOT NULL, "
          "AGE            INT  NOT NULL, "
          "ADDRESS        CHAR(50) NOT NULL, "
          "BALANCE        MONEY NOT NULL );";
    exit = sqlite3_exec(DB, sql, nullptr, nullptr, &messageError);
    if(exit != SQLITE_OK) {
        cerr << "Error creating table " << sqlite3_errmsg(DB) << endl;
        sqlite3_free(messageError);
    }
    else {
        cout << "Table Created Successfully" << endl;
    }
}
void insert_client(sqlite3* &DB){
    char* error_message;
    int age, exit;
    string first_name, last_name, address;
    float balance = 0;
    printf("First Name: ");
    getline(cin, first_name);
//    cin >> first_name;
    printf("Last Name: ");
    getline(cin, last_name);
//    cin >> last_name;
    printf("Age: ");
    cin >> age;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    printf("Address: ");
    getline(cin, address);
//    cin >> address;
    printf("Balance: ");
    cin >> balance;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    string sql;
    sql = "INSERT INTO CLIENT (FIRST_NAME,LAST_NAME,AGE,ADDRESS,BALANCE) VALUES( '" + first_name + "', '" + last_name + "', " + to_string(age) + ", '" + address + "', " +
          to_string(balance) + ");";

    exit = sqlite3_exec(DB, sql.c_str(), nullptr, nullptr, &error_message);;

    if(exit != SQLITE_OK) {
        cerr << "Error Insert " << sqlite3_errmsg(DB) << endl;
        sqlite3_free(error_message);
    }
    else {
        cout << "Records created successfully" << endl;
    }
}
