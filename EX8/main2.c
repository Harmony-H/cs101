#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define COUNTER_FILE "counter.bin"

void init_file() {
    int write_array[1] = {0};
    FILE *fp = fopen(COUNTER_FILE, "r");
    if (fp == NULL) {
        FILE *tmpfp = fopen(COUNTER_FILE, "wb+");
        fwrite(write_array, sizeof(int), 1, tmpfp);
        fclose(tmpfp);
    } else {
        fclose(fp);
    }
}

int get_counter() {
    int read_array[1];
    FILE *tmpfp = fopen(COUNTER_FILE, "rb");
    fread(read_array, sizeof(int), 1, tmpfp);
    fclose(tmpfp);
    return read_array[0];
}

void set_counter(int counter) {
    int write_array[1];
    write_array[0] = counter;
    FILE *tmpfp = fopen(COUNTER_FILE, "wb");
    fwrite(write_array, sizeof(int), 1, tmpfp);
    fclose(tmpfp);
}

void generate_lotto(int n, int counter) {
    srand(1);

    char lotto_file[32];
    snprintf(lotto_file, sizeof(lotto_file), "lotto[%05d].txt", counter);
    FILE *fp = fopen(lotto_file, "wt+");

    fprintf(fp, "========= lotto649 =========\n");
    fprintf(fp, "========+ No.%05d +========\n", counter);

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%B %d %Y", tm_info);
    fprintf(fp, "======%s======\n", buffer);

    for (int i = 1; i <= n; i++) {
        int used[72] = {0};
        fprintf(fp, "[%d]:", i);
        for (int j = 0; j < 7;) {
            int temp = rand() % 69 + 1;
            if (used[temp] == 0) {
                used[temp] = 1;
                fprintf(fp, " %02d", temp);
                j++;
            }
        }
        fprintf(fp, "\n");
    }

    for (int i = n + 1; i <= 5; i++) {
        fprintf(fp, "[%d]: __ __ __ __ __ __ __\n", i);
    }

    fprintf(fp, "========= csie@CGU =========\n");
    fclose(fp);

}

int main() {
    int counter;
    init_file();
    counter = get_counter();

    int n;
    scanf("%d", &n);

    generate_lotto(n, ++counter);
    set_counter(counter);

    return 0;
}