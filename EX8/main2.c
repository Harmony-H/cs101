#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n;
    scanf("%d", &n);
    srand(time(NULL));

    // --- 讀取或建立紀錄單數的 binary file ---
    FILE *count_fp;
    int counter = 0;
    count_fp = fopen("counter.bin", "rb");
    if (count_fp == NULL) {
        // 如果沒有檔案，表示第一次執行
        counter = 1;
    } else {
        fread(&counter, sizeof(int), 1, count_fp);
        fclose(count_fp);
        counter++;  // 每執行一次，單數加一
    }

    // --- 將新的單數寫回 counter.bin ---
    count_fp = fopen("counter.bin", "wb");
    fwrite(&counter, sizeof(int), 1, count_fp);
    fclose(count_fp);

    // --- 檔名設定 ---
    char filename[32];
    sprintf(filename, "lotto[%05d].txt", counter);
    FILE *fp = fopen(filename, "wt+");

    // --- 取得目前時間 ---
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    fprintf(fp, "========= lotto649 =========\n");
    fprintf(fp, "========+ No.%05d +========\n", counter);
    fprintf(fp, "= %s", asctime(t));  // 顯示時間，例如 "Mon Mar 7 10:11:14 2022"

    // --- 產生號碼 ---
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

    // --- 未使用的組數以 __ 填充 ---
    for (int i = n + 1; i <= 5; i++) {
        fprintf(fp, "[%d]: __ __ __ __ __ __ __\n", i);
    }

    fprintf(fp, "========= csie@CGU =========\n");
    fclose(fp);
    return 0;
}
