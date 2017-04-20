#ifndef REC_FUN_H 
#define REC_FUN_H 

#include <string>
#include <map>
#include <set>

namespace mry2270 {
  void triangle(std::ostream& outs, unsigned int m, unsigned int n);
  void numbers(std::ostream& outs, const std::string& prefix, unsigned int levels);
  bool bears(int n);
  void pattern(std::ostream& outs, unsigned int n, unsigned int i);
  bool path(const std::multimap<int,int>& m, int s, int t, std::set<int>& already_tried);
}

#endif