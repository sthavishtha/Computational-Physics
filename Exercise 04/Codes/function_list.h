/**
   Function declarations are done here
 **/

#ifndef FUNCTION_LIST_H
#define FUNCTION_LIST_H

extern int *lat, *no_sites, *M;

double get_wtime(void);
int index(int, int, int);
int chk_neg_m(int);
int compare_left(int,int, int);
int compare_top(int,int, int);
void update_sing_top(int,int, int);
void update_sing_left(int,int, int);
void update_both(int,int, int);
void update_none(int&,int,int, int); 
void initialize(float, int, int);
void cluster_first_row(int&, int);
int largest_cluster(int);
void flag_find(int, int*, int);
void cluster_size(float, int[], int);
void min(int, int, int*, int*, int);
void center_occ_pos(int[], int&, int&, int);
void file_print(int, int);
void mass_radius(int, int, int, int[], int[], int);

#endif
