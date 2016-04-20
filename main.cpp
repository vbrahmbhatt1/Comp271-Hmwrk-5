//Valay Brahmbhatt
//Comp 271
//04-20-2016

/*
NOTE: went to tutoring with Abdul, Tara, Tom Biju
ALL the algorithms are taken from the Data Structure Using C++ textbook
*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void Bubble_Sort(int A[], int n);
void Insertion_Sort(int A[], int n);
void swap(int &x, int &y);
int partition(int a[], int left, int right, int pivotIndex);
void Quick_Sort(int a[], int left, int right);
void Shell_Sort(int A[], int n);
void merge(int A[], int low, int high, int mid);
void Merge_Sort(int A[], int low, int high);
bool array_y(string red, int *& noms);
int comparisons = 0;
int exchanges = 0;

void Bubble_Sort(int A[], int n)    //Bubble sorting
{
    int i, j, temp;
    for(i = 1; i < n; i++)      //number of passes
    {
        for(j = 0; j < n - 1; j++)      //j varies from 0 to n - 1
        {
            comparisons++;         //comparison within the for loop but before the if statement
            if(A[j] > A[j + 1])     //compare two successive numbers
            {
                temp = A[j];        //swap A[j] with A[j + 1]
                A[j] = A[j + 1];
                A[j + 1] = temp;
                exchanges++;        //making exchanges within the if statement
            }
        }
    }
    cout << "Bubble Comparisons: " << comparisons << endl; //console output
    cout << "Bubble Exchanges: " << exchanges << endl; //console output
    cout << endl; //space
}

void Insertion_Sort(int A[], int n)     //Insertion sorting
{
    int i, j, element;
    for(i = 1; i < n; i++)
    {
        element = A[i];     //insert ith element in 0 to i - 1 array
        j = i;
        comparisons++;      //making comparison
        while ((j > 0) && (A[j - 1] > element))     //compare if A[j - 1] > element
        {

            A[j] = A[j - 1];        //shift elements
            j = j - 1;
            exchanges++;        //making exchanges
            comparisons++;      //making comparison
        }
        A[j] = element;         //place element at jth position
    }
    cout << "Insertion Comparisons: " << comparisons << endl;   //console output
    cout << "Insertion Exchanges: " << exchanges << endl;       //console output
    cout << endl; //space
}

void swap(int &x, int &y)       //for Quick_Sort, passing by reference rather than value
{
    int temp;
    temp = x;
    x = y;
    y = temp;
}

int partition(int a[], int left, int right, int pivotIndex)     //for Quick_Sort
{
    int pivot = a[pivotIndex];      //creating a pivot
    do
    {
        while (a[left] < pivot)
        {
            left++;     //increase left by one
            comparisons++;      //making comparisons for left
        }
        comparisons++;
        while (a[right] > pivot)
        {
            right--;        //decrease right by one
            comparisons++;      //making comparisons for right
        }
        comparisons++;
        if (left < right && a[left] != a[right])
        {
            swap(a[left], a[right]);        //making a swap with left and right
            exchanges++;        //making exchanges in the if statement for swap
        }
        else
        {
            return right;
        }
    }
    while (left < right);
    return right;
}

void Quick_Sort(int a[], int left, int right)
//Quick sorting, will call swap and partition function above
{
    if (left < right)
    {
        int pivot = (left + right) / 2;         // middle
        int pivotNew = partition(a, left, right, pivot);
        Quick_Sort(a, left, pivotNew - 1);
        Quick_Sort(a, pivotNew + 1, right);
    }
}

void Shell_Sort(int A[], int n)     //Shell sorting
{
    int temp, gap, i;
    int swapped;
    gap = n/2;
    do
    {
        do
        {
            swapped = 0;        //swapped here is different that the swap function above
            for(i = 0; i < n - gap; i++)
            {
                comparisons++;      //comparison within the for loop but before the if statement, same as bubble sort function
                if(A[i] > A[i + gap])
                {
                    temp = A[i];
                    A[i] = A[i + gap];
                    A[i + gap] = temp;
                    swapped = 1;
                    exchanges++;    //making exchanges within the if statement, same as bubble sort function
                }
            }
        }
        while(swapped == 1);    //set swap equal to 1
    }
    while((gap = gap/2) >= 1);
    cout << "Shell Comparisons: " << comparisons << endl;   //console output
    cout << "Shell Exchanges: " << exchanges << endl;       //console output
    cout << endl; //space
}

void merge(int A[], int low, int high, int mid)     //for Merge_Sort
{
    int i, j, k, C[10000];
    i = low;          //index for first part
    j = mid + 1;      //index for second part
    k = 0;            //merge arrays A and B in array C
    while ((i <= mid) && (j <= high))
    {
        comparisons++;      //making comparisons
        if (A[i] < A[j])
        {
            C[k] = A[i++];
            exchanges++;        //making exchanges
        }
        else
        {
            C[k] = A[j++];
            exchanges++;        //making exchanges
        }
            k++;
    }
    while (i <= mid)
    {
        C[k++] = A[i++];
        exchanges++;        //making exchanges
    }
    while (j <= high)
    {
        C[k++] = A[j++];
        exchanges++;        //making exchanges
    }
    for (i = low, j = 0; i < high; i++, j++)
        //copy array C contents back to array A
    {
        A[i] = C[j];
    }
}

void Merge_Sort(int A[], int low, int high)     //Merge sorting, call to the function above
{
    int mid;
    if (low < high)
    {
        mid=(low + high)/2;
        Merge_Sort(A, low, mid);
        Merge_Sort(A, mid + 1, high);
        merge(A, low, high, mid);       //call the function above
    }
    return;
}

bool array_y(string red, int *& noms)   //reading in the text files into arrays
{
    ifstream thisfile;      //input file stream
    thisfile.open(red.c_str());     //c-style string, open the input file

    if(!thisfile.is_open())     //if the file fails to open
    {
        cout << "Can't find the file yo!" << red << endl;
        cout << "Wrong! check the location \n";
        cout << endl; //space
        return false;
    }
    string y;       //create a random string
    string x = " ";     //create a random string
    while(thisfile.peek()!= EOF)
        //peek reads and returns the next character without extracting
        //while this is not equal to end of the file
    {
        thisfile >> y;      //read in string y
        x += y + " ";
    }
    thisfile.clear();
    thisfile.close();       //close the input file

    vector<string> vertical;        //a vector of string
    y = "";
    for( int i = 0; i < x.length();i++)
    {
        if (x[i] == ' ')
        {
            vertical.push_back(y);
            y = "";
        }
        else
        {
            y += x[i];
        }
    }
    if(noms != NULL)        //making sure the memory is free
    {
        delete noms;
    }
   noms = new int[vertical.size()];
   for(int i = 0; i < vertical.size(); i++)
    {
        noms[i]= atoi(vertical[i].c_str());
    }
    return true;
}

int main(int argc, const char * argv[])
{
    int * Every_nums;
    string just_names[4];
    just_names[0] = "FewUnique.txt";
    cout << "FewUnique.txt" << endl;    //console output
    just_names[1] = "NearlySorted.txt";
    cout << "NearlySorted.txt" << endl;     //console output
    just_names[2] = "Random.txt";
    cout << "Random.txt" << endl;       //console output
    just_names[3] = "Reversed.txt";
    cout << "Reversed.txt" << endl;     //console output
    cout << endl;  //space

    for(int i = 0; i < 4; i++)
    {
        //NOTE: reading each algorithm one by one so the sorted array is reset
        //to unsorted array

       /*array_y(just_names[i], Every_nums);
       Bubble_Sort(Every_nums, 10000);*/

       /*array_y(just_names[i], Every_nums);
       Insertion_Sort(Every_nums, 10000);*/

       /*array_y(just_names[i], Every_nums);
       Quick_Sort(Every_nums, 0, 9999);
       cout << "Quick Comparisons: " << comparisons << endl;    //console output
       cout << "Quick Exchanges: " << exchanges << endl;      //console output
       cout << endl;*/    //space

       /*array_y(just_names[i], Every_nums);
       Shell_Sort(Every_nums, 10000);*/

       array_y(just_names[i], Every_nums);
       Merge_Sort(Every_nums, 0, 9999);
       cout << "Merge Comparisons: " << comparisons << endl;     //console output
       cout << "Merge Exchanges: " << exchanges << endl;      //console output
       cout << endl;   //space





       //Test on each algorithm with smaller array
       /*int nums[] = {1,13,4,6,4,33,5,25,7,1};
       Bubble_Sort(nums, 10);*/

       /*int nums[] = {1,13,4,6,4,33,5,25,7,1};
       Insertion_Sort(nums, 10);*/

       /*int nums[] = {1,13,4,6,4,33,5,25,7,1};
       Quick_Sort(nums, 1, 10);*/

       /*int nums[] = {1,13,4,6,4,33,5,25,7,1};
       Shell_Sort(nums, 10);*/

       /*int nums[] = {1,13,4,6,4,33,5,25,7,1};
       Merge_Sort(nums, 1, 10);*/
    }
    cout << "Done, good job!" << endl; //words of encouragements
    return 0;
}
