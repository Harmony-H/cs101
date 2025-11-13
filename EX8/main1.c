#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generate_lotto(int n) {
    srand(1);

    FILE *fp;
    fp = fopen("lotto.txt", "wt+");

    fprintf(fp, "========= lotto649 =========\n");
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

void check_lotto(int n) {
    printf("請輸入中獎號碼三個: ");
    int win_num[3];
    scanf("%d %d %d", &win_num[0], &win_num[1], &win_num[2]);
    printf("輸入中獎號碼為: %02d %02d %02d\n", win_num[0], win_num[1], win_num[2]);
    printf("以下為中獎彩卷:\n");

    FILE *read_fp;
    read_fp = fopen("lotto.txt", "r");

    char line_buffer[256];
    char date_str[256] = "";

    while (fgets(line_buffer, sizeof(line_buffer), read_fp) != NULL) {
        if (strstr(line_buffer, "======") != NULL && strstr(line_buffer, "csie") == NULL) {
            strcpy(date_str, line_buffer);
            date_str[strcspn(date_str, "\n")] = 0;
        }

        if (line_buffer[0] == '[') {
            int lotto_id;
            int ticket_nums[7];
            int parsed_count = sscanf(line_buffer, "[%d]: %d %d %d %d %d %d %d",
                                      &lotto_id, &ticket_nums[0], &ticket_nums[1],
                                      &ticket_nums[2], &ticket_nums[3], &ticket_nums[4],
                                      &ticket_nums[5], &ticket_nums[6]);
            if (parsed_count == 8) {
                int match_count = 0;
                for (int i = 0; i < 7; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (ticket_nums[i] == win_num[j]) {
                            match_count++;
                        }
                    }
                }
                if (match_count > 0) {
                    line_buffer[strcspn(line_buffer, "\n")] = 0;
                    printf("售出時間%s: %s\n", date_str, line_buffer);
                }
            }
        }
    }

    fclose(read_fp);
}

int main() {
    int n;
    scanf("%d", &n);
    generate_lotto(n);
    check_lotto(n);
    return 0;
}