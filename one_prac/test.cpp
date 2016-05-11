#include<stdio.h>
#include<iostream>
#include<string.h>

//题目一：如下为类型CMyString的声明，请为该类型添加赋值操作符函数

//注意四点：1.返回值为该类型的引用(支持连等)
//          2.传人的参数为常量引用(避免拷贝构造的开销)
//          3.释放已有内存
//          4.判断是否是同一个实例
//缺点：当在开辟新内存时，如果此时内存空间容量不够，会分配失败，
//      但已经释放了原有内存，产生错误
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

//优化版本
//创建临时变量和原来的交换，这样当内存不足时，原来的实例并没有改变
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


//题目二：设计一个类，我们只能生成该类的一个实例

//1.缺点：只适用于单线程，当有多个线程同时进入到GetInstance时，而且实例
//没有创建，则两个线程分别创建一个实例，违背单例模式原则
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
//2.只有当实例还没有创建的时候加互斥锁，减小系统开销，并且可以实现多线程
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
//3.利用静态构造函数,在进入主函数之前，就完成初始化，而且只会初始化一次
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


//题目三：在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下的顺序排序
//完成函数，输入这样一个二维数组和一个整数，判断数组中是否含有该整数

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


//题目四：实现一个函数，把字符串中的每个空格都替换成“%20”，例如输入“we are happy.”,
//则输出“we%20are%20happy.”

void replace(char arr[], int len)
{
	if (arr == NULL || len <= 0)
	{
		return;
	}
	//real_len:字符串真实长度
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
	//new_len:转化为%20后的新长度
	int new_len = real_len + 2 * blank_num;
	if (new_len > len)
	{
		return;
	}
	//未转换之前的末尾
	int end1 = real_len;
	//转换之后的末尾
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


//题目五：输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和
//中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1，2，4，7，3，5，6，8}和
//中序遍历序列{4，7，2，1，5，3，8，6}，则重建出二叉树并输出它的头节点。

struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};
BinaryTreeNode* construct(int preOrder[], int startpre, int endpre, int inOrder[], int startin, int endin)
{
	//先序遍历和中序遍历长度应相等
	if ((endpre - startpre) != (endin - startin))
	{
		return NULL;
	}
	//起始位置不应大于末尾位置
	if (startpre > endpre)
	{
		return NULL;
	}
	//先序遍历的第一个节点为根节点
	int root_val = preOrder[startpre];
	BinaryTreeNode* tree = new BinaryTreeNode();
	tree->m_nValue = root_val;
	tree->m_pLeft = NULL;
	tree->m_pRight = NULL;

	//先序遍历和中序遍历只有一个节点时，返回该节点
	if (startpre == endpre)
		return tree;
	//在中序遍历中找到根节点
	int index=0, length=0;
	for (index = startin; index <= endin; index++)
	{
		if (inOrder[index] == preOrder[startpre])
		{
			break;
		}
	}
	//如果没找到，返回NULL
	if (index > endin)
		return NULL;
	//有左子树
	if (index > startin)
	{
		length = index - startin;
		tree->m_pLeft=construct(preOrder, startpre + 1, startpre + 1 + length - 1, inOrder, startin, startin + length - 1);
	}
	//有右子树，递归构造右子树
	if (index < endin)
	{
		length = endin - index;
		tree->m_pRight = construct(preOrder, endpre-length+1, endpre, inOrder, endin-length+1, endin);
	}
	return tree;
}




//题目六：输入一个链表的头节点，从尾到头反过来打印每个节点的值

//1.递归实现，当链表非常长的时候，效率低
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
//2.非递归实现，递归的本质就是栈结构，所以用栈来实现
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




//题目七：用两个栈实现一个队列。队列的声明如下，请实现它的两个函数appendTail和deleteHead,
//分别完成在队列尾部插入结点和在队列头部删除结点的功能

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
//队列：先进先出
//栈：先进后出
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