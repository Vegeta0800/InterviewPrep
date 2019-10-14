
#include "pch.h"
#include <iostream>
#include <unordered_set>
#include <vector>
#include <functional>
#include <string>

template <typename T>
struct Node
{
public:
	T value;
	Node* next = nullptr;

	Node(T data)
	{
		this->value = data;
		this->next = nullptr;
	}

	Node(Node<T>* data)
	{
		this->value = data->value;
		this->next = data->next;
	}
};

template <typename T>
struct LinkedList
{
	Node<T>* node;

	LinkedList()
	{
		node = nullptr;
	}

	virtual void Add(T data) 
	{
		Node<T>* temp =  new Node<T>(data);
		temp->next = node;
		node = temp;
	};

	virtual void Print()
	{
		Node<T>* temp = node;
		while (temp != nullptr) {
			std::cout << temp->value << " ";
			temp = temp->next;
		}

		std::cout << std::endl;
	}

	virtual void DeleteNode(int index)
	{
		Node<T>* current = node;
		Node<T>* previous = nullptr;

		int i = 0;
		while (current != nullptr)
		{
			if (i == index)
				break;

			previous = current;
			current = current->next;
			i++;
		}

		if (i == 0)
			node = node->next;
		else if (current->next == nullptr)
			previous->next = nullptr;
		else
			previous->next = current->next;
	}

	virtual void DeleteDuplicates()
	{
		Node<T>* current = node;
		Node<T>* previous = nullptr;

		std::unordered_set<T> set;

		while (current != nullptr)
		{
			if (set.find(current->value) != set.end())
			{
				if (current->next == nullptr)
					previous->next = nullptr;
				else
					previous->next = current->next;
			}

			set.insert(current->value);

			previous = current;
			current = current->next;
		}
	}

	virtual Node<T>* GetNode(int index)
	{
		Node<T>* current = new Node<T>(node);

		int i = 0;
		while (current != nullptr)
		{
			if (i == index)
				return current;

			current = current->next;
			i++;
		}

		delete current;
		return nullptr;
	}

	virtual void RemoveEvenNumbers()
	{
		Node<int>* current = node;
		Node<int>* prev = nullptr, *next = node->next;

		while (current != nullptr)
		{
			next = current->next;

			if (current->value % 2 == 0)
			{
				if (prev != nullptr)
				{
					current = prev;
					current->next = next;
				}
				else
				{
					current = next;
				}
			}

			prev = current;
			current = next;
		}
	}

	virtual void Reverse()
	{
		int counter = 0; 

		Node<T>* current = node;
		Node<T>* prev = nullptr, * next = nullptr;

		while (current != nullptr) 
		{
			next = current->next;

			current->next = prev;

			prev = current;
			current = next;
		}
		node = prev;
	}

	virtual bool HasCycle()
	{
		Node<T>* current = new Node<T>(node);

		std::unordered_set<Node<T>*> set;

		while (current != nullptr)
		{
			if (set.find(current) != set.end())
			{
				delete current;
				return true;
			}

			set.insert(current);

			current = current->next;
		}

		delete current;
		return false;
	}
};

enum class CalculateMode
{
	ADD = 0,
	SUBTRACT = 1,
	MULTIPLY = 2,
	DIVIDE = 3,
	NONE = 4
};

template <typename T>
class Stack
{
public:
	Stack()
	{
		this->m = -1;
		this->size = 8;
		this->elements = new T[size];
	}

	~Stack()
	{
		delete[] elements;
	}

	void PushBack(T element)
	{
		m++;
		elements[m] = element;

		if (m > size)
		{
			T* tempElements = new T[size * 2];
			memcpy(tempElements, elements, size);
			size *= 2;
		}
	}

	void Pop()
	{
		m--;

		if (m < size / 4)
		{
			T* tempElements = new T[size / 2];
			memcpy(tempElements, elements, size);
			size /= 2;
		}
	}

	T Top()
	{
		return elements[m];
	}

	bool Empty()
	{
		return (m < 0 || m > size);
	}

	int Size()
	{
		return m + 1;
	}

private:
	T* elements = nullptr;
	int m = -1;
	int size = 8;
};

template <typename T>
struct Queue
{
	Queue()
	{
		queueStart = nullptr;
		queueEnd = nullptr;
		size = 0;
	}

	~Queue()
	{
		delete queueStart;
		delete queueEnd;
	}

	void Push(T element)
	{
		Node<T>* temp = new Node<T>(element);

		if (size == 0)
		{
			queueStart = temp;
			queueEnd = queueStart;
		}
		else
		{
			queueEnd->next = temp;
			queueEnd = queueEnd->next;
		}

		size++;
	}

	void Pop()
	{
		if (size == 1)
			queueStart = nullptr;
		else
			queueStart = queueStart->next;
		size--;
	}

	void Print()
	{
		Node<T>* temp = new Node<T>(queueStart);

		while (temp != queueEnd)
		{
			std::cout << temp->value << " ";
			temp = temp->next;
		}

		std::cout << queueEnd->value << std::endl;
		
		temp = nullptr;
		delete temp;
	}

	void Reverse()
	{
		Stack<T> stack;

		while (!this->isEmpty())
		{
			stack.PushBack(this->GetFront());
			this->Pop();
		}

		while (!stack.Empty())
		{
			this->Push(stack.Top());
			stack.Pop();
		}
	}

	void Clear()
	{
		while (!this->isEmpty())
		{
			this->Pop();
		}
	}

	int GetSize()
	{
		return this->size;
	}

	bool isEmpty()
	{
		return (this->size == 0);
	}

	T GetFront()
	{
		return this->queueStart->value;
	}

	T GetBack()
	{
		return this->queueEnd->value;
	}

	Node<T>* queueStart;
	Node<T>* queueEnd;
	int size;
};

template<typename T>
struct CircleQueue
{
	CircleQueue(int size)
	{
		front = -1;
		back = 0;

		this->size = size;
		this->arr = new T[size];
	}

	void Push(T element)
	{
		if (front == back && front != -1)
		{
			return;
		}
		else
		{
			if (front == -1)
				front = 0;

			arr[back] = element;

			if (back == this->size - 1 && front != 0)
				back = 0;
			else
				back++;
		}
	}

	void Pop()
	{
		if (front != -1)
		{
			arr[front] = INT_MIN;
			front++;

			if (front > back)
				front = -1;
		}
	}

	void Print()
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << arr[i] << " ";
		}
	}

	int size;
	T* arr;

	int front;
	int back;
};

template<typename T>
struct Leaf	
{
	T value;
	Leaf* left;
	Leaf* right;

	Leaf(T val)
	{
		value = val;
		left = nullptr;
		right = nullptr;
	}

};

int height(Leaf<int>* node)
{
	if (node == nullptr)
		return 0;
	else
	{
		int lheight = height(node->left);
		int rheight = height(node->right);

		if (lheight > rheight)
			return(lheight + 1);
		else
			return(rheight + 1);
	}
}

class Graph
{
public:
	Graph(int V)
	{
		this->V = V;
		this->adj.resize(V);
	}
	void AddEdge(int v, int w)
	{
		this->adj[v].push_back(w);
	}

	void DFS()
	{
		std::vector<bool> visited(this->V, false);

		for (int i = 0; i < this->V; i++)
		{
			if (!visited[i])
				DFSRoutine(i, visited);
		}
	}

	void Travesal()
	{
		std::vector<bool> visited(this->V, false);

		for (int i = 0; i < this->V; i++)
		{
			if (!visited[i])
				TraversalRoutine(i, visited);
		}
	}

private:
	void DFSRoutine(int s, std::vector<bool> &visited)
	{
		Stack<int> stack;

		stack.PushBack(s);

		while (!stack.Empty())
		{
			s = stack.Top();
			stack.Pop();

			if (!visited[s])
			{
				visited[s] = true;
				std::cout << s << " ";
			}

			for (uint16_t i = 0; i < adj[s].size(); i++)
			{
				if (!visited[adj[s][i]])
					stack.PushBack(adj[s][i]);
			}
		}
	}

	void TraversalRoutine(int s, std::vector<bool> &visited)
	{
		Queue<int> queue;

		queue.Push(s);

		while (!queue.isEmpty())
		{
			int temp = queue.GetFront();
			queue.Pop();

			if (!visited[temp])
			{
				visited[temp] = true;
				std::cout << temp << " ";
			}

			for (int i = 0; i < adj[temp].size(); i++)
			{
				if (!visited[adj[temp][i]])
					queue.Push(adj[temp][i]);
			}
		}
	}

	int V;    
	std::vector<std::vector<int>> adj;    
};

bool CheckBalancedParentheses(const char* expression, int length)
{
	char currentParenth;
	Stack<char> chars;

	for (int i = 0; i < length; i++)
	{
		if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{')
		{
			chars.PushBack(expression[i]);
			continue;
		}

		if (chars.Empty())
			return false;

		switch (expression[i])
		{
		case ')':
			currentParenth = chars.Top();
			chars.Pop();
			if (currentParenth == '{' || currentParenth == '[')
				return false;
			break;

		case '}':
			currentParenth = chars.Top();
			chars.Pop();
			if (currentParenth == '(' || currentParenth == '[')
				return false;
			break;

		case ']':
			currentParenth = chars.Top();
			chars.Pop();
			if (currentParenth == '(' || currentParenth == '{')
				return false;
			break;
		}
	}

	// Check Empty Stack 
	return (chars.Empty());
}

int EvaluateLanguage(const char* expression, int length)
{
	Stack<char> stack;
	CalculateMode mode = CalculateMode::NONE;

	for (int i = 0; i < length; i++)
	{
		if (expression[i] == '(')
		{
			stack.PushBack(expression[i]);
			continue;
		}

		if (stack.Empty())
			continue;

		if (mode == CalculateMode::NONE)
		{
			switch (expression[i])
			{
			case '+':
				mode = CalculateMode::ADD;
				continue;
				break;
			case '-':
				mode = CalculateMode::SUBTRACT;
				continue;
				break;
			case '*':
				mode = CalculateMode::MULTIPLY;
				continue;
				break;
			case '/':
				mode = CalculateMode::DIVIDE;
				continue;
				break;
			}
		}

		if (expression[i] < 58 && expression[i] > 47)
		{
			stack.PushBack(expression[i]);
		}

		if (expression[i] == ')')
		{
			stack.PushBack(')');
			break;
		}
	}

	int value = 0;
	int size = stack.Size();

	for (int i = 0; i < size; i++)
	{
		if (stack.Top() != '(' && stack.Top() != ')')
		{
			if (value == 0)
			{
				value = stack.Top() - 48;
				stack.Pop();
				continue;
			}

			switch (mode)
			{
			case CalculateMode::ADD:
				value += (stack.Top() - 48);
				break;
			case CalculateMode::SUBTRACT:
				value -= (stack.Top() - 48);
				break;
			case CalculateMode::MULTIPLY:
				value *= (stack.Top() - 48);
				break;
			case CalculateMode::DIVIDE:
				value /= (stack.Top() - 48);
				break;
			}

		}
		stack.Pop();
	}

	return value;
}

class Nimm
{
public:
	Nimm(int size)
	{
		rows.resize(size);
	}

	~Nimm()
	{
		rows.clear();
	}

	void DrawBoard()
	{
		for (int i = 0; i < this->rows.size(); i++)
		{
			for (int j = 0; j < this->rows[i]; j++)
			{
				std::cout << '|';
			}

			std::cout << '\n';
		}
	}

	std::vector<int>& GetRows()
	{
		return this->rows;
	}

	void Game()
	{
		running = true;
		KnowWinnerBeforePlaying();

		while (running)
		{
			DrawBoard();

			if (this->player1Turn)
			{
				int inputIndex;

				std::cout << "Input row between 1 and " << rows.size() << ": ";
				std::cin >> inputIndex;
				std::cout << '\n';

				if (inputIndex <= rows.size() && inputIndex > 0 && rows[inputIndex - 1] > 0)
				{
					inputIndex--;

					bool validInput = false;

					while (!validInput)
					{
						int inputAmount;

						std::cout << "How many do you wish to remove " << rows[inputIndex] << " : ";
						std::cin >> inputAmount;
						std::cout << '\n';

						if (inputAmount > 0 && inputAmount <= rows[inputIndex])
						{
							validInput = true;
							this->player1Turn = false;
							rows[inputIndex] -= inputAmount;

							if (rows[inputIndex] <= 0)
							{
								bool empty = true;

								for (int i = 0; i < rows.size(); i++)
								{
									if (rows[i] > 0)
										empty = false;
								}

								if (empty)
									running = false;
							}
						}
					}
				}
				else
				{
					std::cout << "Invalid Input" << std::endl;
				}
			}
			else
			{
				DoComputerMove();
			}
		}

		if (this->player1Turn)
			std::cout << "Computer won" << std::endl;
		else
			std::cout << "Player 1 won" << std::endl;
	}

	int CalculateNimSum()
	{
		int i, nimsum = this->rows[0];
		for (i = 1; i < this->rows.size(); i++)
			nimsum = nimsum ^ this->rows[i];
		return(nimsum);
	}

	void DoComputerMove()
	{
		int i, nim_sum = CalculateNimSum();

		if (nim_sum != 0)
		{
			for (i = 0; i < this->rows.size(); i++)
			{
				if ((this->rows[i] ^ nim_sum) < this->rows[i])
				{
					std::cout << "Computer removed " << this->rows[i] - (this->rows[i] ^ nim_sum) <<
						" stones from row " << (i + 1) << "." << std::endl;

					this->rows[i] = (this->rows[i] ^ nim_sum);
					this->player1Turn = true;

					if (rows[i] <= 0)
					{
						bool empty = true;

						for (int k = 0; k < rows.size(); k++)
						{
							if (rows[k] > 0)
								empty = false;
						}

						if (empty)
							running = false;
					}
					break;
				}
			}
		}
		else
		{
			std::vector<int> non_zero_indices(this->rows.size());
			int count;

			for (i = 0, count = 0; i < this->rows.size(); i++)
				if (this->rows[i] > 0)
					non_zero_indices[count++] = i;

			int index = (rand() % (count));
			int remove =
				1 + (rand() % (this->rows[index]));
			this->rows[index] =
				this->rows[index] - remove;

			if (this->rows[index] < 0)
				this->rows[index] = 0;

			std::cout << "Computer removed " << remove <<
				" stones from row " << (index + 1) << "." << std::endl;

			if (rows[index] <= 0)
			{
				bool empty = true;

				for (int k = 0; k < rows.size(); k++)
				{
					if (rows[k] > 0)
						empty = false;
				}

				if (empty)
					running = false;
			}

			this->player1Turn = true;
		}
		return;
	}

	void KnowWinnerBeforePlaying()
	{
		std::cout << "Computer has already won!" << std::endl;

		if (CalculateNimSum() != 0)
		{
			player1Turn = false;
		}
		else
		{
			player1Turn = true;
		}

		return;
	}


private:
	std::vector<int> rows;
	bool player1Turn;
	bool running;
};

bool CheckIfPalindrome(const char* input, int start, int end)
{
	for (int i = ((end - start) - 1); i >= 0; i--)
	{
		size_t hashOne = std::hash<char>() (input[i]);
		size_t hashTwo = std::hash<char>() (input[((end - start) - (i +  1))]);

		if (hashOne != hashTwo)
			return false;
	}

	return true;
}

template<typename T>
class Tree
{
public:
	void PreorderTraversalRecursion(Leaf<T>* root)
	{
		if (root == nullptr)
			return;

		std::cout << root->value << " ";

		PreorderTraversalRecursion(root->left);
		PreorderTraversalRecursion(root->right);
	}
	void InorderTraversalRecursion(Leaf<T>* root)
	{
		if (root == nullptr)
			return;

		InorderTraversalRecursion(root->left);

		std::cout << root->value << " ";

		InorderTraversalRecursion(root->right);
	}
	void PostorderTraversalRecursion(Leaf<T>* root)
	{
		if (root == nullptr)
			return;

		PostorderTraversalRecursion(root->left);
		PostorderTraversalRecursion(root->right);

		std::cout << root->value << " ";

	}
	void LevelOrderRoutine(Leaf<T>* node, int i)
	{
		if (node == nullptr)
			return;
		if (i == 1)
			std::cout << node->value << " ";
		else if (i > 1)
		{
			LevelOrderRoutine(node->left, i - 1);
			LevelOrderRoutine(node->right, i - 1);
		}
	}
	void LevelOrderTraversalRecursion(Leaf<T>* root)
	{
		int h = height(root);

		for (int i = 1; i <= h; i++)
			LevelOrderRoutine(root, i);
	}

	void PreorderTraversalIterative(Leaf<T>* root)
	{
		Stack<Leaf<T>*> stack;

		Leaf<T>* current = root;

		while (true)
		{
			while (current != nullptr)
			{
				std::cout << current->value << " ";
				stack.PushBack(current);
				current = current->left;
			}

			if (stack.Empty())
				return;

			current = stack.Top();
			stack.Pop();
			current = current->right;
		}
	}
	void InorderTraversalIterative(Leaf<T>* root)
	{
		Stack<Leaf<T>*> stack;

		Leaf<T>* current = root;

		while (true)
		{
			while (current != nullptr)
			{
				stack.PushBack(current);
				current = current->left;
			}

			if (stack.Empty())
				return;

			current = stack.Top();
			std::cout << current->value << " ";
			stack.Pop();
			current = current->right;
		}
	}
	void PostorderTraversalIterative(Leaf<T>* root)
	{
		Stack<Leaf<T>*> stack;

		Leaf<T>* current = root;

		do
		{
			while (current != nullptr)
			{

				if (current->right != nullptr)
					stack.PushBack(current->right);

				stack.PushBack(current);

				current = current->left;
			}

			current = stack.Top();
			stack.Pop();

			if (current->right != nullptr && stack.Top() == current->right)
			{
				stack.Pop();
				stack.PushBack(current);
				current = current->right;
			}
			else
			{
				std::cout << current->value << " ";
				current = nullptr;
			}
		} while (!stack.Empty());
	}
	void LevelOrderTraversalIterative(Leaf<T>* root)
	{
		if (root == nullptr) return;

		Queue<Leaf<T>*> q;

		q.Push(root);

		while (q.isEmpty() == false)
		{
			int nodeCount = q.GetSize();

			while (nodeCount > 0)
			{
				Leaf<T>*  node = q.GetFront();
				std::cout << node->value << " ";
				q.Pop();
				if (node->left != nullptr)
					q.Push(node->left);
				if (node->right != nullptr)
					q.Push(node->right);
				nodeCount--;
			}

			std::cout << std::endl;
		}
	}

	int FindMaximum(Leaf<T>* root)
	{
		if (root == nullptr) return 0;

		int val = root->value;
		int lval = FindMaximum(root->left);
		int rval = FindMaximum(root->right);

		if (lval > val)
			val = lval;
		if (rval > val)
			val = rval;

		return val;
	}
	int CountNodes(Leaf<T>* root)
	{
		if (root == nullptr) return 0;

		return (1 + CountNodes(root->left) + CountNodes(root->right));
	}
	bool isComplete(Leaf<T>* root, int index, int nodeAmount)
	{
		if (root == nullptr) return true;

		if (index >= nodeAmount)
			return (false);

		return (isComplete(root->left, 2 * index + 1, nodeAmount) &&
			isComplete(root->right, 2 * index + 2, nodeAmount));
	}
	T PrintSumOfLevels(Leaf<T>* root)
	{
		if (root == nullptr) return NULL;

		Queue<Leaf<T>*> q;

		T totalSum = NULL;

		q.Push(root);

		while (q.isEmpty() == false)
		{
			int nodeCount = q.GetSize();

			T sumOfLevel = NULL;

			while (nodeCount > 0)
			{
				Leaf<T>*  node = q.GetFront();
				sumOfLevel += node->value;
				totalSum += node->value;
				q.Pop();
				if (node->left != nullptr)
					q.Push(node->left);
				if (node->right != nullptr)
					q.Push(node->right);
				nodeCount--;
			}

			std::cout << sumOfLevel << std::endl;
		}

		return totalSum;
	}
	bool FindValue(Leaf<T>* root, T value)
	{
		if (root == nullptr) return false;

		bool l = FindValue(root->left, value);
		bool r = FindValue(root->right, value);

		if (root->value == value) return true;

		return l | r;
	}
	bool FindSubtree(Leaf<T>* root, T value)
	{
		if (root == nullptr) return false;

		T lV = PrintSumOfLevels(root->left);
		T rV = PrintSumOfLevels(root->right);

		T sum = root->value + lV + rV;

		if (sum == value) return true;

		bool lB = FindSubtree(root->left, value);
		bool rB = FindSubtree(root->right, value);

		return lB | rB;
	}
};

bool isPowerOfTwo(int number)
{
	return (number & (number - 1)) == 0;
}

int FindNonDuplicate(int arr[], int size)
{
	int result = arr[0];

	for (int i = 1; i < size; i++)
	{
		result = result ^ arr[i];
	}

	return result;
}

void possibleSubsets(int A[], int N)
{
	for (int i = 0; i < (1 << N); ++i)
	{
		for (int j = 0; j < N; ++j)
			if (i & (1 << j))
				std::cout << A[j] << ' ';
		std::cout << std::endl;
	}
}

std::vector<int> GetSetBits(int number)
{
	std::vector<int> arr;

	int count = 0;
	int n = 0;

	for (int i = 1; i <= number; i++)
	{
		count = 0;
		n = i;

		while (n)
		{
			n &= (n - 1);
			count++;
		}
		arr.push_back(count);
	}

	return arr;
}

void Reverse(std::string& input)
{
	for (int i = 0; i < input.size() / 2; i++)
	{
		char temp = input[i];
		input[i] = input[(input.size() - 1) - i];
		input[(input.size() - 1) - i] = temp;
	}
}

int ReversDigits(int num)
{
	static int rev_num = 0;
	static int base_pos = 1;
	if (num > 0)
	{
		ReversDigits(num / 10);
		rev_num += (num % 10) * base_pos;
		base_pos *= 10;
	}
	return rev_num;
}

char FirstUnique(std::string input)
{
	bool unique = true;

	for (int i = 0; i < input.size(); i++)
	{
		unique = true;

		for (int j = 0; j < input.size(); j++)
		{
			if(j == i) continue;
			if (input[i] == input[j])
			{
				unique = false;
				break;
			}
		}

		if (unique)
			return input[i];
	}

	return 0;
}

bool ValidAnagram(std::string string, std::string check)
{
	int valOfString = 0;
	int valOfCheck = 0;

	for (char c : string)
	{
		valOfString += c;
	}

	for (char c : check)
	{
		valOfCheck += c;
	}

	return (valOfCheck == valOfString);
}

std::string CountAndSay(int number)
{
	if (number == 1) return "1";
	if (number == 2) return "11";

	std::string str = "11";
	for (int i = 3; i <= number; i++)
	{
		// In below for loop, previous character 
		// is processed in current iteration. That 
		// is why a dummy character is added to make 
		// sure that loop runs one extra iteration. 
		str += '$';
		int len = str.length();

		int cnt = 1; // Initialize count of matching chars 
		std::string  tmp = ""; // Initialize i'th term in series 

		// Process previous term to find the next term 
		for (int j = 1; j < len; j++)
		{
			// If current character does't match 
			if (str[j] != str[j - 1])
			{
				// Append count of str[j-1] to temp 
				tmp += cnt + '0';

				// Append str[j-1] 
				tmp += str[j - 1];

				// Reset count 
				cnt = 1;
			}

			//  If matches, then increment count of matching 
			// characters 
			else cnt++;
		}

		// Update str 
		str = tmp;
	}

	return str;
}

void DeleteElem(int* arr, int size, int index)
{
	for (int i = index; i > (size - 1); i++)
	{
		int temp = arr[i];
		arr[i] = arr[i + 1];
		arr[i + 1] = temp;
	}
}

int FilterIterator(int* arr, int size, bool predicate(int))
{
	int newSize = size;

	for (int i = 0; i < newSize;)
	{
		if (!predicate(arr[i]))
		{
			for (int j = i; j < (newSize - 1); j++)
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}

			newSize--;
		}
		else
			i++;
	}

	int* output = new int[newSize];
	memcpy(output, arr, newSize * sizeof(int));
	arr = output;
	delete[] output;

	return newSize;
}

bool Filter(int value)
{
	return (value % 2 == 0);
}

int convert(char c)
{
	if (c == 'I')
		return 1;
	if (c == 'V')
		return 5;
	if (c == 'X')
		return 10;
	if (c == 'L')
		return 50;
	if (c == 'C')
		return 100;
	if (c == 'D')
		return 500;
	if (c == 'M')
		return 1000;
}

int ConvertRoman(std::string input)
{
	int number = 0;

	for (int i = 0; i < input.size(); i++)
	{
		int first = convert(input[i]);

		if (i != input.size() - 1)
		{
			int second = convert(input[i + 1]);

			if (second > first)
			{
				number += (second - first);
				i++;
			}
			else
				number += first;
		}
		else
			number += first;
	}

	return number;
}

bool ValidateSquare(int arr[][3])
{
	int magic = 0;
	int value = 0;

	for (int i = 0; i < 3; i++)
		magic += arr[i][i];

	for (int i = 0; i < 3; i++)
		value += arr[i][3 - 1 - i];

	if (magic != value) return false;

	for (int i = 0; i < 3; i++)
	{
		value = 0;
		for (int j = 0; j < 3; j++)
		{
			value += arr[j][i];
		}

		if (value != magic) return false;
	}

	for (int i = 0; i < 3; i++)
	{
		value = 0;
		for (int j = 0; j < 3; j++)
		{
			value += arr[i][j];
		}

		if (value != magic) return false;
	}

	return true;
}

struct Conversion
{
	Conversion(std::string n1, std::string n2, float r)
	{
		name1 = n1;
		name2 = n2;
		ratio = r;
	}

	std::string name1;
	std::string name2;
	float ratio;
};

void ConvertUnits(float input)
{
	std::vector<Conversion> conversions;
	conversions.push_back(Conversion("kg", "lbs", 2.2f));
	conversions.push_back(Conversion("miles", "km", 1.6f));

	for (int i = 0; i < conversions.size(); i++)
	{
		std::cout << input << " " << conversions[i].name1 << " == ";
		std::cout << input * conversions[i].ratio << " " << conversions[i].name2 << std::endl;
	}
}

int FindMaxFont(std::string input)
{
	int max = 100;
	int min = 1;

	int rh = 50;
	int rw = 70;

	int h = 30;
	int w = input.size() * 3 * min;

	int font = min;

	for (int i = min; i <= max; i++)
	{
		w = input.size() * 3 * i;

		if (w > rw) return w;
	}
}

int main()
{
	ConvertUnits(5);
}
