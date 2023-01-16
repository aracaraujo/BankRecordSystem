#include <iostream>
#include <sqlite3.h>
#include <cstdio>
#include <random>

void main_menu_options();
void search_record();
void show_records();
void update_record();
void delete_record();
int create_database();
void create_client_table();
void add_client();

namespace {
    std::random_device rd;
    std::mt19937 gen(rd());}

using namespace std;

static int callback(void* data, int argc, char** argv, char** azColName){
    int i;
//    fprintf(stderr, "%s: ", (const char*)data);
    printf("\n\t");

    for (i = 0; i< argc; i++){
        printf("%s = %s\n\t", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main() {
    int exit;
    // Creating the database and then if there's no issues it will open the database.
    string query = "SELECT * FROM CLIENT;";
    exit = create_database();
    if (exit){
        cout << "\n\tThe Database is Open" << endl;
    }
    else{
        cout << "\n\tError Database" << endl;
        printf("\n\tLaunch The Software Again.");
        cin.get();
        return -1;
    }
    // Creating CLIENT table. If the table already exists it will tell that the table is ready.
    create_client_table();

    system("clear");

    cout << "\n";

    main_menu_options();

    return 0;
}

void main_menu_options(){
    // Displays the main menu when the system is initiated.
    bool program_control = true;
    int option;
    while (program_control) {
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
                add_client();
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
                printf("\n\tHave a great day!");
                program_control = false;
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
void search_record(){
    //Booking menu.
    //This menu has the reservations options. It will allow an employee to create, edit, and delete a
    //reservation. It is linked to the reservation table in the database.
    bool program_control = true;
    int option;
    sqlite3 *DB = nullptr;
    sqlite3_open("bank_record", &DB);
    while (program_control) {
        system("clear");
        printf("\n\t           Search Record\n");
        printf("\n\t=================================\n");
        printf("\n\tChoose between the options below:\n");
        printf("\t1. Search by First Name\n");
        printf("\t2. Search by Last Name\n");
        printf("\t3. Search by ID\n");
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
                string first_name;
                printf("\n\tFirst Name: ");
                getline(cin,first_name);
                string query = "SELECT * FROM CLIENT WHERE FIRST_NAME='"+ first_name + "';";
                system("clear");
                sqlite3_exec(DB,query.c_str(), callback, nullptr, nullptr);
                printf("\n\tPress Enter to go back to client menu");
                cin.get();
                break;
            }
            case 2: {
                string last_name;
                printf("\n\tLast Name: ");
                getline(cin,last_name);
                string query = "SELECT * FROM CLIENT WHERE LAST_NAME='"+ last_name + "';";
                system("clear");
                sqlite3_exec(DB,query.c_str(), callback, nullptr, nullptr);
                printf("\n\tPress Enter to go back to client menu");
                cin.get();
                break;
            }
            case 3: {
                int client_id;
                printf("\n\tClient ID: ");
                cin >> client_id;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                string query = "SELECT * FROM CLIENT WHERE PERSON_ID="+ to_string(client_id) + ";";
                system("clear");
                sqlite3_exec(DB,query.c_str(), callback, nullptr, nullptr);
                printf("\n\tPress Enter to go back to client menu");
                cin.get();
                break;
            }
            case 4: {
                program_control = false;
                break;
            }
            default: {
                printf("\nThis is not a proper option.");
                printf("\nPress Enter to go back to the search menu");
                cin.get();
                continue;
            }
        }
    }
    sqlite3_close(DB);
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
void create_client_table(){
    sqlite3 *DB = nullptr;
    sqlite3_open("bank_record", &DB);
    int exit;
    char* messageError;
    const char *sql;
    sql = "CREATE TABLE CLIENT("
          "PERSON_ID INTEGER PRIMARY KEY NOT NULL, "
          "FIRST_NAME          TEXT NOT NULL, "
          "LAST_NAME          TEXT NOT NULL, "
          "AGE            INT  NOT NULL, "
          "ADDRESS        CHAR(50) NOT NULL, "
          "BALANCE        MONEY NOT NULL );";
    exit = sqlite3_exec(DB, sql, nullptr, nullptr, &messageError);
    if(exit != SQLITE_OK) {
        string answer = sqlite3_errmsg(DB);
        if(answer == "table CLIENT already exists"){
            cout << "\n\tCLIENT Table is ready." << endl;
        }else{
            system("clear");
            cerr << "\n\t" << sqlite3_errmsg(DB) << endl;
            sqlite3_free(messageError);
            printf("\n\tLaunch The Software Again.");
            cin.get();
        }
    }
    else {
        cout << "\n\tTable Created Successfully" << endl;
    }
    sqlite3_close(DB);
}
void add_client(){
    sqlite3 *DB = nullptr;
    sqlite3_open("bank_record", &DB);
    char* error_message;
    int client_id,age, exit;
    string first_name, last_name, address;
    float balance = 0;
    uniform_int_distribution<> dist(1000,9999);
    client_id = dist(gen);
    system("clear");
    printf("\n\t        New Client Information\n");
    printf("\n\t========================================\n");
    printf("\n\tClient ID: %d\n",client_id);
    printf("\n\tFirst Name: ");
    getline(cin, first_name);
    printf("\n\tLast Name: ");
    getline(cin, last_name);
    printf("\n\tAge: ");
    cin >> age;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    printf("\n\tAddress: ");
    getline(cin, address);
    printf("\n\tBalance: ");
    cin >> balance;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    string sql;
    sql = "INSERT INTO CLIENT (PERSON_ID,FIRST_NAME,LAST_NAME,AGE,ADDRESS,BALANCE) VALUES(" + to_string(client_id) + ", '" + first_name + "', '" + last_name + "', " + to_string(age) + ", '" + address + "', " +
          to_string(balance) + ");";

    exit = sqlite3_exec(DB, sql.c_str(), nullptr, nullptr, &error_message);

    if(exit != SQLITE_OK) {
        cerr << "Error Insert " << sqlite3_errmsg(DB) << endl;
        sqlite3_free(error_message);
    }
    else {
        system("clear");
        cout << "\n\tThe Following Record Was Created Successfully:" << endl;
        string query = "SELECT * FROM CLIENT WHERE PERSON_ID="+ to_string(client_id) + ";";
        sqlite3_exec(DB,query.c_str(), callback, nullptr, nullptr);
    }
    printf("\n\tPress Enter to go back to client menu");
    cin.get();
    sqlite3_close(DB);
}

