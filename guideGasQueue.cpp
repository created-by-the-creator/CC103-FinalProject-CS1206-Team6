// ============================================================
// GASQUEUE SYSTEM - Customer Queue Management
// ------------------------------------------------------------
// WHAT THIS PROGRAM DOES (simple version):
//   Imagine a gas station. People line up to get served.
//   Some people (like ambulances or police) get served FIRST
//   no matter how long others have been waiting.
//   This program manages those lines using DATA STRUCTURES.
// ============================================================

#include <iostream>   // lets us use cout (print) and cin (input)
#include <queue>      // gives us the queue and priority_queue tools
#include <stack>      // gives us the stack tool (like a stack of plates)
#include <string>     // lets us use words/text (strings)
using namespace std;  // so we don't have to type "std::" every time

#define MAX 50        // the MAXIMUM number of people allowed in the system at once
                      // think of it like: the gas station only has room for 50 people

// ============================================================
// STRUCT: Customer
// ------------------------------------------------------------
// A "struct" is like a folder that holds related info together.
// Here, each Customer has 3 pieces of info stored in one place.
// Think of it like a paper form each customer fills out.
// ============================================================
struct Customer {
    int id;        // a unique number given to each customer (like a ticket number)
    string name;   // the customer's name (e.g., "Juan")
    int priority;  // how urgent they are:
                   //   0 = regular customer (normal line)
                   //   1 = emergency/highest priority (served first)
                   //   2 = authority/secondary priority (served second)
};

// ============================================================
// STRUCT: Compare
// ------------------------------------------------------------
// This tells the priority queue HOW to sort customers.
// Lower priority NUMBER = served FIRST (1 before 2 before 0).
// Think of it like: 1st place wins, then 2nd, then everyone else.
//
// NOTE: The ">" makes it a MIN-heap (smallest number = highest priority).
//       Without this, C++ would use ">" by default making it a MAX-heap.
// ============================================================
struct Compare {
    bool operator()(Customer a, Customer b) {
        return a.priority > b.priority; // if a's priority number is bigger, b goes first
    }
};

// ============================================================
// FUNCTION: displayPriorityQueue (RECURSIVE)
// ------------------------------------------------------------
// This function PRINTS all customers in the priority queue.
// It calls ITSELF repeatedly until the queue is empty.
//
// RECURSION EXPLAINED (simple):
//   Imagine peeling an onion one layer at a time.
//   Each time: show the top layer, remove it, then peel again.
//   Stop when there are no more layers (base case).
//
// DEFENSE TIP: "I used recursion here instead of a loop to
//   demonstrate understanding of recursive thinking with
//   data structures. The base case is when the queue is empty."
// ============================================================
void displayPriorityQueue(priority_queue<Customer, vector<Customer>, Compare> pq) {
    // BASE CASE: if the queue is empty, stop — nothing left to show
    if (pq.empty()) return;

    // print the customer at the TOP (highest priority person)
    cout << pq.top().name << " (P" << pq.top().priority << ")\n";

    // remove the top customer so we can see the next one
    pq.pop();

    // RECURSIVE CALL: do the same thing again with the remaining queue
    displayPriorityQueue(pq);
}

// ============================================================
// FUNCTION: displayRegularQueue (RECURSIVE)
// ------------------------------------------------------------
// Same idea as above, but for the regular (normal) queue.
// Regular queue uses FIFO — First In, First Out.
// Think of it like a line at a cashier: whoever came first, leaves first.
//
// DEFENSE TIP: "Both display functions are passed by VALUE (copy),
//   so the original queues are NOT modified when displaying."
// ============================================================
void displayRegularQueue(queue<Customer> q) {
    // BASE CASE: if the queue is empty, stop
    if (q.empty()) return;

    // print the customer at the FRONT of the line
    cout << q.front().name << endl;

    // remove the front customer so we can see the next one
    q.pop();

    // RECURSIVE CALL: repeat for the rest of the queue
    displayRegularQueue(q);
}

// ============================================================
// MAIN FUNCTION — This is where the program starts running
// ============================================================
int main() {

    // REGULAR QUEUE: stores normal customers in FIFO order
    // (like a regular line — first come, first served)
    queue<Customer> regularQueue;

    // PRIORITY QUEUE: stores urgent customers
    // automatically sorts them so the most urgent is always at the top
    // uses our custom "Compare" rule to decide who goes first
    priority_queue<Customer, vector<Customer>, Compare> priorityQueue;

    // HISTORY STACK: remembers the last served customers
    // used for the UNDO feature — like Ctrl+Z on a computer
    // LIFO order: Last In, First Out (like a stack of plates)
    stack<Customer> historyStack;

    int totalCustomers = 0; // keeps count of how many people are currently in the system
    int idCounter = 1;      // starts ID numbers at 1, goes up every time someone is added
    int choice;             // stores what menu option the user picks

    // MAIN LOOP: keeps showing the menu until the user picks "Exit" (option 5)
    do {
        // display the main menu
        cout << "\n===== GASQUEUE SYSTEM =====\n";
        cout << "1. Add Customer\n";
        cout << "2. Serve Customer\n";
        cout << "3. Undo Last Serve\n";
        cout << "4. Display Queues\n";
        cout << "5. Exit\n";
        cout << "----------------------------\n";
        cout << "Enter choice: ";
        cin >> choice;        // read what number the user typed
        cout << "----------------------------\n";
        cin.ignore();         // clears leftover newline from the input buffer
                              // (prevents bugs when using getline() after cin)

        // SWITCH: checks which option was chosen and runs that block
        switch(choice) {

        // ========================================================
        // CASE 1: ADD A CUSTOMER
        // ========================================================
        case 1: {
            // check if the system is already full
            if (totalCustomers >= MAX) {
                cout << "System FULL.\n"; // cannot add more than MAX customers
                break;
            }

            Customer c;           // create a new empty customer
            c.id = idCounter++;   // assign the next available ID, then increase the counter
                                  // e.g., first customer gets ID 1, next gets 2, and so on

            cout << "----------------------------\n";
            cout << "Enter name: ";
            getline(cin, c.name); // read the full name (including spaces) into c.name
            cout << "----------------------------\n";

            int type;
            cout << "1. Regular\n2. Priority\nChoice: ";
            cin >> type; // ask if the customer is regular or priority

            if (type == 1) {
                // REGULAR CUSTOMER: goes to the back of the normal line
                c.priority = 0;           // 0 means regular (lowest priority)
                regularQueue.push(c);     // add to the regular queue
                cout << c.name << " added to REGULAR queue.\n";

            } else if (type == 2) {
                // PRIORITY CUSTOMER: ask HOW urgent they are
                cout << "Priority level:\n";
                cout << "1 - Emergency\n2 - Authority\nChoice: ";
                cin >> c.priority; // 1 = emergency (served first), 2 = authority (served second)

                // validate: only 1 or 2 are valid priority levels
                if (c.priority != 1 && c.priority != 2) {
                    cout << "Invalid priority.\n";
                    break; // exit this case without adding anyone
                }

                priorityQueue.push(c); // add to the priority queue (auto-sorted by Compare)
                cout << c.name << " added to PRIORITY queue.\n";

            } else {
                cout << "Invalid type.\n"; // user typed something other than 1 or 2
                break;
            }

            totalCustomers++; // one more person is now in the system
            break;
        }

        // ========================================================
        // CASE 2: SERVE THE NEXT CUSTOMER
        // ========================================================
        // DEFENSE TIP: "Priority customers are always served before
        //   regular ones. Only when the priority queue is empty do
        //   we move on to the regular queue. This simulates real-world
        //   priority-based service (e.g., PWDs, seniors, emergency)."
        // ========================================================
        case 2: {
            Customer served; // will hold whoever gets served next

            if (!priorityQueue.empty()) {
                // if there's anyone in the priority queue, serve them first
                served = priorityQueue.top(); // peek at the most urgent customer
                priorityQueue.pop();           // remove them from the queue
                cout << "Serving PRIORITY: " << served.name << endl;

            } else if (!regularQueue.empty()) {
                // no priority customers — serve the first regular customer
                served = regularQueue.front(); // peek at the front of the regular line
                regularQueue.pop();            // remove them from the queue
                cout << "Serving REGULAR: " << served.name << endl;

            } else {
                // both queues are empty — nobody to serve
                cout << "No customers available.\n";
                break;
            }

            historyStack.push(served); // save this customer to history (for undo)
            totalCustomers--;          // one less person in the system
            break;
        }

        // ========================================================
        // CASE 3: UNDO THE LAST SERVE
        // ========================================================
        // DEFENSE TIP: "The stack gives us O(1) access to the most
        //   recently served customer, making undo very efficient.
        //   This is why a stack (LIFO) is the right data structure here."
        // ========================================================
        case 3: {
            // check if there's anything to undo
            if (historyStack.empty()) {
                cout << "Nothing to undo.\n";
                break;
            }

            // check if the system can accept the customer back
            if (totalCustomers >= MAX) {
                cout << "Cannot undo. System full.\n";
                break;
            }

            Customer last = historyStack.top(); // get the most recently served customer
            historyStack.pop();                 // remove them from history

            if (last.priority == 0) {
                // they were a regular customer — put them back in the regular queue
                regularQueue.push(last);
                cout << last.name << " returned to REGULAR queue.\n";
            } else {
                // they were a priority customer — put them back in the priority queue
                priorityQueue.push(last);
                cout << last.name << " returned to PRIORITY queue.\n";
            }

            totalCustomers++; // they're back in the system
            break;
        }

        // ========================================================
        // CASE 4: DISPLAY ALL QUEUES
        // ========================================================
        // DEFENSE TIP: "We pass the queues by value (copy) to the
        //   display functions so the originals remain unchanged.
        //   The recursion mimics traversal without using a loop."
        // ========================================================
        case 4: {
            cout << "\n--- PRIORITY QUEUE ---\n";
            if (priorityQueue.empty()) cout << "Empty\n";
            else displayPriorityQueue(priorityQueue); // call recursive display function

            cout << "\n--- REGULAR QUEUE ---\n";
            if (regularQueue.empty()) cout << "Empty\n";
            else displayRegularQueue(regularQueue);   // call recursive display function

            // show how many people are in the system vs the maximum allowed
            cout << "\nTotal: " << totalCustomers << "/" << MAX << endl;
            break;
        }

        // choice 5 exits the do-while loop (handled by the while condition below)

        } // end of switch

    } while (choice != 5); // keep looping until user picks Exit

    cout << "System terminated.\n"; // goodbye message
    return 0; // 0 means the program ended successfully
}

// ============================================================
// QUICK DEFENSE CHEAT SHEET
// ------------------------------------------------------------
// Q: Why use a priority_queue?
//    A: It automatically keeps the most urgent customer at the
//       top, so we don't have to manually sort every time.
//
// Q: Why use a stack for history?
//    A: Stacks are LIFO — perfect for undo because we always
//       want to reverse the MOST RECENT action first.
//
// Q: Why use recursion for display?
//    A: To demonstrate understanding of recursion with data
//       structures. Base case = empty queue. Recursive case =
//       print top/front, pop, call self again.
//
// Q: What is the time complexity of serving a customer?
//    A: O(log n) for priority queue (heap operations),
//       O(1) for regular queue and stack.
//
// Q: What does cin.ignore() do?
//    A: It clears the leftover newline character from the
//       input buffer so getline() works correctly after cin >>.
// ============================================================