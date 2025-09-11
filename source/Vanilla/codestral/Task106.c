#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef long long ll;

ll generate_prime() {
    ll num;
    do {
        num = (rand() % ((ll)pow(2, 1024) - (ll)pow(2, 1023))) + (ll)pow(2, 1023);
    } while (!is_prime(num));
    return num;
}

int is_prime(ll num) {
    if (num < 2) {
        return 0;
    }
    for (ll i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

ll generate_e(ll phi) {
    ll e = 2;
    while (__gcd(e, phi) != 1) {
        e++;
    }
    return e;
}

ll mod_inverse(ll a, ll m) {
    ll m0 = m, t, q;
    ll x0 = 0, x1 = 1;

    if (m == 1) {
        return 1;
    }

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) {
        x1 += m0;
    }

    return x1;
}

typedef struct {
    ll p, q, n, phi, e, d;
} Task106;

Task106* create_rsa() {
    Task106* rsa = (Task106*)malloc(sizeof(Task106));
    rsa->p = generate_prime();
    rsa->q = generate_prime();
    rsa->n = rsa->p * rsa->q;
    rsa->phi = (rsa->p - 1) * (rsa->q - 1);
    rsa->e = generate_e(rsa->phi);
    rsa->d = mod_inverse(rsa->e, rsa->phi);
    return rsa;
}

ll encrypt(Task106* rsa, ll message) {
    return (ll)pow(message, rsa->e) % rsa->n;
}

ll decrypt(Task106* rsa, ll encrypted_message) {
    return (ll)pow(encrypted_message, rsa->d) % rsa->n;
}

int main() {
    srand(time(0));
    Task106* rsa = create_rsa();
    ll messages[] = {12345, 67890, 54321, 98765, 13579};
    int size = sizeof(messages) / sizeof(messages[0]);

    for (int i = 0; i < size; i++) {
        ll encrypted_message = encrypt(rsa, messages[i]);
        ll decrypted_message = decrypt(rsa, encrypted_message);
        printf("Original Message: %lld\n", messages[i]);
        printf("Encrypted Message: %lld\n", encrypted_message);
        printf("Decrypted Message: %lld\n", decrypted_message);
        printf("\n");
    }

    free(rsa);
    return 0;
}