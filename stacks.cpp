#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
};

struct Stack {
    Node* top;
};

void init(Stack &s) {
    s.top = nullptr;
}

void push(Stack &s, int x) {
    Node* newNode = new Node();
    newNode->data = x;
    newNode->next = s.top;
    s.top = newNode;
    cout << x << " pushed into stack\n";
}

void pop(Stack &s) {
    if (s.top == nullptr) {
        cout << "Stack Underflow\n";
        return;
    }
    cout << s.top->data << " popped from stack\n";
    Node* temp = s.top;
    s.top = s.top->next;
    delete temp;
}

int peek(Stack &s) {
    if (s.top == nullptr) {
        cout << "Stack is Empty\n";
        return -1;
    }
    return s.top->data;
}

bool isEmpty(Stack &s) {
    return (s.top == nullptr);
}

int main() {
    Stack s;
    init(s);
    return 0;
}