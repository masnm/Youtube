#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void panic ( char * message ) {
    fprintf ( stderr, "Error : %s\n", message );
    exit ( 1 );
}

int get_random ( int low, int high ) {
    if ( low < 0 ) panic ( "Low can't be negative" );
    if ( high < 0 ) panic ( "High can't be negative" );
    if ( low >= high ) panic ( "Low must be less than high" );

    int range = high - low;
    int number = rand() % range;
    return (number + low);
}

typedef struct node node;
struct node {
    int value;
    node* next;
};

node * get_new_node ( int value ) {
    node * next = (node*) malloc ( sizeof ( node ) );
    if ( next == NULL ) panic ( "New node creation failed" );
    next->value = value;
    next->next = NULL;
    return next;
}

void insert_value ( node ** root, int value ) {
    node ** head = root;
    while ( (*head) != NULL ) {
        head = &(*head)->next;
    }
    *head = get_new_node ( value );
}

void print_list ( node * root ) {
    if ( root == NULL ) {
        printf ( "NULL\n" );
        return;
    }
    printf ( "%d -> ", root->value );
    print_list ( root->next );
}

void free_list ( node ** root ) {
    if ( (*root) == NULL ) {
        return;
    }
    free_list ( &(*root)->next );
    free ( *root );
    (*root) = NULL;
}

void swap ( int * l, int * r ) {
    int t = *l;
    *l = *r;
    *r = t;
}

void sort_list ( node * root ) {
    bool changed = true;
    while ( changed ) {
        changed = false;
        node * head = root;
        for ( ; head->next != NULL; head = head->next ) {
            node * im_next = head->next;
            if ( head->value > im_next->value ) {
                changed = true;
                swap ( &head->value, &im_next->value );
            }
        }
    }
}

node * find_intersections ( node * first, node * second ) {
    node * intersections = NULL;
    while ( first != NULL && second != NULL ) {
        if ( first->value == second->value ) {
            insert_value ( &intersections, first->value );
            first = first->next;
            second = second->next;
        } else if ( first->value < second->value ) {
            first = first->next;
        } else if ( first->value > second->value ) {
            second = second->next;
        }
    }
    return intersections;
}

int main ( int args, char ** argv ) {
    (void) args;
    (void) argv;

    srand ( time(0) );

    int first_list_length = get_random ( 5, 10 );
    int second_list_length = get_random ( 5, 10 );

    node *first_list = NULL, *second_list = NULL;

    for ( int i = 0; i < first_list_length; i++ ) {
        insert_value ( &first_list, get_random ( 0, 10 ) );
    }

    for ( int i = 0; i < second_list_length; i++ ) {
        insert_value ( &second_list, get_random ( 0, 10 ) );
    }

    sort_list ( first_list );
    sort_list ( second_list );

    node * intersections = find_intersections ( first_list, second_list );

    print_list ( first_list );
    print_list ( second_list );
    print_list ( intersections );

    free_list ( &first_list );
    free_list ( &second_list );

    return 0;
}
