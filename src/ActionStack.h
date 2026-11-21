#ifndef ActionStack_H
#define ActionStack_H

#include "Ticket.h" 

class ActionStack {
private:
    struct Node {
        int action;
        Node* next;
        Ticket ticket = Ticket(0, "", "", 0);
        int position = 0;

        Node(int action) {
            this->action = action;
            next = nullptr;
        }

        Node(int action, Ticket ticket, int position) : 
ticket(ticket) {
            this->action = action;
            this->position = position;
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

    void push(int action, Ticket ticket, int position) {
        Node* newNode = new Node(action, ticket, position);
        newNode->next = top;
        top = newNode;
    }

    Ticket peekTicket() {
        if (isEmpty()) {
            return Ticket(0, "", "", 0);
        }
        return top->ticket;
    }

    int peekPosition() {
        if (isEmpty()) {
            return -1;
        }
        return top->position;
    }
};

#endif
