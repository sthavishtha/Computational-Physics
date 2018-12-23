#ifndef FUNCTION_LIST_H
#define FUNCTION_LIST_H

extern int N;
extern int *lat, *M, *no_sites;

int index(int, int);
int chk_neg_m(int);
/*int compare_left(int*,int,int,int);
int compare_top(int*,int,int,int);
void update_sing_top(int*,int*,int,int,int);
void update_sing_left(int*,int*,int,int,int);
void update_both(int*,int*,int,int,int);
void update_none(int*,int*,int&,int,int, int); */
int compare_left(int,int);
int compare_top(int,int);
void update_sing_top(int,int);
void update_sing_left(int,int);
void update_both(int,int);
void update_none(int&,int,int); 

void cluster_size(float);

#endif FUNCTION_LIST_H
