#ifndef LIBAPP_H_
#define LIBAPP_H_
#include "Menu.h"

class LibApp : public Menu{
    bool m_changed;      // Variable to hold the changing status of the program.
    Menu m_mainMenu;     // Class variable to hold the main menu messages.
    Menu m_exitMenu;     // Class variable to hold the exit menu messages.

    bool confirm(const char* message);

    void load();        // prints: "Loading Data"<NEWLINE>
    void save();        // prints: "Saving Data"<NEWLINE>
    void search();      // prints: "Searching for publication"<NEWLINE>
    void returnPub();  /*  Calls the search() method.
                            prints "Returning publication"<NEWLINE>
                            prints "Publication returned"<NEWLINE>
                            sets m_changed to true;
                        */
public:
    LibApp();    // Default constructor.

    // Rules of three
    ~LibApp();                                      // Destructor.
    LibApp(const LibApp& src) = delete;             // Prevent copying the instance of a class.
    LibApp& operator=(const LibApp& src) = delete;  // Prevent assigning the instance of a class.

    void newPublication();      // Adding new publication method.
    void removePublication();   // Remove publication method.
    void checkOutPub();         // Check out republication method.
    void run();                 // The run method is the main application driver.
};
#endif // !LIBAPP_H_