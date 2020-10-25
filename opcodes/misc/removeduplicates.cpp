#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <set>
#include <vector>




int main()
{
  std::vector<std::string> vec_of_strings;

  std::ifstream IFILE_STREAM("out.txt");

  std::set<std::string> missed_strings;
  std::string temp_string;
  
  while (IFILE_STREAM >> temp_string)
    {
      missed_strings.insert(temp_string);
    }

  std::ofstream OUTFILE_STREAM("missed_strings.txt");

  std::set<std::string>::iterator iterator_for_set = missed_strings.begin();

  
  for (; iterator_for_set != missed_strings.end(); iterator_for_set++)
    {
      OUTFILE_STREAM << *iterator_for_set;
      OUTFILE_STREAM << std::endl;
    }
   


  
  

}
