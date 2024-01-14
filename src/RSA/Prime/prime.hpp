#include <tuple>

using bigInt = unsigned long long;

class primeGen{
    public:
        bool isPrime(bigInt n, unsigned int k);
        bigInt randPrime();
    
    private:
        std::tuple<bigInt, bigInt> decompose(bigInt n);
        bigInt power(bigInt a, bigInt e, bigInt mod);
};
