#include <iostream>;
#include <fstream>;
#include <sstream>;
#include <vector>;

using namespace std;

class ToDoList
{
public:
	int ID;
	string title;
	string description;
	bool completion_status;
	vector<ToDoList> queues;
private:
};

void mainMenu(ToDoList);
void deleteRecent(ToDoList main_object);
void deleteAtPos(ToDoList main_object);
bool validateInput(string user_input);
void fullView(ToDoList main_object);
void quickView(ToDoList main_object);
void viewListMenu(ToDoList main_object);

// Loads data from text file into main object queue
void loadFile(ToDoList main_object) {
	
	// Erase currently stored memory
	main_object.queues.clear();

	ifstream file;
	string user_input;
	int line_counter = 0; // Counts which line getline is at
	int queue_counter = 0; // Counts how many total tasks have been retrived

	// Prompt user
	cout << endl << "What is the file name? (Default = 'tasks.txt')" << endl;
	cout << ": ";
	cin >> user_input;
	cout << endl;

	file.open(user_input);
	
	// Clear buffer
	cin.clear();
	cin.ignore();

	// Validation of input file
	if (file.is_open()) {
		string line;
		ToDoList tempObj = main_object;

		while(getline(file, line))
		{
			switch (line_counter)
			{
				case 0:
					tempObj.title = line;
					line_counter++;
					break;
				case 1:
					tempObj.description = line;
					line_counter++;
					break;
				case 2:
					main_object.queues.push_back(tempObj);
					line_counter = 0;
					queue_counter++;
					break;
			}
		}
	}
	else {
		cout << "Error: Could not open file " << user_input << endl;
		mainMenu(main_object);
	}

	cout << "Loaded file successfully." << endl << endl;
	mainMenu(main_object);
}

// Saves vector holding ToDoList objects to text file
void saveToFile(ToDoList main_object) {
	string user_input;

	// Prompt user
	cout << endl << "What is the file name? (Default = 'tasks.txt')" << endl;
	cout << ": ";
	cin >> user_input;
	cout << endl;

	while (true)
	{
		ofstream file(user_input);

		if (file) {
			
			for (int i = 0; i < main_object.queues.size(); i++)
			{
				file << main_object.queues[i].title << endl;
				file << main_object.queues[i].description << endl << endl;
			}
			file.close();

			cout << "File saved successfully." << endl << endl;
			mainMenu(main_object);
			break;
		}
		else
		{
			cout << "No file found trying again " << endl << endl;
			mainMenu(main_object);
		}
	}
}


void newItemMenu(ToDoList main_object) {
	
	// Holds user input
	string user_input;
	string title = "";
	string description = "";

	// Create list object
	ToDoList newList = main_object;

	// Prompt user
	cout << endl << "To add a new list, fill out a title, and description (optional)." << endl << endl;
	
	// Get title and description with input validation
	while (true)
	{
		cout << "Please enter title: " << endl;
		getline(cin >> ws, title);
		cout << endl;

		if (title != "") {
			cout << "Please enter a description: " << endl;
			getline(cin >> ws, description);
			cout << endl;
			break;
		}	

		continue;
	}

	// Store title and description
	newList.title = title;
	newList.description = description;

	// Add object to list of tasks
	main_object.queues.push_back(newList);

	// Add more?
	while (true) {
		string retry;
		cout << "Do you want to add another one? (Y or N)" << endl;
		cin >> retry;
		cout << endl;

		cin.clear();
		cin.ignore();

		if (retry == "Y" || retry == "N") {
			if (retry == "Y") {
				newItemMenu(main_object);
				return;
			}
			else {
				mainMenu(main_object);
				return;
			}
		}
		else {
			cout << "Error: Invalid selection " << endl << endl;
			continue;
		}
	}
	
}

void deleteItemMenu(ToDoList main_object) {
	
	string user_input;
	int int_user_input;

	// Prompt user
	cout << " Deletion Menu: " << endl << endl;
	cout << " 1. Delete newest task" << endl;
	cout << " 2. Delete a specific task" << endl;
	cout << " 3. Back" << endl << endl;
	cout << ": ";
	cin >> user_input;
	cout << endl;

	// Clear buffer
	cin.clear();
	cin.ignore();

	// If valid convert
	if (validateInput(user_input)) {
		// Convert input to int
		stringstream ss(user_input);
		ss >> int_user_input;
	}
	else {
		cout << "Error: Invalid selection " << endl << endl;
		deleteItemMenu(main_object);
	}

	switch (int_user_input)
	{
		case 1:
			deleteRecent(main_object);
			break;
		case 2:
			deleteAtPos(main_object);
			break;
		case 3:
			mainMenu(main_object);
			break;
		default:
			cout << "Error: Invalid selection " << endl << endl;
			deleteItemMenu(main_object);
			break;
	}

	return;
}

// Deletes newest added entry (last)
void deleteRecent(ToDoList main_object) {
	
	if (main_object.queues.size() > 0) {
		main_object.queues.pop_back();
		cout << "Task deleted." << endl << endl;
	}
	else {
		cout << "No task to delete." << endl << endl;
	}

	deleteItemMenu(main_object);
}

// Deletes at a specific position in stack
void deleteAtPos(ToDoList main_object) {
	string user_input;
	int int_user_input;

	// Prompt user
	cout << "What is the title of the task?" << endl;
	cout << ": ";
	cin >> user_input;
	cout << endl;

	for (int i = 0; i < main_object.queues.size(); i++)
	{
		if (!(user_input == main_object.queues[i].title)) {
			continue;
		}
		else {
			main_object.queues.erase(main_object.queues.begin() + i);
			cout << "The task with title ( " << user_input << " ) has been deleted." << endl << endl;
			deleteItemMenu(main_object);
		}
	}

	cout << "The task with title ( " << user_input << " ) was not found." << endl << endl;
	deleteItemMenu(main_object);
}

// Views menus
void quickView(ToDoList main_object) {
	
	vector<ToDoList> temp = main_object.queues;
	
	cout << "Tasks by title: " << endl;

	if (temp.size() == 0) {
		cout << "No tasks need attention!" << endl;
	}
	else {
		for (int i = 0; i < temp.size(); i++)
		{
			cout << " " << temp[i].title << endl;
		}
	}
	cout << endl;

	main_object.queues = temp;

	viewListMenu(main_object);
}

void fullView(ToDoList main_object) {
	
	string user_input;

	// Prompt user
	cout << "What is the title of the task?" << endl;
	cout << ": ";
	cin >> user_input;

	cout << endl;

	// Check through tasks
	for (int i = 0; i < main_object.queues.size(); i++)
	{
		if (!(user_input == main_object.queues[i].title)) {
			continue;
		}
		else {
			cout << "Title: \n" << main_object.queues[i].title << endl << endl;
			cout << "Description: \n" << main_object.queues[i].description << endl << endl;
			viewListMenu(main_object);
		}
	}

	cout << "The task with title ( " << user_input << " ) was not found." << endl << endl;

	cin.clear();
	cin.ignore();

	viewListMenu(main_object);
}

void viewListMenu(ToDoList main_object) {
	
	string user_input;
	int int_user_input;

	// Prompt user
	cout << " Views Menu: " << endl << endl;
	cout << " 1. Quick view" << endl;
	cout << " 2. Full view" << endl;
	cout << " 3. Back" << endl;

	cout << endl;
	cout << ": ";
	cin >> user_input;
	cout << endl;

	// If valid convert
	if (validateInput(user_input)) {
		// Convert input to int
		stringstream ss(user_input);
		ss >> int_user_input;
	}
	else {
		deleteItemMenu(main_object);
	}

	switch (int_user_input)
	{
		case 1:
			quickView(main_object);
		case 2:
			fullView(main_object);
		case 3:
			mainMenu(main_object);
		default:
			cout << " Error: Invalid selection ";
			viewListMenu(main_object);
	}
}

bool validateInput(string user_input) {
	
	bool inputValid = false;

	// Holds int of user input
	int int_user_input;

	// Convert input to int
	stringstream ss(user_input);

	if (ss >> int_user_input) {
		return true;
	}
	else {
		// Clear ss
		ss.clear();
		return false;
	}
}

void mainMenu(ToDoList main_object) {

	// Holds int of user input
	int int_user_input;

	// Holds user input
	string user_input;

	// Prompt user
	cout << " Main Menu: " << endl << endl;
	cout << " 1. Add a new item" << endl;
	cout << " 2. Delete a item" << endl;
	cout << " 3. View lists" << endl;
	cout << " 4. Save to file" << endl;
	cout << " 5. Load from file" << endl;
	cout << " 6. Exit" << endl << endl;
	cout << ": ";
	cin >> user_input;

	cout << endl;

	cin.clear();
	cin.ignore();

	// If valid convert
	if (validateInput(user_input)) {
		// Convert input to int
		stringstream ss(user_input);
		ss >> int_user_input;
	}
	else {
		cout << "Error: Invalid selection" << endl << endl;
		mainMenu(main_object);
	}

	// Decision switch
	switch (int_user_input)
	{
		case 1:
			newItemMenu(main_object);
			break;
		case 2:
			deleteItemMenu(main_object);
			break;
		case 3:
			viewListMenu(main_object);
			break;
		case 4:
			saveToFile(main_object);
		case 5:
			loadFile(main_object);
			break;
		case 6:
			exit(99);
			break;
		default:
			cout << "Error: Invalid selection" << endl << endl;
			mainMenu(main_object);
	}
	return;
}


void driver() {

	// List object
	ToDoList main_object;

	// Prompt menu
	mainMenu(main_object);
};

int main() {

	// Main driver
	driver();
}