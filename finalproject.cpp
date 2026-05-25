#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

// ================= NODE =================
struct Message {
    int id;
    string text;
    Message* next;
};

// ================= HEADS =================
Message* sobiaHead = NULL;
Message* atifaHead = NULL;

int messageID = 1;

// ================= CREATE =================
Message* createMessage(int id, string text) {
    Message* temp = new Message;
    temp->id = id;
    temp->text = text;
    temp->next = NULL;
    return temp;
}

// ================= INSERT =================
void insertMessage(Message*& head, int id, string text) {
    Message* newNode = createMessage(id, text);

    if (head == NULL) {
        head = newNode;
    } else {
        Message* temp = head;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

// ================= CLEAR SCREEN =================
void clearScreen() {
    system("cls");
}

// ================= DISPLAY =================
void displayChats() {

    clearScreen();

    cout << "=========== CHAT SIMULATION ===========\n\n";

    cout << "SOBIA CHAT               |               ATIFA CHAT\n";
    cout << "------------------------------------------------------\n";

    Message* t1 = sobiaHead;
    Message* t2 = atifaHead;

    while (t1 != NULL || t2 != NULL) {

        // LEFT SIDE
        if (t1 != NULL) {
            cout << t1->text;
        }

        int len1 = (t1 != NULL) ? t1->text.length() : 0;

        for (int i = len1; i < 25; i++) {
            cout << " ";
        }

        cout << "| ";

        // RIGHT SIDE
        if (t2 != NULL) {
            cout << t2->text;
        }

        cout << endl;

        if (t1 != NULL) t1 = t1->next;
        if (t2 != NULL) t2 = t2->next;
    }

    cout << endl;
}

// ================= SEND MESSAGE =================
void sendMessage() {

    string text;

    cin.ignore();

    cout << "Enter message for Atifa: ";
    getline(cin, text);

    int id = messageID++;

    insertMessage(sobiaHead, id, text);
    insertMessage(atifaHead, id, text);

    cout << "Message sent\n";

    Sleep(1000);

    displayChats();
}

// ================= SCHEDULE MESSAGE =================
void scheduleMessage() {

    string text;
    int seconds;

    cin.ignore();

    cout << "Enter message: ";
    getline(cin, text);

    cout << "Delay (seconds): ";
    cin >> seconds;

    int id = messageID++;

    insertMessage(sobiaHead, id, text + " (waiting)");

    displayChats();

    cout << "Message scheduled...\n";

    Sleep(seconds * 1000);

    // UPDATE SOBIA MESSAGE
    Message* temp = sobiaHead;

    while (temp != NULL) {

        if (temp->id == id) {
            temp->text = text;
            break;
        }

        temp = temp->next;
    }

    insertMessage(atifaHead, id, text);

    cout << "Message delivered\n";

    Sleep(1000);

    displayChats();
}

// ================= DELETE NODE =================
void deleteNode(Message*& head, int id) {

    if (head == NULL) return;

    // DELETE FIRST NODE
    if (head->id == id) {

        Message* del = head;
        head = head->next;

        delete del;
        return;
    }

    Message* temp = head;

    while (temp->next != NULL && temp->next->id != id) {
        temp = temp->next;
    }

    if (temp->next == NULL) return;

    Message* del = temp->next;

    temp->next = temp->next->next;

    delete del;
}

// ================= DELETE FOR EVERYONE =================
void deleteForEveryone() {

    int id;

    cout << "Enter message id to delete: ";
    cin >> id;

    deleteNode(sobiaHead, id);
    deleteNode(atifaHead, id);

    cout << "Message deleted for everyone\n";

    Sleep(1000);

    displayChats();
}

// ================= MAIN =================
int main() {

    int choice;

    do {

        displayChats();

        cout << "1 Send message\n";
        cout << "2 Schedule message\n";
        cout << "3 Delete for everyone\n";
        cout << "4 Exit\n";

        cout << "Choose: ";
        cin >> choice;

        switch (choice) {

            case 1:
                sendMessage();
                break;

            case 2:
                scheduleMessage();
                break;

            case 3:
                deleteForEveryone();
                break;

            case 4:
                cout << "Bye\n";
                break;

            default:
                cout << "Invalid choice\n";
        }

    } while (choice != 4);

    system("pause");

    return 0;
}
