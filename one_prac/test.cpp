#include<stdio.h>
#include<iostream>
#include<string.h>

//��Ŀһ������Ϊ����CMyString����������Ϊ��������Ӹ�ֵ����������

//ע���ĵ㣺1.����ֵΪ�����͵�����(֧������)
//          2.���˵Ĳ���Ϊ��������(���⿽������Ŀ���)
//          3.�ͷ������ڴ�
//          4.�ж��Ƿ���ͬһ��ʵ��
//ȱ�㣺���ڿ������ڴ�ʱ�������ʱ�ڴ�ռ����������������ʧ�ܣ�
//      ���Ѿ��ͷ���ԭ���ڴ棬��������
class CMyString
{
public:
	CMyString(char* pData = NULL);
	CMyString(const CMyString& str);
	~CMyString();
	CMyString& operator=(const CMyString& str)
	{
		if (this != &str)
		{
			delete []m_pData;
			m_pData = new char[strlen(str.m_pData)+1];
			strcpy(m_pData, str.m_pData);
		}
		return *this;
	}
private:
	char* m_pData;
};

//�Ż��汾
//������ʱ������ԭ���Ľ������������ڴ治��ʱ��ԭ����ʵ����û�иı�
class CMyString
{
public:
	CMyString(char* pData = NULL);
	CMyString(const CMyString& str);
	~CMyString();
	CMyString& operator=(const CMyString& str)
	{
		if (this != &str)
		{
			CMyString tmp_str(str);
			char* tmp = tmp_str.m_pData;
			tmp_str.m_pData = m_pData;
			m_pData = tmp;
		}
		return *this;
	}
private:
	char* m_pData;
};


//��Ŀ�������һ���࣬����ֻ�����ɸ����һ��ʵ��

//1.ȱ�㣺ֻ�����ڵ��̣߳����ж���߳�ͬʱ���뵽GetInstanceʱ������ʵ��
//û�д������������̷ֱ߳𴴽�һ��ʵ����Υ������ģʽԭ��
class Singletion
{
private:
	Singletion()
	{}
	static Singletion* instance;
public:
	static Singletion* GetInstance()
	{
		if (instance == NULL)
		{
			instance = new Singletion();
		}
		return instance;
	}
};
Singletion* Singletion::instance = NULL;
//2.ֻ�е�ʵ����û�д�����ʱ��ӻ���������Сϵͳ���������ҿ���ʵ�ֶ��߳�
class Singletion
{
private:
	Singletion()
	{}
	static Singletion* instance;
public:
	static Singletion* GetInstance()
	{
		if (instance == NULL)
		{
			Lock();
			if (instance == NULL)
			{
				instance = new Singletion();
			}
			UnLock();
		}
		return instance;
	}
};
Singletion* Singletion::instance = NULL;
//3.���þ�̬���캯��,�ڽ���������֮ǰ������ɳ�ʼ��������ֻ���ʼ��һ��
class Singletion
{
private:
	Singletion()
	{}
	static Singletion* instance;
public:
	static Singletion* GetInstance()
	{
		return instance;
	}
};
Singletion* Singletion::instance = new Singletion();


//��Ŀ������һ����ά�����У�ÿһ�ж����մ����ҵ�����˳������ÿһ�ж����մ��ϵ��µ�˳������
//��ɺ�������������һ����ά�����һ���������ж��������Ƿ��и�����

int find(int arr[4][4], int row, int col, int x)
{
	if (arr != NULL && row > 0 && col > 0)
	{
		int i = 0;
		int j = col-1;
		while (i < row && j >= 0)
		{
			if (arr[i][j] == x)
			{
				//printf("%d\n", x);
				return x;
			}
			else if (arr[i][j]>x)
			{
				j--;
			}
			else
			{
				i++;
			}
		}
	}
	return -1;
}
int main()
{
	int arr[][4] = { 1, 2, 8, 9, 2, 4, 9, 12, 4, 7, 10, 13, 6, 8, 11, 15 };
	int row = 4;
	int col = 4;
	int ret=find(arr, row, col, 5);
	printf("%d\n", ret);
	return 0;
}


//��Ŀ�ģ�ʵ��һ�����������ַ����е�ÿ���ո��滻�ɡ�%20�����������롰we are happy.��,
//�������we%20are%20happy.��

void replace(char arr[], int len)
{
	if (arr == NULL || len <= 0)
	{
		return;
	}
	//real_len:�ַ�����ʵ����
	int real_len = 0;
	int blank_num = 0;
	int i = 0;
	while (arr[i] != '\0')
	{
		real_len++;
		if (arr[i] == ' ')
		{
			blank_num++;
		}
		++i;
	}
	//new_len:ת��Ϊ%20����³���
	int new_len = real_len + 2 * blank_num;
	if (new_len > len)
	{
		return;
	}
	//δת��֮ǰ��ĩβ
	int end1 = real_len;
	//ת��֮���ĩβ
	int end2 = new_len;
	while (end1 >= 0 && end2 > end1)
	{
		if (arr[end1] == ' ')
		{
			arr[end2--] = '0';
			arr[end2--] = '2';
			arr[end2--] = '%';
		}
		else
		{
			arr[end2--] = arr[end1];
		}
		--end1;
	}
}


//��Ŀ�壺����ĳ��������ǰ���������������Ľ�������ؽ����ö����������������ǰ�������
//��������Ľ���ж������ظ������֡���������ǰ���������{1��2��4��7��3��5��6��8}��
//�����������{4��7��2��1��5��3��8��6}�����ؽ������������������ͷ�ڵ㡣

struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};
BinaryTreeNode* construct(int preOrder[], int startpre, int endpre, int inOrder[], int startin, int endin)
{
	//��������������������Ӧ���
	if ((endpre - startpre) != (endin - startin))
	{
		return NULL;
	}
	//��ʼλ�ò�Ӧ����ĩβλ��
	if (startpre > endpre)
	{
		return NULL;
	}
	//��������ĵ�һ���ڵ�Ϊ���ڵ�
	int root_val = preOrder[startpre];
	BinaryTreeNode* tree = new BinaryTreeNode();
	tree->m_nValue = root_val;
	tree->m_pLeft = NULL;
	tree->m_pRight = NULL;

	//����������������ֻ��һ���ڵ�ʱ�����ظýڵ�
	if (startpre == endpre)
		return tree;
	//������������ҵ����ڵ�
	int index=0, length=0;
	for (index = startin; index <= endin; index++)
	{
		if (inOrder[index] == preOrder[startpre])
		{
			break;
		}
	}
	//���û�ҵ�������NULL
	if (index > endin)
		return NULL;
	//��������
	if (index > startin)
	{
		length = index - startin;
		tree->m_pLeft=construct(preOrder, startpre + 1, startpre + 1 + length - 1, inOrder, startin, startin + length - 1);
	}
	//�����������ݹ鹹��������
	if (index < endin)
	{
		length = endin - index;
		tree->m_pRight = construct(preOrder, endpre-length+1, endpre, inOrder, endin-length+1, endin);
	}
	return tree;
}




//��Ŀ��������һ�������ͷ�ڵ㣬��β��ͷ��������ӡÿ���ڵ��ֵ

//1.�ݹ�ʵ�֣�������ǳ�����ʱ��Ч�ʵ�
struct PLinkList
{
	int data;
	PLinkList* next;
};
void Print_Tail_To_Head(PLinkList* PList)
{
	if (PList!=NULL)
	{
		Print_Tail_To_Head(PList->next);
		printf("%d->", PList->data);
	}
}
//2.�ǵݹ�ʵ�֣��ݹ�ı��ʾ���ջ�ṹ��������ջ��ʵ��
#include<stack>
struct PLinkList
{
	int data;
	PLinkList* next;
};
void Print_Tail_To_Head(PLinkList* PList)
{
	std::stack<PLinkList*> nodes;
	PLinkList* begin = PList;
	while (begin != NULL)
	{
		nodes.push(begin);
		begin = begin->next;
	}
	while (!nodes.empty())
	{
		begin=nodes.top();
		printf("%d->", begin->data);
		nodes.pop();
	}
}




//��Ŀ�ߣ�������ջʵ��һ�����С����е��������£���ʵ��������������appendTail��deleteHead,
//�ֱ�����ڶ���β����������ڶ���ͷ��ɾ�����Ĺ���

template <typename T> class CQueue
{
public:
	CQueue();
	~CQueue();
	void appendTail(const T& node);
	T deleteHead();
private:
	std::stack<T> stack1;
	std::stack<T> stack2;
};
//���У��Ƚ��ȳ�
//ջ���Ƚ����
template<typename T> void CQueue<T>::appendTail(const T& node)
{
	if (stack1.empty())
	{
		while (!stack2.empty())
		{
			stack1.push(stack2.top());
			stack2.pop();
		}
	}
	stack1.push(node);
}
template<typename T> T CQueue<T>::deleteHead()
{
	if (stack2.empty())
	{
		while (!stack1.empty())
		{
			stack2.push(stack1.top());
			stack1.pop();
		}
	}
	T head = stack2.top();
	stack2.pop();
	return head;

}