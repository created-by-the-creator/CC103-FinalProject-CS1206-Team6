#include <iostream>
using namespace std;

// Official file draft for GasQueue: Fuel Distribution System

#define MAX 50 // Maximum number of customers allowed in the stack

// Struct to hold customer identification details
struct Customer {
    string name; // Full name of the customer
    string type; // Customer type: "Regular" or "Priority"
};

// Manual implementation of a stack using a fixed-size array
class Stack {

private:
    Customer arr[MAX]; // Array to store customers in the stack
    int top;           // Index of the topmost customer (-1 if empty)

public:
    // Constructor: initializes the stack as empty
    Stack() {
        top = -1;
    }

    // Returns true if the stack has no customers
    bool isEmpty() {
        return top == -1;
    }

    // Returns true if the stack has reached maximum capacity
    bool isFull() {
        return top == MAX - 1;
    }

    // Adds a customer to the top of the stack (Push operation)
    void push(Customer person) {
        if (isFull()) {
            cout << "Designated fuel queue is already full. Please try again later.\n";
            return;
        }

        top++;           // Move top pointer up
        arr[top] = person; // Store the customer at the new top position

        cout << "Customer \"" << person.name << "\" (" << person.type << ") added to queue.\n";
    }

    // Removes and returns the most recently added customer (Pop operation)
    Customer pop() {
        if (isEmpty()) {
            cout << "No customers in queue.\n";
            return Customer{"", ""}; // Return empty customer as sentinel value
        }

        Customer person = arr[top]; // Retrieve the top customer
        top--;                      // Move top pointer down
        return person;
    }

    // Returns the top customer without removing them (Peek operation)
    Customer peek() {
        if (isEmpty()) {
            return {"", ""}; // Return empty customer if stack is empty
        }
        return arr[top];
    }

    // Displays all customers in the stack from top (most recent) to bottom (oldest)
    void display() {
        if (isEmpty()) {
            cout << "The queue is currently empty.\n";
            return;
        }

        cout << "\n===== CURRENT QUEUE (Top to Bottom) =====\n";

        // Loop from top to bottom to reflect LIFO order
        for (int i = top; i >= 0; i--) {
            cout << "[" << (top - i + 1) << "] "
                 << arr[i].name << " (" << arr[i].type << ")\n";
        }

        cout << "==========================================\n";
    }
};

int main() {

    Stack undoStack; // Stack object to manage the fuel distribution queue
    int choice;

    do {
        // Display menu options
        cout << "\n===== GasQueue: Fuel Distribution System =====\n";
        cout << "1. Add Customer to Queue (Push)\n";
        cout << "2. Undo Last Entry (Pop)\n";
        cout << "3. View Next to be Undone (Peek)\n";
        cout << "4. Display Full Queue\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1: {
                Customer c;

                cin.ignore(); // Clear leftover newline from input buffer

                // Get customer name
                cout << "Enter customer name: ";
                getline(cin, c.name);

                // Get and validate customer type
                cout << "Enter type (Regular/Priority): ";
                getline(cin, c.type);

                if (c.type != "Regular" && c.type != "Priority") {
                    cout << "Invalid type. Please enter \"Regular\" or \"Priority\".\n";
                    break;
                }

                // Push validated customer to stack
                undoStack.push(c);
                break;
            }

            case 2: {
                // Pop the most recently added customer
                Customer removed = undoStack.pop();

                if (removed.name != "") {
                    cout << "Undo: Customer \"" << removed.name << "\" removed from queue.\n";
                }
                break;
            }

            case 3: {
                // Peek at the top customer without removing
                Customer next = undoStack.peek();

                if (next.name != "") {
                    cout << "Next to be undone: " << next.name << " (" << next.type << ")\n";
                } else {
                    cout << "No customers in queue.\n";
                }
                break;
            }

            case 4:
                // Display all customers in the stack
                undoStack.display();
                break;

            case 5:
                cout << "Exiting GasQueue. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please enter a number from 1 to 5.\n";
        }

    } while (choice != 5); // Keep looping until user chooses to exit

    return 0;
}