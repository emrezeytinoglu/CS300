//Do not forget to rename this file according to the file naming rules
#ifndef _emrezeytinoglu_Zeytinoglu_Emre_hw4_DYNSTACK_H
#define _emrezeytinoglu_Zeytinoglu_Emre_hw4_DYNSTACK_H
struct StackNode
{
	char symbol;
	int line_number;
	StackNode *next;
	StackNode() : next(nullptr){}
};

class DynStack
{
private:
	StackNode *top;
	void clear();
	StackNode* clone() const;

public:
	DynStack(void);
	DynStack(const DynStack&);
	const DynStack& operator=(const DynStack&);
	void push(char, int);
	void pop(char &, int &);
	bool isEmpty(void);
	~DynStack();
};
#endif