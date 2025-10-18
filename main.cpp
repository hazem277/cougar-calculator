#include <iostream>
#include <string>

std::string expression = "1+(2+3)*(4/5)";

double eval(const std::string &s) {
   size_t close = s.find(')');
   if (close == std::string::npos) {
      std::cout << s;
      return 0;
   }

   size_t open = s.rfind('(', close);
    if(open == std::string::npos) {
      std::cout << "invalid parenthesis";
      return 0;
   }

   std::string inside = s.substr(open + 1, close - open - 1);
   std::cout << inside;

   return 0;
}

int main() {
   eval(expression);
   std::cout << std::endl;
}