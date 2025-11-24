#include <iostream>
#include <vector>
#include <cctype>

// Each attempt made by the player
struct Attempt {
    int guess[3];     // the guessed code
    int wrong;        // totally wrong numbers
    int right;        // correct number in correct place
    int misplaced;    // correct number in wrong place
};

// calculate how a candidate code scores against a guess
void score_candidate(const int code[3], const int guess[3], int &right, int &misplaced, int &wrong) {
    int usedC[3] = {0}, usedG[3] = {0};
    right = misplaced = 0;

    // count greens (right number, right place)
    for(int i = 0; i < 3; i++) {
        if(code[i] == guess[i]) {
            right++;
            usedC[i] = usedG[i] = 1;
        }
    }

    // count blues (right number, wrong place)
    for(int i = 0; i < 3; i++) {
        if(!usedG[i]) {
            for(int j = 0; j < 3; j++) {
                if(!usedC[j] && guess[i] == code[j]) {
                    misplaced++;
                    usedC[j] = 1;
                    usedG[i] = 1;
                    break;
                }
            }
        }
    }

    wrong = 3 - right - misplaced;
}

// read the next integer from input, skipping any non-digits
int next_int() {
    char c;

    // skip non-digits
    do {
        c = std::cin.get();
    } while(!isdigit(c));

    int value = 0;
    while(isdigit(c)) {
        value = value * 10 + (c - '0');
        c = std::cin.get();
    }

    return value;
}

int main() {
    std::cout << "your input:\n";

    std::vector<Attempt> attempts;
    char ch;

    // read all attempts until we hit '}'
    while(std::cin.get(ch) && ch != '}') {
        if(ch == '[') {
            Attempt a;

            // read counts: wrong / right / misplaced
            a.wrong     = next_int();  // totally wrong
            a.right     = next_int();  // right number in right place
            a.misplaced = next_int();  // right number, wrong place

            // skip until next '[' or '}' to get to the guess
            while(std::cin.get(ch) && ch != '[' && ch != '}');
            if(ch == '}') break;

            // read the actual guess
            a.guess[0] = next_int();
            a.guess[1] = next_int();
            a.guess[2] = next_int();

            attempts.push_back(a);
        }
    }

    // try all possible 3-digit codes (0-9)
    for(int d0 = 0; d0 <= 9; d0++) {
        for(int d1 = 0; d1 <= 9; d1++) {
            for(int d2 = 0; d2 <= 9; d2++) {
                int code[3] = {d0, d1, d2};
                bool valid = true;

                // check this code against all previous attempts
                for(const auto &a : attempts) {
                    int r, m, w;
                    score_candidate(code, a.guess, r, m, w);

                    if(r != a.right || m != a.misplaced || w != a.wrong) {
                        valid = false;
                        break;  // no need to check further
                    }
                }

                // if it fits all attempts, it's a possible answer
                if(valid) {
                    std::cout << "Answer is: [" << d0 << " " << d1 << " " << d2 << "]\n";
                }
            }
        }
    }

    return 0;
}
