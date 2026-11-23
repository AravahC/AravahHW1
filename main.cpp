#include "Utilities.h"
#include "Transaction.h"
#include "BlockChain.h"
#include <fstream>
#include <iostream>

int main(){
    BlockChain blockie;
    std::ofstream outFile("tests/hash.out");
    std::ifstream inFile("tests/hash.source");
    blockie = BlockChainLoad(inFile);
    std::cout<< "Was able to load the blockchain!" << std::endl;
    //BlockChainCompress(blockie);
    //std::cout<< "Compressed the Blockchain!" << std::endl;
    BlockChainDumpHashed(blockie, outFile);
    std::cout<< "Was able to dump the blockchain!" << std::endl;
    inFile.close();
    outFile.close();
    return 0;
}