#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>
#include <conio.h>

using namespace std;

class Reader
{
private:
    int pn, id;
    string name;

public:
    void createAccount()
    {
        cin.ignore();
        cout << "Name: ";
        getline(cin, name);
        cout << "Phone Number: ";
        cin >> pn;
        cout << "ID: ";
        cin >> id;
        while (cin.fail() || id < 0)
        {
            cout << "Please enter valid ID: ";
            cin.clear();
            cin.ignore();
            cin >> id;
        }
        ofstream file1("Reader.txt", ios_base::app);
        file1 << "Name: " << name << endl;
        file1 << "Phone Number: " << pn << endl;
        file1 << "ID: " << id << "\n\n";
    }

    void changeAccount()
    {
        createAccount();
    }

    ~Reader() {}
};

class Author
{
private:
    string name;

public:
    void createAccount()
    {
        cin.ignore();
        cout << "Name: ";
        getline(cin, name);
        ofstream file2("Author.txt", ios_base::app);
        file2 << "\n"
              << name << endl;
    }

    ~Author() {}
};

class Book
{
private:
    string title;
    int price;

public:
    // Setter
    void setTitle(string Title) { title = Title; }
    void setPrice(int Price) { price = Price; }
    // Getter
    string getTitle() { return title; }
    int getPrice() { return price; }
};

Book books[200];
int counter = 0;

void increment()
{
    counter++;
}

void decrement()
{
    counter--;
}

void Filebook(int counter);
void addbook(int &counter);
void editbook(int &counter);
void deletebook(int &counter);
void searchbook(int counter);
void viewall(int counter);

int main()
{
    int choice;
    char x;
    Author author1;
    Reader reader1;

    do
    {
        cout << "-----Online library-----" << endl;
        cout << "1. Reader" << endl;
        cout << "2. Author" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            reader1.createAccount();
            do
            {
                cout << "1. Find book by name" << endl;
                cout << "2. View all books" << endl;
                cout << "3. Change account" << endl;
                cout << "4. Exit" << endl;
                cout << "Enter choice: ";
                cin >> choice;

                switch (choice)
                {
                case 1:
                    searchbook(counter);
                    break;
                case 2:
                    viewall(counter);
                    break;
                case 3:
                    reader1.changeAccount();
                    break;
                }
            } while (choice != 4);
            break;

        case 2:
            author1.createAccount();
            do
            {
                cout << "1. Add book" << endl;
                cout << "2. Delete book" << endl;
                cout << "3. Edit book" << endl;
                cout << "4. Exit" << endl;
                cout << "Enter choice: ";
                cin >> choice;

                switch (choice)
                {
                case 1:
                    addbook(counter);
                    break;
                case 2:
                    deletebook(counter);
                    break;
                case 3:
                    editbook(counter);
                    break;
                }
            } while (choice != 4);
            break;

        default:
            cout << "Failed!! Please try again" << endl;
        }

        cout << "Do you want to select another option? (y/n): ";
        cin >> x;
        system("CLS");
    } while (x == 'y' || x == 'Y');

    return 0;
}

void Filebook(int counter)
{
    ofstream file3;
    file3.open("Book.txt", ios_base::out);
    for (int i = 0; i < counter; i++)
    {
        file3 << books[i].getTitle();
        file3 << setw(15) << right << books[i].getPrice() << "$" << endl;
    }
    file3.close();
}

void addbook(int &counter)
{
    string title;
    int price;
    if (counter < 200)
    {
        cin.ignore();
        cout << "Book title: ";
        getline(cin, title);
        cout << "Rental price: ";
        cin >> price;
        while (cin.fail() || price < 0)
        {
            cin.clear();
            cout << "Please enter valid price: ";
            cin.ignore();
            cin >> price;
        }
        books[counter].setTitle(title);
        books[counter].setPrice(price);
        increment();
        Filebook(counter);
    }
    else
    {
        cout << "The library is full." << endl;
    }
}

void editbook(int &counter)
{
    string title;
    int price;
    bool print = false;
    if (counter == 0)
    {
        cout << "There are no books to edit." << endl;
    }
    else
    {
        cout << "Enter book name to edit: ";
        cin.ignore();
        getline(cin, title);
        for (int i = 0; i < counter; i++)
        {
            if (books[i].getTitle() == title)
            {
                cout << "Enter new name: ";
                getline(cin, title);
                cout << "New rental price: ";
                cin >> price;
                while (cin.fail() || price < 0)
                {
                    cout << "Please enter valid price: ";
                    cin.clear();
                    cin.ignore();
                    cin >> price;
                }
                books[i].setTitle(title);
                books[i].setPrice(price);
                print = true;
            }
        }
        Filebook(counter);
        if (!print)
        {
            cout << "Book not found." << endl;
        }
    }
}

void deletebook(int &counter)
{
    string title;
    bool print = false;
    if (counter == 0)
    {
        cout << "There are no books to delete." << endl;
    }
    else
    {
        cout << "Enter book name to delete: ";
        cin.ignore();
        getline(cin, title);
        for (int i = 0; i < counter; i++)
        {
            if (books[i].getTitle() == title)
            {
                print = true;
                for (int a = i; a < (counter - 1); a++)
                {
                    books[a] = books[a + 1];
                }
                decrement();
                Filebook(counter);
            }
        }
        if (!print)
        {
            cout << "Book not found." << endl;
        }
    }
}

void searchbook(int counter)
{
    string title;
    bool print = false;
    if (counter == 0)
    {
        cout << "Library is empty." << endl;
    }
    else
    {
        cout << "Search: ";
        cin.ignore();
        getline(cin, title);
        for (int i = 0; i < counter; i++)
        {
            if (books[i].getTitle() == title)
            {
                print = true;
                cout << books[i].getTitle();
                cout << setw(15) << right << books[i].getPrice() << "$" << endl;
            }
        }
        if (!print)
        {
            cout << "Book not found." << endl;
        }
    }
}

void viewall(int counter)
{
    if (counter == 0)
    {
        cout << "Library is empty." << endl;
    }
    else
    {
        for (int i = 0; i < counter; i++)
        {
            cout << books[i].getTitle();
            cout << setw(15) << right << books[i].getPrice() << "$" << endl;
        }
    }
}
