#include <iostream>
#include <sqlite3.h>
#include <cstdio>

void main_menu_options();
void add_record();
void search_record();
void show_records();
void update_record();
void delete_record();
//bool input_tester();

using namespace std;

int main() {
//    main_menu_options();
    sqlite3* DB;
    string sql = "CREATE TABLE CLIENT("
                 "ID INT PRIMARY KEY NOT NULL, "
                 "FNAME          TEXT NOT NULL, "
                 "LNAME          TEXT NOT NULL, "
                 "AGE            INT  NOT NULL, "
                 "ADDRESS        CHAR(50) NOT NULL, "
                 "BALANCE        MONEY NOT NULL );";
    int exit;
    exit = sqlite3_open("bank_record", &DB);
    char* messageError;
    exit = sqlite3_exec(DB, sql.c_str(), nullptr, nullptr, &messageError);

    if(exit != SQLITE_OK) {
        cerr << "Error creating table " << sqlite3_errmsg(DB) << endl;
        sqlite3_free(messageError);
    }
    else {
        cout << "Table Created Successfully" << endl;
    }
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

