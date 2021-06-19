#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Сравнение эффективности разных методов сортировки

int chng = 0, comp = 0;

void print(long long * a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%lld ", a[i]);
    }
    printf("\n");
}

int check(long long * a, long long * s_a, int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != s_a[i]) return 0;
    }
    return 1;
}

int compare(const void * a, const void * b) {
    if(*(long long int*) a - *(long long int*) b < 0)
        return -1;
    if(*(long long int*) a - *(long long int*) b > 0)
        return 1;
    return 0;
}

int compare_1(const void * a, const void * b) {
    if(*(long long int*) a - *(long long int*) b > 0)
        return -1;
    if(*(long long int*) a - *(long long int*) b < 0)
        return 1;
    return 0;
}

void fill(long long * a, long long * sorted_a, int n) {
    for (int i = 0; i < n; i++) {
        sorted_a[i] = a[i];
    }
    qsort(sorted_a, n, sizeof(long long), compare);
}

void cpy(long long * a, long long * c, int n) {
    for (int i = 0; i < n; i++) {
        c[i] = a[i];
    }
}


void create(long long * a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = (rand() * rand() * rand() * rand() * rand());
    }
    printf("\n");
}

void bubble(long long *a, int n) {
  for (int i = 0; i < n - 1; i++) {
      for (int j = n - 1; j > i; j--) {
          if (a[j - 1] > a[j]) {
              long long temp = a[j - 1];
              a[j - 1] = a[j];
              a[j] = temp;
              chng ++;
          }
          comp++;
      }
  }
}

void sift(long long *a, int root, int bottom) {
  int maxChild;
  int done = 0;
  while ((root * 2 <= bottom) && (!done)) {
      if (root * 2 == bottom) {
          maxChild = root * 2;
      }
      else if (a[root * 2] > a[root * 2 + 1]) {
          maxChild = root * 2;
          comp++;
      }
      else {
          maxChild = root * 2 + 1;
          comp++;
      }
    if (a[root] < a[maxChild]) {
        long long temp = a[root];
        a[root] = a[maxChild];
        a[maxChild] = temp;
        root = maxChild;
        chng++;
    }
    else {
      done = 1;
    }
    comp ++;
    
  }
}

void heapsrt(long long *a, int n) {
  for (int i = (n / 2) - 1; i >= 0; i--)
    sift(a, i, n - 1);
  for (int i = n - 1; i >= 1; i--)
  {
    long long temp = a[0];
    a[0] = a[i];
    a[i] = temp;
    sift(a, 0, i - 1);
    chng++;
  }
}


int main(void) {
    srand( (unsigned int) time(NULL) );
    int n;
    scanf("%d", &n);
    long long * a = malloc(n * sizeof(long long));
    long long * copy = malloc(n * sizeof(long long));
    long long * sorted_a = malloc(n * sizeof(long long));
    
    create(a, n);
    //print(a, n);
    //printf("\n");
    fill(a, sorted_a, n);
    //print(sorted_a, n);
    //printf("\n");
    cpy(a, copy, n);
    bubble(copy, n);
    //print(copy, n);
    printf("Метод пузырька случайный массив №1: ");
    check(copy,sorted_a, n) ? printf("да") : printf("нет");
    printf("\nЗначения счетчиков сравнения и перемещения: %d %d\n", comp, chng);
    chng = comp = 0;
    cpy(a, copy, n);
    heapsrt(copy, n);
    printf("Пирамидальный метод случайный массив №1: ");
    check(copy,sorted_a, n) ? printf("да") : printf("нет");
    printf("\nЗначения счетчиков сравнения и перемещения: %d %d\n", comp, chng);
    chng = comp = 0;
    
    create(a, n);
    //print(a, n);
    //printf("\n");
    fill(a, sorted_a, n);
    //print(sorted_a, n);
    //printf("\n");
    cpy(a, copy, n);
    bubble(copy, n);
    //print(copy, n);
    //printf("\n");
    printf("\nМетод пузырька случайный массив №2: ");
    check(copy,sorted_a, n) ? printf("да") : printf("нет");
    printf("\nЗначения счетчиков сравнения и перемещения: %d %d\n", comp, chng);
    chng = comp = 0;
    cpy(a, copy, n);
    heapsrt(copy, n);
    printf("Пирамидальный метод случайный массив №2: ");
    check(copy,sorted_a, n) ? printf("да") : printf("нет");
    printf("\nЗначения счетчиков сравнения и перемещения: %d %d\n", comp, chng);
    chng = comp = 0;
    
    
    create(a, n);
    qsort(a, n, sizeof(long long), compare);
    //print(a, n);
    fill(a, sorted_a, n);
    cpy(a, copy, n);
    bubble(copy, n);
    printf("Метод пузырька упорядоченный массив: ");
    check(copy,sorted_a, n) ? printf("да") : printf("нет");
    printf("\nЗначения счетчиков сравнения и перемещения: %d %d\n", comp, chng);
    chng = comp = 0;
    cpy(a, copy, n);
    heapsrt(copy, n);
    printf("\nПирамидальный метод упорядоченный массив: ");
    check(copy, sorted_a, n) ? printf("да") : printf("нет");
    printf("\nЗначения счетчиков сравнения и перемещения: %d %d\n", comp, chng);
    chng = comp = 0;
    
    
    create(a, n);
    qsort(a, n, sizeof(long long), compare_1);
    //print(a, n);
    fill(a, sorted_a, n);
    cpy(a, copy, n);
    bubble(copy, n);
    printf("Метод пузырька упорядоченный в обратном порядке массив: ");
    check(copy,sorted_a, n) ? printf("да") : printf("нет");
    printf("\nЗначения счетчиков сравнения и перемещения: %d %d\n", comp, chng);
    chng = comp = 0;
    cpy(a, copy, n);
    heapsrt(copy, n);
    printf("\nПирамидальный метод упорядоченный в обратном порядке массив: ");
    check(copy, sorted_a, n) ? printf("да") : printf("нет");
    printf("\nЗначения счетчиков сравнения и перемещения: %d %d\n", comp, chng);
    chng = comp = 0;
    
    return 0;
}
