#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int mod_inverse(int a, int m) {
    int m0 = m;
    int y = 0, x = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        int q = a / m;
        int t = m;

        m = a % m;
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += m0;

    return x;
}

int encrypt(int msg, int e, int n) {
    int result = 1;
    while (e > 0) {
        if (e & 1)
            result = (result * msg) % n;
        msg = (msg * msg) % n;
        e >>= 1;
    }
    return result;
}

int decrypt(int encrypted, int d, int n) {
    int result = 1;
    while (d > 0) {
        if (d & 1)
            result = (result * encrypted) % n;
        encrypted = (encrypted * encrypted) % n;
        d >>= 1;
    }
    return result;
}

void rsa_encrypt_decrypt(int p, int q, int msg) {
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e = 2;
    while (gcd(e, phi) != 1) {
        e++;
    }
    int d = mod_inverse(e, phi);

    int encrypted = encrypt(msg, e, n);
    int decrypted = decrypt(encrypted, d, n);

    printf("p: %d, q: %d, msg: %d\n", p, q, msg);
    printf("Encrypted: %d\n", encrypted);
    printf("Decrypted: %d\n\n", decrypted);
}

int main() {
    int test_cases[][3] = {
        {3, 11, 12},
        {5, 7, 25},
        {7, 11, 30},
        {11, 13, 40},
        {13, 17, 50}
    };

    for (int i = 0; i < 5; i++) {
        rsa_encrypt_decrypt(test_cases[i][0], test_cases[i][1], test_cases[i][2]);
    }

    return 0;
}