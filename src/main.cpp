#include "AVLTree.h"
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <unordered_set>

using namespace std;


int main()
{
    AVLTree avlTree;

    string intstring;
    int commandsnum;
    getline(cin, intstring);
    stringstream(intstring) >> commandsnum;

    // unorder set for command validation
    unordered_set<string> validCommands = {
            "insert", "remove", "search", "printInorder",
            "printPreorder", "printPostorder", "printLevelCount", "removeInorder", " "
    };

    for (int i = 0; i < commandsnum; ++i)
    {
        string input;
        getline(cin, input);
        istringstream iss(input);

        string command;
        iss >> command;

        if (validCommands.find(command) == validCommands.end()) // if command isn't one of the required then automatic unsuccessful
        {
            cout << "unsuccessful" << endl;
            continue;
        }

        if (command == "insert") // insert command
        {
            string nameWithQuotes;
            string idString; // read the ID as a string

            // fully parsing through the input
            getline(iss, nameWithQuotes, '"');
            getline(iss, nameWithQuotes, '"');
            iss >> idString;

            if (avlTree.isValidIdRegex(idString)) // validate the ID using regex, validate in main instead of insert.
            {
                int id = stoi(idString);
                if (avlTree.insert(nameWithQuotes, id))
                {
                    cout << "successful" << endl;
                }
                else
                {
                    cout << "unsuccessful" << endl;
                }
            }
            else
            {
                cout << "unsuccessful" << endl;
            }
        }
        else if (command == "remove") // remove command
        {
            int id;
            iss >> id;

            if (avlTree.remove(id))
            {
                cout << "successful" << endl;
            }
            else
            {
                cout << "unsuccessful" << endl;
            }
        }
        else if (command == "search") // search command
        {
            string query;
            getline(iss, query);

            // check for leading spaces and trailing spaces, trims them
            // https://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
            query = regex_replace(query, regex("^ +| +$"), "");

            if (query.front() == '"' && query.back() == '"')
            {
                string name = query.substr(1, query.length() - 2);

                string result = avlTree.search(name);
                if (result == "unsuccessful")
                {
                    cout << "unsuccessful" << endl;
                }
                else
                {
                    cout << result << endl;
                }
            }
            else
            {
                try { // try catch block to catch for stoll error
                    int id = stoll(query);

                    string result = avlTree.search(id);
                    cout << result << endl;
                }
                catch (const invalid_argument& ia)
                {
                    cout << "unsuccessful" << endl;
                }
            }
        }
        else if (command == "printInorder") // print inorder
        {
            string result = avlTree.printInorder();
            if(result != "")
            {
                cout << result << endl;
            }
        }
        else if (command == "printPreorder") // print preorder
        {
            string result = avlTree.printPreorder();
            if(result != "")
            {
                cout << result << endl;
            }
        }
        else if (command == "printPostorder") // print postorder
        {
            string result = avlTree.printPostorder();
            if(result != "")
            {
                cout << result << endl;
            }
        }
        else if (command == "printLevelCount") // level count
        {
            avlTree.printLevelCount();
        }
        else if (command == "removeInorder") // remove inorder
        {
            int n;
            iss >> n;

            if (n < 0)
            {
                cout << "unsuccessful" << endl;
                continue;
            }
            if (avlTree.removeInorder(n))
            {
                cout << "successful" << endl;
            }
            else
            {
                cout << "unsuccessful" << endl;
            }
        }

    }

    return 0;
}
