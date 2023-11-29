#include <iostream>
#include <cryptlib.h>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Функція для перевірки простоти числа
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Функція для знаходження НСД
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Функція для обчислення ейлерової функції
int calculatePhi(int p, int q) {
    return (p - 1) * (q - 1);
}

// Функція для генерації випадкового простого числа
int generateRandomPrime() {
    int num;
    do {
        num = rand() % 100 + 1;
    } while (!isPrime(num));
    return num;
}

// Функція для знаходження відкритого ключа
int generatePublicKey(int phi) {
    int e = 2; // Зазвичай використовується 65537 як значення e
    while (e < phi) {
        if (gcd(e, phi) == 1) break;
        e++;
    }
    return e;
}

// Функція для знаходження секретного ключа
int generatePrivateKey(int e, int phi) {
    int k = 1;
    while (true) {
        k += phi;
        if (k % e == 0) return k / e;
    }
}

// Функція для обчислення модулярного експоненціювання (a^b mod m)
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

// Функція для обчислення геш-значення повідомлення
int calculateHash(const string& message) {
    int hash = 0;
    for (char ch : message) {
        hash += static_cast<int>(ch);
    }
    return hash;
}

// Функція для підпису повідомлення
int signMessage(int messageHash, int privateKey, int n) {
    return modPow(messageHash, privateKey, n);
}

// Функція для перевірки цифрового підпису
bool verifySignature(int messageHash, int signature, int publicKey, int n) {
    int decryptedSignature = modPow(signature, publicKey, n);
    return decryptedSignature == messageHash;
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    // Генерація простих чисел p та q
    int p = generateRandomPrime();
    int q = generateRandomPrime();

    // Обчислення модуля n та ейлерової функції phi
    int n = p * q;
    int phi = calculatePhi(p, q);

    // Генерація відкритого та секретного ключів
    int publicKey = generatePublicKey(phi);
    int privateKey = generatePrivateKey(publicKey, phi);

    // Виведення ключів
    cout << "Public Key (n, e): (" << n << ", " << publicKey << ")\n";
    cout << "Private Key (n, d): (" << n << ", " << privateKey << ")\n";

    //Приклад повідомлення для підпису
    string message = "Hello, RSA!";

    // Обчислення геш-значення повідомлення
    int messageHash = calculateHash(message);

    // Підписання повідомлення
    int signature = signMessage(messageHash, privateKey, n);

    // Виведення підпису
    cout << "Signature: " << signature << "\n";

    // Перевірка підпису
    bool isVerified = verifySignature(messageHash, signature, publicKey, n);

    // Виведення результату перевірки
    if (isVerified) {
        cout << "Signature is verified.\n";
    }
    else {
        cout << "Signature verification failed.\n";
    }

    return 0;
}