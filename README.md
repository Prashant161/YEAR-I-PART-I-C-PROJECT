# Simple Banking System (C Programming)

## Overview
This project was developed to fulfill the **internal evaluation requirement for C Programming (First Semester – Part I)**. It is a **teamwork project** that simulates a **prototype banking system** with basic functionalities for both **admin (bank staff)** and **clients**.

The system allows the admin to manage client accounts and allows clients to view and perform limited operations on their accounts.

---

## Features

### Admin Functions
- Register new clients
- Search client details
- Update client balance (deposit)
- Withdraw balance
- Add interest to client accounts

### Client Functions
- Login using registered phone number and password
- Create password during first login
- View account details
- Transfer money to another account

---

## Default Admin Login
Username: admin
Password: admin

---

## Dummy Database Setup

Before running the main program, execute:
dummyDatabase.c

This program creates a **dummy database file (`clients.txt`)** containing three sample users for testing the search and client features.

### Dummy Users
- Prashant Acharya
- Yugal Kishore Dahal
- Ghanshyam Pokhrel

---

## How to Run

1. Compile and run `dummyDatabase.c` first to create sample data.
2. Compile and run the main banking system program.
3. Choose from the main menu:
   - **Admin**
   - **Client**
   - **Exit**
4. Admin can register new clients and manage accounts.
5. Clients can login using their **name and registered phone number**.
6. On the **first login**, clients will be asked to **create a password** for future access.

---

## Notes
- Client search is **case-insensitive**.
- The **full name must be entered** for successful search.
- Account data is stored in a file (`clients.txt`) using **file handling in C**.

---

  ## Project Structure
  
--> complete.c        # Main banking system program

--> clientPart.c      # Client-side functionality (no need to run separately)

--> dummyDatabase.c   # Generates dummy client records (run for ease in testing)

--> clients.txt       # Database file (generated after running program)

--> README.md         # Project documentation

