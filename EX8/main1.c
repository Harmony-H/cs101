#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generate_lotto(int n) {
    srand(1); // use current time as seed

    FILE *fp = fopen("lotto.txt", "wt+");
    if (!fp) {
        printf("無法開啟 lotto.txt\n");
        return;
    }

    // Get date in "Month day year" format
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char date_str[64];
    strftime(date_str, sizeof(date_str), "%B %d %Y", t); // e.g. "March 13 2025"

    fprintf(fp, "========= lotto649 =========\n");

    for (int i = 1; i <= n; i++) {
        int used[70] = {0};
        fprintf(fp, "%s: [%d]:", date_str, i);
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
        fprintf(fp, "%s: [%d]: __ __ __ __ __ __ __\n", date_str, i);
    }

    fprintf(fp, "========= csie@CGU =========\n");
    fclose(fp);
}

void check_lotto(int n) {
    int num1, num2, num3;
    printf("請輸入中獎號碼三個:");
    scanf("%1d%1d%1d", &num1, &num2, &num3); // handles input like 579
    num1 = num1 * 1; // just to use the same type
    num2 = num2 * 1;
    num3 = num3 * 1;

    printf("\n輸入中獎號碼為:%02d %02d %02d\n", num1, num2, num3);

    FILE *fp = fopen("lotto.txt", "r");
    if (!fp) {
        printf("無法開啟 lotto.txt\n");
        return;
    }

    printf("以下為中獎彩卷:\n");

    char line[128];
    while (fgets(line, sizeof(line), fp)) {
        // only lines with actual ticket numbers
        if (strchr(line, '[')) {
            int nums[7], ticket_num;
            char date_str[64];
            int matched = 0;

            if (sscanf(line, "%[^:]: [%d]: %d %d %d %d %d %d %d",
                       date_str, &ticket_num,
                       &nums[0], &nums[1], &nums[2],
                       &nums[3], &nums[4], &nums[5], &nums[6]) == 9) {

                for (int i = 0; i < 7; i++) {
                    if (nums[i] == num1 || nums[i] == num2 || nums[i] == num3)
                        matched++;
                }

                if (matched > 0) {
                    printf("售出時間: %s: [%d]:", date_str, ticket_num);
                    for (int i = 0; i < 7; i++)
                        printf(" %02d", nums[i]);
                    printf("\n");
                }
            }
        }
    }

    fclose(fp);
}

int main() {
    int n;
    scanf("%d", &n);

    generate_lotto(n);
    check_lotto(n);

    return 0;
}
