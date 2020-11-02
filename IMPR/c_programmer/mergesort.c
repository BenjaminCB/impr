#include <stdio.h> 
#include <stdlib.h> 

void Merge(int L[], int start, int slut, int midt);
void MergeSort(int L[], int start, int slut);
void printList(int L[], int size);

int main(void){ 
    int L[] = { 5, 3, 8, 1, 6, 10, 7, 2, 4, 9 }; 
    int L_size = sizeof(L) / sizeof(L[0]); 
        
    printf("Givet listen \n"); 
    printList(L, L_size); 
    
    MergeSort(L, 0, L_size - 1); 
    
    printf("Er den sorterede liste \n"); 
    printList(L, L_size); 
    return 0; 
} 

void Merge(int L[], int start, int slut, int midt){
    /* Start med at kopiere de to dellister ind i to nye lister L1 og L2, så vi ikke sletter nogle elementer fra L når vi begynder at flette elementerne derind */
    int size1 = midt - start + 1;
    int size2 = slut - midt;
    int i, j, k;
    
    int L1[size1], L2[size2];

    for (i = 0; i < size1; i++) {
        L1[i] = L[start + i]; 
    }
    for (j = 0; j < size2; j++) {
        L2[j] = L[midt + 1 + j]; 
    }

    /* Herefter skal vi kopiere elementer fra L1 og L2 ind på pladserne i L mellem start og slut men i sorteret rækkefølge */
    i = 0;
    j = 0;
    k = 1;
    while (i < size1 && j < size2) { 
        if (L1[i] <= L2[j]) { 
            L[k] = L1[i]; 
            i++; 
        } 
        else { 
            L[k] = L2[j]; 
            j++; 
        } 
        k++; 
    } 

    while (i < size1) { 
        L[k] = L1[i]; 
        i++; 
        k++; 
    } 
  
    while (j < size2) { 
        L[k] = L2[j]; 
        j++; 
        k++; 
    } 
}

void MergeSort(int L[], int start, int slut){
    /* Udfyld her */
    if (start < slut) {
        int midt = start + (slut - start) / 2;
        MergeSort(L, start, midt);
        MergeSort(L, midt + 1, slut);
        Merge(L, start, slut, midt);
    }
}

void printList(int L[], int size){ 
  int i; 
  for (i = 0; i < size; i++) 
    printf("%d ", L[i]); 
  printf("\n"); 
} 