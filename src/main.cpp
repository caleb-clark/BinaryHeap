#include "BinaryHeap.h"
#include <iostream>
#include <time.h>

int main() 
{
     srand (time(NULL));
	BinaryHeap<int> b;
     for (int i = 9; i >= 0; i--) {
          b.insert(i);
          b.print();
          std::cout << "--------------------------------" << std::endl << std::endl;
     }

     for (int i = 9; i >= 0; i--) {
          b.remove_first();
          b.print();
          std::cout << "--------------------------------" << std::endl << std::endl;
     }
     clock_t begin = clock();

     for (int i = 0; i < 1000000; i++) {
          b.insert(rand() % 100000 + 1);
     }
     clock_t mid = clock();
     for (int i = 0; i < 1000000; i++) {
          b.remove_first();
     }
     
     clock_t end = clock();
     double s_m = double(mid - begin) / CLOCKS_PER_SEC;
     double m_e = double(end - mid) / CLOCKS_PER_SEC;

     std::cout << "Time start to middle: " << s_m << std::endl;
     std::cout << "Time middle to end: " << m_e << std::endl; 

     BinaryHeap<std::string> s;

     std::string my_string = "";

     for (int i = 0; i < 10; i++) {
          char qq = 'a' + i;
          my_string += qq;
          s.insert(my_string);
     }
     s.print();
     for (int i = 0; i < 10; i++) {
          s.remove_first();
          s.print();
          std::cout << std::endl << std::endl;
     }     
     
     
}

