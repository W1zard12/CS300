// Project_Two.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

// Course structure
struct Course {
    std::string courseNumber;
    std::string courseTitle;
    std::vector<std::string> prerequisites;
};

// Binary Search Tree for Course Management
class CourseBST {
private:
    struct Node {
        Course course;
        Node* left;
        Node* right;

        Node(Course course) : course(course), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void inOrder(Node* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        std::cout << node->course.courseNumber << ": " << node->course.courseTitle << std::endl;
        inOrder(node->right);
    }

    void insert(Node*& node, Course course) {
        if (node == nullptr) {
            node = new Node(course);
        }
        else if (course.courseNumber < node->course.courseNumber) {
            insert(node->left, course);
        }
        else {
            insert(node->right, course);
        }
    }

    Node* search(Node* node, std::string courseNumber) {
        if (node == nullptr || node->course.courseNumber == courseNumber) {
            return node;
        }
        if (courseNumber < node->course.courseNumber) {
            return search(node->left, courseNumber);
        }
        else {
            return search(node->right, courseNumber);
        }
    }

public:
    CourseBST() : root(nullptr) {}

    void insert(Course course) {
        insert(root, course);
    }

    void printAllCourses() {
        inOrder(root);
    }

    void printCourseInfo(std::string courseNumber) {
        Node* node = search(root, courseNumber);
        if (node == nullptr) {
            std::cout << "Course not found!" << std::endl;
        }
        else {
            std::cout << node->course.courseNumber << ": " << node->course.courseTitle << std::endl;
            std::cout << "Prerequisites: ";
            if (node->course.prerequisites.empty()) {
                std::cout << "None";
            }
            else {
                for (size_t i = 0; i < node->course.prerequisites.size(); ++i) {
                    std::cout << node->course.prerequisites[i];
                    if (i < node->course.prerequisites.size() - 1) {
                        std::cout << ", ";
                    }
                }
            }
            std::cout << std::endl;
        }
    }
};

// Convert string to uppercase for case-insensitive comparison
std::string toUpperCase(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

// Load courses from a CSV file
void loadCoursesFromFile(std::string filename, CourseBST& bst) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return;
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string courseNumber, courseTitle, prereq;
        std::getline(ss, courseNumber, ',');
        std::getline(ss, courseTitle, ',');

        Course course;
        course.courseNumber = courseNumber;
        course.courseTitle = courseTitle;

        while (std::getline(ss, prereq, ',')) {
            if (!prereq.empty()) {
                course.prerequisites.push_back(prereq);
            }
        }

        bst.insert(course);
    }

    file.close();
    std::cout << "Courses loaded successfully." << std::endl;
}

// Display the main menu
void displayMenu() {
    std::cout << "1. Load Data Structure" << std::endl;
    std::cout << "2. Print Course List" << std::endl;
    std::cout << "3. Print Course" << std::endl;
    std::cout << "9. Exit" << std::endl;
}

int main() {
    CourseBST bst;
    std::string filename;
    int choice;

    do {
        displayMenu();
        std::cout << "What would you like to do? ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter filename: ";
            std::cin >> filename;
            loadCoursesFromFile(filename, bst);
            break;

        case 2:
            bst.printAllCourses();
            break;

        case 3: {
            std::cout << "What course do you want to know about? ";
            std::string courseNumber;
            std::cin >> courseNumber;
            courseNumber = toUpperCase(courseNumber);
            bst.printCourseInfo(courseNumber);
            break;
        }

        case 9:
            std::cout << "Thank you for using the course planner!" << std::endl;
            break;

        default:
            std::cout << "Invalid choice, please try again." << std::endl;
            break;
        }
    } while (choice != 9);

    return 0;
}
