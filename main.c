#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

char *clean_json(char *json) {
    bool in_string = false;
    size_t count = 0;
    size_t e = 0;
    for (size_t i=0; i<strlen(json); i++) {
        if (json[i] == '\"') {
            in_string = !in_string;
        }
        if (strchr("{}[]:,\"0123456789tfn", json[i]) == NULL && in_string == false) {
            count++;
        }
    }
    char *result = malloc(strlen(json) - count);
    for (size_t i=0; i<strlen(json); i++) {
        if (json[i] == '\"') {
            in_string = !in_string;
        }
        if (in_string == true) {
            result[e] = json[i];
            e++;
        } else {
            if (strchr("{}[]:,\"0123456789tfn", json[i]) != NULL) {
                result[e] = json[i];
                e++;
            }
        }
    }
    result[strlen(json) - count] = '\0';
    return result;
}

char *get_keys(char *json) {
    bool in_key = false;
    size_t next_key = 0;
    size_t keys = 0;
    char array[10][10];
    for (size_t i=0; i<strlen(json); i++) {
        if (json[i] == '{' || json[i] == ',' && json[i+1] == '\"') {
            next_key = i+2;
            keys++;
        }
        if (json[i] == '\"' && json[i+1] == ':') {
            in_key = false;
        }
        if (i == next_key) {
            in_key = true;
        }
        if (in_key == true) {
            array[keys]
        }
    }
}

int main() {
    char *data = "{\"test1\" : \"bababooey\", \"test2\" : \"memes2\", \"test3\" : 69420}";
    //printf("%s\n", clean_json(data));
    get_keys(clean_json(data));
    return 0;
}
