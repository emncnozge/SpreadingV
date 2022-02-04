#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
using namespace std;

class Entity
{
public:
	string gates;
	string location;
	string situation;
	int time = 0;
	bool firstinf = 0;
	bool alive = 1;
	bool spreader = 0;
	bool deleted = 0;
	bool immunity = 0;
	bool recovered = 0;
	bool infected = 0;
	bool deadability = 1;
	bool dead = 0;
	int x = 0;
	int y = 0;
	int dx = 0;
	int dy = 0;
};

bool death(int a, int b, int c, int d)
{
	int differencex = abs(a - c);
	int differencey = abs(b - d);
	if (differencex <= 3 && differencey <= 3)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int main()
{
	string path;
	int alive = 0;
	int dead = 0;
	int infected = 0;
	int recovered = 0;
	int deleted = 0;
	map<int, Entity> entity;
	vector<vector<string>> allturns;
	int entitycounter = 0, xcounter = 0, infectedcounter = 0;
	path = "INPUT.txt";
	ofstream turnsfile("TURNS.txt");
	if (turnsfile.is_open()) {}
	turnsfile.close();
	ofstream outfile("OUTPUT.txt");
	if (outfile.is_open()) {}
	outfile.close();
	ifstream file(path.c_str());
	if (file.is_open())
	{
		string find;
		while (file >> find)
		{
			if ("entity" == find) ++entitycounter;
		}
		file.close();
	}
	ifstream file3(path.c_str());
	if (file3.is_open())
	{
		string find;
		while (file3 >> find)
		{
			if ("infected" == find) ++infectedcounter;
		}
		file3.close();
	}
	string word, turn_count1;;
	string size1;
	ifstream inputFile{ "INPUT.txt" };
	string file_contents{ istreambuf_iterator<char>(inputFile), istreambuf_iterator<char>() };
	inputFile.close();
	stringstream stream(file_contents);
	stream >> word;
	stream >> word;
	size1 = word;
	long long size = atoi(size1.c_str());
	stream >> word;
	stream >> word;
	turn_count1 = word;
	long long turn_count = atoi(turn_count1.c_str());
	int entityq = 1;
	string text = file_contents;
	string txt;
	stream >> word;
	stream >> word;
	stream >> word;

	for (int i = 0; i < 10 * entitycounter; i++)
	{
		entity[i + 1].gates = word;
		stream >> word;
		stream >> word;
		if (word == "infected")
		{
			entity[i + 1].infected = 1;
			stream >> word;
			stream >> word;
			stream >> word;
		}
		else if (word == "entity")
		{
			stream >> word;
			stream >> word;
		}
	}
	stringstream stream2(text);
	stream2 >> txt;
	stream2 >> txt;
	stream2 >> txt;
	stream2 >> txt;
	stream2 >> txt;
	stream2 >> txt;
	stream2 >> txt;
	stream2 >> txt;
	for (int i = 0; i < 10 * entitycounter; i++)
	{
		entity[i + 1].location = txt;
		stream2 >> txt;
		if (txt == "infected")
		{
			stream2 >> txt;
			stream2 >> txt;
			stream2 >> txt;
			stream2 >> txt;
		}
		else if (txt == "entity")
		{
			stream2 >> txt;
			stream2 >> txt;
			stream2 >> txt;
		}
	}
	for (int j = 1; j < entitycounter + 1; j++)
	{
		bool cntrl = 0;
		string code = entity[j].location;
		string temp = "";
		for (int i = 0; i < code.size(); i++)
		{
			if (code[i] != 'x' && cntrl == 0)
			{
				temp += code[i];
				int a = stoi(temp);
				entity[j].x = a;
			}
			else if (code[i] == 'x')
			{
				temp = "";
				cntrl = 1;
			}
			else if (code[i] != 'x' && cntrl == 1)
			{
				temp += code[i];
				int a = stoi(temp);
				entity[j].y = a;
			}
			else break;
		}
	}
	string turns = file_contents;
	stringstream stream3(turns);
	string line;
	ifstream file5("INPUT.txt");
	while (turns != "turn")
	{
		stream3 >> turns;
	}
	while (getline(file5, line))
	{
		vector <string> turnler(entitycounter + 2);

		for (int i = 0; i < entitycounter + 2; i++)
		{
			turnler[i] = turns;
			stream3 >> turns;
		}
		for (int i = 0; i < turnler.size() - 2; i++)
		{
			turnler[i] = turnler[i + 2];
		}
		turnler.resize(turnler.size() - 2);
		allturns.push_back(turnler);
	}
	for (int i = 1; i < entitycounter + 1; i++)
		if ((entity[i].gates)[0] == 'A' || (entity[i].gates)[1] == 'A' || (entity[i].gates)[2] == 'A' || (entity[i].gates)[3] == 'A' || (entity[i].gates)[4] == 'A' || (entity[i].gates)[0] == 'B' || (entity[i].gates)[1] == 'B' || (entity[i].gates)[2] == 'B' || (entity[i].gates)[3] == 'B' || (entity[i].gates)[4] == 'B')
		{
			entity[i].immunity = 0;
		}
		else entity[i].immunity = 1;
	for (int i = 1; i < entitycounter + 1; i++) {
		int deathcounter = 0;
		for (int j = 0; j < 5; j++) {
			if ((entity[i].gates)[j] == 'A' || (entity[i].gates)[j] == 'B' || (entity[i].gates)[j] == 'C' || (entity[i].gates)[j] == 'D')
			{
				deathcounter++;
			}
			if (deathcounter >= 3) {
				entity[i].deadability = 1;
			}
			else entity[i].deadability = 0;
		}
	}
	for (int turn = 0; turn < turn_count; turn++)
	{

		for (int i = 1; i < entitycounter + 1; i++)
		{
			for (int j = i + 1; j < entitycounter + 1; j++)
			{
				if ((death(entity[i].x, entity[i].y, entity[j].x, entity[j].y)) && (entity[i].spreader == 1 || entity[j].spreader == 1))
				{
					if (entity[i].immunity != 1)
					{
						entity[i].infected = 1;
					}

					if (entity[j].immunity != 1)
					{
						entity[j].infected = 1;
					}
				}
			}
			if (turn == 0 && entity[i].infected == 1)
			{
				entity[i].firstinf = 1;
			}
			if (entity[i].infected == 1 || entity[i].spreader == 1)
				entity[i].time++;
			if (entity[i].time == 3)
				entity[i].spreader = 1;
			if ((entity[i].deadability == 1) && entity[i].time == 15 && entity[i].firstinf == 1)
			{
				entity[i].dead = 1;
				entity[i].infected = 1;
				entity[i].alive = 0;
				entity[i].dx = entity[i].x;
				entity[i].dy = entity[i].y;
			}
			if ((entity[i].deadability == 1) && entity[i].time == 16 && entity[i].firstinf == 0)
			{
				entity[i].dead = 1;
				entity[i].infected = 1;
				entity[i].alive = 0;
				entity[i].dx = entity[i].x;
				entity[i].dy = entity[i].y;

			}
			if (entity[i].dead == 1 && entity[i].time == 19)
			{
				entity[i].infected = 0;
				entity[i].spreader = 0;
				entity[i].deleted = 1;
				entity[i].alive = 0;
				entity[i].dx = entity[i].x;
				entity[i].dy = entity[i].y;
			}
			if (entity[i].deadability == 0 && entity[i].time == 31)
			{
				entity[i].recovered = 1;
				entity[i].immunity = 1;
				entity[i].alive = 1;
				entity[i].infected = 0;
				entity[i].spreader = 0;
				entity[i].dx = entity[i].x;
				entity[i].dy = entity[i].y;
			}
		}

		for (int i = 0; i < entitycounter; i++)
		{
			bool cntrl = 0;
			string temp = "";
			for (int j = 0; j < allturns[turn][i].size(); j++)
			{
				if (entity[i + 1].alive == 1 && entity[i + 1].dead != 1)
				{

					if (allturns[turn][i][j] != 'x' && cntrl == 0)
					{
						temp += allturns[turn][i][j];
						int a = stoi(temp);
						entity[i + 1].x = a;
					}
					else if (allturns[turn][i][j] == 'x')
					{
						temp = "";
						cntrl = 1;
					}
					else if (allturns[turn][i][j] != 'x' && cntrl == 1)
					{
						temp += allturns[turn][i][j];
						int a = stoi(temp);
						entity[i + 1].y = a;

					}
				}
			}

		}

		for (int i = 1; i < entitycounter + 1; i++)
		{
			if (entity[i].dead == 1)
				entity[i].situation = "dead";
			else if (entity[i].infected == 1)
				entity[i].situation = "infected";
			else if (entity[i].recovered == 1)
				entity[i].situation = "immune";
			else entity[i].situation = "normal";
		}

		ofstream turnsfile("TURNS.txt", ios::app);
		if (turnsfile.is_open()) {
			turnsfile << "Turn " << turn + 1 << ": " << endl;
			for (int i = 0; i < size + 2; i++)
			{
				for (int j = 0; j < size + 2; j++)
				{
					int counter = 1;
					if (i == 0 || i == size + 1 || j == 0 || j == size + 1)
						turnsfile << "-";
					else
					{
						for (int k = 1; k < entitycounter + 1; k++)
						{
							if (i == entity[k].x && j == entity[k].y)
							{
								if (entity[k].infected != 1 && entity[k].spreader != 1 && entity[k].dead == 0 && entity[k].recovered == 0)
									turnsfile << "O";
								else if (entity[k].infected = 1 && entity[k].dead == 0 && entity[k].recovered == 0)
									turnsfile << "X";
								else if ((entity[k].dead == 1 || entity[k].spreader == 1) && entity[k].deleted != 1 && entity[k].recovered == 0)
									turnsfile << "D";
								else if (entity[k].recovered == 1)
									turnsfile << "0";
								else if (entity[k].deleted == 1 && entity[k].recovered == 0)
									turnsfile << " ";
								counter = 2;
							}
						}
						if (counter == 2) continue;
						else turnsfile << " ";
					}
				}
				turnsfile << endl;
			}
		}
		turnsfile.close();
	}

	for (int i = 1; i < entitycounter + 1; i++)
	{
		if (entity[i].recovered == 1)
			recovered++;
		if (entity[i].dead == 1)
			dead++;
		if (entity[i].dead == 0 && (entity[i].infected == 1 || entity[i].spreader == 1))
			infected++;
	}
	ofstream output;
	output.open("OUTPUT.txt");
	output << "Normal    : " << entitycounter - infected - recovered - dead << endl << "Infected  : " << infected << endl << "Dead      : " << dead << endl << "Recovered : " << recovered << endl;
	output.close();
	output.open("OUTPUT.txt", ios::app);

	for (int i = 1; i < entitycounter + 1; i++)
	{
		if (entity[i].situation != "dead")
			output << "entity " << i << " " << allturns[turn_count - 1][i - 1] << " " << entity[i].situation << endl;
		else if (entity[i].situation == "dead")
			output << "entity " << i << " " << entity[i].dx << "x" << entity[i].dy << " " << entity[i].situation << endl;
	}
	output.close();
}