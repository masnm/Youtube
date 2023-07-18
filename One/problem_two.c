#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node {
    int value;
    node * left;
    node * right;
};

node * get_new_node ( int key ) {
    node * next = (node*) malloc ( sizeof ( node ) );
    if ( next == NULL ) {
        fprintf ( stderr, "Node creation failed\n" );
        exit ( 1 );
    }
    next -> value = key;
    next -> left = NULL;
    next -> right = NULL;
    return next;
}

void tree_insert ( node ** root, int key ) {
    if ( (*root) == NULL ) {
        *root = get_new_node ( key );
    } else if ( (*root)->value >= key ) {
        tree_insert ( &(*root)->left, key );
    } else {
        tree_insert ( &(*root)->right, key );
    }
}

void tree_print ( node * root ) {
    if ( root == NULL ) return;
    printf ( "value : %d \n", root->value );
    printf ( "Going to left child of %d\n", root->value );
    tree_print ( root->left );
    printf ( "Going to right child of %d\n", root->value );
    tree_print ( root->right );
}

void tree_cleanup ( node ** root ) {
    if ( (*root) == NULL ) return;
    tree_cleanup ( &(*root)->left );
    tree_cleanup ( &(*root)->right );
    free ( (*root) );
    (*root) = NULL;
}

#define KEYS_ARR_CAP 1024
int keys_arr[KEYS_ARR_CAP];
int keys_arr_size = 0;

void saved_keys_print ( void ) {
    printf ( "Printing Keys: " );
    for ( int i = 0; i < keys_arr_size; i++ ) {
        printf ( "%d ", keys_arr[i] );
    }
    puts ( "" );
}

void save_key ( int key ) {
    if ( keys_arr_size >= KEYS_ARR_CAP ) return;
    keys_arr[keys_arr_size++] = key;
}

void tree_save_keys ( node * root ) {
    if ( root == NULL ) return;
    save_key ( root->value );
    tree_save_keys ( root->left );
    tree_save_keys ( root->right );
}

void tree_add_keys ( node * root ) {
    if ( root == NULL ) return;
    int sum = 0;
    for ( int i = 0; i < keys_arr_size; i++ )
        if ( keys_arr[i] > root->value )
            sum += keys_arr[i];
    root->value += sum;
    tree_add_keys ( root->left );
    tree_add_keys ( root->right );
}

int main ( int argc, char ** argv ) {
    (void) argc;
    (void) argv;

    int key_count, key;

    printf ( "Enter how many keys in the bst : " );
    scanf ( "%d", &key_count );

    printf ( "Please Enter %d keys : ", key_count );
    node * root = NULL;
    for ( int i = 0; i < key_count; i++ ) {
        scanf ( "%d", &key );
        tree_insert ( &root, key );
    }

    tree_save_keys ( root );
    // saved_keys_print ();
    tree_add_keys ( root );
    tree_print ( root );

    tree_cleanup ( &root );

    return 0;
}
