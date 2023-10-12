#include "../include/global.h"

/**
 *  Feel free to use the functions that you made in strPtr.c
 */ 
// this method encrypts the plaintext into ciphertext given a few cases
int encrypt(const char *plaintext, char *ciphertext, int key){
    char *original_ciphertext = ciphertext;
    int encoded = 0;
    char undefined_strg[] = "undefined__EOM__";
    int plaintext_length = strgLen((char *)plaintext);
    int ciphertext_length = strgLen(ciphertext);
    // Case -2: if either text is null at any point
    // don't encrypt
    if (plaintext == NULL || ciphertext == NULL) {
        return -2;
    }
    // Case -1: if there is not enough space to hold the message and the marker the message won't be encrptyed
    // don't encrypt
    else if ((plaintext_length + 7) > ciphertext_length) {
        return -1;
    }
    else {
        // No errors before attempting to encrypt the message
        // start to encrypt the message
        while (*plaintext != '\0' && *ciphertext != '\0') {
            // ecryption of capital letters
            if (*plaintext >= 'A' && *plaintext <= 'Z') {
                if ((*plaintext + key) > 'Z') {
                    // use of module to fix overlap with large key value
                    key = key % 26;
                    *ciphertext++ = (*plaintext++ + key - 'A') % ('Z' - 'A' + 1) + 'A';
                }
                else {
                    *ciphertext++ = *plaintext++ + key;
                }
            }
            // encryption of lower case ltters
            else if (*plaintext >= 'a' && *plaintext <= 'z') {
                if ((*plaintext + key) > 'z') {
                    // use of module to fix overlap with large key value
                    key = key % 26;
                    *ciphertext++ = (*plaintext++ + key - 'a') % ('z' - 'a' + 1) + 'a';
                }
                else {
                    *ciphertext++ = *plaintext++ + key;
                }
            }
            // encryption of digits
            else if (*plaintext >= '0' && *plaintext <= '9') {
                if ((*plaintext + key) > '9') {
                    // use of module to fix overlap with large key values
                    key = key % 10;
                     *ciphertext++ = (*plaintext++ + key - '0') % ('9' - '0' + 1) + '0';
                }
                else {
                    *ciphertext++ = *plaintext++ + key;
                }
            }
            // encryption of nonaplhanumeric values
            // notice how continue is used so encoded isn't incrmeneted
            else {
                *ciphertext++ = *plaintext++;
                // don't want to increment encoded, so continue
                continue;
            }
            encoded++;
        }
        // when all of the characters are non alphanumeric the encoded number is zero, this will result in an undefined encryption
        // no storage errors should occur because that was already checked previously
        if (encoded == 0 && ciphertext_length >= 16) {
            ciphertext = original_ciphertext;
            for (int i = 0; i < strgLen(undefined_strg) && *ciphertext != '\0'; i++) {
                *ciphertext++ = undefined_strg[i];
            }
        }
        // When ciphertext can't hold undefined__EOM__ from above if statement
        // This will be the only time a storage issue occurs because undefined__EOM__ might be larger than the plaintext length with a non alphanumeric string
        // this error can only be found only ou have attempted to encrypt all the characters
        else if (encoded == 0 && ciphertext_length < 16){
            *ciphertext = '\0';
            return -1;
        }
        // This will add the EOM marker to the ciphertext
        // no need to check the sizes of anything because that was done in the beginning to return -1 before encrypting
        else {
            char eom[] = "__EOM__";
            for (int i = 0; i < strgLen(eom) && *ciphertext != '\0'; i++) {
                *ciphertext++ = eom[i];
            }
        }
        // mark as end of string
        *ciphertext = '\0';
        // return the number of encrypted characters
        return encoded;
    }
    abort();
}
// This is a helper function I created that returns true if the ciphertext contains the EOM marker and false if it doesn't
bool has_eom(char *ciphertext) {
    char *eom = "__EOM__";
    while (*ciphertext != '\0') {
        // Check if the current position matches the start of the eom string
        if (*ciphertext == eom[0]) {
            char *pos_cipher = ciphertext;
            char *pos_eom = eom;
            // Check if the characters following match the rest of the eom string
            while (*pos_cipher != '\0' && *pos_eom != '\0' && *pos_cipher == *pos_eom) {
                pos_cipher++;
                pos_eom++;
            }
            // If we reached the end of the eom string, we found it, return true
            if (*pos_eom== '\0') {
                return true;
            }
        }
        // Move to the next character in ciphertext
        ciphertext++;
    }
    // EOM was not found
    return false;
}
// this method decrypts the ciphertext into plaintext
int decrypt(const char *ciphertext, char *plaintext, int key){
    int decoded = 0;
    char *original_ciphertext = (char *)ciphertext;
    char *original_plaintext = plaintext;
    int plaintext_length = strgLen(plaintext);
    int ciphertext_length = strgLen((char *)ciphertext);
    // Case -2: if either text is null at any point
    // don't decrypt
    if (plaintext == NULL || ciphertext == NULL) {
        return -2;
    }
    // Case 0: if the length of plaintext is 0
    // don't decrypt
    else if (plaintext_length == 0) {
        return 0;
    }
    // Case -1: if the ciphertext is missing the EOM marker
    // uses my custom has_eom method
    else if (!has_eom((char *)ciphertext)) {
        return -1;
    }
    else {
        ciphertext = original_ciphertext;
        char eom[] = "__EOM__";
        // start decrypting until you reach the EOM marker
        while (*plaintext != '\0' && *ciphertext != '\0') {
            // check if we have reach the EOM marker
            if (*ciphertext == '_') {
                int i = 0;
                char *before_searching = (char *)ciphertext;
                while (*ciphertext != '\0') {
                    if (*ciphertext == eom[i]) {
                        i++;
                        if (eom[i] == '\0') {
                            // eom marker found so you are done encryption
                            goto stopDecryption;
                        }
                    }
                    // underscore is a character that is not part of the EOM marker
                    else {
                        i = 0;
                        break;
                    }
                    ciphertext++;
                }
                // this goes back to the ciphertext point location you were at before you checked if the '_' was the start of the EOM marker
                ciphertext = before_searching;
                *plaintext++ = *ciphertext++;
                continue;
            }
            // The character reached is an upper case letter
            else if (*ciphertext >= 'A' && *ciphertext <= 'Z') {
                // use of module to fix overlap with large key values
                key = key % 26;
                 *plaintext++ = (*ciphertext++ - 'A' + 26 - key) % 26 + 'A';
            }
            // The character reached is an lower case letter
            else if (*ciphertext >= 'a' && *ciphertext <= 'z') {
                // use of module to fix overlap with large key values
                key = key % 26;
                *plaintext++ = (*ciphertext++ - 'a' + 26 - key) % 26 + 'a';
            }
            // The character reached is a digit
            else if (*ciphertext >= '0' && *ciphertext <= '9') {
                // use of module to fix overlap with large key values
                key = key % 10;
                *plaintext++ = (*ciphertext++ - '0' + 10 - key) % 10 + '0';
            }
            // The character reached is a nonalphanumeric value
            else {
                *plaintext++ = *ciphertext++;
                // don't want to increment decoded, so continue
                continue;
            }
            decoded++;
        }
        // goto from checking for EOM marker in beginning
        stopDecryption:
            // This means that nothing was encrypted which is undefined
            if (decoded == 0 && plaintext_length >= 9) {
                plaintext = original_plaintext;
                char undef[] = "undefined";
                for (int i = 0; i < strgLen(undef) && *plaintext != '\0'; i++) {
                    *plaintext++ = undef[i];
                }
                 *plaintext = '\0';

            }
             *plaintext = '\0';
            return decoded;
    }
    // mark as end of string
    *plaintext = '\0';
    // return the number of decrypted characters
    return decoded;
    abort();
}