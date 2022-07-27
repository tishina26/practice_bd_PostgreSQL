#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// can take from DB?
int elements = 3;
int seconds_sleep = 3 * 60; // 3 minutes

struct ban {
    int id_system;
    char* date_block;
};

// only for 3 elements
void fill_data(struct ban* arr) {
    arr[0].id_system = 123;
    arr[1].id_system = 1234;
    arr[2].id_system = 12345;
    arr[0].date_block = "26.07.2022 16:50:00";
    arr[1].date_block = "26.07.2022 16:51:05";
    arr[2].date_block = "26.07.2022 16:52:00";
}

void print_data(struct ban* arr) {
    printf("____________________________\n");
    printf("data_recipient_ban is:\n");

    for (int i = 0; i < elements; i++) {
        printf("%d\t%s\n", arr[i].id_system, arr[i].date_block);
    }

    printf("____________________________\n");
}

// if (date2 - date1 >= 1hour) {1} else {0}
int check_time(char* s, char* t) {
    // compare with 1 h = 60 m = 3600 s
    int s_time = (10 * (int)(s[11]-'0') + (int)(s[12]-'0')) * 3600;
    s_time += (10 * (int)(s[14]-'0') + (int)(s[15]-'0')) * 60;
    s_time += (10 * (int)(s[17]-'0') + (int)(s[18]-'0'));

    int t_time = (10 * (int)(t[11]-'0') + (int)(t[12]-'0')) * 3600;
    t_time += (10 * (int)(t[14]-'0') + (int)(t[15]-'0')) * 60;
    t_time += (10 * (int)(t[17]-'0') + (int)(t[18]-'0'));

    // if dates are not equel
    if (strncmp(s, t, 10) != 0) {
        t_time += 3600 * 24; // seconds in 1 day
    }

    if (t_time - s_time >= 3600) {
        return 1;
    }

    return 0;
}

// delete elements from array; change value of 'elements'
struct ban* check_DB(struct ban* arr, char* t) {
    int count_deletes = 0; // alse used as a new_index

    for (int i = 0; i < elements - count_deletes; i++) {
        char* s = arr[i + count_deletes].date_block;
        
        if (check_time(s, t) == 1) {
            count_deletes++;

            if (i < elements - count_deletes) {
                arr[i] = arr[i + count_deletes];
                i--;
            }
        } else {
            arr[i] = arr[i + count_deletes];
        }
    }

    elements -= count_deletes;
    return realloc(arr, elements * sizeof(struct ban));
}

int main(void) {
    // create, fill and print data base
    struct ban* data_recipient_ban = malloc(sizeof(struct ban) * elements);

    fill_data(data_recipient_ban);
    print_data(data_recipient_ban);

    while (1) {
        // take data from computer; 20 is len of string for full date
        long int system_time = time(NULL);
        char* time_now = (char*)malloc(20 * sizeof(char));
        strftime(time_now, 20, "%d.%m.%Y %H:%M:%S", localtime(&system_time));

        printf("\n\n\ndate now is %s\n\n\n", time_now);

        // check DB
        data_recipient_ban = check_DB(data_recipient_ban, time_now);
        print_data(data_recipient_ban);
        free(time_now);

        sleep(seconds_sleep);
    }

    //free
    free(data_recipient_ban);
    
    return 0;
}