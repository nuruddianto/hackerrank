// TSP with Simulated Annealing Techique.
// This is advance technique.
// Heuristics for solving TSP


#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cmath>

using namespace std;


#define TRUE    1
#define FALSE   0

#define TRACE_OUTPUT    FALSE           /* print the swaps as they happen */
#define PRINT_FREQUENCY 10000             /* how often we report progress */

/**************** Simulated Annealing Constants **************************/

#define REPEAT_COUNT        1   
#define INITIAL_TEMPERATURE 1
#define COOLING_STEPS       500     /* how many times do we cool -- */
#define COOLING_FRACTION    0.97    /* how much to cool each time -- */
#define STEPS_PER_TEMP      1000    /* lower makes it faster, higher makes it potentially better. */
#define E           2.718           /* number e -- probably leave intact*/
#define K           0.01            /* problem specific Boltzman's constant */
#define ERROR       "ERROR"         /* string denoting error id */
#define ERROR_VALUE 0.0             /* float denoting error value */

/*************************** TSP Constants *******************************/

#define NMAX    1000                /* maximum number of points */

typedef struct {
    int x, y;                       /* x and y coordinates of point */
} point;

typedef struct {
    int n;                          /* how many points in problem? */
    point p[NMAX+1];                /* array of points */
} tsp_instance;

typedef struct {
    int n;                          /* how many elements in permutation? */
    int p[NMAX+1];                  /* array if indices */
} tsp_solution;


int solution_count;                 /* how many solutions evaluated */


int random_int(int low,int high){
    int i,j,r;
    i = RAND_MAX / (high-low+1);
    i *= (high-low+1);
    while ((j = rand()) >=i) continue;
    r = (j % (high-low+1)) + low;
    cout << "rand= " << r << " RAND_MAX=" << RAND_MAX << endl;
    if ((r < low) || (r > high))
        cout << "Error: random integer " << r << " out of range [" << low << "," << high << "]" << endl;
        return(r);
}

/*      Construct a random permutation of the $n$ elements of the given array. */

void swapint(int *a,int *b){
    int x;
    x = *a;
    *a = *b;
    *b = x;
}


double random_float(int low,int high)
{
    double i,j;                             /* avoid arithmetic trouble */
    double r;                                  /*random number*/
    i = RAND_MAX / (high-low);
    i *= (high-low);
    while ((j = rand()) >=i) continue;
    r = (j/i) * (high-low) + low;
    
    if ((r < low) || (r > high))
        cout << "Error: random real " << r << " out of range [" << low << "," << high << "]" << endl;
        return(r);
}



void random_permutation(int a[], int n){
    int i;
    for (i=n; i>1; i--) swapint(&a[i-1],&a[random_int(0,i-1)]);
}

void read_tsp(tsp_instance *t)
{
    int i,j;            /* counters */
    cin >> t->n;
    for (i=1; i<=(t->n); i++)
        cin >> j >> t->p[i].x >> t->p[i].y;
}

void print_tsp(tsp_instance *t)
{
    int i;              /* counter */
    for (i=1; i<=(t->n); i++)
        cout << i << " " << t->p[i].x << " " << t->p[i].y << endl;
}

int sq(int x)
{
    return(x*x);
}

double distance(tsp_solution *s, int x, int y, tsp_instance *t)
{
    int i, j;
    
    i = x;
    j = y;
    
    if (i==((t->n)+1)) i=1;
    if (j==((t->n)+1)) j=1;
    
    if (i==0) i=(t->n);
    if (j==0) j=(t->n);
    
    return ( sqrt( (double) (sq(t->p[(s->p[i])].x - t->p[(s->p[j])].x) +
                             sq(t->p[(s->p[i])].y - t->p[(s->p[j])].y) ) ) );
}


double solution_cost(tsp_solution *s, tsp_instance *t)
{
    int i;              /* counter */
    double cost;            /* cost of solution */
    cost = distance(s,t->n,1,t);
    for (i=1; i<(t->n); i++)
        cost = cost + distance(s,i,i+1,t);
    
    return(cost);
}

void initialize_solution(int n, tsp_solution *s){
    int i;              /* counter */
    
    s->n = n;
    for (i=1; i<=n; i++)
        s->p[i] = i;
}

void copy_solution(tsp_solution *s, tsp_solution *t){
    int i;              /* counter */
    t->n = s->n;
    for (i=1; i<=(s->n); i++)
        t->p[i] = s->p[i];
}


void print_solution(tsp_solution *s){
    for (int i=1; i<=(s->n); i++) cout << " " << s->p[i];
    cout << "\n------------------------------------------------------\n";
}

void read_solution(tsp_solution *s){
    int i;              /* counter */
    cin >> s->n;
    cout << endl;
    for (i=1; i<=(s->n); i++)
        cin >> s->p[i];
}

void random_solution(tsp_solution *s)
{
    random_permutation(&(s->p[1]),(s->n)-1);
}

double transition(tsp_solution *s, tsp_instance *t, int i, int j)
{
    double was, willbe;     /* before and after costs */
    bool neighbors;         /* i,j neighboring tour positions? */
    neighbors = FALSE;
    
    if (i == j) {
        /*printf("Warning: null transition i=%d j=%d\n",i,j);*/
        return(0.0);
    }
    
    if (i > j) return( transition(s,t,j,i) );
    
    if (i==(j-1)) neighbors = TRUE;
    
    if ((i==1) && (j==(s->n))) {
        swapint(&i,&j);
        neighbors = TRUE;
    }
    
    if (neighbors) {
        was = distance(s,i-1,i,t) + distance(s,j,j+1,t);
    } else {
        was = distance(s,i-1,i,t) + distance(s,i,i+1,t)
        + distance(s,j-1,j,t) + distance(s,j,j+1,t);
    }
    
    swapint(&(s->p[i]),&(s->p[j]));
    
    if (neighbors) {
        willbe = distance(s,i-1,i,t) + distance(s,j,j+1,t);
    } else {
        willbe = distance(s,i-1,i,t) + distance(s,i,i+1,t)
        + distance(s,j-1,j,t) + distance(s,j,j+1,t);
    }
    
    return(willbe - was);
}

/**********************************************************************/

void solution_count_update(tsp_solution *s, tsp_instance *t){
    solution_count = solution_count+1;
    if ((solution_count % PRINT_FREQUENCY) == 0) printf("%d %7.1f\n",solution_count,solution_cost(s,t));
}


void anneal(tsp_instance *t, tsp_solution *s)
{
    int i1, i2;                 /* pair of items to swap */
    int i,j;                    /* counters */
    double temperature;         /* the current system temp */
    double current_value;       /* value of current state */
    double start_value;         /* value at start of loop */
    double delta;               /* value after swap */
    double merit, flip;         /* hold swap accept conditions*/
    double exponent;            /* exponent for energy funct*/
    
    temperature = INITIAL_TEMPERATURE;
    
    initialize_solution(t->n,s);
    current_value = solution_cost(s,t);
    
    for (i=1; i<=COOLING_STEPS; i++) {
        temperature *= COOLING_FRACTION;
        
        start_value = current_value;
        
        for (j=1; j<=STEPS_PER_TEMP; j++) {
            
            /* pick indices of elements to swap */
            i1 = random_int(1,t->n);
            i2 = random_int(1,t->n);
            
            delta = transition(s,t,i1,i2);
            
            flip = random_float(0,1);
            exponent = (-delta/current_value)/(K*temperature);
            merit = pow(E,exponent);
            /*printf("merit = %f  flip=%f  exponent=%f\n",merit,flip,exponent); */
            /*if (merit >= 1.0)
             merit = 0.0;*/ /* don't do unchanging swaps*/
            
            if (delta < 0) {    /*ACCEPT-WIN*/
                current_value = current_value+delta;
                
                if (TRACE_OUTPUT) {
                    printf("swap WIN %d--%d value %f  temp=%f i=%d j=%d\n",
                           i1,i2,current_value,temperature,i,j);
                }
            } else { if (merit > flip) {        /*ACCEPT-LOSS*/
                current_value = current_value+delta;
                if (TRACE_OUTPUT) {
                    printf("swap LOSS %d--%d value %f merit=%f flip=%f i=%d j=%d\n",
                           i1,i2,current_value,merit,flip,i,j);
                }
            } else {                /* REJECT */
                transition(s,t,i1,i2);
            } }
            solution_count_update(s,t);
        }
        if ((current_value-start_value) < 0.0){ /* rerun at this temp */
            temperature /= COOLING_FRACTION;
            if (TRACE_OUTPUT) printf("rerun at temperature %f\n",temperature);
        }
    }
}


void repeated_annealing(tsp_instance *t, int nsamples, tsp_solution *bestsol)
{
    tsp_solution s;                 /* current tsp solution */
    double best_cost;               /* best cost so far */
    double cost_now;                /* current cost */
    int i;                          /* counter */
    
    initialize_solution(t->n,&s);
    best_cost = solution_cost(&s,t);
    copy_solution(&s,bestsol);
    
    for (i=1; i<=nsamples; i++) {
        anneal(t,&s);
        cost_now = solution_cost(&s,t);
        if (cost_now < best_cost) {
            best_cost = cost_now;
            copy_solution(&s,bestsol);
        }
    }
}



int main()
{
    tsp_instance t;         /* tsp points */
    tsp_solution s;         /* tsp solution */
    read_tsp(&t);
    print_tsp(&t);
    
    read_solution(&s);
    printf("OPTIMAL SOLUTION COST = %7.1f\n",solution_cost(&s,&t));
    print_solution(&s);
    
    
    initialize_solution(t.n, &s);
    printf("solution_cost = %7.1f\n",solution_cost(&s,&t));
    print_solution(&s);
    
    
    /*
     solution_count=0;
     random_sampling(&t,1500000,&s);
     printf("random sampling %d iterations, cost = %7.1f\n",
     solution_count,solution_cost(&s,&t));
     print_solution(&s);
     
     solution_count=0;
     repeated_hill_climbing(&t,195,&s);
     printf("repeated hill climbing %d iterations, cost = %7.1f\n",
     solution_count,solution_cost(&s,&t));
     print_solution(&s);
     */
    
    solution_count=0;
    repeated_annealing(&t,3,&s);
    printf("repeated annealing %d iterations, cost = %7.1f\n", solution_count,solution_cost(&s,&t));
    print_solution(&s);
   
}