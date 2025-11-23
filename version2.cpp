#include <bits/stdc++.h>
using namespace std;

bool evalue(vector<int>& solution_possible , pair<vector<int>, vector<int>>& testpair) {
        vector<int> result_test=testpair.first;
        vector<int> test=testpair.second;
        vector<int> result_solution={0,0,0};
        
        // wrong=result_solution[0]
        
        // correct=result_solution[1]
        
        // correct_wrong_place=result_solution[2]
            
        for (int i=0 ; i<3 ; i++){
            for (int j = 0; j < 3; j++)
            {
                if (test[i]==solution_possible[j]){
                    if (i==j){
                        result_solution[1]++;
                    }else {result_solution[2]++;}
                }
            }
        }
        result_solution[0]=3-(result_solution[1]+result_solution[2]);
        if (result_solution == result_test) {return true;}
        else {return false;}
    }

int main() {
    // read a standar input and transform it to a victor of pairs
    int n;
    cin >> n;
    vector<pair<vector<int>, vector<int>>> input(n);

    for (int i = 0; i < n; i++) {
        vector<int> result(3), test(3);

        cin >> result[0] >> result[1] >> result[2];
        cin >> test[0]   >> test[1]   >> test[2];

        input[i] = { result, test };
    }
    

    cout << "Code possible:" << endl ;;
    for (int x = 0; x <= 999; x++) {
        vector<int> possibleSolution = {(x/100), (x/10)%10, x%10};
        // exp 954 --> {9,5,4}
        bool is_solution = true;
        for (int i=0 ; i<n ; i++){
            if (!evalue(possibleSolution,input[i])){  // possible solution ne verifie pas le i eme test
                is_solution=false;
                break;
            }
        }
    if (is_solution) {
        // possiblesolution passer tout les tests
        cout << possibleSolution[0] << possibleSolution[1] << possibleSolution[2] << endl;}
    }
}
