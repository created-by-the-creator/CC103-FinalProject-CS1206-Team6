# GasQueue: Fuel Distribution System
## ❓ Problem Description
The ongoing global oil shortage has led to limited fuel availability, causing long queues, transportation delays, and disruptions in essential services. Existing fuel distribution systems commonly follow a first-come, first-served approach, which does not consider urgency among users.

As a result, emergency responders and essential service vehicles may experience delays despite needing immediate access. Additionally, the lack of structured prioritization leads to inefficiency, unequal distribution, and difficulty in managing high-demand situations.

This project addresses these issues by developing a structured fuel distribution system that uses appropriate data structures to manage regular and priority users efficiently.

---

## 🧩 Data Structures Used

### 🔹 Queue
- **What it is:** A FIFO (First In, First Out) data structure.
- **Why used:** To manage regular customers fairly based on arrival order.

### 🔹 Priority Queue
- **What it is:** A data structure that serves elements based on priority level.
- **Why used:** To ensure urgent users (e.g., emergency cases) are served before regular customers.

### 🔹 Stack
- **What it is:** A LIFO (Last In, First Out) data structure.
- **Why used:** To store served customers and allow undoing the most recent transaction.

---

## ⚙️ Algorithm Explanation (Step-by-Step)

- Display menu options to the user using a loop.
- Accept user input for selected operation.

### Add Customer
- Input customer details.
- If regular → add to Queue.
- If priority → add to Priority Queue with assigned level.

### Serve Customer
- Check Priority Queue first.
- If not empty → serve highest priority customer.
- Else → serve from regular Queue.
- Store served customer in Stack.

### Undo Operation
- Retrieve last served customer from Stack.
- Return customer to their original queue.

### Display
- Display Priority Queue contents.
- Display Regular Queue contents using recursion.

---

## 🔁 Iterative vs Recursive Comparison

### Iterative
- Used in menu loop.
- Faster because it avoids function call overhead.
- Easier to control program flow.

### Recursive
- Used in displaying queue elements.
- Easier to understand for sequential traversal.
- Uses more memory due to function call stack.

---

## ⚖️ Design Decisions

- Queue was chosen for fairness in handling regular customers.
- Priority Queue was used to prioritize urgent cases efficiently.
- Stack was used to implement undo functionality.
- Recursion was used for clean and simple queue display logic.

### Trade-offs:
- Priority Queue does not preserve arrival order among same priority levels.
- Undo feature restores last action but not full system state.
- Recursion is less memory efficient than iteration but improves code clarity.

---

## 👥 Team Members

- Alvar, Kaixer Emmanuel Oscar Antonio M. – Queue Implementation  
- Manacop, Venice Anne M. – Stack / Undo Feature  
- Zamora, Emmanuel Joshua P. – Priority Queue Logic  

---

## 🙏 Acknowledgement

We would like to express our sincere gratitude to our instructor for guiding us in understanding data structures and their practical applications in this project. We also thank God for giving us the strength, knowledge, and perseverance to complete this project successfully.
