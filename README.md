# 🏦 Project 1: Bank Extension 2 (ATM System Simulation) - Level 8

This project marks my transition into **Level 8 (Algorithms & Problem Solving Level 4)**. It serves as the **second extension** of the Bank System, evolving from an administrative backend tool into a full-scale, user-centric **ATM Machine Simulation**.

---

## 🔄 What's New in "Extension 2"?
In this phase, the system's perspective shifts from the "Employee" to the "Client." The focus is entirely on **User Experience (UX)** and autonomous financial transaction logic.

### 1️⃣ Secure Authentication (Login System)
* **Identity Verification:** Users can only access the system using their unique `Account Number` and `Pin Code`.
* **Session Management:** The program captures and holds the `CurrentClient` data immediately after a successful login to manage their specific transactions throughout the session.



### 2️⃣ Specialized ATM Transaction Features
* **Quick Withdraw:** A convenient menu offering pre-defined fixed amounts (20, 50, 100, etc.) for rapid cash access.
* **Normal Withdraw:** Allows custom amount entry with a specialized validation rule requiring the amount to be in multiples of 5.
* **Deposit:** A streamlined interface for users to add funds directly to their account balance.
* **Check Balance:** A dedicated screen for users to view their current available funds instantly.

### 3️⃣ Advanced Logic & Data Validation
* **Overdraft Protection:** The system dynamically verifies if the withdrawal amount (Quick or Normal) exceeds the available balance before processing the transaction.
* **Real-time File Synchronization:** Every transaction is automatically synced with the `Clients.text` database, ensuring data consistency across all bank system versions.

---

## 🛠️ Technical Concepts Applied
* **Global Structs:** Utilizing a global state to track the `CurrentClient` across multiple functions.
* **Vector Manipulation:** Efficiently loading, modifying, and re-saving data to maintain database integrity.
* **Advanced Flow Control:** Managing multi-layered menus (Main Menu -> Sub-menus) using Enums and Switch-Case statements.
* **String Processing:** Applying advanced splitting and record conversion techniques for data persistence.

---

## 🔗 Quick Links (Related Projects)
* **Level 7 - Phase 1 (Foundation):** [Bank Management System V1](https://github.com/ammmrrr18-cloud/07-Algorithms-Level-3-Bank-Project)
* **Level 7 - Phase 2 (Extension 1):** [Bank Extension V2](https://github.com/ammmrrr18-cloud/Project-2---Bank-Extension---Level-7)

---

## 📁 Repository Structure
* **My-Solution:** Contains my full C++ source code and implementation for the ATM simulation.
* **Instructor-Solution:** The model solution by Dr. Mohammed Abu-Hadhoud for technical reference and best practices.

---
*📌 "Transitioning from managing data to simulating user interaction is a major milestone in a software developer's journey."*
