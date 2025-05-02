#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

void swap(vector<int>& arr, int i, int j){
    const int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp; 
}

void bubble_sort_serial(vector<int>& arr){
    int n= arr.size();
    for(int i=n-1; i>0; i--){
        for(int j=1; j<=i; j++){
            if(arr[j]<arr[j-1])swap(arr, j, j-1);
        }
    }
}

void bubble_sort_parallel(vector<int>& arr){
    //Odd-Even Transposition Sort Algorithm
    int n = arr.size();
    for(int i=0; i<n; i++){
        int offset = i%2;

        #pragma omp for
        for(int j=offset; j<n-1; j+=2){
            if(arr[j] > arr[j+1]){
                swap(arr, j, j+1);
            }
        }
    }
}

int main(){
    vector<int>v = {1,4,2,3,7,5,9,6,12,8,14,12,15,16,6,1,7,17,18,8,1,19};
    bubble_sort_serial(v);
    for (auto &&i : v)cout<<i<<", "; cout<<"\n";

    v = {1,4,2,3,7,5,9,6,12,8,14,12,15,16,6,1,7,17,18,8,1,19};
    bubble_sort_parallel(v);
    for (auto &&i : v)cout<<i<<", "; cout<<"\n";
    
}