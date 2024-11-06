/*======================================
    ETS STRUKTUR DATA
======================================*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct mhs{
	char nama[50];
    char jenis_kelamin;
    struct mhs* nxt;	
};

typedef struct mhs mhs;

void tambahmhs(mhs** pNew, char* nama, char jenis_kelamin);
void delMhs(mhs** head, char* nama, int* cnt);
void addCircle(mhs** head, char* nama, char jenis_kelamin, int* cnt);
void pCircle(mhs* head);
void gabungcircle(mhs* circle_L, mhs* circle_P, mhs** mrgCircle);
void pMerge(mhs* mrgCircle);


int main(){
	mhs* circle_L = NULL;
	mhs* circle_P = NULL;
	mhs* mrgCircle = NULL; 
	int pilih;
	int cntL = 0, cntP = 0;
    char nama[50], jenis_kelamin;
    
	do {
        system("cls");
        printf("Masukkan pilihan anda :\n");
        printf("1. Tambahkan Mahasiswa/i\n");
        printf("2. Hapus Mahasiswa/i\n");
        printf("3. Tampilkan Cirle Keseluruhan\n");
        printf("4. Tampilkan Circle Kecil\n");
    	printf("0. Keluar\n");
    	printf("Pilih opsi: ");
        fflush(stdin);
        scanf("%d", &pilih);

        switch (pilih) {
            case 1:
                printf("Masukkan nama: ");
                scanf("%s", nama);
                printf("Masukkan jenis kelamin (L/P): ");
                scanf(" %c", &jenis_kelamin);

                if (jenis_kelamin == 'L') {
                    addCircle(&circle_L, nama, jenis_kelamin, &cntL);
                } else if (jenis_kelamin == 'P') {
                    addCircle(&circle_P, nama, jenis_kelamin, &cntP);
                } else {
                    printf("Jenis kelamin tidak valid.\n");
                }
                break;
                
            case 2:
                printf("Masukkan nama yang ingin dihapus: ");
                scanf("%s", nama);
                printf("Jenis kelamin (L/P): ");
                scanf(" %c", &jenis_kelamin);

                if (jenis_kelamin == 'L') {
                    delMhs(&circle_L, nama, &cntL);
                } else if (jenis_kelamin == 'P') {
                    delMhs(&circle_P, nama, &cntP);
                } else {
                    printf("Jenis kelamin tidak valid.\n");
                }
                break;

            case 3:
                gabungcircle(circle_L, circle_P, &mrgCircle);
                pMerge(mrgCircle);
                break;

            case 4:
                printf("Lingkaran Laki-Laki:\n");
                pCircle(circle_L);
                printf("Lingkaran Perempuan:\n");
                pCircle(circle_P);
                break;
                
            case 0:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    } while (pilih != '0');
    getchar();
    return 0;
};

void tambahmhs(mhs** pNew, char* nama, char jenis_kelamin) {
    *pNew = (mhs*)malloc(sizeof(mhs));
    if (*pNew == NULL) {
        printf("Gagal mengalokasikan memori.\n");
        exit(1);
    }
    strcpy((*pNew)->nama, nama);
    (*pNew)->jenis_kelamin = jenis_kelamin;
    (*pNew)->nxt = NULL;
}

void delMhs(mhs** head, char* nama, int* cnt) {
    if (*head == NULL) {
        printf("Lingkaran kosong, tidak ada yang bisa dihapus.\n");
        return;
    }

    mhs* temp = *head;
    mhs* pPre = NULL;

    do {
        if (strcmp(temp->nama, nama) == 0) {
            if (pPre == NULL) {
                mhs* pCur = *head;
                while (pCur->nxt != *head) {
                    pCur = pCur->nxt;
                }
                *head = temp->nxt;
                pCur->nxt = *head;
            } else {
                pPre->nxt = temp->nxt;
            }
            free(temp);
            (*cnt)--;
            printf("%s berhasil keluar dari lingkaran.\n", nama);
            return;
        }
        pPre = temp;
        temp = temp->nxt;
    } while (temp != *head);

    printf("%s tidak ditemukan dalam lingkaran.\n", nama);
}

void addCircle(mhs** head, char* nama, char jenis_kelamin, int* cnt) {
    system("cls");
    if (*cnt >= 20) {
        printf("Lingkaran Circle sudah penuh! Tidak bisa menambah %s.\n", nama);
        return;
    }

    mhs* newMhs = NULL;
    tambahmhs(&newMhs, nama, jenis_kelamin);

    if (*head == NULL) {
        *head = newMhs;
        newMhs->nxt = *head;
    } else {
        mhs* temp = *head;
        do {
            if (strcmp(temp->nama, nama) == 0) {
                printf("%s sudah ada dalam lingkaran.\n", nama);
                free(newMhs);
                return;
            }
            temp = temp->nxt;
        } while (temp != *head);

        // Tambah mahasiswa lain di akhir
        mhs* last = *head;
        while (last->nxt != *head) {
            last = last->nxt;
        }
        last->nxt = newMhs;
        newMhs->nxt = *head;
        (*cnt)++;
        printf("%s berhasil masuk ke lingkaran.\n", nama);
    }
}

void pCircle(mhs* head) {
    system("cls");
    if (head == NULL) {
        printf("Lingkaran kosong.\n");
        return;
    }

    mhs* temp = head;
    do {
        printf("%s (%c) -> ", temp->nama, temp->jenis_kelamin);
        temp = temp->nxt;
    } while (temp != head);
    printf("CIRCLE\n");
}

void gabungcircle(mhs* circle_L, mhs* circle_P, mhs** mrgCircle) {
    system("cls");
    if (circle_L == NULL && circle_P == NULL) {
        printf("Kedua lingkaran circle kosong.\n Tidak ada mahasiswa yang gabung.\n");
        return;
    }

    mhs* lastL = NULL;
    mhs* lastP = NULL;

    if (circle_L != NULL) {
        lastL = circle_L;
        while (lastL->nxt != circle_L) {
            lastL = lastL->nxt;
        }
    }

    if (circle_P != NULL) {
        lastP = circle_P;
        while (lastP->nxt != circle_P) {
            lastP = lastP->nxt;
        }
    }

    if (circle_L != NULL && circle_P != NULL) {
        lastL->nxt = circle_P;
        lastP->nxt = circle_L;
        *mrgCircle = circle_L;
    } else if (circle_L != NULL) {
        *mrgCircle = circle_L;
    } else if (circle_P != NULL) {
        *mrgCircle = circle_P;
    }
}

void pMerge(mhs* mrgCircle) {
    system("cls");
    if (mrgCircle == NULL) {
        printf("Lingkaran gabungan kosong.\n");
        return;
    }

    mhs* temp = mrgCircle;
    do {
        printf("%s (%c) -> ", temp->nama, temp->jenis_kelamin);
        temp = temp->nxt;
    } while (temp != mrgCircle);
    printf("CIRCLE\n");
}

