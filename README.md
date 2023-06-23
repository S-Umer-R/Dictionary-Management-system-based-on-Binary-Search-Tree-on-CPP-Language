# Dictionary Management System

This is a Dictionary Management System implemented in C++. It allows users to store and manage word definitions using a binary search tree data structure.

## Usage

The Dictionary Management System provides the following features:

1. Find a word: Search for a word and display its corresponding definition.
2. Enter a new word: Add a new word and its definition to the dictionary.
3. Delete a word: Remove a word and its definition from the dictionary.
4. Show the tree: Display the binary search tree in an inorder traversal.
5. Exit: Quit the program.

## Binary Search Tree

The Dictionary Management System utilizes a binary search tree data structure to efficiently store and retrieve word definitions. The binary search tree maintains the following properties:

- Each node in the tree contains a key-value pair, where the key represents a word and the value represents its definition.
- The keys in the left subtree of a node are less than the key of the node.
- The keys in the right subtree of a node are greater than the key of the node.

By leveraging the properties of a binary search tree, the system enables fast search, insertion, and deletion of words.

## How to Compile and Run

To compile and run the Dictionary Management System, follow these steps:

1. Ensure you have a C++ compiler installed on your system.
2. Clone this repository to your local machine.
3. Open a terminal or command prompt and navigate to the repository directory.
4. Compile the program using the following command:

   ```bash
   g++ main.cpp -o dictionary
   ```

5. Run the program by executing the generated binary:

   ```bash
   ./dictionary
   ```

## File Structure

The repository contains the following files:

- `main.cpp`: The main source code file containing the implementation of the Dictionary Management System.
- `dictionary.txt`: The file that stores the word entries in the dictionary.
- `definitions.txt`: The file that stores the corresponding definitions of the words in the dictionary.
