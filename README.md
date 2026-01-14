# 🏦 Bank Management System (Extension 2) - Users & Permissions | Level 8

> **"A transition from simple data management to building secure, permission-based systems."** 🚀

📌 This project is the **direct second extension (Extension 2)** of the final bank project. I have elevated this version to meet the requirements of **[Level 08: Algorithms & Problem Solving Level 4](https://github.com/ammmrrr18-cloud/Programming-Foundations-Roadmap/tree/main/08%20-%20Algorithms%20%26%20Problem%20Solving%20Level%204)** by implementing an advanced security layer based on **User Permissions**.

---

## 🔄 What's New in "Extension 2"?

I have upgraded the previous bank project into a professional **Functional System** that includes:

### 1️⃣ User Permissions System (Access Control)
* **From Client to Employee:** The system now manages not just bank clients, but also the employees (Users) who have access to the data.
* **Granular Control:** Each employee has a specific permission set. I utilized **Bitwise Flags** logic to determine allowed tasks (e.g., Show List, Add, Delete, or access Transactions).
* **Data Security:** If a user attempts to enter a section they are not authorized for, the system instantly triggers an `Access Denied` warning.

### 2️⃣ User Management (Manage Users Menu)
* Added a complete dedicated menu to manage employee accounts (Add, Delete, Update, and Find).
* Hardcoded protection to prevent the deletion of the primary `Admin` account, ensuring there is always a master controller for the system.

### 3️⃣ Secure Login System
* Users must authenticate via `UserName` and `Password` validated against the `Users.txt` database.
* The system maintains a `CurrentUser` session variable to apply the correct permissions in real-time across all menus.

---

## 🛠️ Technical Concepts Applied
This **Functional System** focuses on applying high-level engineering concepts:

* **Bitwise Operations:** The most efficient method to manage multiple permissions within a single variable.
* **Advanced Structs & Vectors:** Used for dynamic in-memory management of both Clients and Users data.
* **Multi-File Handling:** Simultaneous management of two database files: `Clients.text` and `Users.txt`.
* **Nested Enums:** Organizing the program flow across three main interconnected menus.

---

## 🔗 Quick Links (Previous Phases)
* **Level 08 Roadmap:** 🚀 [Algorithms & Problem Solving Level 4](https://github.com/ammmrrr18-cloud/Programming-Foundations-Roadmap/tree/main/08%20-%20Algorithms%20%26%20Problem%20Solving%20Level%204)
* **Phase 1 (Foundation):** [Bank System V1](https://github.com/ammmrrr18-cloud/07-Algorithms-Level-3-Bank-Project)
* **Phase 2 (Extension 1):** [Bank Extension V2](https://github.com/ammmrrr18-cloud/Project-2---Bank-Extension---Level-7)

---

## 📁 Repository Structure
* **My-Solution:** The enhanced source code featuring the advanced permissions and user management system.
* **Instructor-Solution:** The model solution by Dr. Mohammed Abu-Hadhoud for technical reference and comparison.

---
*📌 "Evolving a project from simple records to a secure system with permissions is the core of professional software engineering."*
