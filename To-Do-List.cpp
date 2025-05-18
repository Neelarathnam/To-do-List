#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Task {
    int id;
    string description;
};

const string FILENAME = "todo.txt";

// Function declarations
void loadTasks(vector<Task>& tasks);
void saveTasks(const vector<Task>& tasks);
void addTask(vector<Task>& tasks);
void viewTasks(const vector<Task>& tasks);
void updateTask(vector<Task>& tasks);
void deleteTask(vector<Task>& tasks);

int main() {
    vector<Task> tasks;
    int choice;

    loadTasks(tasks);

    do {
        cout << "\n====== To-Do List Manager ======" << endl;
        cout << "1. View Tasks" << endl;
        cout << "2. Add Task" << endl;
        cout << "3. Update Task" << endl;
        cout << "4. Delete Task" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: viewTasks(tasks); break;
            case 2: addTask(tasks); break;
            case 3: updateTask(tasks); break;
            case 4: deleteTask(tasks); break;
            case 5: saveTasks(tasks); cout << "Exiting. Tasks saved!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}

// Load tasks from file
void loadTasks(vector<Task>& tasks) {
    ifstream inFile(FILENAME);
    Task task;
    while (inFile >> task.id) {
        inFile.ignore();
        getline(inFile, task.description);
        tasks.push_back(task);
    }
    inFile.close();
}

// Save tasks to file
void saveTasks(const vector<Task>& tasks) {
    ofstream outFile(FILENAME);
    for (const auto& task : tasks) {
        outFile << task.id << endl << task.description << endl;
    }
    outFile.close();
}

// Add a new task
void addTask(vector<Task>& tasks) {
    Task task;
    cout << "Enter task description: ";
    getline(cin, task.description);
    task.id = tasks.empty() ? 1 : tasks.back().id + 1;
    tasks.push_back(task);
    cout << "Task added successfully.\n";
}

// View all tasks
void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks available.\n";
        return;
    }

    cout << "\n--- To-Do List ---\n";
    for (const auto& task : tasks) {
        cout << "[" << task.id << "] " << task.description << endl;
    }
}

// Update a task
void updateTask(vector<Task>& tasks) {
    int id;
    cout << "Enter task ID to update: ";
    cin >> id;
    cin.ignore();

    for (auto& task : tasks) {
        if (task.id == id) {
            cout << "Current description: " << task.description << endl;
            cout << "Enter new description: ";
            getline(cin, task.description);
            cout << "Task updated.\n";
            return;
        }
    }
    cout << "Task ID not found.\n";
}

// Delete a task
void deleteTask(vector<Task>& tasks) {
    int id;
    cout << "Enter task ID to delete: ";
    cin >> id;

    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->id == id) {
            tasks.erase(it);
            cout << "Task deleted.\n";
            return;
        }
    }
    cout << "Task ID not found.\n";
}

