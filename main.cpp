#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct GatorNode
{
    string gtrID;
    string gtrName;
    GatorNode* left;
    GatorNode* right;
    int gtrHeight;

    // constructor
    GatorNode()
    {
        gtrID = "";
        gtrName = "";
        left = nullptr;
        right = nullptr;
    }

    // parameterized constructor
    GatorNode(string gtrName, string gtrID)
    {
        this->gtrName = gtrName;
        this->gtrID = gtrID;
        left = nullptr;
        right = nullptr;
    }
};

class GtrAVL
{
public:

    GatorNode* avlRoot = nullptr;

    // Constructor
    GtrAVL()
    {
        avlRoot = nullptr;
    }

    // Right Rotation
    // CITATION: heavily influenced by class slide presentations and Stepik solutions
    GatorNode* RotateRight(GatorNode* currNode)
    {
        GatorNode* temp2 = currNode->left->right;
        GatorNode* temp1 = currNode->left;
        temp1->right = currNode;
        currNode->left = temp2;
        currNode->gtrHeight = GetHeight(currNode);
        temp1->gtrHeight = GetHeight(temp1);
        return temp1;
    }

    // Left Rotation
    // CITATION: heavily influenced by class slide presentations and Stepik solutions
    GatorNode* RotateLeft(GatorNode* currNode)
    {
        GatorNode* temp2 = currNode->right->left;
        GatorNode* temp1 = currNode->right;
        temp1->left = currNode;
        currNode->right = temp2;

        currNode->gtrHeight = GetHeight(currNode);
        temp1->gtrHeight = GetHeight(temp2);

        return temp1;
    }
    
    // Node Height Function
    // CITATION: taken directly from Canvas Stepik solutions
    int GetHeight(GatorNode* currRoot) {
        if (currRoot == nullptr)
            return 0;
        return 1 + std::max(GetHeight(currRoot->left), GetHeight(currRoot->right));
    }

    // Calculating Balance Factor of a given node
    int FindBalFact(GatorNode* currNode)
    {
        if (currNode == nullptr) {
            return 0;
        }
        else {
            return GetHeight(currNode->left) - GetHeight(currNode->right);
        }
    }

    // Recursive Insertion Function
    GatorNode* RecursiveInsert(GatorNode* currRoot, string currName, string currID)
    {
        if (currRoot == nullptr)
        {
            return new GatorNode(currName, currID);
        }
        // greater -> set right
        else if (currRoot->gtrID < currID)
        {
            currRoot->right = RecursiveInsert(currRoot->right, currName, currID);
        }
        // lesser -> set left
        else
        {
            currRoot->left = RecursiveInsert(currRoot->left, currName, currID);
        }

        currRoot->gtrHeight = GetHeight(currRoot);

        int found = FindBalFact(currRoot);

        if (found < -1)
        {
            // right-right
            if (currRoot->right->gtrID < currID)
            {
                return RotateLeft(currRoot);
            }
            // right-left
            else if (currRoot->right->gtrID > currID)
            {
                currRoot->right = RotateRight(currRoot->right);
                return RotateLeft(currRoot);
            }
        }
        else if (found > 1)
        {
            // left-left
            if (currRoot->left->gtrID > currID)
            {
                return RotateRight(currRoot);
            }
            // left-right
            else if (currRoot->left->gtrID < currID)
            {
                currRoot->left = RotateLeft(currRoot->left);
                return RotateRight(currRoot);
            }
        }
        return currRoot;
    }

    // Find the smallest node for the RemoveID() func
    GatorNode* FindSmallest(GatorNode* currNode)
    {
        GatorNode* node = currNode;
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    // Remove ID
    GatorNode* RemoveID(GatorNode* currRoot, string currID)
    {
        if (currRoot == nullptr)
        {
            return nullptr;
        }
        // left side
        else if (currID < currRoot->gtrID)
        {
            currRoot->left = RemoveID(currRoot->left, currID);
        }
        // right side
        else if (currRoot->gtrID < currID)
        {
            currRoot->right = RemoveID(currRoot->right, currID);
        }
        else
        {
            // if (only one child && left->nullptr)
            if (currRoot->left == nullptr)
            {
                GatorNode* tempN = currRoot->right;
                delete currRoot;
                return tempN;
            }
            // if (only one child && right->nullptr)
            else if (currRoot->right == nullptr)
            {
                GatorNode* tempN = currRoot->left;
                delete currRoot;
                return tempN;
            }
            // if (two children)
            else
            {
                GatorNode* tempN = FindSmallest(currRoot->right);
                currRoot->gtrName = tempN->gtrName;
                currRoot->gtrID = tempN->gtrID;
                currRoot->right = RemoveID(currRoot->right, tempN->gtrID);
            }
        }
        return currRoot;
    }

    // Search through tree using inputted ID
    // CITATION: heavily influenced by Stepik
    GatorNode* SearchID(GatorNode* currRoot, string currID)
    {
        if (currRoot == nullptr)
        {
            return currRoot;
        }
        else if (currRoot->gtrID == currID)
        {
            return currRoot;
        }
        // recursively call SearchID() func
        // greater -> set right
        else if (currRoot->gtrID < currID)
        {
            return SearchID(currRoot->right, currID);
        }
        // lesser -> set left
        else
        {
            return SearchID(currRoot->left, currID);
        }
    }

    // Search through tree using inputted NAME
    // CITATION: heavily influenced by Stepik
    void SearchName(GatorNode* currRoot, string currName, vector<string>& vect)
    {
        if (currRoot == nullptr)
        {
            return;
        }
        SearchName(currRoot->left, currName, vect);
        if (currRoot->gtrName == currName)
        {
            vect.push_back(currRoot->gtrID);
        }
        SearchName(currRoot->right, currName, vect);

        return;
    }

    // traverse "IN ORDER"
    // CITATION: taken directly from Canvas Stepik solutions
    void InOrderTraversal(GatorNode* currRoot, vector<GatorNode*>& vect) {
        if (currRoot == nullptr)
            return;
        InOrderTraversal(currRoot->left, vect);
        vect.push_back(currRoot);
        InOrderTraversal(currRoot->right, vect);
    }

    // PRINT InOrderTraversal() func
    void PrintINOrder(GatorNode* currRoot)
    {
        if (currRoot == nullptr)
        {
            cout << "";
        }
        else
        {
            vector<GatorNode*> vect;
            InOrderTraversal(currRoot, vect);
            for (int i = 0; i < vect.size(); i++)
            {
                // don't add coma after last name/gatorID printed out
                if (i == vect.size() - 1)
                {
                    cout << vect[i]->gtrName << endl;
                }
                else
                {
                    cout << vect[i]->gtrName << ", ";
                }
            }
        }
    }

    // traverse "PRE ORDER"
    // CITATION: heavily influenced by Stepik solution to inorderTraversal
    void PreOrderTraversal(GatorNode* currRoot, vector<GatorNode*>& vect) {
        if (currRoot == nullptr)
            return;
        vect.push_back(currRoot);
        PreOrderTraversal(currRoot->left, vect);
        PreOrderTraversal(currRoot->right, vect);
    }

    // PRINT PreOrderTraversal() func
    void PrintPREOrder(GatorNode* currRoot)
    {
        if (currRoot == nullptr)
        {
            cout << "";
        }
        else
        {
            vector<GatorNode*> vect;
            PreOrderTraversal(currRoot, vect);
            for (int i = 0; i < vect.size(); i++)
            {
                // don't add coma after last name/gatorID printed out
                if (i == vect.size() - 1)
                {
                    cout << vect[i]->gtrName << endl;
                }
                else
                {
                    cout << vect[i]->gtrName << ", ";
                }
            }
        }
    }

    // traverse "POST ORDER"
    // CITATION: heavily influenced by Stepik solution to inorderTraversal
    void PostOrderTraversal(GatorNode* currRoot, vector<GatorNode*>& vect) {
        if (currRoot == nullptr)
            return;
        PostOrderTraversal(currRoot->left, vect);
        PostOrderTraversal(currRoot->right, vect);
        vect.push_back(currRoot);
    }

    // PRINT PostOrderTraversal() func
    void PrintPOSTOrder(GatorNode* currRoot)
    {
        if (currRoot == nullptr)
        {
            cout << "";
        }
        else
        {
            vector<GatorNode*> vect;
            PostOrderTraversal(currRoot, vect);
            for (int i = 0; i < vect.size(); i++)
            {
                // don't add coma after last name/gatorID printed out
                if (i == vect.size() - 1)
                {
                    cout << vect[i]->gtrName << endl;
                }
                else
                {
                    cout << vect[i]->gtrName << ", ";
                }
            }
        }
    }

    // PrintLevelCount() func
    void PrintLevelCount(GatorNode* currRoot)
    {
        cout << GetHeight(currRoot) << endl;
    }

    // creates In Order Traversal of IDS and stores in vector for RemoveInOrder() func
    vector<string> TravInOrderID(GatorNode* currRoot, vector<string>& vect)
    {
        if (currRoot == nullptr)
        {
            return vect;
        }
        TravInOrderID(currRoot->left, vect);
        vect.push_back(currRoot->gtrID);
        TravInOrderID(currRoot->right, vect);
        return vect;
    }

    // creates In Order Traversal of NAMES and stores in vector for RemoveInOrder() func
    vector<string> TravInOrderName(GatorNode* currRoot, vector<string>& vect)
    {
        if (currRoot == nullptr)
        {
            return vect;
        }
        TravInOrderName(currRoot->left, vect);
        vect.push_back(currRoot->gtrName);
        TravInOrderName(currRoot->right, vect);
        return vect;
    }

    // function to remove nth node
    GatorNode* RemoveInOrder(GatorNode* currRoot, int num)
    {
        if (currRoot == nullptr)
        {
            return nullptr;
        }
        vector<string> finalVect;

        finalVect = TravInOrderID(currRoot, finalVect);
        string currID = finalVect[num];

        return RemoveID(currRoot, currID);
    }
};


// removes quotes for an input in the command line
string QuoteCancel(string input)
{
    size_t pos = 0;
    size_t posQ = input.find('"');
    if (posQ != string::npos)
    {
        return input.substr(1, input.length()-2);
    }
    return input;
}

// reads input string to check if it's a valid name
string ValidateName(istringstream& readIn)
{
    string str;
    getline(readIn, str, '"');

    // Validate if it's all letters
    for (int i = 0; i < str.length(); ++i)
    {
        if (!isalpha(str[i]))
        {
            return "";
        }
    }
    return str;
}

// reads input string to check if it's a valid ID
string ValidateID(istringstream& readIn)
{
    string str;
    getline(readIn, str, ' ');

    while (str.empty())
    {
        getline(readIn, str, ' ');
    }

    // Validate length of ID
    if (str.length() != 8)
    {
        return "";
    }

    // Validate if it's all digits
    for (int i = 0; i < str.length(); ++i)
    {
        if (!isdigit(str[i]))
        {
            return "";
        }
    }

    return str;
}

int main() {
    
    //cout << "TEST" << endl;

    // create GtrAVL class obj
    GtrAVL avl;

    // get num of commands from user on first line
    string input;
    getline(cin, input);
    int promptCount = stoi(input);

    while (promptCount > 0)
    {
        string prompt;
        getline(cin, input);
        istringstream readIn(input);
        readIn >> prompt;

        // insert command
        if (prompt == "insert")
        {
            string quotes;
            getline(readIn, quotes, '"');

            // call ValidateName()
            string inputName = ValidateName(readIn);
            if (inputName.empty())
            {
                promptCount--;
                cout << "unsuccessful" << endl;
               
                continue;
            }
            
            // call ValidateID()
            string inputID = ValidateID(readIn);
            if (inputID.empty())
            {
                promptCount--;
                cout << "unsuccessful" << endl;
                
                continue;
            }

            avl.avlRoot = avl.RecursiveInsert(avl.avlRoot, inputName, inputID);

            if (avl.avlRoot == nullptr)
            {
                promptCount--;
                cout << "unsuccessful" << endl;
                
                continue;
            }
            cout << "successful" << endl;
        }

        // remove command
        else if (prompt == "remove")
        {
            string inputID = ValidateID(readIn);
            if (inputID.empty())
            {
                promptCount--;
                cout << "unsuccessful" << endl;
                continue;
            }

            // search for ID in tree
            // continue if not in tree
            GatorNode* findN = avl.SearchID(avl.avlRoot, inputID);
            if (findN == nullptr)
            {
                promptCount--;
                cout << "unsuccessful" << endl;
                continue;
            }

            // remove the inputted ID
            GatorNode* removeN = avl.RemoveID(avl.avlRoot, inputID);

            if (removeN == nullptr)
            {
                promptCount--;
                cout << "unsuccessful" << endl;
                continue;
            }

            cout << "successful" << endl;
        }

        // search command
        else if (prompt == "search")
        {
            // read name + id
            string quotes;
            getline(readIn, quotes, ' ');
            getline(readIn, quotes, ' ');

            if ((quotes.at(0) == '"'))
            {
                // when input == name
                bool checkTF = true;
                string inputName = QuoteCancel(quotes);
                for (int i = 0; i < inputName.length(); ++i)
                {
                    if (!isalpha(inputName[i]))
                    {
                        checkTF = false;
                    }
                }
             
                if (!checkTF)
                {
                    promptCount--;
                    cout << "unsuccessful" << endl;                    
                    continue;
                }

                // create vectors for SearchName() funcs
                vector<string> vectNames;
                vector<string> vectNone;
                avl.SearchName(avl.avlRoot, inputName, vectNames);
                
                // print "unsuccessful" if not in vector
                if (vectNames == vectNone)
                {
                    promptCount--;
                    cout << "unsuccessful" << endl;
                    continue;
                }
                // print out names
                else
                {
                    for (int i = 0; i < vectNames.size(); i++)
                    {
                        cout << vectNames[i] << endl;
                    }
                    promptCount--;
                    continue;
                }
            }
            else
            {
                // remove excess space
                getline(readIn, quotes, ' ');
                bool checkTF = true;
                
                // if input == ID
                // check if correct length
                if (quotes.length() != 8)
                {
                    promptCount--;
                    cout << "unsuccessful" << endl;
                    continue;
                }

                // check if all digits
                for (int i = 0; i < quotes.length(); ++i)
                {
                    if (!isdigit(quotes[i]))
                    {
                        checkTF = false;
                    }
                }

                if (!checkTF)
                {
                    promptCount--;
                    cout << "unsuccessful" << endl;
                    continue;
                }

                // search tree with inputted ID
                GatorNode* newNode = avl.SearchID(avl.avlRoot, quotes);
                if (newNode == nullptr)
                {
                    promptCount--;
                    cout << "unsuccessful" << endl;
                    continue;
                }
                else
                {
                    cout << newNode->gtrName << endl;
                }
            }
        }

        // PrintInOrder command
        else if (prompt == "printInorder")
        {
            promptCount--;
            avl.PrintINOrder(avl.avlRoot);
            continue;
        }

        // PrintPreOrder command
        else if (prompt == "printPreorder")
        {
            promptCount--;
            avl.PrintPREOrder(avl.avlRoot);
            continue;
        }

        // PrintPostOrder command
        else if (prompt == "printPostorder")
        {
            promptCount--;
            avl.PrintPOSTOrder(avl.avlRoot);
            continue;
        }

        // PrintLevelCount command
        else if (prompt == "printLevelCount")
        {
            promptCount--;
            avl.PrintLevelCount(avl.avlRoot);
            continue;
        }

        // RemoveInOrder N command
        else if (prompt == "removeInorder")
        {
            // get inputted n digit from getline()
            int digitN;
            string input;
            getline(readIn, input, ' ');
            getline(readIn, input, ' ');
            digitN = stoi(input);

            // validate n
            vector<string> vect;
            vect = avl.TravInOrderName(avl.avlRoot, vect);
            if (digitN >= vect.size() || digitN < 0)
            {
                promptCount--;
                cout << "unsuccessful" << endl;
                continue;
            }

            // call RemoveInOrder() func
            GatorNode* removeN;
            removeN = avl.RemoveInOrder(avl.avlRoot, digitN);
            if (removeN == nullptr)
            {
                promptCount--;
                cout << "unsuccessful" << endl;
                continue;
            }

            cout << "successful" << endl;
        }
        // if not valid command -> print "unsuccessful"
        else
        {
            cout << "unsuccessful" << endl;
        }

        promptCount--;
    }
    return 0;
}
