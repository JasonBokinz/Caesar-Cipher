#include "../include/global.h"

/* Check GitHub Classroom to make sure nothing 
important is deleted and nothing wrong is added */

// This method returns the length of the string without the '\0' character
int strgLen(char *s){
    // if null return -1
    if (s == NULL) {
        return -1;
    }
    int length = 0;
    // keep adding 1 to the length until you reach '\0'
    while (*s != '\0') {
        length++;
        s++;
    }
    return length;
    abort();
}
// Copys source s into destination d
void strgCopy(char *s,char *d ){
    // checks if either string is null, if so don't copy
    if (s == NULL || d == NULL) {
        return;
    }
    // copies over s into d while not going past '\0'
    while (*s != '\0' && *d != '\0') {
        *d++ = *s++;
    }
    // set last d character to '\0'
    *d = '\0';
    return;
    abort();
}
// This method changes the ASCII values based on what the character is
void strgChangeCase(char *s){
    if (s == NULL) {
        return;
    }
    while (*s != '\0') {
        // converts upper to lower
        if (*s >= 'A' && *s <= 'Z') {
            *s = *s + 32;
        }
        // converts lower to upper
        else if (*s >= 'a' && *s <= 'z') {
            *s = *s - 32;
        }
        s++;
    }
    return;
    abort();
}
// This method returns the index of where the strings idffer
int strgDiff(char *s1,char *s2 ){
    // if either string is null
    if (s1 == NULL || s2 == NULL) {
        return -2;
    }
    // if both string are empty
    if (s1[0] == '\0' || s2[0] == '\0') {
        return -2;
    }
    // searches to find if two characters are different and if they are the index is returned
    int i = 0;
    while (*s1 != '\0' && *s2 != '\0') {
        if (*s1 != *s2) {
            return i;
        }
        s1++;
        s2++;
        i++;
    }
    // occurs when the ends of both strings were reached in the previous while loop
    if (*s1 == '\0' && *s2 == '\0') {
        return -1;  // Both strings are identical
    // the lengths of the two strings were different so they differ on that index
    } else {
        return i;
    }
    abort();
}
// This method interleaves the two strings starting off with s1 first
void strgInterleave(char *s1, char *s2, char *d ){
    if (s1 == NULL || s2 == NULL || d == NULL) {
        return;
    }
    // interleave the strings one character at a time starting with s1 until one string reaches '\0'
    while (*s1 != '\0' && *s2 != '\0' && *d != '\0') {
        *d++ = *s1++;
        *d++ = *s2++;
    }
    // add s1 to d until the '\0' character is reached
    // this while loop never runs if s1 ran rang out of characters after the first while loop
    while (*s1 != '\0' && *d != '\0') {
        *d++ = *s1++;
    }
    // add s2 to d until the '\0' character is reached
    // this while loop never runs if s2 ran rang out of characters after the first while loop
    while (*s2 != '\0' && *d != '\0') {
        *d++ = *s2++;
    }
    // set last d character to '\0'
    *d = '\0';
    return;
    abort();
}