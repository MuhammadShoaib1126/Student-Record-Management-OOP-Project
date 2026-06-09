# Student Record Management System — Summary

- The project is a **Student Record Management System** with three departments:  
  **CS (Computer Science), SE (Software Engineering), EE (Electrical Engineering)**  
  (designed so more departments can be added easily)

- Data is stored in **binary files** for both users and students.

- When the program runs:  
  - All data is **loaded from files**  
  - Any changes made during the program **are saved back to files**

- **Input validation** is thoroughly handled, including valid ranges for:  
  - GPA  
  - Age  
  - ID

- The console interface uses three custom formatting functions:  
  - `bold()`  
  - `italic()`  
  - `setColor()`  
  These use **ANSI escape sequences** to style terminal output.

## 📌 Features

- Add new student records  
- Edit existing student records  
- Delete student records  
- Search students by:
  - Name  
  - ID  
- Sort students by:
  - Age  
  - Name  
  - ID  
  - GPA  
  (currently ascending only for simplicity)
- Display data loaded from binary files  
- Generate detailed reports in text format  
- Calculate:
  - **Average GPA across all departments**  
  - **Average GPA for each individual department**

## 📁 Files Used

- `students.data` — stores student records  
- `users.data` — stores user login data  
- `reports.txt` — generated report output  
- `header.txt` — console header/layout text