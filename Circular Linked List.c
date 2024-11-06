/*======================================
    Tugas	: Circular Linked List
======================================*/

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *nxt;
};
typedef struct node node;

void tambahData(node **head);
void tambahAwal(node **head);
void tambahTengah(node **head);
void tambahAkhir(node **head);
void delData(node **head);
void delAwal(node **head);
void delTengah(node **head);
void delAkhir(node **head);
void tampilData(node *head);
int countData(node *head);
int sumData(node *head);
node *cariData(node *head, int angka);

int main() {
    node *head = NULL;
    int pilih;
    int angka;

    do {
        system("cls");
        printf("Masukkan pilihan anda :\n");
        printf("1. Tambahkan data\n");
        printf("2. Hapus data\n");
        printf("3. Tampilkan semua data\n");
        printf("4. Mencari data\n");
        printf("5. Tampilkan jumlah data\n");
        printf("6. Tampilkan hasil penjumlahan semua data\n");
        printf("Masukkan pilihan anda (Tekan 'x' untuk keluar) : ");
        fflush(stdin);
        scanf("%d", &pilih);

        switch (pilih) {
            case 1:
                tambahData(&head);
                getchar();
                break;
            case 2:
                delData(&head);
                getchar();
                break;
            case 3:
                tampilData(head);
                getchar();
                break;
            case 4:
                system("cls");
                printf("\nMasukkan data yang dicari : ");
                scanf("%d", &angka);
                node *hasil = cariData(head, angka);
                tampilData(head);
                if (hasil != NULL) {
                    printf("Data %d ditemukan\n", hasil->data);
                } else {
                    printf("Data %d tidak ditemukan\n", angka);
                }
                getchar();
                break;
            case 5:
                printf("\nJumlah data dalam linked list : %d\n", countData(head));
                getchar();
                break;
            case 6:
                printf("\nHasil penjumlahan semua data : %d\n", sumData(head));
                getchar();
                break;
        }
    } while (pilih != 'x');

    return 0;
}

void tambahData(node **head) {
    int pilih;
    system("cls");
    tampilData(*head);
    printf("\nPilih opsi tambah data :\n");
    printf("1. Tambah data di awal\n");
    printf("2. Tambah data di tengah list\n");
    printf("3. Tambah data di akhir\n");
    printf("Masukkan pilihan : ");
    fflush(stdin);
    scanf("%d", &pilih);

    if (pilih == 1) {
        tambahAwal(head);
        return;
    } else if (pilih == 2) {
        tambahTengah(head);
        return;
    } else if (pilih == 3) {
        tambahAkhir(head);
        return;
    } else {
        printf("Mohon Maaf Yang Anda Input salah!");
        return;
    }
}

void tambahAwal(node **head) {
    int angka;
    node *pNew;
    system("cls");
    printf("Masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &angka);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = angka;

        if (*head == NULL) { // List kosong
            pNew->nxt = pNew; // menunjuk ke dirinya sendiri
            *head = pNew;
        } else {
            node *temp = *head;
            while (temp->nxt != *head) {
                temp = temp->nxt; // Menemukan node terakhir
            }
            temp->nxt = pNew; // Menghubungkan node terakhir dengan node baru
            pNew->nxt = *head; // Node baru menunjuk ke head
            *head = pNew; // Update head
        }
    } else {
        printf("Alokasi memori gagal");
        getchar();
    }
}

void tambahTengah(node **head) {
    int poss, angka;
    node *pNew, *pCur;
    system("cls");
    tampilData(*head);
    printf("\nPosisi penyisipan setelah data bernilai : ");
    fflush(stdin);
    scanf("%d", &poss);
    printf("\nMasukkan Bilangan : ");
    fflush(stdin);
    scanf("%d", &angka);

    pCur = *head;
    if (pCur == NULL) {
        printf("\nList kosong, tambahkan data di awal.\n");
        return;
    }

    do {
        if (pCur->data == poss) {
            pNew = (node *)malloc(sizeof(node));
            if (pNew == NULL) {
                printf("\nAlokasi memori gagal\n");
                return;
            }
            pNew->data = angka;
            pNew->nxt = pCur->nxt;
            pCur->nxt = pNew;
            return;
        }
        pCur = pCur->nxt;
    } while (pCur != *head);

    printf("\nNode tidak ditemukan\n");
}

void tambahAkhir(node **head) {
    int angka;
    node *pNew, *pCur;
    system("cls");
    printf("Masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &angka);

    pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL) {
        printf("Alokasi memori gagal");
        getchar();
        return;
    }

    pNew->data = angka;
    if (*head == NULL) {
        pNew->nxt = pNew; // menunjuk ke dirinya sendiri
        *head = pNew;
    } else {
        pCur = *head;
        while (pCur->nxt != *head) {
            pCur = pCur->nxt; // Menemukan node terakhir
        }
        pCur->nxt = pNew; // Menghubungkan node terakhir dengan node baru
        pNew->nxt = *head; // Node baru menunjuk ke head
    }
}

void delData(node **head) {
    int pilih;
    system("cls");
    tampilData(*head);
    printf("\nPilih opsi hapus :\n");
    printf("1. Hapus data di awal\n");
    printf("2. Hapus data di tengah\n");
    printf("3. Hapus data di akhir\n");
    printf("Masukkan pilihan : ");
    fflush(stdin);
    scanf("%d", &pilih);

    if (pilih == 1) {
        delAwal(head);
        return;
    } else if (pilih == 2) {
        delTengah(head);
        return;
    } else if (pilih == 3) {
        delAkhir(head);
        return;
    } else {
        printf("Input salah!");
        return;
    }
}

void delAwal(node **head) {
    if (*head == NULL) {
        printf("List kosong\n");
        return;
    }

    node *temp = *head;
    if (temp->nxt == *head) { // Jika hanya ada satu node
        free(temp);
        *head = NULL;
    } else {
        node *last = *head;
        while (last->nxt != *head) {
            last = last->nxt; // Menemukan node terakhir
        }
        *head = (*head)->nxt; // Update head
        last->nxt = *head; // Node terakhir menunjuk ke node baru head
        free(temp);
    }
    printf("Node di awal berhasil dihapus.\n");
}

void delTengah(node **head) {
    if (*head == NULL) {
        printf("List kosong\n");
        return;
    }

    tampilData(*head);
    int data;
    printf("\nMasukkan nilai data yang ingin dihapus : ");
    fflush(stdin);
    scanf("%d", &data);

    node *pCur = *head, *pPrev = NULL;
    do {
        if (pCur->data == data) {
            if (pPrev == NULL) { // Node yang ingin dihapus adalah head
                delAwal(head);
                return;
            }
            pPrev->nxt = pCur->nxt; // Menghubungkan node sebelumnya ke node setelah pCur
            free(pCur);
            printf("Node dengan data %d berhasil dihapus.\n", data);
            return;
        }
        pPrev = pCur;
        pCur = pCur->nxt;
    } while (pCur != *head);

    printf("Data %d tidak ditemukan\n", data);
}

void delAkhir(node **head) {
    if (*head == NULL) {
        printf("List kosong\n");
        return;
    }

    node *pCur = *head, *pPrev = NULL;

    if (pCur->nxt == *head) { // Jika hanya ada satu node
        free(pCur);
        *head = NULL;
        printf("Node di akhir berhasil dihapus.\n");
        return;
    }

    while (pCur->nxt != *head) {
        pPrev = pCur;
        pCur = pCur->nxt;
    }

    pPrev->nxt = *head; // Menghubungkan node sebelumnya ke head
    free(pCur);
    printf("Node di akhir berhasil dihapus.\n");
}

node *cariData(node *head, int angka) {
    node *pCur = head;
    if (head == NULL) {
        return NULL;
    }
    do {
        if (pCur->data == angka) {
            return pCur;
        }
        pCur = pCur->nxt;
    } while (pCur != head);
    return NULL;
}

void tampilData(node *head) {
    node *pWalker = head;
    system("cls");
    printf("Data dalam linked list :\n");
    if (pWalker == NULL) {
        printf("Linked list kosong\n");
    } else {
        do {
            printf("%d -> ", pWalker->data);
            pWalker = pWalker->nxt;
        } while (pWalker != head);
        printf("(kembali ke head)\n");
    }
}

int countData(node *head) {
    int count = 0;
    if (head == NULL) {
        return count;
    }
    node *pWalker = head;
    do {
        count++;
        pWalker = pWalker->nxt;
    } while (pWalker != head);
    return count;
}

int sumData(node *head) {
    int sum = 0;
    if (head == NULL) {
        return sum;
    }
    node *pWalker = head;
    do {
        sum += pWalker->data;
        pWalker = pWalker->nxt;
    } while (pWalker != head);
    return sum;
}
