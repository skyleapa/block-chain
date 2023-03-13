#include "chain.h"
#include "chain_given.cpp"
#include <cmath>
#include <iostream>

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain()
{
    clear();
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block &ndata)
{
    Node *tail = walk(head_, length_);
    tail->next = new Node(ndata);
    tail->next->next = head_;
    length_++;
}


/**
 * Swaps the two nodes at the indexes "node1" and "node2".
 * The indexes of the nodes are 1 based.
 * assumes i and j are valid (in {1,length_} inclusive)
 * 
 */
void Chain::swap(int i, int j)
{
    Node *previ = walk(head_, i - 1);
    Node *curri = walk(head_, i);
    Node *prevj = walk(head_, j - 1);
    Node *currj = walk(head_, j);
    Node *nextj = walk(head_, j + 1);

    if (abs(j - i) == 1) {
        curri->next = nextj;
        currj->next = curri;
        previ->next = currj;
    } else {
        curri->next = nextj;
        currj->next = curri;
        previ->next = currj;
        prevj->next = curri;
    }
}

/**
 * Reverses the chain
 */
void Chain::reverse()
{
    Node *prev = head_;
    Node *curr = head_->next;
    
    while(curr != head_) {
        Node *nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }

    head_->next = prev;

}

/*
* Modifies the current chain by "rotating" every k nodes by one position.
* In every k node sub-chain, remove the first node, and place it in the last 
* position of the sub-chain. If the last sub-chain has length less than k,
* then don't change it at all. 
* Some examples with the chain a b c d e:
*   k = 1: a b c d e
*   k = 2: b a d c e
*   k = 3: b c a d e
*   k = 4: b c d a e
*/
void Chain::rotate(int k)
{
    int start = 1;
    int end = k;
    int traversed = 0;
    int capacity = size();

    while (traversed + k <= capacity) {

        for (int i = start; i < end; i++) {
            swap(i, i + 1);
        }

        start += k;
        end += k;
        traversed += k;
    }
}

/**
 * Destroys ALL dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear()
{
    // for (int i = 0; i < length_; i++) {
    //     Node *temp = head_;
    //     head_ = head_->next;
    //     delete(temp);
    //     temp = NULL;
    // }
    Node *currNode = head_->next;
    while (currNode != head_) {
        Node *temp = currNode;
        currNode = currNode->next;
        delete temp;
    }
    delete head_;
    length_ = 0;
}


/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other)
{
    height_ = other.height_;
    width_ = other.width_;
    length_ = other.length_;

    Node *currOther = other.head_;
    Node *currNewList = new Node();
    head_ = currNewList;

    while(currOther->next != other.head_) {
        currNewList->next = new Node(currOther->next->data);
        currOther = currOther->next;
        currNewList = currNewList->next;
    }

    currNewList->next = head_;

}
