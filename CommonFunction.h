#pragma once
#include "LoopHero.h"

inline void SetClientRect(HWND hWnd, int width, int height)
{
	RECT crt;
	DWORD style, exStyle;

	SetRect(&crt, 0, 0, width, height);
	style = GetWindowLong(hWnd, GWL_STYLE);
	exStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
	AdjustWindowRectEx(&crt, style, GetMenu(hWnd) != NULL, exStyle);
	if (style & WS_VSCROLL) crt.right += GetSystemMetrics(SM_CXVSCROLL);
	if (style & WS_HSCROLL) crt.bottom += GetSystemMetrics(SM_CYHSCROLL);
	SetWindowPos(hWnd, NULL, 0, 0, crt.right - crt.left, crt.bottom - crt.top,
		SWP_NOMOVE | SWP_NOZORDER);
}

//연산자 우선순위 지정
inline int GetOpPrec(char oper)
{
	switch (oper)
	{
	case '*':
	case '/':
		return 5;
	case '+':
	case '-':
		return 3;
	case '(':
		return 1;
	}
	return -1;
}
//연산자 우선순위 판별
inline int whoPrecOp(char op1, char op2)
{
	int op1Prec = GetOpPrec(op1);
	int op2Prec = GetOpPrec(op2);

	if (op1Prec > op2Prec)
		return 1;
	else if (op1Prec < op2Prec)
		return -1;
	else
		return 0;
}
//후위 계산식으로 변환
inline vector<string> ConvToRPN(string fomula)
{
	stack<char> stack;
	vector<string> convExp;
	string num;
	char tok, popOp;

	for (int i = 0; i < fomula.size(); ++i)
	{
		tok = fomula[i];

		if (isdigit(tok) || tok == '.')
		{
			num.push_back(tok);
		}
		else
		{
			if (!num.empty())
				convExp.push_back(num);
			num.clear();

			switch (tok)
			{
			case '(':
				stack.push(tok);
				break;
			case ')':
				while (1)
				{
					popOp = stack.top();
					stack.pop();
					if (popOp == '(')
						break;
					convExp.push_back(string{ popOp });

				}
				break;
			case '+': case '-':
			case '*': case '/':
				while (!stack.empty() && whoPrecOp(stack.top(), tok) >= 0)
				{
					convExp.push_back(string{ stack.top() });
					stack.pop();
				}
				stack.push(tok);
				break;
			}
		}
	}
	convExp.push_back(num);

	while (!stack.empty())
	{
		convExp.push_back(string{ stack.top() });
		stack.pop();
	}

	return convExp;

}
//스택 계산
inline float StackCalculater(vector<string> fomula)
{
	stack<float> stack;

	string fomulaNum;
	string s;
	float num1, num2;

	for (int i = 0; i < fomula.size(); ++i)
	{
		if (fomula[i].size() > 1)
		{
			//숫자임 , 
			stack.push(stof(fomula[i]));
		}
		else
		{
			switch ((fomula[i])[0])
			{
			case '+':
				num2 = stack.top();
				stack.pop();
				num1 = stack.top();
				stack.pop();

				stack.push(num1 + num2);
				break;
			case '-':
				num2 = stack.top();
				stack.pop();
				num1 = stack.top();
				stack.pop();

				stack.push(num1 - num2);
				break;
			case '*':
				num2 = stack.top();
				stack.pop();
				num1 = stack.top();
				stack.pop();

				stack.push(num1 * num2);
				break;
			case '/':
				num2 = stack.top();
				stack.pop();
				num1 = stack.top();
				stack.pop();

				stack.push(num1 / num2);
				break;
			default:
				//숫자임
				stack.push(stof(fomula[i]));

				break;
			}
		}

	}

	if (stack.empty())
		return 0.0f;

	return stack.top();
}
//스트링 파싱
inline vector<string> StringSplit(string str, char token)
{
	vector<string> vString;
	int offset = 0, preOffset = 0;
					//token 찾고자하는 문자 , preOffset은 탐색 시작 위치, -1로 한 이유는? string::npos가 아니라
	while ((offset = str.find(token, preOffset)) != -1)
	{
		vString.push_back(str.substr(preOffset, offset - preOffset));
		preOffset = offset + 1;
	}
	if (!str.empty()) vString.push_back(str.substr(preOffset, str.size() - preOffset));
	return vString;
}
