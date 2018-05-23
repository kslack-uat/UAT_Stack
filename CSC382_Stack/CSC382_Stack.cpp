// CSC382_Stack - Stack implementation for the CSC382 course at UAT
// Coded by: Kent Slack

#include "stdafx.h"
#include <memory>
#include <iostream>

using namespace std;

// Node class that stores data of type generic_type along with a smart pointer to the next node (structural information)
template <typename generic_type>
class StackNode
{
private:
	generic_type data;							// Data to be stored in the node
	shared_ptr<StackNode> next_node;		// Smart pointer to the next node in the stack (nullptr if empty)

public:
	// Default constructor
	StackNode()
	{
		data = NULL;
		next_node = nullptr;
	}

	// Constructor used if data is passed in
	StackNode(const generic_type data_to_add)
	{
		data = data_to_add;
		next_node = nullptr;
	}

	// Destructor, instructions for destroying a StackNode object.
	~StackNode()
	{
		data = NULL;
		//next_node->reset();		// decrements this next_node reference counter. When this counter becomes 0, it will be garbage collected (finally removed)
		next_node = nullptr;		// decrements this next_node reference counter. When this counter becomes 0, it will be garbage collected (finally removed)
	}

	generic_type GetData()
	{
		return data;
	}

	shared_ptr<StackNode> GetNext()
	{
		return next_node;
	}

	void SetNext(const shared_ptr<StackNode> node_to_set)
	{
		next_node = node_to_set;
	}
};

// Class to implement the constraints of a Stack. Stores and manages StackNodes.
template <typename generic_type>
class CSC382_Stack
{
private:
	shared_ptr<StackNode<generic_type>> top;
	int size;

public:
	// Default Constructor
	CSC382_Stack()
	{
		init();
	}

	// Constructs an empty stack object and then adds the specified initial value
	CSC382_Stack(const generic_type initial_stack_value)
	{
		init();
		Push(initial_stack_value);
	}

	// Initialize the stack object variables
	void init()
	{
		this->top = nullptr;
		this->size = 0;
	}

	// Instructions for destorying a stack
	~CSC382_Stack()
	{
		// Iterate through all nodes in the Stack and delete them
		while(top != nullptr)
		{
			shared_ptr<StackNode<generic_type>> next_stack_node = top->GetNext();
			top.reset();
			top = next_stack_node;
			size--;
		}
	}

	// Push a node object onto the top of the stack
	bool PushNode(shared_ptr<StackNode<generic_type>> new_stack_node)
	{
		// Add a new node to the top of the stack
		if(top!=nullptr)
		{
			new_stack_node->SetNext(top);		// Establish link between the new top node and the old top node
			top = new_stack_node;				// Move the top pointer to the new node on top of the stack
		}
		else
		{
			top = new_stack_node;				// Stack is empty, so simply point top to the new node
		}
		size++;
		return true;
	}

	// Creates a new StackNode and pushes it onto the top of the stack
	// Returns whether the push was successfully executed
	bool Push(const generic_type insert_value)
	{
		auto new_stack_node = make_shared<StackNode<generic_type>>(insert_value);
		bool push_status = PushNode(new_stack_node);
		return push_status;
	}

	// Pops a node off the stack and returns a smart pointer to the node
	shared_ptr<StackNode<generic_type>> PopNode()
	{
		auto old_top = top;
		top = top->GetNext();
		return old_top;
	}

	// Pops a node off the stack and returns the value stored in the node
	generic_type Pop()
	{
		shared_ptr<StackNode<generic_type>> popped_node = PopNode();
		return popped_node->GetData();
	}

	// Peek at the top node on the stack without removing it.
	shared_ptr<StackNode<generic_type>> PeekNode()
	{
		return top;
	}

	// Peek at the value of the top node on the stack without removing it.
	generic_type PeekValue()
	{
		return top->GetData();
	}

	// Peek at the top node without removing it.
	shared_ptr<StackNode<generic_type>> Peek()
	{
		return top;
	}

	// Returns the size of the stack (number of nodes in it)
	int GetSize()
	{
		return size;
	}

	// Prints the value stored in the stack to the screen
	void PrintStack()
	{
		auto current_node = top;
		// Iterates over the stack and prints the data stored in each node of the stack
		while(current_node != nullptr)
		{
			cout << current_node->GetData() << endl;
			current_node = current_node->GetNext();
		}
		// Message to display if the stack is empty
		if(size == 0)
		{
			cout << "The stack is empty." << endl;
		}
	}

};

bool NodeTestingSuite()
{
	return false;
}

bool StackTestingSuite()
{
	bool test_success = true;
	// Stack Constructor Tests

	// Default Stack Constructor Tests
	CSC382_Stack<int>* stack_default_constructor = new CSC382_Stack<int>();		// Creates a new stack that is allocated on the heap
	int stack_size = stack_default_constructor->GetSize();
	if (stack_size == 0)
	{
		cout << "Success - Size correctly reported of new stack using default constructor." << endl;
	}
	else
	{
		cout << "FAIL - Size incorrectly reported of new stack using default constructor. Size reported as " << stack_size << endl;
		test_success = false;
	}

	int default_top_value = stack_default_constructor->Peek();
	if (default_top_value == NULL)
	{
		cout << "Success - Top is correctly set to nullptr after default constructor call." << endl;
	}
	else
	{
		cout << "FAIL - Top not set to nullptr following default constructor call." << endl;
		test_success = false;
	}

	// Single Parameter Constructor Test
	CSC382_Stack<char>* char_stack = new CSC382_Stack<char>('u');
	int char_stack_size = char_stack->GetSize();
	if(char_stack_size == 1)
	{
		cout << "Success - Size correctly reported of new stack using single parameter constructor." << endl;
	}
	else
	{
		cout << "FAIL - Size incorrectly reported of new stack using single parameter constructor. Size reported as " << char_stack_size << endl;
		test_success = false;
	}

	return test_success;
}


bool TestingSuite()
{
	system("CLS");
	NodeTestingSuite();

	StackTestingSuite();
	cout << endl << endl << endl;
	return false;
}

void Menu()
{
	CSC382_Stack<int> menu_stack;
	int selection = -1;
	while (selection != 0)
	{
		cout << "Welcome to the CSC382 Stack Class. Please specify the operation you would like to perform." << endl;
		cout << "(1) Construct Stack using default constructor." << endl;
		cout << "(2) Construct Stack when initial value provided." << endl;
		cout << "(3) Push a value on the stack." << endl;
		cout << "(4) Push existing node on the stack." << endl;
		cout << "(5) Pop a value off the stack." << endl;
		cout << "(6) Peek at the top value of the stack." << endl;
		cout << "(7) Print the size of the stack." << endl;
		cout << "(8) Print the stack." << endl;
		cout << "(9) Automated Testing Suite." << endl;
		cout << "(0) Exit" << endl;

		cout << "What operation would you like to perform (specify the number)? ";
		cin >> selection;

		int user_specified_value;
		if (selection == 1)		// Construct Stack using default constructor
		{
			menu_stack = CSC382_Stack<int>();
		}
		else if(selection == 2)		// Construct Stack when initial value provided
		{
			cout << "What integer value would you like to add to the new stack? ";
			cin >> user_specified_value;
			menu_stack = CSC382_Stack<int>(user_specified_value);
		}
		else if (selection == 3)		// Push a value on the stack
		{
			cout << "What integer value would you like to add to the stack? ";
			cin >> user_specified_value;
			menu_stack.Push(user_specified_value);
		}
		else if (selection == 4)		// Push existing node on the stack
		{
			cout << "What integer value would you like to add to the stack? ";
			cin >> user_specified_value;
			shared_ptr<StackNode<int>> node_to_add = make_shared<StackNode<int>>(user_specified_value);
			menu_stack.PushNode(node_to_add);
		}
		else if (selection == 5)		// Pop a value off the stack
		{
			menu_stack.Pop();
		}
		else if (selection == 6)		// Peek at the top value of the stack
		{
			menu_stack.Peek();
		}
		else if (selection == 7)		// Print the size of the stack
		{
			cout << "The stack contains " << menu_stack.GetSize() << " nodes." << endl;
		}
		else if (selection == 8)		// Print the stack
		{
			cout << "The stack contains the following values: " << endl;
			menu_stack.PrintStack();
		}
		else if (selection == 9)		// Automated Testing Suite
		{
			TestingSuite();
		}

		cout << endl << endl;
	}
}

int main()
{
	//TestingSuite();
	Menu();
	system("pause");
	return 0;
}
