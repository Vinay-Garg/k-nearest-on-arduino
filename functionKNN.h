/*----------------------------------------------------------------
functions for the computation algorithm KNN
----------------------------------------------------------------*/

typedef struct couple
{
  double d; //distance
  int c;    //class
}couple;

//Euclidean calculation distance between two points
double Euclidian_distance (double pt1[], double pt2[], int n);

//calculation of Euclidean distance between a point and the database
void total_Euclid_dist(double pt1[], double aux[], double *attributes, int X_rows, int n);


int left(int i);
int right(int i);
void swap(couple *x, couple *y);
void buildMaxHeap(couple* arr, int n);
void MinHeapify(int i, couple *arr, int heap_size);
int extractMin(couple *arr, int heap_size);
int mostCommonClass(int* arr, int n, int k);


//Sorting distances from lowest to highest preserving class
void commands(double data[], int classes[],int fi);

//Remove the first N
void  First_extracted_K(double data[], double first_K[], int classes[], 
                     int kclasses[], int k);
                     
//Calculate the most common class : Fashion
int Most_Frequent_class(int classes[], int k);

//Maps a class integer value to a string
char* obtain_class_string(int claseint);

//Calculate the class of a set of attributes using KNN
int classify_KNN(double *data, int classesNum[], double dato[], int k, int fi, int co);

                     

