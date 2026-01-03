#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

struct Queue {
    Node* front;
    Node* rear;
};

void init(Queue &q) {
    q.front = q.rear = nullptr;
}

bool isEmpty(Queue &q) {
    return (q.front == nullptr);
}

void enqueue(Queue &q, int value) {
    Node* temp = new Node();     
    temp->data = value;
    temp->next = nullptr;
    temp->prev = q.rear;

    if (q.rear == nullptr) {      
        q.front = q.rear = temp;
    } else {                     
        q.rear->next = temp;
        q.rear = temp;
    }
    cout << value << " enqueued" << endl;
}

void dequeue(Queue &q) {
    if (isEmpty(q)) { 
        cout << "Queue underflow! Queue is empty..." << endl;
        return;
    }

    Node* temp = q.front;          
    cout << q.front->data << " dequeued" << endl;
    q.front = q.front->next;

    if (q.front == nullptr)  {
        q.rear = nullptr;
    }            

    delete temp;
}

int peek(Queue &q) {
    if (isEmpty(q)) {
        cout << "Queue is empty" << endl;
        return -1;
    }
    return q.front->data;
}

void clone(Queue &q) {
    if (isEmpty(q)) {
        cout << "There's nothing to clone." << endl;
        return;
    }  
    Node* temp = q.front;
    Node* prevRear = q.rear;
    
    while (temp != nullptr) {
        Node* clone = new Node();
        clone->data = temp->data;
        clone->next = nullptr;
    
        q.rear->next = clone;
        q.rear = clone;
        cout << temp->data << " cloned" << endl;
        temp = temp->next;

        if (temp == prevRear->next) {
            break;
        }
    }
}

void reverse(Queue &q) {
    if (isEmpty(q)) {
        cout << "Queue is empty" << endl;
        return;
    }
    
    Node* prev = nullptr;
    Node* currFront = q.front;
    Node* next = nullptr;
    
    Node* temp = q.front;
    q.front = q.rear;
    q.rear = temp;
    
    while (currFront != nullptr) {
        next = currFront->next;
        currFront->next = prev;
        prev = currFront;
        currFront = next;
    }
    cout << "Queue is reversed" << endl;
}

void multipleEnqueue(Queue &q, int value[], int length) {
    for (int i = 0; i < length; i++) {
        enqueue(q,value[i]);
    }
}

void multipleDequeue(Queue &q, int quantity) {
    for (int i = 0; i < quantity; i++) {
        dequeue(q);
    }
}

void displayAll(Queue &q) {
    Node* temp = q.front;
    
    cout << "In-queue: ";
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->next != nullptr) {
            cout << ", ";
        }
        temp = temp->next;
    }
    cout << "\n" << endl;
}

int main() {
    Queue q;
    init(q);
    
    int choice = 0;
    
    while (choice != 9) {
        cout << "\n|========= QUEUE =========|" << endl;
        cout << "What would you like to do?" << endl;
        cout << "  1) Enqueue" << endl
             << "  2) Dequeue" << endl
             << "  3) Multiple Enqueue" << endl
             << "  4) Multiple Dequeue" << endl
             << "  5) Peek" << endl
             << "  6) Display All" << endl
             << "  7) Reverse the queue" << endl
             << "  8) Clone current queue" << endl
             << "  9) Exit" << endl;
        cout << "Input here: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: {
                cout << "Value: ";
                int value;
                cin >> value;
                enqueue(q, value);
                break;
            }
            case 2:
                dequeue(q);
                break;
                
            case 3: {
                cout << "Enter values (enter -1 to stop):" << endl;
                int value;
                int count = 0;
                int arrSize = 10;
                int* values = new int[arrSize];
                
                while (true) {
                    cin >> value;
                    
                    if (value == -1) {
                        break;
                    }
                    
                    if (count >= arrSize) {
                        arrSize *= 2; 
                        int* newValues = new int[arrSize];
                        
                        for (int i = 0; i < count; i++) {
                            newValues[i] = values[i];
                        }
                        delete[] values;
                        values = newValues;
                    }
                    values[count] = value;
                    count++;
                }
                multipleEnqueue(q, values, count);
                delete[] values;
                break;
            }
            case 4: {
                cout << "How many do you want to dequeue? ";
                int toDequeue;
                cin >> toDequeue;
                multipleDequeue(q, toDequeue);
                break;
            }
            case 5: {
                int front = peek(q);
                if (front != -1) {
                    cout << "Front element: " << front << endl;
                }
                break;
            }
            case 6:
                displayAll(q);
                break;
                
            case 7:
                reverse(q);
                break;
                
            case 8:
                clone(q);
                break;
                
            case 9:
                cout << "Exiting.\n" << "Leonardo, Jan Eriz Angelo S.\n" << "CPE-2B<<" << endl;
                break;
                
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
    
    return 0;
}