
#include "stats.h"
namespace main_savitch_2C {
	statistician::statistician() {
		count = 0;
		total = 0;
		tinyest = 0;
		largest = 0;
	}

	void statistician::next(double r) {
		count += 1;
		total += r;
		if (count == 1 || r < tinyest) tinyest = r;
		if (count == 1 || r > largest) largest = r;}
	void statistician::reset() {
		count = 0;
		total = 0;
		tinyest = 0;
		largest = 0;
	}

	int statistician::length() const {return count;}
	double statistician::sum() const {return total;}
	double statistician::mean() const {return sum()/length();}
	double statistician::minimum() const {return tinyest;}
	double statistician::maximum() const {return largest;}

	statistician operator+(const statistician& s1, const statistician& s2) {
		statistician answer;
		answer.count = s1.count + s2.count;
		answer.total = s1.total + s2.total;
		if (s1.length() == 0) {
			answer.tinyest = s2.tinyest;
			answer.largest = s2.largest;
		} else if (s2.length() == 0) {
			answer.tinyest = s1.tinyest;
			answer.largest = s2.largest; 
		} else {
			answer.tinyest = ((s1.tinyest <= s2.tinyest) ? s1.tinyest : s2.tinyest);
			answer.largest = ((s1.largest >= s2.largest) ? s1.largest : s2.largest);
		}
		return answer;
	} 
	statistician operator*(double scale, const statistician& s) {
		statistician answer;
		answer.count = s.count;
		answer.total = scale * s.total;
		if (scale <= 0) answer.tinyest = scale * s.largest;
			else answer.tinyest = scale * s.tinyest;
		if (scale <= 0) answer.largest = scale * s.tinyest;
			else answer.largest = scale * s.largest;
		return answer;
	}

	bool operator==(const statistician& s1, const statistician& s2) {
		if (s1.length() == 0 && s2.length() == 0)
			return true;
		return s1.length() == s2.length() && s1.sum() == s2.sum() && s1.mean() == s2.mean() 
		&& s1.minimum() == s2.minimum() && s2.maximum() == s2.maximum();
	}

}