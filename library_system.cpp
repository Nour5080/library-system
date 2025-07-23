#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
using namespace std;

const int MAX_books = 10;
const int MAX_users = 10;

bool is_text(const string& input) {
    if (input.empty()) return false;
    for (char c : input) {
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' '))
            return false;
    }
    return true;
}

bool is_number(const string& input) {
    if (input.empty()) return false;
    for (char c : input) {
        if (c < '0' || c > '9')
            return false;
    }
    return true;
}

int read_number(const string& msg) {
    string input;
    while (true) {
        cout << msg;
        getline(cin, input);
        if (is_number(input)) return stoi(input);
        cout << "Invalid input. Please enter a number.\n";
    }
}

string read_text(const string& msg) {
    string input;
    while (true) {
        cout << msg;
        getline(cin, input);
        if (is_text(input)) return input;
        cout << "Invalid input. Please use letters only.\n";
    }
}

struct Book {
    string name;
    int id, total_borrowed, total_quantity;

    Book() : id(-1), total_borrowed(0), total_quantity(0), name(" ") {}

    void read() {
        cout << "Please enter book info:\n";
        id = read_number("Enter Id: ");
        name = read_text("Enter Name: ");
        total_quantity = read_number("Enter Quantity: ");
    }

    bool has_prefix(const string& prefix) {
        return name.substr(0, prefix.size()) == prefix;
    }

    bool borrowed(int user_id) {
        if (total_quantity == total_borrowed) return false;
        total_borrowed++;
        return true;
    }

    void return_copy() {
        if (total_borrowed > 0) total_borrowed--;
        else cout << "Error: no borrowed copies to return.\n";
    }

    void print() {
        cout << "ID: " << id << ", Name: " << name
            << ", Total: " << total_quantity
            << ", Borrowed: " << total_borrowed << endl;
    }
};

bool cmp_by_name(Book& a, Book& b) { return a.name < b.name; }
bool cmp_by_id(Book& a, Book& b) { return a.id < b.id; }

struct User {
    string name;
    int id;
    int borrowed_books_id[MAX_books];
    int len;

    User() : id(-1), len(0), name(" ") {}

    void read() {
        id = read_number("Enter user ID: ");
        name = read_text("Enter user name: ");
    }

    void borrowed(int book_id) {
        borrowed_books_id[len++] = book_id;
    }

    void return_copy(int book_id) {
        bool found = false;
        for (int i = 0; i < len; ++i) {
            if (borrowed_books_id[i] == book_id) {
                for (int j = i + 1; j < len; ++j)
                    borrowed_books_id[j - 1] = borrowed_books_id[j];
                len--;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "User " << name << " never borrowed book ID " << book_id << endl;
        }
    }

    bool is_borrowed(int book_id) {
        for (int i = 0; i < len; ++i)
            if (borrowed_books_id[i] == book_id)
                return true;
        return false;
    }

    void print() {
        sort(borrowed_books_id, borrowed_books_id + len);
        cout << "User: " << name << " (ID: " << id << ") borrowed books: ";
        for (int i = 0; i < len; ++i)
            cout << borrowed_books_id[i] << " ";
        cout << endl;
    }
};

struct LibrarySystem {
    int total_books = 0;
    Book books[MAX_books];
    int total_users = 0;
    User users[MAX_users];

    void run() {
        while (true) {
            int choice = menu();
            if (choice == 1) add_book();
            else if (choice == 2) search_books_by_prefix();
            else if (choice == 3) print_who_borrowed_book_by_name();
            else if (choice == 4) print_library_by_id();
            else if (choice == 5) print_library_by_name();
            else if (choice == 6) add_user();
            else if (choice == 7) user_borrow_book();
            else if (choice == 8) user_return_book();
            else if (choice == 9) print_users();
            else if (choice == 10) break;
        }
    }

    int menu() {
        string input;
        while (true) {
            cout << "\nLibrary Menu:\n"
                << "1) Add book\n"
                << "2) Search books by prefix\n"
                << "3) Print who borrowed book by name\n"
                << "4) Print library by ID\n"
                << "5) Print library by name\n"
                << "6) Add user\n"
                << "7) User borrow book\n"
                << "8) User return book\n"
                << "9) Print users\n"
                << "10) Exit\n"
                << "\nEnter your menu choice [1 - 10]: ";
            getline(cin, input);
            if (is_number(input)) {
                int choice = stoi(input);
                if (choice >= 1 && choice <= 10) return choice;
            }
            cout << "Invalid input. Try again.\n";
        }
    }

    void add_book() {
        books[total_books++].read();
    }

    void add_user() {
        users[total_users++].read();
    }

    int find_book(const string& name) {
        for (int i = 0; i < total_books; ++i)
            if (books[i].name == name)
                return i;
        return -1;
    }

    int find_user(const string& name) {
        for (int i = 0; i < total_users; ++i)
            if (users[i].name == name)
                return i;
        return -1;
    }

    bool read_book_and_user(int& book_idx, int& user_idx) {
        for (int i = 0; i < 3; ++i) {
            string user_name = read_text("Enter user name: ");
            string book_name = read_text("Enter book name: ");

            user_idx = find_user(user_name);
            if (user_idx == -1) {
                cout << "Invalid user name.\n";
                continue;
            }

            book_idx = find_book(book_name);
            if (book_idx == -1) {
                cout << "Invalid book name.\n";
                continue;
            }

            return true;
        }
        cout << "Too many failed attempts. Try again later.\n";
        return false;
    }

    void user_borrow_book() {
        int book_idx, user_idx;
        if (!read_book_and_user(book_idx, user_idx)) return;
        if (!books[book_idx].borrowed(users[user_idx].id))
            cout << "No more copies available.\n";
        else
            users[user_idx].borrowed(books[book_idx].id);
    }

    void user_return_book() {
        int book_idx, user_idx;
        if (!read_book_and_user(book_idx, user_idx)) return;
        books[book_idx].return_copy();
        users[user_idx].return_copy(books[book_idx].id);
    }

    void print_users() {
        for (int i = 0; i < total_users; ++i)
            users[i].print();
    }

    void print_library_by_id() {
        sort(books, books + total_books, cmp_by_id);
        for (int i = 0; i < total_books; ++i)
            books[i].print();
    }

    void print_library_by_name() {
        sort(books, books + total_books, cmp_by_name);
        for (int i = 0; i < total_books; ++i)
            books[i].print();
    }

    void search_books_by_prefix() {
        string prefix = read_text("Enter book name prefix: ");
        int count = 0;
        for (int i = 0; i < total_books; ++i) {
            if (books[i].has_prefix(prefix)) {
                books[i].print();
                count++;
            }
        }
        if (count == 0)
            cout << "No books found with that prefix.\n";
    }

    void print_who_borrowed_book_by_name() {
        string book_name = read_text("Enter book name: ");
        int book_idx = find_book(book_name);
        if (book_idx == -1) {
            cout << "Invalid book name.\n";
            return;
        }

        int book_id = books[book_idx].id;
        if (books[book_idx].total_borrowed == 0) {
            cout << "No copies are currently borrowed.\n";
            return;
        }

        for (int i = 0; i < total_users; ++i)
            if (users[i].is_borrowed(book_id))
                cout << users[i].name << endl;
    }
};

int main() {
    LibrarySystem library;
    library.run();
    return 0;
}
