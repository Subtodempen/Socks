#include "bigNum.hpp"
#include <algorithm>
#include <random>

BigNum::BigNum(unsigned int bitSize){
    vectorNum.resize(bitSize);

    std::fill(vectorNum.begin(), vectorNum.end(), 0);
}

BigNum::BigNum(const BigNum &copy){
    this->vectorNum = copy.vectorNum;
}

BigNum::~BigNum(){}

void BigNum::print(){
    for(int i=0; i < vectorNum.size(); i++){
        std::cout<<vectorNum.at(i);
    }
    
    std::cout<<std::endl;
}


void BigNum::rand(){
    for(unsigned int &i : vectorNum){
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> rand(0, 9);

        i = rand(rng);
    }
}

constexpr inline size_t BigNum::size() const{
    return vectorNum.size();
}


int BigNum::getFirstNum() const{
    int i = vectorNum.size()-1;

    while(vectorNum.at(i) == 0 && i > 0)
        i--;

    return i;
}


