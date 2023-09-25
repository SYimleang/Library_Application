#include <iostream>
#include <fstream>
#include "Publication.h"
#include "Date.h"

void fcopy( const char* dest, const char* source ) {
   std::ifstream fin( source);
   std::ofstream fout( dest );
   char ch;
   while ( fin.get( ch ) ) fout << ch;
}

Publication readPublication(std::istream& istr) {
   Publication P;
   istr >> P;
   return P;
}
Publication getNextRec(std::ifstream& ifstr) {
   Publication P;
   ifstr >> P;
   ifstr.ignore(1000, '\n');
   return P;
}

int main() {
   test = true;
   Publication pd;
   fcopy( "Periodicals.txt", "PeriodicalsOriginal.txt" );
   std::cout << "An Invalid publication printout:" << std::endl;
   std::cout << ">" << pd << "<" << std::endl;
   std::cout << "Enter the following: " << std::endl
      << "P1234" << std::endl
      << "------------------------------" << std::endl;
   pd = readPublication(std::cin);
   if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(1000, '\n');
   }
   else {
      std::cout << "This is not supposed to be printed!" << std::endl;
   }
   std::cout << "You entered:" << std::endl;
   std::cout << ">" << pd << "<" << std::endl;
   std::cout << "Enter the following: " << std::endl
      << "P123" << std::endl
      << "Publication Weekly" << std::endl
      << "2023/13/17" << std::endl
      << "------------------------------" << std::endl;
   pd = readPublication(std::cin);
   if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(1000, '\n');
   }
   else {
      std::cout << "This is not supposed to be printed!" << std::endl;
   }
   std::cout << "You entered:" << std::endl;
   std::cout << ">" << pd << "<" << std::endl;
   std::cout << "Enter the following: " << std::endl
      << "P123" << std::endl
      << "Publication Weekly" << std::endl
      << "2023/11/17" << std::endl
      << "------------------------------" << std::endl;
   pd = readPublication(std::cin);
   std::cout << "You entered:" << std::endl;
   std::cout << pd << std::endl;
   std::cout << "And the title is agian: \"" << (const char*)pd << "\"" << std::endl;
   pd.set(12345);
   if (pd.onLoan()) {
      std::cout << "Now this publication is on loan to a member with the id: 12345" << std::endl;
      pd.resetDate();
      std::cout << "The checkout date is: " << pd.checkoutDate() << std::endl;
      pd.setRef(9999);
      std::cout << "The library unique reference id is: " << pd.getRef() << std::endl;
      std::cout << pd << std::endl;
      std::cout << "----------------------------------------------------------------" << std::endl;
    }
   std::cout << "Adding the periodical publication to the end of the data file:" << std::endl;
   std::ofstream fileout("Periodicals.txt", std::ios::app);
   if (pd) {
      std::cout << "appeneded to the file" << std::endl;
      fileout << pd << std::endl;
   }
   fileout.close();
   std::cout << std::endl << "Contents of the file:" << std::endl;
   std::ifstream filein("Periodicals.txt");
   char pType{};
   for (int row = 1; filein; row++) {
      filein >> pType;
      if (pType != 'P') {
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