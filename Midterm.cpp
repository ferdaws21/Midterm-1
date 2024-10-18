#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;          // Data held by the node
        Node* prev;       // Pointer to the previous node
        Node* next;       // Pointer to the next node
        
        // Constructor for the Node
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val;     // Initialize the data
            prev = p;      // Initialize the previous pointer
            next = n;      // Initialize the next pointer
        }
    };
    
    Node* head;  // Pointer to the first node in the list
    Node* tail;  // Pointer to the last node in the list

public:
    // Constructor to initialize an empty list
    DoublyLinkedList() { 
        head = nullptr; 
        tail = nullptr; 
    }

    // Method to insert a new node after a given position
    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }
        
        Node* newNode = new Node(value); // Create a new node with the given value
        
        if (!head) { // If the list is empty
            head = tail = newNode; // Set the new node as both head and tail
            return;
        }
        
        Node* temp = head; // Start at the head
        for (int i = 0; i < position && temp; ++i) // Traverse to the position
            temp = temp->next;

        if (!temp) { // If the position exceeds the list size
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; // Clean up the new node
            return;
        }

        newNode->next = temp->next; // Set the new node's next pointer
        newNode->prev = temp; // Set the new node's previous pointer
        
        if (temp->next) // If there is a next node
            temp->next->prev = newNode; // Update the previous pointer of the next node
        else
            tail = newNode; // If at the end, update the tail

        temp->next = newNode; // Link the new node in the list
    }

    // Method to delete a node by value
    void delete_val(int value) {
        if (!head) return; // If the list is empty

        Node* temp = head; // Start at the head
        while (temp && temp->data != value) // Search for the value
            temp = temp->next;

        if (!temp) return; // If not found, return

        // Adjust pointers to remove the node from the list
        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp; // Clean up the removed node
    }

    // Method to delete a node by position
    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        
        if (pos == 1) { // If deleting the first node
            pop_front();
            return;
        }
        
        Node* temp = head; // Start at the head
        for (int i = 1; i < pos; i++) {
            if (!temp) { // If position doesn't exist
                cout << "Position doesn't exist." << endl;
                return;
            }
            temp = temp->next; // Move to the next node
        }

        if (!temp) { // If position doesn't exist
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp->next) { // If deleting the last node
            pop_back();
            return;
        }

        // Adjust pointers to remove the node from the list
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;

        delete temp; // Clean up the removed node
    }

    // Method to push a value to the back of the list
    void push_back(int v) {
        Node* newNode = new Node(v); // Create a new node
        if (!tail) // If the list is empty
            head = tail = newNode; // Set head and tail to the new node
        else {
            tail->next = newNode; // Link the new node to the end
            newNode->prev = tail; // Set the new node's previous pointer
            tail = newNode; // Update the tail to the new node
        }
    }

    // Method to push a value to the front of the list
    void push_front(int v) {
        Node* newNode = new Node(v); // Create a new node
        if (!head) // If the list is empty
            head = tail = newNode; // Set head and tail to the new node
        else {
            newNode->next = head; // Link the new node to the front
            head->prev = newNode; // Set the current head's previous pointer
            head = newNode; // Update the head to the new node
        }
    }

    // Method to pop the front node
    void pop_front() {
        if (!head) { // If the list is empty
            cout << "List is empty." << endl;
            return;
        }
        
        Node* temp = head; // Store the current head
        if (head->next) { // If there is a next node
            head = head->next; // Move head to the next node
            head->prev = nullptr; // Update the new head's previous pointer
        } else // If only one node
            head = tail = nullptr; // Set head and tail to nullptr

        delete temp; // Clean up the removed node
    }

    // Method to pop the back node
    void pop_back() {
        if (!tail) { // If the list is empty
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = tail; // Store the current tail
        if (tail->prev) { // If there is a previous node
            tail = tail->prev; // Move tail to the previous node
            tail->next = nullptr; // Update the new tail's next pointer
        } else // If only one node
            head = tail = nullptr; // Set head and tail to nullptr

        delete temp; // Clean up the removed node
    }

    // Destructor to clean up the list
    ~DoublyLinkedList() {
        while (head) { // While there are nodes in the list
            Node* temp = head; // Store the current head
            head = head->next; // Move head to the next node
            delete temp; // Clean up the removed node
        }
    }

    // Method to print the list
    void print() {
        Node* current = head; // Start at the head
        if (!current) { // If the list is empty
            cout << "List is empty." << endl;
            return;
        }
        while (current) { // Traverse the list
            cout << current->data << " "; // Print the current node's data
            current = current->next; // Move to the next node
        }
        cout << endl; // New line after printing the list
    }

    // Method to print the list in reverse
    void print_reverse() {
        Node* current = tail; // Start at the tail
        if (!current) { // If the list is empty
            cout << "List is empty." << endl;
            return;
        }
        while (current) { // Traverse the list in reverse
            cout << current->data << " "; // Print the current node's data
            current = current->prev; // Move to the previous node
        }
        cout << endl; // New line after printing the list
    }

    // Method to print every other element
    void every_other_element() {
        Node* current = head; // Start at the head
        bool printElement = true; // Toggle to print every other element
        while (current) {
            if (printElement) { // Print the current node's data if toggled
                cout << current->data << " ";
            }
            printElement = !printElement; // Switch toggle to skip the next element
            current = current->next; // Move to the next node
        }
        cout << endl; // New line after printing
    }
};

int main() {
    DoublyLinkedList list; // Create an instance of the list

    // Add some elements to the list
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);
    list.push_back(50);

    // Print the entire list
    cout << "Full list: ";
    list.print();

    // Print every other element
    cout << "Every other element: ";
    list.every_other_element();

    return 0; // Exit the program
}
