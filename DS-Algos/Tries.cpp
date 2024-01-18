#include <bits/stdc++.h>
using namespace std;

class TrieNode
{
public:
    char data;
    bool isEnd = false;
    vector<TrieNode *> children;
    // map<char, TrieNode *> children;
    TrieNode(char data = '\0')
    {
        this->data = data;
        this->children = vector<TrieNode *>(26, NULL);
    }
};
class Trie
{
public:
    TrieNode *root;
    Trie()
    {
        this->root = new TrieNode('\0');
    }
    bool has_child(TrieNode *curr, int w)
    {
        // return curr->children.find(w)!=curr->children.end();
        cout << (curr != NULL);
        return curr->children[w] != NULL;
    }
    void insert(string word)
    {
        TrieNode *curr = root;
        for (auto w : word)
        {
            w -= 'a';
            if (!has_child(curr, w))
            {
                curr->children[w] = new TrieNode(w);
            }
            curr = curr->children[w];
        }
        curr->isEnd = true;
    }
    bool search(string word)
    {
        TrieNode *curr = root;
        for (auto w : word)
        {
            w -= 'a';
            if (!has_child(curr, w))
                return false;
            curr = curr->children[w];
        }
        return curr->isEnd;
    }
};