#include "red_black_tree.h"
using namespace std;


int main() {
	setlocale(2, "rus");

	Red_Black_Tree tree;
	size_t k = 0;
	cout << "Добавьте элементы в красно - черное дерево" << endl;
	cin >> k;
	tree.insert(k);
	while (k != 1) {
		cin >> k;
		try {
			tree.insert(k);
		}
		catch (const std::logic_error& e) {
			std::cout << e.what() << std::endl;
			exit(-1);
		}
	}
	cout << "Удалите элементы в красно - черном дереве" << endl;
	cin >> k;
	while (k != 1) {

		try {
			tree.erase(k);
		}
		catch (const std::logic_error& e) {
			std::cout << e.what() << std::endl;
			exit(-1);
		}
		cin >> k;
	}
	tree.print();
	cout << "Где 0 - черное звено и 1 - красное" << endl;
	return 0;
}