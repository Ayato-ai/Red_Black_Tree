// UNN, IITMM, Course "Algorithms and Data Structures"
// 
// Noskov I.A.

#pragma once
#include<iostream>

enum colors { black, red };

struct Node {
	Node* parent;
	Node* left;
	Node* right;
	colors color;
	std::size_t key;
	Node(colors c = black, std::size_t k = 0) {
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		color = c;
		key = k;
	}
};

class Red_Black_Tree {
public:
	Red_Black_Tree() {
		root = nullptr;
	};
	Red_Black_Tree(Node* node) {
		root = node;
	};

	//void erase(std::size_t key) {
	//	Node* temp = find(key);
	//	Node* new_root = nullptr;
	//	if (temp == nullptr)
	//		throw std::logic_error("key_infallible");
	//	else {
	//		if (temp->left == nullptr && temp->right == nullptr) { //нет детей
	//			if (temp == root)
	//				root = nullptr;
	//			else {
	//				if (temp->parent->left == temp)
	//					temp->parent->left == nullptr;
	//				else
	//					temp->parent->right = nullptr;
	//			}
	//			return;
	//		}

	//		if ((temp->left && temp->right == nullptr) || (temp->right && temp->left == nullptr)) { //Один ребенок
	//			if (temp->parent->left == temp) {
	//				if (temp->left) {
	//					temp->left->parent = temp->parent;
	//					temp->parent->left = temp->left;
	//				}
	//				else {
	//					temp->right->parent = temp->parent;
	//					temp->parent->left = temp->right;
	//				}
	//			}
	//			else {
	//				if (temp->left) {
	//					temp->left->parent = temp->parent;
	//					temp->parent->right = temp->left;
	//				}
	//				else {
	//					temp->right->parent = temp->parent;
	//					temp->parent->right = temp->right;
	//				}
	//			}

	//			temp = nullptr;
	//			return;
	//		}

	//		if (temp->left && temp->right) { // Два ребенка
	//			Node* min_elem = find_min(temp->right);
	//			//colors save_color = min_elem->color;
	//			new_root = min_elem->right;


	//			if (temp == root) {
	//				min_elem->left = temp->left;
	//				min_elem->right = temp->right;
	//				min_elem->parent->left = nullptr;
	//				min_elem->parent = nullptr;
	//				min_elem->color = black;
	//				root = min_elem;
	//			}
	//			else {

	//				if (new_root) {
	//					new_root->parent = min_elem->parent;
	//					/*if (min_elem->parent == temp)
	//						new_root->parent = min_elem;*/

	//						//min_elem -> new_root
	//					if (min_elem == min_elem->parent->left)
	//						min_elem->parent->left = new_root;
	//					else
	//						min_elem->parent->right = new_root;
	//					new_root->parent = min_elem->parent;

	//					min_elem->right = temp->right;
	//					min_elem->right->parent = min_elem;
	//				}

	//				//temp -> min_elem

	//				if (temp == temp->parent->left)
	//					temp->parent->left = min_elem;
	//				else
	//					temp->parent->right = min_elem;
	//				min_elem->parent = temp->parent;

	//				min_elem->left = temp->left;
	//				min_elem->left->parent = min_elem;
	//				min_elem->color = temp->color;
	//			}
	//		}

	//	}
	//};

	void insert(std::size_t key) {
		Node* new_node = new Node(red, key);
		Node* par = nullptr;
		Node* this_node;
		this_node = root;

		if (root == nullptr) {
			new_node->color = black;
			root = new_node;
			return;
		}
		else {
			while (this_node) {
				par = this_node;
				if (this_node->key > key)
					this_node = this_node->left;

				else if (this_node->key < key)
					this_node = this_node->right;

				else if (this_node->key == key)
					throw std::logic_error("key_infallible");

			}
			if (par->key > key) {
				par->left = new_node;
				new_node->parent = par;
			}
			if (par->key < key) {
				par->right = new_node;
				new_node->parent = par;
			}
		}
		balance(new_node);
	};
	Node* find(std::size_t key) {
		return find(root, key);
	};

	void print() const {
		print(root);
	}

	void erase(std::size_t key) {
		deleteNode(root, key);
	}

	~Red_Black_Tree() {
		delete_Red_Black_Tree(root);
	};


private:
	Node* root;

	Node* find(Node* node, std::size_t key) {
		if (node->key == key)
			return node;
		if (node->key > key) {
			if (node->left)
				return find(node->left, key);
			else
				return nullptr;
		}
		if (node->key < key) {
			if (node->right)
				return find(node->right, key);
			else
				return nullptr;
		}
		return nullptr;

	};

	Node* find_min(Node* node) {
		while (node && node->left)
			node = node->left;
		return node;
	};

	void balance(Node* node) {
		Node* temp;
		while (node != root && node->parent->color == red && node->parent->parent) {
			if (node->parent == node->parent->parent->left) {
				temp = node->parent->parent->right;


				if (temp && temp->color == red) {
					node->parent->color = black;
					temp->color = black;
					node->parent->parent->color = red;
					node = node->parent->parent;
				}
				else {
					if (node == node->parent->right) {
						node = node->parent;
						left_turn(node);
					}


					node->parent->color = black;
					node->parent->parent->color = red;
					right_turn(node->parent->parent);
				}
			}
			else {
				temp = node->parent->parent->left;


				if (temp && temp->color == red) {
					node->parent->color = black;
					temp->color = black;
					node->parent->parent->color = red;
					node = node->parent->parent;
				}
				else {
					if (node == node->parent->left) {
						node = node->parent;
						right_turn(node);
					}

					node->parent->color = black;
					node->parent->parent->color = red;
					left_turn(node->parent->parent);
				}
			}
		}

		root->color = black;
	};


	void right_turn(Node* node) {
		Node* new_root = node->left;
		node->left = new_root->right;

		if (new_root->right)
			new_root->right->parent = node;

		new_root->parent = node->parent;

		if (node->parent == nullptr)
			root = new_root;
		else if (node->parent->right == node)
			node->parent->right = new_root;
		else
			node->parent->left = new_root;

		new_root->right = node;
		node->parent = new_root;
	};


	void left_turn(Node* node) {
		Node* new_root = node->right;
		node->right = new_root->left;

		if (new_root->left)
			new_root->left->parent = node;

		new_root->parent = node->parent;

		if (node->parent == nullptr)
			root = new_root;
		else if (node->parent->right == node)
			node->parent->right = new_root;
		else
			node->parent->left = new_root;

		new_root->left = node;
		node->parent = new_root;
	};


	void print(Node* node) const {
		if (node)
			std::cout << node->key << " - " << (node->color) << std::endl;
		else
			return;
		print(node->left);
		print(node->right);
	}

	void replace_root(Node* node, Node* new_node) {
		if (node->parent == nullptr)
			root = new_node;
		else if (node == node->parent->left)
			node->parent->left = new_node;
		else
			node->parent->right = new_node;
		if (new_node)
			new_node->parent = node->parent;
	}

	void fix_erase(Node* node) {
		while (node && node != root && node->color == black) {
			if (node == node->parent->left) {
				Node* parent_node = node->parent->right;

				if (parent_node->color == red) {
					parent_node->color = black;
					node->parent->color = red;
					left_turn(node->parent);
					parent_node = node->parent->right;
				}

				if (parent_node->left->color == black &&
					parent_node->right->color == black) {
					parent_node->color = red;
					node = node->parent;
				}
				else {
					if (parent_node->right->color == black) {
						parent_node->left->color = black;
						parent_node->color = red;
						right_turn(parent_node);
						parent_node = node->parent->right;
					}
					parent_node->color = node->parent->color;
					node->parent->color = black;
					parent_node->right->color = black;
					left_turn(node->parent);
					node = root;
				}
			}
			else {
				Node* parent_node = node->parent->left;

				if (parent_node->color == red) {
					parent_node->color = black;
					node->parent->color = red;
					right_turn(node->parent);
					parent_node = node->parent->left;
				}

				if (parent_node->left->color == black && parent_node->right->color == black) {
					parent_node->color = red;
					node = node->parent;
				}
				else {
					if (parent_node->left->color == black) {
						parent_node->right->color = black;
						parent_node->color = red;
						left_turn(parent_node);
						parent_node = node->parent->left;
					}
					parent_node->color = node->parent->color;
					node->parent->color = black;
					parent_node->left->color = black;
					right_turn(node->parent);
					node = root;
				}
			}
		}
		if (node)
			node->color = black;
	}

	void deleteNode(Node* node, std::size_t key) {
		Node* delete_node = nullptr;
		Node* this_node = node;
		Node* nodeToFix = nullptr;
		Node* temp_node = nullptr;

		delete_node = find(root, key);

		if (delete_node == nullptr)
			throw std::logic_error("key_infallible");

		temp_node = delete_node;
		colors temp_color = temp_node->color;

		if (delete_node->left == nullptr) {
			nodeToFix = delete_node->right;
			replace_root(delete_node, delete_node->right);
		}
		else if (delete_node->right == nullptr) {
			nodeToFix = delete_node->left;
			replace_root(delete_node, delete_node->left);
		}

		else {
			temp_node = find_min(delete_node->right);
			temp_color = temp_node->color;
			nodeToFix = temp_node->right;


			if (temp_node->parent == delete_node) {
				if (nodeToFix)
					nodeToFix->parent = temp_node;
			}
			else {
				replace_root(temp_node, temp_node->right);
				temp_node->right = delete_node->right;
				temp_node->right->parent = temp_node;
			}

			replace_root(delete_node, temp_node);
			temp_node->left = delete_node->left;
			temp_node->left->parent = temp_node;
			temp_node->color = delete_node->color;
		}

		delete delete_node;

		if (temp_color == black) {
			fix_erase(nodeToFix);
		}
	}

	void delete_Red_Black_Tree(Node* node) {
		if (node) {
			delete_Red_Black_Tree(node->left);
			delete_Red_Black_Tree(node->right);
			delete node;
		}
	}
};
