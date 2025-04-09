#include "sc_list.h"

SC_LIST(int)

int main() {
  sc_list_int ints = sc_list_int_alloc();

  for (unsigned int i = 0; i < 130; i++)
    sc_list_int_add(&ints, 8);

  sc_list_int_remove_at(ints, 0);

  sc_foreach(i, sc_list_int_count(ints)) {
    printf("ints[%d] = %d  ", i, ints[i]);
    if (i % 3 == 0) {
      putchar('\n');
    }
  }

  sc_list_int_free(ints);
}
