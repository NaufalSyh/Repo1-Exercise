/*======================================
    Tugas	: Double Linked List
======================================*/

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *nxt;
    struct node *prev;  // Pointer ke node sebelumnya
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

//=====================================================
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

//=====================================================
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
        pNew->nxt = *head;
        pNew->prev = NULL; // Node baru tidak memiliki prev
        if (*head != NULL) {
            (*head)->prev = pNew; // Menghubungkan prev node yang ada
        }
        *head = pNew; // Update head
    } else {
        printf("Alokasi memori gagal");
        getchar();
    }
}

//=================================================
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
    while (pCur != NULL && pCur->data != poss) {
        pCur = pCur->nxt;
    }

    if (pCur == NULL) {
        printf("\nNode tidak ditemukan\n");
        getchar();
        return;
    }

    pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL) {
        printf("\nAlokasi memori gagal\n");
        getchar();
        return;
    }
    
    pNew->data = angka;
    pNew->nxt = pCur->nxt;
    pNew->prev = pCur; // Node baru menunjuk ke pCur

    if (pCur->nxt != NULL) {
        pCur->nxt->prev = pNew; // Menghubungkan node setelah pCur ke pNew
    }
    pCur->nxt = pNew; // Menghubungkan pCur ke pNew
}

//==================================
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
    pNew->nxt = NULL; // Node baru di akhir, tidak ada next
    pNew->prev = NULL; // Akan diperbarui nanti

    if (*head == NULL) {
        *head = pNew; // List kosong
    } else {
        pCur = *head;
        while (pCur->nxt != NULL) {
            pCur = pCur->nxt; // Menemukan node terakhir
        }
        pCur->nxt = pNew; // Menghubungkan node terakhir dengan node baru
        pNew->prev = pCur; // Node baru menunjuk ke node sebelumnya
    }
}

//=====================================
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

//====================================================
void delAwal(node **head) {
    if (*head == NULL) {
        printf("List kosong\n");
        return;
    }
    node *temp = *head;
    *head = (*head)->nxt;
    if (*head != NULL) {
        (*head)->prev = NULL; // Update prev untuk node baru di depan
    }
    free(temp);
    printf("Node di awal berhasil dihapus.\n");
}

//===================================================
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

    node *pCur = *head;

    while (pCur != NULL && pCur->data != data) {
        pCur = pCur->nxt;
    }

    if (pCur == NULL) {
        printf("Data %d tidak ditemukan\n", data);
        return;
    }

    if (pCur->prev != NULL) {
        pCur->prev->nxt = pCur->nxt; // Menghubungkan node sebelumnya ke node setelahnya
    } else {
        *head = pCur->nxt; // Mengupdate head jika node yang dihapus adalah head
    }

    if (pCur->nxt != NULL) {
        pCur->nxt->prev = pCur->prev; // Menghubungkan node setelahnya ke node sebelumnya
    }

    free(pCur);
    printf("Node dengan data %d berhasil dihapus.\n", data);
}

//=================================================
void delAkhir(node **head) {
    if (*head == NULL) {
        printf("List kosong\n");
        return;
    }

    node *pCur = *head;

    if (pCur->nxt == NULL) { // Jika hanya ada satu node
        free(pCur);
        *head = NULL;
        printf("Node di akhir berhasil dihapus.\n");
        return;
    }

    while (pCur->nxt != NULL) {
        pCur = pCur->nxt; // Menemukan node terakhir
    }

    pCur->prev->nxt = NULL; // Menghapus node terakhir
    free(pCur);
    printf("Node di akhir berhasil dihapus.\n");
}

//===================================================
node *cariData(node *head, int angka) {
    node *pCur = head;
    while (pCur != NULL) {
        if (pCur->data == angka) {
            return pCur;
        }
        pCur = pCur->nxt;
    }
    return NULL;
}

//==================================================
void tampilData(node *head) {
    node *pWalker = head;

    system("cls");
    printf("Data dalam linked list :\n");
    if (pWalker == NULL) {
        printf("Linked list kosong\n");
    } else {
        while (pWalker != NULL) {
            printf("%d <-> ", pWalker->data); // Menggunakan <-> untuk menunjukkan dua arah
            pWalker = pWalker->nxt;
        }
        printf("NULL\n");
    }
}

//============================================================
int countData(node *head) {
    system("cls");
    tampilData(head);
    int count = 0;
    node *pWalker = head;

    while (pWalker != NULL) {
        count++;
        pWalker = pWalker->nxt;
    }

    return count;
}

//=================================================
int sumData(node *head) {
    system("cls");
    tampilData(head);
    int sum = 0;
    node *pWalker = head;

    while (pWalker != NULL) {
        sum += pWalker->data;
        pWalker = pWalker->nxt;
    }

    return sum;
}

