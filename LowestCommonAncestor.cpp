#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <functional>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int d)
    {
        data = d;
        left = nullptr;
        right = nullptr;
    }
};

class Solution
{
public:
    Node *insert(Node *root, int data)
    {
        if (root == nullptr)
        {
            return new Node(data);
        }
        else
        {
            Node *cur;
            if (data <= root->data)
            {
                cur = insert(root->left, data);
                root->left = cur;
            }
            else
            {
                cur = insert(root->right, data);
                root->right = cur;
            }

            return root;
        }
    }

    /*The tree node has data, left child and right child
    class Node {
        int data;
        Node* left;
        Node* right;
    };

    */

    Node *lca(Node *root, int v1, int v2)
    {
        if (v1 == root->data || v2 == root->data)
        {
            return root;
        }
        vector<string> paths{"", ""};
        getTwoPaths(root, v1, v2, "", paths);
        int index = 0;
        while (paths.at(0).at(index) == paths.at(1).at(index))
        {
            index++;
        }
        Node *currentNode = root;
        for (int i = 0; i < index; ++i)
        {
            char side = paths.at(0).at(i);
            currentNode = side == '0' ? currentNode->left : currentNode->right;
        }
        return currentNode;
    }

    void getTwoPaths(Node *root, int v1, int v2, string currentPath, vector<string> &paths)
    {
        if (v1 < root->data && v2 < root->data)
        {
            getTwoPaths(root->left, v1, v2, currentPath + "0", paths);
        }
        else if (v1 > root->data && v2 > root->data)
        {
            getTwoPaths(root->right, v1, v2, currentPath + "1", paths);
        }
        else
        {
            paths.insert(paths.begin(), getPath(root, v1, currentPath));
            paths.insert(paths.begin() + 1, getPath(root, v2, currentPath));
        }

        if (paths.at(0) != "" && paths.at(1) != "")
        {
            return;
        }
    }

    string getPath(Node *root, int v, string currentPath)
    {
        if (root->data == v)
        {
            return currentPath;
        }
        if (root->data > v)
        {
            if (root->left != nullptr)
            {
                string res = getPath(root->left, v, currentPath + "0");
                if (res != "NULL")
                {
                    return res;
                }
            }
            return "NULL";
        }

        else if (root->data < v)
        {
            if (root->right != nullptr)
            {
                string res = getPath(root->right, v, currentPath + "1");
                if (res != "NULL")
                {
                    return res;
                }
            }
            return "NULL";
        }
        return "NULL";
    }

}; // End of Solution

int main()
{

    Solution myTree;
    Node *root = nullptr;

    string t_temp;

    getline(cin, t_temp);
    int t = stoi(ltrim(rtrim(t_temp)));

    string data_temp;
    getline(cin, data_temp);

    vector<string> data_array = split(rtrim(data_temp));

    for (int i = 0; i < t; ++i)
    {
        int data = stoi(ltrim(rtrim(data_array.at(i))));
        root = myTree.insert(root, data);
    }

    string v_temp;
    getline(cin, v_temp);
    vector<string> v_array = split(rtrim(v_temp));

    int v1 = stoi(v_array[0]);

    int v2 = stoi(v_array[1]);

    Node *ans = myTree.lca(root, v1, v2);

    cout << ans->data;

    return 0;
}

string ltrim(const string &str)
{
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), [](int c)
                { return !std::isspace(c); }));

    return s;
}

string rtrim(const string &str)
{
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), [](int c)
                { return !std::isspace(c); })
            .base(),
        s.end());

    return s;
}

vector<string> split(const string &str)
{
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos)
    {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
