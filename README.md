# 📚 Simple Library Management System (C++)

A basic console-based **Library Management System** written in C++ that manages books and users.  
The system allows adding books and users, borrowing and returning books, and viewing who borrowed what — all through a text-based interface.

---

## ✅ Features

- ➕ Add new books and users
- 🔎 Search books by name prefix
- 🔢 Sort and display books by **ID** or **Name**
- 👥 Track borrowed books per user
- 📖 Borrow and return books with limited copies
- 🔍 Show who borrowed a specific book
- ⛔ Handles invalid input and borrowing limits

---

## 🧠 How It Works

- The system supports:
  - Up to **10 books**
  - Up to **10 users**
- Each book has:
  - `id`, `name`, `total_quantity`, `total_borrowed`
- Each user has:
  - `name`, `national id`, and a list of borrowed book IDs
- Borrowing reduces available copies; returning increases them.

---

## 💻 Technologies

- **Language**: C++
- **Platform**: Terminal / Console
- **No external libraries** required

---

## 🚀 Running the Program

1. Copy the code into a file called `library_system.cpp`
2. Compile and run:
   ```bash
   g++ library_system.cpp -o library_system
   ./library_system
## 📋 Sample Menu

Library Menu;
1) add_book
2) search_books_by_prefix
3) print_who_borrowed_book_by_name
4) print_library_by_id
5) print_library_by_name
6) add_user
7) user_borrow_book
8) user_return_book
9) print_users
10) Exit
## 📂 File Structure
library_system.cpp – Complete C++ source code

README.md – Project documentation

🛠️ Possible Improvements
Expand user and book limits with dynamic structures (e.g., vectors)

Implement file storage (saving/loading users and books)

Add GUI using Qt or integrate with a simple database

Support due dates and penalties for late returns

## 👨‍💻 Author
Created by Nour Mohamed
Faculty of Science – Statistics & Computer Science Department – Ain Shams University

## 🪪 License
This project is open-source and available for learning and educational purposes.
