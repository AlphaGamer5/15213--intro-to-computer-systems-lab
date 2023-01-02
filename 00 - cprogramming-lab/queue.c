/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 *
 * TODO: fill in your name and Andrew ID
 * @author XXX <XXX@andrew.cmu.edu>
 */

#include "queue.h"
#include "harness.h"

#include <stdlib.h>
#include <string.h>
#include<stdio.h>

/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    queue_t *q = malloc(sizeof(queue_t));

    if(q == NULL) {
        return NULL;
    }
    /* What if malloc returned NULL? */
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/**
    char *t;
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if(q == NULL) {
        return;
    }
    list_ele_t *current = q->head, *next = NULL;
    while (current) {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }

    free(q);
}

int strlength(const char* c) {
    int len = 0;
    while(c[len] != '\0') {
        len++;
    }

    return len;
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {
    if(q == NULL) {
        return false;
    }

    list_ele_t *newh = malloc(sizeof(list_ele_t));;
    /* What should you do if the q is NULL? */

    if(!newh) {
        return false;
    }

    if(q->size == 0) {
        q->tail = newh;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */

    char *t = malloc(sizeof(char) * strlength(s));
    if(!t) {
        free(newh);
        return false;
    }
    strcpy(t, s);
    newh->value = t;
    newh->next = q->head;
    q->head = newh;
    q->size++;
    return true;
}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if(q == NULL){
        return false;
    }

    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));

    if(newt == NULL) {
        return false;
    }

    if(q->size == 0) {
        q->head = newt;
    }

    char *t = malloc(sizeof(char) * strlength(s));
    if (!t) {
        free(newt);
        return false;
    }
    strcpy(t, s);
    newt->value = t;
    newt->next = NULL;
    q->tail->next = newt;
    q->tail = newt;
    q->size++;

    return true;
}

/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {
    /* You need to fix up this code. */
    if(q == NULL || q->head == NULL) {
        return false;
    }


    list_ele_t *tmp = q->head;
    q->head = q->head->next;
    q->size--;

    // memcpy(buf, tmp->value, bufsize);

    if(buf) {
        int i = 0;
        for (; i < bufsize - 1 && *(tmp->value + i) != '\0'; i++) {
            *(buf + i) = *(tmp->value + i);
        }

        *(buf + i) = '\0';
    }

    if(tmp == q->tail)
        q->tail = NULL;

    free(tmp->value);
    free(tmp);
    return true;
}

/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if(q == NULL) {
        return 0;
    }

    return q->size;
}

/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    if(q == NULL || q->head == NULL)
        return;
    /* You need to write the code for this function */
    list_ele_t *current = q->head, *next = q->head->next, *tmp;
    while(next) {
        tmp = next->next;
        next->next = current;
        current = next;
        next = tmp;
    }

    q->head->next = NULL;
    q->tail = q->head;
    q->head = current;
}
