#include <iostream>
#include <queue>
#include <map>
#include <string>

//Student class
class Student {
private:
    std::string name;
    int id;
    std::string major;

public:

    // Default constructor
    Student() : name(""), id(0), major("") {}
    
    // Constructor
    Student(std::string _name, int _id, std::string _major){
        name=_name;
        id=_id;
        major=_major;
    } 
        
    //Display details function
    void displayDetails() const {
        std::cout<<"Name: "<<name<<", ID: "<<id<<", Major: "<<major<<std::endl;
    }

    int getId() const {
        return id;
    }
};

int main(){
    std::queue<Student> stuQueue;
    std::map<int, Student> stuMap;

    //Menu
    int choice;
    do {
        std::cout << "\n--- Menu ---\n";
        std::cout << "1. Add a Student to the queue and map\n";
        std::cout << "2. Display the details of the first student in the queue\n";
        std::cout << "3. Remove the first student from the queue after processing\n";
        std::cout << "4. Display all stored Student IDs and details from the map\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string name, major;
            int id;
            std::cout << "Enter the student's name: ";
            std::cin >> name;
            std::cout << "Enter the student's ID: ";
            std::cin >> id;
            std::cout << "Enter student's major: ";
            std::cin >> major;

            Student stu(name, id, major);
            stuQueue.push(stu);
            stuMap[id] = stu;
            std::cout << "Student added\n";
        } 
        else if (choice == 2) {
            if (!stuQueue.empty()) {
                std::cout << "1st student in queue:\n";
                stuQueue.front().displayDetails();
            } else {
                std::cout << "The Queue is empty\n";
            }
        } 
        else if (choice == 3) {
            if (!stuQueue.empty()) {
                stuQueue.pop();
                std::cout << "1st student removed from the queue\n";
            } else {
                std::cout << "The queue is empty\n";
            }
        } 
        else if (choice == 4) {
            if (!stuMap.empty()) {
                std::cout << "Data of the stored students and their IDs:\n";
                for (const auto& pair : stuMap) {
                    std::cout << "ID: " << pair.first << " -> ";
                    pair.second.displayDetails();
                }
            }
            else {
                std::cout << "The Map is Empty\n";
            }
        } 
        else if (choice == 5) {
            std::cout << "Exiting the program\n";
        } 
        else {
            std::cout << "Invalid option, please try again\n";
        }
    } while (choice != 5);

    return 0;
}