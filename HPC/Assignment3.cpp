#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

int sum_parallel(vector<int>arr){
    int n = arr.size(), sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for(int i=0; i<n; i++){
        sum += arr[i];
    }
    return sum;
}

int min_parallel(vector<int>arr){
    int n = arr.size(), min_val = INT_MAX;

    #pragma omp parallel for reduction(min:min_val)
    for (int i = 0; i < n; i++){
        min_val = min(min_val, arr[i]);
    }
    return min_val;
}

int max_parallel(vector<int>arr){
    int n = arr.size(), max_val = INT_MIN;

    #pragma omp parallel for reduction(max: max_val)
    for (int i = 0; i < n; i++){
        max_val = max(max_val, arr[i]);
    }
    return max_val;
}

int main(){
    vector<int>v = {1,4,2,3,7,5,9,6,12,8,14,12,15,16,6,1,7,17,18,8,1,19};
    printf("Sum: %d \n", sum_parallel(v));
    printf("Min: %d \n", min_parallel(v));
    printf("Max: %d \n", max_parallel(v));
}