
#include "pch.h"
#include <iostream>
#include <unordered_set>
#include <vector>

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

int main()
{
	Nimm nimm(4);

	nimm.GetRows()[0] = 4;
	nimm.GetRows()[1] = 5;
	nimm.GetRows()[2] = 2;
	nimm.GetRows()[3] = 3;

	nimm.Game();
}
