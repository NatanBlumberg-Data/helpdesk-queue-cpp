#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "HelpDesk.h"
using namespace std;

bool isNumber(string text) {
    if (text.size() == 0 || text.size() > 9) {
        return false;
    }
    for (int i = 0; i < (int)text.size(); i++) {
        if (text[i] < '0' || text[i] > '9') {
            return false;
        }
    }
    return true;
}

int findSpace(string text) {
    for (int i = 0; i < (int)text.size(); i++) {
        if (text[i] == ' ') {
            return i;
        }
    }
    return -1;
}

string firstWord(string text) {
    int space = findSpace(text);
    if (space == -1) {
        return text;
    }
    return text.substr(0, space);
}

string restAfterFirstWord(string text) {
    int space = findSpace(text);
    if (space == -1) {
        return "";
    }
    return text.substr(space + 1);
}

string getField(string line, int index) {
    string field = "";
    int current = 0;
    for (int i = 0; i < (int)line.size(); i++) {
        if (line[i] == ',') {
            current = current + 1;
        } else if (current == index) {
            field = field + line[i];
        }
    }
    return field;
}

void runSimulation(vector<int> minutes, int agents) {
    vector<int> freeAt(agents);
    int totalWait = 0;
    int longestWait = 0;
    for (int i = 0; i < (int)minutes.size(); i++) {
        int agent = 0;
        for (int a = 1; a < agents; a++) {
            if (freeAt[a] < freeAt[agent]) {
                agent = a;
            }
        }
        int wait = freeAt[agent];
        freeAt[agent] = freeAt[agent] + minutes[i];
        totalWait = totalWait + wait;
        if (wait > longestWait) {
            longestWait = wait;
        }
    }
    double average = 0;
    if (minutes.size() > 0) {
        average = (double)totalWait / minutes.size();
    }
    cout << "Agents: " << agents << endl;
    cout << "Average wait: " << average << " minutes" << endl;
    cout << "Longest wait: " << longestWait << " minutes" << endl;
}

void simulateDay(string fileName) {
    ifstream file(fileName);
    if (file.is_open() == false) {
        cout << "Could not open " << fileName << endl;
        return;
    }
    vector<int> minutes;
    string line;
    getline(file, line);
    while (getline(file, line)) {
        string minutesText = getField(line, 2);
        if (isNumber(minutesText)) {
            minutes.push_back(stoi(minutesText));
        } else if (line != "") {
            cout << "Skipped line: " << line << endl;
        }
    }
    file.close();
    cout << "Tickets: " << minutes.size() << endl;
    cout << endl;
    runSimulation(minutes, 1);
    cout << endl;
    runSimulation(minutes, 2);
}

int main() {
    HelpDesk desk;
    string line;

    cout << "Help Desk Ticket System" << endl;
    cout << "Commands: add, serve, print, search id <id>, search name <name>, cancel <id>," << endl;
    cout << "undo, load <file>, save <file>, simulate <file>, quit" << endl;
    cout << "> ";

    while (getline(cin, line)) {
        string command = firstWord(line);
        string rest = restAfterFirstWord(line);
        if (command == "quit") {
            break;
        } else if (command == "add") {
            string studentName;
            string category;
            string minutesText;
            cout << "Student name: ";
            getline(cin, studentName);
            cout << "Category: ";
            getline(cin, category);
            cout << "Minutes needed: ";
            getline(cin, minutesText);
            if (isNumber(minutesText)) {
                desk.add(studentName, category, stoi(minutesText));
            } else {
                cout << "Minutes needed must be a whole number." << endl;
            }
        } else if (command == "serve") {
            desk.serve();
        } else if (command == "print") {
            desk.print();
        } else if (command == "search") {
            string kind = firstWord(rest);
            string value = restAfterFirstWord(rest);
            if (kind == "id" && isNumber(value)) {
                desk.searchId(stoi(value));
            } else if (kind == "name" && value != "") {
                desk.searchName(value);
            } else {
                cout << "Use: search id <id> or search name <name>" << endl;
            }
        } else if (command == "cancel") {
            if (isNumber(rest)) {
                desk.cancel(stoi(rest));
            } else {
                cout << "Use: cancel <id>" << endl;
            }
        } else if (command == "undo") {
            desk.undo();
        } else if (command == "load") {
            desk.load(rest);
        } else if (command == "save") {
            desk.save(rest);
        } else if (command == "simulate") {
            if (rest == "") {
                cout << "Use: simulate <file>" << endl;
            } else {
                simulateDay(rest);
            }
        } else if (command != "") {
            cout << "Unknown command." << endl;
        }
        cout << "> ";
    }

    return 0;
}
