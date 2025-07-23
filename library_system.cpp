#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

const int MAX_books = 10;
const int MAX_users = 10;

bool is_text(string input) {
    if (input.empty()) return false;

    for (int i = 0; i < input.length(); i++) {
        char c = input[i];

        if (!((c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == ' ')) {
            return false;
        }
    }

    return true;
}



bool is_number(string input) {
    if (input.empty()) return false;

    for (int i = 0; i < input.length(); i++) {
        char c = input[i];

        if (c < '0' || c > '9') {
            return false;
        }
    }

    return true;
}



struct book {
    string name;
    int id;
    int total_borrowed;
    int total_quantity;
    book() {
        total_borrowed = total_quantity = 0;
        id = -1;
        name = " ";
    }

    void read() {
        cout << "please enter book info: \n \n";
        
            while (true) {

                string Id_input;
                cout << "Enter Id:\n\n";
                cin >> Id_input;
                if (is_number(Id_input)) {
                    id = stoi(Id_input);
                    break;
                }
                else {
                    cout << "invaild Id, please try again.\n\n";
                }
            }
        

        while (true) {

            string Name_input;
            cout << "Enter Name:\n\n";
            cin >> Name_input;
            if (is_text(Name_input)) {
                name = Name_input;
                break;
            }
            else {
                cout << "invaild Name, please try again.\n\n";
            }
        }


        while (true) {

            string quantity_input;
            cout << "Enter Quantity:\n\n";
            cin >> quantity_input;
            if (is_number(quantity_input)) {
                total_quantity = stoi(quantity_input);
                break;
            }
            else {
                cout << "invaild spcialization, please try again.\n\n";
            }
        }
    }

   
    bool has_prefix(string prefix) {
        if (name.size() < prefix.size()) {
            return false;
        }
        for (int i = 0; i < prefix.size(); ++i) {
            if (prefix[i] != name[i]) {
                return false;
            }
        }
        return true;
    }

    bool borrowed(int user_id) {
        if (total_quantity == total_borrowed)
            return false;
        total_borrowed++;
        return true;
    }

    void return_coby() {
        if (total_borrowed > 0) {
            total_borrowed--;
        } else {
            cout << "there is an error\n";
        }
    }

    void print() {
        cout << " id = " << id << " name = " << name
             << " total quantity = " << total_quantity
             << " total borrowed = " << total_borrowed << endl;
    }
};

bool cmd_by_name(book &a, book &b) {
    return a.name < b.name;
}

bool cmd_by_id(book &a, book &b) {
    return a.id < b.id;
}

struct user {
    string name;
    int borrowed_books_id[MAX_books]{};
    int id;
    int len;
    user() {
        name = " ";
        id = -1;
        len = 0;
    }

    void read() {
        while (true) {

            string Id_input;
            cout << "Enter Id:\n\n";
            cin >> Id_input;
            if (is_number(Id_input)) {
                id = stoi(Id_input);
                break;
            }
            else {
                cout << "invaild Id, please try again.\n\n";
            }
        }


        while (true) {

            string Name_input;
            cout << "Enter Name:\n\n";
            cin >> Name_input;
            if (is_text(Name_input)) {
                name = Name_input;
                break;
            }
            else {
                cout << "invaild Name, please try again.\n\n";
            }
        }


    }


    void borrowed(int book_id) {
        borrowed_books_id[len++] = book_id;
    }
    void return_coby(int book_id) {
        bool clear = false;
        for (int i = 0; i < len; ++i) {
            if (borrowed_books_id[i] == book_id) {
                for (int j = i + 1; j < len; ++j)
                    borrowed_books_id[j - 1] = borrowed_books_id[j];
                clear = true;
                --len;
                break;
            }
        }
        if (!clear) {
            cout << "ooops user " << name << " never borrowed book id " << book_id << endl;
        }
    }
    bool is_borrowed(int book_id) {
        for (int i = 0; i < len; ++i) {
            if (book_id == borrowed_books_id[i]) {
                return true;
            }
        }
        return false;
    }
    void print() {
        sort(borrowed_books_id, borrowed_books_id + len);
        cout << "the user " << name << " his id " << id << " borrowed books ids: ";
        for (int i = 0; i < len; ++i) {
            cout << borrowed_books_id[i] << " ";
        }
        cout << "\n";
    }
};

struct library_system {
    int total_books;
    book books[MAX_books]{};
    int total_users;
    user users[MAX_users]{};
    library_system(){
        total_books=0;
        total_users=0;

    }

    void run() {
        while (true) {

            int choice = menu();
            if (choice == 1) {
                add_book();
            } else if (choice == 2) {
                search_book_by_prefix();
            } else if (choice == 3) {
                print_who_borrowed_book_by_name();
            } else if (choice == 4) {
                print_library_by_ID();
            } else if (choice == 5) {
                print_library_by_NAME();
            } else if (choice == 6) {
                add_user();
            } else if (choice == 7) {
                user_borrow_book();
            } else if (choice == 8) {
                user_return_book();
            } else if (choice == 9) {
                print_user();
            }

        }
    }

    bool vaild(int choice) {
        return (1 <= choice && choice <= 10);
    }
     int menu() {
        int choice ;
        while (true) {
            cout << "\nLibrary Menu;\n";
            cout << "1) add_book\n";
            cout << "2) search_books_by_prefix\n";
            cout << "3) print_who_borrowed_book_by_name\n";
            cout << "4) print_library_by_id\n";
            cout << "5) print_library_by_name\n";
            cout << "6) add_user\n";
            cout << "7) user_borrow_book\n";
            cout << "8) user_return_book\n";
            cout << "9) print_users\n";
            cout << "10) Exit\n";
            cout << "\nEnter your menu choice [1 - 10]: ";
            
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Invalid input. Please enter a number between 1 and 10.\n\n";
                continue;
            }

            if (!vaild(choice)) {
                cout << "Invalid choice. Try again\n";
                continue;                                                                // loop keep working
            }
            break;
        }
        return choice;
    }

    void add_book() {
        books[total_books++].read();
    }

    void search_book_by_prefix() {
        cout << "enter book name prefix: ";
        int count = 0;
        string prefix;

        while (true) {
            string prefix_input;
            cout << "Enter prefix:\n\n";
            cin >> prefix_input;
            if (is_text(prefix_input)) {
                prefix = prefix_input;
                break;
            }
            else {
                cout << "invaild prefix, please try again.\n\n";
            }
        }

        for (int i = 0; i < total_books; ++i) {
            if (books[i].has_prefix(prefix)) {
                cout << books[i].name;
                count++;
            }
        }
        if (count == 0) {
            cout << "not found\n";
        }
    }

    void print_library_by_ID() {
        sort(books, books + total_books, cmd_by_id);
        cout << "\n";
        for (int i = 0; i < total_books; ++i)
            books[i].print();

    }

    void print_library_by_NAME() {
        sort(books, books + total_books, cmd_by_name);
        cout << "\n";
        for (int i = 0; i < total_books; ++i) {
            books[i].print();
        }
    }

    void add_user() {
        users[total_users++].read();
    }

    void print_user() {
        cout << "\n";
        for (int i = 0; i < total_users; ++i) {
            users[i].print();
        }
    }

    int find_book(const string& name) {
        for (int i = 0; i < total_books; ++i) {
            if (name == books[i].name) {
                return i;
            }
        }
        return -1;
    }
    int find_user(const string& name){
        for (int i = 0; i < total_users; ++i) {
            if (name==users[i].name){
                return i;
            }

        }
        return -1;
    }


    bool read_books_name_and_user_name(int &book_idx,int &user_idx,int trail=3){
        string book_name;
        string user_name;
        while (trail--){
            cout << "enter user name:\n \n";
            cin >> user_name;
            cout<< "enter book name: \n\n";
            cin>> book_name;
            user_idx= find_user(user_name);

            if(user_idx==-1){
                cout<<"invalid user name! please try again\n";
                continue;
            }
            book_idx= find_book(book_name);
            if(book_idx==-1){
                cout<<"invalid book name! please try again\n";
                continue;
            }
            return true;
        }
        cout<<"you did several trials!! try later XP\n";
        return false;
    }

    void print_who_borrowed_book_by_name(){

        string book_name;
        cout<<"enter book name:\n";
        cin>>book_name;

        int book_idx= find_book(book_name);
        if(book_idx==-1){
            cout<<"invalid book name\n";
            return;
        }
        int book_id = books[book_idx].id;
        if(books[book_idx].total_borrowed==0){
            cout<<"no borrowed copies\n";
            return;
        }
        for (int i = 0; i < total_users; ++i) {
            if(users[i].is_borrowed(book_id)){
                cout<<users[i].name;
            }
        }

    }
    void user_return_book() {
        int book_idx,user_idx;
        if(!read_books_name_and_user_name(book_idx,user_idx)){
            return;
        }
        int book_id=books[book_idx].id;
        books[book_idx].return_coby();
        users[user_idx].return_coby(book_id);

    }
    void user_borrow_book() {
        int user_idx,book_idx;
        if(!read_books_name_and_user_name(book_idx,user_idx)){
            return;
        }
        int user_id=users[user_idx].id;
        int book_id=books[book_idx].id;
        if(!books[book_idx].borrowed(user_id)){
            cout<<"no more copies available right now\n";
        }
        else{
            users[user_idx].borrowed(book_id);
        }

    }

};

int main() {
    library_system library ;
    library.run();
    return 0;
}
