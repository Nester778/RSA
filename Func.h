#pragma once
#include <iostream>
#include <cryptlib.h>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

bool isPrime(int n);
int gcd(int a, int b);
int calculatePhi(int p, int q);
int generateRandomPrime();
int generatePublicKey(int phi);
int generatePrivateKey(int e, int phi);
int modPow(int a, int b, int m);
int calculateHash(const string& message);
int signMessage(int messageHash, int privateKey, int n);
bool verifySignature(int messageHash, int signature, int publicKey, int n);