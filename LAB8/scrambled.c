#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool isScramble(char *s1, char *s2, int len) {
    if (len <= 1) return true;

    if (memcmp(s1, s2, len) == 0) return true;

    int count[26] = {0};

    for (int i = 0; i < len; i++) {
        count[s1[i] - 'a']++;
        count[s2[i] - 'a']--;
    }
    for (int i = 0; i < 26; i++) {
        if (count[i] != 0) return false;
    }
  
    for (int i = 1; i < len; i++) {
        if (isScramble(s1, s2, i) &&
            isScramble(s1 + i, s2 + i, len - i)) {
            return true;
        }
        if (isScramble(s1, s2 + len - i, i) &&
            isScramble(s1 + i, s2, len - i)) {
            return true;
        }
    }
    return false;
}

int main()
{
    char s1[100];
    char s2[100];
    printf("Ingrese la primera palabra: ");
    scanf("%99s", s1);
    printf("Ingrese la segunda palabra: ");
    scanf("%99s", s2);

    int len1 = strlen(s1);
    int len2 = strlen(s2);

    if (len1 != len2) {
        printf("%s NO es un scrambled de %s (porque tiene longitud distinta)\n", s2, s1);
        return 0;
    }
  
    if (isScramble(s1, s2, len1))
        printf("%s es un scrambled de %s\n", s2, s1);
    else
        printf("%s NO es un scrambled de %s\n", s2, s1);
        
    return 0;
}
