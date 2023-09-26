
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_BOOKS 5



struct Book {
    char identifier[9];
    char name[100];
    char author[100];
    int year;
    bool is_loaned;
    char customer_name[100];
    int loan_count;
    struct Book* next; // pointer to the next book node in the linked list
};

struct Book* head = NULL;
int num_books = 0;

void display_menu() {
    printf("\n==================================\n");
    printf("Welcome to the Library Management System\n");
    printf("==================================\n\n");
    printf("Please select an option:\n\n");
    printf("1. Add a new book to the library\n");
    printf("2. Allow a customer to borrow a book\n");
    printf("3. Allow a customer to return a book\n");
    printf("4. Delete an old book from the library stock\n");
    printf("5. View all books\n");
    printf("6. View a specific book\n");
    printf("7. View details of most popular and least popular books\n");
    printf("8. My own option\n");
    printf("9. Exit the system\n\n");
}

void add_book() {
    if (num_books >= MAX_BOOKS) {
        printf("Cannot add more books. Maximum limit reached.\n");
        return;
    }

    struct Book* new_book = (struct Book*) malloc(sizeof(struct Book));
if (new_book == NULL) {
    printf("Error: Could not allocate memory for new book.\n");
    return;
}
new_book->next = NULL;

    printf("Enter book details:\n");

    // Get book identifier
    printf("Identifier (in format xxxx-xxxx): ");
    scanf("%8s", new_book->identifier);

    // Get book name
    printf("Name: ");
    scanf("%99s", new_book->name);

    // Get book author
    printf("Author: ");
    scanf("%99s", new_book->author);

    // Get publication year
    printf("Publication year: ");
    scanf("%d", &new_book->year);

    if (new_book->year < 2017) {
        printf("Error: Publication year cannot be earlier than 2017.\n");
        free(new_book);
        return;
    }

    // Check if the book identifier already exists
for (int i = 0; i < num_books; i++) {
    if (strcmp(head->identifier, new_book->identifier) == 0) {
        printf("Error: A book with the same identifier already exists in the library.\n");
        return;
    }
}

    // Set initial loan status and loan count
    new_book->is_loaned = false;
    strcpy(new_book->customer_name, "");
    new_book->loan_count = 0; // set loan count to 0

    // Set loan status if the book has been loaned out
    printf("Has the book been loaned out? (Enter 1 for Yes, 0 for No): ");
    int is_loaned;
    scanf("%d", &is_loaned);
    if (is_loaned == 1) {
        new_book->is_loaned = true;
        printf("Enter customer name: ");
        scanf("%99s", new_book->customer_name);
        new_book->loan_count = 1; // increase loan count by 1
    }

    // Add the new book to the library
    

    if (head == NULL) {
    head = new_book;
} else {
    struct Book* curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = new_book;
}

    printf("Book added successfully.\n");
}

void delete_book() {
    // Check if there are any books in the library
    if (head == NULL) {
        printf("There are no books in the library.\n");
        return;
    }

    // Get book identifier to be deleted
    char identifier[9];
    printf("Enter book identifier to be deleted: ");
    scanf("%8s", identifier);

    // Find the book to be deleted
    struct Book* curr = head;
    struct Book* prev = NULL;
    while (curr != NULL && strcmp(curr->identifier, identifier) != 0) {
        prev = curr;
        curr = curr->next;
    }

    // Check if the book was found
    if (curr == NULL) {
        printf("Book not found.\n");
        return;
    }

    // Check if the book can be deleted (i.e., published before 2010)
    if (curr->year >= 2010) {
        printf("Error: Book cannot be deleted. It was published in or after 2010.\n");
        return;
    }

    // Delete the book
    if (prev == NULL) {
        head = curr->next;
    } else {
        prev->next = curr->next;
    }
    free(curr);

    printf("Book deleted successfully.\n");
}

void view_all_books(struct Book* head) {
    struct Book* current = head;
    while (current != NULL) {
        printf("Name: %s\n", current->name);
        printf("Author: %s\n", current->author);
        printf("Year published: %d\n\n", current->year);
        current = current->next;
    }
}

   void view_specific_book(struct Book* head) {
    char identifier[9];
    printf("Enter book identifier: ");
    scanf("%8s", identifier);
    struct Book* current = head;
    while (current != NULL) {
        if (strcmp(current->identifier, identifier) == 0) {
            printf("Name: %s\n", current->name);
            printf("Author: %s\n", current->author);
            printf("Year Published: %d\n", current->year);
            return;
        }
        current = current->next;
    }
    printf("Book not found.\n");
}

void borrow_book(struct book* head, int identifier, char* customer_name) {
  struct book* current = head;

  // Search for the book by identifier
  while (current != NULL && current->identifier != identifier) {
    current = current->next;
  }

  // If book is found and not already loaned, update the book information
  if (current != NULL && !current->is_loaned) {
    current->is_loaned = true;
    strcpy(current->customer_name, customer_name);
    current->loan_count++;

    printf("Book with identifier %d has been successfully borrowed by %s.\n", identifier, customer_name);
  } else {
    printf("Error: Book with identifier %d cannot be borrowed.\n", identifier);
  }
}

void return_book(struct book_node **head_ref) {
    char identifier[MAX_ID_LEN];
    char customer_name[MAX_NAME_LEN];
    int is_found = 0;
    struct book_node *current = *head_ref;
    
    printf("Enter the book identifier: ");
    scanf("%s", identifier);
    printf("Enter the customer name: ");
    scanf("%s", customer_name);
    
    // Search for the book in the linked list
    while (current != NULL) {
        if (strcmp(current->book.identifier, identifier) == 0) {
            is_found = 1;
            // Check if the book is loaned by the given customer
            if (current->book.is_loaned && strcmp(current->book.customer_name, customer_name) == 0) {
                current->book.is_loaned = 0;
                printf("Book '%s' has been returned by customer '%s'.\n", identifier, customer_name);
                break;
            } else {
                printf("Book '%s' is not loaned by customer '%s'.\n", identifier, customer_name);
                break;
            }
        }
        current = current->next;
    }
    
    if (!is_found) {
        printf("Book with identifier '%s' not found.\n", identifier);
    }
}

void view_popularity_of_books() {
    if (head == NULL) {
        printf("No books in library.\n");
    } else {
        Book* most_popular_book = head;
        Book* least_popular_book = head;
        Book* current = head;
        while (current != NULL) {
            if (current->loan_count > most_popular_book->loan_count) {
                most_popular_book = current;
            }
            if (current->loan_count < least_popular_book->loan_count) {
                least_popular_book = current;
            }
            current = current->next;
        }
        printf("Most popular book:\n");
        printf("Identifier\tName\tAuthor\tYear\tLoan Count\n");
        printf("%d\t%s\t%s\t%d\t%d\n", most_popular_book->identifier, most_popular_book->name, most_popular_book->author, most_popular_book->year, most_popular_book->loan_count);
        printf("Least popular book:\n");
        printf("Identifier\tName\tAuthor\tYear\tLoan Count\n");
        printf("%d\t%s\t%s\t%d\t%d\n", least_popular_book->identifier, least_popular_book->name, least_popular_book->author, least_popular_book->year, least_popular_book->loan_count);
    }
}

// Function to read books from file and add them to the linked list
void read_books_from_file(Book **head) {
    FILE *file = fopen("book.dat", "rb");
    if (file == NULL) {
        printf("Database file does not exist. Please input books to create a new database.\n");
        return;
    }
    while (!feof(file)) {
        Book *new_book = (Book *) malloc(sizeof(Book));
        fread(new_book, sizeof(Book), 1, file);
        new_book->next = NULL;
        if (*head == NULL) {
            *head = new_book;
        } else {
            Book *current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_book;
        }
    }
    fclose(file);
    printf("Database file has been read and loaded into the linked list.\n");
}

// Function to write books from linked list to file
void write_books_to_file(Book *head) {
    FILE *file = fopen("book.dat", "wb");
    if (file == NULL) {
        printf("Error: Could not open file for writing.\n");
        return;
    }
    while (head != NULL) {
        fwrite(head, sizeof(Book), 1, file);
        head = head->next;
    }
    fclose(file);
    printf("All books have been written to the database file.\n");
}



int main() {
    int option;
    do {
        display_menu();
        printf("Enter your choice (1-9): ");

        while (scanf("%d", &option) != 1 || option < 1 || option > 9) {
            printf("Invalid input. Please enter a number between 1 and 9: ");
            while (getchar() != '\n') {
                continue; // Clear input buffer
            }
        }

        switch (option) {
            case 1:
                add_book();
                break;
            case 2:
                borrow_book();
                break;
            case 3:
                return_book();
                break;
            case 4:
                delete_book();
                break;
            case 5:
                view_all_books();
                break;
            case 6:
                view_specific_book();
                break;
            case 7:
                view_popularity_of_books();
                break;
            case 8:
                my_own_option();
                break;
            case 9:
                write_books_to_file()
                printf("Exiting the system...\n");
                break;
            default:
                printf("Invalid option. Please choose a number from 1 to 9.\n");
                break;
        }
    } while (option != 9);

    return 0;
}   
