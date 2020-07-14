#include <random>     // mt19937 and uniform_int_distribution
#include <algorithm>  // generate
#include <vector>     // vector
#include <iterator>   // begin, end, and ostream_iterator
#include <functional> // bind
#include <iostream>   // cout

std::vector<int> create_random_data(long int n) {
  std::random_device r;
  std::seed_seq      seed{r(), r(), r(), r(), r(), r(), r(), r()};
  std::mt19937       eng(seed); // a source of random data

  std::uniform_int_distribution<int> dist;
  std::vector<int> v(n);

  generate(begin(v), end(v), bind(dist, eng));
  return v;
}

bool binary_mismatch(std::vector<int>* vec1, std::vector<int>* vec2, std::string debug)
{
	if (vec1->size() != vec2->size())
	{
		return false;
	}

	int middle = vec1->size() / 2 - 1;
	if (middle <= 10)
	{
		for (short int i = 0; i != vec1->size(); i++) {
			if ((*vec1)[i] != (*vec2)[i]) {
				return false;
			}
		}
		return true;
	}
	
	if ((*vec1)[middle] != (*vec2)[middle])
	{
		return false;
	}

	std::vector<int> sub1L(vec1->begin(), vec1->begin() + middle + 1);
	std::vector<int> sub2L(vec2->begin(), vec2->begin() + middle + 1);

	bool resL = binary_mismatch(&sub1L, &sub2L, "left");
	if (!resL)
	{
		return false;
	}

	std::vector<int> sub1R(vec1->begin() + middle + 1, vec1->end());
	std::vector<int> sub2R(vec2->begin() + middle + 1, vec2->end());

	return binary_mismatch(&sub1R, &sub2R, "right");
}

int main() {
  std::vector<int> A = create_random_data(100000000);
	std::vector<int> B(A);
	
	A[49999999] = 34;

	auto res = std::mismatch(A.begin(), A.end(), B.begin());

	std::cout << *res.first << std::endl;

	// bool res = binary_mismatch(&A, &B, "left");
	// printf("res: %d\n", res);

	// std::vector<int> a = {1, 3, 2, 3, 54, 6, 9};
	// std::vector<int> b(a.begin() + a.size() / 2, a.end());
	// for (int el : b) {
	// 	std::cout << el << std::endl;
	// }

	return 0;
}