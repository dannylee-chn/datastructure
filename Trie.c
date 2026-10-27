#ifndef TRIE_H
#define TRIE_H
#include <ctype.h>

#include "Map.h"
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef struct TrieNode {
    bool isWord;
    LinkedListMap* next;
} TrieNode;

TrieNode* trie_node_create(bool isWord) {
    TrieNode* n = malloc(sizeof(TrieNode));
    n->isWord = isWord;
    n->next = map_create();
    return n;
}

TrieNode* trie_node_create_default() {
    return trie_node_create(false);
}

typedef struct Trie {
    TrieNode* root;
    int size;
} Trie;

Trie* trie_create() {
    Trie* t = malloc(sizeof(Trie));
    t->root = trie_node_create_default();
    t->size = 0;
    return t;
}

int tr_getSize(Trie* trie) {
    return trie->size;
}

//向Trie中添加一个新的单词 word
void trie_add(Trie* trie, const char* word) {
    TrieNode* cur = trie->root;
    for (int i = 0; word[i] != '\0'; i++) {
        char c = word[i];
        TrieNode* child = get(cur->next, c);
        if (child == NULL) {
            child = trie_node_create_default();
            add(cur->next, c, child);
        }
        cur = get(cur->next, c);
    }
    if (!cur->isWord) {
        cur->isWord = true;
        trie->size++;
    }
}
//查询单词word是否在trie里
bool tr_contains(Trie* trie,char* word) {
    TrieNode* cur=trie->root;
    for (int i=0;word[i]!='\0';i++) {
        char c=word[i];
        TrieNode* child = get(cur->next, c);
        if (child == NULL) {
            return false;
        }
        cur = get(cur->next, c);
    }
    return cur->isWord;
}

//查询是否在Trie中有以prefix为前缀的
bool isPrefix(Trie* trie,char* prefix) {
    TrieNode* cur=trie->root;
    for (int i=0;prefix[i]!='\0';i++) {
        char c=prefix[i];
        TrieNode* child = get(cur->next, c);
        if (child==NULL) {
            return false;
        }
        cur = get(cur->next, c);
    }
    return true;
}

char book[] =
"It is a truth universally acknowledged, that a single man in possession of a good fortune, must be in want of a wife.\n"
"However little known the feelings or views of such a man may be on his first entering a neighbourhood, this truth is so well fixed in the minds of the surrounding families, that he is considered as the rightful property of some one or other of their daughters.\n"
"My dear Mr. Bennet,\" said his lady to him one day, \"have you heard that Netherfield Park is let at last?\"\n"
"Mr. Bennet replied that he had not.\n"
"But it is,\" returned she; \"for Mrs. Long has just been here, and she told me all about it.\"\n"
"Mr. Bennet made no answer.\n"
"Do not you want to know who has taken it?\" cried his wife impatiently.\n"
"You want to tell me, and I have no objection to hearing it.\"\n"
"This was invitation enough.\n"
"Why, my dear, you must know, Mrs. Long says that Netherfield is taken by a young man of large fortune from the north of England; that he came down on Monday in a chaise and four to see the place, and was so much delighted with it that he agreed with Mr. Morris immediately; that he is to take possession before Michaelmas, and some of his servants are to be in the house by the end of next week.\n"
"What is his name?\"\n"
"Bingley.\"\n"
"Is he married or single?\"\n"
"Oh! single, my dear, to be sure! A single man of large fortune; four or five thousand a year. What a fine thing for our girls!\"\n";

int main() {
    Trie* trie = trie_create();
    char word_buf[128];
    int idx = 0;

    clock_t start;
    // 遍历整篇字符串，拆分单词
    for(int i = 0; book[i] != '\0'; i++)
    {
        char c = book[i];
        if(isalpha(c))
        {
            word_buf[idx++] = tolower(c);
        }
        else
        {
            if(idx > 0)
            {
                word_buf[idx] = '\0';
                trie_add(trie, word_buf);
                idx = 0;
            }
        }
    }
    if(idx > 0)
    {
        word_buf[idx] = '\0';
        trie_add(trie, word_buf);
        idx = 0;
    }
    clock_t end;
    printf("单词总数（去重）：%d\n", tr_getSize(trie));
    printf("测试时间：%.6f\n", (end-start)/CLOCKS_PER_SEC);
    return 0;
}
#endif