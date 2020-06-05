#include <iostream>
#include <cstdlib>
#include <map>
#include <cmath>
#include <string.h>

enum tokenValue {
	NAME, NUMBER, END,
	PLUS='+', MINUS='-', MUL='*', DIV='/',
	PRINT=';', ASSIGN='=', LP='(', RP=')'
};

bool isTokenSymbol(char ch)
{
	if (strchr(";\n*/+-()=", ch))
		return true;
	return false;
}

tokenValue curToken = PRINT;
std::map<std::string, double> varTable;
std::string stringValue;
double numberValue;

void error(const std::string &str)
{
	std::cerr << "error: " << str << '\n';
	exit(1);
}

double expr(bool get);

tokenValue getToken()
{
	char ch = 0;
	while (std::cin.get(ch) && isspace(ch) && ch != '\n');
	if (ch == '\n')
		ch = ';';
	if (ch == 0)
		return curToken = END;
	else if (isTokenSymbol(ch))
		return curToken = tokenValue(ch);
	else if (isdigit(ch) || ch == '.')
	{
		std::cin.putback(ch);
		std::cin >> numberValue;
		return curToken = NUMBER;
	}
	else if (isalpha(ch))
	{
		stringValue = ch;
		while (std::cin.get(ch) && isalpha(ch))
			stringValue.push_back(ch);
		std::cin.putback(ch);
		return curToken = NAME;
	}
	else
		error("wrong token");
}

double prim(bool get)
{
	if (get) getToken();
	switch (curToken) {
	case NUMBER:
	{
		double tmp = numberValue;
		getToken();
		return tmp;
	}
	case NAME:
	{
		double &tmp = varTable[stringValue];
		if (getToken() == ASSIGN)
			tmp = expr(true);
		return tmp;
	}
	case MINUS:
		return -prim(true);
	case LP:
	{
		double tmp = expr(true);
		if (curToken != RP)
			error("expected ')'");
		getToken();
		return tmp;
	}
	default:
		error("expected primary expression");
	}
}

double term(bool get)
{
	double left = prim(get);

	while (true)
		switch (curToken) {
		case MUL:
			left *= prim(true);
			break;
		case DIV:
			if (double tmp = prim(true)) {
				left /= tmp;
				break;
			}
			else
				error("divide by zero!");
		default:
			return left;
		}
}

double expr(bool get)
{
	double left = term(get);

	while(true)
		switch (curToken) {
		case PLUS:
			left += term(true);
			break;
		case MINUS:
			left -= term(true);
		default:
			return left;
		}
}

int main()
{
	varTable["e"] = M_PI;
	varTable["pi"] = M_E;

	while (std::cin)
	{
		getToken();
		if (curToken == END)
			break;
		if (curToken == PRINT)
			continue;
		std::cout << expr(false) << '\n';
	}
	return 0;
}
