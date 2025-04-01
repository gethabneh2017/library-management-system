#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Book structure for array storage
struct Book {
    int id;
    string title;
    string author;
    string genre;
    bool isIssued = false;

    void display() const {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author
             << ", Genre: " << genre << ", Issued: " << (isIssued ? "Yes" : "No") << endl;
    }
};
//bellow this is basha code
//basha contribute 
// Library Member as a linked list node
class Member {
public:
    int id;
    string name;
    int borrowedBooks = 0;
    bool isActive = true;
    Member* next = nullptr;

    Member(int id, const string& name) : id(id), name(name) {}

    void display() const {
        cout << "ID: " << id << ", Name: " << name
             << ", Borrowed: " << borrowedBooks << ", Status: " << (isActive ? "Active" : "Inactive") << endl;
    }
};

// Library System
class Library {
private:
    static const int MAX_BOOKS = 100;
    Book books[MAX_BOOKS];
    int bookCount = 0;
    Member* membersHead = nullptr;

    // Helper function to convert string to lowercase
    string toLower(const string& str) const {
        string lowerStr = str;
        for (char& c : lowerStr) {
            if (c >= 'A' && c <= 'Z') {
                c += 32; // Convert to lowercase
            }
        }
        return lowerStr;
    }

public:
    // Add a book
    void addBook(int id, const string& title, const string& author, const string& genre) {
        if (bookCount < MAX_BOOKS) {
            books[bookCount++] = {id, title, author, genre, false};
            cout << "Book added successfully!\n";
        } else {
            cout << "Library is full!\n";
        }
    }

    // Search book by title (case-insensitive)
    void searchBook(const string& title) const {
        string lowerTitle = toLower(title);

        for (int i = 0; i < bookCount; i++) {
            string lowerBookTitle = toLower(books[i].title);

            if (lowerBookTitle == lowerTitle) {
                books[i].display();
                return;
            }
        }
        cout << "Book not found!\n";
    }

    // Update book details
    void updateBook(int id, const string& newTitle, const string& newAuthor, const string& newGenre) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].id == id) {
                books[i] = {id, newTitle, newAuthor, newGenre, books[i].isIssued};
                cout << "Book updated successfully!\n";
                return;
            }
        }
        cout << "Book not found!\n";
    }

    // Delete book
    void deleteBook(int id) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].id == id) {
                books[i] = books[--bookCount]; // Replace with last book
                cout << "Book deleted successfully!\n";
                return;
            }
        }
        cout << "Book not found!\n";
    }

    // Add a member
    void addMember(int id, const string& name) {
        Member* newMember = new Member(id, name);
        newMember->next = membersHead;
        membersHead = newMember;
        cout << "Member added successfully!\n";
    }

    // Search member by ID
    void searchMember(int id) const {
        for (Member* temp = membersHead; temp; temp = temp->next) {
            if (temp->id == id) {
                temp->display();
                return;
            }
        }
        cout << "Member not found!\n";
    }

    // Update member status
    void updateMember(int id, bool status) {
        for (Member* temp = membersHead; temp; temp = temp->next) {
            if (temp->id == id) {
                temp->isActive = status;
                cout << "Member status updated!\n";
                return;
            }
        }
        cout << "Member not found!\n";
    }

    // Delete member
    void deleteMember(int id) {
        Member* temp = membersHead;
        Member* prev = nullptr;


           while (temp) {
            if (temp->id == id) {
                if (prev) {
                    prev->next = temp->next;
                } else {
                    membersHead = temp->next;
                }
                delete temp;
                cout << "Member deleted successfully!\n";
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        cout << "Member not found!\n";
    }

    // Issue a book
    void issueBook(int bookId, int memberId) {
        Book* book = nullptr;
        for (int i = 0; i < bookCount; i++) {
            if (books[i].id == bookId) {
                book = &books[i];
                break;
            }
        }

        Member* member = membersHead;
        while (member) {
            if (member->id == memberId) break;
            member = member->next;
        }

        if (!book || !member) {
            cout << "Invalid book or member!\n";
            return;
        }

        if (book->isIssued) {
            cout << "Book is already issued!\n";
            return;
        }

        if (member->borrowedBooks >= 3) {
            cout << "Member has reached the borrowing limit!\n";
            return;
        }

        book->isIssued = true;
        member->borrowedBooks++;
        cout << "Book issued successfully!\n";
    }

    // Return a book
    void returnBook(int bookId, int memberId) {
        Book* book = nullptr;
        for (int i = 0; i < bookCount; i++) {
            if (books[i].id == bookId) {
                book = &books[i];
                break;
            }
        }

        Member* member = membersHead;
        while (member) {
            if (member->id == memberId) break;
            member = member->next;
        }

        if (!book || !member) {
            cout << "Invalid book or member!\n";
            return;
        }

        if (!book->isIssued) {
            cout << "This book was not issued!\n";
            return;
        }

        book->isIssued = false;
        member->borrowedBooks--;
        cout << "Book returned successfully!\n";
    }

    // Save book data to file
    void saveBooksToFile() const {
        ofstream file("books.txt");
        for (int i = 0; i < bookCount; i++) {
            file << books[i].id << "," << books[i].title << "," << books[i].author
                 << "," << books[i].genre << "," << books[i].isIssued << endl;
        }
        file.close();
    }
};

// Function to display the menu
void displayMenu() {
    cout << "\nLibrary Management System Menu:\n";
    cout << "1. Add Book\n";
    cout << "2. Search Book\n";
    cout << "3. Update Book\n";
    cout << "4. Delete Book\n";
    cout << "5. Add Member\n";
    cout << "6. Search Member\n";
    cout << "7. Update Member Status\n";
    cout << "8. Delete Member\n";
    cout << "9. Issue Book\n";
    cout << "10. Return Book\n";
    cout << "11. Save Books to File\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    Library lib;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: { // Add Book
                int id;
                string title, author, genre;
                cout << "Enter Book ID: ";
                cin >> id;
                cout << "Enter Title: ";
                cin.ignore(); // Clear the newline character from the input buffer
                getline(cin, title);
                cout << "Enter Author: ";
                getline(cin, author);
                cout << "Enter Genre: ";
                getline(cin, genre);
                lib.addBook(id, title, author, genre);
                break;
            }
            case 2: { // Search Book
                string title;
                cout << "Enter Title to Search: ";


cin.ignore();
                getline(cin, title);
                lib.searchBook(title);
                break;
            }
            case 3: { // Update Book
                int id;
                string newTitle, newAuthor, newGenre;
                cout << "Enter Book ID to Update: ";
                cin >> id;
                cout << "Enter New Title: ";
                cin.ignore();
                getline(cin, newTitle);
                cout << "Enter New Author: ";
                getline(cin, newAuthor);
                cout << "Enter New Genre: ";
                getline(cin, newGenre);
                lib.updateBook(id, newTitle, newAuthor, newGenre);
                break;
            }
            case 4: { // Delete Book
                int id;
                cout << "Enter Book ID to Delete: ";
                cin >> id;
                lib.deleteBook(id);
                break;
            }
            case 5: { // Add Member
                int id;
                string name;
                cout << "Enter Member ID: ";
                cin >> id;
                cout << "Enter Member Name: ";
                cin.ignore();
                getline(cin, name);
                lib.addMember(id, name);
                break;
            }
            case 6: { // Search Member
                int id;
                cout << "Enter Member ID to Search: ";
                cin >> id;
                lib.searchMember(id);
                break;
            }
            case 7: { // Update Member Status
                int id;
                bool status;
                cout << "Enter Member ID to Update: ";
                cin >> id;
                cout << "Enter New Status (1 for Active, 0 for Inactive): ";
                cin >> status;
                lib.updateMember(id, status);
                break;
            }
            case 8: { // Delete Member
                int id;
                cout << "Enter Member ID to Delete: ";
                cin >> id;
                lib.deleteMember(id);
                break;
            }
            case 9: { // Issue Book
                int bookId, memberId;
                cout << "Enter Book ID to Issue: ";
                cin >> bookId;
                cout << "Enter Member ID: ";
                cin >> memberId;
                lib.issueBook(bookId, memberId);
                break;
            }
            case 10: { // Return Book
                int bookId, memberId;
                cout << "Enter Book ID to Return: ";
                cin >> bookId;
                cout << "Enter Member ID: ";
                cin >> memberId;
                lib.returnBook(bookId, memberId);
                break;
            }
            case 11: { // Save Books to File
                lib.saveBooksToFile();
                cout << "Books saved to file successfully!\n";
                break;
            }
            case 0: // Exit
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
