
////////////////////////// Trees ////////////////////////////////





#include<iostream>

using namespace std;

class BST_node
{
	BST_node * left;
	BST_node * right;
	int value;

public:

	BST_node(int v, BST_node *  l = NULL, BST_node * r = NULL) : value(v), left(l), right(r)
	{}


	~BST_node()
	{

	}




	friend class BST;

	void insert_left(int v)
	{
		this->left = new BST_node(v);
	}

	void insert_right(int v)
	{
		this->right = new BST_node(v);
	}


	BST_node* right_successor()
	{
		BST_node * leftMost = right;

		while (leftMost->left != NULL && leftMost != NULL)
		{
			leftMost = right->left;
		}

		return leftMost;
	}


	bool is_leaf()
	{
		return (left == NULL && right == NULL);
	}




};

class BST
{
	BST_node * root;


	bool remove_node(BST_node* &root, int value)
	{
		BST_node * target = root;
		BST_node * parent = NULL;
		bool lefted;
		bool isRoot=true;


		if (target == NULL)
			return false;

		//Finding part
		while (target != NULL)
		{

			// if I finally found the Value break
			if (target->value == value)
				break;

			else if (target->value > value) // move left
			{
				parent = target;
				target = target->left;
				lefted = true;
				isRoot = false;
			}

			else if (target->value < value) // move right
			{
				parent = target;
				target = target->right;
				lefted = false;
				isRoot = false;
			}

		}

		if (target == NULL) // not found the element to delete it
			return false;

		// 3 cases are here

		if (target->is_leaf())
		{

		    if(isRoot)
            {
                delete root;
                root = NULL;
                return true;
            }


			delete target;
			if (lefted)
				parent->left = NULL;
			else
				parent->right = NULL;

			return true;
		}

		else if (target->right == NULL ) // target have one left child
		{

		    if(isRoot)
            {
                root =  target ->left;
                delete target;
                return true;
            }



			if (lefted)
				parent->left = target->left;
			else
				parent->right = target->left;
			delete target;
			return true;
		}

		else if (target->left == NULL) // target have one right child
		{


		    if(isRoot)
            {
                root =  target ->right;
                delete target;
                return true;
            }



			if (lefted)
				parent->left = target->right;
			else
				parent->right = target->right;
			delete target;
			return true;
		}






		else // have right and left
		{

				BST_node* leftMost = target->right_successor();

				target->value = leftMost->value;

			return remove_node(target->right,target-> value);
		}






	}

public:
	BST()
	{
		root = NULL;
	}

	~BST()
	{

	}

	BST_node* get_root()
	{
		return root;
	}

	bool insert_node(int value)
	{
		if (root == NULL)
		{
			root = new BST_node(value);
			return true;
		}
		BST_node* temp = root;

		while (temp != NULL)
		{
			if (temp->value == value)
				return false;

			else if (temp->value > value) // move left
			{

				if (temp->left == NULL)
				{
					temp->insert_left(value);
					return true;
				}

				temp = temp->left;
			}


			else if (temp->value < value) // move right
			{

				if (temp->right == NULL)
				{
					temp->insert_right(value);
					return true;
				}

				temp = temp->right;
			}


		}

	}

	bool remove_node(int value)
	{
		return remove_node(root, value);
	}


	void inorder_traversal(BST_node * root)
	{
		if (root == NULL)
			return;


		inorder_traversal(root->left);
		cout << root->value << endl;
		inorder_traversal(root->right);

	}


};

int main()
{

	BST test;

	cout << "----- insert -----" << endl;
	cout << "inserting 10 ->" << test.insert_node(10) << endl;
	cout << "inserting 5 ->" << test.insert_node(5) << endl;
	cout << "inserting 20 ->" << test.insert_node(20) << endl;
	cout << "inserting 3 ->" << test.insert_node(3) << endl;
	cout << "inserting 9 ->" << test.insert_node(9) << endl;
	cout << "inserting 25 ->" << test.insert_node(25) << endl;
	cout << "inserting 15 ->" << test.insert_node(15) << endl;
	cout << "inserting 1 ->" << test.insert_node(1) << endl;
	cout << "inserting 4 ->" << test.insert_node(4) << endl;
	cout << "inserting 13 ->" << test.insert_node(13) << endl;
	cout << "inserting 30 ->" << test.insert_node(30) << endl;
	cout << "inserting 17 ->" << test.insert_node(17) << endl;


	cout << "----- delete -----" << endl;
	cout << "deleting 7-> " << test.remove_node(7) << endl;
    cout << "deleting 5-> " << test.remove_node(5) << endl;
	cout << "deleting 5-> " << test.remove_node(5) << endl;
	cout << "deleting 7-> " << test.remove_node(7) << endl;


	test.inorder_traversal(test.get_root());


	return 0;
}


