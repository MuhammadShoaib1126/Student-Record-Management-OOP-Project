# 🎓 Student Record Management System

A console-based **Student Record Management System** built in C++. This was developed as an OOP project to manage student records with full CRUD operations, file persistence, user authentication, sorting, searching, GPA calculations, and report generation.

---

## 📌 Overview

The system manages students across three departments:
- **CS** (Computer Science)
- **SE** (Software Engineering)
- **EE** (Electrical Engineering)


Data is stored persistently using **binary files**. Any changes made during execution are automatically saved. The program includes thorough input validation for:
- GPA (0.0 – 4.0)
- Age (16 – 23)
- Unique Student ID

The console interface uses ANSI escape sequences for:
- **Bold** and *italic* text
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
- Sort by ID
- Sort by Name (lexicographically)
- Sort by GPA (lowest to highest)
- Sort by Age

### Analytics & Reports
- Average GPA (overall)
- Department-wise average GPA
- Department-wise student count
- Generate timestamped text reports
- Display reports from file

### File Persistence
- Save/load student data to binary file
- Auto-save on every change
- User credentials stored in binary file

### User Authentication
- Create account / Login system
- 3 failed login attempts → program exits
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

## 📦 Compilation & Running

### Prerequisites
- C++ compiler (g++ recommended)

### Steps

```bash
# Compile
g++ main.cpp -o student_system

# Run
./student_system   # Linux/Mac
student_system.exe # Windows
