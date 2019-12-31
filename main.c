#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define ull unsigned long long

ull g(ull x, ull c, unsigned int pow) {
    ull p = 1;
    for(int i = 0; i < pow; i++) {
        p *= x;
    }
    return p + c;
}
ull gcd(ull a ,ull b){
    ull rem;
    do {
        rem = a%b;
        a = b;
        b = rem;
    }while(rem != 0);
    return a;
}
ull pollard_rho_factor(ull n) {
    int pow = 2;

    if (n == 4) {
        pow = 3;
    }

    bool success = false;
    ull d = 0;
    int i = 0;
    srand(time(NULL));
    do {
        ull x0 = rand() % (n);
        ull c = i + 1;
        ull x = x0, y = x0;
        int j = 0;
        do {
            x = g(x, c, pow) % n;
            y = g(g(y, c, pow), c, pow) % n;
            d = gcd((ull) x - y, n);
            j++;
        } while (d == 1 && j < 1000);
        if (j >= 1000) {
            i++;
        } else if (d != n && d != 1) {
            success = true;
        } else {
            i++;
        }
    } while (!success && i < 100);
    if (!success) {
        return n;
    }
    return d;
}

void factorise_pollard_rho(ull n) {
    ull a = pollard_rho_factor(n);
    if(a == n || a == 1) {
        printf("%lld\n", a);
        return;
    }
    factorise_pollard_rho(a);
    ull b = n/a;
    factorise_pollard_rho(b);
}

int main() {
    ull var;
    scanf("%lld", &var);
    factorise_pollard_rho(var);
    return 0;
}
