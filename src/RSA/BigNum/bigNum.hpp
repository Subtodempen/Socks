#pragma once

#include <vector>
#include <iostream>

class BigNum{
    public:
        BigNum(unsigned int byteSize);
        ~BigNum();

        BigNum(const BigNum &copy);
        
        void rand();
        void set(unsigned long long num);   
        void print();
        constexpr inline size_t size() const;

        BigNum& operator=(const BigNum& obj);
        BigNum& operator=(unsigned long long num);    

        BigNum operator+(const BigNum& obj) const;
        BigNum operator+(const unsigned long long) const;
        
        BigNum operator-(const BigNum& obj) const;
        
        BigNum operator*(const BigNum& obj) const;
        BigNum operator*(const unsigned long long num) const;
        
        std::pair<BigNum, BigNum> operator/(const BigNum& obj) const; 

        BigNum operator%(const BigNum& obj) const;
        
        bool operator==(const BigNum& obj) const;
        bool operator>(const BigNum& obj);
        bool operator>=(const BigNum& obj);
    
    private:
        std::vector<unsigned int> vectorNum;   
        const unsigned int base = 10;

        int getFirstNum() const;
};
