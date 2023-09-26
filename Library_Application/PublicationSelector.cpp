#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "PublicationSelector.h"

/* Method to display the content of the program. First display the title then will display the content as the format. */
void PublicationSelector::display(int page) const {
   std::cout << m_title << std::endl 
         << " Row  |LocID | Title                          |Mem ID | Date       | Author          |" << std::endl
         << "------+------+--------------------------------+-------+------------+-----------------|" << std::endl;
   for (int i = (page - 1) * m_pageSize ; i < m_noOfPubs && i < page * m_pageSize; i++) {
      std::cout.width(4);
      std::cout.setf(std::ios::right);
      std::cout.fill(' ');
      std::cout << (i + 1);
      std::cout.unsetf(std::ios::right);
      std::cout << "- " << *m_pub[i] << std::endl;
   }
}

/*  */
int PublicationSelector::getSelectedLibRef()const{
   bool ok{};
   char newline{};
   char chPeek{};
   int val{};
   int retVal{};
   if (m_noOfPubs > m_pageSize) {
      if (m_currentPage > 1) 
         std::cout << "> P (Previous Page)" << std::endl;
      if (m_currentPage * m_pageSize < m_noOfPubs) 
         std::cout << "> N (Next page)" << std::endl;
   }
   std::cout << "> X (to Exit)" << std::endl << "> Row Number(select publication)" << std::endl;
   std::cout << "> ";
   do {
      chPeek = std::cin.peek();
      switch (chPeek) {
      case 'P':
      case 'p':
         std::cin.ignore(1000, '\n');
         retVal = 2;  // previous page
         if (m_currentPage > 1)
            ok = true;
         else
            ok = false;
         break;
      case 'N':
      case 'n':
         std::cin.ignore(1000, '\n');
         retVal = 1; // Next page
         if (m_currentPage * m_pageSize < m_noOfPubs)
            ok = true;
         else
            ok = false;
         break;
      case 'X':
      case 'x':
         std::cin.ignore(1000, '\n');
         retVal = 0; // Exit
         ok = true;
         break;
      default:
         std::cin >> val;
         newline = std::cin.get();
         if (std::cin.fail() || newline != '\n') {
            ok = false;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
         }
         else {
            ok = val >= 1 && val <= m_noOfPubs;
            if(ok) retVal = m_pub[val - 1]->getRef();
         }
         break;
      }
   } while (!ok && std::cout << "Invalid selection, retry" << std::endl << "> ");
   return retVal;
}


PublicationSelector::~PublicationSelector() {
   delete[] m_pub;
}


PublicationSelector::PublicationSelector(const char* title, int pageSize) :m_pageSize{ pageSize } {
   strncpy(m_title, title, 80);
   m_title[80] = 0;
   m_pub = new const Publication*[m_arraySize = allocationUnit];
}

PublicationSelector& PublicationSelector::operator<<(const Publication& pub) {
   return operator<<(&pub);
}

PublicationSelector& PublicationSelector::operator<<(const Publication* pub) {
   if (m_noOfPubs == m_arraySize) {
      const Publication** temp = new const Publication*[m_arraySize += allocationUnit];
      for (int i = 0; i < m_noOfPubs; i++) {
         temp[i] = m_pub[i];
      }
      delete[] m_pub;
      m_pub = temp;
   }
   m_pub[m_noOfPubs++] = pub;
   return *this;
}

void PublicationSelector::reset() {
   delete[] m_pub;
   m_pub = new const Publication*[20];
   m_noOfPubs = 0;
}

int PublicationSelector::run() {
   int retVal{};
   do {
      display(m_currentPage);
      retVal = getSelectedLibRef();
      if (retVal && retVal < 3) {
         if (retVal == 2) retVal = -1;
         m_currentPage += retVal;
         //if (m_currentPage == 0) 
         //   m_currentPage = 1; // don't go before first page
         //else if (m_currentPage * m_pageSize > m_noOfPubs) //((m_currentPage-1) * m_pageSize > m_noOfPubs) 
         //   m_currentPage = m_noOfPubs/m_pageSize +1; // don't go after last page
      }
   } while (retVal && retVal < 3);
   return retVal;
}

void PublicationSelector::sort() {
   int i, j;
   const Publication* temp{};
   for (i = 0; i < m_noOfPubs - 1; i++) {
      for (j = 0; j < m_noOfPubs - i - 1; j++) {
         if (m_pub[j]->checkoutDate() > m_pub[j + 1]->checkoutDate()) {
            temp = m_pub[j];
            m_pub[j] = m_pub[j + 1];
            m_pub[j + 1] = temp;
         }
      }
   }
   for (i = 0; i < m_noOfPubs - 1; i++) {
      for (j = 0; j < m_noOfPubs - i - 1; j++) {
         if (strcmp((const char*)*m_pub[j], (const char*)*m_pub[j + 1]) > 0 ) {
            temp = m_pub[j];
            m_pub[j] = m_pub[j + 1];
            m_pub[j + 1] = temp;
         }
      }
   }
}

PublicationSelector::operator bool()const {
   return m_noOfPubs > 0;
}