#include "prime.hpp"
#include <cmath>
#include <cstdlib>
#include <tuple>
#include <iostream>
#include <random>



bigInt primeGen::randPrime(){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rand;
    
    bool isNumPrime = false; 
    bigInt randNum = 0;

    while(!isPrime(randNum, 100)){
        randNum = rand(rng) >> 40;
    }    

    return randNum;
}

bool primeGen::isPrime(bigInt n, unsigned int k) {
    if (n <= 1 || n % 2 == 0)
        return false;
    
    if (n <= 3)
        return true;

    auto sd = decompose(n);

    bigInt s = std::get<0>(sd);
    bigInt d = std::get<1>(sd);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<bigInt> dis(2, n - 2);
    
    bigInt y = 0;

    for(int count = 0; count < k; count++) {
        bigInt a = dis(gen);
        bigInt x = power(a, d, n);

        for (bigInt i = 0; i < s; i++) {
            y = (x * x) % n;
            
            if (x != 1 && y == 1 && x != n - 1)
                return false;

            x = y;
        }

        if(y != 1)
            return false;
    }

    return true;
}

std::tuple<bigInt, bigInt> primeGen::decompose(bigInt n) {
    bigInt d = n - 1;
    bigInt s = 0;
    
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }
    return { s, d };
}

bigInt primeGen::power(bigInt a, bigInt e, bigInt mod) {
    bigInt res = 1;
    a %= mod;
    while (e > 0) {
        if (e & 1)
            res = (res * a) % mod;
        e >>= 1;
        a = (a * a) % mod;
    }
    return res;
}

