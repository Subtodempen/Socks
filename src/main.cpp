#include "PeerToPeer/p2p.hpp"
#include "RSA/Prime/prime.hpp"
#include "RSA/BigNum/bigNum.hpp"

#include <iostream>
#include <ostream>
#include <string>


int main(int argc, char *argv[]){
    primeGen prime;
        
    std::cout<<":"<<prime.randPrime()<<std::endl;

    BigNum test(1024/4);
    BigNum test1(1024/4);
    BigNum test2(1024/4);
    
    test1 = 9833;
    test2 = 200;
    
    std::cout<< (test1 >= test2) <<std::endl;

    auto pair = test1 / test2;

    test = std::get<0>(pair);
    test1 = std::get<1>(pair);
    
    test.print();
    test1.print();
}


