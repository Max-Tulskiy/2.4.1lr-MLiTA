#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<string>

using namespace std;

int priority(char c) {
	if (c == '*' || c == '/') return 2;
	if (c == '+' || c == '-') return 1;
	else return 0;
}

struct univers {
	char oper;
	double value;
};

double sum(char operat, double a, double b) {
	switch (operat) {
	case '+':
		return a+b;
		break;
	case '-':
		return a-b;
		break;
	case '*':
		return a*b ;
		break;
	case '/':
		return a/b;
		break;
	}
}

double count(queue<univers>& que) {
	stack<double>st;
	
	while (!que.empty())
	{
		if (que.front().oper == '0') {
			st.push(que.front().value);
			que.pop();
			continue;
		}
		else  
		{
			double a, b;
			b = st.top();
			st.pop();
			a = st.top();
			st.pop();
			st.push(sum(que.front().oper, a, b));
			que.pop();
		}
	}
	return st.top();
}

int main() {
	setlocale(LC_ALL, "Russian");
	queue <univers> q;
	stack<char>steck;
	double num = 0;
	char ch;
	univers elem;
	cout << "Введите выражение:\n";
	while (true) {
		ch = cin.peek();
		if (ch == ' ') {
			cin.ignore();
			continue;
		}
		if (ch == '\n') {
			break;
		}
	
		if (ch >= '0' && ch <= '9') {
			cin >> num;
			elem.oper = '0';
			elem.value = num;
			q.push(elem);
			continue;
		}
		if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		{
			if (steck.empty()) {
				steck.push(ch);
				cin.ignore();
				continue;
			}
			if (priority(ch) > priority(steck.top())) {
				steck.push(ch);
				cin.ignore();
				continue;
			}
			if (priority(ch) == priority(steck.top())) {
				elem.oper = steck.top();
				elem.value = 0;
				q.push(elem);
				steck.pop();
				steck.push(ch);
				cin.ignore();
				continue;
			}
			while (priority(ch) < priority(steck.top())) {
				elem.oper = steck.top();
				elem.value = 0;
				q.push(elem);
				steck.pop();
				steck.push(ch);
				cin.ignore();
				continue;
			}
		}
	}
	
	while (!steck.empty()) {
		elem.value = 0;
		elem.oper = steck.top();
		q.push(elem);
		steck.pop();
	}
	queue<univers> q1;
	q1 = q;
	cout << "\nРезультат в постфиксной форме: ";
	while (!q1.empty()) {
		if (q1.front().oper == '0') cout << q1.front().value << " ";
		else cout << q1.front().oper << " ";
		q1.pop();
	}

	  cout<<"\n\nРезультат выражения: "<< count(q) <<"\n \n \n";
	  return 0;

}

	

