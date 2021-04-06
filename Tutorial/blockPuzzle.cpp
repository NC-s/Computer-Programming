#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include<string>
#include <stdlib.h>
#include <ctime>
#include <cstring>

using namespace std;

char player_sea[10][10] = { '\0' };
char PC_sea[10][10] = { '\0' };
const int sizeCarrier = 5;
const int sizeBattleship = 4;
const int sizeSubmarine = 3;
const int sizeDestroyer = 2;

//  use object for types of ship
class Carrier
{
public:
	Carrier()
	{
		v = 0;
		placedDirection = '0';
		placedRow = '0';
		placedColumn = 0;
		for (int i = 0; i < sizeCarrier; i++)
		{
			h[i] = 0;
		}

	}

	void arrangement(bool inUse, char placedD, char placedR, int placedC)
	{
		v = inUse;
		placedDirection = placedD;
		placedRow = placedR; //for Y
		placedColumn = placedC; //for X
		for (int i = 0; i < sizeCarrier; i++)
		{
			h[i] = 1;
		}
	}

	int attack_check(bool attacker, char attack_Y, int attack_X, char player_sea[][10], char PC_sea[][10], int sea_size, bool PC_sea_attacked[][10], bool player_sea_attacked[][10], int seaPCI[][10])
	{
		if (v == 1)
		{
			int testSumHealth = 0;

			if (placedDirection == 'H')
			{
				if (attack_Y == placedRow)
				{
					if ((placedColumn <= attack_X) && (attack_X < placedColumn + sizeCarrier))
					{
						if (h[attack_X - placedColumn] == 0)
						{
							return 1;
						}
						else
						{
							h[attack_X - placedColumn]--;
						}

						for (int i = 0; i < sizeCarrier; i++)
						{
							testSumHealth += h[i];
						}

						if (testSumHealth == 0)
						{
							if (attacker == 0) //The player did that attack
							{
								PC_sea[(int)attack_Y - 65][attack_X] = 'H';
								PC_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							else if (attacker == 1) // The PC did that attack
							{
								player_sea[(int)attack_Y - 65][attack_X] = 'H';
								player_sea_attacked[(int)attack_Y - 65][attack_X] = 1;

								//reset probability inside seaPCI
								if (placedColumn != 0) // Left hand side < 0
									if (seaPCI[(int)placedRow - 65][placedColumn - 1] >= 25)
										seaPCI[(int)placedRow - 65][placedColumn - 1] -= 25;
								if (placedColumn + sizeCarrier != sea_size) // Right hand side > sea_size
									if (seaPCI[(int)placedRow - 65][placedColumn + 1] >= 25)
										seaPCI[(int)placedRow - 65][placedColumn + 1] -= 25;
								for (int i = 0; i < sizeCarrier; i++)
								{
									if ((int)placedRow - 65 != 0) //Upper head < 0
										if (seaPCI[(int)placedRow - 65 - 1][placedColumn + i] >= 25)
											seaPCI[(int)placedRow - 65 - 1][placedColumn + i] -= 25;
									if ((int)placedRow - 65 + 1 != sea_size) //Lower > sea_size
										if (seaPCI[(int)placedRow - 65 + 1][placedColumn + i] >= 25)
											seaPCI[(int)placedRow - 65 + 1][placedColumn + i] -= 25;
								}
							}
							return 3;
						}
						else
						{
							if (attacker == 0) //The player attacked
							{
								PC_sea[(int)attack_Y - 65][attack_X] = 'H';
								PC_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							else if (attacker == 1) // The PC did that attack
							{
								player_sea[(int)attack_Y - 65][attack_X] = 'H';
								player_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							return 2;

						}
					}
					else
					{
						if (attacker == 0) //The player attacked
						{
							if (PC_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
							{
								PC_sea[(int)attack_Y - 65][attack_X] = '*';
							}
						}
						else if (attacker == 1) // The PC attacked
						{
							if (player_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
								player_sea[(int)attack_Y - 65][attack_X] = '*';
						}
						return 0;
					}
				}
				else
				{
					if (attacker == 0) //The player attacked
					{
						if (PC_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
						{
							PC_sea[(int)attack_Y - 65][attack_X] = '*';
						}
					}
					else if (attacker == 1) // The PC attacked
					{
						if (player_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
							player_sea[(int)attack_Y - 65][attack_X] = '*';
					}
					return 0;
				}
			}
			else if (placedDirection == 'V')
			{
				if (attack_X == placedColumn)
				{
					if ((int)placedRow <= (int)attack_Y && (int)attack_Y < (int)placedRow + sizeCarrier)
					{
						if (h[(int)attack_Y - (int)placedRow] == 0)
						{
							return 1;
						}
						else
						{
							h[(int)attack_Y - (int)placedRow]--;
						}

						for (int i = 0; i < sizeCarrier; i++)
						{
							testSumHealth += h[i];
						}

						if (testSumHealth == 0)
						{
							if (attacker == 0) //The player attacked
							{
								PC_sea[(int)attack_Y - 65][attack_X] = 'H';
								PC_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							else if (attacker == 1) // The PC attacked
							{
								player_sea[(int)attack_Y - 65][attack_X] = 'H';
								player_sea_attacked[(int)attack_Y - 65][attack_X] = 1;

								//reset probability inside seaPCI
								if ((int)placedRow - 65 != 0) // Upper head < 0
									if (seaPCI[(int)placedRow - 65 - 1][placedColumn] >= 25)
										seaPCI[(int)placedRow - 65 - 1][placedColumn] -= 25;
								if ((int)placedRow + sizeCarrier - 65 != sea_size) // Lower > sea_size
									if (seaPCI[(int)placedRow - 65 + sizeCarrier][placedColumn] >= 25)
										seaPCI[(int)placedRow - 65 + sizeCarrier][placedColumn] -= 25;
								for (int i = 0; i < sizeCarrier; i++)
								{
									if (placedColumn != 0) //Left < 0
										if (seaPCI[(int)placedRow - 65 + i][placedColumn - 1] >= 25)
											seaPCI[(int)placedRow - 65 + i][placedColumn - 1] -= 25;
									if (placedColumn + 1 != sea_size) //Right > sea_size
										if (seaPCI[(int)placedRow - 65 + i][placedColumn + 1] >= 25)
											seaPCI[(int)placedRow - 65 + i][placedColumn + 1] -= 25;
								}
							}
							return 3;
						}
						else
						{
							if (attacker == 0) //The player attacked
							{
								PC_sea[(int)attack_Y - 65][attack_X] = 'H';
								PC_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							else if (attacker == 1) // The PC attacked
							{
								player_sea[(int)attack_Y - 65][attack_X] = 'H';
								player_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							return 2;
						}
					}
					else
					{
						if (attacker == 0) //The player attacked
						{
							if (PC_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
							{
								PC_sea[(int)attack_Y - 65][attack_X] = '*';
							}
						}
						else if (attacker == 1) // The PC attacked
						{
							if (player_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
								player_sea[(int)attack_Y - 65][attack_X] = '*';
						}
						return 0;

					}
				}
				else
				{
					if (attacker == 0) //The player  attacked
					{
						if (PC_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
						{

							PC_sea[(int)attack_Y - 65][attack_X] = '*';
						}
					}
					else if (attacker == 1) // The PC  attacked
					{
						if (player_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
							player_sea[(int)attack_Y - 65][attack_X] = '*';
					}
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
		return 0;
	}

private:
	bool v;  // check number of ship is either valid or invalid (more than what user specify)
	char placedDirection; // either h for horizontal direction or v for vertical direction
	char placedRow; // the row shows (A~J) / Along the Y-axis
	int placedColumn; // the column shows (0~9) / Along the X-axis
	int h[sizeCarrier];
};

class Battleship
{
public:
	Battleship()
	{
		v = 0;
		placedDirection = '0';
		placedRow = '0';
		placedColumn = 0;
		for (int i = 0; i < sizeBattleship; i++)
		{
			h[i] = 0;
		}

	}

	void arrangement(bool inUse, char placedD, char placedR, int placedC)
	{
		v = inUse;
		placedDirection = placedD;
		placedRow = placedR; // for Y
		placedColumn = placedC; //for X
		for (int i = 0; i < sizeBattleship; i++)
		{
			h[i] = 1;
		}
	}

	int attack_check(bool attacker, char attack_Y, int attack_X, char player_sea[][10], char PC_sea[][10], int sea_size, bool PC_sea_attacked[][10], bool player_sea_attacked[][10], int seaPCI[][10])
	{
		if (v == 1)
		{
			int testSumHealth = 0;

			if (placedDirection == 'H')
			{
				if (attack_Y == placedRow)
				{
					if ((placedColumn <= attack_X) && (attack_X < placedColumn + sizeBattleship))
					{
						if (h[attack_X - placedColumn] == 0)
						{
							return 1;
						}
						else
						{
							h[attack_X - placedColumn]--;
						}

						for (int i = 0; i < sizeBattleship; i++)
						{
							testSumHealth += h[i];
						}

						if (testSumHealth == 0)
						{
							if (attacker == 0) //The player did that attack
							{
								PC_sea[(int)attack_Y - 65][attack_X] = 'H';
								PC_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							else if (attacker == 1) // The PC did that attack
							{
								player_sea[(int)attack_Y - 65][attack_X] = 'H';
								player_sea_attacked[(int)attack_Y - 65][attack_X] = 1;

								//reset probability inside seaPCI
								if (placedColumn != 0) // Left hand side < 0
									if (seaPCI[(int)placedRow - 65][placedColumn - 1] >= 25)
										seaPCI[(int)placedRow - 65][placedColumn - 1] -= 25;
								if (placedColumn + sizeBattleship != sea_size) // Right hand side > sea_size
									if (seaPCI[(int)placedRow - 65][placedColumn + 1] >= 25)
										seaPCI[(int)placedRow - 65][placedColumn + 1] -= 25;
								for (int i = 0; i < sizeBattleship; i++)
								{
									if ((int)placedRow - 65 != 0) //Upper head < 0
										if (seaPCI[(int)placedRow - 65 - 1][placedColumn + i] >= 25)
											seaPCI[(int)placedRow - 65 - 1][placedColumn + i] -= 25;
									if ((int)placedRow - 65 + 1 != sea_size) //Lower head > sea_size
										if (seaPCI[(int)placedRow - 65 + 1][placedColumn + i] >= 25)
											seaPCI[(int)placedRow - 65 + 1][placedColumn + i] -= 25;
								}
							}
							return 3;
						}
						else
						{
							if (attacker == 0) //The player  attacked
							{
								PC_sea[(int)attack_Y - 65][attack_X] = 'H';
								PC_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							else if (attacker == 1) // The PC  attacked
							{
								player_sea[(int)attack_Y - 65][attack_X] = 'H';
								player_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							return 2;
						}
					}
					else
					{
						if (attacker == 0) //The player  attacked
						{
							if (PC_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
							{
								PC_sea[(int)attack_Y - 65][attack_X] = '*';
							}
						}
						else if (attacker == 1) // The PC  attacked
						{
							if (player_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
								player_sea[(int)attack_Y - 65][attack_X] = '*';
						}
						return 0;
					}
				}
				else
				{
					if (attacker == 0) //The player attacked
					{
						if (PC_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
						{
							PC_sea[(int)attack_Y - 65][attack_X] = '*';
						}
					}
					else if (attacker == 1) // The PC  attacked
					{
						if (player_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
							player_sea[(int)attack_Y - 65][attack_X] = '*';
					}
					return 0;
				}
			}
			else if (placedDirection == 'V')
			{
				if (attack_X == placedColumn)
				{
					if ((int)placedRow <= (int)attack_Y && (int)attack_Y < (int)placedRow + sizeBattleship)
					{
						if (h[(int)attack_Y - (int)placedRow] == 0)
						{
							return 1;
						}
						else
						{
							h[(int)attack_Y - (int)placedRow]--;
						}

						for (int i = 0; i < sizeBattleship; i++)
						{
							testSumHealth += h[i];
						}

						if (testSumHealth == 0)
						{
							if (attacker == 0) //The player attacked
							{
								PC_sea[(int)attack_Y - 65][attack_X] = 'H';
								PC_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							else if (attacker == 1) // The PC attacked
							{
								player_sea[(int)attack_Y - 65][attack_X] = 'H';
								player_sea_attacked[(int)attack_Y - 65][attack_X] = 1;

								//reset probability inside seaPCI
								if ((int)placedRow - 65 != 0) // Upper head < 0
									if (seaPCI[(int)placedRow - 65 - 1][placedColumn] >= 25)
										seaPCI[(int)placedRow - 65 - 1][placedColumn] -= 25;
								if ((int)placedRow + sizeBattleship - 65 != sea_size) // Lower > sea_size
									if (seaPCI[(int)placedRow - 65 + sizeBattleship][placedColumn] >= 25)
										seaPCI[(int)placedRow - 65 + sizeBattleship][placedColumn] -= 25;
								for (int i = 0; i < sizeBattleship; i++)
								{
									if (placedColumn != 0) //Left < 0
										if (seaPCI[(int)placedRow - 65 + i][placedColumn - 1] >= 25)
											seaPCI[(int)placedRow - 65 + i][placedColumn - 1] -= 25;
									if (placedColumn + 1 != sea_size) //Right > sea_size
										if (seaPCI[(int)placedRow - 65 + i][placedColumn + 1] >= 25)
											seaPCI[(int)placedRow - 65 + i][placedColumn + 1] -= 25;
								}
							}
							return 3;
						}
						else
						{
							if (attacker == 0) //The player attacked
							{
								PC_sea[(int)attack_Y - 65][attack_X] = 'H';
								PC_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							else if (attacker == 1) // The PC attacked
							{
								player_sea[(int)attack_Y - 65][attack_X] = 'H';
								player_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							return 2;
						}
					}
					else
					{
						if (attacker == 0) //The player attacked
						{
							if (PC_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
							{
								PC_sea[(int)attack_Y - 65][attack_X] = '*';
							}
						}
						else if (attacker == 1) // The PC attacked
						{
							if (player_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
								player_sea[(int)attack_Y - 65][attack_X] = '*';
						}
						return 0;
					}
				}
				else
				{
					if (attacker == 0) //The player attacked
					{
						if (PC_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
						{

							PC_sea[(int)attack_Y - 65][attack_X] = '*';
						}
					}
					else if (attacker == 1) // The PC attacked
					{
						if (player_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
							player_sea[(int)attack_Y - 65][attack_X] = '*';
					}
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
		return 0;
	}

private:
	bool v;  // check number of ship is either valid or invalid (more than what user specify)
	char placedDirection; // either h for horizontal or v for vertical
	char placedRow; // the row shows (A~J) / Along the Y-axis
	int placedColumn; // the column shows (0~9) / Along the X-axis
	int h[sizeBattleship];
};

class Submarine
{
public:
	Submarine()
	{
		v = 0;
		placedDirection = '0';
		placedRow = '0';
		placedColumn = 0;
		for (int i = 0; i < sizeSubmarine; i++)
		{
			h[i] = 0;
		}

	}

	void arrangement(bool inUse, char placedD, char placedR, int placedC)
	{
		v = inUse;
		placedDirection = placedD;
		placedRow = placedR; //for Y
		placedColumn = placedC; //For X
		for (int i = 0; i < sizeSubmarine; i++)
		{
			h[i] = 1;
		}
	}

	int attack_check(bool attacker, char attack_Y, int attack_X, char player_sea[][10], char PC_sea[][10], int sea_size, bool PC_sea_attacked[][10], bool player_sea_attacked[][10], int seaPCI[][10])
	{
		if (v == 1)
		{
			int testSumHealth = 0;

			if (placedDirection == 'H')
			{
				if (attack_Y == placedRow)
				{
					if ((placedColumn <= attack_X) && (attack_X < placedColumn + sizeSubmarine))
					{
						if (h[attack_X - placedColumn] == 0)
						{
							return 1;
						}
						else
						{
							h[attack_X - placedColumn]--;
						}

						for (int i = 0; i < sizeSubmarine; i++)
						{
							testSumHealth += h[i];
						}

						if (testSumHealth == 0)
						{
							if (attacker == 0) //The player attacked
							{
								PC_sea[(int)attack_Y - 65][attack_X] = 'H';
								PC_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							else if (attacker == 1) // The PC attacked
							{
								player_sea[(int)attack_Y - 65][attack_X] = 'H';
								player_sea_attacked[(int)attack_Y - 65][attack_X] = 1;

								//reset probability inside seaPCI
								if (placedColumn != 0) // Left hand side < 0
									if (seaPCI[(int)placedRow - 65][placedColumn - 1] >= 25)
										seaPCI[(int)placedRow - 65][placedColumn - 1] -= 25;
								if (placedColumn + sizeSubmarine != sea_size) // Right hand side > sea_size
									if (seaPCI[(int)placedRow - 65][placedColumn + 1] >= 25)
										seaPCI[(int)placedRow - 65][placedColumn + 1] -= 25;
								for (int i = 0; i < sizeSubmarine; i++)
								{
									if ((int)placedRow - 65 != 0) //Upper head < 0
										if (seaPCI[(int)placedRow - 65 - 1][placedColumn + i] >= 25)
											seaPCI[(int)placedRow - 65 - 1][placedColumn + i] -= 25;
									if ((int)placedRow - 65 + 1 != sea_size) //Lower head > sea_size
										if (seaPCI[(int)placedRow - 65 + 1][placedColumn + i] >= 25)
											seaPCI[(int)placedRow - 65 + 1][placedColumn + i] -= 25;
								}
							}
							return 3;
						}
						else
						{
							if (attacker == 0) //The player attacked
							{
								PC_sea[(int)attack_Y - 65][attack_X] = 'H';
								PC_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							else if (attacker == 1) // The PC attacked
							{
								player_sea[(int)attack_Y - 65][attack_X] = 'H';
								player_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							return 2;
						}
					}
					else
					{
						if (attacker == 0) //The player attacked
						{
							if (PC_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
							{
								PC_sea[(int)attack_Y - 65][attack_X] = '*';
							}
						}
						else if (attacker == 1) // The PC attacked
						{
							if (player_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
								player_sea[(int)attack_Y - 65][attack_X] = '*';
						}
						return 0;
					}
				}
				else
				{
					if (attacker == 0) //The player attacked
					{
						if (PC_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
						{
							PC_sea[(int)attack_Y - 65][attack_X] = '*';
						}
					}
					else if (attacker == 1) // The PC attacked
					{
						if (player_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
							player_sea[(int)attack_Y - 65][attack_X] = '*';
					}
					return 0;
				}
			}
			else if (placedDirection == 'V')
			{
				if (attack_X == placedColumn)
				{
					if ((int)placedRow <= (int)attack_Y && (int)attack_Y < (int)placedRow + sizeSubmarine)
					{
						if (h[(int)attack_Y - (int)placedRow] == 0)
						{
							return 1;
						}
						else
						{
							h[(int)attack_Y - (int)placedRow]--;
						}

						for (int i = 0; i < sizeSubmarine; i++)
						{
							testSumHealth += h[i];
						}

						if (testSumHealth == 0)
						{
							if (attacker == 0) //The player attacked
							{
								PC_sea[(int)attack_Y - 65][attack_X] = 'H';
								PC_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							else if (attacker == 1) // The PC attacked
							{
								player_sea[(int)attack_Y - 65][attack_X] = 'H';
								player_sea_attacked[(int)attack_Y - 65][attack_X] = 1;

								//reset probability inside seaPCI
								if ((int)placedRow - 65 != 0) // Upper head < 0
									if (seaPCI[(int)placedRow - 65 - 1][placedColumn] >= 25)
										seaPCI[(int)placedRow - 65 - 1][placedColumn] -= 25;
								if ((int)placedRow + sizeSubmarine - 65 != sea_size) // Lower > sea_size
									if (seaPCI[(int)placedRow - 65 + sizeSubmarine][placedColumn] >= 25)
										seaPCI[(int)placedRow - 65 + sizeSubmarine][placedColumn] -= 25;
								for (int i = 0; i < sizeSubmarine; i++)
								{
									if (placedColumn != 0) //Left < 0
										if (seaPCI[(int)placedRow - 65 + i][placedColumn - 1] >= 25)
											seaPCI[(int)placedRow - 65 + i][placedColumn - 1] -= 25;
									if (placedColumn + 1 != sea_size) //Right > sea_size
										if (seaPCI[(int)placedRow - 65 + i][placedColumn + 1] >= 25)
											seaPCI[(int)placedRow - 65 + i][placedColumn + 1] -= 25;
								}
							}
							return 3;
						}
						else
						{
							if (attacker == 0) //The player attacked
							{
								PC_sea[(int)attack_Y - 65][attack_X] = 'H';
								PC_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							else if (attacker == 1) // The PC attacked
							{
								player_sea[(int)attack_Y - 65][attack_X] = 'H';
								player_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							return 2;
						}
					}
					else
					{
						if (attacker == 0) //The player attacked
						{
							if (PC_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
							{
								PC_sea[(int)attack_Y - 65][attack_X] = '*';
							}
						}
						else if (attacker == 1) // The PC attacked
						{
							if (player_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
								player_sea[(int)attack_Y - 65][attack_X] = '*';
						}
						return 0;
					}
				}
				else
				{
					if (attacker == 0) //The player attacked
					{
						if (PC_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
						{

							PC_sea[(int)attack_Y - 65][attack_X] = '*';
						}
					}
					else if (attacker == 1) // The PC attacked
					{
						if (player_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
							player_sea[(int)attack_Y - 65][attack_X] = '*';
					}
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
		return 0;
	}

private:
	bool v;  // check number of ship is either valid or invalid (more than what user specify)
	char placedDirection; // either h for horizontal or v for vertical
	char placedRow; // the row shows (A~J) / Along the Y-axis
	int placedColumn; // the column shows (0~9) / Along the X-axis
	int h[sizeBattleship];
};

class Destroyer
{
public:
	Destroyer()
	{
		v = 0;
		placedDirection = '0';
		placedRow = '0';
		placedColumn = 0;
		for (int i = 0; i < sizeDestroyer; i++)
		{
			h[i] = 0;
		}

	}

	void arrangement(bool inUse, char placedD, char placedR, int placedC)
	{
		v = inUse;
		placedDirection = placedD;
		placedRow = placedR; //for Y
		placedColumn = placedC; //for X
		for (int i = 0; i < sizeDestroyer; i++)
		{
			h[i] = 1;
		}
	}

	int attack_check(bool attacker, char attack_Y, int attack_X, char player_sea[][10], char PC_sea[][10], int sea_size, bool PC_sea_attacked[][10], bool player_sea_attacked[][10], int seaPCI[][10])
	{
		if (v == 1)
		{
			int testSumHealth = 0;

			if (placedDirection == 'H')
			{
				if (attack_Y == placedRow)
				{
					if ((placedColumn <= attack_X) && (attack_X < placedColumn + sizeDestroyer))
					{
						if (h[attack_X - placedColumn] == 0)
						{
							return 1;
						}
						else
						{
							h[attack_X - placedColumn]--;
						}

						for (int i = 0; i < sizeDestroyer; i++)
						{
							testSumHealth += h[i];
						}

						if (testSumHealth == 0)
						{
							if (attacker == 0) //The player attacked
							{
								PC_sea[(int)attack_Y - 65][attack_X] = 'H';
								PC_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							else if (attacker == 1) // The PC attacked
							{
								player_sea[(int)attack_Y - 65][attack_X] = 'H';
								player_sea_attacked[(int)attack_Y - 65][attack_X] = 1;

								//reset probability inside seaPCI
								if (placedColumn != 0) // Left hand side < 0
									if (seaPCI[(int)placedRow - 65][placedColumn - 1] >= 25)
										seaPCI[(int)placedRow - 65][placedColumn - 1] -= 25;
								if (placedColumn + sizeDestroyer != sea_size) // Right hand side > sea_size
									if (seaPCI[(int)placedRow - 65][placedColumn + 1] >= 25)
										seaPCI[(int)placedRow - 65][placedColumn + 1] -= 25;
								for (int i = 0; i < sizeDestroyer; i++)
								{
									if ((int)placedRow - 65 != 0) //Upper head < 0
										if (seaPCI[(int)placedRow - 65 - 1][placedColumn + i] >= 25)
											seaPCI[(int)placedRow - 65 - 1][placedColumn + i] -= 25;
									if ((int)placedRow - 65 + 1 != sea_size) //Lower head > sea_size
										if (seaPCI[(int)placedRow - 65 + 1][placedColumn + i] >= 25)
											seaPCI[(int)placedRow - 65 + 1][placedColumn + i] -= 25;
								}
							}
							return 3;
						}
						else
						{
							if (attacker == 0) //The player attacked
							{
								PC_sea[(int)attack_Y - 65][attack_X] = 'H';
								PC_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							else if (attacker == 1) // The PC attacked
							{
								player_sea[(int)attack_Y - 65][attack_X] = 'H';
								player_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							return 2;
						}
					}
					else
					{
						if (attacker == 0) //The player attacked
						{
							if (PC_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
							{
								PC_sea[(int)attack_Y - 65][attack_X] = '*';
							}
						}
						else if (attacker == 1) // The PC attacked
						{
							if (player_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
								player_sea[(int)attack_Y - 65][attack_X] = '*';
						}
						return 0;
					}
				}
				else
				{
					if (attacker == 0) //The player attacked
					{
						if (PC_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
						{
							PC_sea[(int)attack_Y - 65][attack_X] = '*';
						}
					}
					else if (attacker == 1) // The PC attacked
					{
						if (player_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
							player_sea[(int)attack_Y - 65][attack_X] = '*';
					}
					return 0;
				}
			}
			else if (placedDirection == 'V')
			{
				if (attack_X == placedColumn)
				{
					if ((int)placedRow <= (int)attack_Y && (int)attack_Y < (int)placedRow + sizeDestroyer)
					{
						if (h[(int)attack_Y - (int)placedRow] == 0)
						{
							return 1;
						}
						else
						{
							h[(int)attack_Y - (int)placedRow]--;
						}

						for (int i = 0; i < sizeDestroyer; i++)
						{
							testSumHealth += h[i];
						}

						if (testSumHealth == 0)
						{
							if (attacker == 0) //The player attacked
							{
								PC_sea[(int)attack_Y - 65][attack_X] = 'H';
								PC_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							else if (attacker == 1) // The PC attacked
							{
								player_sea[(int)attack_Y - 65][attack_X] = 'H';
								player_sea_attacked[(int)attack_Y - 65][attack_X] = 1;

								//reset probability inside seaPCI
								if ((int)placedRow - 65 != 0) // Upper head < 0
									if (seaPCI[(int)placedRow - 65 - 1][placedColumn] >= 25)
										seaPCI[(int)placedRow - 65 - 1][placedColumn] -= 25;
								if ((int)placedRow + sizeDestroyer - 65 != sea_size) // Lower > sea_size
									if (seaPCI[(int)placedRow - 65 + sizeDestroyer][placedColumn] >= 25)
										seaPCI[(int)placedRow - 65 + sizeDestroyer][placedColumn] -= 25;
								for (int i = 0; i < sizeDestroyer; i++)
								{
									if (placedColumn != 0) //Left < 0
										if (seaPCI[(int)placedRow - 65 + i][placedColumn - 1] >= 25)
											seaPCI[(int)placedRow - 65 + i][placedColumn - 1] -= 25;
									if (placedColumn + 1 != sea_size) //Right > sea_size
										if (seaPCI[(int)placedRow - 65 + i][placedColumn + 1] >= 25)
											seaPCI[(int)placedRow - 65 + i][placedColumn + 1] -= 25;
								}
							}
							return 3;
						}
						else
						{
							if (attacker == 0) //The player attacked
							{
								PC_sea[(int)attack_Y - 65][attack_X] = 'H';
								PC_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							else if (attacker == 1) // The PC attacked
							{
								player_sea[(int)attack_Y - 65][attack_X] = 'H';
								player_sea_attacked[(int)attack_Y - 65][attack_X] = 1;
							}
							return 2;
						}
					}
					else
					{
						if (attacker == 0) //The player attacked
						{
							if (PC_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
							{
								PC_sea[(int)attack_Y - 65][attack_X] = '*';
							}
						}
						else if (attacker == 1) // The PC attacked
						{
							if (player_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
								player_sea[(int)attack_Y - 65][attack_X] = '*';
						}
						return 0;
					}
				}
				else
				{
					if (attacker == 0) //The player attacked
					{
						if (PC_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
						{

							PC_sea[(int)attack_Y - 65][attack_X] = '*';
						}
					}
					else if (attacker == 1) // The PC attacked
					{
						if (player_sea_attacked[(int)attack_Y - 65][attack_X] == 0)
							player_sea[(int)attack_Y - 65][attack_X] = '*';
					}
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
		return 0;
	}

private:
	bool v;  // check number of ship is either valid or invalid (more than what user specify)
	char placedDirection; // either h for horizontal or v for vertical
	char placedRow; // the row shows (A~J) / Along the Y-axis
	int placedColumn; // the column shows (0~9) / Along the X-axis
	int h[sizeBattleship];
};
//end of object used  

//Function protypes 
void game(char player_sea[][10], char PC_sea[][10], bool WhoStartFirst, bool DisplayPCShips, int sea_size, int numCarrier, int numBattleship, int numSubmarine, int numDestroyer);

void game_arrangement_player(char player_sea[][10], int sea_size, int numCarrier, int numBattleship, int numSubmarine, int numDestroyer, Carrier PlayerCarrier[5], Battleship PlayerBattleship[5], Submarine PlayerSubmarine[5], Destroyer PlayerDestroyer[5]);
void game_arrangement_PC(char PC_sea[][10], int sea_size, int numCarrier, int numBattleship, int numSubmarine, int numDestroyer, Carrier PCCarrier[5], Battleship PCBattleship[5], Submarine PCSubmarine[5], Destroyer PCDestroyer[5]);
void game_arrangement_instruction(int sea_size);

void game_printSea_player(int sea_size);
void game_printSea_PC(int sea_size, bool DisplayPCShips);

void game_battlestage(char player_sea[][10], char PC_sea[][10], bool WhoStartFirst, bool DisplayPCShips, int sea_size, int numCarrier, int numBattleship, int numSubmarine, int numDestroyer, Carrier PlayerCarrier[5], Battleship PlayerBattleship[5], Submarine PlayerSubmarine[5], Destroyer PlayerDestroyer[5], Carrier PCCarrier[5], Battleship PCBattleship[5], Submarine PCSubmarine[5], Destroyer PCDestroyer[5]);
void game_printSea_battlestage(int sea_size, bool DisplayPCShips);
void game_quit();

void PCI_decide_attack(int size, int seaPCI[][10], int &, int &, int &, int &, int &);
int PCI_calculate_Pro(int size, int pro, int seaPCI[][10]);

void PCI_attack_phrase(int size, int seaPCI[][10], int numUnknownPro, int numLowPro, int numMedPro, int numHighPro, int numVHighPro, char &attack_Y, int &attack_X);
void PCI_fire(int size, int pro, int numPro, int seaPCI[][10], char &attack_Y, int &attack_X);

void setting(bool &WhoStartFirst, bool &DisplayPCShips, int &sea_size, int &numCarrier, int &numBattleship, int &numSubmarine, int &numDestroyer);
void whoFirst(bool &WhoStartFirst);
void displayPCships(bool &DisplayPCShips);
void boardSize(int &board_size, int numCarrier, int numBattleship, int numSubmarine, int numDestroyer);
void numberOFships(int sea_size, int &numCarrier, int &numBattleship, int &numSubmarine, int &numDestroyer);

void instructions();

void credits();


int main()
{

	bool WhoStartFirst = 0;
	bool DisplayPCShips = 0;
	int sea_size = 10;
	int numCarrier = 1;
	int numBattleship = 2;
	int numSubmarine = 3;
	int numDestroyer = 4;

	int prog_choice;

MAIN_MENU:
	do {
		system("cls");
		cout << "Welcome to Block Puzzle Game!~ " << endl;
		cout << "Let's get started!!!" << endl;

		cout << "\n";

		cout << "*** Game Menu ***" << endl;
		cout << "[1] Start Game" << endl;
		cout << "[2] Settings" << endl;
		cout << "[3] Instructions" << endl;
		cout << "[4] Credits" << endl;
		cout << "[5] Exit" << endl;
		cout << "*****************" << endl;
		cout << endl;
		cout << "Option (1 - 5): ";
		cin >> prog_choice;
		switch (prog_choice)
		{
		case 1: game(player_sea, PC_sea, WhoStartFirst, DisplayPCShips, sea_size, numCarrier, numBattleship, numSubmarine, numDestroyer); break;
		case 2: setting(WhoStartFirst, DisplayPCShips, sea_size, numCarrier, numBattleship, numSubmarine, numDestroyer); break;
		case 3: instructions(); break;
		case 4: credits(); break;
		case 5: {
			char ans;

			cout << "Quit?" << endl;
			cout << "Please input 'y'/'Y' if you want to quit ." << endl;
			cout << "Please input 'n'/'N'if you want to return the main menu ." << endl;
			cin >> ans;

			if (ans == 'y' || ans == 'Y')
				cout << "Thanks for playing!~ Bye Bye! " << endl;
			else if (ans == 'n' || ans == 'N')
				goto MAIN_MENU;
			else
			{
				cout << "Wrong input! The program will not define." << endl;
				system("pause");
			}
		}	break;
		default:
			cout << "Please enter choice 1 - 5 only." << endl;
			system("pause");
			break;
		}
		cin.clear();
		cin.ignore(10000, '\n');
	} while (prog_choice != 5);
	return 0;
}

void game(char player_sea[][10], char PC_sea[][10], bool WhoStartFirst, bool DisplayPCShips, int sea_size, int numCarrier, int numBattleship, int numSubmarine, int numDestroyer)
{

	Carrier PlayerCarrier[5];
	Battleship PlayerBattleship[5];
	Submarine PlayerSubmarine[5];
	Destroyer PlayerDestroyer[5];

	Carrier PCCarrier[5];
	Battleship PCBattleship[5];
	Submarine PCSubmarine[5];
	Destroyer PCDestroyer[5];


	system("cls");
	game_arrangement_player(player_sea, sea_size, numCarrier, numBattleship, numSubmarine, numDestroyer, PlayerCarrier, PlayerBattleship, PlayerSubmarine, PlayerDestroyer); // Player place ship first //call
	game_arrangement_PC(PC_sea, sea_size, numCarrier, numBattleship, numSubmarine, numDestroyer, PCCarrier, PCBattleship, PCSubmarine, PCDestroyer); //PC arrange ship randomly in this function //call

	game_battlestage(player_sea, PC_sea, WhoStartFirst, DisplayPCShips, sea_size, numCarrier, numBattleship, numSubmarine, numDestroyer, PlayerCarrier, PlayerBattleship, PlayerSubmarine, PlayerDestroyer, PCCarrier, PCBattleship, PCSubmarine, PCDestroyer); //call
}

void game_arrangement_player(char player_sea[][10], int sea_size, int numCarrier, int numBattleship, int numSubmarine, int numDestroyer, Carrier PlayerCarrier[5], Battleship PlayerBattleship[5], Submarine PlayerSubmarine[5], Destroyer PlayerDestroyer[5])
{

	char direction, y; //  the ship is put vertically or horizontally, x is the coordinate of x-axis, y is the coordinate of y-axis
	int x;

	//Arrangement of carrier
	for (int i = 1; i <= numCarrier; i++) {
		game_printSea_player(sea_size);
		game_arrangement_instruction(sea_size);
		cout << "\n(" << i << " out of " << numCarrier << ") Please input the direction of the carrier: ";
		cin >> direction;
		cout << "Please input the coordinate of the carrier  (size of " << sizeCarrier << ") : ";
		cin >> y >> x;

		if ((direction == 'Q') && (y == 'u') && (x = 'i'))
		{
			game_quit();
			i--;
			continue;
		}

		if (direction == 'H') {  //  ship place towards x-axis/horizontally
			while ((int)y < 65 || (int)y > 64 + sea_size || x < 0 || x > sea_size - 1 || x >= sea_size - 4 || player_sea[(int)y - 65][x] == 'O' || player_sea[(int)y - 65][x + 1] == 'O' || player_sea[(int)y - 65][x + 2] == 'O' || player_sea[(int)y - 65][x + 3] == 'O' || player_sea[(int)y - 65][x + 4] == 'O') {  // Prevent wrong input
				cout << "Wrong input! Try again." << endl;

				cin.clear();
				cin.ignore(10000, '\n');

				system("pause");
				system("cls");

				game_printSea_player(sea_size);
				game_arrangement_instruction(sea_size);
				cout << "\n(" << i << " out of " << numCarrier << ") Please input the direction of the carrier: ";
				cin >> direction;
				cout << "Please input the coordinate of the carrier  (size of " << sizeCarrier << ") : ";
				cin >> y >> x;
			}
			for (int i = 0; i < sizeCarrier; i++) {
				player_sea[(int)y - 65][x + i] = 'O';
			}
		}
		else if (direction == 'V') { // ship place towards y-axis/vertically
			while ((int)y < 65 || (int)y > 64 + sea_size || x < 0 || x > sea_size - 1 || y >= (char)(sea_size + 61) || player_sea[(int)y - 65][x] == 'O' || player_sea[(int)y - 64][x] == 'O' || player_sea[(int)y - 63][x] == 'O' || player_sea[(int)y - 62][x] == 'O' || player_sea[(int)y - 61][x] == 'O') { // Prevent wrong input
				cout << "Wrong input! Try again." << endl;

				cin.clear();
				cin.ignore(10000, '\n');

				system("pause");
				system("cls");

				game_printSea_player(sea_size);
				game_arrangement_instruction(sea_size);
				cout << "\n(" << i << " out of " << numCarrier << ") Please input the direction of the carrier: ";
				cin >> direction;
				cout << "Please input the coordinate of the carrier  (size of " << sizeCarrier << ") : ";
				cin >> y >> x;
			}
			for (int i = 0; i < sizeCarrier; i++) {
				player_sea[(int)y - 65 + i][x] = 'O';
			}
		}
		if (direction == 'H' || direction == 'V')
		{
			PlayerCarrier[i - 1].arrangement(1, direction, y, x);
		}
		else // Neither X nor Y
		{
			cout << "Wrong input! Try again." << endl;

			cin.clear();
			cin.ignore(10000, '\n');

			system("pause");
			system("cls");
			i--;
			continue;
		}

		for (int i = numCarrier; i <= 4; i++) // For carrier not to be used
			PlayerCarrier[i].arrangement(0, '0', '0', -1);

		cout << endl;
		system("cls");
	}

	// Arrangement of battleship
	for (int i = 1; i <= numBattleship; i++) {
		game_printSea_player(sea_size);
		game_arrangement_instruction(sea_size);
		cout << "\n(" << i << " out of " << numBattleship << ") Please input the direction of the battleship : ";
		cin >> direction;
		cout << "Please input the coordinate of the battleship (size of " << sizeBattleship << ") : ";
		cin >> y >> x;

		if ((direction == 'Q') && (y == 'u') && (x = 'i'))
		{
			game_quit();
			i--;
			continue;
		}

		if (direction == 'H') {  //  ship place towards x-axis/horizontally
			while ((int)y < 65 || (int)y > 64 + sea_size || x < 0 || x > sea_size - 1 || x >= sea_size - 3 || player_sea[(int)y - 65][x] == 'O' || player_sea[(int)y - 65][x + 1] == 'O' || player_sea[(int)y - 65][x + 2] == 'O' || player_sea[(int)y - 65][x + 3] == 'O') {  // Prevent wrong input
				cout << "Wrong input! Try again." << endl;

				cin.clear();
				cin.ignore(10000, '\n');

				system("pause");
				system("cls");

				game_printSea_player(sea_size);
				game_arrangement_instruction(sea_size);
				cout << "\n(" << i << " out of " << numBattleship << ") Please input the direction of the battleship : ";
				cin >> direction;
				cout << "Please input the coordinate of the battleship (size of " << sizeBattleship << ") : ";
				cin >> y >> x;
			}
			for (int i = 0; i < sizeBattleship; i++) {
				player_sea[(int)y - 65][x + i] = 'O';
			}
		}
		else if (direction == 'V') { //  ship place towards y-axis/vertically
			while ((int)y < 65 || (int)y > 64 + sea_size || x < 0 || x > sea_size - 1 || y >= (char)(sea_size + 62) || player_sea[(int)y - 65][x] == 'O' || player_sea[(int)y - 64][x] == 'O' || player_sea[(int)y - 63][x] == 'O' || player_sea[(int)y - 62][x] == 'O') { // Prevent wrong input
				cout << "Wrong input! Try again." << endl;

				cin.clear();
				cin.ignore(10000, '\n');

				system("pause");
				system("cls");

				game_printSea_player(sea_size);
				game_arrangement_instruction(sea_size);
				cout << "\n(" << i << " out of " << numBattleship << ") Please input the direction of the battleship : ";
				cin >> direction;
				cout << "Please input the coordinate of the battleship (size of " << sizeBattleship << ") : ";
				cin >> y >> x;
			}
			for (int i = 0; i < sizeBattleship; i++) {
				player_sea[(int)y - 65 + i][x] = 'O';
			}
		}
		if (direction == 'H' || direction == 'V')
		{
			PlayerBattleship[i - 1].arrangement(1, direction, y, x);
		}
		else
		{
			cout << "Wrong input! Try again." << endl;

			cin.clear();
			cin.ignore(10000, '\n');

			system("pause");
			system("cls");
			i--;
			continue;
		}

		for (int i = numBattleship; i <= 4; i++) // For battleship not to be used
			PlayerBattleship[i].arrangement(0, '0', '0', -1);

		cout << endl;
		system("cls");
	}

	// Arrangement of submarine
	for (int i = 1; i <= numSubmarine; i++) {
		game_printSea_player(sea_size);
		game_arrangement_instruction(sea_size);
		cout << "\n(" << i << " out of " << numSubmarine << ") Please input the direction of the submarine: ";
		cin >> direction;
		cout << "Please input the coordinate of the submarine  (size of " << sizeSubmarine << ") : ";
		cin >> y >> x;

		if ((direction == 'Q') && (y == 'u') && (x = 'i'))
		{
			game_quit();
			i--;
			continue;
		}

		if (direction == 'H') {  //  ship place towards x-axis/horizontally
			while ((int)y < 65 || (int)y > 64 + sea_size || x < 0 || x > sea_size - 1 || x >= sea_size - 2 || player_sea[(int)y - 65][x] == 'O' || player_sea[(int)y - 65][x + 1] == 'O' || player_sea[(int)y - 65][x + 2] == 'O') {  // Prevent wrong input
				cout << "Wrong input! Try again." << endl;

				cin.clear();
				cin.ignore(10000, '\n');

				system("pause");
				system("cls");

				game_printSea_player(sea_size);
				game_arrangement_instruction(sea_size);
				cout << "\n(" << i << " out of " << numSubmarine << ") Please input the direction of the submarine: ";
				cin >> direction;
				cout << "Please input the coordinate of the submarine  (size of " << sizeSubmarine << ") : ";
				cin >> y >> x;
			}
			for (int i = 0; i < sizeSubmarine; i++) {
				player_sea[(int)y - 65][x + i] = 'O';
			}
		}
		else if (direction == 'V') { // ship place towards y-axis/vertically
			while ((int)y < 65 || (int)y > 64 + sea_size || x < 0 || x > sea_size - 1 || y >= (char)(sea_size + 63) || player_sea[(int)y - 65][x] == 'O' || player_sea[(int)y - 64][x] == 'O' || player_sea[(int)y - 63][x] == 'O') { // Prevent wrong input
				cout << "Wrong input! Try again." << endl;

				cin.clear();
				cin.ignore(10000, '\n');

				system("pause");
				system("cls");

				game_printSea_player(sea_size);
				game_arrangement_instruction(sea_size);
				cout << "\n(" << i << " out of " << numSubmarine << ") Please input the direction of the submarine: ";
				cin >> direction;
				cout << "Please input the coordinate of the submarine  (size of " << sizeSubmarine << ") : ";
				cin >> y >> x;
			}
			for (int i = 0; i < sizeSubmarine; i++) {
				player_sea[(int)y - 65 + i][x] = 'O';
			}
		}
		if (direction == 'H' || direction == 'V')
		{
			PlayerSubmarine[i - 1].arrangement(1, direction, y, x);
		}
		else // Neither X nor Y
		{
			cout << "Wrong input! Try again." << endl;

			cin.clear();
			cin.ignore(10000, '\n');

			system("pause");
			system("cls");
			i--;
			continue;
		}

		for (int i = numSubmarine; i <= 4; i++) // For submarine not to be used
			PlayerSubmarine[i].arrangement(0, '0', '0', -1);

		cout << endl;
		system("cls");
	}

	// Arrangement of destroyer
	for (int i = 1; i <= numDestroyer; i++) {
		game_printSea_player(sea_size);
		game_arrangement_instruction(sea_size);
		cout << "\n(" << i << " out of " << numDestroyer << ") Please input the direction of the destroyer: ";
		cin >> direction;
		cout << "Please input the coordinate of the destroyer (size of " << sizeDestroyer << ") : ";
		cin >> y >> x;

		if ((direction == 'Q') && (y == 'u') && (x = 'i'))
		{
			game_quit(); // Quit the game
			i--;
			continue;
		}

		if (direction == 'H') {  //  ship place towards x-axis/horizontally
			while ((int)y < 65 || (int)y > 64 + sea_size || x < 0 || x > sea_size - 1 || x >= sea_size - 1 || player_sea[(int)y - 65][x] == 'O' || player_sea[(int)y - 65][x + 1] == 'O') {  // Prevent wrong input
				cout << "Wrong input! Try again." << endl;

				cin.clear();
				cin.ignore(10000, '\n');

				system("pause");
				system("cls");

				game_printSea_player(sea_size);
				game_arrangement_instruction(sea_size);
				cout << "\n(" << i << " out of " << numDestroyer << ") Please input the direction of the destroyer: ";
				cin >> direction;
				cout << "Please input the coordinate of the destroyer (size of " << sizeDestroyer << ") : ";
				cin >> y >> x;
			}
			for (int i = 0; i < sizeDestroyer; i++) {
				player_sea[(int)y - 65][x + i] = 'O';
			}
		}
		else if (direction == 'V') { //  ship place towards y-axis/vertically
			while ((int)y < 65 || (int)y > 64 + sea_size || x < 0 || x > sea_size - 1 || y >= (char)(sea_size + 64) || player_sea[(int)y - 65][x] == 'O' || player_sea[(int)y - 64][x] == 'O') { // Prevent wrong input
				cout << "Wrong input! Try again." << endl;

				cin.clear();
				cin.ignore(10000, '\n');

				system("pause");
				system("cls");

				game_printSea_player(sea_size);
				game_arrangement_instruction(sea_size);
				cout << "\n(" << i << " out of " << numDestroyer << ") Please input the direction of the destroyer: ";
				cin >> direction;
				cout << "Please input the coordinate of the destroyer (size of " << sizeDestroyer << ") : ";
				cin >> y >> x;
			}
			for (int i = 0; i < sizeDestroyer; i++) {
				player_sea[(int)y - 65 + i][x] = 'O';
			}
		}
		if (direction == 'H' || direction == 'V')
		{
			PlayerDestroyer[i - 1].arrangement(1, direction, y, x);
		}
		else // Neither X nor Y
		{
			cout << "Wrong input! Try again." << endl;

			cin.clear();
			cin.ignore(10000, '\n');

			system("pause");
			system("cls");
			i--;
			continue;
		}

		for (int i = numDestroyer; i <= 4; i++) // For destroyer not to be use
			PlayerDestroyer[i].arrangement(0, '0', '0', -1);

		cout << endl;
		system("cls");
	}
	system("cls");
}

void game_arrangement_PC(char PC_sea[][10], int sea_size, int numCarrier, int numBattleship, int numSubmarine, int numDestroyer, Carrier PCCarrier[5], Battleship PCBattleship[5], Submarine PCSubmarine[5], Destroyer PCDestroyer[5])
{

	int numDirection = 0, numY = 0; // for random number
	char direction = '0', y = '0'; //  the ship is put vertically or horizontally, x is the coordinate of x-axis, y is the coordinate of y-axis
	int x = 0;

	srand((unsigned int)time(0));

	//Arrangement of carrier
	for (int i = 1; i <= numCarrier; i++) {

		numDirection = rand() % 2;
		switch (numDirection)
		{
		case 0: direction = 'H'; break;		case 1: direction = 'V'; break;
		}

		numY = rand() % sea_size;
		switch (numY)
		{
		case 0: y = 'A'; break;			case 1: y = 'B'; break;			case 2: y = 'C'; break;			case 3: y = 'D'; break;			case 4: y = 'E'; break;
		case 5: y = 'F'; break;			case 6: y = 'G'; break;			case 7: y = 'H'; break;			case 8: y = 'I'; break;			case 9: y = 'J'; break;
		}

		x = rand() % sea_size;

		if (direction == 'H') {  //  ship place towards x-axis/horizontally
			if (x >= sea_size - 4 || PC_sea[(int)y - 65][x] == 'O' || PC_sea[(int)y - 65][x + 1] == 'O' || PC_sea[(int)y - 65][x + 2] == 'O' || PC_sea[(int)y - 65][x + 3] == 'O' || PC_sea[(int)y - 65][x + 4] == 'O') {  // Prevent wrong input
				i--;
				continue;
			}
			for (int i = 0; i < sizeCarrier; i++) {
				PC_sea[(int)y - 65][x + i] = 'O';
			}
		}
		else if (direction == 'V') { //  ship place towards y-axis/vertically
			if (y >= (char)(sea_size + 61) || PC_sea[(int)y - 65][x] == 'O' || PC_sea[(int)y - 64][x] == 'O' || PC_sea[(int)y - 63][x] == 'O' || PC_sea[(int)y - 62][x] == 'O' || PC_sea[(int)y - 61][x] == 'O') { // Prevent wrong input
				i--;
				continue;
			}
			for (int i = 0; i < sizeCarrier; i++) {
				PC_sea[(int)y - 65 + i][x] = 'O';
			}
		}
		PCCarrier[i - 1].arrangement(1, direction, y, x);
	}
	for (int i = numCarrier; i <= 4; i++) // For carrier not to be used
		PCCarrier[i].arrangement(0, '0', '0', -1);

	//Arrangement of battleship
	for (int i = 1; i <= numBattleship; i++) {
		numDirection = rand() % 2;
		switch (numDirection)
		{
		case 0: direction = 'H'; break;		case 1: direction = 'V'; break;
		}

		numY = rand() % sea_size;
		switch (numY)
		{
		case 0: y = 'A'; break;			case 1: y = 'B'; break;			case 2: y = 'C'; break;			case 3: y = 'D'; break;			case 4: y = 'E'; break;
		case 5: y = 'F'; break;			case 6: y = 'G'; break;			case 7: y = 'H'; break;			case 8: y = 'I'; break;			case 9: y = 'J'; break;
		}

		x = rand() % sea_size;

		if (direction == 'H') {  //  ship place towards x-axis/horizontally
			if (x >= sea_size - 3 || PC_sea[(int)y - 65][x] == 'O' || PC_sea[(int)y - 65][x + 1] == 'O' || PC_sea[(int)y - 65][x + 2] == 'O' || PC_sea[(int)y - 65][x + 3] == 'O') {  // Prevent wrong input
				i--;
				continue;
			}
			for (int i = 0; i < sizeBattleship; i++) {
				PC_sea[(int)y - 65][x + i] = 'O';
			}
		}
		else if (direction == 'V') { //  ship place towards y-axis/vertically
			if (y >= (char)(sea_size + 62) || PC_sea[(int)y - 65][x] == 'O' || PC_sea[(int)y - 64][x] == 'O' || PC_sea[(int)y - 63][x] == 'O' || PC_sea[(int)y - 62][x] == 'O') { // Prevent wrong input
				i--;
				continue;
			}
			for (int i = 0; i < sizeBattleship; i++) {
				PC_sea[(int)y - 65 + i][x] = 'O';
			}
		}
		PCBattleship[i - 1].arrangement(1, direction, y, x);
	}
	for (int i = numBattleship; i <= 4; i++) // For battleship not to useed
		PCBattleship[i].arrangement(0, '0', '0', -1);

	//Arrangement of submarine
	for (int i = 1; i <= numSubmarine; i++) {
		numDirection = rand() % 2;
		switch (numDirection)
		{
		case 0: direction = 'H'; break;		case 1: direction = 'V'; break;
		}

		numY = rand() % sea_size;
		switch (numY)
		{
		case 0: y = 'A'; break;			case 1: y = 'B'; break;			case 2: y = 'C'; break;			case 3: y = 'D'; break;			case 4: y = 'E'; break;
		case 5: y = 'F'; break;			case 6: y = 'G'; break;			case 7: y = 'H'; break;			case 8: y = 'I'; break;			case 9: y = 'J'; break;
		}

		x = rand() % sea_size;

		if (direction == 'H') {  // ship place towards x-axis/horizontally
			if (x >= sea_size - 2 || PC_sea[(int)y - 65][x] == 'O' || PC_sea[(int)y - 65][x + 1] == 'O' || PC_sea[(int)y - 65][x + 2] == 'O') {  // Prevent wrong input
				i--;
				continue;
			}
			for (int i = 0; i < sizeSubmarine; i++) {
				PC_sea[(int)y - 65][x + i] = 'O';
			}
		}
		else if (direction == 'V') { // ship place towards y-axis/vertically
			if (y >= (char)(sea_size + 63) || PC_sea[(int)y - 65][x] == 'O' || PC_sea[(int)y - 64][x] == 'O' || PC_sea[(int)y - 63][x] == 'O') { // Prevent wrong input
				i--;
				continue;
			}
			for (int i = 0; i < sizeSubmarine; i++) {
				PC_sea[(int)y - 65 + i][x] = 'O';
			}
		}
		PCSubmarine[i - 1].arrangement(1, direction, y, x);
	}
	for (int i = numSubmarine; i <= 4; i++) // For submarine not to be used
		PCSubmarine[i].arrangement(0, '0', '0', -1);

	//Arrangement of destroyer
	for (int i = 1; i <= numDestroyer; i++) {
		numDirection = rand() % 2;
		switch (numDirection)
		{
		case 0: direction = 'H'; break;		case 1: direction = 'V'; break;
		}

		numY = rand() % sea_size;
		switch (numY)
		{
		case 0: y = 'A'; break;			case 1: y = 'B'; break;			case 2: y = 'C'; break;			case 3: y = 'D'; break;			case 4: y = 'E'; break;
		case 5: y = 'F'; break;			case 6: y = 'G'; break;			case 7: y = 'H'; break;			case 8: y = 'I'; break;			case 9: y = 'J'; break;
		}

		x = rand() % sea_size;
		if (direction == 'H') {  // ship place towards x-axis/horizontally
			if (x >= sea_size - 1 || PC_sea[(int)y - 65][x] == 'O' || PC_sea[(int)y - 65][x + 1] == 'O') {  // Prevent wrong input
				i--;
				continue;
			}
			for (int i = 0; i < sizeDestroyer; i++) {
				PC_sea[(int)y - 65][x + i] = 'O';
			}
		}
		else if (direction == 'V') { // ship place towards y-axis/vertically
			if (y >= (char)(sea_size + 64) || PC_sea[(int)y - 65][x] == 'O' || PC_sea[(int)y - 64][x] == 'O') { // Prevent wrong input
				i--;
				continue;
			}
			for (int i = 0; i < sizeDestroyer; i++) {
				PC_sea[(int)y - 65 + i][x] = 'O';
			}
		}
		PCDestroyer[i - 1].arrangement(1, direction, y, x);
	}
	for (int i = numDestroyer; i <= 4; i++) // For destroyer not to be used
		PCDestroyer[i].arrangement(0, '0', '0', -1);
}

void game_arrangement_instruction(int sea_size)
{
	cout << "\nDirection: H(Horizontal) / V(Vertical)" << endl;
	cout << "Row: A ~ " << (char)(sea_size + 64) << endl;
	cout << "Column: 0 ~ " << sea_size - 1 << endl;
	cout << "Command \"Quit\" to leave . " << endl;
}

void game_printSea_player(int sea_size)
{
	int count = 0;
	int z = 65;

	cout << "\n";
	for (int i = 0; i < sea_size; i++) {
		if (i == 0)
			cout << setw(5) << i;
		else
			cout << setw(2) << i;
	}
	cout << endl;

	do {
		for (int i = 0; i < sea_size * 2 + 3; i++) {
			if (i == 0)
				cout << setw(3) << "+";
			else if (i == sea_size * 2 + 2)
				cout << "+";
			else
				cout << "-";
		}
		cout << endl;

		if (count == 1) break;

		for (int row = 0; row < sea_size; row++) {
			cout << (char)z << setw(2) << "|";
			z++;

			for (int col = 0; col < sea_size; col++) {
				cout << " " << player_sea[row][col];
			}

			cout << " |" << endl;
		}
		count++;
	} while (count < 2);
}

void game_printSea_PC(int sea_size, bool DisplayPCShips)
{
	int count = 0;
	int z = 65;

	cout << "\n";
	for (int i = 0; i < sea_size; i++) {
		if (i == 0)
			cout << setw(5) << i;
		else
			cout << setw(2) << i;
	}
	cout << endl;

	do {
		for (int i = 0; i < sea_size * 2 + 3; i++) {
			if (i == 0)
				cout << setw(3) << "+";
			else if (i == sea_size * 2 + 2)
				cout << "+";
			else
				cout << "-";
		}
		cout << endl;

		if (count == 1) break;

		for (int row = 0; row < sea_size; row++) {
			cout << (char)z << setw(2) << "|";
			z++;

			for (int col = 0; col < sea_size; col++) {
				if (DisplayPCShips == 0)
				{
					if (PC_sea[row][col] == 'O')
					{
						cout << "  ";
					}
					else
					{
						cout << " " << PC_sea[row][col];
					}
				}
				else
				{
					cout << " " << PC_sea[row][col];
				}
			}
			cout << " |" << endl;
		}
		count++;
	} while (count < 2);
}

void game_battlestage(char player_sea[][10], char PC_sea[][10], bool WhoStartFirst, bool DisplayPCShips, int sea_size, int numCarrier, int numBattleship, int numSubmarine, int numDestroyer, Carrier PlayerCarrier[5], Battleship PlayerBattleship[5], Submarine PlayerSubmarine[5], Destroyer PlayerDestroyer[5], Carrier PCCarrier[5], Battleship PCBattleship[5], Submarine PCSubmarine[5], Destroyer PCDestroyer[5])
{
	bool FirstTurn = 0;
	char attack_Y = '0';
	int attack_X = 0;
	int sumAttackStatus = 0;

	int attack_status = 0;
	bool flag_destroyed = 0;
	bool PC_sea_attacked[10][10] = { 0 };
	bool player_sea_attacked[10][10] = { 0 };

	//Global variables
	int numCarrier_player = numCarrier;
	int numBattleship_player = numBattleship;
	int numSubmarine_player = numSubmarine;
	int numDestroyer_player = numDestroyer;

	int numCarrier_PC = numCarrier;
	int numBattleship_PC = numBattleship;
	int numSubmarine_PC = numSubmarine;
	int numDestroyer_PC = numDestroyer;

	//for PC Intelligence 
	int numUnknownPro = 0, numLowPro = 0, numMedPro = 0, numHighPro = 0, numVHighPro = 0; // number of all probability 
	int seaPCI[10][10] = { 0 }; // 2-dimensional [row][column] array for storing the probability

	system("cls");

	while (1)
	{
		//Player turn 
		if (WhoStartFirst == 1 && FirstTurn == 0) // PC starts first
		{
			FirstTurn = 1;
			goto PC_FIRST;
		}
		else
		{

		QUIT_BUT_N:
			game_printSea_battlestage(sea_size, DisplayPCShips);
			cout << "Row: A ~ " << (char)(sea_size + 64) << "    Column: 0 ~ " << sea_size - 1 << endl;
			cout << "Command \"Quit\" to leave ." << "\n\n";
			cout << "Please input the coordinate which you want to attack: ";
			cin >> attack_Y >> attack_X;

			if (attack_Y == 'Q')
			{
				game_quit();
				cin.clear();
				cin.ignore(10000, '\n');
				goto QUIT_BUT_N;
			}

			while ((attack_X >= sea_size || (int)attack_Y >= sea_size + 65 || attack_X < 0 || (int)attack_Y < 65))
			{  // Prevent wrong input 
				if (attack_Y == 'Q')
				{
					game_quit();
					cin.clear();
					cin.ignore(10000, '\n');
					goto QUIT_BUT_N;
				}

				cout << "Invaild vaule!~ Try input again." << endl;

				cin.clear();
				cin.ignore(10000, '\n');

				system("pause");
				system("cls");

				game_printSea_battlestage(sea_size, DisplayPCShips);
				cout << "Row: A ~ " << (char)(sea_size + 64) << "    " << "Column: 0 ~ " << sea_size - 1 << endl;
				cout << "Please input the coordinate which you want to attack: ";
				cin >> attack_Y >> attack_X;
			}

			cout << "The player decides to attack " << attack_Y << attack_X << ". ";

			//Check fire status 
			for (int i = 0; i < 5; i++)
			{
				attack_status += PCCarrier[i].attack_check(0, attack_Y, attack_X, player_sea, PC_sea, sea_size, PC_sea_attacked, player_sea_attacked, seaPCI); // 0 --> Player did that attack
			}
			if (attack_status == 3)
			{
				cout << "A carrier is destroyed!" << endl;
				flag_destroyed = 1;
				attack_status = 0;
				numCarrier_PC--;
			}

			for (int i = 0; i < 5; i++)
			{
				attack_status += PCBattleship[i].attack_check(0, attack_Y, attack_X, player_sea, PC_sea, sea_size, PC_sea_attacked, player_sea_attacked, seaPCI); // 0 --> Player did that attack
			}
			if (attack_status == 3)
			{
				cout << "A battleship is destroyed!" << endl;
				flag_destroyed = 1;
				attack_status = 0;
				numBattleship_PC--;
			}

			for (int i = 0; i < 5; i++)
			{
				attack_status += PCSubmarine[i].attack_check(0, attack_Y, attack_X, player_sea, PC_sea, sea_size, PC_sea_attacked, player_sea_attacked, seaPCI); // 0 --> Player did that attack
			}
			if (attack_status == 3)
			{
				cout << "A submarine is destroyed!" << endl;
				flag_destroyed = 1;
				attack_status = 0;
				numSubmarine_PC--;
			}

			for (int i = 0; i < 5; i++)
			{
				attack_status += PCDestroyer[i].attack_check(0, attack_Y, attack_X, player_sea, PC_sea, sea_size, PC_sea_attacked, player_sea_attacked, seaPCI); // 0 --> Player did that attack
			}
			if (attack_status == 3)
			{
				cout << "A destroyer is destroyed!" << endl;
				flag_destroyed = 1;
				attack_status = 0;
				numDestroyer_PC--;
			}

			if (flag_destroyed != 1)
			{
				switch (attack_status)
				{
				case 0: cout << "It is a miss!" << endl; break;					case 1: cout << "The grid has been hit before. Nothing happens." << endl; break;
				case 2: cout << "Part of a ship is destoryed!" << endl; break;
				}
			}

			cout << endl;

			flag_destroyed = 0;
			attack_status = 0;


			//Check win 
			if (numDestroyer_PC == 0 && numSubmarine_PC == 0 && numBattleship_PC == 0 && numCarrier_PC == 0)
			{
				system("pause");
				system("cls");
				game_printSea_battlestage(sea_size, DisplayPCShips);
				cout << "\n\n";
				cout << "Congradulation! All enemy's ships have been destoryed !~ Player Won!~" << endl;
				cout << "Press any key to return to the main menu." << "\n\n";
				goto GAME_END;
			}


			system("pause");
			system("cls");
		}


		//PC turn 
	PC_FIRST:
		game_printSea_battlestage(sea_size, DisplayPCShips);
		PCI_decide_attack(sea_size, seaPCI, numUnknownPro, numLowPro, numMedPro, numHighPro, numVHighPro); //calculate the probability
		PCI_attack_phrase(sea_size, seaPCI, numUnknownPro, numLowPro, numMedPro, numHighPro, numVHighPro, attack_Y, attack_X); //decide which to hit and also adjusting probability accordingly

																															   //Check fire status starts here
		for (int i = 0; i < 5; i++)
		{
			attack_status += PlayerCarrier[i].attack_check(1, attack_Y, attack_X, player_sea, PC_sea, sea_size, PC_sea_attacked, player_sea_attacked, seaPCI); // 1 --> PC did that attack
		}
		if (attack_status == 3)
		{
			cout << "A carrier is destroyed!" << endl;
			flag_destroyed = 1;
			attack_status = 0;
			numCarrier_player--;
		}

		for (int i = 0; i < 5; i++)
		{
			attack_status += PlayerBattleship[i].attack_check(1, attack_Y, attack_X, player_sea, PC_sea, sea_size, PC_sea_attacked, player_sea_attacked, seaPCI); // 1 --> PC did that attack
		}
		if (attack_status == 3)
		{
			cout << "A battleship is destroyed!" << endl;
			flag_destroyed = 1;
			attack_status = 0;
			numBattleship_player--;
		}

		for (int i = 0; i < 5; i++)
		{
			attack_status += PlayerSubmarine[i].attack_check(1, attack_Y, attack_X, player_sea, PC_sea, sea_size, PC_sea_attacked, player_sea_attacked, seaPCI); // 1 --> PC did that attack
		}
		if (attack_status == 3)
		{
			cout << "A submarine is destroyed!" << endl;
			flag_destroyed = 1;
			attack_status = 0;
			numSubmarine_player--;
		}

		for (int i = 0; i < 5; i++)
		{
			attack_status += PlayerDestroyer[i].attack_check(1, attack_Y, attack_X, player_sea, PC_sea, sea_size, PC_sea_attacked, player_sea_attacked, seaPCI); // 1 --> PC did that attack
		}
		if (attack_status == 3)
		{
			cout << "A destroyer is destroyed!" << endl;
			flag_destroyed = 1;
			attack_status = 0;
			numDestroyer_player--;
		}

		if (flag_destroyed != 1)
		{
			switch (attack_status)
			{
			case 0: cout << "It is a miss!" << endl; break;
			case 1: cout << "The grid has been hit before. Nothing happens." << endl; break;
			case 2: cout << "Part of a ship is destoryed!" << endl;
				//change of probability inside seaPCI
				//ignore grid that is out of boundary
			case 3:	int i = (int)attack_Y - 65;
				int j = attack_X;
				if (i < sea_size - 1)
					seaPCI[i + 1][j] += 25;
				if (i != 0)
					seaPCI[i - 1][j] += 25;
				if (j < sea_size - 1)
					seaPCI[i][j + 1] += 25;
				if (j != 0)
					seaPCI[i][j - 1] += 25;
				break;
			}
		}

		cout << endl;

		flag_destroyed = 0;
		attack_status = 0;


		//Check win 
		if (numDestroyer_player == 0 && numSubmarine_player == 0 && numBattleship_player == 0 && numCarrier_player == 0)
		{
			system("pause");
			system("cls");
			game_printSea_battlestage(sea_size, DisplayPCShips);
			cout << "\n\n";
			cout << "All ship of Player has been destroyed . PC won!!~" << endl;
			cout << "Press any key to return to the main menu." << "\n\n";
			goto GAME_END;
		}

		system("pause");
		system("cls");
	}
GAME_END:
	//Reset sea arrangement
	for (int i = 0; i < sea_size; i++)
	{
		for (int j = 0; j < sea_size; j++)
		{
			player_sea[i][j] = ' ';
			PC_sea[i][j] = ' ';
		}
	}
	system("pause");
	system("cls");
}

void game_quit()
{
	char ans;

	cin.clear();
	cin.ignore(10000, '\n');

	cout << "\n";
	cout << "Are you sure to leave?" << endl;
	cout << "If yes, please input 'y'/'Y'." << endl;
	cout << "If no, please input 'n'/'N'." << endl;
	cin >> ans;

	if (ans == 'y' || ans == 'Y')
	{
		cout << "Good Bye!" << endl;
		exit(1);
	}
	else if (ans == 'n' || ans == 'N')
	{
		system("cls");
		cin.clear();
		cin.ignore(10000, '\n');
	}
	else
	{
		cout << "Wrong input! Please try again.";
		game_quit();
	}
}

void PCI_decide_attack(int size, int seaPCI[][10], int &numUnknownPro, int &numLowPro, int &numMedPro, int &numHighPro, int &numVHighPro)
{
	int numPro = 0; // for sotring number of that probability

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i >= size || j >= size)
				seaPCI[i][j] = -1;
		}
	}

	for (int i = 0; i <= 100; i += 25) // 0~100 (25 increament)
	{
		numPro = PCI_calculate_Pro(size, i, seaPCI);
		switch (i)
		{
		case 0: numUnknownPro = numPro; break;		case 25: numLowPro = numPro; break;		case 50:numMedPro = numPro; break;
		case 75:numHighPro = numPro; break;			case 100:numVHighPro = numPro; break;
		}
	}
}

int PCI_calculate_Pro(int size, int pro, int seaPCI[][10])
{
	int numPro = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (seaPCI[i][j] == pro) // when the probability stored in the array equals to the target probability
			{
				numPro++;
			}
		}
	}
	return numPro; // return the number of grid that matches that probability
}

void PCI_attack_phrase(int size, int seaPCI[][10], int numUnknownPro, int numLowPro, int numMedPro, int numHighPro, int numVHighPro, char &attack_Y, int &attack_X)
{
	// cout << "numVHighPro: " << numVHighPro << " numHighPro: " << numHighPro << " numMedPro: " << numMedPro << " numLowPro: " << numLowPro << " numUnknownPro: " << numUnknownPro << "." << endl;
	if (numVHighPro > 0)
		PCI_fire(size, 100, numVHighPro, seaPCI, attack_Y, attack_X); // PC will attack grid that has the highest probability first
	else if (numHighPro > 0)
		PCI_fire(size, 75, numHighPro, seaPCI, attack_Y, attack_X);
	else if (numMedPro > 0)
		PCI_fire(size, 50, numMedPro, seaPCI, attack_Y, attack_X);
	else if (numLowPro > 0)
		PCI_fire(size, 25, numLowPro, seaPCI, attack_Y, attack_X);
	else
		PCI_fire(size, 0, numUnknownPro, seaPCI, attack_Y, attack_X);
}

void PCI_fire(int size, int pro, int numPro, int seaPCI[][10], char &attack_Y, int &attack_X)
{
	int attack_position = 0;
	int orderPro = 0;

	srand((unsigned int)time(0)); // change seed of random
	attack_position = rand() % numPro + 1; // determine the position of attack randomly, pick one number from 1 ~ numPro

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (seaPCI[i][j] == pro)
			{
				orderPro++;
				if (attack_position == orderPro) //Search the attack_position(th) grid
				{
					int attack_Y_to_int = 0;
					attack_Y = (char)(i + 65);
					attack_X = j;

					cout << "The PC decides to attack " << attack_Y << attack_X << ". ";
					switch (attack_Y)
					{
					case 'A': attack_Y_to_int = 0; break;  case 'B': attack_Y_to_int = 1; break;  case 'C': attack_Y_to_int = 2; break;	case 'D': attack_Y_to_int = 3; break;
					case 'E': attack_Y_to_int = 4; break;  case 'F': attack_Y_to_int = 5; break;  case 'G': attack_Y_to_int = 6; break;  case 'H': attack_Y_to_int = 7; break;
					case 'I': attack_Y_to_int = 8; break;  case 'J': attack_Y_to_int = 9; break;
					}

					seaPCI[attack_Y_to_int][attack_X] = -1; //reset that attack grid in order to indicate that it has been attacked by PC


					goto FOUND;
				}
			}
		}
	}
FOUND:
	;
}

void game_printSea_battlestage(int sea_size, bool DisplayPCShips)
{
	game_printSea_PC(sea_size, DisplayPCShips);
	cout << setw(sea_size) << "" << "PC's sea" << "\n\n";

	game_printSea_player(sea_size);
	cout << setw(sea_size - 2) << "" << "Player's sea" << "\n\n";
}

void setting(bool &WhoStartFirst, bool &DisplayPCShips, int &sea_size, int &numCarrier, int &numBattleship, int &numSubmarine, int &numDestroyer)
{
	system("cls");
	int option;

	cout << "\n";

	cout << "*** Settings Menu ***" << endl;
	cout << "[1] PC Game Demo" << endl;
	cout << "[2] Timer Bomb Mode" << endl;
	cout << "[3] Change Board Size" << endl;
	cout << "[4] Change Bomb Timer" << endl;
	cout << "[5] Return to game menu" << endl;
	cout << "*********************" << endl;
	cout << "Option (1 - 5): ";

	cin >> option;
	switch (option)
	{
	case 1: whoFirst(WhoStartFirst); break;
	case 2: displayPCships(DisplayPCShips); break;
	case 3: boardSize(sea_size, numCarrier, numBattleship, numSubmarine, numDestroyer); break;
	case 4: numberOFships(sea_size, numCarrier, numBattleship, numSubmarine, numDestroyer); break;
	case 5: system("cls"); break;
	default:
		cout << "Please enter choice 1 - 5 only." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		system("pause");
		system("cls");
		setting(WhoStartFirst, DisplayPCShips, sea_size, numCarrier, numBattleship, numSubmarine, numDestroyer);
		break;
	}
}

void whoFirst(bool &WhoStartFirst)
{
	system("cls");
	int option;

	cout << endl;
	cout << "How start first?" << endl;
	cout << "Current setting (default: Player): ";
	if (WhoStartFirst == 0)
		cout << "Player" << "\n\n";
	else
		cout << "PC" << "\n\n";
	cout << "Change of setting ((0)Player starts first [default], (1)  PC Intelligence starts first): ";
	cin >> option;

	if (option == 0)
	{
		WhoStartFirst = 0;
		cout << "\n\n";
		cout << "Starts First:Player ." << "\n\n";
		cout << "Press any key to return to main menu." << "\n";
		system("pause");
		system("cls");
	}
	else if (option == 1)
	{
		WhoStartFirst = 1;
		cout << "\n\n";
		cout << "Starts First:PC Intelligence ." << "\n\n";
		cout << "Press any key to return to main menu." << "\n";
		system("pause");
		system("cls");
	}
	else
	{
		cout << "Error. Please try again." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		system("pause");
		whoFirst(WhoStartFirst);
	}
}

void displayPCships(bool &DisplayPCShips)
{
	system("cls");
	int option;

	cout << endl;
	cout << "Display PC ships?" << endl;
	cout << "Current Setting (default: No): ";
	if (DisplayPCShips == 0)
		cout << "No" << "\n\n";
	else if (DisplayPCShips == 1)
		cout << "Yes" << "\n\n";
	cout << "Change of setting ((0) - Do NOT display PC ships [default], (1) - Display PC ships): ";
	cin >> option;

	if (option == 0)
	{
		DisplayPCShips = 0;
		cout << "\n\n\n";
		cout << "System will NOT display PC ships ." << "\n\n";
		cout << "Press any key to return to main menu." << "\n";
		system("pause");
		system("cls");
	}
	else if (option == 1)
	{
		DisplayPCShips = 1;
		cout << "\n\n\n";
		cout << "System will display PC ships ." << "\n\n";
		cout << "Press any key to return to main menu." << "\n";
		system("pause");
		system("cls");
	}
	else
	{
		cout << "Error . Please try again." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		system("pause");
		displayPCships(DisplayPCShips);
	}
}

void boardSize(int &board_size, int numCarrier, int numBattleship, int numSubmarine, int numDestroyer)
{
	system("cls");
	int option;

	cout << endl;
	cout << "The size of the board" << endl;
	cout << "Current setting (Default Number 10x10): ";
	cout << board_size << "x" << board_size << "\n\n";

	cout << "Change of setting (7~10): ";
	cin >> option;

	if ((option >= 7 && option <= 10) && (numCarrier * 5 + numBattleship * 4 + numSubmarine * 3 + numDestroyer * 2 <= option * option))
	{
		board_size = option;
		cout << "\n\n\n";
		cout << "The board size has been changed to " << board_size << "x" << board_size << "." << "\n\n";
		cout << "Press any key to return to main menu." << "\n";
		system("pause");
		system("cls");
	}
	else
	{
		cout << "Invaild Value . ";
		cin.clear();
		cin.ignore(10000, '\n');
		if ((option >= 7 && option <= 10) == 0)
		{
			cout << "The size of the board must be within 7 to 10." << endl;
		}
		else if ((option >= 7 && option <= 10) && (numCarrier * 5 + numBattleship * 4 + numSubmarine * 3 + numDestroyer * 2 >= option * option))
		{
			cout << "Not enough capacity for the blocks." << endl;
		}
		cout << endl;
		cout << "Please try again." << endl;
		system("pause");
		boardSize(board_size, numCarrier, numBattleship, numSubmarine, numDestroyer);
	}
}

void numberOFships(int sea_size, int &numCarrier, int &numBattleship, int &numSubmarine, int &numDestroyer)
{
	int tempNumCarrier, tempNumBattleship, tempNumSubmarine, tempNumDestroyer;
	system("cls");

	cout << left << endl;
	cout << setw(21) << "Type of ship" << "Number" << endl;
	cout << setw(11) << "Carrier" << setw(12) << "(size 5):" << numCarrier << endl;
	cout << setw(11) << "Battleship" << setw(12) << "(size 4):" << numBattleship << endl;
	cout << setw(11) << "Submarine" << setw(12) << "(size 3):" << numSubmarine << endl;
	cout << setw(11) << "Destroyer" << setw(12) << "(size 2):" << numDestroyer << endl;

	cout << "\n\n";
	cout << "Please be aware that the total size occupied by all the ships must be smaller than or equal to the capacity of the sea" << endl;
	cout << "Please enter the new number of carrier (size 5)(1~5, default:1): ";
	cin >> tempNumCarrier;

	cout << "Please enter the new number of battleship (size 4)(1~5, default:2): ";
	cin >> tempNumBattleship;

	cout << "Please enter the new number of submarine (size 3)( 1~5, default:3): ";
	cin >> tempNumSubmarine;

	cout << "Please enter the new number of destroyer (size 2)(1~5, default:4): ";
	cin >> tempNumDestroyer;

	if ((tempNumCarrier >= 1 && tempNumCarrier <= 5) && (tempNumBattleship >= 1 && tempNumBattleship <= 5) &&
		(tempNumSubmarine >= 1 && tempNumSubmarine <= 5) && (tempNumDestroyer >= 1 && tempNumDestroyer <= 5) &&
		(tempNumCarrier * 5 + tempNumBattleship * 4 + tempNumSubmarine * 3 + tempNumDestroyer * 2 <= sea_size * sea_size) == 1)
	{
		numCarrier = tempNumCarrier;
		numBattleship = tempNumBattleship;
		numSubmarine = tempNumSubmarine;
		numDestroyer = tempNumDestroyer;

		cout << "\n\n";
		cout << "All the changes have been saved. The new setting is as follow:" << "\n\n";
		cout << setw(21) << "Type of ship" << "Number" << endl;
		cout << setw(11) << "Carrier" << setw(12) << "(size 5):" << numCarrier << endl;
		cout << setw(11) << "Battleship" << setw(12) << "(size 4):" << numBattleship << endl;
		cout << setw(11) << "Submarine" << setw(12) << "(size 3):" << numSubmarine << endl;
		cout << setw(11) << "Destroyer" << setw(12) << "(size 2):" << numDestroyer << endl;
		cout << "\n\n\n";
		cout << "Press any key to return to main menu." << "\n";
		system("pause");
		system("cls");
	}
	else
	{
		cout << "\n\nError. ";
		cin.clear();
		cin.ignore(10000, '\n');
		if ((tempNumCarrier >= 1 && tempNumCarrier <= 5) && (tempNumBattleship >= 1 && tempNumBattleship <= 5) &&
			(tempNumSubmarine >= 1 && tempNumSubmarine <= 5) && (tempNumDestroyer >= 1 && tempNumDestroyer <= 5) == 0)
		{
			cout << "Number of Carrier, Battleship, Submarine and Destroyer must be within 1 to 5" << endl;
		}
		else if (tempNumCarrier * 5 + tempNumBattleship * 4 + tempNumSubmarine * 3 + tempNumDestroyer * 2 >= sea_size * sea_size)
		{
			cout << "The total size occupied by all the ships is larger than to the capacity of the sea" << endl;
		}
		cout << "Please try again." << endl;
		system("pause");
		numberOFships(sea_size, numCarrier, numBattleship, numSubmarine, numDestroyer);
	}
}

void instructions()
{
	system("cls");

	cout << "Instructions" << "\n\n";

	cout << "At the beginning, you are required to input the coordinate so as to place 1\n";
	cout << "block among 3, which are randomly selected by the system, into the board.Each\n";
	cout << "block carries marks depends on the size of them, i.e., 1 square carries 10\n";
	cout << "marks.The more blocks you put on the board, the more marks you will get.\n";
	cout << "Moreover, If you put a block that can successfully produce complete horizontal\n";
	cout << "or vertical line(s), the line(s) will be removed and marks will be added, i.e.,\n";
	cout << "100 marks for 1 line, 300 marks for 2 lines, 600 marks for 3 lines, 1000 marks\n";
	cout << "for 4 lines and 1500 marks for 5 lines. The game is over untill there is no\n";
	cout << "place for putting the block."<< endl;
	cout << "For the time bomb mode, for every 5 moves, a bomb will be placed randomly on\n";
	cout << "any board location that has been occupied by a block(i.e., ‘X’).  A bomb is\n";
	cout << "represented by a digit(i.e., the bomb timer) on the game board, which starts\n"; 
	cout << "from the value according to the current game setting and decreases by 1 on each\n";
	cout << "move. You need to put blocks and form a complete line across the bomb to clear\n";
	cout << "it before the bomb timer decreases to 0. Otherwise, you will lose and the game\n";
	cout << "finishes.\n";

	system("pause");
	system("cls");
}

void credits() // group member
{
	system("cls");

	cout << "\n" << left << endl;
	cout << "Credit:" << "\n\n";
	cout << "Student Name" << "\t\t" << "Student ID" << "\t\t" << "Class and Group" << endl;
	cout << "Lam Shek Chit" << "\t\t" << "16013315A" << "\t\t" << "102A" << endl;
	cout << "Lau Hin Chung" << "\t\t" << "16173163A" << "\t\t" << "102A" << endl;
	cout << "Yan Ho Hin" << "\t\t" << "16060353A" << "\t\t" << "102C" << endl;
	cout << "Lai Ka Ho" << "\t\t" << "16006256A" << "\t\t" << "102C" << endl;
	cout << "Cheng King Hei" << "\t\t" << "16032262A" << "\t\t" << "102C" << endl;

	system("pause");
	system("cls");
}