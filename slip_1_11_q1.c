#include <stdio.h>

#define max 20

int frames[max], ref[max], mem[max][max], faults = 0, sp = 0, n, m, count[max];

void accept() {
    int i;
    printf("Enter number of frames: ");
    scanf("%d", &n);
    printf("Enter number of references: ");
    scanf("%d", &m);
    printf("Enter reference string:\n");
    for (i = 0; i < m; i++) {
        printf("[%d] = ", i);
        scanf("%d", &ref[i]);
    }
}


void disp() {
    int i, j;
    printf("\nReference String:\n");
    for (i = 0; i < m; i++)
        printf("%3d", ref[i]);
    printf("\n\nMemory Frames:\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (mem[i][j])
                printf("%3d", mem[i][j]);
            else
                printf("  -");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", faults);
}


int search(int pno) {
    int i;
    for (i = 0; i < n; i++) {
        if (frames[i] == pno)
            return i;
    }
    return -1;
}


int get_lfu(int sp) {
    int i, min_i, min = 9999;
    i = sp;
    do {
        if (count[i] < min) {
            min = count[i];
            min_i = i;
        }
        i = (i + 1) % n;
    } while (i != sp);
    return min_i;
}


void lfu() {
    int i, j, k;
    
  
    for (i = 0; i < m && sp < n; i++) {
        k = search(ref[i]);
        if (k == -1) {  
            frames[sp] = ref[i]; 
            count[sp] = 1; 
            faults++; 
            sp++; 
            for (j = 0; j < n; j++)
                mem[j][i] = frames[j];
        } else {
            count[k]++; 
        }
    }

    
    sp = 0;
    for (; i < m; i++) {
        k = search(ref[i]);
        if (k == -1) {  
            sp = get_lfu(sp); 
            frames[sp] = ref[i]; 
            count[sp] = 1; 
            faults++; 
            for (j = 0; j < n; j++)
                mem[j][i] = frames[j];
        } else {
            count[k]++;
        }
    }
}

int main() {
 
    for (int i = 0; i < max; i++) {
        frames[i] = 0;
        count[i] = 0;
    }

    accept(); 
    lfu();    
    disp();   
    return 0;
}
