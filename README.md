# ToDoList (C++)
A To-Do List application created with C++. It gives the user the ability to create tasks, delete tasks, search for tasks, save to a file, and load from a file. Each task is stored in a queue of ToDoList objects that holds each entries information.

## Included Libraries
- iostream: Input/output stream library for handling console input and output.
* fstream: File stream library for handling file input and output.
* sstream: String stream library for converting strings to other data types.
* vector: Dynamic array container for storing a collection of objects.

## Skills and Concepts
1. Object-Oriented Programming: The code demonstrates the use of classes (ToDoList) to encapsulate data and behavior related to to-do list items. It utilizes object-oriented principles like encapsulation and data abstraction.
2. File Input/Output
3. Standard Input/Output
4. Container Classes
5. User Input Validation
6. Control Flow
7. Error Handling: Although the code lacks comprehensive error handling, it demonstrates basic error handling for file input and user input validation.
8. Function Calls and Recursion
9. Program Structure

## Addressing Improvements
1. Modularize functionality
2. Simplify code
3. Increase level of error handling and input validation techniques

## Functions and Classes
### Class ToDoList
Represents a single to-do list item. It has the following public members:

* ID: An integer representing the ID of the to-do item.
* title: A string representing the title of the to-do item.
* description: A string representing the description of the to-do item.
* completion_status: A boolean indicating the completion status of the to-do item.
* queues: A vector of ToDoList objects representing sub-tasks or sub-items.

### Function mainMenu(ToDoList main_object)
* Displays the main menu of the application and handles user input.

### Function deleteRecent(ToDoList main_object)
* Deletes the most recently added to-do item from the main list.

### Function deleteAtPos(ToDoList main_object)
* Deletes a specific to-do item from the main list based on user input.

### Function validateInput(string user_input)
* Validates user input to ensure it can be converted to an integer.

### Function fullView(ToDoList main_object)
* Displays the full details of a specific to-do item based on user input.

### Function quickView(ToDoList main_object)
* Displays a quick overview of all the to-do item titles.

### Function viewListMenu(ToDoList main_object)
* Displays the view menu options and handles user input for viewing to-do items.

### Function loadFile(ToDoList main_object)
* Loads data from a text file into the main ToDoList object.

### Function saveToFile(ToDoList main_object)
* Saves the to-do items from the main ToDoList object to a text file.

### Function newItemMenu(ToDoList main_object)
* Displays the menu for adding a new to-do item and handles user input for creating a new item.

### Function driver()
* The main entry point of the application. Calls the mainMenu function to start the program.
