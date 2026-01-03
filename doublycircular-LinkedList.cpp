#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
    Node *prev;
};

Node *currNode = nullptr;

void append(Node *&head, int value) {
    Node *newNode = new Node();
    newNode->data = value;
    if (head == nullptr) {
        head = newNode;
        head->next = head;
        head->prev = head;
    } else {
        Node *tail = head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
    }
}

void insertAtBeginning(Node *&head, int value) {
    Node *newNode = new Node();
    newNode->data = value;
    if (head == nullptr) {
        head = newNode;
        head->next = head;
        head->prev = head;
    } else {
        Node *tail = head->prev;
        newNode->next = head;
        newNode->prev = tail;
        tail->next = newNode;
        head->prev = newNode;
        head = newNode; // Update head to new node
    }
    cout << "Inserted " << value << " at the beginning.\n";
}

void insertAfter(Node *&head, int afterValue, int newValue) {
    if (head == nullptr) {
        cout << "List is empty, adding as first element.\n";
        append(head, newValue);
        return;
    }
    Node *temp = head;
    do {
        if (temp->data == afterValue) {
            Node *newNode = new Node();
            newNode->data = newValue;
            newNode->next = temp->next;
            newNode->prev = temp;
            temp->next->prev = newNode;
            temp->next = newNode;
            cout << "Inserted " << newValue << " after " << afterValue << ".\n";
            return;
        }
        temp = temp->next;
    } while (temp != head);
    cout << "Value " << afterValue << " not found in list.\n";
}

void displayAll(Node *head) {
    if (head == nullptr) {
        cout << "List is empty.\n";
        return;
    }
    cout << "Doubly Circular Linked List: ";
    Node *temp = head;
    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);
    cout << endl;
}

//-- FILLER LOGICS ---------------------------------------------------------------------------------------------------------------------------------
void append_info(Node *head) { // shows message for appended values after input ends
    Node *temp = head;
    cout << "Appended ";
    do {
        cout << temp->data << ", ";
        temp = temp->next;
        if (temp->next == head) {
            cout << "and " << temp->data;
            break;
        }
    } while (temp != head);
    cout << endl;
}

void LL_info(Node *head) { // js to check current status/structure of the linked list
    Node *temp = head;
    cout << "Nodes: " << endl;
    do {
        cout << temp->data << " (" << temp << ")   | " << " next: " << temp->next << " | " << "prev: " << temp->prev << endl;
        temp = temp->next;
    } while (temp != head);
    cout << "current head is " << head << endl;
}

void sort(Node *&head, int sorting_order) {
    if (!head || head->next == head) return; // empty or single node
    bool sorting = false;
    
    LL_info(head);
    switch (sorting_order) {
        case 1: // Least to Greatest
            do {
                Node *node1 = head; // inside do-while() so that we continuously update the head, and re-start from the new head;
                sorting = false;
                do {
                    Node *node2 = node1->next;
                    if (node1->data > node2->data) {
                        node1->prev->next = node2; // node->next of the prev node of node1 changes from node1 to node2
                        node2->prev = node1->prev; 
            
                        node2->next->prev = node1; // node->prev of the next node of node2 changes from node2 to node1
                        node1->prev = node2;
            
                        node1->next = node2->next;
                        node2->next = node1;
            
                        if (node1 == head){
                            head = node2;
                        } 
                        sorting = true;
                    }
                    else {
                        node1 = node1->next;
                    }
                } while (node1->next != head);
            } while (sorting);
            break;      
        
        case 2: // Greatest to Least
            do {
                Node *node1 = head; // inside do-while() so that we continuously update the head, and re-start from the new head;
                sorting = false;
                do {
                    Node *node2 = node1->next;
                    if (node1->data < node2->data) {
                        node1->prev->next = node2; // node->next of the prev node of node1 changes from node1 to node2
                        node2->prev = node1->prev; 
            
                        node2->next->prev = node1; // node->prev of the next node of node2 changes from node2 to node1
                        node1->prev = node2;
            
                        node1->next = node2->next;
                        node2->next = node1;
            
                        if (node1 == head){
                            head = node2;
                        } 
                        sorting = true;
                    }
                    else {
                        node1 = node1->next;
                    }
                } while (node1->next != head);
            } while (sorting);
            break;
    }
    LL_info(head);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------


void nextNode() {
    if (currNode != nullptr)
        currNode = currNode->next;
    else
        cout << "No current node selected.\n";
}

void prevNode() {
    if (currNode != nullptr)
        currNode = currNode->prev;
    else
        cout << "No current node selected.\n";
}

void getValue(Node *head) {
    if (head == nullptr) {
        cout << "List is empty.\n";
        return;
    }
    if (currNode == nullptr)
        currNode = head;
    cout << "Current data: " << currNode->data << endl;
}

void deleteElement(Node *&head, int value) {
    if (head == nullptr) {
        cout << "List is empty, nothing to delete.\n";
        return;
    }
    Node *temp = head;
    do {
        if (temp->data == value) {
            // Only one node
            if (temp->next == temp && temp->prev == temp) {
                head = nullptr;
            } else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                if (temp == head)
                    head = temp->next;
            }
            if (currNode == temp)
                currNode = head; // safer than temp->next after deletion
            delete temp;
            cout << "Deleted element: " << value << endl;
            return;
        }
        temp = temp->next;
    } while (temp != head);
    cout << "Element not found: " << value << endl;
}

void search(Node *&head, int value) {
    if (head == nullptr) {
        cout << "List is empty, adding as first element.\n";
        return;
    }
    Node *temp = head;
    do {
        if (temp->data == value) {
            cout << "Value " << value << " was found at address: " <<  *&temp; // temporary to be removed
            return;
        }
        temp = temp->next;
    } while (temp != head);
    cout << "Value " << value << " not found in list.\n";
}

int main() {
    Node *head = nullptr;
    int value, afterValue;
    char choice;

    cout << "Enter numbers (-1 to end):" << endl;
    while (true) {
        cin >> value;
        if (value == -1) break;
        append(head, value);
    }
    append_info(head);

    currNode = head;
    while (choice != -1) {
        cout << "\nChoose a function:\n";
        cout << "[1] next\n[2] prev\n[3] getValue\n[4] display all\n[5] delete element\n";
        cout << "[6] insert at beginning\n[7] insert after value\n[8] search\n[9] sort\n [-1] EXIT\n";
        cin >> choice;

        switch (choice) {
            case '1': nextNode(); break;
            case '2': prevNode(); break;
            case '3': getValue(head); break;
            case '4': displayAll(head); break;
            case '5':
                cout << "Enter value to delete: ";
                cin >> value;
                deleteElement(head, value);
                break;
            case '6':
                cout << "Enter value to insert at beginning: ";
                cin >> value;
                insertAtBeginning(head, value);
                break;
            case '7':
                cout << "Enter value to insert after: ";
                cin >> afterValue;
                cout << "Enter new value to insert: ";
                cin >> value;
                insertAfter(head, afterValue, value);
                break;
            case '8':
                cout << "Enter value to search for: ";
                cin >> value;
                search(head, value);
                break;
            

            case '9':
                int sorting_order;
                cout << "How do you want it to be sorted?\n1) Least to Greatest\n2) Greatest to Least" << endl;
                cin >> sorting_order;
                sort(head, sorting_order);
                break;
            default:
                cout << "Invalid input, please try again.\n";
                break;
        }
    }

    cout << "Exiting program.\n";
    return 0;
}
