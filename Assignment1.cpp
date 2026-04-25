#include <iostream>
#include <string>
using namespace std;

class LinkList {
private:
    struct equipment {
        string equipmentID;
        string name;
        string modelNumber;
        string category;
        string manufacturer;
        string status;
        string purchaseDate;
        string lastMaintenanceDate;
        string maintenanceFrequency;
        string condition;
        equipment* link;
    }*head;
public:
    LinkList();
    void addEquipment();
    bool searchID(string target);
    bool viewStatus(string searchStatus);
    void updateEquipment(string updateID);
    void deleteEquipment(string deleteID);
    void printAllRecord();
    ~LinkList();
};

/* Constructor: initialize head pointer */
LinkList::LinkList() {
    head = NULL;
}

/* Destructor: delete all nodes from the head */
LinkList::~LinkList() {
    equipment* q;
    if (head == NULL) {
        return;
    }
    while (head != NULL) {
        q = head->link;
        delete head;
        head = q;
    }
}

/* Insert Equipment Record */
void LinkList::addEquipment() {
    // Create new equipment node defaultly at beginning of list
    equipment* newEquipment = new equipment();
    newEquipment->link = head;
    head = newEquipment;

    cin.ignore();
    cout << "\nPlease enter Equipment details below." << endl;
    cout << "Equipment ID: ";
    getline(cin, newEquipment->equipmentID);
    cout << "Equipment Name: ";
    getline(cin, newEquipment->name);
    cout << "Model Number: ";
    getline(cin, newEquipment->modelNumber);
    cout << "Category: ";
    getline(cin, newEquipment->category);
    cout << "Manufacturer: ";
    getline(cin, newEquipment->manufacturer);
    cout << "Status (Available, Under Maintenance, Reserved): ";
    getline(cin, newEquipment->status);
    cout << "Purchase Date (YYYY-MM-DD): ";
    getline(cin, newEquipment->purchaseDate);
    cout << "Last Maintenance Date (YYYY-MM-DD): ";
    getline(cin, newEquipment->lastMaintenanceDate);
    cout << "Maintenance Frequency (Monthly, Quarterly, etc.): ";
    getline(cin, newEquipment->maintenanceFrequency);
    cout << "Condition (Good, Needs Repair, etc.): ";
    getline(cin, newEquipment->condition);

    cout << "\nEquipment added successfully!" << endl;
    cout << "====================================================================\n\n\n\n";
}

/* Search eqiupmentID */
bool LinkList::searchID(string target) {
    equipment* current;
    current = head;
    bool found;
    found = false;

    while ((current != NULL) && (!found)) {
        if (current->equipmentID == target) {
            found = true;
        }
        else {
            current = current->link;
        }
    }
    return found;
}

/* View status by eqiupmentID */
bool LinkList::viewStatus(string searchStatus) {
    equipment* current;
    current = head;
    bool found;
    found = false;

    while (current != NULL) {
        if (current->status == searchStatus) {
            cout << "\n====================================================================\n";
            cout << "Equipment ID: " << current->equipmentID << endl;
            cout << "Equipment Name: " << current->name << endl;
            cout << "Model Number: " << current->modelNumber << endl;
            cout << "Condition: " << current->condition << endl;
            cout << "====================================================================\n";
            found = true;
        }
        current = current->link;
    }
    cout << "\n\n\n\n";
    return found;
}

/* Delte equipment by eqiupmentID */
void LinkList::deleteEquipment(string deleteID) {
    if (head != NULL) {
        if (head->link == NULL) { //list has only one node
            delete head;
            head = NULL;
        }
        else {
            equipment* p, * q; //search ID to be deleted in the list
            p = q = head;
            while (q->equipmentID != deleteID && q != NULL) {
                p = q;
                q = q->link;
            }
            p->link = q->link;
            delete q;
        }
    }
    else {
        cout << "Record is empty.\n";
        return;
    }//end checking the link empty or not
}

/* Update equipment by eqiupmentID */
void LinkList::updateEquipment(string updateID) {
    if (head != NULL) {
        equipment* p;
        p = head;

        while (p != NULL) {
            if (p->equipmentID == updateID) {
                cin.ignore();  // so getline() works correctly

                cout << "\nEnter New Status (Available, Under Maintenance, Reserved): ";
                getline(cin, p->status);
                cout << "Enter New Last Maintenance Date (YYYY-MM-DD): ";
                getline(cin, p->lastMaintenanceDate);
                cout << "Enter New Condition (Good, Needs Repair, etc.): ";
                getline(cin, p->condition);
            }
            p = p->link;
        } //end while
        cout << "\n\n\n\n";
    } ////end checking the link empty or not
}

/* Print all record in the list */
void LinkList::printAllRecord() {
    equipment* current;
    current = head;
    while (current != NULL) {
        cout << "\n=====================================================================\n";
        cout << "Equipment ID: " << current->equipmentID << endl;
        cout << "Equipment Name: " << current->name << endl;
        cout << "Model Number: " << current->modelNumber << endl;
        cout << "Category: " << current->category << endl;
        cout << "Manufacture: " << current->manufacturer << endl;
        cout << "Status: " << current->status << endl;
        cout << "Purchase date: " << current->purchaseDate << endl;
        cout << "Last maintenance date: " << current->lastMaintenanceDate << endl;
        cout << "Maintenance frequency: " << current->maintenanceFrequency << endl;
        cout << "Condition: " << current->condition << endl;
        cout << "\n=====================================================================\n";

        current = current->link;  //Move to next record
    }
    cout << "\n\n\n\n";
    if (head == NULL) {
        cout << "No equipment records are recorded.\n\n\n\n";
        return;
    }
}


int main() {
    LinkList Record; //Create new object
    char choice = ' ';
    while (choice != '6') {
        cout << "====================================================================\n";
        cout << "Engineering Lab Equipment Management System (ELEMS)" << endl;
        cout << "====================================================================\n";
        cout << "1. Add Equipment" << endl;
        cout << "2. Update Equipment" << endl;
        cout << "3. Delete Equipment" << endl;
        cout << "4. Search Equipment by status" << endl;
        cout << "5. View all Equipment Records" << endl;
        cout << "6. Exit" << endl;
        cout << "====================================================================\n";
        cout << "Enter choice (1/2/3/4/5) or 6 to exit: ";
        cin >> choice;

        switch (choice) {
        case '1': {
            Record.addEquipment();
            break;
        }
        case '2': {
            cin.ignore();
            string updateID = " ";
            cout << "\nEnter Equipment ID to update: ";
            getline(cin, updateID);

            if (Record.searchID(updateID)) {
                cout << "Equipment Found! Please enter details to be updated. " << endl;
                Record.updateEquipment(updateID);
                cout << "\nEquipment with " << updateID << " has been updated successfully!\n\n\n\n";
            }
            else {
                cout << "\nEquipment ID not found.\n\n\n\n";
            }
            break;
        }
        case '3': {
            cin.ignore();
            string deleteID = " ";
            cout << "\nEnter Equipment ID to delete: ";
            getline(cin, deleteID);

            if (Record.searchID(deleteID)) {
                Record.deleteEquipment(deleteID);
                cout << "Equipment with " << deleteID << " has been deleted successfully!\n\n\n\n";
            }
            else {
                cout << "\nEquipment ID not found.\n\n\n\n";
            }
            break;
        }
        case '4': {
            cin.ignore();
            string searchStatus = " ";
            cout << "Enter Status to Search (Available / Under Maintenance / Reserved): ";
            getline(cin, searchStatus); //Use get line as there might be input with spaces

            if (!Record.viewStatus(searchStatus)) {
                cout << "\nNo equipment is found.\n\n\n\n";
            }
            break;
        }
        case '5': {
            Record.printAllRecord();
            break;
        }
        case '6': {
            cout << "Thanks for using the system. System exiting...." << endl;
            break;
        }
        default:
            cout << "Invalid choice. Please try again. \n\n\n\n";
        }
    }

}