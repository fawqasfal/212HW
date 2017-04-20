#include "rec_fun.h"
#include <iostream>
#include <assert.h>
using namespace std;

namespace mry2270 { 
	void triangle(ostream& outs, unsigned int m, unsigned int n) {
		assert(m <= n);
		string ans = "";
		for (int i = 0; i < m; i++) ans += "*";
  		outs << ans << endl;
  		if (m < n) triangle(outs, m + 1, n);
  		outs << ans << endl; 
	}

	void numbers(ostream& outs, const string& prefix, unsigned int levels) {
		if (levels == 0) {
			outs << prefix << endl;
			return;
		}
		for (char i = '1'; i <= '9'; i++) {
			numbers(outs, prefix + i + '.', levels-1);
		}
	}

	bool bears(int n) {
		if ((n % 5) == 0) return true;
		else if ((n % 3) == 0 or (n % 4) == 0) return bears((n%10) * ((n%100)/10));
		else if ((n % 2) == 0) return bears(n / 2); 
		return false;
	}

	void pattern(ostream& outs, unsigned int n, unsigned int i) {
 		if (n == 0) return;
		pattern(outs, n/2, i);
		for (int k = 0; k < i; k++) outs << " ";
		for (int k = 0; k < n; k++) outs << "*";
		outs << endl;		
		pattern(outs, n/2, i + n/2);
	}

	bool path(const multimap<int,int>& m, int s, int t, set<int>& already_tried) {
		if (m.count(s) != 0) already_tried.insert(s); //this is the first step in set building 
		for (auto it = m.begin(); it != m.end(); it++) {
			if(it->first == s) {
				if (it->second == t) return true;
				bool test = already_tried.insert(it->second).second; 
				//returns whether an element was truly added or not; if not, no need to repeat pathfinding on that element
				if (test and path(m, it->second, t, already_tried)) return true;
				already_tried.erase(it->second); 
			}
		}
		return false;
	}

}

