#include<iostream>
#include<fstream>
#include <string>

using namespace std;

class node 
{
public:
  string key, def;
  node *left, *right;
};

node *insert(node*, string, string);
node *newNode(string, string);
void inorder(node*);
node *ReadFromFile(node*);
void DeleteFromFile(string,string);
void InsertInFile(string, string);
string convert(string);

node *search(node *root, string key)
{
    if (root == NULL) {
        cout << "Word not found" << endl;
        return root;
    }
    
    if (root->key == key) {
        cout <<"\nWord: "<<root->key << "\nDefinition: " << root->def << endl;
        return root;
    }
    
    if (root->key < key)
        return search(root->right, key);
 
    return search(root->left, key);
}

void deleteNode(node *&root, string key)
{
    if (root == NULL) {
        cout << "Word not found" << endl;
        return;
    }
    
    if (key < root->key)
        deleteNode(root->left, key);
    else if (key > root->key)
        deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            node *temp = root->right;
            delete root;
            root = temp;
        }
        else if (root->right == NULL) {
            node *temp = root->left;
            delete root;
            root = temp;
        }
        else {
            node *temp = root->right;
            while (temp->left != NULL)
                temp = temp->left;
            root->key = temp->key;
            root->def = temp->def;
            deleteNode(root->right, temp->key);
        }
        cout << "Word deleted" << endl;
    }
}

void displayMenu()
{
    cout << "Dictionary Management System" << endl;
    cout << "1. Find a word" << endl;
    cout << "2. Enter a new word" << endl;
    cout << "3. Delete a word" << endl;
    cout << "4. Show the tree" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

int CalculateSpacesBeforeWord(string word)
{
	int count = 0;
    ifstream fin("dictionary.txt");

    if (!fin.is_open()) {
        cout << "File error!" << endl;
        return 0;
    }

    string line2;

    while (getline(fin, line2))
    {
        int spaceCount = 0;
        size_t pos = line2.find(word);

        if (pos != string::npos)
        {
            for (size_t i = 0; i < pos; i++)
            {
                if (line2[i] == ' ')
                    spaceCount++;
            }

            cout << "Line: " << line2 << endl;
            cout << "Number of spaces before the word '" << word << "': " << spaceCount << endl;
            count = spaceCount;
            break; // Stop processing further lines after finding the word
        }
    }

    fin.close();
    return count;
}

int main()
{
    node *root = NULL;
    string w, word, meaning;
    root = ReadFromFile(root);
    
    int choice;
    do {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter a word to find: ";
                cin >> w;
                search(root, convert(w));
                break;
                
            case 2:
                cout << "Enter a new word: ";
                cin >> word;
                cout << "Enter the meaning: ";
                cin.ignore();
                getline(cin, meaning);
                InsertInFile(convert(word), meaning);
                root = insert(root, convert(word), meaning);
                break;
                
            case 3:
                cout << "Enter a word to delete: ";
                cin >> word;
                DeleteFromFile(convert(word),word);
                deleteNode(root, convert(word));
                break;
                
            case 4:
                cout << "Tree: ";
                inorder(root);
                cout << endl;
                break;
                
            case 5:
                cout << "Exiting..." << endl;
                break;
                
            default:
                cout << "Invalid choice!" << endl;
                break;
        }
        
        cout << endl;
    } while (choice != 5);
    
    return 0;
}

node *insert(node *node, string key, string def) {
    if (node == NULL)
        return newNode(key, def);

    if (key < node->key || key == node->key)
        node->left = insert(node->left, key, def);
    else
        node->right = insert(node->right, key, def);

    return node;
}

node *newNode(string item, string def1) 
{
    node *temp = new node;
    temp->key = item;
    temp->def = def1;
    temp->left = temp->right = NULL;
    return temp;
}

void inorder(node *root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << "   " << root->def << " -> ";
        inorder(root->right);
    }
}

node *ReadFromFile(node *root1)
{
    ifstream obj1, obj2;
    string line1, line2;
    obj1.open("dictionary.txt");
    obj2.open("definitions.txt");
    
    if (!obj1.is_open()) {
        cout << "File error!" << endl;
    }
    else if (!obj2.is_open()) {
        cout << "File error!" << endl;
    }
    else {
        while (!obj1.eof() && !obj2.eof()) {
            obj1 >> line1;
            getline(obj2, line2);
            root1 = insert(root1, line1, line2);
        }
    }
    
    obj1.close();
    obj2.close();
    return root1;
}

void DeleteFromFile(string deleteline, string word)
{
    int Count = CalculateSpacesBeforeWord(word);
    ifstream fin("dictionary.txt");
    ofstream temp("temp.txt");

    if (!fin.is_open()) {
        cout << "File error!" << endl;
        return;
    }

    string line;
    while (getline(fin, line)) {
        size_t pos = line.find(deleteline);
        if (pos != string::npos) {
            line.erase(pos, deleteline.length() + 1); // Include the space after the word
            if (line.empty())
                continue;
        }
        temp << line << endl;
    }
    temp.close();
    fin.close();
    remove("dictionary.txt");
    rename("temp.txt", "dictionary.txt");
    

    // Delete the corresponding definition from definitions.txt
    

    fin.open("definitions.txt");
    temp.open("temp.txt");

    if (!fin.is_open()) {
        cout << "File error!" << endl;
        return;
    }

    string line1;
    int lineCount = 0;

    while (getline(fin, line1))
    {
        if (lineCount != Count)
            temp << line1 << endl;

        lineCount++;
    }

    temp.close();
    fin.close();
    remove("definitions.txt");
    rename("temp.txt", "definitions.txt");
}

void InsertInFile(string word, string def)
{
    ofstream ob1("dictionary.txt", ios::app);
    ob1 << word << " ";
    ob1.close();
    
    ofstream ob2("definitions.txt", ios::app);
    ob2 << endl << def;
    ob2.close();
}

string convert(string word)
{
    for (int i = 0; i < word.length(); i++) {
        word[i] = tolower(word[i]);
    }
    return word;
}

