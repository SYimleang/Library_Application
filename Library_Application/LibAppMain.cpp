#include <fstream>
#include <iostream>
#include "LibApp.h"
#include "Date.h"
#include "Menu.h"

void runApp(const char* filename) {
   size_t i{};
   char ch;
   char original[50] = "./resource_files/orig";
   // creating original file name
   while(filename[i]) original[21u + i] = filename[i++];
   original[21u + i] = char(0);
   // Copying original values to data file;
   std::ofstream outFile(filename);
   std::ifstream inFile(original);
   while(inFile.get(ch)) {
      outFile << ch;
   }
   outFile.close();
   inFile.close();
   // setting test values
   day = 10;
   mon = 8;
   year = 2023;
   test = true;
   LibApp app(filename);
   app.run();
   std::cout << "Content of " << filename << "\n=========>\n";
   inFile.open(filename);
   while(inFile.get(ch)) std::cout << ch;
   std::cout << "<=========\n";
}
int main() {
   Menu outFile("Select Data File");
   outFile << "LibRecsSmall.txt" << "LibRecs.txt";
   switch(outFile.run()) {
   case 1:
      std::cout << "Test started using small data: " << std::endl;
      runApp("LibRecsSmall.txt");
      break;
   case 2:
      std::cout << "Test started using big data: " << std::endl;
      runApp("LibRecs.txt");
      break;
   default:
      std::cout << "Aborted by user! " << std::endl;
      break;
   }
   return 0;
}