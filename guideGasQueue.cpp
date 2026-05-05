// ============================================================
// GASQUEUE SYSTEM - OOP Version
// ------------------------------------------------------------
// WHAT THIS PROGRAM DOES (simple version):
//   Same as before — manages a gas station queue where
//   emergency and authority vehicles get served FIRST.
//
//   BUT NOW it's written using OOP (Object-Oriented Programming).
//   Instead of dumping everything in main(), we pack all the
//   data and functions into one "class" called GasQueueSystem.
//
//   Think of a class like a vending machine:
//   - The buttons (functions) are on the outside (public)
//   - The internal mechanics are hidden inside (private)
// ============================================================

#include <iostream>   // lets us use cout (print) and cin (input)
#include <string>     // lets us use words/text (strings)
#include <queue>      // gives us queue and priority_queue tools
#include <stack>      // gives us the stack tool (like a stack of plates)
#include <vector>     // gives us vector (resizable list) — needed by priority_queue
#include <limits>     // gives us numeric_limits — used for clearing the input buffer safely
using namespace std;  // so we don't have to type "std::" every time

const int MAX = 50;   // maximum number of people allowed in the system at once
                      // "const" means this value never changes — it's a fixed rule

// ============================================================
// STRUCT: Customer
// ------------------------------------------------------------
// A "struct" is like a folder that holds related info together.
// Each Customer has 3 pieces of info stored in one place.
// Think of it like a paper form each customer fills out.
// ============================================================
struct Customer {
    int id;        // a unique number given to each customer (like a ticket number)
    string name;   // the customer's name (e.g., "Juan")
    int priority;  // how urgent they are:
                   //   0 = Regular customer (normal line)
                   //   1 = Emergency (served first)
                   //   2 = Authority (served second)
};

// ============================================================
// STRUCT: Compare
// ------------------------------------------------------------
// This tells the priority queue HOW to decide who goes first.
// Lower priority NUMBER = served FIRST (1 before 2 before 0).
//
// The "const" after each parameter means we promise not to
// accidentally change the customers while comparing them.
//
// DEFENSE TIP: "The '>' makes it a MIN-heap — the customer
//   with the SMALLEST priority number floats to the top."
// ============================================================
struct Compare {
    bool operator()(const Customer& a, const Customer& b) const {
        return a.priority > b.priority; // if a's number is bigger, b goes first
    }
};

// ============================================================
// CLASS: GasQueueSystem
// ------------------------------------------------------------
// This is the heart of the new version.
// A "class" bundles all the data (variables) and behavior
// (functions) of the gas queue system into one neat package.
//
// PRIVATE = only usable INSIDE the class (hidden internals)
// PUBLIC  = usable from OUTSIDE the class (buttons the user presses)
// ============================================================
class GasQueueSystem {
private:
    // --------------------------------------------------------
    // THE 3 MAIN CONTAINERS (same as the old version)
    // --------------------------------------------------------
    queue<Customer> regularQueue;
    // stores normal customers in FIFO order (first in, first out)
    // like a regular line at a cashier

    priority_queue<Customer, vector<Customer>, Compare> priorityQueue;
    // stores emergency/authority customers
    // automatically sorts itself — most urgent always at the top
    // uses our Compare rule to decide who's more urgent

    stack<Customer> historyStack;
    // remembers recently served customers for the UNDO feature
    // LIFO order: Last In, First Out (like a stack of plates)

    int totalCustomers; // tracks how many people are currently in the system
    int idCounter;      // keeps increasing so every customer gets a unique ID

    // ============================================================
    // PRIVATE FUNCTION: displayPriorityRecursive
    // ------------------------------------------------------------
    // Prints all customers in the priority queue one by one.
    // Uses RECURSION — it calls itself until the queue is empty.
    //
    // RECURSION EXPLAINED (simple):
    //   Like peeling an onion — show the top layer, remove it,
    //   then peel again. Stop when there are no more layers.
    //
    // NOTE: The queue is passed BY VALUE (a copy), so the real
    //   queue is NOT affected when we pop items to display them.
    //
    // DEFENSE TIP: "Base case = empty queue. Recursive case =
    //   print top customer, pop, call self again."
    // ============================================================
    void displayPriorityRecursive(priority_queue<Customer, vector<Customer>, Compare> pq) {
        // BASE CASE: if the queue is empty, stop — nothing left to show
        if (pq.empty()) return;

        Customer c = pq.top(); // peek at the most urgent customer
        pq.pop();              // remove them so we can see the next one

        // print the customer's ID and name
        cout << "ID: " << c.id << " | " << c.name;

        // print their priority label
        if (c.priority == 1) cout << " (Emergency)";
        else if (c.priority == 2) cout << " (Authority)";

        cout << endl;

        // RECURSIVE CALL: do the same thing for the rest of the queue
        displayPriorityRecursive(pq);
    }

    // ============================================================
    // PRIVATE FUNCTION: displayRegularRecursive
    // ------------------------------------------------------------
    // Same idea as above but for the regular (normal) queue.
    // Regular queue uses FIFO — first person in = first printed.
    // ============================================================
    void displayRegularRecursive(queue<Customer> q) {
        // BASE CASE: if the queue is empty, stop
        if (q.empty()) return;

        Customer c = q.front(); // peek at the front of the line
        q.pop();                // remove them so we can see the next one

        cout << "ID: " << c.id << " | " << c.name << endl;

        // RECURSIVE CALL: repeat for the rest of the queue
        displayRegularRecursive(q);
    }

    // ============================================================
    // PRIVATE FUNCTION: searchRegularByName
    // ------------------------------------------------------------
    // Looks through the regular queue to find a customer by name.
    // Returns TRUE if found, FALSE if not found.
    //
    // Uses a WHILE LOOP instead of recursion here — simpler for search.
    // The queue is passed by VALUE (copy) so the real queue is safe.
    // ============================================================
    bool searchRegularByName(queue<Customer> q, const string& name) {
        while (!q.empty()) {
            if (q.front().name == name) return true; // found!
            q.pop(); // not this one, check the next
        }
        return false; // went through everyone, not found
    }

    // ============================================================
    // PRIVATE FUNCTION: searchPriorityByName
    // ------------------------------------------------------------
    // Same as above but searches the priority queue by name.
    // ============================================================
    bool searchPriorityByName(priority_queue<Customer, vector<Customer>, Compare> pq, const string& name) {
        while (!pq.empty()) {
            if (pq.top().name == name) return true; // found!
            pq.pop(); // not this one, check the next
        }
        return false; // not found
    }

    // ============================================================
    // PRIVATE FUNCTION: searchRegularById
    // ------------------------------------------------------------
    // Looks through the regular queue to find a customer by ID number.
    // Returns TRUE if found, FALSE if not.
    // ============================================================
    bool searchRegularById(queue<Customer> q, int id) {
        while (!q.empty()) {
            if (q.front().id == id) return true; // found!
            q.pop();
        }
        return false;
    }

    // ============================================================
    // PRIVATE FUNCTION: searchPriorityById
    // ------------------------------------------------------------
    // Same as above but searches the priority queue by ID number.
    // ============================================================
    bool searchPriorityById(priority_queue<Customer, vector<Customer>, Compare> pq, int id) {
        while (!pq.empty()) {
            if (pq.top().id == id) return true; // found!
            pq.pop();
        }
        return false;
    }

    // ============================================================
    // PRIVATE FUNCTION: clearInput
    // ------------------------------------------------------------
    // Cleans up the input buffer after using cin >>.
    //
    // WHY THIS EXISTS:
    //   When you type "1" and press Enter, cin >> reads "1" but
    //   leaves the Enter key ('\n') stuck in the buffer.
    //   If we then use getline(), it reads that leftover Enter
    //   instead of waiting for your real input — causing bugs.
    //
    //   cin.clear()  → resets any error flags on cin
    //   cin.ignore() → throws away everything up to the next Enter
    //
    // DEFENSE TIP: "This is a reusable helper — cleaner than
    //   writing cin.ignore() manually everywhere."
    // ============================================================
    void clearInput() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // numeric_limits<streamsize>::max() just means "ignore as many
        // characters as needed" — a safe way to clear the whole buffer
    }

public:
    // ============================================================
    // CONSTRUCTOR: GasQueueSystem()
    // ------------------------------------------------------------
    // A constructor runs AUTOMATICALLY when you create the class.
    // Think of it like the "setup" step — runs once at the start.
    //
    // Here it just sets the counters to their starting values.
    // ============================================================
    GasQueueSystem() {
        totalCustomers = 0; // nobody in the system yet
        idCounter = 1;      // first customer will get ID #1
    }

    // ============================================================
    // PUBLIC FUNCTION: addCustomer
    // ------------------------------------------------------------
    // Asks the user for a name and type, then adds them to the
    // correct queue (regular or priority).
    // ============================================================
    void addCustomer() {
        // check if the system is already full
        if (totalCustomers >= MAX) {
            cout << "System FULL.\n";
            return; // stop here, don't add anyone
        }

        Customer c;           // create a new empty customer
        c.id = idCounter++;   // assign the next available ID, then increase the counter
                              // e.g., first customer gets ID 1, next gets 2, and so on

        cout << "Enter customer name: ";
        getline(cin, c.name); // read full name including spaces

        int type;
        cout << "1. Regular\n";
        cout << "2. Priority\n";
        cout << "Choice: ";
        cin >> type;

        // cin.fail() checks if the user typed something that's NOT a number
        // e.g., they typed "abc" instead of "1" or "2"
        if (cin.fail()) {
            clearInput();
            cout << "Invalid input.\n";
            return;
        }

        if (type == 1) {
            // REGULAR CUSTOMER: goes to the back of the normal line
            c.priority = 0;
            regularQueue.push(c);
            cout << c.name << " added to REGULAR queue.\n";
        }
        else if (type == 2) {
            // PRIORITY CUSTOMER: ask HOW urgent they are
            cout << "Priority Level:\n";
            cout << "1. Emergency\n";
            cout << "2. Authority\n";
            cout << "Choice: ";
            cin >> c.priority;

            // validate: only 1 or 2 are valid — anything else is rejected
            if (cin.fail() || (c.priority != 1 && c.priority != 2)) {
                clearInput();
                cout << "Invalid priority level.\n";
                return;
            }

            priorityQueue.push(c); // auto-sorted by Compare rule
            cout << c.name << " added to PRIORITY queue.\n";
        }
        else {
            cout << "Invalid type.\n";
            return;
        }

        totalCustomers++; // one more person is now in the system
        clearInput();     // clean up the input buffer for next use
    }

    // ============================================================
    // PUBLIC FUNCTION: serveCustomer
    // ------------------------------------------------------------
    // Serves the next customer in line.
    // Priority queue is ALWAYS checked first.
    // Only serves from regular queue when priority queue is empty.
    //
    // DEFENSE TIP: "This simulates real-world priority service —
    //   emergencies are never made to wait behind regular customers."
    // ============================================================
    void serveCustomer() {
        // check if both queues are empty — nobody to serve
        if (priorityQueue.empty() && regularQueue.empty()) {
            cout << "No customers available.\n";
            return;
        }

        Customer served; // will hold whoever gets served next

        if (!priorityQueue.empty()) {
            // someone urgent is waiting — serve them first
            served = priorityQueue.top(); // peek at most urgent customer
            priorityQueue.pop();           // remove them from the queue
            cout << "Serving PRIORITY customer: " << served.name << endl;
        }
        else {
            // no urgent customers — serve the first regular customer
            served = regularQueue.front(); // peek at front of normal line
            regularQueue.pop();            // remove them
            cout << "Serving REGULAR customer: " << served.name << endl;
        }

        historyStack.push(served); // save to history for possible undo
        totalCustomers--;          // one less person in the system
    }

    // ============================================================
    // PUBLIC FUNCTION: undoLastServe
    // ------------------------------------------------------------
    // Reverses the most recent serve — puts the customer back in queue.
    //
    // DEFENSE TIP: "The stack gives us O(1) access to the most
    //   recently served customer. LIFO is perfect for undo because
    //   we always reverse the MOST RECENT action first."
    // ============================================================
    void undoLastServe() {
        // nothing in history means nothing to undo
        if (historyStack.empty()) {
            cout << "Nothing to undo.\n";
            return;
        }

        // can't bring the customer back if the system is full
        if (totalCustomers >= MAX) {
            cout << "Cannot undo. System full.\n";
            return;
        }

        Customer last = historyStack.top(); // get the most recently served customer
        historyStack.pop();                  // remove them from history

        if (last.priority == 0) {
            // they were a regular customer — send them back to the regular line
            regularQueue.push(last);
            cout << last.name << " returned to REGULAR queue.\n";
        } else {
            // they were a priority customer — send them back to the priority lane
            priorityQueue.push(last);
            cout << last.name << " returned to PRIORITY queue.\n";
        }

        totalCustomers++; // they're back in the system
    }

    // ============================================================
    // PUBLIC FUNCTION: displayQueues
    // ------------------------------------------------------------
    // Shows all customers currently waiting in both queues.
    // Calls the recursive helper functions to print them.
    //
    // DEFENSE TIP: "We pass the queues by value (copy) to the
    //   recursive functions so the originals remain unchanged."
    // ============================================================
    void displayQueues() {
        cout << "\n===== PRIORITY QUEUE =====\n";
        if (priorityQueue.empty()) cout << "Empty\n";
        else displayPriorityRecursive(priorityQueue); // recursive display

        cout << "\n===== REGULAR QUEUE =====\n";
        if (regularQueue.empty()) cout << "Empty\n";
        else displayRegularRecursive(regularQueue);   // recursive display

        // show current count vs maximum allowed
        cout << "\nTotal Customers: " << totalCustomers << "/" << MAX << endl;
    }

    // ============================================================
    // PUBLIC FUNCTION: searchCustomer
    // ------------------------------------------------------------
    // NEW FEATURE (not in the old version).
    // Lets the user find a specific customer by name OR by ID.
    // Checks priority queue first, then regular queue.
    //
    // DEFENSE TIP: "Search is O(n) because we may need to check
    //   every customer in the worst case — it's a linear search."
    // ============================================================
    void searchCustomer() {
        int option;
        cout << "Search by:\n";
        cout << "1. Name\n";
        cout << "2. ID\n";
        cout << "Choice: ";
        cin >> option;

        if (cin.fail()) {
            clearInput();
            cout << "Invalid input.\n";
            return;
        }

        clearInput(); // clean buffer before using getline below

        if (option == 1) {
            // SEARCH BY NAME
            string name;
            cout << "Enter customer name: ";
            getline(cin, name); // read full name including spaces

            // check priority queue first, then regular queue
            if (searchPriorityByName(priorityQueue, name)) {
                cout << name << " found in PRIORITY queue.\n";
            }
            else if (searchRegularByName(regularQueue, name)) {
                cout << name << " found in REGULAR queue.\n";
            }
            else {
                cout << name << " not found.\n";
            }
        }
        else if (option == 2) {
            // SEARCH BY ID
            int id;
            cout << "Enter customer ID: ";
            cin >> id;

            if (cin.fail()) {
                clearInput();
                cout << "Invalid input.\n";
                return;
            }

            // check priority queue first, then regular queue
            if (searchPriorityById(priorityQueue, id)) {
                cout << "Customer ID " << id << " found in PRIORITY queue.\n";
            }
            else if (searchRegularById(regularQueue, id)) {
                cout << "Customer ID " << id << " found in REGULAR queue.\n";
            }
            else {
                cout << "Customer ID " << id << " not found.\n";
            }

            clearInput();
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    // ============================================================
    // PUBLIC FUNCTION: run
    // ------------------------------------------------------------
    // This is the main menu loop — it keeps showing options
    // until the user picks Exit (option 6).
    //
    // Think of this as the "engine" that drives the whole system.
    // It reads the user's choice and calls the right function.
    // ============================================================
    void run() {
        int choice;

        do {
            // display the main menu
            cout << "\n===== GASQUEUE SYSTEM =====\n";
            cout << "1. Add Customer\n";
            cout << "2. Serve Customer\n";
            cout << "3. Undo Last Serve\n";
            cout << "4. Display Queues\n";
            cout << "5. Search Customer\n";
            cout << "6. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            // if user typed a letter instead of a number, catch the error
            if (cin.fail()) {
                clearInput();
                cout << "Invalid input.\n";
                continue; // skip to the next loop iteration, show menu again
            }

            clearInput(); // clean buffer before any getline calls inside functions

            // run the function matching the user's choice
            switch (choice) {
                case 1: addCustomer(); break;
                case 2: serveCustomer(); break;
                case 3: undoLastServe(); break;
                case 4: displayQueues(); break;
                case 5: searchCustomer(); break;
                case 6: cout << "System terminated.\n"; break;
                default: cout << "Invalid choice.\n"; // anything other than 1-6
            }

        } while (choice != 6); // keep looping until user picks Exit
    }
};

// ============================================================
// MAIN FUNCTION — Entry point of the program
// ------------------------------------------------------------
// Much simpler than the old version.
// We just CREATE the system and CALL run().
// All the real work happens inside the class.
// ============================================================
int main() {
    GasQueueSystem system; // creates the object — constructor runs automatically
    system.run();          // starts the menu loop
    return 0;              // 0 means the program ended successfully
}

// ============================================================
// QUICK DEFENSE CHEAT SHEET
// ------------------------------------------------------------
// Q: Why use a class instead of just functions in main()?
//    A: A class keeps all related data and functions together.
//       It's cleaner, easier to debug, and easier to expand.
//
// Q: What is private vs public?
//    A: Private = hidden internals (the user can't touch these).
//       Public = the buttons exposed to the outside world.
//
// Q: Why use a priority_queue?
//    A: It automatically keeps the most urgent customer at the
//       top, so we don't have to manually sort every time.
//
// Q: Why use a stack for history?
//    A: Stacks are LIFO — perfect for undo because we always
//       want to reverse the MOST RECENT action first. O(1) access.
//
// Q: Why use recursion for display?
//    A: To demonstrate recursive thinking with data structures.
//       Base case = empty queue. Recursive case = print, pop, repeat.
//
// Q: What is the time complexity of search?
//    A: O(n) — worst case we check every customer in the queue.
//
// Q: What does clearInput() do?
//    A: It resets cin and clears the leftover newline from the
//       input buffer so getline() works correctly after cin >>.
//
// Q: What does the constructor do?
//    A: Sets totalCustomers to 0 and idCounter to 1 when the
//       system is first created — the "setup" step.
// ============================================================