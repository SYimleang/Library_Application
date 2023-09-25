#include <iostream>
#include <fstream>
#include "Book.h"
#include "Date.h"

void fcopy( const char* dest, const char* source ) {
   std::ifstream fin( source );
   std::ofstream fout( dest );
   char ch;
   while ( fin.get( ch ) ) fout << ch;
}

Book readBook(std::istream& istr) {
   Book P;
   istr >> P;
   return P;
}
Book getNextRec(std::ifstream& ifstr) {
   Book P;
   ifstr >> P;
   ifstr.ignore(1000, '\n');
   return P;
}

int main() {
   test = true;
   Book pd;
   fcopy( "./source_files/Books.txt", "./source_files/BooksOriginal.txt" );
   std::cout << "An Invalid Book printout:" << std::endl;
   std::cout << ">" << pd << "<" << std::endl;
   std::cout << std::endl << "Enter the following: " << std::endl
      << "P1234" << std::endl
      << "------------------------------" << std::endl;
   pd = readBook(std::cin);
   if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(1000, '\n');
   }
   else {
      std::cout << "This is not supposed to be printed!" << std::endl;
   }
   std::cout << "You entered:" << std::endl;
   std::cout << ">" << pd << "<" << std::endl;
   std::cout << std::endl << "Enter the following: " << std::endl
      << "P123" << std::endl
      << "Publication Handbook" << std::endl
      << "2023/13/17" << std::endl
      << "------------------------------" << std::endl;
   pd = readBook(std::cin);
   if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(1000, '\n');
   }
   else {
      std::cout << "This is not supposed to be printed!" << std::endl;
   }
   std::cout << "You entered:" << std::endl;
   std::cout << ">" << pd << "<" << std::endl;
   std::cout << std::endl << "Enter the following: " << std::endl
      << "P123" << std::endl
      << "The Story of My Experiments with Truth" << std::endl
      << "2023/11/17" << std::endl
      << "Mohandas Karamchand Gandhi" << std::endl
      << "------------------------------" << std::endl;
   pd = readBook(std::cin);
   std::cout << "You entered:" << std::endl;
   std::cout << pd << std::endl;
   std::cout << "And the title is agian: \"" << (const char*)pd << "\"" << std::endl;
   pd.set(12345);
   if (pd.onLoan()) {
      std::cout << "Now this publication is on loan to a member with the id: 12345" << std::endl;
      std::cout << "The checkout date is: " << pd.checkoutDate() << std::endl;
      pd.setRef(9999);
      std::cout << "The library unique reference id is: " << pd.getRef() << std::endl;
      std::cout << pd << std::endl;
      std::cout << "----------------------------------------------------------------" << std::endl;
    }
   std::cout << "Adding the Book to the end of the data file:" << std::endl;
   std::ofstream fileout("./source_files/Books.txt", std::ios::app);
   if (pd) {
      std::cout << "appeneded to the file" << std::endl;
      fileout << pd << std::endl;
   }
   fileout.close();
   std::cout << std::endl << "Contents of the file:" << std::endl;
   std::ifstream filein("./source_files/Books.txt");
   char pType{};
   for (int row = 1; filein; row++) {
      filein >> pType;
      if (pType != 'B') {
         std::cout << "The Record type signature is supposed to be B, but it is: " << pType << std::endl;
         filein.setstate(std::ios::failbit);
      }
      filein.ignore();
      pd = getNextRec(filein);
      if (filein) {
         std::cout << (pd.onLoan() ? "|*" : "| ");
         std::cout.width(4);
         std::cout.fill(' ');
         std::cout.setf(std::ios::right);
         std::cout << row << (pd.onLoan()? "*": " ");
         std::cout.unsetf(std::ios::right);
         std::cout << pd << (pd == "Star" ? "<<<":"") << std::endl;
      }
   }
   return 0;
}