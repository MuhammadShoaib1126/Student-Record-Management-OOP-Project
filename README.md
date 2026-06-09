# 🎓 Student Record Management System

A console-based **Student Record Management System** built in C++ as an OOP project. It allows managing student records with file persistence, user authentication, sorting, searching, GPA calculations, and report generation.

---

## 📌 Project Overview

The system manages students across three departments:
- **CS** (Computer Science)
- **SE** (Software Engineering)
- **EE** (Electrical Engineering)

> The design allows easy addition of more departments.

All data is stored persistently using **binary files** for both users and students.  
When the program runs:
- Data is loaded from files
- Changes are saved back automatically
- Input validation is thorough (GPA, Age, ID ranges)

The console interface uses custom ANSI escape sequences for:
- **Bold text**
- *Italic text*
- Colored output

---

## 🚀 Features

### Student Management
- Add new students (ID, name, age, GPA, department)
- View all students
- Search by ID or Name
- Edit student records
- Delete student records

### Sorting (Ascending)
- Sort by **ID**
- Sort by **Name** (lexicographically)
- Sort by **GPA** (lowest to highest)
- Sort by **Age**

### Analytics & Reports
- Average GPA (overall)
- Department-wise average GPA
- Department-wise student count
- Generate timestamped text reports
- Display reports from file

### File Persistence
- Save/load student data to binary file
- Auto-save on every change
- User data stored in binary file

### User Authentication
- Create account / Login system
- 3 failed attempts → program exit
- Welcome screen with system info

---

## 🛠 Tech Stack

| Category | Technology |
|----------|------------|
| Language | C++ |
| File I/O | Binary files (`.data`) + Text files (`.txt`) |
| Memory Management | Dynamic arrays with resizing |
| Console Styling | ANSI escape sequences |
| Build System | Any C++ compiler (g++, MinGW, MSVC) |

---

## 📁 Files Used

| File | Purpose |
|------|---------|
| `students.data` | Stores student records (binary) |
| `users.data` | Stores user login data (binary) |
| `reports.txt` | Generated report output |
| `header.txt` | Console header/layout text |

---

## 📦 Installation & Running

### Prerequisites
- C++ compiler (g++ recommended)
- Terminal / Command Prompt

### Steps

```bash
# Clone the repository
git clone https://github.com/MuhammadShoaib1126/student-record-management-system.git
cd student-record-management-system

# Compile
g++ main.cpp -o student_system

# Run
./student_system   # Linux/Mac
student_system.exe # Windows
