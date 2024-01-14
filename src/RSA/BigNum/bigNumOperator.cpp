#include "bigNum.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <utility>

//TODO move to a diff file
//operator overloading
BigNum& BigNum::operator=(const BigNum& obj){
    this->vectorNum = obj.vectorNum;

    return *this;
}

BigNum& BigNum::operator=(unsigned long long num){
    BigNum bigNum(vectorNum.size());
    int i = 0;

    while(num != 0){
        bigNum.vectorNum.at(i) = num % 10;

        num /= 10; 
        i++;
    }

    this->vectorNum = bigNum.vectorNum;
    return *this;
}

BigNum BigNum::operator+(const BigNum& obj) const {
    BigNum output(this->vectorNum.size());
    int carry = 0;

    output.vectorNum = this->vectorNum;

    for(size_t i = 0; i < std::max(obj.vectorNum.size(), output.vectorNum.size()) || carry; i++){
        if(i == output.vectorNum.size())
            output.vectorNum.push_back(0);

        output.vectorNum[i] += carry + obj.vectorNum[i];

        if(base <= output.vectorNum[i]){
            carry = 1;
            output.vectorNum[i] %= 10;

        } else {
            carry = 0;
        }
    }
    
    return output;
}

BigNum BigNum::operator+(const unsigned long long num) const {
    BigNum temp(vectorNum.size());
    BigNum output(vectorNum.size());

    temp = num;
    output = *this + temp;

    return output;
}

/*
BigNum BigNum::operator-(const BigNum& obj) const {
    //create a new bigNum this is a kinda buffer and is what gets 
    BigNum output(this->vectorNum.size());
    int i = getFirstNum();

    output.vectorNum = this->vectorNum;
    
    //check to make sure lhs is bigger 
    if(output.vectorNum.at(i) < obj.vectorNum.at(i))
        return output;

    for(size_t i = 0; i < obj.vectorNum.size(); i++){
        unsigned int &lhs = output.vectorNum.at(i);
        unsigned int rhs = obj.vectorNum.at(i);
        int x = i;

        if(lhs >= rhs)
            lhs -= rhs;

        else{
            while(output.vectorNum.at(x) == 0)
                x++;
            x++;

            output.vectorNum.at(x) -= 1;

            lhs += 10;
            lhs -= rhs;
        }
    }

    return output;
}
*/

BigNum BigNum::operator-(const BigNum& obj) const {
    BigNum out(this->vectorNum.size());
    int carry = 0;

    auto &lhs = *this;
    auto &rhs = obj;

    for(size_t i=0; i < this->vectorNum.size(); i++){
        out.vectorNum.at(i) = lhs.vectorNum.at(i) - (carry + rhs.vectorNum.at(i));

        carry = out.vectorNum.at(i) > base;

        if(carry)
            out.vectorNum.at(i) = (lhs.vectorNum.at(i) + base) - rhs.vectorNum.at(i); // violates DRY i repeat myself
    }

    return out;
}


//temp will change
BigNum BigNum::operator*(const BigNum& obj) const{
    BigNum sum(this->vectorNum.size());

    for(size_t i = 1; i < std::min(this->vectorNum.size(), obj.vectorNum.size()); i++){
       sum = sum + obj; 
    }

    return sum;
}


BigNum BigNum::operator*(const unsigned long long num) const {
    BigNum tempSum(vectorNum.size());
    BigNum tempNum(sizeof(unsigned long long));
    
    tempNum = num; 
    tempSum = *this * tempNum;

    return tempSum;
}

//Euclids division algo VERY SLOW
std::pair<BigNum, BigNum> BigNum::operator/(const BigNum& obj) const{
    BigNum Q(vectorNum.size()); //result
    BigNum R(vectorNum.size()); //remender

    R = *this; //lhs
    Q = 0;

    while(R >= obj){
        R = R - obj;
        Q = Q + 1;
    }

    return {Q, R}; 
}

BigNum BigNum::operator%(const BigNum& obj) const{
    auto pair = *this / obj; 

    return std::get<1>(pair); 
}


//TODO
//implement binary left shift
//implement bit access
//so if you want to access a specific binary bit of a bigNUm you can dfo it
/*
std::pair<BigNum, BigNum> BigNum::operator/(const BigNum& obj){
    BigNum Q(vectorNum.size());
    BigNum R(vectorNum.size());
    
    Q = 0;
    R = 0;

    int i = getFirstNum(); // bigNUm has zeros after num so 2 would be stored as 2000000 and so on but doesnt matter because it stores data least signifacnt first 

    for(; i >= 0; i--){ // count down starting form first number other than zero
        R = R * 2;
        R.vectorNum.at(0) |= (obj.vectorNum.at(std::floor(i/4)) >> i) & 1; //get bit i and set it to bit zero

        if(R >= obj){
            R = R - obj;
            Q.vectorNum.at(std::floor(i/4)) |= (1 << i);
        }
    }

    return {Q, R};
}
*/
bool BigNum::operator==(const BigNum& obj) const {
    size_t i = vectorNum.size()-1;

    while(vectorNum.at(i) == obj.vectorNum.at(i)){
        if(i == 0)
            return true;
        

        i--;
    }

    return false;
}

bool BigNum::operator>(const BigNum& obj){
    int i = getFirstNum();

    while(i >= 0) {
        if (this->vectorNum.at(i) > obj.vectorNum.at(i))
            return true;
       
        else if (vectorNum.at(i) < obj.vectorNum.at(i))
            return false;
        
        i--;
    }

    return false; // Both numbers are equal
}


bool BigNum::operator>=(const BigNum& obj){
    if (*this > obj)
        return true;
     

    return (*this == obj);
}
