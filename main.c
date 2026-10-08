#include <stdio.h>

struct UserAccount {
    int user_id;
    char username[50];
    int plan_type;
    int days_overdue;
    int active_devices;
};

int main() {
    struct UserAccount users[100];
    int n;
    int i;
    int total_revenue = 0;
    int downgraded_count = 0;

    /* Nhap so luong tai khoan */
    do {
        printf("Nhap so luong tai khoan (1-100): ");
        scanf("%d", &n);

        if (n < 1 || n > 100) {
            printf("Loi: So luong tai khoan phai tu 1 den 100!\n");
        }
    } while (n < 1 || n > 100);

    /* Nhap thong tin tung tai khoan */
    for (i = 0; i < n; i++) {
        printf("\n=== NHAP TAI KHOAN %d ===\n", i + 1);

        printf("Ma tai khoan: ");
        scanf("%d", &users[i].user_id);

        printf("Ten tai khoan: ");
        scanf("%49s", users[i].username);

        /* Kiem tra plan_type */
        do {
            printf("Loai goi (1-Free, 2-Personal, 3-Family): ");
            scanf("%d", &users[i].plan_type);

            if (users[i].plan_type < 1 || users[i].plan_type > 3) {
                printf("Loi: Loai goi phai tu 1 den 3!\n");
            }
        } while (users[i].plan_type < 1 ||
                 users[i].plan_type > 3);

        /* Kiem tra days_overdue */
        do {
            printf("So ngay no cuoc: ");
            scanf("%d", &users[i].days_overdue);

            if (users[i].days_overdue < 0) {
                printf("Loi: So ngay no cuoc khong duoc am!\n");
            }
        } while (users[i].days_overdue < 0);

        /* Kiem tra active_devices */
        do {
            printf("So thiet bi dang ket noi: ");
            scanf("%d", &users[i].active_devices);

            if (users[i].active_devices < 0) {
                printf("Loi: So thiet bi khong duoc am!\n");
            }
        } while (users[i].active_devices < 0);
    }

    /* Xu ly du lieu */
    for (i = 0; i < n; i++) {
        int actual_fee = 0;

        /*
         * Quy tac 1:
         * Neu no cuoc >= 3 ngay thi ha cap ve Free
         */
        if (users[i].days_overdue >= 3) {
            users[i].plan_type = 1;
            downgraded_count++;
        }

        /*
         * Quy tac 2:
         * Chi ap dung phu thu neu sau khi xu ly
         * tai khoan van la goi Personal
         */
        if (users[i].plan_type == 2) {
            actual_fee = 120000;

            if (users[i].active_devices > 1) {
                actual_fee +=
                        (users[i].active_devices - 1) * 30000;
            }
        } else if (users[i].plan_type == 3) {
            actual_fee = 250000;
        } else {
            actual_fee = 0;
        }

        total_revenue += actual_fee;
    }

    /* Xuat bao cao */
    printf("\n\n===============================================================\n");
    printf("           BAO CAO DOI SOAT TAI KHOAN SAAS\n");
    printf("===============================================================\n");

    printf("%-8s %-20s %-8s %-12s %-12s %-18s\n",
           "Ma TK",
           "Ten TK",
           "Ma Goi",
           "Thiet Bi",
           "No Cuoc",
           "Phi Thuc Thu");

    printf("---------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        int actual_fee = 0;

        if (users[i].plan_type == 2) {
            actual_fee = 120000;

            if (users[i].active_devices > 1) {
                actual_fee +=
                        (users[i].active_devices - 1) * 30000;
            }
        } else if (users[i].plan_type == 3) {
            actual_fee = 250000;
        } else {
            actual_fee = 0;
        }

        printf("%-8d %-20s %-8d %-12d %-12d %-18d\n",
               users[i].user_id,
               users[i].username,
               users[i].plan_type,
               users[i].active_devices,
               users[i].days_overdue,
               actual_fee);
    }

    printf("---------------------------------------------------------------\n");
    printf("Tong doanh thu thuc thu: %d VND\n", total_revenue);
    printf("Tong so tai khoan bi ha cap: %d\n", downgraded_count);
    printf("===============================================================\n");

    return 0;
}