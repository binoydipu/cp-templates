// Euler's totient function, also known as phi-function Φ(n) , 
// counts the number of integers between 1 and n inclusive, which are coprime to n.
void phi_1_to_n(int n) { // O(loglogn)
    vector<int> phi(n + 1);
    for (int i = 0; i <= n; i++) phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}