#ifndef PUBLICATIONSELECTOR_H_
#define PUBLICATIONSELECTOR_H_
#include "Publication.h"

class PublicationSelector {
   const int allocationUnit{ 10 };  //
   const int m_pageSize{ };         // Constant integer variable to hold the size of the publication.
   const Publication** m_pub{};     // Constant array of Publication object.
   char m_title[81]{};              // C-style type to hold the title.
   int m_currentPage{ 1 };          // Integer to hold the current page of the publication.
   int m_arraySize{};               // Integer variable to hold the array size.
   int m_noOfPubs{};                // Integer variable to hold the number of publication.

   void display(int page)const;     // Display header and the contents of the publication.
   int getSelectedLibRef()const;    // 

public:
   PublicationSelector(const char* title = "Select a publication: ", int pageSize = 15);

   // Rules of five
   ~PublicationSelector();                                              // Destructor
   PublicationSelector(const PublicationSelector&) = delete;            // Prevent copy constructor
   PublicationSelector& operator=(const PublicationSelector&) = delete; // Prevent Copy assignment operator
   PublicationSelector(PublicationSelector&&) = delete;                 // Prevent Move constructor
   PublicationSelector& operator=(PublicationSelector&&) = delete;      // Prevent Move assignment operator

   operator bool()const;   // Return true menu is not empty 
   void reset();           // Clears all the publications and sets the selector empty and ready to be refilled
   void sort();            // Sorts the selections based on date and title
   int run();              // Runs the selection return the library reference fo the selection publication.

   PublicationSelector& operator<<(const Publication* pub);    // adds publication to the menu by address
   PublicationSelector& operator<<(const Publication& pub);    // add publication tot he menu by reference
   
};

#endif //!PUBLICATIONSELECTOR_H_