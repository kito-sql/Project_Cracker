#include <iostream>
#include <vector>

using namespace std;

struct A {
    int guess[3];
    int right;
    int misplaced;
    int wrong;
};

void score_candidate(int code[3], int guess[3], int &right, int &misplaced, int &wrong) {
    right = misplaced = wrong = 0;

    for (int i = 0; i < 3; i++) {
        if (code[i] == guess[i]) {
            right++;
            guess[i] = -1;
            code[i] = -1;
        }
    }

    for (int i = 0; i < 3; i++) {
        if (guess[i] != -1) {
            for (int j = 0; j < 3; j++) {
                if (code[j] == guess[i] && code[j] != -1) {
                    misplaced++;
                    code[j] = -1;
                    break;
                }
            }
        }
    }

    wrong = 3 - right - misplaced;
}

int main() {
    vector<A> A1;
    string input;
    
    while (getline(cin, input)) {
        int wrong, right, misplaced, g0, g1, g2;
        if (sscanf(input.c_str(), "[%d %d %d] %d %d %d", &wrong, &right, &misplaced, &g0, &g1, &g2) == 6) {
            A guess;
            guess.right = right;
            guess.misplaced = misplaced;
            guess.wrong = wrong;
            guess.guess[0] = g0;
            guess.guess[1] = g1;
            guess.guess[2] = g2;
            A1.push_back(guess);
        }
    }

    for (int d0 = 0; d0 <= 9; d0++) {
        for (int d1 = 0; d1 <= 9; d1++) {
            for (int d2 = 0; d2 <= 9; d2++) {
                int code[3] = {d0, d1, d2};
                bool valid = true;

                for (const auto& guess : A1) {
                    int r, m, w;
                    score_candidate(code, guess.guess, r, m, w);
                    if (r != guess.right || m != guess.misplaced || w != guess.wrong) {
                        valid = false;
                        break;
                    }
                }

                if (valid) {
                    cout << "Possible solution: [" << d0 << " " << d1 << " " << d2 << "]" << endl;
                }
            }
        }
    }

    return 0;
}
