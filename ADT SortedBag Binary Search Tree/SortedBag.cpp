#include "SortedBag.h"
#include "SortedBagIterator.h"

// complexity
// BC = AC = BC = theta(1)
// overall = theta(1)
SortedBag::SortedBag(Relation r) {

	this->root = NULL;
	this->relation = r;
	this->nrElements = 0;
}

// complexity
// BC = theta(1), the searched element is in the root
// AC = theta(log2n)
// WC = theta(n), if the BST is a degenerate one and the element should be in one of the leaves
// overall = O(n)
void SortedBag::add(TComp e) {

	BSTNode* currentNode = this->root;
	BSTNode* parentNode = NULL;

	while (currentNode != NULL)
	{
		if (currentNode->info.first == e)
		{
			// increase the frequency if the element already exists
			currentNode->info.second++;
			this->nrElements++;
			return;
		}

		parentNode = currentNode;

		if (this->relation(e, currentNode->info.first))
			currentNode = currentNode->left;
		else
			currentNode = currentNode->right;
	}

	// allocate memory for the new node, as the element does not already exist in the bag
	BSTNode* newBSTNode = new BSTNode;
	newBSTNode->info.first = e;
	newBSTNode->info.second = 1;
	newBSTNode->left = NULL;
	newBSTNode->right = NULL;

	if (this->root == NULL)
	{
		// it is the first node
		this->root = newBSTNode;
	}
	else
	{
		// check on which side of the parent it will be put
		if (this->relation(e, parentNode->info.first))
			parentNode->left = newBSTNode;
		else
			parentNode->right = newBSTNode;
	}

	this->nrElements++;
}

// complexity
// BC = theta(1), the searched element is in the root
// AC = theta(log2n)
// WC = theta(n), if the BST is a degenerate one and the element is in one of the leaves
// overall = O(n)
bool SortedBag::remove(TComp e) {
	
	BSTNode* currentNode = this->root;
	BSTNode* parentNode = NULL;

	while (currentNode != NULL)
	{
		if (currentNode->info.first == e)
			break;

		parentNode = currentNode;

		if (this->relation(e, currentNode->info.first))
			currentNode = currentNode->left;
		else
			currentNode = currentNode->right;
	}

	if (currentNode != NULL && currentNode->info.first == e)
	{
		// the element exists, check if we have to decrease the number of occurences or remove it(nrOccurences = 1)
		if (currentNode->info.second > 1)
		{
			// decrease the number of occurences
			currentNode->info.second--;
		}
		else
		{
			// remove the node

			if (currentNode->left == NULL && currentNode->right == NULL)
			{
				// no descendants
				if (currentNode == this->root)
					this->root = NULL;
				else
				{
					// check on which side of the parent it is
					if (this->relation(e, parentNode->info.first))
						parentNode->left = NULL;
					else
						parentNode->right = NULL;
				}

				delete currentNode;
			}
			else if (currentNode->right == NULL)
			{
				// it has only left descendant
				if (currentNode == this->root)
					this->root = this->root->left;
				else
				{
					// check on which side of the parent it is
					if (this->relation(e, parentNode->info.first))
						parentNode->left = currentNode->left;
					else
						parentNode->right = currentNode->left;
				}
				delete currentNode;
			}
			else if (currentNode->left == NULL)
			{
				// it has only right descendant
				if (currentNode == this->root)
					this->root = this->root->right;
				else
				{
					// check on which side of the parent it is
					if (this->relation(e, parentNode->info.first))
						parentNode->left = currentNode->right;
					else
						parentNode->right = currentNode->right;
				}
				delete currentNode;
			}
			else
			{
				// it has both left and right descendants
				// it will be replaced by its predecessor (the maximum element smaller than itself)
				// the predecessor is actually the maximum from the left subtree
				// only the info is changed

				// currentNode->left cannot be NULL
				currentNode->left->parent = currentNode;
				BSTNode* replacementNode = this->getMaximum(currentNode->left);

				// the replacement node can have at most the left descendant
				if (replacementNode->left == NULL)
				{
					// if the replacement node has no descendant
					// set the new links

					currentNode->info = replacementNode->info;

					if (replacementNode->parent == currentNode) // if replacement.parent == current
						replacementNode->parent->right = NULL;
					else
						currentNode->left = NULL;

					delete replacementNode;
				}
				else
				{
					// if the replacement has only a left descendant, it is just like the situation where we would remove
					// a node with only a left descendant

					// set the right of the parent of the replacement node to point to the replacement node's
					// left child
					BSTNode* childNode = replacementNode->left;

					if (replacementNode->parent == currentNode)
						replacementNode->parent->right = childNode;
					else
						currentNode->left = childNode;

					// set the new links
					currentNode->info = replacementNode->info;

					delete replacementNode;
				}
				
			}
		}

		this->nrElements--;
		return true;
	}

	return false;
}

// complexity
// BC = theta(1), the searched element is in the root
// AC = theta(log2n)
// WC = theta(n), if the BST is a degenerate one and the element does not exist
// overall = O(n)
bool SortedBag::search(TComp elem) const {

	BSTNode* currentNode = this->root;

	while (currentNode != NULL)
	{
		if (currentNode->info.first == elem)
			return true;

		if (this->relation(elem, currentNode->info.first))
			currentNode = currentNode->left;
		else
			currentNode = currentNode->right;
	}

	return false;
}

// complexity
// BC = theta(1), the searched element is in the root
// AC = theta(log2n)
// WC = theta(n), if the BST is a degenerate one and the element does not exist
// overall = O(n)
int SortedBag::nrOccurrences(TComp elem) const {

	BSTNode* currentNode = this->root;

	while (currentNode != NULL)
	{
		if (currentNode->info.first == elem)
			return currentNode->info.second;

		if (this->relation(elem, currentNode->info.first))
			currentNode = currentNode->left;
		else
			currentNode = currentNode->right;
	}

	return 0;
}

// complexity
// BC = AC = BC = theta(1)
// overall = theta(1)
int SortedBag::size() const {
	
	return this->nrElements;
}

// complexity
// BC = AC = BC = theta(1)
// overall = theta(1)
bool SortedBag::isEmpty() const {
	
	if (this->root == NULL)
		return true;
	return false;
}

// complexity
// BC = AC = BC = theta(1)
// overall = theta(1)
SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}

// complexity
// BC = AC = BC = theta(n)
// overall = theta(n)
SortedBag::~SortedBag() {

	std::stack<BSTNode*> stack{};
	BSTNode* currentNode = this->root;
	BSTNode* deletedNode = NULL;

	while (currentNode != NULL)
	{
		stack.push(currentNode);
		currentNode = currentNode->left;
	}
	
	while (!stack.empty())
	{
		currentNode = stack.top();
		stack.pop();
		deletedNode = currentNode;

		currentNode = currentNode->right;
		while (currentNode != NULL)
		{
			stack.push(currentNode);
			currentNode = currentNode->left;
		}

		delete deletedNode;
	}
}

// complexity
// BC = AC = BC = theta(n) - it traverses all the nodes
// overall = theta(n)
// extra space compexity = O(n)
int SortedBag::uniqueCount() const
{
	std::stack<BSTNode*> stack{};
	BSTNode* currentNode = this->root;
	int numberUniqueElements = 0;

	while (currentNode != NULL)
	{
		stack.push(currentNode);
		currentNode = currentNode->left;
	}

	while (!stack.empty())
	{
		currentNode = stack.top();
		stack.pop();
		numberUniqueElements++;

		currentNode = currentNode->right;
		while (currentNode != NULL)
		{
			stack.push(currentNode);
			currentNode = currentNode->left;
		}

	}

	return numberUniqueElements;
}

// complexity
// BC = theta(1), the searched element is the startNode
// AC = theta(log2n)
// WC = theta(n), if the BST is a degenerate one and the element is in a leaf
// overall = O(n)
BSTNode* SortedBag::getMaximum(BSTNode* startNode)
{
	BSTNode* currentNode = new BSTNode{};
	currentNode->info = startNode->info;
	currentNode->left = startNode->left;
	currentNode->right = startNode->right;

	BSTNode* parentNode = startNode->parent;

	while (currentNode->right != NULL)
	{
		parentNode = currentNode;
		currentNode = currentNode->right;
	}

	if(parentNode != NULL)
		currentNode->parent = parentNode;

	return currentNode;
}
