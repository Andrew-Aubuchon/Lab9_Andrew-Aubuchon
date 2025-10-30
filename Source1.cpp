// main.cpp
// EECS 348 - Lab 9: Matrix Operations
// Name: Andrew Aubuchon
// KUID: 3165875
// Date: October 27, 2025
//
// This program reads two square matrices from a file and performs different operations
// such as addition, multiplication, diagonal sums, row/column swaps, and updates.

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

using Matrix = vector<vector<int>>;

// Reads matrix size and data for A and B from a file
bool loadMatrices(const string& fname, int& N, Matrix& A, Matrix& B) {
    ifstream in(fname);
    if (!in) {
        cerr << "Error: could not open file " << fname << "\n";
        return false;
    }

    if (!(in >> N) || N <= 0) {
        cerr << "Error: invalid matrix size\n";
        return false;
    }

    // set up matrices
    A.assign(N, vector<int>(N, 0));
    B.assign(N, vector<int>(N, 0));

    // read matrix A
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (!(in >> A[i][j])) {
                cerr << "Error reading matrix A\n";
                return false;
            }

    // read matrix B
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (!(in >> B[i][j])) {
                cerr << "Error reading matrix B\n";
                return false;
            }

    return true;
}

// Prints a matrix neatly formatted
void printMatrix(const Matrix& M, const string& label = "") {
    if (!label.empty()) cout << label << ":\n";
    int N = M.size();
    int maxv = 0;
    for (auto& row : M)
        for (int val : row)
            maxv = max(maxv, abs(val));

    int w = max(2, (int)to_string(maxv).size()) + 1;

    for (auto& row : M) {
        for (int val : row)
            cout << setw(w) << val;
        cout << '\n';
    }
    cout << '\n';
}

// Adds two matrices
Matrix add(const Matrix& A, const Matrix& B) {
    int N = A.size();
    Matrix C(N, vector<int>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

// Multiplies two matrices
Matrix multiply(const Matrix& A, const Matrix& B) {
    int N = A.size();
    Matrix C(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++)
        for (int k = 0; k < N; k++)
            for (int j = 0; j < N; j++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

// Gets sum of main diagonal
long long sumMainDiagonal(const Matrix& M) {
    long long sum = 0;
    for (int i = 0; i < (int)M.size(); i++)
        sum += M[i][i];
    return sum;
}

// Gets sum of secondary diagonal
long long sumSecondaryDiagonal(const Matrix& M) {
    long long sum = 0;
    int N = M.size();
    for (int i = 0; i < N; i++)
        sum += M[i][N - 1 - i];
    return sum;
}

// Swaps two rows
bool swapRows(Matrix& M, int r1, int r2) {
    int N = M.size();
    if (r1 < 0 || r2 < 0 || r1 >= N || r2 >= N) return false;
    swap(M[r1], M[r2]);
    return true;
}

// Swaps two columns
bool swapCols(Matrix& M, int c1, int c2) {
    int N = M.size();
    if (c1 < 0 || c2 < 0 || c1 >= N || c2 >= N) return false;
    for (int i = 0; i < N; i++)
        swap(M[i][c1], M[i][c2]);
    return true;
}

// Updates one element in the matrix
bool updateElement(Matrix& M, int r, int c, int val) {
    int N = M.size();
    if (r < 0 || c < 0 || r >= N || c >= N) return false;
    M[r][c] = val;
    return true;
}

// Lets user choose between matrix A or B
char chooseAB() {
    cout << "Choose matrix (A or B): ";
    char ch;
    cin >> ch;
    ch = toupper(ch);
    if (ch != 'A' && ch != 'B') {
        cout << "Invalid choice, defaulting to A.\n";
        return 'A';
    }
    return ch;
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string fname;
    // Let user give file name
    if (argc >= 2) fname = argv[1];
    else {
        cout << "Enter input filename: ";
        cin >> fname;
    }

    int N;
    Matrix A, B;

    // Load matrices from file
    if (!loadMatrices(fname, N, A, B)) return 1;

    cout << "Loaded matrices (N = " << N << ")\n\n";
    printMatrix(A, "Matrix A");
    printMatrix(B, "Matrix B");

    // Menu loop
    while (true) {
        cout << "Menu:\n"
            << "1. Print matrices\n"
            << "2. Add A + B\n"
            << "3. Multiply A * B\n"
            << "4. Diagonal sums\n"
            << "5. Swap rows\n"
            << "6. Swap columns\n"
            << "7. Update element\n"
            << "8. Reload from file\n"
            << "0. Exit\n"
            << "Choice: ";

        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid input, exiting.\n";
            break;
        }

        if (choice == 0) break;

        if (choice == 1) {
            printMatrix(A, "Matrix A");
            printMatrix(B, "Matrix B");
        }
        else if (choice == 2) {
            Matrix C = add(A, B);
            printMatrix(C, "A + B");
        }
        else if (choice == 3) {
            Matrix C = multiply(A, B);
            printMatrix(C, "A * B");
        }
        else if (choice == 4) {
            char which = chooseAB();
            Matrix& M = (which == 'A') ? A : B;
            long long m = sumMainDiagonal(M);
            long long s = sumSecondaryDiagonal(M);
            cout << which << " main diagonal sum = " << m << '\n';
            cout << which << " secondary diagonal sum = " << s << '\n';
            cout << which << " total = " << (m + s) << "\n\n";
        }
        else if (choice == 5) {
            char which = chooseAB();
            Matrix& M = (which == 'A') ? A : B;
            int r1, r2;
            cout << "Enter row1 (0-based): ";
            cin >> r1;
            cout << "Enter row2 (0-based): ";
            cin >> r2;
            if (swapRows(M, r1, r2)) {
                cout << "Swapped rows.\n";
                printMatrix(M, string("Matrix ") + which);
            }
            else {
                cout << "Invalid rows.\n\n";
            }
        }
        else if (choice == 6) {
            char which = chooseAB();
            Matrix& M = (which == 'A') ? A : B;
            int c1, c2;
            cout << "Enter col1 (0-based): ";
            cin >> c1;
            cout << "Enter col2 (0-based): ";
            cin >> c2;
            if (swapCols(M, c1, c2)) {
                cout << "Swapped columns.\n";
                printMatrix(M, string("Matrix ") + which);
            }
            else {
                cout << "Invalid columns.\n\n";
            }
        }
        else if (choice == 7) {
            char which = chooseAB();
            Matrix& M = (which == 'A') ? A : B;
            int r, c, v;
            cout << "Enter row (0-based): ";
            cin >> r;
            cout << "Enter col (0-based): ";
            cin >> c;
            cout << "Enter new value: ";
            cin >> v;
            if (updateElement(M, r, c, v)) {
                cout << "Updated value.\n";
                printMatrix(M, string("Matrix ") + which);
            }
            else {
                cout << "Invalid indices.\n\n";
            }
        }
        else if (choice == 8) {
            cout << "Enter filename: ";
            string f;
            cin >> f;
            if (loadMatrices(f, N, A, B)) {
                cout << "Reloaded.\n";
                printMatrix(A, "Matrix A");
                printMatrix(B, "Matrix B");
            }
            else {
                cout << "Reload failed.\n";
            }
        }
        else {
            cout << "Unknown choice.\n";
        }
    }

    cout << "Goodbye.\n";
    return 0;
}
