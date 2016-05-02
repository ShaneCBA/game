#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>

using namespace std;

void debugStr(string str)
{
	str = str + "\n";
	OutputDebugStringA(str.c_str());
}

void debugInt(int num)
{
	debugStr(to_string(num));
}

string removeWhiteSpace(string str)
{
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r') {
			str[i] = '\b';
		}
	}
	return str;
}

class image
{
public:
	map<int, char>colors;
	vector<vector<int>>pixels;//Multi-dimensional vector of pixels [collumns][row]

	int loadImage(string image)
	{
		string line;
		string strFile;
		ifstream newImage(image);
		while (getline(newImage, line))
		{
			line = line + "\n";
			//OutputDebugStringA(line.c_str());
			strFile += line;
		}
		newImage.close();

		strFile = removeWhiteSpace(strFile);

		vector<int>openCarrot;
		vector<int>closeCarrot;

		vector<int>openBrace;
		vector<int>closeBrace;

		vector<int>openBracket;
		vector<int>closeBracket;

		for (int i = 0; strFile[i]; i++)
		{
			switch (strFile[i])
			{
			case '<':
				openCarrot.push_back(i);
				break;
			case '>':
				closeCarrot.push_back(i);
				break;

			case '{':
				openBrace.push_back(i);
				break;
			case '}':
				closeBrace.push_back(i);
				break;

			case '[':
				openBracket.push_back(i);
				break;
			case ']':
				closeBracket.push_back(i);
				break;
			}
		}
		string row;
		string snum;
		int num;
		vector<int>vRow;
		for (int i = 0; i < openCarrot.size() - 1; i++)
		{
			row = strFile.substr(openCarrot[i] + 1, closeCarrot[i] - openCarrot[i] - 1);
			for (int n = 0; row[n]; n++)
			{
				while (isdigit(row[n]))
				{
					snum += row[n];
					n++;
				}
				num = atoi(snum.c_str());
				vRow.push_back(num);
				if (row[n] == ']')
				{
					pixels.push_back(vRow);
					vRow.clear();
					debugStr("*");
				}
				debugStr("==");
				debugInt(num);
				num = 0;
				snum = "";
			}
			debugStr("---");
		}
		
		return true;
	}
};
int main()
{
	image newImage;
	if (newImage.loadImage("test.dpf")) {
	};
}