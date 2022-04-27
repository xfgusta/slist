#ifndef SLIST_H
#define SLIST_H

#define list_data(list) ((list) ? (list)->data : NULL)
#define list_next(list) ((list) ? (list)->next : NULL)
#define list_is_empty(list) ((list) == NULL)
#define list_append_args(list, ...) _list_append_args(list, __VA_ARGS__, NULL)
#define list_prepend_args(list, ...) _list_prepend_args(list, __VA_ARGS__, NULL)
#define list_concat_args(dest_list, ...) _list_concat_args(dest_list, __VA_ARGS__, NULL)

typedef void (*fn) (void *data, void *user_data);
typedef int (*cmp_fn) (void *data, void *user_data);
typedef struct List List;

struct List {
    void *data;
    List *next;
};

List *list_new(void *data, List *next);

void list_free(List *list);

unsigned list_length(List *list);

List *list_append(List *list, void *data);

List *_list_append_args(List *list, ... /*, NULL */);

List *list_prepend(List *list, void *data);

List *_list_prepend_args(List *list, ... /*, NULL */);

List *list_insert(List *list, void *data, int index);

List *list_concat(List *dest_list, List *src_list);

List *_list_concat_args(List *dest_list, ... /*, NULL */);

List *list_remove(List *list, void *data);

List *list_find(List *list, void *user_data, cmp_fn func);

int list_index(List *list, void *data);

List *list_at(List *list, int index);

void *list_data_at(List *list, int index);

List *list_last(List *list);

List *list_copy(List *list);

List *list_reverse(List *list);

void list_foreach(List *list, fn func, void *user_data);

void list_cycle(List *list, fn func, void *user_data, int n);

#endif