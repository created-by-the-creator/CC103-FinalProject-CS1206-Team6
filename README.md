# ⛽ GasQueue: Fuel Distribution System

> A priority-based fuel distribution system that ensures emergency and authority vehicles are served first — no matter how long the line gets.

![C++](https://img.shields.io/badge/Language-C++-blue) ![Data Structures](https://img.shields.io/badge/Topic-Data%20Structures-green)

---

## ❓ Problem Description

The ongoing global oil shortage has led to limited fuel availability, causing long queues, transportation delays, and disruptions in essential services. Existing fuel distribution systems commonly follow a **first-come, first-served** approach, which does not consider urgency among users.

As a result, emergency responders and essential service vehicles may experience delays despite needing immediate access. Additionally, the lack of structured prioritization leads to inefficiency, unequal distribution, and difficulty in managing high-demand situations.

This project addresses these issues by developing a structured fuel distribution system that uses appropriate data structures to manage regular and priority users efficiently.

---

## 🧩 Data Structures Used

### 🔹 Queue
- **What it is:** A FIFO (First In, First Out) data structure.
- **Why used:** To manage regular customers fairly based on arrival order.

### 🔹 Priority Queue
- **What it is:** A min-heap that serves elements based on priority level.
- **Why used:** To ensure urgent users (emergency, authority) are always served before regular customers. Auto-sorts using a custom `Compare` struct — no manual sorting needed.

### 🔹 Stack
- **What it is:** A LIFO (Last In, First Out) data structure.
- **Why used:** To store served customers and allow undoing the most recent transaction in O(1) time.



---

## 🏛️ OOP Design

The system is built using a single class `GasQueueSystem` that encapsulates all data and behavior.

### Private (hidden internals)
| Member | Description |
|---|---|
| `regularQueue` | Normal customer line |
| `priorityQueue` | Urgent customer lane |
| `historyStack` | Undo log of served customers |
| `totalCustomers` | Current count in system |
| `idCounter` | Auto-incrementing ID tracker |
| `displayPriorityRecursive()` | Recursive display helper |
| `displayRegularRecursive()` | Recursive display helper |
| `searchBy...()` | Search helper functions |
| `clearInput()` | Input buffer cleaner |

### Public (accessible functions)
| Function | Description |
|---|---|
| `GasQueueSystem()` | Constructor — sets up initial state |
| `addCustomer()` | Add a customer to the correct queue |
| `serveCustomer()` | Serve the next customer |
| `undoLastServe()` | Undo the most recent serve |
| `displayQueues()` | Show all waiting customers |
| `searchCustomer()` | Find a customer by name or ID |
| `run()` | Main menu loop |

---

## ⚙️ Algorithm Explanation (Step-by-Step)

### 1. Add Customer
- Input customer name and type (regular or priority)
- If regular → push to `regularQueue` with priority = 0
- If priority → ask level (1 = Emergency, 2 = Authority) → push to `priorityQueue`
- Priority queue auto-sorts via `Compare` — smallest number floats to top

### 2. Serve Customer
- Check `priorityQueue` first — if not empty, serve top customer
- Else serve the front of `regularQueue`
- Push served customer to `historyStack` for possible undo

### 3. Undo Last Serve
- Pop top of `historyStack` (most recently served customer)
- If priority = 0 → return to `regularQueue`
- Else → return to `priorityQueue`

### 4. Search Customer *(new)*
- Choose to search by name or ID
- Searches `priorityQueue` first, then `regularQueue`
- Queues are passed by value (copy) — originals remain unchanged
- Returns which queue the customer was found in

### 5. Display Queues
- Calls recursive helper functions to print each queue
- Base case: queue is empty → stop recursion
- Queues passed by value so originals are not modified during display

---

## ⏱️ Time Complexity

| Operation | Complexity | Reason |
|---|---|---|
| Add regular customer | O(1) | Append to back of queue |
| Add priority customer | O(log n) | Heap insertion finds correct position |
| Serve customer | O(log n) | Heap removal reshuffles order |
| Undo last serve | O(1) | Stack top always = most recent |
| Display queues | O(n) | Visits every customer via recursion |
| Search by name / ID | O(n) | Linear scan — worst case checks all |

---

## 🔁 Iterative vs Recursive

### Iterative
- Used in the main menu loop and search functions
- Faster — avoids function call overhead
- Easier to control program flow

### Recursive
- Used in display functions (`displayPriorityRecursive`, `displayRegularRecursive`)
- Clean and readable traversal logic
- Base case = empty queue; recursive case = print, pop, call self again
- Uses more memory due to function call stack

---

## ⚖️ Design Decisions & Trade-offs

- **Queue** was chosen for fairness — regular customers served in strict arrival order
- **Priority Queue** was used so urgent cases are served efficiently without manual sorting
- **Stack** was used for undo — O(1) access to the most recent action makes it the best fit
- **OOP Class** keeps all data private and functions organized — `main()` stays clean at just 2 lines
- Priority queue does **not** preserve arrival order among customers of the same priority level
- Undo restores the last served customer only — not the full system state
- Recursion improves display clarity but is less memory-efficient than a loop
- Search is O(n) linear — acceptable given the system maximum of 50 customers

---

## 👥 Team Members

| Name | Role |
|---|---|
| Alvar, Kaixer Emmanuel Oscar Antonio M. | Queue Implementation |
| Manacop, Venice Anne M. | Stack / Undo Feature |
| Zamora, Emmanuel Joshua P. | Priority Queue Logic |

---

## 🙏 Acknowledgement

We would like to express our sincere gratitude to our instructor for guiding us in understanding data structures and their practical applications in this project. We also thank God for giving us the strength, knowledge, and perseverance to complete this project successfully.
