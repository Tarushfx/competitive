class TrieNode:
    def __init__(self, data):
        self.data = data
        self.children = {}
        self.isEnd = False


class Trie:
    def __init__(self):
        self.root = TrieNode("")

    def insert(self, word: str) -> None:
        cur = self.root
        for i in word:
            if i not in cur.children:
                cur.children[i] = TrieNode(i)
            cur = cur.children[i]
        cur.isEnd = True

    def search(self, word: str) -> bool:
        cur = self.root
        for i in word:
            if i not in cur.children:
                return False
            cur = cur.children[i]

        return cur.isEnd
