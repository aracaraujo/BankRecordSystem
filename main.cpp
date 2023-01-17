#include <iostream>
#include <sqlite3.h>
#include <cstdio>
#include <random>

void main_menu_options();
void search_client();
void show_all_clients();
void update_client();
void delete_client();
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
        printf("\t1. Add Client\n");
        printf("\t2. Update Client\n");
        printf("\t3. Delete Client\n");
        printf("\t4. Search Client\n");
        printf("\t5. Show All Clients\n");
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
                update_client();
                break;
            }
            case 3: {
                delete_client();
                break;
            }
            case 4: {
                search_client();
                break;
            }
            case 5: {
                show_all_clients();
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
void search_client(){
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
                printf("\n\tSearching for: %s",first_name.c_str());
                printf("\n\t=================================\n");
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
                printf("\n\tSearching for: %s",last_name.c_str());
                printf("\n\t=================================\n");
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
                printf("\n\tSearching for: %d",client_id);
                printf("\n\t=================================\n");
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
void show_all_clients(){
    //Flights menu.
    //This menu has the flight options. It will allow an admin to create, edit, and delete a
    //flight. This menu will be protected by password. It is linked to the flight table in the database.
    system("clear");
    string query = " SELECT * FROM CLIENT";
    sqlite3 *DB = nullptr;
    sqlite3_open("bank_record", &DB);
    printf("\n\tAll Clients: \n");
    sqlite3_exec(DB,query.c_str(), callback, nullptr, nullptr);
    printf("\nPress Enter to go back to main menu");
    cin.get();
    sqlite3_close(DB);
}
void update_client(){
    bool program_control = true;
    int option;
    sqlite3 *DB = nullptr;
    sqlite3_open("bank_record", &DB);
    while (program_control) {
        system("clear");
        printf("\n\t           Update Client\n");
        printf("\n\t=================================\n");
        printf("\n\tChoose between the options below:\n");
        printf("\t1. Update First Name\n");
        printf("\t2. Update Last Name\n");
        printf("\t3. Update Age\n");
        printf("\t4. Update Address\n");
        printf("\t5. Update Balance\n");
        printf("\t6. Exit\n");
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
                string query,new_first_name;
                int client_id;
                printf("\n\tClient ID of The Client To Be Update: ");
                cin >> client_id;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                system("clear");
                printf("\n\tOld Record:");
                query = "SELECT PERSON_ID,FIRST_NAME,LAST_NAME FROM CLIENT WHERE PERSON_ID="+ to_string(client_id) + ";";
                sqlite3_exec(DB,query.c_str(), callback, nullptr, nullptr);
                printf("\n\t=================================\n");
                printf("\n\tNew First Name: ");
                getline(cin,new_first_name);
                query = "UPDATE CLIENT SET FIRST_NAME='" + new_first_name + "' WHERE PERSON_ID="+ to_string(client_id)+";";
                sqlite3_exec(DB,query.c_str(), nullptr, nullptr, nullptr);
                printf("\n\tRecord Updated.");
                printf("\n\tNew Record:");
                query = "SELECT * FROM CLIENT WHERE PERSON_ID="+ to_string(client_id)+";";
                sqlite3_exec(DB,query.c_str(), callback, nullptr, nullptr);
                printf("\n\tPress Enter to go back to client menu");
                cin.get();
                break;
            }
            case 2: {
                string query,new_last_name;
                int client_id;
                printf("\n\tClient ID of The Client To Be Update: ");
                cin >> client_id;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                system("clear");
                printf("\n\tOld Record:");
                query = "SELECT PERSON_ID,FIRST_NAME,LAST_NAME FROM CLIENT WHERE PERSON_ID="+ to_string(client_id) + ";";
                sqlite3_exec(DB,query.c_str(), callback, nullptr, nullptr);
                printf("\n\t=================================\n");
                printf("\n\tNew Last Name: ");
                getline(cin,new_last_name);
                query = "UPDATE CLIENT SET LAST_NAME='" + new_last_name + "' WHERE PERSON_ID="+ to_string(client_id)+";";
                sqlite3_exec(DB,query.c_str(), nullptr, nullptr, nullptr);
                printf("\n\tRecord Updated.\n");
                printf("\n\tNew Record:");
                query = "SELECT * FROM CLIENT WHERE PERSON_ID="+ to_string(client_id)+";";
                sqlite3_exec(DB,query.c_str(), callback, nullptr, nullptr);
                printf("\n\tPress Enter to go back to client menu");
                cin.get();
                break;
            }
            case 3: {
                int client_id,new_age;
                printf("\n\tClient ID of The Client To Be Update: ");
                cin >> client_id;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                system("clear");
                printf("\n\tOld Record:");
                string query = "SELECT PERSON_ID,FIRST_NAME,LAST_NAME,AGE FROM CLIENT WHERE PERSON_ID="+ to_string(client_id) + ";";
                sqlite3_exec(DB,query.c_str(), callback, nullptr, nullptr);
                printf("\n\t=================================\n");
                printf("\n\tNew Age: ");
                cin >> new_age;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                query = "UPDATE CLIENT SET AGE='" + to_string(new_age) + "' WHERE PERSON_ID="+ to_string(client_id)+";";
                sqlite3_exec(DB,query.c_str(), nullptr, nullptr, nullptr);
                printf("\n\tRecord Updated.");
                printf("\n\tNew Record:");
                query = "SELECT * FROM CLIENT WHERE PERSON_ID="+ to_string(client_id)+";";
                sqlite3_exec(DB,query.c_str(), callback, nullptr, nullptr);
                printf("\n\tPress Enter to go back to client menu");
                cin.get();
                break;
            }
            case 4: {
                string query,new_address;
                int client_id;
                printf("\n\tClient ID of The Client To Be Update: ");
                cin >> client_id;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                system("clear");
                printf("\n\tOld Record:");
                query = "SELECT PERSON_ID,FIRST_NAME,LAST_NAME,ADDRESS FROM CLIENT WHERE PERSON_ID="+ to_string(client_id) + ";";
                sqlite3_exec(DB,query.c_str(), callback, nullptr, nullptr);
                printf("\n\t=================================\n");
                printf("\n\tNew Address: ");
                getline(cin,new_address);
                query = "UPDATE CLIENT SET ADDRESS='" + new_address + "' WHERE PERSON_ID="+ to_string(client_id)+";";
                sqlite3_exec(DB,query.c_str(), nullptr, nullptr, nullptr);
                printf("\n\tRecord Updated.\n");
                printf("\n\tNew Record:");
                query = "SELECT * FROM CLIENT WHERE PERSON_ID="+ to_string(client_id)+";";
                sqlite3_exec(DB,query.c_str(), callback, nullptr, nullptr);
                printf("\n\tPress Enter to go back to client menu");
                cin.get();
                break;
            }
            case 5: {
                int client_id,new_balance;
                printf("\n\tClient ID of The Client To Be Update: ");
                cin >> client_id;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                system("clear");
                printf("\n\tOld Record:");
                string query = "SELECT PERSON_ID,FIRST_NAME,LAST_NAME,BALANCE FROM CLIENT WHERE PERSON_ID="+ to_string(client_id) + ";";
                sqlite3_exec(DB,query.c_str(), callback, nullptr, nullptr);
                printf("\n\t=================================\n");
                printf("\n\tNew Balance: ");
                cin >> new_balance;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                query = "UPDATE CLIENT SET BALANCE='" + to_string(new_balance) + "' WHERE PERSON_ID="+ to_string(client_id)+";";
                sqlite3_exec(DB,query.c_str(), nullptr, nullptr, nullptr);
                printf("\n\tRecord Updated.");
                printf("\n\tNew Record:");
                query = "SELECT * FROM CLIENT WHERE PERSON_ID="+ to_string(client_id)+";";
                sqlite3_exec(DB,query.c_str(), callback, nullptr, nullptr);
                printf("\n\tPress Enter to go back to client menu");
                cin.get();
                break;
            }
            case 6: {
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
void delete_client(){}
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

