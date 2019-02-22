#include <stdio.h>

void reverse( int arr[], unsigned int len ){
    int tmp, last = len-1;

    for(int i = 0; i < len/2; i++){
        tmp = arr[i];
        arr[i] = arr[last];
        arr[last] = tmp;
        last--;
    }
}
