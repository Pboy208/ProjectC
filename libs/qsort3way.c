#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void exch(int a[], int i, int j);
void swap(int *a,int *b);
void quicksort_3_way(int a[], int l, int r,int indexarr[]);
int int_compare(void const *x,void const *y);

// Compare two integer numbers
int int_compare(void const *x,void const *y){
    int m,n;
    m=*((int *)x);
    n=*((int *)y);
    if (m==n) return 0;
    return m>n ? 1:-1;
}

void quicksort_3_way(int x[],int left,int right,int index[]){
    // Before partitioning
    int i,j,p,q,pivot,k;
    i=left-1; j=right;
    p=left-1; q=right;
    pivot=x[right];
    if (right<=left) return;
    
    // During swapping
    for (;;){
        while (x[++i]<pivot);
        while (x[--j]>pivot) if (j==left) break;
        
        if (i>=j) break;
        swap(&x[i],&x[j]);
        swap(&index[i],&index[j]);
        
        if (x[i]==pivot){
            p++;
            swap(&x[p],&x[i]);
            swap(&index[p],&index[i]);
        }
        
        if (x[j]==pivot){
            q--;
            swap(&x[q],&x[j]);
            swap(&index[q],&index[j]);
        }
    }
    swap(&x[i],&x[right]);
    swap(&index[i],&index[right]);
    j=i-1; i++;
    
    // Moving equal elements to the pivot
    for (k=left;k<p;k++,j--) 
    {   
        swap(&x[k],&x[j]);
        swap(&index[k],&index[j]);
    }
    for (k=right-1;k>q;k--,i++)
    {   
        swap(&x[i],&x[k]);
        swap(&index[i],&index[k]);
    }
    
    // Calling QS 3 way for smaller partitions
    quicksort_3_way(x,left,j,index);
    quicksort_3_way(x,i,right,index);
}

void exch(int a[], int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void swap(int *a,int *b){
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
