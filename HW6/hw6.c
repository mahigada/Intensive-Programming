/* HW6 read cafefully and follow all the instructions/comments
   this program compiles and runs as is although it's not doing much.
   DO NOT CHANGE THE SEED. Changing seed gives a different sequence of
   numbers but we want the same numbers for comparison purposes.

   FLOATING point radix sort requires some substantial changes to this code
   float n, lst[N],tmp[N];	
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define OK 1
#define NOK 0
//#define NELM 100
		/* default 100 elements */
#define NELM 5
#define N 1048576		/* 2^20 or 1 meg elements  */
//#define N 2097152
//#define N 4194304
//#define N 8388608
//#define N 16777216
//#define N 33554432

void selection_sort();
void swap();

void merge_sort();
void msort_recursive();

void int_radix_sort();
void float_radix_sort();
void swap();
void self_check();

int rand(void);
void srand();
int rand_r();
void init_lst();
void float_lst();
void print_lst();
void swap();

int n, lst[N], buf[N];
float lst2[N], buf2[N];
int main(int argc,char **argv) {

  long int del_sec,del_msec;
  struct timeval tv_s,tv_e;

  if (argc>1) n = atoi(argv[1]);
  else n = NELM;
  printf("n=%d\n",n);
  init_lst(lst,n);
  float_lst(lst2,n);
  printf("-- radix sort (float) -- \n");
  print_lst(lst2,n);
  gettimeofday(&tv_s, NULL);
  //selection_sort(lst,n);
  //merge_sort(lst,buf,n);
  //int_radix_sort(lst, buf, n);
  float_radix_sort(lst2,buf2,n);
  //print_lst(lst,n);
  //self_check(lst,n);
  //self_check(buf,n);
  print_lst(lst2,n);
  self_check(lst2,n);
  self_check(buf2,n);
  gettimeofday(&tv_e, NULL); 
  del_sec=tv_e.tv_sec-tv_s.tv_sec;
  del_msec=tv_e.tv_usec-tv_s.tv_usec;
  printf("time taken: %ld seconds and %ld microseconds (%ld microsec)\n",del_sec,del_msec,del_sec*1000000+del_msec);
  return 0;
}


void selection_sort(int lst[],int n){
    int i, j, min_ind;
    for (i = 0; i < n-1; i++) 
    { 
        // Find the min in unsorted arr 
        min_ind = i;
        for (j = i+1; j < n; j++) 
          if (lst[j] < lst[min_ind]){
              min_ind = j;
          } 
          // Swap the  min w/ first  
          swap(&lst[min_ind], &lst[i]); 
    }  
}
void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
}
void merge_sort(int lst[], int buf[], int n){
  msort_recursive(lst, buf, 0, n-1);
}

//use recursion
void msort_recursive(int lst[], int tmp[], int left, int right){
    if (right<=left){
        return;
    }
    int mid = (right + left) / 2;
    msort_recursive(lst, tmp, left, mid);    
    msort_recursive(lst, tmp, mid + 1, right); 
    int pt_l = left;      
    int pt_r = mid + 1;       
    int k; 
    for (k = left; k <= right; k++) {
        if (pt_l == mid + 1) {      
            tmp[k] = lst[pt_r];
            pt_r++;
        } else if (pt_r == right + 1) {       
            tmp[k] = lst[pt_l];
            pt_l++;
        } else if (lst[pt_l] < lst[pt_r]) {       
            tmp[k] = lst[pt_l];
            pt_l++;
        } else {       
            tmp[k] = lst[pt_r];
            pt_r++;
        }
    }
    for (k = left; k <= right; k++) {      
        lst[k] = tmp[k];
    }
}

void int_radix_sort(int lst[],int tmp[],int n) {
	int group = 8;			
	int bucket = 256;	
	int mask=0xFF;
	int count[bucket], total[bucket];
	int i,pass;
	for(pass = 0;pass < 32; pass += group){
		for(i=0;i< bucket; i++){
            count[i]=0;
        }
		for(i=0;i<n;i++){
            count[(lst[i]>>pass)&mask]++;
        }
		total[0]=0;
		for(i=1;i<bucket;i++){
            total[i]=total[i-1]+count[i-1];
        }
		for(i=0;i<n;i++){
            tmp[total[(lst[i]>>pass)&mask]++]=lst[i];
        }
		for(i=0;i<n;i++){
            lst[i]=tmp[i];
        }
	}
	int neg_ind;
	for(i=0;i<n;i++){
		if(lst[i]<0){
			neg_ind=i;
			break;
		}
	}
	for(i=0;i<n;i++){
		if(i<neg_ind){
            tmp[n-neg_ind+i]=lst[i];

        }
		else {
            tmp[i-neg_ind]=lst[i];
        }
	}
	for(i=0;i<n;i++){
        lst[i]=tmp[i];

    }
}


//fix the bucket size to 256. run 4 passes where each pass processes 8 bits
//use lst and tmp only. do not use any more memory of size n.

void float_radix_sort(int lst[],int tmp[],int n) {
    int_radix_sort(lst,tmp, n);
}

void print_lst(int *l,int n){
  int i;
  for (i=0; i<n; i++) {
    printf("%d ",l[i]);
  }
  printf("\n");
}
void init_lst(int *l,int n){
  int i;
  int seed = time(0) % 100;	/* seconds since 1/1/1970 */
  printf ("seed=%d\n", seed);
  srand(1234);			/* SEED */
  for (i=0; i<n; i++) {
    l[i] = rand();
  }
}
void float_lst(float *l, int n){

  for (int i=0; i<n; i++) {
      l[i] = ((float)rand()/(float)(RAND_MAX))*100.0;
  }
}

void self_check(int *lst,int n) {
  int i,j,flag=OK,*lstp;

  lstp = lst;
  for (i=0;i<n-1;i++)
     if (lstp[i] > lstp[i+1]) { flag = NOK; break; }

  if (flag == OK) printf("sorted\n");
  else printf("NOT sorted at %d\n",i);
}

/* End of file */
