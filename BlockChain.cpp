#include <string>
#include <fstream>
#include <iostream>
#include "Transaction.h"
#include "BlockChain.h"

using std::string;
using std::ifstream;
using std::ofstream;


typedef unsigned int (*updateFunction)(unsigned int);




/**
 * @return newly initialized empty BlockChain Object
*/
BlockChain BlockChainInit(){
    BlockChain blockchain;
    blockchain.size = 0;
    blockchain.head = nullptr;
    return blockchain;
}

/**
 * BlockChainDestory - Destroys an existing BlockChain and deallocates all of its memory, after calling this method, blockChain can't be used/accessed again.
*/
void BlockChainDestroy(BlockChain& blockChain){
    while(blockChain.head != nullptr){
        Node* temp = blockChain.head->next;
        delete blockChain.head;
        blockChain.head = temp;
    }
    blockChain.size = 0;
}


/**
 * BlockChainGetSize - returns the number of Blocks in the BlockChain
 *
 * @param blockChain - BlockChain to measure
 *
 * @return Number of Blocks in the BlockChain
*/
int BlockChainGetSize(const BlockChain& blockChain){
    return blockChain.size;
}


/**
 * BlockChainPersonalBalance - returns the balance of a given person, relative to a given BlockChain
 *
 * @param blockChain - BlockChain to calculate the balance from
 * @param name - Name of the person to calculate the balance for
 *
 * @return Balance of the person
*/
int BlockChainPersonalBalance(const BlockChain& blockChain, const string& name){
    int balance = 0;
    bool personFound = false;
    Node* iter = blockChain.head;
    while(iter!=nullptr){
        if(iter->transaction.sender == name){
            balance -= iter->transaction.value;
            personFound = true;
        }
        else if(iter->transaction.receiver == name){
            balance += iter->transaction.value;
            personFound = true;
        }
        iter = iter->next;
    }
    if(personFound){
        return balance;
    }
    return -1;
}



/**
 * BlockChainAppendTransaction - creates and appends a new transaction to the BlockChain
 *
 * @param blockChain BlockChain to append the transaction to
 * @param value Value of the transaction
 * @param sender Name of the sender
 * @param receiver Name of the receiver
 * @param timestamp String that holds the time the transaction was made
*/
void BlockChainAppendTransaction(
        BlockChain& blockChain,
        unsigned int value,
        const string& sender,
        const string& receiver,
        const string& timestamp
){
    std::cout<< "EnteredAppendTransaction" << std::endl;
    Node* iter = blockChain.head;
    if(iter == nullptr){
        Node* newNode = new Node;
        Transaction transaction;
    //std::cout<< "Initialized my node iter as the head of the blockchain and the transaction" << std::endl;
    transaction.value = value;
    transaction.sender = sender;
    transaction.receiver = receiver;
    newNode-> transaction = transaction;
    newNode->timestamp = timestamp;
    blockChain.head = newNode;
    return;
    }
    while(iter->next != nullptr){
        //std::cout<< "Iterating to next element"<< std::endl;
        iter = iter->next;
    }
    
   // std::cout<< "Segfault here? after iterating to last element?" << std::endl; 
    Transaction transaction;
    //std::cout<< "Initialized my node iter as the head of the blockchain and the transaction" << std::endl;
    transaction.value = value;
    transaction.sender = sender;
    transaction.receiver = receiver;
    //std::cout<< "Transaction.sender" << transaction.sender << std::endl;
    //std::cout<< "set the values of the new transaction" << std::endl;
    Node* newNode = new Node;
    //std::cout<< "Created the new node" << std::endl;
    newNode-> transaction = transaction;
    newNode->timestamp = timestamp;
    //std::cout<< "Set the timestamp as timestamp of the newNode" << std::endl;

    //std::cout<< "Node " << std::endl;
    iter->next = newNode;
   // std::cout<< "iter->next to be newNode"<< std::endl; 
    blockChain.size++;
}


/**
 * BlockChainAppendTransaction - appends a copy of a given transaction to the BlockChain
 *
 * @param blockChain BlockChain to append the transaction to
 * @param transaction Transaction we want to append
 * @param timestamp String that holds the time the transaction was made
*/
void BlockChainAppendTransaction(
        BlockChain& blockChain,
        const Transaction& transaction,
        const string& timestamp
){
    Node* iter = blockChain.head;
    while(iter->next!=nullptr){
        iter = iter->next;
    }
    Node* newNode = nullptr;
    newNode->transaction = transaction;
    newNode->timestamp = timestamp;
    iter->next = newNode;
    blockChain.size++;
}


/**
 * BlockChainLoad - Reads data from a file and creates a new block chain
 *
 * @param file Data file to read from
 *
 * @return BlockChain created from the file
 *
*/
BlockChain BlockChainLoad(ifstream& file){
    BlockChain block = BlockChainInit();
    std::string sender;
    std::string receiver;
    int sum = 0;
    int value;
    std::string timestamp;
    //std::cout<< "I have entered the BlockChainLoad Function" << std::endl;
    while(file >> sender >> receiver >> value >> timestamp){
      //  std::cout<< "added element: " << sum+1 << std::endl;
        BlockChainAppendTransaction(block, value, sender, receiver, timestamp);
        sum++;
    }
    block.size = sum;
    return block;
}


/**
 * BlockChainDump - Prints the data of all transactions in the BlockChain to a given file
 *
 * Data will be printed in the following format:
 *
 * BlockChain info:
 * <n>.
 * Sender Name: <name>
 * Receiver Name: <name>
 * Transaction Value: <value>
 * Transaction Timestamp: <time>
 *
 * @param blockChain BlockChain to print
 * @param file File to print to
 *
*/
void BlockChainDump(const BlockChain& blockChain, ofstream& file){
    file << "BlockChain Info:" << std::endl;
    Node* iter = blockChain.head;
    int num = 1;
    while(iter != nullptr){
        file << num << "."<< std::endl;
        TransactionDumpInfo(iter->transaction, file);
        file << "Transaction timestamp: " << iter->timestamp << std::endl;
        iter = iter->next;
        num++;
    }
}



/**
 * BlockChainDumpHashed - Prints the *hashed data* of all transactions in the BlockChain to a given file
 *
 * Data will be printed in the following format:
 * <hashed message>
 * <hashed message>
 * ...
 * <hashed message>
 *
 * @param blockChain BlockChain to print
 * @param file File to print to
 *
*/
void BlockChainDumpHashed(const BlockChain& blockChain, ofstream& file){

    //file << "BlockChain Info:" << std::endl;
    Node* iter = blockChain.head;
    int num = 1;
    while(iter->next != nullptr){
        //file << num << "."<< std::endl;
        //TransactionDumpInfo(iter->transaction, file);
        std::cout<< "This is number: "<< num << std::endl;
        file << TransactionHashedMessage(iter->transaction) << std::endl;
        iter = iter->next;
        num++;
    }
    file << TransactionHashedMessage(iter->transaction);
    //file << std::endl;
}
/*     Node* iter = blockChain.head;
    std::cout<< "Blockchain size: " << blockChain.size << std::endl;
    int num = 1;
    while(iter != nullptr){
        std::cout<< "Added trasnaction number: " << num << std::endl;
        std::string hash = TransactionHashedMessage(iter->transaction);
        file << hash << std::endl;
        iter = iter->next;
        std::cout << "Time of next transaction: " << iter->timestamp << std::endl;
        num++;
    } */


/**
 * BlockChainVerifyFile - verifies that the file contains correct hashed messages of the given BlockChain
 *
 * Input file is expected to contain data in the following format:
 * <hashed message>
 * <hashed message>
 * ...
 * <hashed message>
 *
 * @param blockChain BlockChain to verify
 * @param file File to read from
 *
 * @return true if the file is valid, false otherwise
*/
bool BlockChainVerifyFile(const BlockChain& blockChain, std::ifstream& file){
    //if error, check the sizing
    Node* iter;
    std::string hashed;
    bool hashedCorrectly = true;
    while(file >> hashed){
        if(!TransactionVerifyHashedMessage(iter->transaction, hashed)){
            return false;
        }
        iter = iter->next;
    }
    return hashedCorrectly;
}


/**
 * BlockChainCompress - Compresses the given block chain based on the transaction's data.
 * All consecutive blocks with the same sender and receiver will be compressed to one Block.
 *
 * @param blockChain BlockChain to compress
*/
void BlockChainCompress(BlockChain& blockChain){
    Node* iter = blockChain.head;
    while(iter->next != nullptr){
        if ((iter->transaction.sender == iter->next->transaction.sender) && (iter->transaction.receiver == iter->next->transaction.receiver)){
            iter->transaction.value += iter->next->transaction.value;
            //std::cout<< "Old timestamp: " << iter->timestamp << " New timestamp: "<< iter->next->timestamp << std::endl;
            iter->timestamp = iter->next->timestamp;
        }
        Node* newNode = iter->next->next;
        Node* nodeToDelete = iter->next;
        iter->next = newNode;
        delete nodeToDelete;
    }
}


/**
 * BlockChainTransform - Update the values of each transaction in the BlockChain
 *
 * @param blockChain BlockChain to update
 * @param function a pointer to a transform function
*/
void BlockChainTransform(BlockChain& blockChain, updateFunction function){

}
