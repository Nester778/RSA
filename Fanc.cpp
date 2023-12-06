#include <iostream>
#include <cryptlib.h>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// function to check the primeness of a number
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// function for finding GCD
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// function for calculating the Euler function
int calculatePhi(int p, int q) {
    return (p - 1) * (q - 1);
}

// function for generating a random prime number
int generateRandomPrime() {
    int num;
    do {
        num = rand() % 100 + 1;
    } while (!isPrime(num));
    return num;
}

// function for finding public key
int generatePublicKey(int phi) {
    int e = 2;
    while (e < phi) {
        if (gcd(e, phi) == 1) break;
        e++;
    }
    return e;
}

// function for finding the secret key
int generatePrivateKey(int e, int phi) {
    int k = 1;
    while (true) {
        k += phi;
        if (k % e == 0) return k / e;
    }
}

// function for calculating modular exponentiation (a^b mod m)
int modPow(int a, int b, int m) {
    int result = 1;
    a = a % m;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % m;
        }
        b = b / 2;
        a = (a * a) % m;
    }
    return result;
}

// function to calculate the hash value of a message
int calculateHash(const string& message) {
    int hash = 0;
    for (char ch : message) {
        hash += static_cast<int>(ch);
    }
    return hash;
}

// message signature function
int signMessage(int messageHash, int privateKey, int n) {
    return modPow(messageHash, privateKey, n);
}

// digital signature verification function
bool verifySignature(int messageHash, int signature, int publicKey, int n) {
    int decryptedSignature = modPow(signature, publicKey, n);
    return decryptedSignature == messageHash;
}
