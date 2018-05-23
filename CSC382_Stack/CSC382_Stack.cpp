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
	void Push(const generic_type insert_value)
	{
		auto new_stack_node = make_shared<StackNode<generic_type>>(insert_value);
		PushNode(new_stack_node);
		//bool push_status = PushNode(new_stack_node);
		//return push_status;
	}

	// Pops a node off the stack and returns a smart pointer to the node
	shared_ptr<StackNode<generic_type>> Pop()
	{
		auto old_top = top;
		top = top->GetNext();
		return old_top;
	}

	// Pops a node off the stack and returns the value stored in the node
	generic_type PopValue()
	{
		auto popped_node = Pop();
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
		if (top != nullptr)
		{
			return top->GetData();
		}
		else
		{
			cout << "Stack is empty." << endl;
			return NULL;
		}
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
	//**************************************
	//****** Stack Constructor Tests *******
	//****** Default Stack Constructor Tests
	auto stack_default_constructor = make_shared<CSC382_Stack<int>>();		// Creates a new stack
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

	int default_top_value = stack_default_constructor->PeekValue();
	if (default_top_value == NULL)
	{
		cout << "Success - Top value is correctly set to NULL after default constructor call." << endl;
	}
	else
	{
		cout << "FAIL - Top value not set to NULL following default constructor call." << endl;
		test_success = false;
	}

	auto top_node_ptr = stack_default_constructor->Peek();
	if(top_node_ptr == nullptr)
	{
		cout << "Success - The top value of the stack is nullptr as expected." << endl;
	}
	else
	{
		cout << "FAIL - The top value of an empty stack is not nullptr" << endl;
		test_success = false;
	}


	//****** Single Parameter Constructor Test
	auto char_stack = make_shared<CSC382_Stack<char>>('u');
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

	char one_param_top_value = char_stack->PeekValue();
	if (one_param_top_value == 'u')
	{
		cout << "Success - Top is correctly set to u after one parameter constructor call." << endl;
	}
	else
	{
		cout << "FAIL - Top not set to u following one parameter constructor call." << endl;
		test_success = false;
	}

	//************************************
	//****** Function Tests ******
	// Push Tests
	stack_default_constructor->Push(5);
	if(stack_default_constructor->GetSize() == 1)
	{
		cout << "Success - Stack size is now 1 as expected." << endl;
	}
	else
	{
		cout << "FAIL - Stack size is not 1 as expected." << endl;
		test_success = false;
	}

	int top_value = stack_default_constructor->PeekValue();
	if(top_value == 5)
	{
		cout << "Success - Top value of stack is 5 as expected." << endl;
	}
	else
	{
		cout << "FAIL - Top value of stack is " << top_value << ". Expected a value of 5." << endl;
		test_success = false;
	}


	// PushNode Tests
	auto new_stack_node = make_shared<StackNode<int>>(4);
	stack_default_constructor->PushNode(new_stack_node);
	if(stack_default_constructor->GetSize() == 2)
	{
		cout << "Success - Stack is size 2 after PushNode function called." << endl;
	}
	else
	{
		cout << "FAIL - Stack is not size 2 after PushNode function call." << endl;
		test_success = false;
	}

	top_value = stack_default_constructor->PeekValue();
	if (top_value == 4)
	{
		cout << "Success - Top value of stack is 4 as expected after PushNode function call." << endl;
	}
	else
	{
		cout << "FAIL - Top value of stack is " << top_value << ". Expected a value of 4 after PushNode function call." << endl;
		test_success = false;
	}


	// Print Stack Tests
	cout << "Printing the current state of the stack to the screen." << endl;
	cout << "Expected output is:\n4\n5" << endl;
	cout << "Actual output is:" << endl;
	stack_default_constructor->PrintStack();

	// Pop Test


	

	// Load Testing Stack with many Push function calls
	for(int counter = 0; counter < 1000; counter++)
	{
		stack_default_constructor->Push(counter);
	}
	if(stack_default_constructor->GetSize() == 1002)
	{
		cout << "Success - 1002 nodes now found in the stack after load testing." << endl;
	}
	else
	{
		cout << "FAIL - Incorrect number of nodes found in the stack after load testing." << endl;
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
