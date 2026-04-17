//  main.cpp
//  Power__of__Lists
//
//  Created by Antonio Johnson on 4/14/26.

#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;

struct Node {
    int numbers;
    Node * prev;
    Node * next;
    Node(int n) {
        numbers = n;
        prev = NULL;
        next  = NULL;
    }
};

void Multiply(Node** head, Node** tail, int base) {
    Node* curr = *tail;
    int carry = 0;
    
    while (curr != NULL) {
        int prod = curr->numbers * base + carry;
        curr->numbers = prod %10;
        carry = prod /10;
        
        if(curr->prev == NULL) break;
        curr = curr->prev;
        
    }
    
    while (carry !=0) {
        Node* nextNode = new Node(carry % 10);
        nextNode->next = *head;
        (*head)->prev = nextNode;
        *head = nextNode;
        carry /= 10;
    }
   
}

int main() {
    int m, n;
    
    cout << " --- Welcome to the Power of Lists Calculator (m^n)   :) ---" << endl;
    cout << "Please enter a number for m to be the base number: ";
    if (!(cin >> m) || m < 0) {
        cout << " Please try again. Enter a number that is greater than zero and it cannot be a negative number. " << endl;
        return 1;
    }
    cout << "Please enter a number to the exponent (n): ";
    if (!(cin >> n) || n < 0) {
        cout << " Please try again. Enter a number that is greater than zero and it cannot be a negative number. " << endl;
        return 1;
    }
    
    auto start = chrono::high_resolution_clock::now();
    
    Node* head = new Node(1);
    Node* tail= head;
    
    if (n > 0) {
        for (int i = 1; i <= n; i++) {
            Multiply(&head,&tail, m);
        }
    }
    
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<long double> duration = stop - start;
    
    cout << "\nThe Reseults of (" << m << "^" << n << "): " << endl;
    int digitCount = 0;
    Node* temp = head;
    while (temp != NULL) {
        cout << temp->numbers;
        digitCount++;
        temp = temp->next;
    }
    cout << endl;

    
    cout << "\nThe total number of digits is: " << digitCount << endl;
    
    ofstream outFile ("/Users/tony/Desktop/Cis 150/Power__of__Lists/the_powerResults.txt");
    // ofstream outFile ("the_powerResults.txt")
    
    if (outFile.is_open()){
        Node* fileTemp = head;
        while (fileTemp != NULL) {
            outFile << fileTemp->numbers;
            fileTemp = fileTemp->next;
        }
        outFile.close();
        cout << "\nThe result are saved in the file the_powerResults.txt..." << endl;
    }
    
    cout << "The calculations took about " << duration.count() << " seconds. " << endl;
    
    return 0;
}
