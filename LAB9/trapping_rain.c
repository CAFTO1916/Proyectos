#include <stdio.h>
#include <stdlib.h>

int trap(int* height, int n) {
    if (n <= 2) return 0;

    int* left_max = (int*)malloc(n * sizeof(int)); 
    int* right_max = (int*)malloc(n * sizeof(int)); 
    int water = 0;

    left_max[0] = height[0];
    for (int i = 1; i < n; i++) {
        if (height[i] > left_max[i-1]) 
            left_max[i] = height[i];
        else
            left_max[i] = left_max[i-1];
    }
    
    right_max[n-1] = height[n-1];
    for (int i = n-2; i >= 0; i--) {
        if (height[i] > right_max[i+1]) 
            right_max[i] = height[i];
        else
            right_max[i] = right_max[i+1];
    }
    
    for (int i = 0; i < n; i++) {
        int trapped = (left_max[i] < right_max[i] ? left_max[i] : right_max[i]) - height[i];
        if (trapped > 0) water += trapped;
    }
    
    free(left_max);
    free(right_max);
    return water;
}

int main()
{
    int arr1[] = {0,1,0,2,1,0,1,3,2,1,2,1};

    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", trap(arr1, n1)); // Salida: 6

    int arr2[] = {4,2,0,3,2,5};

    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", trap(arr2, n2)); // Salida: 9

    return 0;
}
