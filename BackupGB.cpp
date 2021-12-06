#include <iostream>
#include "MyLibs.h"
#include "classAbs.h"
using namespace std;
Abilities a;
bool cont = 1; //Cont pretty much to check if we should start the game loop
char t[6][97]; //The box
void meniu(); //Start up meniu
void death_screen(); //Death Screen
void moveinput(char k, int& p); //moving the player
void back(size_t bac); //Backgrounds 0 - Default hallway, 1 - splitt hallway, 2 - killed enemy, 3 - Skelly, 4 - SkellyWarr, 5 - Demonico, 6 - Beast, 7;8;9 - lastB1/B2/B3, 10 - door
void space(size_t numb_of_spaces); //To help ourselfs with spaces
void decs(int& pos); //Decision for the 2's of the vec
void visual_hud(); //For player and mobs
int find_MAXLength(); //A helper function of visual hud
void game(bool Life, int& pos); //The game loop
void sound(size_t op); //Sound effects
void logmess(size_t op); //Messages box 0 - enc, 1 - Options for player, 2;3 - dmg a lot pl/mob, 4;5 - not dmg pl/mob, 6;7;8;9 - intiN,intiB mob intiN,intiB pl, 10 - armour up, 11 - for hp & stamina, 12 - armour up m
vector <float> atP; //Abilities for player
vector <float> atM; //Abilities for mobs
vector <string> spells; //The vector where all the spells are being placed
vector <short> map; //The map
ofstream E("mobs.txt"); //What attributes the mobs have
ofstream P("player.txt"); //What attributes the player has
float Php{}, Mhp{};
string pname{}, mname{};
int main()
{
	int p = -1; //The position in the map
	mapINIT(map); //Initilizing the map with everything that it needs
	game(1, p); //The actual game
}

void meniu()
{
again:
	system("cls");
	string c;
	ifstream M("Menu.txt");
	while (!M.eof())
	{
		getline(M, c);
		delay(0.1);
		cout << c << "\n";
	}
	M.close();
	auto select = 1;
	while (select != 0)
	{
		//sound(2);
		char op = _getch();
		if (op == '1')
		{
			system("cls");
		}
		else if (op == '2')
		{
			cont = 0;
			break;
		}
		else
		{
			system("cls");
			cout<< "Error espected input 1 or 2 \n NOT " << op << "\n";
			system("pause");
			goto again;
		}
		select--;
	}
}

void death_screen()
{
	system("cls");
	system("color 04");
	const char dead[15] = { "Y O U  D I E D" };
	cout << "\t\t";
	for (auto i = 0; i < strlen(dead); ++i)
	{
		if (dead[i] == ' ')
		{
			delay(0.25);
		}
		else
		{
			delay(0.5);
		}
		cout << dead[i];
	}
	cout << "\n";
	ifstream D("Dead.txt");
	string c;
	while (!D.eof())
	{
		getline(D, c);
		delay(0.2);
		cout << c << "\n";
	}
	D.close();
	system("pause");
}

void decs(int& p)
{
	system("cls");
	system("color 6");
	bool b;
	cout << "\t\t\t ";
	const char mess[] = { "The hallway is splitting into two ways \n\t\t\t In which direction do you want to move ? \n\t\t\t 0 - Left \t\t\t 1 - Right" };
	const char mess2[] = { "The long hallway has come to an end \n\t\t\t There appears to be a door in front of you \n\t\t\t\t Do you want to open it ? \n\t\t\t 0 - No \t\t\t\t 1 - Yes" };
	const char mess3[] = { "The door opened by itself" };
	if (p == 24)
	{
		for (auto j = 0; j < strlen(mess2); ++j)
		{
			if (mess2[j] != '\t' && mess2[j] != '\n')
			{
				delay(0.1);
			}
			cout << mess2[j];
		}
		cout << "\n";
		back(10);
		cin >> b;
		if (b == 1)
		{
			p++;
		}
		else
		{
			system("cls");
			//soundeffect
			cout << "\t\t\t";
			for (auto in = 0; in < strlen(mess3); ++in)
			{
				delay(0.1);
				cout << mess3[in];
			}
		}
	}
	else
	{
		for (auto i = 0; i < strlen(mess); ++i)
		{
			if (mess[i] != '\t' && mess[i] != '\n')
			{
				delay(0.1);
			}
			cout << mess[i];
		}
		cout << "\n";
		back(1);
		cin >> b;
		if (b == 0)
		{
			p++;
		}
		else if (b == 1)
		{
			p += 2;
		}
	}
}

void logmess(size_t op)
{
	const char att[] = { "1. Attack" };
	const char def[] = { "2. Armour up" };
	const char inti[] = { "3. Intimidate" };
	const char det[] = { "'s options:" };
	const char enc[] = { " encoutered an enemy" };
	const char resN[] = { " did a lot of damage" };
	const char resB[] = { " did not do a lot of damage" };
	const char intiB[] = { " was not intimidated" };
	const char intiN[] = { " was intimidated" };
	const char defU[] = { " armoured up" };
	char hpBar[25], staBar[25];
	auto ly = 0, con = 0, ly1 = 0, con1 = 0, ly2 = 0, con2 = 0;
	switch (op)
	{
	case 0: //enc
		logdetailsINIT(t, 6);
		for (size_t x = 0; x < 6; x++)
			for (size_t y = 0; y < 97; y++)
			{
				if (x == 2 && y == 5)
				{
					for (char c : pname)
					{
						t[x][y] = c;
						if (y >= 95)
						{
							x++;
							y = 0;
						}
						else
						{
							y++;
						}
					}
					ly = y;
					con++;
				}
				if (ly != 0 && ly == y && con < 2)
				{
					for (auto i = 0; i < strlen(enc); ++i)
					{
						if (y >= 95)
						{
							x++;
							y = 0;
						}
						t[x][y] = enc[i];
						y++;
					}
					con++;
				}
			}
		for (size_t x = 0; x < 6; x++)
		{
			for (size_t y = 0; y < 97; y++)
			{
				cout << t[x][y];
			}
			cout << "\n";
		}
		break;
	case 1: // For checking the list of things to do to the mob
		logdetailsINIT(t, 6);
		for (size_t x = 0; x < 6; x++)
			for (size_t y = 0; y < 97; y++)
			{
				if (x == 2 && y == 5)
				{
					for (char c : pname)
					{
						t[x][y] = c;
						if (y >= 95)
						{
							x++;
							y = 0;
						}
						else
						{
							y++;
						}
					}
					ly1 = y;
					con1++;
				}
				if (ly1 != 0 && ly1 == y && con1 < 2)
				{
					for (auto i = 0; i < strlen(det); ++i)
					{
						if (y >= 95)
						{
							x++;
							y = 0;
						}
						t[x][y] = det[i];
						y++;
					}
					x++;
					y = 5;
					for (auto in = 0; in < strlen(att); ++in)
					{
						t[x][y] = att[in];
						y++;
					}
					x++;
					auto oldy = y;
					y = 5;
					for (auto inj = 0; inj < strlen(def); ++inj)
					{
						t[x][y] = def[inj];
						y++;
					}
					x--;
					for (auto injj = 0; injj < strlen(inti); ++injj)
					{
						t[x][oldy + 6] = inti[injj];
						oldy++;
					}

					con1++;
				}
			}
		for (size_t x = 0; x < 6; x++)
		{
			for (size_t y = 0; y < 97; y++)
			{
				cout << t[x][y];
			}
			cout << "\n";
		}
		break;
	case 2: // For when we will do damage
		logdetailsINIT(t, 6);
		for (size_t x = 0; x < 6; x++)
			for (size_t y = 0; y < 97; y++)
			{
				if (x == 2 && y == 5)
				{
					for (char c : pname)
					{
						t[x][y] = c;
						if (y >= 95)
						{
							x++;
							y = 0;
						}
						else
						{
							y++;
						}
					}
					for (auto i = 0; i < strlen(resN); ++i)
					{
						t[x][y] = resN[i];
						y++;
					}
				}
			}
		for (size_t x = 0; x < 6; x++)
		{
			for (size_t y = 0; y < 97; y++)
			{
				if (t[x][y] != ' ' && t[x][y] != '|' && t[x][y] != '°' && t[x][y] != '_')
				{
					delay(0.1);
				}
				cout << t[x][y];
			}
			cout << "\n";
		}
		break;
	case 3: // For mobs doing a lot of dmg
		logdetailsINIT(t, 6);
		for (size_t x = 0; x < 6; x++)
			for (size_t y = 0; y < 97; y++)
			{
				if (x == 2 && y == 5)
				{
					for (char c : mname)
					{
						t[x][y] = c;
						if (y >= 95)
						{
							x++;
							y = 0;
						}
						else
						{
							y++;
						}
					}
					for (auto i = 0; i < strlen(resN); ++i)
					{
						t[x][y] = resN[i];
						y++;
					}
				}
			}
		for (size_t x = 0; x < 6; x++)
		{
			for (size_t y = 0; y < 97; y++)
			{
				if (t[x][y] != ' ' && t[x][y] != '|' && t[x][y] != '°' && t[x][y] != '_')
				{
					delay(0.1);
				}
				cout << t[x][y];
			}
			cout << "\n";
		}
		break;
	case 4: //For not a lot of damage
		logdetailsINIT(t, 6);
		for (size_t x = 0; x < 6; x++)
			for (size_t y = 0; y < 97; y++)
			{
				if (x == 2 && y == 5)
				{
					for (char c : pname)
					{
						t[x][y] = c;
						if (y >= 95)
						{
							x++;
							y = 0;
						}
						else
						{
							y++;
						}
					}
					for (auto i = 0; i < strlen(resB); ++i)
					{
						t[x][y] = resB[i];
						y++;
					}
				}
			}
		for (size_t x = 0; x < 6; x++)
		{
			for (size_t y = 0; y < 97; y++)
			{
				if (t[x][y] != ' ' && t[x][y] != '|' && t[x][y] != '°' && t[x][y] != '_')
				{
					delay(0.1);
				}
				cout << t[x][y];
			}
			cout << "\n";
		}
		break;
	case 5: //For not doing a lot of damage mobs
		logdetailsINIT(t, 6);
		for (size_t x = 0; x < 6; x++)
			for (size_t y = 0; y < 97; y++)
			{
				if (x == 2 && y == 5)
				{
					for (char c : mname)
					{
						t[x][y] = c;
						if (y >= 95)
						{
							x++;
							y = 0;
						}
						else
						{
							y++;
						}
					}
					for (auto i = 0; i < strlen(resB); ++i)
					{
						t[x][y] = resB[i];
						y++;
					}
				}
			}
		for (size_t x = 0; x < 6; x++)
		{
			for (size_t y = 0; y < 97; y++)
			{
				if (t[x][y] != ' ' && t[x][y] != '|' && t[x][y] != '°' && t[x][y] != '_')
				{
					delay(0.1);
				}
				cout << t[x][y];
			}
			cout << "\n";
		}
		break;
	case 6: //Intimidated mob
		logdetailsINIT(t, 6);
		for (size_t x = 0; x < 6; x++)
			for (size_t y = 0; y < 97; y++)
			{
				if (x == 2 && y == 5)
				{
					for (char c : mname)
					{
						t[x][y] = c;
						if (y >= 95)
						{
							x++;
							y = 0;
						}
						else
						{
							y++;
						}
					}
					for (auto i = 0; i < strlen(intiN); ++i)
					{
						t[x][y] = intiN[i];
						y++;
					}
				}
			}
		for (size_t x = 0; x < 6; x++)
		{
			for (size_t y = 0; y < 97; y++)
			{
				if (t[x][y] != ' ' && t[x][y] != '|' && t[x][y] != '°' && t[x][y] != '_')
				{
					delay(0.1);
				}
				cout << t[x][y];
			}
			cout << "\n";
		}
		break;
	case 7: //Not intimidated mob
		logdetailsINIT(t, 6);
		for (size_t x = 0; x < 6; x++)
			for (size_t y = 0; y < 97; y++)
			{
				if (x == 2 && y == 5)
				{
					for (char c : mname)
					{
						t[x][y] = c;
						if (y >= 95)
						{
							x++;
							y = 0;
						}
						else
						{
							y++;
						}
					}
					for (auto i = 0; i < strlen(intiB); ++i)
					{
						t[x][y] = intiB[i];
						y++;
					}
				}
			}
		for (size_t x = 0; x < 6; x++)
		{
			for (size_t y = 0; y < 97; y++)
			{
				if (t[x][y] != ' ' && t[x][y] != '|' && t[x][y] != '°' && t[x][y] != '_')
				{
					delay(0.1);
				}
				cout << t[x][y];
			}
			cout << "\n";
		}
		break;
	case 8: //Intimidated Player
		logdetailsINIT(t, 6);
		for (size_t x = 0; x < 6; x++)
			for (size_t y = 0; y < 97; y++)
			{
				if (x == 2 && y == 5)
				{
					for (char c : pname)
					{
						t[x][y] = c;
						if (y >= 95)
						{
							x++;
							y = 0;
						}
						else
						{
							y++;
						}
					}
					for (auto i = 0; i < strlen(intiN); ++i)
					{
						t[x][y] = intiN[i];
						y++;
					}
				}
			}
		for (size_t x = 0; x < 6; x++)
		{
			for (size_t y = 0; y < 97; y++)
			{
				if (t[x][y] != ' ' && t[x][y] != '|' && t[x][y] != '°' && t[x][y] != '_')
				{
					delay(0.1);
				}
				cout << t[x][y];
			}
			cout << "\n";
		}
		break;
	case 9: //Not intimidated Player
		logdetailsINIT(t, 6);
		for (size_t x = 0; x < 6; x++)
			for (size_t y = 0; y < 97; y++)
			{
				if (x == 2 && y == 5)
				{
					for (char c : pname)
					{
						t[x][y] = c;
						if (y >= 95)
						{
							x++;
							y = 0;
						}
						else
						{
							y++;
						}
					}
					for (auto i = 0; i < strlen(intiB); ++i)
					{
						t[x][y] = intiB[i];
						y++;
					}
				}
			}
		for (size_t x = 0; x < 6; x++)
		{
			for (size_t y = 0; y < 97; y++)
			{
				if (t[x][y] != ' ' && t[x][y] != '|' && t[x][y] != '°' && t[x][y] != '_')
				{
					delay(0.1);
				}
				cout << t[x][y];
			}
			cout << "\n";
		}
		break;
	case 10: //Armoured up pl
		logdetailsINIT(t, 6);
		for (size_t x = 0; x < 6; x++)
			for (size_t y = 0; y < 97; y++)
			{
				if (x == 2 && y == 5)
				{
					for (char c : pname)
					{
						t[x][y] = c;
						y++;
					}
					for (auto i = 0; i < strlen(defU); ++i)
					{
						t[x][y] = defU[i];
						y++;
					}
				}
			}
		for (size_t x = 0; x < 6; x++)
		{
			for (size_t y = 0; y < 97; y++)
			{
				if (t[x][y] != ' ' && t[x][y] != '|' && t[x][y] != '°' && t[x][y] != '_')
				{
					delay(0.1);
				}
				cout << t[x][y];
			}
			cout << "\n";
		}
		break;
	case 11: //hp bar & stamina bar
		logdetailsINIT(t, 6);
		break;
	case 12: //armour up m
		logdetailsINIT(t, 6);
		for (size_t x = 0; x < 6; x++)
			for (size_t y = 0; y < 97; y++)
			{
				if (x == 2 && y == 5)
				{
					for (char c : mname)
					{
						t[x][y] = c;
						y++;
					}
					for (auto i = 0; i < strlen(defU); ++i)
					{
						t[x][y] = defU[i];
						y++;
					}
				}
			}
		for (size_t x = 0; x < 6; x++)
		{
			for (size_t y = 0; y < 97; y++)
			{
				if (t[x][y] != ' ' && t[x][y] != '|' && t[x][y] != '°' && t[x][y] != '_')
				{
					delay(0.1);
				}
				cout << t[x][y];
			}
			cout << "\n";
		}
		break;
	}
}

void moveinput(char k, int& p)
{
	while (k != 's' && k != 'S' && k != 'w' && k != 'W')
	{
		system("cls");
		system("color F");
		back(0);
		cin >> k;
	}
	if ((k == 'S' || k == 's') && p == 0)
	{
		p++;
		p--;
	}
	else if (k == 'S' || k == 's')
	{
		p--;
	}
	else if (k == 'w' || k == 'W')
	{
		p++;
	}
}

int find_MAXLength()
{
	int max = -41055, len{};
	len = mname.size() + 11;
	getMax(len, max);
	len = 0;
	len = Mhp + 4;
	getMax(len, max);
	len = 0;
	len = atM.at(0) + 4;
	getMax(len, max);
	return max;
}

void visual_hud()
{
	cout << " " << pname << "'s STATS :";
	int len = find_MAXLength();
	space(92 - len - mname.size() - pname.size());
	cout << mname << "'s STATS :\n";
	for (auto in = 0; in < 96; in++)
	{
		if (in % 2 == 0)
		{
			cout << "<";
		}
		else
		{
			cout << ">";
		}
	}
	cout << endl;
	cout << " HP: ";
	for (auto in = 0; in < Php; in++)
	{
		cout << "#";
	}
	space(92 - len - Mhp);
	cout << "HP: ";
	for (auto in = 0; in < Mhp; in++)
	{
		cout << "#";
	}
	cout << endl;
	cout << " STA:";
	for (auto in = 0; in < atP.at(0); in++)
	{
		cout << "*";
	}
	space(92 - len - atM.at(0));
	cout << "STA:";
	for (auto in = 0; in < atM.at(0); in++)
	{
		cout << "*";
	}
	cout << endl;
}

void sound(size_t op)
{
	switch (op)
	{
	case 0: //Skellies damage taken
		PlaySound(TEXT("skellydmg.wav"), NULL, SND_FILENAME | SND_ASYNC);
		delay(3);
		break;
	case 1: //Guy damage
		PlaySound(TEXT("takedmg.wav"), NULL, SND_FILENAME | SND_ASYNC);
		delay(3);
		break;
	case 2: //Theme for staring
		PlaySound(TEXT("thunder.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	}
}

void space(size_t num_of_spaces)
{
	for (auto in = 0; in < num_of_spaces; in++)
	{
		cout << " ";
	}
}

void back(size_t bac)
{
	//To get the middle of it you find the mid of the log file which is 48 and then you find the mid of the file you are trying to get and subtract them both and got em
	ifstream H3("Hallway3.txt");
	ifstream H1("Hallway.txt");
	ifstream BS("battlesucces.txt");
	ifstream Skel1("skell.txt");
	ifstream Skel2("skell2.txt");
	ifstream Dem("demonico.txt");
	ifstream Beast("beast.txt");
	ifstream F1("Fboss1.txt");
	ifstream F2("Fboss2.txt");
	ifstream F3("Fboss3.txt");
	ifstream Door("door.txt");
	string c;
	const char warn[] = { "T H I S  F I G H T" };
	switch (bac)
	{
	case 0: //Default hallway
		system("cls");
		while (!H3.eof())
		{
			getline(H3, c);
			space(29);
			cout << c << "\n";
		}
		break;
	case 1: //Decs
		while (!H1.eof())
		{
			getline(H1, c);
			space(22);
			cout << c << "\n";
		}
		break;
	case 2: //succes
		system("cls");
		system("color 4");
		while (!BS.eof())
		{
			getline(BS, c);
			space(33);
			delay(0.5);
			cout << c << " \n";
		}
		cout << "\t\t\t\t Y O U  W I N";
		delay(2);
		cout << ", \n\t\t\t\t";
		for (auto in = 0; in < strlen(warn); ++in)
		{
			if (warn[in] == warn[in + 1])
			{
				continue;
			}
			else
			{
				delay(0.2);
			}
			cout << warn[in];
		}
		cout << endl << "\t\t\t\t";
		system("pause");
		break;
	case 3: //Skelly
		system("color F");
		while (!Skel1.eof())
		{
			getline(Skel1, c);
			space(31);
			cout << c << "\n";
		}
		break;
	case 4: //Skelly Warrior
		system("color F");
		while (!Skel2.eof())
		{
			getline(Skel2, c);
			space(11);
			cout << c << "\n";
		}
		break;
	case 5: //Demonico
		system("color D");
		while (!Dem.eof())
		{
			getline(Dem, c);
			space(15);
			cout << c << "\n";
		}
		break;
	case 6: //Beast
		system("color 2");
		while (!Beast.eof())
		{
			getline(Beast, c);
			space(14);
			cout << c << "\n";
		}
		break;
	case 7: //First encounter
		//IDK what colour
		while (!F1.eof())
		{
			getline(F1, c);
			space(27);
			cout << c << "\n";
		}
		break;
	case 8: //If you piss him off
		//colour
		while (!F2.eof())
		{
			getline(F2, c);
			space(35);
			cout << c << "\n";
		}
		break;
	case 9: //Final boss fight
		//colour
		while (!F3.eof())
		{
			getline(F3, c);
			space(12);
			cout << c << "\n";
		}
		break;
	case 10: //Door
		while (!Door.eof())
		{
			getline(Door, c);
			space(12);
			cout << c << "\n";
		}
		break;
	}
	H3.close();
	H1.close();
	BS.close();
	Skel1.close();
	Skel2.close();
	Dem.close();
	Beast.close();
	F1.close();
	F2.close();
	F3.close();
	Door.close();
}

void game(bool Life,int& pos)
{
	system("color F");
	meniu();
	if (cont == 0) //Check that the game is starting
	{
		Life = false;
	}
	else
	{
	again:
		Life = true;
		a.addAbP();
		P.close();
		cout << "Press any key to continue ";
		char key = _getch();
		system("cls");
		while (Life) // Actual game loop
		{
			moveinput(key, pos);
			switch (map.at(pos))
			{
			case 0:
				break;
			case 1:
				if (pos >= 3 && pos <= 6) //Skelly
				{
					a.battle('!');
					if (Php <= 0)
					{
						Life = false;
					}
				}
				else if (pos >= 9 && pos <= 13) //SkellyWarrior
				{
					a.battle('@');
					if (Php <= 0)
					{
						Life = false;
					}
				}
				else if (pos == 15) //Demonico
				{
					//battle
					if (Php <= 0)
					{
						Life = false;
					}
				}
				else if (pos == 15) //Beast
				{
					//battle
					if (Php <= 0)
					{
						Life = false;
					}
				}
				break;
			case 2:
				decs(pos);
				break;
			case 3:
				break;
			case 4:
				system("cls");
				cout << "Done";
				break;
			}
		}
		if (Life == false)
		{
			death_screen();
			system("cls");
			system("color F");
			cout << "Do you want to try again ? \n 0 - No \t 1 - Yes \n";
			bool ag;
			cin >> ag;
			if (ag)
			{
				goto again;
			}
			else
			{
				system("cls");
			}
		}
	}
}

void Abilities::addAbP() // Adding the player
{
	id = 'P';
	P << id << endl;
	cout << "Your name is going to be : \n";
	cin >> name;
	pname = name;
	P << name << endl;
	system("pause");
	cout << "You have 25 points to get yourself started \n Use them with caution \n";
	delay(3);
	auto l = 25;
	hp = 0.0;
	stamina = 0.0;
	armour = 0;
	strength = 0;
	mana = 0;
	num_of_spells = 0;
	name_of_spell = "Nothing";
	while (l != 0)
	{
	again:
		system("cls");
		cout << "Press the adjacent number to add a level to it \n Number of points left are : " << l << "\n";
		cout << "1. HP " << hp << "\n" << "2. STAMINA " << stamina << "\n" << "3. STRENGTH " << strength << "\n" << "4. ARMOUR " << armour << "\n";
		char op = _getch();
		if (op == '1')
		{
			hp++;
		}
		else if (op == '2')
		{
			stamina++;
		}
		else if (op == '3')
		{
			strength++;
		}
		else if (op == '4')
		{
			armour++;
		}
		else
		{
			system("cls");
			cout << "Error espected input 1 or 2 or 3 or 4 \n NOT " << op << "\n";
			system("pause");
			goto again;
		}
		l--;
	}
	Php = hp;
	atP.push_back(stamina);
	atP.push_back(strength);
	atP.push_back(armour);
	atP.push_back(mana);
	atP.push_back(num_of_spells);
	P << hp << endl << stamina << endl << strength << endl << armour << endl << mana << endl << num_of_spells << endl << name_of_spell;
}

void Abilities::addAbM(char id)
{
	E << id << endl;
	switch (id)
	{
	case '!': //For skelies
		name = "Skelly";
		mname = name;
		hp = 6.5;
		Mhp = hp;
		atM.clear();
		stamina = 10;
		strength = 3;
		armour = 0;
		mana = 0;
		num_of_spells = 0;
		atM.push_back(stamina);
		atM.push_back(strength);
		atM.push_back(armour);
		atM.push_back(mana);
		atM.push_back(num_of_spells);
		name_of_spell = "Nothing";
		E << name << endl << hp << endl << stamina << endl << strength << endl << armour << endl << mana << endl << num_of_spells << endl << name_of_spell << endl << endl;
		break;
	case '@': //For Skelies warrior
		name = "SkellyWarrior";
		mname = name;
		hp = 6.5;
		Mhp = hp;
		atM.clear();
		stamina = 12;
		strength = 5;
		armour = 3;
		mana = 0;
		num_of_spells = 0;
		atM.push_back(stamina);
		atM.push_back(strength);
		atM.push_back(armour);
		atM.push_back(mana);
		atM.push_back(num_of_spells);
		name_of_spell = "Nothing";
		E << name << endl << hp << endl << stamina << endl << strength << endl << armour << endl << mana << endl << num_of_spells << endl << name_of_spell << endl << endl;
		break;
	case '#': //For Demons
		name = "Demonico";
		mname = name;
		hp = 13.5;
		Mhp = hp;
		atM.clear();
		stamina = 9;
		strength = 8;
		armour = 0;
		mana = 8;
		num_of_spells = 2;
		atM.push_back(stamina);
		atM.push_back(strength);
		atM.push_back(armour);
		atM.push_back(mana);
		atM.push_back(num_of_spells);
		name_of_spell = "Fireball";
		spells.push_back(name_of_spell);
		name_of_spell = "HellFire";
		spells.push_back(name_of_spell);
		E << name << endl << hp << endl << stamina << endl << strength << endl << armour << endl << mana << endl << num_of_spells << endl << name_of_spell << endl << endl;
		break;
	case '$': //For beast
		name = "Beast";
		mname = name;
		hp = 14;
		Mhp = hp;
		atM.clear();
		stamina = 18;
		strength = 11;
		armour = 1;
		num_of_spells = 0;
		atM.push_back(stamina);
		atM.push_back(strength);
		atM.push_back(armour);
		atM.push_back(mana);
		atM.push_back(num_of_spells);
		name_of_spell = "Nothing";
		E << name << endl << hp << endl << stamina << endl << strength << endl << armour << endl << mana << endl << num_of_spells << endl << name_of_spell << endl << endl;
		break;
	case '%': //For Boss
		name = "Devil_Boss";
		mname = name;
		hp = 40;
		Mhp = hp;
		atM.clear();
		stamina = 30;
		strength = 100;
		armour = 20;
		num_of_spells = 5;
		atM.push_back(stamina);
		atM.push_back(strength);
		atM.push_back(armour);
		atM.push_back(mana);
		atM.push_back(num_of_spells);
		name_of_spell = "Heal";
		spells.push_back(name_of_spell);
		name_of_spell = "Death";
		spells.push_back(name_of_spell);
		name_of_spell = "Dizzy";
		spells.push_back(name_of_spell);
		E << name << endl << hp << endl << stamina << endl << strength << endl << armour << endl << mana << endl << num_of_spells << endl << name_of_spell << endl << endl;
		break;
	}
}

void Abilities::battle(char id)
{
	system("cls");
	size_t enem{}; //To know which background to print out
	switch (id) //To print out the actual background of the enemy
	{
	case '!': //For when encountered a skelly
		a.addAbM('!');
		back(3);
		enem = 3;
		break;
	case '@': //For when encountered a skellyWarrior
		a.addAbM('@');
		back(4);
		enem = 4;
		break;
	case '#': //For when encountered a demonico
		a.addAbM('#');
		back(5);
		enem = 5;
		break;
	case '$': //For when encoutered a beast
		a.addAbM('$');
		back(6);
		enem = 6;
		break;
	}
	logmess(0); //encounter
	cout << "\n Press any key to continue ... \n";
	char ac = _getch();
	auto mac = 0, pac = 0;
	while (Php > 0 && Mhp > 0) //Fight time
	{
		system("cls");
		visual_hud();
		back(enem);
		logmess(1); //Options are presented
		cout << "\n";
		cin >> ac;
		if (ac == '1') //Attack
		{
			pac = 0;
			if (atP.at(pac) > 0) //To check if we have stamina to hit the enemy
			{
				atP.at(pac) -= 2;
				pac = 1;
				mac = 2;
				if (atM.at(mac) == 0) //To check if the enemy has armour or not
				{
					Mhp -= atP.at(pac) / 2; //If no it gets a good chunck of damage
					system("cls");
					visual_hud();
					back(enem);
					logmess(2);
					cout << "\n";
					system("pause");
				}
				else
				{
					Mhp -= atP.at(pac) / atM.at(mac); //If so it doesn't get a good chunck of damage
					system("cls");
					visual_hud();
					back(enem);
					logmess(4);
					cout << "\n";
					system("pause");
				}
			}
		}
		else if (ac == '2') //Armour up
		{
			pac = 2;
			atP.at(pac) += 2;
			pac = 0;
			atP.at(pac) += 3;
			system("cls");
			visual_hud();
			back(enem);
			logmess(10);
			system("pause");
		}
		else if (ac == '3') //Intimidate
		{
			pac = 0;
			system("cls");
			if (Mhp < 4 || atP.at(pac)>10)
			{
				visual_hud();
				back(enem);
				logmess(6); //Success
				atP.at(pac)++;
			}
			else
			{
				visual_hud();
				back(enem);
				logmess(7); //Not success
			}
			cout << "\n";
			system("pause");
		}
		if (Mhp > 0)
		{
			switch (enem)
			{
			case 3:
				if (SkellyA() == 0)
				{
					mac = 0;
					if (atM.at(mac) > 0)
					{
						atM.at(mac) -= 2;
						mac = 1;
						pac = 2;
						if (atP.at(pac) == 0)
						{
							Php -= atM.at(mac) / 2; //Same thing from the player side
							system("cls");
							visual_hud();
							back(enem);
							logmess(3);
							cout << "\n";
							system("pause");
						}
						else
						{
							Php -= atM.at(mac) / atP.at(pac); //same thing from the player side
							system("cls");
							visual_hud();
							back(enem);
							logmess(5);
							cout << "\n";
							system("pause");
						}
					}
				}
				else if (SkellyA() == 1)
				{
					mac = 2;
					atM.at(mac) += 2;
					mac = 0;
					atM.at(mac) += 3;
					system("cls");
					visual_hud();
					back(enem);
					logmess(12);
					system("pause");
				}
				else if (SkellyA() == 2)
				{
					mac = 0;
					system("cls");
					if (Php < 4 || atM.at(mac)>10)
					{
						atM.at(mac)++;
						visual_hud();
						back(enem);
						logmess(8); //Success
					}
					else
					{
						visual_hud();
						back(enem);
						logmess(9); //Not success
					}
					cout << "\n";
					system("pause");
				}
				break;
			case 4: //SkellyWar
				if (SkellyA() == 0)
				{
					mac = 0;
					if (atM.at(mac) > 0)
					{
						atM.at(mac) -= 2;
						pac = 2;
						mac = 1;
						if (atP.at(pac) == 0)
						{
							Php -= atM.at(mac) / 2; //Same thing from the player side
							system("cls");
							visual_hud();
							back(enem);
							logmess(3);
							cout << "\n";
							system("pause");
						}
						else
						{
							Php -= atM.at(mac) / atP.at(pac); //same thing from the player side
							system("cls");
							visual_hud();
							back(enem);
							logmess(5);
							cout << "\n";
							system("pause");
						}
					}
				}
				else if (SkellyA() == 1)
				{
					mac = 2;
					atM.at(mac) += 2;
					mac = 0;
					atM.at(mac) += 3;
					system("cls");
					visual_hud();
					back(enem);
					logmess(12);
					system("pause");
				}
				else if (SkellyA() == 2)
				{
					mac = 0;
					system("cls");
					if (Php < 4 || atM.at(mac)>10)
					{
						visual_hud();
						back(enem);
						atM.at(mac)++;
						logmess(8); //Success
					}
					else
					{
						visual_hud();
						back(enem);
						logmess(9); //Not success
					}
					cout << "\n";
					system("pause");
				}
				break;
			case 5: //Demon
				if (DemonicoA() == 0)
				{
					//Spells
				}
				else if (DemonicoA() == 1)
				{
					mac = 0;
					if (atM.at(mac) > 0)
					{
						atM.at(mac) -= 2;
						pac = 2;
						mac = 1;
						if (atP.at(pac) == 0)
						{
							Php -= atM.at(mac) / 2; //Same thing from the player side
							system("cls");
							visual_hud();
							back(enem);
							logmess(3);
							cout << "\n";
							system("pause");
						}
						else
						{
							Php -= atM.at(mac) / atP.at(pac); //same thing from the player side
							system("cls");
							visual_hud();
							back(enem);
							logmess(5);
							cout << "\n";
							system("pause");
						}
					}
				}
				else if (DemonicoA() == 2)
				{
					mac = 2;
					atM.at(mac) += 2;
					mac = 0;
					atM.at(mac) += 3;
					system("cls");
					visual_hud();
					back(enem);
					logmess(12);
					system("pause");
				}
				else if (DemonicoA() == 3)
				{
					mac = 0;
					system("cls");
					visual_hud();
					back(enem);
					if (Php < 4 || atM.at(mac)>10)
					{
						logmess(8); //Success
						atM.at(mac)++;
					}
					else
					{
						logmess(9); //Not success
					}
					cout << "\n";
					system("pause");
				}
				break;
			case 6: //beast
				break;
			case 7: //LastBoss
				break;
			case 8: //LastLastBoss
				break;
			}
		}
	}
	if (Mhp <= 0)
	{
		back(2);
	}
}