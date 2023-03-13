#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

char *clean_json(char *json) {
    bool instring = false;
    size_t count = 0;
    size_t e = 0;
    for (size_t i=0; i<strlen(json); i++) {
        if (json[i] == '\'' || json[i] == '\"') {
            instring = !instring;
        }
        if (strchr("{}[]:,\'\"0123456789", json[i]) == NULL && instring == false) {
            count++;
        }
    }
    char *result = malloc(strlen(json) - count);
    for (size_t i=0; i<strlen(json); i++) {
        if (json[i] == '\'' || json[i] == '\"') {
            instring = !instring;
        }
        if (instring == true) {
            result[e] = json[i];
            e++;
        } else {
            if (strchr("{}[]:,\'\"0123456789", json[i]) != NULL) {
                result[e] = json[i];
                e++;
            }
        }
    }
    result[strlen(json) - count] = '\0';
    return result;
}

char *getkeys(char *json) {
    
}

int main() {
    char *data = "{\"a\" : \"b\"}";
    printf("%s\n", clean_json(data));
    return 0;
}
