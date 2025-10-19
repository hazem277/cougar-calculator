#include <iostream>
#include <string>

std::string addSubtract(std::string expr) {
   while (true) {
      size_t i = expr.find_first_of("+-");
      if (i == std::string::npos)
         return expr; // done

      size_t start = i;
      while (start > 0 && (isdigit(expr[start - 1]) || expr[start - 1] == '.'))
         start--;

      size_t end = i + 1;
      while (end < expr.size() && (isdigit(expr[end]) || expr[end] == '.'))
         end++;

      double left = std::stod(expr.substr(start, i - start));
      double right = std::stod(expr.substr(i + 1, end - i - 1));

      double result = (expr[i] == '+') ? left + right : left - right;
      expr.replace(start, end - start, std::to_string(result));
   }
}

std::string multiplyDivide(std::string expr) {
   while (true) {
      size_t i = expr.find_first_of("*/");
      if (i == std::string::npos)
         return expr; // stop when no * or / left

      size_t start = i;
      while (start > 0 && (isdigit(expr[start - 1]) || expr[start - 1] == '.'))
         start--;

      size_t end = i + 1;
      while (end < expr.size() && (isdigit(expr[end]) || expr[end] == '.'))
         end++;

      double left = std::stod(expr.substr(start, i - start));
      double right = std::stod(expr.substr(i + 1, end - i - 1));

      double result = (expr[i] == '*') ? left * right : left / right;
      expr.replace(start, end - start, std::to_string(result));
   }
}

double eval(std::string s) {
   // keep resolving innermost parentheses until none left
   while (true) {
      size_t close = s.find(')');
      if (close == std::string::npos)
         break; // no more parentheses

      size_t open = s.rfind('(', close);
      if (open == std::string::npos) {
         std::cout << "invalid parenthesis";
         return 0;
      }

      // isolate and evaluate inner expression
      std::string inside = s.substr(open + 1, close - open - 1);
      std::string result = addSubtract(multiplyDivide(inside));

      // replace "(inside)" with evaluated result
      s.replace(open, close - open + 1, result);
   }

   // evaluate the final expression (no parentheses left)
   std::string result = addSubtract(multiplyDivide(s));
   std::cout << "result: " << result << "\n";

   return std::stod(result);
}

int main() {
   std::string expression;
   std::cout << "input expression: ";
   std::cin >> expression;
   eval(expression);
}