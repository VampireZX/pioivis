#include "RBT.h"

NodePtr RBTree::searchTreeHelper(NodePtr node, int key) {
	if (node == TNULL || key == node->data) {
		return node;
	}

	if (key < node->data) {
		return searchTreeHelper(node->left, key);
	}
	return searchTreeHelper(node->right, key);
}

void RBTree::fixDelete(NodePtr x) {
	NodePtr s;
	while (x != root && x->color == 0) {
		if (x == x->parent->left) {
			s = x->parent->right;
			if (s->color == 1) {
				// case 3.1
				s->color = 0;
				x->parent->color = 1;
				leftRotate(x->parent);
				s = x->parent->right;
			}

			if (s->left->color == 0 && s->right->color == 0) {
				// case 3.2
				s->color = 1;
				x = x->parent;
			}
			else {
				if (s->right->color == 0) {
					// case 3.3
					s->left->color = 0;
					s->color = 1;
					rightRotate(s);
					s = x->parent->right;
				}

				// case 3.4
				s->color = x->parent->color;
				x->parent->color = 0;
				s->right->color = 0;
				leftRotate(x->parent);
				x = root;
			}
		}
		else {
			s = x->parent->left;
			if (s->color == 1) {
				// case 3.1
				s->color = 0;
				x->parent->color = 1;
				rightRotate(x->parent);
				s = x->parent->left;
			}

			if (s->left->color == 0 && s->right->color == 0) {
				// case 3.2
				s->color = 1;
				x = x->parent;
			}
			else {
				if (s->left->color == 0) {
					// case 3.3
					s->right->color = 0;
					s->color = 1;
					leftRotate(s);
					s = x->parent->left;
				}

				// case 3.4
				s->color = x->parent->color;
				x->parent->color = 0;
				s->left->color = 0;
				rightRotate(x->parent);
				x = root;
			}
		}
	}
	x->color = 0;
}

void RBTree::rbTransplant(NodePtr u, NodePtr v) {
	if (u->parent == nullptr) {
		root = v;
	}
	else if (u == u->parent->left) {
		u->parent->left = v;
	}
	else {
		u->parent->right = v;
	}
	v->parent = u->parent;
}

NodePtr RBTree::minimum(NodePtr node) {
	while (node->left != TNULL) {
		node = node->left;
	}
	return node;
}


NodePtr RBTree::maximum(NodePtr node) {
	while (node->right != TNULL) {
		node = node->right;
	}
	return node;
}

void RBTree::deleteNodeHelper(NodePtr node, int key) {
	// ищем вершину содержащую ключ
	NodePtr z = TNULL;
	NodePtr x, y;
	while (node != TNULL) {
		if (node->data == key) {
			z = node;
		}

		if (node->data <= key) {
			node = node->right;
		}
		else {
			node = node->left;
		}
	}

	y = z;
	int y_original_color = y->color;
	if (z->left == TNULL) {
		x = z->right;
		rbTransplant(z, z->right);
	}
	else if (z->right == TNULL) {
		x = z->left;
		rbTransplant(z, z->left);
	}
	else {
		y = minimum(z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->parent == z) {
			x->parent = y;
		}
		else {
			rbTransplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		rbTransplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	delete z;
	if (y_original_color == 0) {
		fixDelete(x);
	}
}

void RBTree::fixInsert(NodePtr k) {
	NodePtr u;
	while (k->parent->color == 1) {
		if (k->parent == k->parent->parent->right) {
			u = k->parent->parent->left; // дядя
			if (u->color == 1) {
				// case 3.1
				u->color = 0;
				k->parent->color = 0;
				k->parent->parent->color = 1;
				k = k->parent->parent;
			}
			else {
				if (k == k->parent->left) {
					// case 3.2.2
					k = k->parent;
					rightRotate(k);
				}
				// case 3.2.1
				k->parent->color = 0;
				k->parent->parent->color = 1;
				leftRotate(k->parent->parent);
			}
		}
		else {
			u = k->parent->parent->right; // дядя

			if (u->color == 1) {
				// mirror case 3.1
				u->color = 0;
				k->parent->color = 0;
				k->parent->parent->color = 1;
				k = k->parent->parent;
			}
			else {
				if (k == k->parent->right) {
					// mirror case 3.2.2
					k = k->parent;
					leftRotate(k);
				}
				// mirror case 3.2.1
				k->parent->color = 0;
				k->parent->parent->color = 1;
				rightRotate(k->parent->parent);
			}
		}
		if (k == root) {
			break;
		}
	}
	root->color = 0;
}

RBTree::RBTree() {
	TNULL = new Node;
	TNULL->color = 0;
	TNULL->left = nullptr;
	TNULL->right = nullptr;
	root = TNULL;
}

NodePtr RBTree::searchTree(int k) {
	if (root == TNULL)
		return TNULL;
	else
		return searchTreeHelper(this->root, k);
}

int RBTree::globalMinimum() {
	if (root == TNULL)
		return NULL;
	NodePtr node = root;
	while (node->left != TNULL) {
		node = node->left;
	}
	return node->data;
}

int RBTree::globalMaximum() {
	if (root == TNULL)
		return NULL;
	else {
		NodePtr node = root;
		while (node->right != TNULL) {
			node = node->right;
		}
		return node->data;
	}
}

void RBTree::leftRotate(NodePtr x) {
	NodePtr y = x->right;
	x->right = y->left;
	if (y->left != TNULL) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr) {
		this->root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

int RBTree::closestLesser(int k) {
	if (k < globalMinimum() || root == TNULL)
		return NULL;
	else {
		while (true) {
			k--;
			if (searchTree(k) != TNULL)
				return searchTree(k)->data;
		}
	}
}

void RBTree::rightRotate(NodePtr x) {
	NodePtr y = x->left;
	x->left = y->right;
	if (y->right != TNULL) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr) {
		this->root = y;
	}
	else if (x == x->parent->right) {
		x->parent->right = y;
	}
	else {
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}

void RBTree::insert(int key) {
	if (searchTree(key) != TNULL)
		return;
	else {
		NodePtr node = new Node;
		node->parent = nullptr;
		node->data = key;
		node->left = TNULL;
		node->right = TNULL;
		node->color = 1; // красная нода

		NodePtr y = nullptr;
		NodePtr x = this->root; //для наглядности

		while (x != TNULL) {
			y = x;
			if (node->data < x->data) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}

		// y родитель x
		node->parent = y;
		if (y == nullptr) {
			root = node;
		}
		else if (node->data < y->data) {
			y->left = node;
		}
		else {
			y->right = node;
		}

		// если родитель корень, возвращаем
		if (node->parent == nullptr) {
			node->color = 0;
			return;
		}

		// если прородитель нулевой, возвращаем
		if (node->parent->parent == nullptr) {
			return;
		}

		fixInsert(node);
	}
}

void RBTree::deleteNode(int data) {
	if (searchTree(data) == TNULL)
		return;
	else
		deleteNodeHelper(this->root, data);
}