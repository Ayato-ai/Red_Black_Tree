#include "red_black_tree.h"
#include <gtest.h>

class red_black_tree_test : public ::testing::Test {
protected:
	void SetUp() {
		tree = new Red_Black_Tree();

		tree->insert(23);
		tree->insert(223);
		tree->insert(1);

		tree->insert(2);
		tree->insert(84);
		tree->insert(3);
		tree->insert(56);
		tree->insert(3000);
	}
	void TearDown() {
		delete tree;
	}

	Red_Black_Tree* tree;
};


TEST_F(red_black_tree_test, create_red_black_tree) {
	ASSERT_NO_THROW(this->SetUp());
};
TEST_F(red_black_tree_test, throw_red_black_tree_insert_new_key) {
	this->SetUp();

	ASSERT_NO_THROW(this->tree->insert(6));
};
TEST_F(red_black_tree_test, throw_red_black_tree_erase_key) {
	this->SetUp();

	ASSERT_NO_THROW(this->tree->erase(56));
};
TEST_F(red_black_tree_test, throw_red_black_tree_erase_root) {
	this->SetUp();

	ASSERT_NO_THROW(this->tree->erase(23));
};
TEST_F(red_black_tree_test, root_color_is_black) {
	this->SetUp();

	EXPECT_EQ(this->tree->find(23)->color, 0);
};
TEST_F(red_black_tree_test, throw_red_black_tree_insert_double_key) {
	this->SetUp();

	ASSERT_ANY_THROW(this->tree->insert(3000));
}
TEST_F(red_black_tree_test, throw_red_black_tree_erase_not_key) {
	this->SetUp();

	ASSERT_ANY_THROW(this->tree->erase(123));
}
TEST_F(red_black_tree_test, find_red_black_tree_correct) {
	this->SetUp();

	EXPECT_EQ((this->tree->find(3))->key, 3);
}
TEST_F(red_black_tree_test, find_red_black_tree_ancorrect) {
	this->SetUp();

	EXPECT_EQ((this->tree->find(123)), nullptr);
}
TEST_F(red_black_tree_test, correct_height_red_black_tree) {
	this->SetUp();
	Node* temp = this->tree->find(23);
	int height_1 = 0;
	int height_2 = 0;
	while (temp->left) {
		if (temp->color == black)
			height_1++;
		temp = temp->left;
	}
	temp = this->tree->find(23);
	while (temp->right) {
		if (temp->color == black)
			height_2++;
		temp = temp->right;
	}
	EXPECT_EQ(height_1, height_2);
}
TEST_F(red_black_tree_test, correct_height_AVL_tree_after_balance) {
	this->SetUp();
	this->tree->insert(456);

	Node* temp = this->tree->find(23);
	int height_1 = 0;
	int height_2 = 0;
	while (temp->left) {
		if (temp->color == black)
			height_1++;
		temp = temp->left;
	}
	if (temp->color == black)
		height_1++;

	temp = this->tree->find(23);
	while (temp->right) {
		if (temp->color == black)
			height_2++;
		temp = temp->right;
	}
	if (temp->color == black)
		height_2++;

	EXPECT_EQ(height_1, height_2);
}
TEST_F(red_black_tree_test, correct_height_AVL_tree_after_erase) {
	this->SetUp();
	this->tree->erase(3000);

	Node* temp = this->tree->find(23);
	int height_1 = 0;
	int height_2 = 0;
	while (temp->left) {
		if (temp->color == black)
			height_1++;
		temp = temp->left;
	}
	if (temp->color == black)
		height_1++;

	temp = this->tree->find(23);
	while (temp->right) {
		if (temp->color == black)
			height_2++;
		temp = temp->right;
	}
	if (temp->color == black)
		height_2++;

	EXPECT_EQ(height_1, height_2);
}
