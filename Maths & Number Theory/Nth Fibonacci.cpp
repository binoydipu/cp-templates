typedef vector<vector<int>> matrix;
// Multiply A x B matrices
matrix multiply(matrix &A, matrix &B) {
    matrix C(2, vector<int>(2, 0));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; ++k) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
            }
        }
    }
    return C;
}
matrix power(matrix A, long long b) { // matrix (A ^ b)
    matrix res = {{1, 0}, {0, 1}};
    while (b) {
        if (b & 1) res = multiply(res, A);
        A = multiply(A, A);
        b >>= 1;
    }
    return res;
}
// Function to calculate the nth Fibonacci number
// using matrix exponentiation
int fibonacci(int n) {
    if (n <= 1) return n;
    // Initialize the transformation matrix
    matrix F = {{1, 1}, {1, 0}};
    matrix res = power(F, n - 1);
    return res[0][0];
}