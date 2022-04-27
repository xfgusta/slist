# slist - a simple singly-linked list

An easy to use singly-linked list implementation for the C programming language.

**Example**

```c
#include <stdio.h>
#include <slist.h>

int main() {
    List *langs = NULL;

    langs = list_append_args(langs, "C", "Perl", "Python");
    langs = list_reverse(langs);

    list_foreach(langs, (fn) puts, NULL);

    printf("len(langs) = %u\n", list_length(langs));

    list_free(langs);
}
```

```
Python
Perl
C
len(langs) = 3
```

**Brief summary**

+ `NULL` is considered to be the empty list, there is no need to use [`list_new`](#new) to create a [`List *`](#list)

+ To add elements, use [`list_append`](#append), [`list_append_args`](#append_args), [`list_prepend`](#prepend), [`list_prepend_args`](#prepend_args), [`list_insert`](#insert), [`list_concat`](#concat) or [`list_concat_args`](#concat_args)

+ To copy a list, use [`list_copy`](#copy)

+ To remove elements, use [`list_remove`](#remove)

+ To get the number of elements, use [`list_length`](#length)

+ To find elements, use [`list_data`](#data), [`list_next`](#next), [`list_find`](#find), [`list_at`](#at), [`list_data_at`](#data_at) or [`list_last`](#last)

+ To find the index of an element, use [`list_index`](#index)

+ To reverse a list, use [`list_reverse`](#reverse)

+ To call a function for each element, use [`list_foreach`](#foreach) or [`list_cycle`](#cycle)

+ To free the list, use [`list_free`](#free)

_Note that this implementation is not thread safe and uses `malloc` and `free` to manage memory, which can be inefficient._

# API

* [Types](#types)
    * [List](#list)
    * [fn](#fn)
    * [cmp_fn](#cmp_fn)
* [Functions and function-like macros](#functions-and-function-like-macros)
    * [new](#new)
    * [data](#data)
    * [next](#next)
    * [free](#free)
    * [append](#append)
    * [append_args](#append_args)
    * [prepend](#prepend)
    * [prepend_args](#prepend_args)
    * [insert](#insert)
    * [concat](#concat)
    * [concat_args](#concat_args)
    * [remove](#remove)
    * [length](#length)
    * [is_empty](#is_empty)
    * [find](#find)
    * [index](#index)
    * [at](#at)
    * [data_at](#data_at)
    * [last](#last)
    * [copy](#copy)
    * [reverse](#reverse)
    * [foreach](#foreach)
    * [cycle](#cycle)

## Types

### List

```c
struct List {
    void *data;
    List *next;
}
```

Each element in the singly-linked list is a `List` struct. The `data` holds the element's data and `next` points to the next element in the list.

### fn

```c
void (*fn) (void *data, void *user_data)
```

Specifies the type of functions passed to [`list_foreach`](#foreach) and [`list_cycle`](#cycle). The `data` holds the element's data and `user_data` is the user data passed to [`list_foreach`](#foreach) and [`list_cycle`](#cycle).

### cmp_fn

```c
int (*cmp_fn) (void *data, void *user_data)
```

Specifies the type of functions passed to [`list_find`](#find). The `data` holds the element's data and `user_data` is the user data passed to [`list_find`](#find).

### Functions and function-like macros

All function and function-like macro names are prefixed with `list_`, except the `_list_append_args`, `_list_prepend_args` and `_list_concat_args` functions. Function names that do not start with `list_` are not supposed to be used directly.

### new

```c
List *list_new(void *data, List *next)
```

Gets a pointer to a newly-allocated `List` element with its `data` and `next` members assigned, or `NULL` on failure. This function is used internally.

### data

```c
#define list_data(list) ((list) ? (list)->data : NULL)
```

Gets the data of `list`, or `NULL` if `list` is empty. It is also valid to use `list->data`.

### next

```c
#define list_next(list) ((list) ? (list)->next : NULL)
```

Gets the next element of `list`, or `NULL` if `list` is empty. It is also valid to use `list->next`.

### free

```c
void list_free(List *list)
```

Frees all allocated memory used by `list`. If `list` elements contain allocated memory, you should free them manually first.

### append

```c
List *list_append(List *list, void *data)
```

Adds a new element on to the end of `list`. It returns the new start of `list`, or `NULL` on failure.

### append_args

```c
#define list_append_args(list, ...) _list_append_args(list, __VA_ARGS__, NULL)
```

Adds a list of elements on to the end of `list`. It returns the new start of `list`, or `NULL` on failure.

### prepend

```c
List *list_prepend(List *list, void *data)
```

Adds a new element on to the start of `list`. It returns the new start of `list`, or `NULL` on failure.

### prepend_args

```c
#define list_prepend_args(list, ...) _list_prepend_args(list, __VA_ARGS__, NULL)
```

Adds a list of elements on to the start of `list`. It returns the new start of `list`, or `NULL` on failure.

### insert

```c
List *list_insert(List *list, void *data, int index)
```

Inserts a new element into `list` at `index`. It returns the new start of `list`, or `NULL` on failure. If `index` is negative or greater than the length of `list`, it inserts the new element on to the end of `list`.

### concat

```c
List *list_concat(List *dest_list, List *src_list)
```

Adds `src_list` on to the end of `dest_list`. It returns the new start of `list`.

### concat_args

```c
#define list_concat_args(dest_list, ...) _list_concat_args(dest_list, __VA_ARGS__, NULL)
```

Adds a list of lists on to the end of `dest_list`. It returns the new start of `list`.

### remove

```c
List *list_remove(List *list, void *data)
```

Removes an element from `list`. If two or more elements contain the same `data`, only the first one is removed.

### length

```c
unsigned list_length(List *list)
```

Gets the number of elements in `list`.

### is_empty

```c
#define list_is_empty(list) ((list) == NULL)
```

Checks if `list` is empty.

### find

```c
List *list_find(List *list, void *user_data, cmp_fn func)
```

Finds the element in `list` which contains the `data`, or `NULL` if it is not found. It calls `func` if `func` is not `NULL`, and `func` must return a non-zero value if the element is found. The `user_data` can be `NULL` and it is passed to `func`.

### index

```c
int list_index(List *list, void *data)
```

Gets the position of the element in `list` containing `data`, or `-1` if it is not found.

### at

```c
List *list_at(List *list, int index)
```

Gets the element at `index` in `list`, or `NULL` if it is not found.

### data_at

```c
void *list_data_at(List *list, int index)
```

Gets the data of the element at `index` in `list`, or `NULL` if it is not found.

### last

```c
List *list_last(List *list)
```

Gets the last element in `list`, or `NULL` if it has no elements. 

### copy

```c
List *list_copy(List *list)
```

Copies `list`. The actual data is not copied, only the pointers to data. It is a shallow copy.

### reverse

```c
List *list_reverse(List *list)
```

Reverses `list`.

### foreach

```c
void list_foreach(List *list, fn func, void *user_data)
```

Calls `func` for each element of `list`. The `user_data` user data can be `NULL` and it is passed to `func`.

### cycle

```c
void list_cycle(List *list, fn func, void *user_data, int n)
```

Calls `func` for each element of `list` repeatedly `n` times or forever if `n` is less or equal to zero. The `user_data` user data can be `NULL` and it is passed to `func`.
