#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "ExpressionConverter.h"


//////////////////////////////////////////////////////////////////////////////////////////////
// DO NOT EDIT THIS FILE (except for your own testing)
// CODE WILL BE GRADED USING A MAIN FUNCTION SIMILAR TO THIS
//////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

template <typename T>
bool testAnswer(const string &nameOfTest, const T &received, const T &expected);
bool testString(const string &nameOfTest, const string &received, const string &expected); 
bool testTree(const string &nameOfTest, const ArithNode *ptr, const string &expected);
void printTree(ArithNode *ptr);
bool passedAllTests = true;

int main() {

	// Convert and evaluate infix expression
	{
		cout<< "start";
		string infix = "10 * ( 20 + 30 )";
		cout << "The infix expression is " << infix << endl;
		int answer = EvaluateInfix(infix);
		cout << "The answer is " << answer << endl;
		testAnswer("EvaluateInfix", answer, 500);
		string rpn = Infix2RPN(infix);
		cout << "The equivalent RPN expression is " << rpn << endl;
		testString("Infix2RPN", rpn, string("10 20 30 + *"));
		cout << "The equivalent expression tree is:" << endl;
		ArithNode *tree = Infix2ExpressionTree(infix);
		printTree(tree);
		testTree("Infix2ExpressionTree", Infix2ExpressionTree(infix), string("*(10)(+(20)(30))"));
		cout << endl;
	}
	// Convert and evaluate infix expression
	{
		string infix = "200 / ( 120 + 10 * ( 20 - 30 ) )";
		cout << "The infix expression is " << infix << endl;
		int answer = EvaluateInfix(infix);
		cout << "The answer is " << answer << endl;
		testAnswer("EvaluateInfix", answer, 10);
		string rpn = Infix2RPN(infix);
		cout << "The equivalent RPN expression is " << rpn << endl;
		testString("Infix2RPN", rpn, string("200 120 10 20 30 - * + /"));
		cout << "The equivalent expression tree is:" << endl;
		ArithNode *tree = Infix2ExpressionTree(infix);
		printTree(tree);
		testTree("Infix2ExpressionTree", Infix2ExpressionTree(infix), string("/(200)(+(120)(*(10)(-(20)(30))))"));
		cout << endl;
	}
	// Convert and evaluate RPN expression
	{
		string rpn = "25 10 20 30 + * +";
		cout << "The RPN expression is " << rpn << endl;
		int answer = EvaluateRPN(rpn);
		cout << "The answer is " << answer << endl;
		testAnswer("EvaluateRPN", answer, 525);
		string infix = RPN2Infix(rpn);
		cout << "The equivalent infix expression is " << infix << endl;
		testString("RPN2Infix", infix, string("(25+(10*(20+30)))"));
		cout << "The equivalent expression tree is:" << endl;
		ArithNode *tree = RPN2ExpressionTree(rpn);
		printTree(tree);
		testTree("RPN2ExpressionTree", tree, string("+(25)(*(10)(+(20)(30)))"));
		cout << endl;
	}
	// Convert and evaluate RPN expression
	{
		string rpn = "200 120 10 20 30 - * + /";
		cout << "The RPN expression is " << rpn << endl;
		int answer = EvaluateRPN(rpn);
		cout << "The answer is " << answer << endl;
		testAnswer("EvaluateRPN", answer, 10);
		string infix = RPN2Infix(rpn);
		cout << "The equivalent infix expression is " << infix << endl;
		testString("RPN2Infix", infix, string("(200/(120+(10*(20-30))))"));
		cout << "The equivalent expression tree is:" << endl;
		ArithNode *tree = RPN2ExpressionTree(rpn);
		printTree(tree);
		testTree("RPN2ExpressionTree", tree, string("/(200)(+(120)(*(10)(-(20)(30))))"));
		cout << endl;
	}	

	if (passedAllTests)
		cout << "Congratulations! Passed all tests" << endl;
}

template <typename T>
bool testAnswer(const string &nameOfTest, const T &received, const T &expected) {
	if (received == expected) {
		cout << "PASSED " << nameOfTest << ": expected and received " << received << endl;
		return true;
	}
	passedAllTests = false;
	cout << "FAILED " << nameOfTest << ": expected " << expected << " but received " << received << endl;
	return false;
}

string removeWhitespace(const string &s) {
	string t;
	for (int i = 0; i < s.length(); i++)
		if (!isspace(s[i]))
			t = t + s[i];
	return t;
}

bool testString(const string &nameOfTest, const string &received, const string &expected) {
	if (removeWhitespace(received) == removeWhitespace(expected)) {
		cout << "PASSED " << nameOfTest << ": expected and received " << received << endl;
		return true;
	}
	cout << "FAILED " << nameOfTest << ": expected " << expected << " but received " << received << endl;
	passedAllTests = false;
	return false;
}

string tree2string(const ArithNode *ptr) {
	if (ptr == nullptr) return "";
	string s;
	if (ptr->isOperator)
		s = string(1, ptr->binaryOperator) + "(" + tree2string(ptr->left) + ")" + "(" + tree2string(ptr->right) + ")";
	else
		s = to_string(ptr->operand);
	return s;
}

bool testTree(const string &nameOfTest, const ArithNode *ptr, const string &expected) {
	string received = tree2string(ptr);
	if (received == expected) {
		cout << "PASSED " << nameOfTest << ": expected and received " << expected << endl;
		return true;
	}
	cout << "FAILED " << nameOfTest << ": expected " << expected << " but received " << received << endl;
	passedAllTests = false;
	return false;
}

void printTree(ArithNode *ptr, string prefix, bool isTail) {
	if (!ptr->isOperator) {
		cout << prefix << (isTail ? "> " : "> ") << ptr->operand << endl;
		return;
	}
	cout << prefix << (isTail ? "> " : "> ") << ptr->binaryOperator << endl;
	printTree(ptr->left, prefix + (isTail ? "   " : "=> "), false);
	printTree(ptr->right, prefix + (isTail ? "   " : "=> "), true);
}

void printTree(ArithNode *ptr) {
	printTree(ptr, "", true);
}
