#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BF 4			/* Branching factor of the search tree */
#define N 4
#define NxN 16
#define DFS 1                   /* depth first search */
#define BFS 2                   /* breadth first search */
#define BEST 3                  /* best first search */
#define BB 4                    /* branch and bound */
#define ASTAR 5                 /* A* search */
#define UNKNOWN 9		/* unknown search strategy */

#define MAX_PATH 1000

#define DN 0			/* for finding path */
#define RT 1
#define UP 2
#define LT 3
#define UK 9

#define FVAL 0			/* f=g+h, keep it simple for now */
#define GVAL 1
#define HVAL 2
#define PATH 3			/* array index, how it got to this state */

#define TRUE 1
#define FALSE 0

int level,strategy;

int nodes_same(),str_compare(),count(),find_h();
void swap(),exit_proc(),print_a_node(),print_nodes();
int toggle_dir(), solvable();
void find_path(),print_path(),find_parent();
int path[MAX_PATH],path_buf[MAX_PATH];
void prep_dir_to_str(),dir_to_str();
char *dir_to_sdir[4],strategy_s[10]; /* four directions */

struct node {
  int board[N+1][N];
  struct node *next;
  struct node *prev;
  int f,g,h;
  int direction;
};

struct node *start,*goal;
struct node *initialize(),*expand(),*merge(),*filter(),*move(),*prepend(),*append();
struct node *insert_node(),*check_list(),*goal_found();

int main(int argc,char **argv) {
  int iter,cnt=0,total=1,ocnt=0,ccnt=0;
  int perm;		/* perm=odd=no solution, perm=even=solvable */
  struct node *cp,*open,*closed,*succ,*tp;
  
  open=closed=succ=NULL;
  start=initialize(argc,argv);	/* init initial and goal states */
  perm=solvable(start);		/* check if solvable permutation */
  if (perm & 1) return 1;

  open=start; 
  iter=0;

  while (open) {
    printf("%d: open=%d + clsd=%d = total=%d\n",iter,ocnt,ccnt,ocnt+ccnt);
    ocnt=count(open);
    ccnt=count(closed);
    cp=open; open=open->next; cp->next=NULL; /* get the first node from open */
    succ = expand(cp);			     /* Find new successors */
    succ = filter(succ,open);		     /* New succ list */
    succ = filter(succ,closed);		     /* New succ list */
    cnt=count(succ);
    total=total+cnt;
    if (succ) open=merge(succ,open,strategy); /* New open list */
    closed=append(cp,closed);		      /* New closed */
    if ((cp=goal_found(succ,goal))) break;
    iter++;
  }
  printf("%s strategy: %d iterations %d nodes\n",strategy_s,iter+1,total);
  find_path(cp,open,closed);

  return 0;
} /* end of main */

int toggle_dir(int dir){
  int opp_dir;
  // return opp direction
  return opp_dir;
}

void print_path(int n,int *path){
  int i,p;
  //  for (i=0;i<n;i++) path[i] = path_buf[path_cnt-i-1];
  //  for (i=0;i<path_cnt;i++) printf("%d ",path[i]); printf("\n");
  //  printf("entering print_path: n=%d\n",n);

  ////  for (i=n-1;i>=0;i--) printf("%d ",*(path+i)); printf("\n");
  for (i=n-1;i>=0;i--) {
    p = *(path+i);
    if (i>0) printf("%s -> ",dir_to_sdir[p]);
    else printf("%s",dir_to_sdir[p]);    
  }
  printf("\n");
  //  printf("exiting print_path\n");
}

//char **dir_to_sdir={"DN","RT","UP","LT"}; //[4];
void prep_dir_to_str(){
}

void find_path(struct node *cp,struct node *opnp,struct node *cldp){
  int i,j,dir,opp_dir;
  char *sdir,*opp_sdir;
  int path_cnt=0,p;
  struct node *tp;
  //start from the very last node that matches the goal state because
  //that has the direction info
  //toggle the direction, get the parent
  //look for that parent in closed
  //repeat until you find the initial state
}

void find_parent(struct node *cp,int prev_dir){
  int i,j,k,cnt,row=0,col=j;
}

// Expand: generate successors of the current node
struct node *expand(struct node *cp) {
  int i,j,k,cnt,row=0,col=j;
  struct node *succ,*tp;
  succ=NULL;
  for(i=0; i < N; i++){
    for(j=0; j < N; j++)
      if (cp->board[i][j]==0) break;
    if (j<N) break;		
  }
  if((i+1) < N){		
    tp = move(cp,i,j,i+1,j,DN);
    succ = append(tp,succ);
  }
  if((j+1) < N){		
    tp = move(cp,i,j,i,j+1,RT);
    succ = append(tp,succ);
  }
  if((i-1) < N){	
    tp = move(cp,i,j,i-1,j,UP);
    succ = append(tp,succ);
  }
  if((j-1) < N){	
    tp = move(cp,i,j,i,j-1,LT);
    succ = append(tp,succ);
  }
  return succ;
}

struct node *prepend(struct node *tp,struct node *sp) {
  sp = append(sp,tp);
  return sp;
}
struct node *append(struct node *tp,struct node *sp) {
	struct node *cp;
	if (!sp)
		return tp;
	if (!tp)
		return sp;
	while (sp->next)
		sp = sp->next;
	sp->next = tp;
	tp->prev = sp;
	cp = tp;
	while(cp->next)
		cp = cp->next;
	cp->next=NULL;
	tp->next=NULL;
	return sp;
}
void swap(struct node *cp,int i,int j,int k,int l){
    int tmp;
    //tmp = cp->board[i][j];
    //cp->board[i][j] = cp->board[k][l];
    //cp->board[k][l]=tmp;
}

struct node *move(struct node *cp,int a,int b,int x,int y,int dir) {
    struct node *newp;
    int i,j,k,l,tmp,count=0,t=1;
    newp=(struct node *) malloc(sizeof(struct node));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            newp->board[i][j] = cp->board[i][j];
    newp->prev = NULL;
	newp->next = NULL;
    tmp = cp->board[i][j];
    cp->board[i][j] = cp->board[k][l];
    cp->board[k][l]=tmp;
	for (int e = 0; e < N; ++e)
		for (int r = 0; r < N; ++r)
			if (newp->board[e][r] != t++)
				count++;
	
    newp->h=count;
	newp->g++;
	newp->f=newp->g + newp->h;
	newp->direction=dir;
	return newp;
}

struct node *goal_found(struct node *cp,struct node *gp){
    int flg=FALSE;
    while (cp){
        if(!(memcmp(cp->board, gp->board, sizeof(cp->board)))){
            cp->next=NULL;
            return cp;
            }
        cp=cp->next;
	}
}

int count(struct node *cp) {
    int cnt=0;
    struct node *temp = cp;
    while (temp){
        cnt++;
        temp = temp->next;
	}
    return cnt;
}

struct node *merge(struct node *succ,struct node *open,int flg) {
    struct node *csucc,*copen;
    if (flg==DFS) {
        int scount = count(succ); 
        open=append(succ,open);
    }else if (flg==BFS) {	  
        open=append(succ,open);
    }else if (flg==BEST) {	
    }else{	
    }
    return open;
}

struct node *insert_node(struct node *succ,struct node *open,int x) {
    int cnt;
    struct node *copen,*topen;
    return open;
}

int find_h(int current[N+1][N],int goalp[N+1][N]) {
    int h=0,i,j,k,l,done;
    return h;
}
int nodes_same(struct node *xp,struct node *yp) {
    int i,j,flg=FALSE;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(xp->board[i][j]!=yp->board[i][j])return flg;}
            }
    flg=TRUE;
    return flg;
}
struct node *filter(struct node *succ,struct node *hp){ 
   struct node *lsp,*rsp;	/* lsp=left succ p, rsp=right succ p */
   struct node *tp, *prev;		
   int flg=0;
    tp=succ;
    while(tp){
        while(hp){
            if(!(memcmp(tp->board, hp->board, sizeof(tp->board)))){
                if(!(tp->prev)){
                    if (!(tp->next)){
                        free(tp);
                        break;}
                    rsp=tp->next;
		   			free(tp);
		   			succ=tp=rsp;
		   			break;
		   		}
		   		if (!(tp->next)){
		   			tp->prev->next = NULL;
		   			free(tp);
		   			break;
		   		}
                if (tp->prev && tp->next){
                    tp->prev->next = tp->next;
                    tp->next->prev = tp->prev;
                    rsp = tp->next;
			   		free(tp);
			   		tp=rsp;
			   		break;}
		   }
           flg++;
           hp=hp->next;
           }
           if (tp) tp=tp->next;
	}
   return succ;
}

void print_nodes(struct node *cp,char name[20]) {
  int i;
  printf("%s:\n",name);
  while (cp) { print_a_node(cp); cp=cp->next; }
}

void print_a_node(struct node *np) {
  int i,j;
  for (i=0;i<N+1;i++) {
    for (j=0;j<N;j++) printf("%2d ",np->board[i][j]);
    printf("\n");
  }
  printf("\n");
}

//cnt=odd -> no solution, cnt=even=solvable
int solvable(struct node *cp) {
    int i,j,k=0,lst[NxN],cnt=0,total=0;
    for (i=0; i<N; ++i){
        for (int j = 0; j < N; ++j){
            if (cp->board[i][j] == 0){ 
                total = i;
                continue;
            }
            lst[k++]=cp->board[i][j];
        }
    }
    for (int i = 0; i < NxN-1; ++i)
        for (int j = i; j < NxN-1; ++j)
            if (lst[i] > lst[j])
                cnt++;
    if ( ((cnt & 1)) && (!(total &1))  ){
        printf("%s\n", "Puzzle is solveable");
        return 1;
    }
    if ( (!(cnt & 1)) && (total &1)  ){
        printf("%s\n", "Puzzle is solveable");
        return 1;
    }
    printf("%s\n", "Puzzle is not solveable");
    return 0;
}

/* fif 0 1 2 4 5 6 3 8 9 10 7 12 13 14 11 15 astar */
struct node *initialize(int argc, char **argv){
    int i,j,k,npe,n,idx,gidx,inv;
    struct node *tp;
    tp=(struct node *) malloc(sizeof(struct node));
    idx = 1;
    for (j=0;j<N;j++)
        for (k=0;k<N;k++) tp->board[j][k]=atoi(argv[idx++]);
    for (k=0;k<N;k++) tp->board[N][k]=0;	
    tp->next=NULL;
    start=tp;
    printf("init state: \n");
    print_a_node(start);
    tp=(struct node *) malloc(sizeof(struct node));
    gidx = 1;
    for (j=0;j<N;j++)
        for (k=0;k<N;k++) tp->board[j][k] = gidx++;
    tp->board[N-1][N-1] = 0;	
    for (k=0;k<N;k++) tp->board[N][k]=0;
    tp->next=NULL;
    goal=tp;
    printf("goal state: \n");
    print_a_node(goal);
    strcpy(strategy_s,argv[idx]);
    if (strcmp(strategy_s,"dfs")==0) strategy=DFS;
    else if (strcmp(strategy_s,"bfs")==0) strategy = BFS;
    else if (strcmp(strategy_s,"best")==0) strategy=BEST;
    else if (strcmp(strategy_s,"bb")==0) strategy=BB;
    else if (strcmp(strategy_s,"astar")==0) strategy=ASTAR;
    else strategy=UNKNOWN;
    printf("strategy=%s\n",strategy_s);
    return start;
}

void exit_proc(char *msg){
   printf("Error: %s\n",msg);
   exit(1);
}