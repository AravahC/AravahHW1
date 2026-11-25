#include "Utilities.h"
#include "Transaction.h"
#include "BlockChain.h"
#include <fstream>
#include <iostream>

int main(int argc, char* argument[]){
    if(argc != 4){
        std::cerr<< "Usage: ./mtm_blockchain <op> <source> <target>";
        return 1;
    }
    std::string operation = argument[1];
    std::string inFiletext = argument[2];
    std::string outFiletext = argument[3];
    BlockChain blockie;
    
    std::ifstream inFile(inFiletext);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open source file" << std::endl;
        return 1;
    }
    //std::ifstream inFile_target("tests/verify.target");
    blockie = BlockChainLoad(inFile);
    //std::cout<< "Was able to load the blockchain!" << std::endl;
    if(operation == "format"){
        std::ofstream outFile(outFiletext);
        BlockChainDump(blockie, outFile);
    }
    else if(operation == "hash"){
        std::ofstream outFile(outFiletext);
        BlockChainDumpHashed(blockie, outFile);
    }
    else if(operation == "compress"){
        std::ofstream outFile(outFiletext);
        BlockChainCompress(blockie);
        BlockChainDump(blockie, outFile);
       // std::cout<< "I am not segfault post dumping in compress" << std::endl;
    }
    else if(operation == "verify"){
        std::ifstream outFile(outFiletext);
        if(BlockChainVerifyFile(blockie, outFile)){
            std::cout<< "Verification passed"<< std::endl;
        }
        else{
            std::cout << "Verification failed" << std::endl;
        }
        BlockChainDumpHashed(blockie, outFile);
    }
    else {
        std::cerr << "Usage: ./mtm_blockchain <op> <source> <target>" << std::endl;
        BlockChainDestroy(blockie);
        inFile.close();
        return 1;
    }
    //BlockChainCompress(blockie);
    //std::cout<< "Compressed the Blockchain!" << std::endl;
    //bool yes = BlockChainVerifyFile(blockie, inFile_target);
    //std::cout<< "was unable to verify the blockchain!" << std::endl;
    //std::cout<< std::boolalpha << yes << std::endl;
    BlockChainDestroy(blockie);
    //std::cout<< "blockchain destroy is totally not the error" << std::endl;
    inFile.close();
    //inFile_target.close();
    //outFile.close();
    return 0;
}