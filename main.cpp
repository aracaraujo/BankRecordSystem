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
void test();

namespace {
    std::random_device rd;
    std::mt19937 gen(rd());}

using namespace std;

static int callback(void* data, int argc, char** argv, char** azColName){
    // This function prints on the screen the results of the queries made to the database.
    int i;
    printf("\n\t");

    for (i = 0; i< argc; i++){
    }
    printf("\n");
    return 0;
}

int main() {
    int exit;
    // Creating the database. If error occur it will ask the user reload the software.
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

    // Display the main menu options. From the main menu all the functionalities of the software are available.
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
        printf("\t7. test\n");
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
                // Changes the program control status to then exit the loop and exit the program.
                printf("\n\tHave a great day!");
                program_control = false;
                break;
            }
            case 7: {
                test();
                break;
            }
            default: {
                // In case an invalid option is displayed it will tell the user that and wait for an input to
                // return to the menu.
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
    // Searching menu.
    // This function will help the user to search for a record. It will allow the user to choose by which
    // information to search. The user can use the first name, last name, or client ID. Searching by first
    // or last name might bring more than one results since more than one person can have the same first
    // or last name. Searching by client ID is the more accurate since client's ID are unique.
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
        printf("\t4. Back To Main Menu\n");
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
                // Search a record through the first name. It might display more than one record in case
                // more than one person has the same first name.
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
                // Search a record through the last name. It might display more than one record in case
                // more than one person has the same last name.
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
                // Search a record through the client ID. This will return only one record since client_id are uniques.
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
                // Changes the program control status to then exit the loop and exit the function.
                program_control = false;
                break;
            }
            default: {
                // In case an invalid option is displayed it will tell the user that and wait for an input to
                // return to the menu.
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
    // This function prints all the records in the database.
    system("clear");
    // Querying all the records in the database.
    string query = " SELECT * FROM CLIENT";
    sqlite3 *DB = nullptr;
    sqlite3_open("bank_record", &DB);
    printf("\n\tAll Clients: \n");
    sqlite3_exec(DB,query.c_str(), callback, nullptr, nullptr);
    // This makes the screen to wait for an input to go back to the menu. I introduced this so the user has time
    // to read the output and then go back to menu when ready.
    printf("\n\tPress Enter to go back to main menu");
    cin.get();
    sqlite3_close(DB);
}
void update_client(){
    // Updating Menu.
    // This function will help the user to update records in the database. It will ask for the client_id in order
    // to get the correct client.
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
        printf("\t6. Back To Main Menu\n");
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
                // Update first name.
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
                // Update second name.
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
                // Update age.
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
                // Update address.
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
                // Update the balance.
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
                // Changes the program control status to then exit the loop and exit the function.
                program_control = false;
                break;
            }
            default: {
                // In case an invalid option is displayed it will tell the user that and wait for an input to
                // return to the menu.
                printf("\nThis is not a proper option.");
                printf("\nPress Enter to go back to the search menu");
                cin.get();
                continue;
            }
        }
    }
    sqlite3_close(DB);
}
void delete_client(){
    // This function helps the user to delete clients from the database.
    int client_id;
    string query;
    char input;
    system("clear");
    sqlite3 *DB = nullptr;
    sqlite3_open("bank_record", &DB);
    printf("\n\t          Deleting Record\n");
    printf("\n\t=================================\n");
    printf("\n\tEnter The Client ID of the Record to be Deleted: ");
    cin >> client_id;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    query = "SELECT * FROM CLIENT WHERE PERSON_ID="+ to_string(client_id)+";";
    printf("\n\tThe Following Record Will Be Deleted:");
    sqlite3_exec(DB,query.c_str(),callback, nullptr, nullptr);
    printf("\n\tWould you like to proceed?(Y/N): ");
    cin >> input;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (toupper(input) == 'Y'){
        query = "DELETE FROM CLIENT WHERE PERSON_ID="+ to_string(client_id)+";";
        sqlite3_exec(DB,query.c_str(), nullptr, nullptr, nullptr);
        printf("\n\tRecord Deleted.");
    }else{
        printf("\n\tRecord Not Deleted.");
    }
    printf("\n\tPress Enter to go back to main menu");
    cin.get();
    sqlite3_close(DB);
}
int create_database(){
    // Creates the database.
    int exit;
    sqlite3* DB;
    exit = sqlite3_open("bank_record", &DB);
    if (exit) {
        cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
        return 0;
    }
    else{
        sqlite3_close(DB);
        return -1;
    }
}
void create_client_table(){
    // Creates a CLIENT table in the database.
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
    // This function add clients to the database. It will ask the user all the required client information and then
    // add to the database.
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
        cerr << "\n\tError Insert " << sqlite3_errmsg(DB) << endl;
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
void test(){
    // This function prints all the records in the database.
    system("clear");
    // Querying all the records in the database.
    string query = "INSERT INTO CLIENT (PERSON_ID,FIRST_NAME,LAST_NAME,AGE,ADDRESS,BALANCE) VALUES(3663, 'DAL', 'CANTANHEDE', 28, '178 UTAH', 200) ";
    sqlite3 *DB = nullptr;
    sqlite3_open("bank_record", &DB);
    char* error_message;
    sqlite3_exec(DB,query.c_str(), nullptr, nullptr, &error_message);
    cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
    string answer = sqlite3_errmsg(DB);
    if (answer == "UNIQUE constraint failed: CLIENT.PERSON_ID"){
        cout << "worked" << endl;
    }else{
        cout << "didn't work" << endl;
    }
    printf("\n\tPress Enter to go back to main menu");
    cin.get();
    sqlite3_close(DB);
}
