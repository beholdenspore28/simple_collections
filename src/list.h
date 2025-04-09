#ifndef SC_LIST_H
#define SC_LIST_H

#include <stdio.h>
#include <stdlib.h>

#define SC_LIST_INITIAL_CAPACITY (128)
#define sc_foreach(i, cap) for (unsigned int i = 0; i < cap; i++)

typedef size_t sc_list_size;

typedef struct {
  sc_list_size capacity;
  sc_list_size count;
} sc_list_meta_data;

#define SC_LIST(type)                                                          \
  typedef int *sc_list_##type;                                                 \
                                                                               \
  static inline sc_list_##type sc_list_##type##_alloc(void) {                  \
    void *ptr = malloc(sizeof(sc_list_meta_data) +                             \
                       (sizeof(int) * SC_LIST_INITIAL_CAPACITY));              \
    sc_list_meta_data *data = (sc_list_meta_data *)ptr;                        \
    data->capacity = SC_LIST_INITIAL_CAPACITY;                                 \
    data->count = 0;                                                           \
                                                                               \
    return (sc_list_##type)(data + 1);                                         \
  }                                                                            \
                                                                               \
  static inline void sc_list_##type##_free(sc_list_##type list) {              \
    sc_list_meta_data *data = ((sc_list_meta_data *)(list)) - 1;               \
    free(data);                                                                \
  }                                                                            \
                                                                               \
  static inline sc_list_size sc_list_##type##_count(                           \
      const sc_list_##type list) {                                             \
    sc_list_meta_data *data = ((sc_list_meta_data *)(list)) - 1;               \
    return data->count;                                                        \
  }                                                                            \
                                                                               \
  static inline void sc_list_##type##_add(sc_list_##type *list,                \
                                          const int element) {                 \
    sc_list_meta_data *data = ((sc_list_meta_data *)(*list)) - 1;              \
    const sc_list_size new_count = data->count + 1;                            \
    const sc_list_size new_capacity = data->capacity * 2;                      \
    if (new_count >= data->capacity) {                                         \
      data = realloc(data, sizeof(sc_list_meta_data) +                         \
                               (sizeof(int) * new_capacity));                  \
      *list = (sc_list_##type)(data + 1);                                      \
    }                                                                          \
    (*list)[data->count] = element;                                            \
    data->count = new_count;                                                   \
  }                                                                            \
                                                                               \
  static inline void sc_list_##type##_remove_at(const sc_list_##type list,     \
                                                const sc_list_size index) {    \
    sc_list_meta_data *data = ((sc_list_meta_data *)(list)) - 1;               \
    (list)[index] = (list)[data->count - 1];                                   \
    data->count--;                                                             \
  }

#endif // SC_SC_LIST_H
