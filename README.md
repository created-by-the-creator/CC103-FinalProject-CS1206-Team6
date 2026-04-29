# 🚗 GasQueue: Fuel Distribution System

## 📌 Project Description
GasQueue is a fuel distribution management system that simulates real-world queue operations using different data structures. It manages regular customers, priority customers, and served customer history using Queue, Priority Queue, and Stack.

The project demonstrates both **manual implementation of data structures (for learning purposes)** and **STL-based implementation (for system integration)**.

---

## 🎯 Objectives
- Simulate a real-world fuel queue system
- Apply FIFO, Priority Scheduling, and LIFO concepts
- Implement and understand data structures manually
- Integrate STL data structures for efficient system design
- Provide undo functionality for served customers

---

## 🧩 Data Structures Used

### 🔹 Manual Implementations (Learning Phase)
- Stack (Array-based implementation with push/pop/peek)
- Queue (Array-based implementation with front/rear logic)

### 🔹 STL Implementations (Final System)
- Queue (STL `queue`) – Regular customers (FIFO)
- Priority Queue (STL `priority_queue`) – Priority-based scheduling
- Stack (STL `stack`) – Served customer history (Undo feature)

---

## ⚙️ Features

- Add customer (Regular or Priority)
- Assign priority levels for emergency cases
- Serve customers based on priority rules
- Undo last served customer
- Display current queues
- Track total number of customers in system

---

## 🔄 System Flow

1. Add customer to system  
2. Identify customer type (Regular or Priority)  
3. Place customer in correct data structure  
4. Serve Priority customers first  
5. If no priority customers exist, serve Regular customers  
6. Store served customers in Stack (history)  
7. Allow undo of last served customer  

---

## 🧠 How It Works

The system prioritizes emergency cases using a priority queue. Regular customers follow FIFO ordering. Every served customer is stored in a stack to allow undo functionality using LIFO behavior.
Manual implementations were first developed to understand how data structures work internally, then replaced/augmented with STL versions for system integration and efficiency.

---

## 🛠️ Technologies Used

- C++
- Data Structures:
  - Manual Stack (Array-based)
  - Manual Queue (Array-based)
  - STL Queue
  - STL Priority Queue (with custom comparator)
  - STL Stack

---

## 👥 Team Members

- Alvar, Kaixer Emmanuel Oscar Antonio M.   – Queue Implementation (Manual + STL understanding) 
- Manacop, Venice Anne M.                   – Stack / Undo Feature
- Zamora, Emmanuel Joshua P.                – Priority Queue Logic  

---

## 🚀 How to Run

### 1. Clone the repository
```bash
git clone https://github.com/your-username/your-repo-name.git
cd your-repo-name
```

### 2. Compile the code
```bash
g++ main.cpp -o gasqueue
```

### 3. Run the program
```bash
# Windows
gasqueue.exe

# Mac / Linux
./gasqueue
```

---

## How to Use

When the program starts you will see a menu:

===== GASQUEUE SYSTEM =====

Add Customer
Serve Customer
Undo Last Serve
Display Queues
Exit

- **Option 1** — Add a customer. You will be asked for their name and whether they are regular or priority. Priority customers can be Emergency (1) or Authority (2).
- **Option 2** — Serve the next customer. Priority customers are always served first.
- **Option 3** — Undo the last serve and put the customer back in their queue.
- **Option 4** — Display everyone currently in both queues.
- **Option 5** — Exit the program.

---

## Priority Order

| Level | Type      |
|-------|-----------|
| 1     | Emergency |
| 2     | Authority |
| 0     | Regular   |

Emergency and authority customers are always served before regular customers regardless of arrival order.

---

## Notes

- Maximum of 50 customers allowed at a time.
- Regular customers are served in the order they arrived (FIFO).
- Priority customers are sorted by urgency, not arrival time.
