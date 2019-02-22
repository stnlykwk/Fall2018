/* 
1. Write a program that calculates the frequency of 
letter occurrences in text.
2. Read ASCII text from standard input.
3. On reaching EOF, print to stdout the normalized 
frequency of occurrence for each letter a-z that 
appeared in the input, one per line, in alphabetical 
order using the format produced by

    printf( "%c %.4f\n", letter, freq);

4. Letters that occur zero times should not appear 
in the output.
5. Characters other than lower and upper case 
letters should be ignored.
6. Lower and upper case instances count as the same 
letter, e.g. 'a' and 'A' are both reported for the 
letter 'a' on the output.
7. The frequencies reported should sum to 
approximately 1 (with a little slack for 
accumulation of printf rounding errors). 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main( void )
{
    int upper[] = {[0 ... 25] = 0};
    int lower[] = {[0 ... 25] = 0};
    char lc[26];
    int sum[26];
    int ch;
    float count = 0;
//create lowercase alphabet
    for(int a = 0; a < 26; a++)
        lc[a] = (a+97);
//read input from stdin and count occurences
    while((ch = getchar()) != EOF){
        if(isalpha(ch)){
            if(isupper(ch))
                upper[ch-65] += 1;
            
            if(islower(ch))
                lower[ch-97] += 1;
            
            count++;
        }
    }
//sum up total occurences
    for(int e = 0; e < 26; e++)
        sum[e] = (lower[e] + upper[e]);
    
    //printf("\n");

    for(int i = 0; i < 26; i++){
        if(sum[i] != 0)
            printf( "%c %.4f\n", lc[i], (sum[i]/count));
    }
        
    return 0;
}