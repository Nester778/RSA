#include <iostream>
#include <cryptlib.h>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iomanip>
#include "Func.h"

using namespace std;

int main() {
    srand(static_cast<unsigned>(time(0)));

    // generation of prime numbers p and q
    int p = generateRandomPrime();
    int q = generateRandomPrime();

    // calculation of the module n and the Euler function phi
    int n = p * q;
    int phi = calculatePhi(p, q);

    // generation of public and secret keys
    int publicKey = generatePublicKey(phi);
    int privateKey = generatePrivateKey(publicKey, phi);

    // Output of keys
    cout << "Public Key (n, e): (" << n << ", " << publicKey << ")\n";
    cout << "Private Key (n, d): (" << n << ", " << privateKey << ")\n";

    // Example message for a signature
    string message = "Hello, RSA!";

    // Calculating the hash value of the message
    int messageHash = calculateHash(message);

    // Signing a message
    int signature = signMessage(messageHash, privateKey, n);

    // Signature output
    cout << "Signature: " << signature << "\n";

    // Signature verification
    bool isVerified = verifySignature(messageHash, signature, publicKey, n);

    // Output of the check result
    if (isVerified) {
        cout << "Signature is verified.\n";
    }
    else {
        cout << "Signature verification failed.\n";
    }

    return 0;
}