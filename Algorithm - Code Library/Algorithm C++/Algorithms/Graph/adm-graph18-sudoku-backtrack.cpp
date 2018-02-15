/*  suduku.c
 
    A backtracking program to solve Seduku
 
 */


#include<string>
#include<iostream>
    
using namespace std;

#define TRUE    1
#define FALSE   0
#define BASED      3                    /* base dimension, 3*3 blocks */
#define DIMENSION  BASED*BASED          /* 9*9 board */
#define NCELLS     DIMENSION*DIMENSION  /* 81 cells in a 9*9 problem */
#define MAXCANDIDATES   100     /* max possible next extensions */
#define NMAX            100     /* maximum solution size */


typedef struct {
    int x, y;                           /* x and y coordinates of point */
} point;

typedef struct {
    int m[DIMENSION+1][DIMENSION+1];    /* matrix of board contents */
    int freecount;                      /* how many open squares remain? */
    point move[NCELLS+1];
} boardtype;

bool finished;          /* solution found, stop search */

int steps;              /* how many total move insertions? */

bool fast;              /* fast or slow nextmove algorithm? */
bool smart;             /* quickly test for unfillable squares?*/

/**********************************************************************/

void possible_values(int x, int y, boardtype *board, bool possible[])
{
    int i,j;                /* counters */
    int xlow,ylow;          /* origin of box with (x,y) */
    bool init;              /* is anything/everthing possible? */
    
    if ((board->m[x][y] != 0) || ((x<0)||(y<0)))
        init = FALSE;
    else
        init = TRUE;
    
    for (i=1; i<=DIMENSION; i++) possible[i] = init;
    
    for (i=0; i<DIMENSION; i++)
        if (board->m[x][i] != 0) possible[ board->m[x][i] ] = FALSE;
    
    for (i=0; i<DIMENSION; i++)
        if (board->m[i][y] != 0) possible[ board->m[i][y] ] = FALSE;
    
    xlow = BASED * ((int) (x / BASED));
    ylow = BASED * ((int) (y / BASED));
    
    for (i=xlow; i<xlow+BASED; i++)
        for (j=ylow; j<ylow+BASED; j++)
            if (board->m[i][j] != 0) possible[ board->m[i][j] ] = FALSE;
}

void print_possible(bool possible[])
{
    int i;              /* counter */
    
    for (i=0; i<=DIMENSION; i++)
        if (possible[i] == TRUE) cout << " " << i;
    cout << endl;
}

int possible_count(int x, int y, boardtype *board)
{
    int i;              /* counter */
    int cnt;            /* number of open squares */
    bool possible[DIMENSION+1];     /* what is possible for the square */
    
    possible_values(x,y,board,possible);
    cnt = 0;
    for (i=0; i<=DIMENSION; i++)
        if (possible[i] == TRUE) cnt++;
    return(cnt);
}

void fill_square(int x, int y, int v, boardtype *board)
{
    if (board->m[x][y] == 0)
        board->freecount=board->freecount-1;
    else
        cout <<"Warning: filling already filled square (" << x << "," << y << ")" << endl;
    
    board->m[x][y] = v;
}

void free_square(int x, int y, boardtype *board)
{
    if (board->m[x][y] != 0)
        board->freecount=board->freecount+1;
    else
        cout <<"Warning: freeing already empty square (" << x << "," << y << ")" << endl;
    board->m[x][y] = 0;
}


void next_square(int *x, int *y, boardtype* board)
{
    int i,j;            /* counters */
    int bestcnt, newcnt;        /* the best and latest square counts */
    bool doomed;            /* some empty square without moves? */
    
    bestcnt = DIMENSION + 1;
    doomed = FALSE;
    
    *x = *y = -1;
    
    for (i=0; i<DIMENSION; i++) {
        for (j=0; j<DIMENSION; j++) {
            newcnt = possible_count(i,j,board);
            if ((newcnt==0) && (board->m[i][j]==0))
                doomed = TRUE;
            if (fast) {
                if ((newcnt < bestcnt) && (newcnt >= 1)) {
                    bestcnt = newcnt;
                    *x = i;
                    *y = j;
                }
            }
            if (!fast) {
                if ((newcnt >= 1) && (board->m[i][j] == 0)) {
                    *x = i;
                    *y = j;
                }
            }
        }
    }
    
    if (doomed && smart) {
        *x = *y = -1;       /* initialize to non-position */
    }
}


void print_board(boardtype *board)
{
    int i,j;            /* counters */
    
    cout << endl;
    cout << "There are "  << board->freecount << " free board positions " << endl;
    
    for (i=0; i<DIMENSION; i++) {
        for (j=0; j<DIMENSION; j++) {
            if (board->m[i][j] == 0)
                cout << " ";
            else
                printf("%c",(char) '0'+board->m[i][j]);
            if ((j+1)%BASED == 0)
                cout << "|";
        }
        cout << endl;
        if ((i+1)%BASED == 0) {
            for (j=0; j<(DIMENSION+BASED-1); j++)
                cout << "-";
            cout << endl;
        }
    }
}

void init_board(boardtype* board)
{
    int i,j;            /* counters */
    
    for (i=0; i<DIMENSION; i++)
        for (j=0; j<DIMENSION; j++)
            board->m[i][j] = 0;
    board->freecount = DIMENSION*DIMENSION;
}

void read_board(boardtype* board)
{
    int i,j;            /* counters */
    char c;
    int value;
    
    init_board(board);
    
    for (i=0; i<DIMENSION; i++) {
        for (j=0; j<DIMENSION; j++) {
            cin >> c;
            value = (int) (c - '0');
            if (value != 0)
                fill_square(i,j,value,board);
        }
        cout << endl;
    }
}

void copy_board(boardtype *a, boardtype *b)
{
    int i,j;
    
    b->freecount = a->freecount;
    
    for (i=0; i<DIMENSION; i++)
        for (j=0; j<DIMENSION; j++)
            b->m[i][j] = a->m[i][j];
}


/******************************************************************/

void process_solution(int a[], int k, boardtype *board)
{
    finished = TRUE;
    cout << "process solution\n";
    print_board(board);
}

bool is_a_solution(int a[], int k, boardtype *board)
{
    steps = steps+1;
    
    if (board->freecount == 0) {
        return (TRUE);
    }
    else
        return(FALSE);
    
}

void make_move(int a[], int k, boardtype *board)
{
    fill_square(board->move[k].x,board->move[k].y,a[k],board);
}


void unmake_move(int a[], int k, boardtype *board)
{
    free_square(board->move[k].x,board->move[k].y,board);
}

void construct_candidates(int a[], int k, boardtype *board, int c[], int *ncandidates)
{
    int x,y;            /* position of next move */
    int i;              /* counter */
    bool possible[DIMENSION+1];     /* what is possible for the square */
    
    next_square(&x,&y,board);   /* which square should we fill next? */
    
    board->move[k].x = x;       /* store our choice of next position */
    board->move[k].y = y;
    
    *ncandidates = 0;
    
    if ((x<0) && (y<0)) return; /* error condition, no moves possible */
    
    possible_values(x,y,board,possible);
    for (i=1; i<=DIMENSION; i++)
        if (possible[i] == TRUE) {
            c[*ncandidates] = i;
            *ncandidates = *ncandidates + 1;
        }
}


void backtrack(int a[], int k, boardtype* input)
{
    int c[MAXCANDIDATES];           /* candidates for next position */
    int ncandidates;                /* next position candidate count */
    int i;                          /* counter */
    
    if (is_a_solution(a,k,input))
        process_solution(a,k,input);
    else {
        k = k+1;
        construct_candidates(a,k,input,c,&ncandidates);
        for (i=0; i<ncandidates; i++) {
            a[k] = c[i];
            make_move(a,k,input);
            
            backtrack(a,k,input);
            if (finished) return;   /* terminate early */
            
            unmake_move(a,k,input);
        }
    }
}


int main()
{
    //int i,j;          /* counters */
    int a[DIMENSION*DIMENSION+1];
    boardtype board;        /* Seduko board structure */
    boardtype temp;
    
    read_board(&board);
    print_board(&board);
    copy_board(&board,&temp);
    
    
    //for (fast=TRUE; fast>=FALSE; fast--)
        //for (smart=TRUE; smart>=FALSE; smart--) {
            
            cout << "----------------------------------\n";
            steps = 0;
            copy_board(&temp,&board);
            finished = FALSE;
            
            backtrack(a,0,&board);
            print_board(&board);
            
            //cout <<"It took " << steps << " steps to find this solution;
            //cout <<"for fast = " << fast << " smart= " << smart << endl;
            
        //}
        //}

}