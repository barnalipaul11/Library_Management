#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

struct Book {
    char title[50];
    char author[50];
    int id;
    int borrowed;
};

struct Library {
    struct Book books[MAX_BOOKS];
    int num_books;
};

void print_book(struct Book book) {
    printf("ID: %d\n", book.id);
    printf("Title: %s\n", book.title);
    printf("Author: %s\n", book.author);
    printf("Borrowed: %d\n", book.borrowed);
    printf("\n");
}

void print_library(struct Library library) {
    int i;
    printf("Library Inventory\n");
    printf("=================\n");
    for (i = 0; i < library.num_books; i++) {
        print_book(library.books[i]);
    }
}

void add_book(struct Library *library, char *title, char *author, int id) {
    struct Book new_book;
    strcpy(new_book.title, title);
    strcpy(new_book.author, author);
    new_book.id = id;
    new_book.borrowed = 0;
    library->books[library->num_books] = new_book;
    library->num_books++;
}

int find_book(struct Library library, int id) {
    int i;
    for (i = 0; i < library.num_books; i++) {
        if (library.books[i].id == id) {
            return i;
        }
    }
    return -1;
}

void borrow_book(struct Library *library, int id) {
    int book_index = find_book(*library, id);
    if (book_index == -1) {
        printf("Book not found in the library.\n");
    } else if (library->books[book_index].borrowed) {
        printf("This book is already borrowed.\n");
    } else {
        library->books[book_index].borrowed = 1;
        printf("You have successfully borrowed the book: %s\n", library->books[book_index].title);
    }
}

void return_book(struct Library *library, int id) {
    int book_index = find_book(*library, id);
    if (book_index == -1) {
        printf("Book not found in the library.\n");
    } else if (!library->books[book_index].borrowed) {
        printf("This book has not been borrowed.\n");
    } else {
        library->books[book_index].borrowed = 0;
        printf("You have successfully returned the book: %s\n", library->books[book_index].title);
    }
}

int main() {
    struct Library library;
    library.num_books = 0;
    
    add_book(&library, "The Great Gatsby", "F. Scott Fitzgerald", 1001);
    add_book(&library, "To Kill a Mockingbird", "Harper Lee", 1002);
    add_book(&library, "1984", "George Orwell", 1003);
    
    print_library(library);
    
    borrow_book(&library, 1002);
    borrow_book(&library, 1002);
    
    return_book(&library, 1002);
    return_book(&library, 1002);
    
    print_library(library);
    
    return 0;
}
