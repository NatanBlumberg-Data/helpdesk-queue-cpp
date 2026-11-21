#ifndef TicketQueue_H
#define TicketQueue_H

#include <iostream>
#include "Ticket.h"
using namespace std;

class TicketQueue {
private:
    struct Node {
        Ticket ticket;
        Node* next;

        Node(Ticket ticket) : ticket(ticket) {
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;
    int count;
    int next_id;
    int served_count;

public:
    TicketQueue() {
        head = nullptr;
        tail = nullptr;
        count = 0;
        next_id = 1;
        served_count = 0;
    }

    ~TicketQueue() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }

        tail = nullptr;
        count = 0;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void add(string student_name, string category, int minutes_needed) {

        Ticket ticket(next_id, student_name, category, minutes_needed);

        Node* newNode = new Node(ticket);

        if (isEmpty()) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }

        count++;
        next_id++;

        cout << "Ticket added - ID: " << ticket.getId() << endl;
    }

    void serve() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }

        cout << "Serving ticket: " << head->ticket.getId() << endl;

        Node* temp = head;
        head = head->next;

        delete temp;

        count--;
        served_count++;

        if (head == nullptr) {
            tail = nullptr;
        }
    }

    void print() const {
        Node* current = head;
        int total_minutes = 0;

        if (isEmpty()) {
            cout << "No waiting tickets." << endl;
        }
        while (current != nullptr) {
            cout << "Ticket ID: " << current->ticket.getId() << endl;
            cout << "Student: " << current->ticket.getStudentName() << endl;
            cout << "Category: " << current->ticket.getCategory() << endl;
            cout << "Minutes Needed: " << current->ticket.getMinutesNeeded() << endl;
            cout << endl;

            total_minutes += current->ticket.getMinutesNeeded();
            current = current->next;
        }
        cout << "Total waiting minutes: " << total_minutes << endl;
    }
    int getNextId() const {
        return next_id;
    }
    int getServedCount() const {
        return served_count;
    }
};

#endif