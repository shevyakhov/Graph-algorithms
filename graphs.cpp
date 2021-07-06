// graphs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
struct el { int s; struct el* p; };
int nv, Pv[20], P0[20], Rv[20], Smin = 1000000;
float Mv[20][20];
void init_1(int ** M , int size) {
    for (int i = 0;i < size;i++)
    {
        M[i] = new int[size];
        for (int j = 0;j < size;j++) M[i][j] = 0;
    }
}
void init_2(FILE *F,int ** M , int size, int howmuch) {
    int i, j;
  
    while (!feof(F)) {
        fscanf(F,"%d", &i);
        fscanf(F,"%d", &j);
        howmuch++;
    
        M[i-1][j-1] = 1; M[j-1][i-1] = 1;
    }
}
void paste2(FILE *F,int** M, int size ) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                fprintf(F, "%3d ", M[i][j]);
            }
            fprintf(F, "\n");
        }
        fprintf(F, "\n________\n");
}
void paste1(FILE* F, int* M, int size) {
        for (int j = 0; j < size; j++) {
            fprintf(F, "%3d ", M[j]);
        }
        fprintf(F, "\n________\n");
}
int smej(int** M, int* L, int* S, int* D, int size ) {
    int z = 0;
    S[0] = 0;
    int dsize = 0;
    int count;
    
    for (int i = 0; i < size; i++) {
        count = 0;
        for (int j = 0; j < size; j++) {
            if (M[i][j] == 1) {
                ++count;
           }
        }
        L[i] = count;
        dsize += count;
        S[i + 1] = dsize;
    }
    for (int  i= 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (M[i][j])
            {
                D[z] = j;
                z++;
            }
        }
    }
    return dsize;
}
void OutputList(FILE* F, struct el** S, int n)
{
    for (int i = 0; i < n; i++)
    {
        fprintf(F, "%d", i);
        while (S[i] != NULL)
        {
            fprintf(F, " -> %d", S[i]->s);
            S[i] = S[i]->p;
        }
        fprintf(F, "\n");
    }
}
void undoD(int** M, int* L, int* S, int* D, int size, int dsize) {
    
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < L[i]; j++)
        {
            M[i][D[j + S[i]]] = 1; 
        }
    }
}
void deåpList(int k, int q, struct el** S, int* C)
{
    int j;
        while (S[k] != NULL)
        {
            j = S[k]->s;
            if (C[j] == 0) {
                C[j] = q;
                deåpList(j, q, S, C);
            }
            S[k] = S[k]->p;
        }
}
void cohesionList(struct el** S, int* C, int size) {
    for (int i = 0;i < size;i++) C[i] = 0;
    int  q = 0;
    for (int i = 0;i < size;i++)
        if (C[i] == 0)
        {
            q++; C[i] = q;
            deåpList(i, q,S ,C);
        }
}
void cdeåp(int k,int q, int *L, int *S, int *D, int *C)
{
    int i, j;
    for (i = S[k];i <= S[k] + L[k] - 1;i++)
    {
        j = D[i];
        if (C[j] == 0) { C[j] = q; cdeåp(j,q,L,S,D,C); }
    }
}
void cohesionComp(int* L, int* S, int* D, int* C,int size) {
    for (int i = 0;i < size;i++) C[i] = 0;
   int  q = 0;
    for (int i = 0;i < size;i++)
        if (C[i] == 0)
        {
            q++; C[i] = q;
            cdeåp(i, q, L, S, D, C);
        }
}
void solveMaze(FILE *F,int i0, int j0,int ik,int jk, int **L) {
    int Pi[401], Pj[401], r, t, i,q, j;
    Pi[1] = i0; Pj[1] = j0; r = 1; t = 1;
    L[i0][j0] = 1;
    
    while (t <= r)
    {
        
        i = Pi[t]; j = Pj[t]; q = L[i][j] + 1;
        if (L[i - 1][j] == 0)
        {
            L[i - 1][j] = q; r++; Pi[r] = i - 1; Pj[r] = j;
        }
        if (L[i][j - 1] == 0)
        {
           
            L[i][j - 1] = q; r++; Pi[r] = i; Pj[r] = j - 1;
        }
        if (L[i + 1][j] == 0)
        {
            L[i + 1][j] = q; r++; Pi[r] = i + 1; Pj[r] = j;
        }
        if (L[i][j + 1] == 0)
        {
            L[i][j + 1] = q; r++; Pi[r] = i; Pj[r] = j + 1;
        }
        t++;
    }
    int Mi[401], Mj[401], k;
    k = L[ik][jk]; i = ik; j = jk;
   
    
    while (k > 0)
    {
        Mi[k] = i; Mj[k] = j;
        if ((L[i - 1][j] < L[i][j])&&(L[i - 1][j]!=-1)) {
            fprintf(F, "%d %d\n", i, j);
            i--; }
        else if ((L[i][j - 1] < L[i][j]) && (L[i][j - 1] != -1)) {
            fprintf(F, "%d %d\n", i, j);
            j--; }
        else if ((L[i + 1][j] < L[i][j]) && (L[i + 1][j] != -1)) {
            fprintf(F, "%d %d\n", i, j);
            i++; }
        else if ((L[i][j + 1] < L[i][j]) && (L[i][j + 1] != -1)) {
            fprintf(F, "%d %d\n", i, j);
            j++; }
            k--;
    }
    
    if ((i != i0) || (j != j0)) {
        fprintf(F, "no path\n");
    }else
    fprintf(F, "%d %d\n", i, j);
}
void redoMaze(int** maze, int size) {
    for (int i = 0; i < size; i++)
    {
        maze[0][i] = -1;
        maze[i][0] = -1;
        maze[i][size-1] = -1;
        maze[size-1][i] = -1;
    }
}
void readMaze(FILE *F, int**L, int size,int *indices) {
    char c;
    for (int i = 1; i < size-1; i++)
        for (int j = 1; j < size-1; j++) {
            {
                fscanf(F, "%c", &c);
                if (c == '\n') {
                    fscanf(F, "%c", &c);
                }
              
                switch (c)
                {
                case '#':
                    L[i][j] = -1;
                    break;
                case '-':
                    L[i][j] = 0;
                    break;
                case 'f':
                    indices[2] = i;
                    indices[3] = j;
                   
                    break;
                case 's':
                    indices[0] = i;
                    indices[1] = j;
                    
                    break;
                
                }
            }
        }
}
bool checkEiler(int* L, int* D, int* R,  int n, int m) {
    for (int i = 0;i < n;i++) R[i] = 0;
    for (int j = 0;j < m;j++) R[D[j]]++;
    int i = 0;
    while ((i < n) && (L[i] == R[i])) i++;
    if (i == n) {
        return true;
    }
    else { return false; }

}
void hamilton(int k, int* P, int* R, int** M, int n)
{
    int i, j;
    i = P[k - 1];
    for (j = 0;j < n;j++)
        if ((R[j] == 0) && (M[i][j]))
        {
            P[k] = j; R[j] = 1;
            if (k == n - 1)
            {
                if (M[j][0]) {
                    cout << "hamilton cycle: " << endl;
                    for (int i = 0; i < n; i++)
                    {
                        cout << P[i] << " ";

                    }
                    cout << P[0] << " "<<endl;
                }
            }
            else hamilton(k + 1, P, R, M, n);
            R[j] = 0;
        }
}
void hamiltonsp(int k, int* P, int *R,int* L, int* S, int* D,int n) 
{
    int i, j, q, r;
    i = P[k - 1];
   
    for (j = S[i]; j < S[i] + L[i]; j++)
    {
        q = D[j];
       
        if (R[q] == 0)
        {
            P[k] = q; R[q] = 1;
            if (k == n - 1) {
                cout << "hamilton path:" << endl;
                for (int i = 0; i < n; i++)
                {
                    cout << P[i]<< " ";
                }
                cout << endl;
            }
            
            else hamiltonsp(k + 1,P,R,L,S,D,n);
            R[q] = 0;
        }
    }
}
void TSP(int k, float S)
{
    int i, j, q; float mij;
    i = Pv[k - 1];
    for (j = 0;j < nv;j++)
        if ((Rv[j] == 0) && ((mij = Mv[i][j] + S) < Smin)&&(Mv[i][j] != -1))
        {
            Pv[k] = j; Rv[j] = 1;
            if (k == nv - 1)
            {
                if (mij + Mv[j][0] < Smin)
                {
                    Smin = mij + Mv[j][0];
                    for (q = 0;q < nv;q++) P0[q] = Pv[q];
                }
            }
            else TSP(k + 1, mij);
            Rv[j] = 0;
        }
}
void init_TSP(FILE *F) {
    int size,num;
    fscanf(F, "%d", &size);
    nv = size;
    for (int i = 0; i < nv; i++) {
        for (int j = 0; j < nv; j++) {
            fscanf(F, "%d", &num);
            Mv[i][j] = num;
        }
    }
}
int main() 
{
    FILE* F1 = fopen("input.txt", "r");
    FILE* F3 = fopen("input.txt", "r");
    FILE* F2 = fopen("output.txt", "w");
    int** M, ** M1, n,m=0, * L, * S,*C,* Clist, * D,i,j;
    fscanf(F1, "%d", &n);
    M = new int* [n];
    M1 = new int* [n];
    L = new int [n];
    S = new int [n];
    C = new int [n];
    Clist = new int [n];
    D = new int [n*n];
    init_1(M, n);
    init_1(M1, n);
    init_2(F1, M, n,m);
    paste2(F2, M,n);
    int dsize =smej(M, L, S, D, n);
    paste1(F2, L, n);
    paste1(F2, S, n);
    paste1(F2, D, dsize);
    undoD(M1, L, S, D, n, dsize);
    paste2(F2, M1, n);
    //1 task done
    //task 2
    cohesionComp(L, S, D, C, n);
    paste1(F2, C, n);
    //2a done
    el** Spis,** Spaste, * ps;
    Spis = new struct el*[n];
    Spaste = new struct el*[n];
    for (i = 0; i < n; i++)
        Spis[i] = NULL; //Èíèöèàëèçàöèÿ
    fscanf(F3, "%d", &i);
    while (!feof(F3)) /*ôîðìèðîâàíèå ñïèñêîâ*/
    {
        ps = new struct el;
        fscanf(F3, "%d%d", &i, &j);
        i--; j--;
        ps->s = j;
        ps->p = Spis[i];
        Spis[i] = ps;
        //Ñèììåòðè÷íàÿ âåðøèíà, ò.ê. ãðàô íå îðèåíòèðîâàí
        ps = new struct el;
        ps->s = i;
        ps->p = Spis[j];
        Spis[j] = ps;
    }
    for (int i = 0; i < n; i++)
    {
        Spaste[i] = Spis[i];
    }
    OutputList(F2, Spaste, n);
    cohesionList(Spis, Clist, n);
    paste1(F2, Clist, n);
    //task 2 done
    //task 3
    FILE* FM = fopen("maze.txt", "r");
    int **maze,i0 = 0,j0 = 0,ie = 0,je = 0,mazeSize = 0;
    int indices[4];
    fscanf(FM, "%d", &mazeSize);
    mazeSize += 2;
    maze = new int* [mazeSize];
    init_1(maze, mazeSize);
    readMaze(FM, maze,mazeSize,indices);
    redoMaze(maze, mazeSize);
    paste2(F2, maze, mazeSize);
    paste1(F2, indices, 4);
    solveMaze(F2,indices[0], indices[1], indices[2], indices[3], maze);
    paste2(F2, maze, mazeSize);
    //task 3 done
    //task 4
    int* R, * P;
    R = new int[n];
    P = new int[n];
   
    for (i = 0;i < n;i++) R[i] = 0;
    P[0] = 0; R[0] = 1;
    hamilton(1, P, R, M, n);    
    for (i = 0;i < n;i++) R[i] = 0;
    
    for (i = 0;i < n;i++)
    {
        P[0] = i; R[i] = 1; hamiltonsp(1, P, R, L, S, D, n); R[i] = 0;
    }
    //task 4 done
    //task five
    FILE* FTSP = fopen("TSP.txt", "r");
    init_TSP(FTSP);
    for (i = 1;i < nv;i++) Rv[i] = 0;
    Rv[0] = 1; Pv[0] = 0;
    TSP(1, 0);
    cout << "!" << Smin << endl;
    for (i = 0;i < nv;i++)
        printf("%d ", P0[i]);
        printf("%d ", P0[0]);
    printf("\n");
    
    fclose(F1);
    fclose(F2);
    fclose(F3);
    fclose(FM);
    fclose(FTSP);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
