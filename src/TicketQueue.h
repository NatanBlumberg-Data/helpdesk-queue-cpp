#ifndef TicketQueue_H
#define TicketQueue_H

#include <iostream>
#include "Ticket.h"
#include <fstream>
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

    void addCSVTicket(int id, string student_name, string category, int minutes_needed) {
        Ticket ticket(id, student_name, category, minutes_needed);
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

        if (id >= next_id) {
            next_id = id + 1;
        }
    }

    void saveToFile(ofstream& file) const {
        Node* current = head;
        while (current != nullptr) {
            file << current->ticket.getId() << ","
                << current->ticket.getStudentName() << ","
                << current->ticket.getCategory() << ","
                << current->ticket.getMinutesNeeded() << endl;
            current = current->next;
        }
    }

    int getNextId() const {
        return next_id;
    }
    int getServedCount() const {
        return served_count;
    }

    void searchId(int id) {
        Node* current = head;
        int position = 1;
        int wait = 0;
        while (current != nullptr) {
            if (current->ticket.getId() == id) {
                cout << "Ticket ID: " << id << endl;
                cout << "Student: " << current->ticket.getStudentName() << endl;
                cout << "Position: " << position << endl;
                cout << "Estimated wait: " << wait << " minutes" << endl;
                return;
            }
            wait = wait + current->ticket.getMinutesNeeded();
            position = position + 1;
            current = current->next;
        }
        cout << "Ticket ID " << id << " not found." << endl;
    }

    void searchName(string studentName) {
        Node* current = head;
        int position = 1;
        int wait = 0;
        bool found = false;
        while (current != nullptr) {
            if (current->ticket.getStudentName() == studentName) {
                cout << "Ticket ID: " << current->ticket.getId() << endl;
                cout << "Student: " << studentName << endl;
                cout << "Position: " << position << endl;
                cout << "Estimated wait: " << wait << " minutes" << endl;
                cout << endl;
                found = true;
            }
            wait = wait + current->ticket.getMinutesNeeded();
            position = position + 1;
            current = current->next;
        }
        if (found == false) {
            cout << "No tickets found for " << studentName << "." << endl;
        }
    }

    int findPosition(int id) {
        Node* current = head;
        int position = 1;
        while (current != nullptr) {
            if (current->ticket.getId() == id) {
                return position;
            }
            position = position + 1;
            current = current->next;
        }
        return -1;
    }

    Ticket getTicketAt(int position) {
        Node* current = head;
        int i = 1;
        while (current != nullptr) {
            if (i == position) {
                return current->ticket;
            }
            i = i + 1;
            current = current->next;
        }
        return Ticket(0, "", "", 0);
    }

    bool cancel(int id) {
        Node* prev = nullptr;
        Node* current = head;
        while (current != nullptr && current->ticket.getId() != id) {
            prev = current;
            current = current->next;
        }
        if (current == nullptr) {
            return false;
        }
        if (prev == nullptr) {
            head = current->next;
        } else {
            prev->next = current->next;
        }
        if (current == tail) {
            tail = prev;
        }
        delete current;
        count = count - 1;
        return true;
    }

    void insertAt(int position, Ticket ticket) {
        Node* newNode = new Node(ticket);
        if (position <= 1 || isEmpty()) {
            newNode->next = head;
            head = newNode;
            if (tail == nullptr) {
                tail = newNode;
            }
        } else {
            Node* prev = head;
            int i = 1;
            while (i < position - 1 && prev->next != nullptr) {
                prev = prev->next;
                i = i + 1;
            }
            newNode->next = prev->next;
            prev->next = newNode;
            if (newNode->next == nullptr) {
                tail = newNode;
            }
        }
        count = count + 1;
    }

    void setNextId(int id) {
        next_id = id;
    }

    void setServedCount(int served) {
        served_count = served;
    }
};

#endif
