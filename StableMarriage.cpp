/*
  Question:
    https://venus.cs.qc.cuny.edu/~waxman/211/stable%20marriage%20using%20backtrack%20assignment.pdf
  References:
    https://repl.it/@CerverizzoE/StableMarriage-iterative-for-StudentUse
*/
#include <iostream>
using namespace std;

void printMatching(int q[]){
    static int sol = 0; 
    sol++;
    cout << "Solution #: " << sol << endl;
    for(int i = 0; i<3; i++){
        cout << "male: " << i << " female: " << q[i] << endl;
    }
    cout << endl;
}
  
bool ok(int q[], int col){  

    //mp = man's preference; wp = women's preference
    
    //mp[i][j] gives man i's ranking of woman j
    
    //lower value implies higher ranking
    int mp[3][3] = {{0,2,1},    //man 0 likes woman 0 the most and woman 1 the least.
                    {0,2,1},    //man 1
                    {1,2,0}};   //man 2

    int wp[3][3] = {{2,1,0},    //woman 0
                    {0,1,2},    //woman 1
                    {2,0,1}};   //woman 2

    //cm = a currently assigned man
    //cw = a currently assigned woman
    //nm = new man
    //nw = new woman
    //nm and nw are the proposed pair to add to the match

    int cm, cw, nm, nw;

    nm = col;
    nw = q[col];

    for (int i = 0; i < col; i++){
        //to check if the woman has already been married (row test)
        if(q[i]==q[col]) return false;
    }
    
    for (cm = 0; cm <2; cm++) {
    /*
       Check the new pair (new man, new woman) against each existing pair consisting of
       (current man, current woman) to see if the new pair would make the match unstable.
    */
        cw = q[cm];
        //Lower value implies a higher preference

        //   a. if the current man prefers the new woman to his partner and
        //   b. if the new woman prefers the current man to her partner, reject
        if(mp[cm][nw] < mp[cm][cw]  && wp[nw][cm] < wp[nw][nm]) return false;

        //   c. if the new man prefers the current woman to his partner and
        //   d. if the current woman prefers the new man to her partner, reject
        if(mp[nm][cw] < mp[nm][nw] && wp[cw][nm] < wp[cw][cm]) return false;
    }

    return true; //since the pair nm & nw do not introduce an instability
}

int main() {

    //Start with the first male
    int newMan = 0;
    int q[3] = {0};
    // While we have not backtracked beyond the first male:
    while (newMan>=0){

        // If all the people have been matched, 
        if(newMan==3){
            printMatching(q);// print 
            // backtrack
            newMan--;
            q[newMan]++;
        }
        // If all the available women are matched already
        else if (q[newMan]==3){
            q[newMan] = 0;//reset new woman to starting value
            //backtrack
            newMan--;
            if (newMan == -1){
                return 0;
            }
            q[newMan]++;
        }
        //check if the q is stable
        else if(ok(q, newMan)){
            newMan++;// move to the next man
        }
        else{
            // pair the man with the next available woman
            q[newMan]++;
        }
    }
    return 0;
}

