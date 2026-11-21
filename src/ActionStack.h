#ifndef ActionStack_H
#define ActionStack_H

class ActionStack {
private:
    struct Node {
        int action;
        Node* next;

        Node(int action) {
            this->action = action;
            next = nullptr;
        }
    };
    Node* top;

public:
    ActionStack() {
        top = nullptr;
    }

    ~ActionStack() {
        while (top != nullptr) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    void push(int action) {
        Node* newNode = new Node(action);
        newNode->next = top;
        top = newNode;
    }

    int pop() {
        if (isEmpty()) {
            return -1;
        }
        Node* temp = top;
        int action = top->action;

        top = top->next;
        delete temp;
        return action;
    }
};

#endif