//#include <HardwareSerial.h> // Debug only
//#include "dataset.h"
//#include "functionKNN.h"
#include <stdlib.h>
#include <math.h>

/*----------------------------------------------
Euclidean distance between two points
------------------------------------------------*/
double Euclidian_distance (double pt1[], double pt2[], int n)
{  
  double sum = 0;
  for(int i=0; i<n; i++)
    sum += (pt1[i] - pt2[i]) * (pt1[i] - pt2[i]); 
  return sqrt(sum);
}


/*---------------------------------------------------------------
calculation of Euclidean distance between a point and the database
----------------------------------------------------------------*/
// total_Euclid_dist(input_data, out_Euc_dist, (double*)dataset, X_rows, y); 
void total_Euclid_dist(double pt1[], double aux[], double *attributes, int X_rows, int n)
{
  double pt2[n];
  for(int i = 0; i<X_rows; i++)
  {
    for(int j=0; j<n; j++)          
      pt2[j] = attributes[i*n+j];
       
    aux[i] = Euclidian_distance (pt1, pt2, n);
  }
}


typedef struct couple
{
	double d; //distance
	int c;	  //class
}couple;


couple* makecouple(double dist[], int *cl, int X_rows)
{
  couple *arr= (couple*)malloc(sizeof(couple) * X_rows);
	for (int i = 0; i < X_rows; ++i)
	{
		arr[i].d = dist[i]; 
		arr[i].c = cl[i];
	}
	return arr;
}



int left(int i) { return (2*i + 1); }
 
int right(int i) { return (2*i + 2); }

void swap(couple *x, couple *y)
{
    couple temp = *x;
    *x = *y;
    *y = temp;
}

void MinHeapify(int i, couple *arr, int heap_size)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && arr[l].d < arr[i].d)
        smallest = l;
    if (r < heap_size && arr[r].d < arr[smallest].d)
        smallest = r;
    if (smallest != i)
    {
        swap(&arr[i], &arr[smallest]);
        MinHeapify(smallest, arr, heap_size);
    }
}


void buildMaxHeap(couple* arr, int n)
{
	 // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        MinHeapify(i, arr, n);
}



int extractMin(couple *arr, int heap_size)
{
    if (heap_size <= 0)
        return -1;
    if (heap_size == 1)
    {
        heap_size--;
        return arr[0].c;
    }
 
    // Store the minimum value, and remove it from heap
    couple root = arr[0];
    arr[0] = arr[heap_size-1];
    heap_size--;
    MinHeapify(0, arr, heap_size);
 
    return root.c;
}


void First_extracted_K(couple* arr, int heap_size, int k, int kclasses[])
{
	for (int i = 0; i < k; ++i)
	{
		kclasses[i] = extractMin(arr, heap_size);
	}
}


/*----------------------------------------------------------------
//Calculate the most common class : Fashion
----------------------------------------------------------------*/
int mostCommonClass(int* arr, int n, int k)
{
    // Iterate though input array, for every element
    // arr[i], increment arr[arr[i]%k] by k
    for (int i = 0; i< n; i++)
        arr[arr[i]%k] += k;
 
    // Find index of the maximum repeating element
    int max = arr[0], result = 0;
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
            result = i;
        }
    }
 
    /* Uncomment this code to get the original array back
       for (int i = 0; i< n; i++)
          arr[i] = arr[i]%k; */
 
    // Return index of the maximum element
    return result;
}


  
/*----------------------------------------------------------------
//Calculate the class of a set of attributes using KNN
----------------------------------------------------------------*/
int classify_KNN(double *dataset, int classesNum[], double input_data[],
							 int k, int X_rows, int y)
{
  double out_Euc_dist[X_rows], first_K[k];
  int classes[X_rows], kclasses[k];


  for (int i = 0; i < X_rows; ++i)
  classes[i] = classesNum[i];
  
  
  total_Euclid_dist(input_data, out_Euc_dist, dataset, X_rows, y); 
  couple* p = makecouple(out_Euc_dist, classes, X_rows);
  buildMaxHeap(p, X_rows);
  First_extracted_K(p, X_rows, k, kclasses);  
  return mostCommonClass(kclasses, k, y);
}
