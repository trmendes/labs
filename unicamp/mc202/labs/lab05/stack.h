#ifndef __STACK_H__
#define __STACK_H__

#define ERR_STACK_NULL -1
#define ERR_NULL_DATA  -2
#define SUCCESS         0
typedef struct st_node_s {
    int                id;
    struct st_node_s * next;
} st_node_t;

typedef struct stack_s {
    int        len;
    st_node_t * top;
} stack_t;

stack_t * st_create  ();
void      st_destroy (stack_t *s);
int       st_pop     (stack_t *s);
int       st_push    (stack_t *s, int data);
int       st_len     (stack_t *s);
void      st_print   (stack_t *s);
#endif

