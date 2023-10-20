#include<bits/stdc++.h>
#include <conio.h>
#include<fstream>
#include <windows.h>
using namespace std;
int a[4][4];
int ans;
int flagx = true; //用于判断是否无效操作
const char* file_path = "2048游戏存档.txt";

/*string returnstring(int x)
{
	if (x == 0)
	{
		return " ";
	}
	else
	{
		cout << x;
	}
}*/
/*void show()
{
	cout << "-------------------------"<<endl;
	for (int i = 0; i < 4; i++)
	{
		cout << "|     |     |     |     |"<<endl;
		cout << "|  " << returnstring(a[i][0]) << "  |  " << returnstring(a[i][1])
			<< "  |  " << returnstring(a[i][2]) << "  |  " << returnstring(a[i][3])<<"  |  " << endl;
		cout << "|     |     |     |     |"<<endl;
		cout << "-------------------------" << endl;
	}
}*/


//输出简约风格界面
void testshow()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (a[i][j] == 0)
			{
				cout << "\t";
			}
			else
			{
				if (a[i][j] >= 1024)
				{
					cout << "\033[31;1m" << a[i][j] << "\t" << "\033[0m";
					//system("color 0f");
					//cout << a[i][j] << "\t";
				}
				else if (a[i][j] >= 512)
				{
					cout << "\033[33;1m" << a[i][j] << "\t" << "\033[0m" ;
					//system("color 0f");
					//cout << a[i][j] << "\t";
				}
				else if(a[i][j] >= 256)
				{
					cout << "\033[34;1m" << a[i][j] << "\t" << "\033[0m" ;
				}
				else if (a[i][j] >= 128)
				{
					cout << "\033[35;1m" << a[i][j] << "\t" << "\033[0m";
				}
				else if (a[i][j] >= 64)
				{
					cout << "\033[36;1m" << a[i][j] << "\t" << "\033[0m";
				}
				else if (a[i][j] >= 16)
				{
					cout << "\033[32;1m" << a[i][j] << "\t" << "\033[0m";
				}
				else if (a[i][j] >= 8)
				{
					cout << "\033[37;1m" << a[i][j] << "\t" << "\033[0m";
				}
				else
				{
					cout << a[i][j] << "\t";
				}
			}
		}
		cout << endl<< endl<< endl;
	}
	cout << endl << endl;
	cout << "项督凯版权所有";
}

//网格中0的个数
int blanknum(int b[4][4]) //统计空白格个数
{
	int num = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (b[i][j] == 0)
			{
				num++;
			}
		}
	}
	return num;
}

//随机生成【x，y】之间的整数
int randomint(int x, int y) 
{
	srand((unsigned)time(NULL));
	return rand() % (y - x + 1) + x;
}

//按9：1概率生成2，4
int randomint_24()
{
	int x = randomint(1, 10);
	if (x ==4)
	{
		return 4;
	}
	else
	{
		return 2;
	}
}

//在网格空位中随机位置添加2或4
void add_num()
{
	int n = blanknum(a);
	if (n < 1)
	{
		return;
	}
	else
	{
		int index = randomint(1, n);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (a[i][j] == 0)
				{
					index--;
					if (index == 0)
					{
						a[i][j] = randomint_24();
						ans += a[i][j];
						return;
					}
				}
			}
		}
	}
}

/*typedef enum _keypress {
	escape,
	up,
	left,
	down,
	right
} keypress;*/
//获取键盘输入的上下左右
int get_keypress() {
	int key;

	while (1) {
		key = _getch();

		if (key == 0xE0) {
			key = _getch();
			switch (key) {
			case 0x48: return 1;
			case 0x4B: return 2;
			case 0x4D: return 3;
			case 0x50: return 4;
			}
		}
		else if (key == 0x1B) {
			return 0;
		}
	}
}

//判断是否无效操作
bool Issame(int a[4][4],int b[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (a[i][j] != b[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

//上下左右操作
void operate_up()
{
	//排除上方的0
	for (int i = 1; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (a[i - 1][j] == 0)
			{
				bool flag = false;
				for (int k = i - 1; k < 3; k++)
				{
					if (a[k + 1][j])
					{
						flag = true;
					}
					a[k][j] = a[k + 1][j];
				}
				a[3][j] = 0;
				if (flag)
				{
					j--;
				}
			}
		}
	}
	//向上合并相同项
	for (int i = 1; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (a[i][j] == a[i - 1][j])
			{
				a[i - 1][j] *= 2;
				for (int k = i; k < 3; k++)
				{
					a[k][j] = a[k + 1][j];
				}
				a[3][j] = 0;
			}
		}
	}
}
void operate_down()
{
	//排除下方的0
	for (int i = 2; i >= 0; i--)
	{
		for (int j = 3; j >= 0; j--)
		{
			if (a[i + 1][j] == 0)
			{
				bool flag = false;
				for (int k = i + 1; k > 0; k--)
				{
					if (a[k - 1][j])
					{
						flag = true;
					}
					a[k][j] = a[k - 1][j];
				}
				a[0][j] = 0;
				if (flag)
				{
					j++;
				}
			}
		}
	}
	//向下合并相同项
	for (int i = 2; i >= 0; i--)
	{
		for (int j = 3; j >= 0; j--)
		{
			if (a[i][j] == a[i + 1][j])
			{
				a[i + 1][j] *= 2;
				for (int k = i; k > 0; k--)
				{
					a[k][j] = a[k - 1][j];
				}
				a[0][j] = 0;
			}
		}
	}
}
void operate_left()
{
	//排除左方的0
	for (int j = 1; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (a[i][j - 1] == 0)
			{
				bool flag = false;
				for (int k = j - 1; k < 3; k++)
				{
					if (a[i][k + 1])
					{
						flag = true;
					}
					a[i][k] = a[i][k + 1];
				}
				a[i][3] = 0;
				if (flag)
				{
					i--;
				}
			}
		}
	}
	//向左合并相同项
	for (int j = 1; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (a[i][j] == a[i][j - 1])
			{
				a[i][j - 1] *= 2;
				for (int k = j; k < 3; k++)
				{
					a[i][k] = a[i][k + 1];
				}
				a[i][3] = 0;
			}
		}
	}
}
void operate_right()
{
	//排除右方的0
	for (int j = 2; j >= 0; j--)
	{
		for (int i = 3; i >= 0; i--)
		{
			if (a[i][j + 1] == 0)
			{
				bool flag = false;
				for (int k = j + 1; k > 0; k--)
				{
					if (a[i][k - 1])
					{
						flag = true;
					}
					a[i][k] = a[i][k - 1];
				}
				a[i][0] = 0;
				if (flag)
				{
					i++;
				}
			}
		}
	}
	//向右合并相同项
	for (int j = 2; j >= 0; j--)
	{
		for (int i = 3; i >= 0; i--)
		{
			if (a[i][j] == a[i][j + 1])
			{
				a[i][j + 1] *= 2;
				for (int k = j; k > 0; k--)
				{
					a[i][k] = a[i][k - 1];
				}
				a[i][0] = 0;
			}
		}
	}
}

bool operate(int key)
{
	//拷贝一份数组a给b
	int b[4][4] = {};
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			b[i][j] = a[i][j];
		}
	}

	switch (key)
	{
	case 0: //escape
		return false;
		break;
	case 1: //up
		operate_up();
		if (!Issame(a, b))
		{
			flagx = false;
		}
		return true;
		break;
	case 2: //left
		operate_left();
		if (!Issame(a, b))
		{
			flagx = false;
		}
		return true;
		break;
	case 3: //right
		operate_right();
		if (!Issame(a, b))
		{
			flagx = false;
		}
		return true;
		break;
	case 4: //down
		operate_down();
		if (!Issame(a, b))
		{
			flagx = false;
		}
		return true;
		break;
	default:
		break;
	}
}

//判断是否真的无法继续
bool Isover(int c[4][4])
{
	//复制一份数据给b，为了不改变全局变量a
	int b[4][4] = {};
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			b[i][j] = c[i][j];
		}
	}
	//向上试探性合并
	for (int i = 1; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (b[i][j] == b[i - 1][j])
			{
				b[i - 1][j] *= 2;
				for (int k = i; k < 3; k++)
				{
					b[k][j] =b[k + 1][j];
				}
				b[3][j] = 0;
			}
		}
	}
	//向左试探性合并
	for (int j = 1; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (b[i][j] == b[i][j - 1])
			{
				b[i][j - 1] *= 2;
				for (int k = j; k < 3; k++)
				{
					b[i][k] = b[i][k + 1];
				}
				b[i][3] = 0;
			}
		}
	}
	if (blanknum(b) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//hello
void hello()
{
	system("color 0e");
	cout << "欢迎来到2048游戏\n\n游戏制作者：项督凯\n\n项督凯版权所有\n\n";
	Sleep(2000);
	cout << "游戏即将开始……\n";
	Sleep(2000);
	system("cls");
	system("color 0f");
}

//分数统计
int sum()
{
	int ans = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ans += a[i][j];
		}
	}
	return ans;
}

//读档
bool read()
{
	cout << "1.新游戏\n2.读取存档\n";
	int p;
	cin >> p;
	if (p == 1)
	{
		return false;
	}
	ifstream ifs;
	ifs.open("2048游戏存档", ios::in | ios::binary);
	if (!ifs.is_open())
	{
		ifs.close();
		return false;
	}
	int ch;
	ifs >> ch;
	if (ifs.eof())
	{
		ifs.close();
		return false;
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (i == 0 && j == 0)
				{
					a[i][j] = ch;
				}
				else
				{
					ifs >> a[i][j];
				}
			}
		}
		ifs >> ans;
		if (ans != sum())
		{
			cout << endl;
			ifs.close();
			remove(file_path);
			cout << "存档文件遭篡改！！！" << endl;
			if (remove(file_path))
			{
				printf("Could not delete the file %s \n", file_path);
			}
			Sleep(3000);
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					a[i][j] = 0;
				}
			}
			ans = 0;
			return false;
		}
		ifs.close();
		return true;
	}
}

//存档
void save()
{
	ofstream ofs;
	ofs.open("2048游戏存档", ios::out | ios::binary);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ofs << a[i][j] << " ";
		}
		ofs << endl;
	}
	cout<< "当前你的成绩是： " << ans << endl;
	//cout << sum() << endl;
	ofs << ans << endl;
}


int main()
{
	hello();
	int flag = true;
	int readflag;
	readflag = read();
	system("cls");
	//cout << readflag << endl;
	if (!readflag)
	{
		add_num();
	}
	while (true)
	{
		testshow();
		flagx = true;
		while (flagx)
		{
			int keypress = get_keypress();
			//cout << keypress << endl;
			flag = operate(keypress);
			if (!flag || (blanknum(a) == 0 && Isover(a)))
			{
				break;
			}
		}
		//system("pause");
		system("cls");
		if (flag == false)
		{
			int p;
			cout << "1.存档\n2.不存档，直接退出\n";
			cin >> p;
			if (p == 1)
			{
				save();
				cout << "已存档" << endl;
				break;
			}
			else
			{
				cout << "本次最终得分是： " << ans << endl << endl;
				if (remove(file_path))
				{
					printf("Could not delete the file %s !!!\n\n", file_path);
				}
				Sleep(2000);
				cout << "Game Over!" << endl;
				break;
			}
		}
		else if (blanknum(a) == 0)
		{
			if (Isover(a))
			{
				cout << "本次最终得分是： " << ans << endl << endl;
				if (remove(file_path))
				{
					printf("Could not delete the file %s !!!\n\n", file_path);
				}
				Sleep(2000);
				cout << "Game Over!" << endl;
				break;
			}
		}
		add_num();
	}
	system("pause");
	return 0;
}

//经测试，无法成功删除文件。无其他bug.