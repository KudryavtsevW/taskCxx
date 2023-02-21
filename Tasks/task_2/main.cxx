#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <stack>
using namespace std;

int globalError = __INT32_MAX__;
class CountryNode
{
public:
	string _name;
	int _value;
	int _deep;
	vector<CountryNode*> _children;
	CountryNode()
	{
		_name = "root";
		_deep = 0;
	}
	void setNode(string name)
	{
		auto m = cmatch{};
		if (regex_match(name.c_str(), m, regex{ R"((\w+):(\w+))" }))
		{
			_name = m[1].str();
			_value = atoi(m[2].str().c_str());
		}
		//_name = name;
	}
	CountryNode* addChild(string name)
	{
		CountryNode* n = new CountryNode(); //Создадим новый узел
		n->setNode(name); //добавим в этот узел значение
		n->_deep = _deep + 1;
		_children.push_back(n); //Добавим в вектор детей этот узел. Вектор детей это вектор того кто вызовет этот метод
		return(n); //Вернем этот узел
	}
};
void printTree(const CountryNode& tree, int ident)
{
	CountryNode* child;
	cout << string(ident++, '\t') << tree._name <<" "<<tree._value<< endl;
	for (int i = 0; i < tree._children.size(); i++)
	{
		child = tree._children[i];
		printTree(*child, ident);
	}
}
void checkError(const CountryNode& tree)
{
	CountryNode* child;
	int value = tree._value;
	int sum = 0;
	for (int i = 0; i < tree._children.size(); i++)
	{
		child = tree._children[i];
		sum += child->_value;

	}
	if (sum != value && tree._children.size() != 0 && tree._name!="root")
		globalError = -1;
}
void passTree(const CountryNode& tree)
{
	CountryNode* child;
	checkError(tree);
	for (int i = 0; i < tree._children.size(); i++)
	{
		child = tree._children[i];
		passTree(*child);
	}
}

void printMyTree(const CountryNode& tree)
{
	CountryNode* child;
	printf("%s deep = %d\n", tree._name.c_str(), tree._deep);
	for (int i = 0; i < tree._children.size(); i++)
	{
		child = tree._children[i];
		printMyTree(*child);
	}
}
FILE* pFile;


CountryNode rootNode;
CountryNode* parentNode = &rootNode;
CountryNode* tmpNode = &rootNode;
stack<CountryNode*> st;
int Error = 0;
enum states { CHAR,READ, OPEN_SKOBKA, CLOSE_SKOBKA, END, WRITE};
enum states State(enum states c, char ch, std::string* str)
{
	switch (c)
	{
	case CHAR:
	{
		if (isalpha(ch) || ch == ':' || isdigit(ch))
		{
			str->push_back(ch);
			return CHAR;
		}
		if (ch == '|')
		{
			if (str->length() != 0)
				return WRITE;
			else
				return CHAR;
		}
		if (ch == '{')
			return OPEN_SKOBKA;
		if (ch == '}')
			return CLOSE_SKOBKA;
		if (ch == '\n')
			return END;
	}
	case WRITE:
		tmpNode = parentNode->addChild(str->c_str());
		//printf("OPEN_SKOBKA { : TMP_NODE -> _name = %s\t_deep = %d\n", tmpNode->_name.c_str(), tmpNode->_deep);
		str->clear();
		return CHAR;
	case OPEN_SKOBKA:
	{


		st.push(parentNode);
		//printf("OPEN_SKOBKA { : PARENT_NODE PUSHED IN STACK -> _name = %s\t_deep = %d\n", parentNode->_name.c_str(), parentNode->_deep);
		parentNode = tmpNode;
		//printf("OPEN_SKOBKA { : PARENT_NODE = TMP_NODE -> _name = %s\t_deep = %d\n", parentNode->_name.c_str(), parentNode->_deep);

		return CHAR;
	}
	case CLOSE_SKOBKA:
	{
		if (st.empty())
		{
			Error = -11;
			//printf("Error skobka }\n");
			return END;
		}
		else {
			parentNode = st.top();
			//printf("CLOSE_SKOBKA } : PARENT_NODE GET OUT STACK AND DELETE IN STACK -> _name = %s\t_deep = %d\n", parentNode->_name.c_str(), parentNode->_deep);
			st.pop();
			return CHAR;
		}
	}
	case END:
		return END;
	default:
		break;
	}
}

int main()
{

	pFile = fopen("protocol.txt", "r");
	if (!pFile)
	{
		printf("no such file <protocol.txt>\n");
		return -11;
	}
	char ch = 0;
	bool mode = false;
	string str;
	
	enum states s = CHAR;
	while (s != END)
	{
		if (!(s == OPEN_SKOBKA || s == CLOSE_SKOBKA || s == WRITE))
		{
			short q = fscanf(pFile, "%c", &ch);
		}
		s = State(s, ch, &str);
	}
	switch (Error)
	{
	case -11:
		printf("Error Skobka } \n");
		break;
	default:
		printTree(rootNode, 0);
		passTree(rootNode);
		if (globalError == -1)
		{
			printf("error!!!\n");
		}
		printMyTree(rootNode);
		break;
	}
	
	fclose(pFile);
	return 0;
}
