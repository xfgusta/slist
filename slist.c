#include <stdlib.h>
#include <stdarg.h>
#include "slist.h"

List *list_new(void *data, List *next) {
    List *list;

    list = malloc(sizeof(List));
    if(!list)
        return NULL;

    list->data = data;
    list->next = next;

    return list;
}

void list_free(List *list) {
    for(List *next_list; list; list = next_list) {
        next_list = list->next;
        free(list);
    }
}

unsigned list_length(List *list) {
    unsigned length = 0;

    while(list) {
        length++;
        list = list->next;
    }

    return length;
}

List *list_append(List *list, void *data) {
    List *new_list;

    new_list = list_new(data, NULL);
    if(!new_list)
        return NULL;

    return list_concat(list, new_list);
}

List *_list_append_args(List *list, ... /*, NULL */) {
    void *data = NULL;
    va_list args;

    va_start(args, list);

    while((data = va_arg(args, void *))) {
        list = list_append(list, data);
        if(!list)
            break;
    }

    va_end(args);

    return list;
}

List *list_prepend(List *list, void *data) {
    List *new_list;

    new_list = list_new(data, list);
    if(!new_list)
        return NULL;

    return new_list;
}

List *_list_prepend_args(List *list, ... /*, NULL */) {
    void *data = NULL;
    va_list args;

    va_start(args, list);

    while((data = va_arg(args, void *))) {
        list = list_prepend(list, data);
        if(!list)
            break;
    }

    va_end(args);

    return list;
}

List *list_insert(List *list, void *data, int index) {
    List *prev_list = NULL;
    List *new_list;

    if(index == 0)
        return list_prepend(list, data);
    else if(index < 0)
        return list_append(list, data);

    if(!list) {
        new_list = list_new(data, NULL);
        if(!new_list)
            return NULL;

        return new_list;
    }

    prev_list = list_at(list, index - 1);
    if(!prev_list)
        return list_append(list, data);

    new_list = list_new(data, prev_list->next);
    if(!new_list)
        return NULL;

    prev_list->next = new_list;

    return list;
}

List *list_concat(List *dest_list, List *src_list) {
    List *last_list;

    if(!dest_list)
        return src_list;

    last_list = list_last(dest_list);
    last_list->next = src_list;

    return dest_list;
}

List *_list_concat_args(List *dest_list, ... /*, NULL */) {
    List *src_list = NULL;
    va_list args;

    va_start(args, dest_list);

    while((src_list = va_arg(args, List *)))
        dest_list = list_concat(dest_list, src_list);

    va_end(args);

    return dest_list;
}

List *list_remove(List *list, void *data) {
    List **prev_list = &list;
    List *current_list = NULL;

    while(*prev_list) {
        current_list = *prev_list;
        if(current_list->data == data) {
            *prev_list = current_list->next;
            free(current_list);
            break;
        } else
            prev_list = &current_list->next;
    }

    return list;
}

List *list_find(List *list, void *user_data, cmp_fn func) {
    while(list) {
        if(!func) {
            if(list->data == user_data)
                return list;
        } else {
            if(func(list->data, user_data))
                return list;
        }

        list = list->next;
    }

    return NULL;
}

int list_index(List *list, void *data) {
    for(int index = 0; list; index++) {
        if(list->data == data)
            return index;

        list = list->next;
    }

    return -1;
}

List *list_at(List *list, int index) {
    while(list && index-- > 0)
        list = list->next;

    return list;
}

void *list_data_at(List *list, int index) {
    List *new_list;

    new_list = list_at(list, index);
    if(!new_list)
        return NULL;

    return new_list->data;
}

List *list_last(List *list) {
    if(list) {
        while(list->next)
            list = list->next;
    }

    return list;
}

List *list_copy(List *list) {
    List *new_list = NULL;
    List *last_list;

    if(!list)
        return NULL;

    new_list = list_new(list->data, NULL);
    if(!new_list)
        return NULL;

    last_list = new_list;

    for(list = list->next; list; list = list->next) {
        last_list->next = list_append(last_list->next, list->data);
        if(!last_list->next)
            return NULL;
    }

    return new_list;
}

List *list_reverse(List *list) {
    List *prev_list = NULL;
    List *next_list;

    while(list) {
        next_list = list->next;
        list->next = prev_list;
        prev_list = list;
        list = next_list;
    }

    return prev_list;
}

void list_foreach(List *list, fn func, void *user_data) {
    if(!func)
        return;

    while(list) {
        (*func)(list->data, user_data);
        list = list->next;
    }
}

void list_cycle(List *list, fn func, void *user_data, int n) {
    if(!func)
        return;

    if(n <= 0) {
        while(1)
            list_foreach(list, (fn) func, user_data);
    }

    while(n-- > 0)
        list_foreach(list, (fn) func, user_data);
}
