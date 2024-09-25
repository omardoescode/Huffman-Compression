#include <locale.h>
#include <stdio.h>
#include <wchar.h>

int main(void) {
  setlocale(LC_ALL, "");
  wchar_t wc;
  printf("Hello");
  while (WEOF != (wc = fgetwc(stdin))) {
    printf("%lc: %d\n", wc, wc);
    if (wc < 0) {
      puts("Wrong!!!");
      return 1;
    }
  }
  return 0;
}
