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
    size_t next_key = 0;
    size_t keys = 0;
    for (size_t i=0; i<strlen(json); i++) {
        if (json[i] == '{' || json[i] == ',' && json[i+1] == '\"') {
            next_key = i+2;
            keys++;
        }
    }
    char **result = malloc(sizeof(char *) * keys);
    bool in_key = false;
    size_t on_key = -1;
    size_t key_size = 0;
    next_key = 0;
    for (size_t i=0; i<strlen(json); i++) {
        if (json[i] == '{' || json[i] == ',' && json[i+1] == '\"') {
            next_key = i+2;
            on_key++;
            on_key -= on_key/2;
        }
        if (json[i] == '\"' && json[i+1] == ':') {
            in_key = false;
        }
        if (i == next_key) {
            in_key = true;
        }
        if (in_key == true) {
            key_size++;
        }
        if (in_key == false && key_size > 0) {
            result[on_key] = malloc(key_size);
            on_key++;
            key_size = 0;
        }
    }
    in_key = false;
    on_key = -1;
    key_size = 0;
    next_key = 0;
    for (size_t i=0; i<strlen(json); i++) {
        if (json[i] == '{' || json[i] == ',' && json[i+1] == '\"') {
            next_key = i+2;
            on_key++;
            on_key -= on_key/2;
        }
        if (json[i] == '\"' && json[i+1] == ':') {
            in_key = false;
        }
        if (i == next_key) {
            in_key = true;
        }
        if (in_key == true) {
            result[on_key][key_size] = json[i];
            key_size++;
        }
        if (in_key == false && key_size > 0) {
            on_key++;
            key_size = 0;
        }
    }
    printf("%s\n", result[0]);
}

int main() {
    char *data = "{\"test69\" : \"bababooey\", \"test2\" : \"memes2\", \"test3\" : 69420}";
    printf("%s\n", clean_json(data));
    get_keys(clean_json(data));
    return 0;
}
