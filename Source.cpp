#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <string.h>
#include <stdlib.h>

static double w1For2Pc[4] = { 1, 1, 1, 1 };
static double w2For2Pc[4] = { 1, 1, 1, 1 };
static double w1For3Pc[9] = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0, 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0, 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };
static double w2For3Pc[9] = { 5.0 / 9.0, 5.0 / 9.0, 5.0 / 9.0, 8.0 / 9.0, 8.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0, 5.0 / 9.0, 5.0 / 9.0 };
static double w1For4Pc[16] = { (18.0 - sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 - sqrt(30.0)) / 36.0, (18.0 - sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0,
							(18.0 - sqrt(30.0)) / 36.0, (18.0 - sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 - sqrt(30.0)) / 36.0, (18.0 - sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0,
							(18.0 + sqrt(30.0)) / 36.0, (18.0 - sqrt(30.0)) / 36.0 };
static double w2For4Pc[16] = { (18.0 - sqrt(30.0)) / 36.0, (18.0 - sqrt(30.0)) / 36.0, (18.0 - sqrt(30.0)) / 36.0, (18.0 - sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0,(18.0 + sqrt(30.0)) / 36.0,
							(18.0 + sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 - sqrt(30.0)) / 36.0,(18.0 - sqrt(30.0)) / 36.0,
							(18.0 - sqrt(30.0)) / 36.0, (18.0 - sqrt(30.0)) / 36.0 };

struct Node {
	double x;
	double y;
	bool BC = false;
};

struct Element {
	int id[4];

	void printID() {
		for (int i = 0; i < 4; i++) {
			std::cout << id[i] << "\t";
		}
		std::cout << std::endl;
	}
};

struct Grid {
	int nND;
	int nEL;
	std::vector<Node>ND;
	std::vector<Element>NE;

	void toString() {
		std::cout << "Number of nodes: " << nND << std::endl;

		for (int i = 0; i < ND.size(); i++) {
			std::cout << "X: " << std::setprecision(10) << std::fixed << ND[i].x << "\tY: " << std::setprecision(11) << std::fixed << ND[i].y << "\t" << ND[i].BC << std::endl;
		}
		std::cout << std::endl;
		std::cout << "Number of elements: " << nEL << std::endl;

		for (int j = 0; j < NE.size(); j++) {
			NE[j].printID();
		}
	}
};

struct GlobalData {
	double SimulationTime;
	double SimulationStepTime;
	double Conductivity;
	double Alfa;
	double Tot;
	double InitialTemp;
	double Density;
	double SpecificHeat;

	void toString() {
		std::cout << std::setprecision(2) << std::fixed << "SimulationTime: " << SimulationTime << std::endl;
		std::cout << std::setprecision(2) << std::fixed << "SimulationStepTime: " << SimulationStepTime << std::endl;
		std::cout << std::setprecision(2) << std::fixed << "Conductivity: " << Conductivity << std::endl;
		std::cout << std::setprecision(2) << std::fixed << "Alfa: " << Alfa << std::endl;
		std::cout << std::setprecision(2) << std::fixed << "Tot: " << Tot << std::endl;
		std::cout << std::setprecision(2) << std::fixed << "InitialTemp: " << InitialTemp << std::endl;
		std::cout << std::setprecision(2) << std::fixed << "Density: " << Density << std::endl;
		std::cout << std::setprecision(2) << std::fixed << "SpecificHeat: " << SpecificHeat << std::endl;
	}
};

void readFile(std::string fileName, Grid& grid, GlobalData& globalData) {
	std::ifstream file(fileName);

	if (file.is_open()) {
		std::cout << "File successfully opened." << std::endl;
	}
	else {
		std::cout << "Did not found a file." << std::endl;
		return;
	}

	std::string string;
	double number;
	int numInt;

	for (int i = 0; i < 10; i++) {
		if (i < 8) {
			file >> string >> number;
			if (i == 0) {
				(&globalData)->SimulationTime = number;
			}
			else if (i == 1) {
				(&globalData)->SimulationStepTime = number;
			}
			else if (i == 2) {
				(&globalData)->Conductivity = number;
			}
			else if (i == 3) {
				(&globalData)->Alfa = number;
			}
			else if (i == 4) {
				(&globalData)->Tot = number;
			}
			else if (i == 5) {
				(&globalData)->InitialTemp = number;
			}
			else if (i == 6) {
				(&globalData)->Density = number;
			}
			else if (i == 7) {
				(&globalData)->SpecificHeat = number;
			}
		}
		else if (i == 8) {
			file >> string >> string >> numInt;
			(&grid)->nND = numInt;
		}
		else if (i == 9) {
			file >> string >> string >> numInt;
			(&grid)->nEL = numInt;
		}
	}
	file >> string;

	for (int j = 0; j < grid.nND; j++) {
		double x, y;
		Node newNode;
		file >> numInt >> string >> x >> string >> y;
		newNode.x = x;
		newNode.y = y;
		(&grid)->ND.push_back(newNode);
	}

	file >> string >> string;

	for (int k = 0; k < (&grid)->nEL; k++) {
		int x, y, z, w;
		std::string str;
		Element newElement;

		file >> numInt >> str >> x >> str >> y >> str >> z >> str >> w;
		newElement.id[0] = x;
		newElement.id[1] = y;
		newElement.id[2] = z;
		newElement.id[3] = w;

		(&grid)->NE.push_back(newElement);
	}

	while (!file.eof()) {
		file >> string >> numInt;

		(&grid)->ND[numInt - 1].BC = true;
	}

	file.close();
}

double functionN(int n, double ksi, double eta) {
	if (n == 1) {
		return 0.25 * (1 - ksi) * (1 - eta);
	}
	else if (n == 2) {
		return 0.25 * (1 + ksi) * (1 - eta);
	}
	else if (n == 3) {
		return 0.25 * (1 + ksi) * (1 + eta);
	}
	else if (n == 4) {
		return 0.25 * (1 - ksi) * (1 + eta);
	}
	else {
		return NULL;
	}
}

double dNdKsi(int n, double eta) {
	if (n == 1) {
		return -0.25 * (1 - eta);
	}
	else if (n == 2) {
		return 0.25 * (1 - eta);
	}
	else if (n == 3) {
		return 0.25 * (1 + eta);
	}
	else if (n == 4) {
		return -0.25 * (1 + eta);
	}
	else {
		return NULL;
	}
}

double dNdEta(int n, double ksi) {
	if (n == 1) {
		return -0.25 * (1 - ksi);
	}
	else if (n == 2) {
		return -0.25 * (1 + ksi);
	}
	else if (n == 3) {
		return 0.25 * (1 + ksi);
	}
	else if (n == 4) {
		return 0.25 * (1 - ksi);
	}
	else {
		return NULL;
	}
}

struct UniversalElement {
	double pcKsiFor2PC[4] = { -1 / sqrt(3), 1 / sqrt(3), -1 / sqrt(3), 1 / sqrt(3) };
	double pcEtaFor2PC[4] = { -1 / sqrt(3), -1 / sqrt(3), 1 / sqrt(3), 1 / sqrt(3) };
	double pcKsiFor3PC[9] = { -sqrt(0.6), 0, sqrt(0.6), -sqrt(0.6), 0, sqrt(0.6), -sqrt(0.6), 0, sqrt(0.6) };
	double pcEtaFor3PC[9] = { -sqrt(0.6), -sqrt(0.6), -sqrt(0.6), 0, 0, 0, sqrt(0.6), sqrt(0.6), sqrt(0.6) };
	double pcKsiFor4PC[16] = { -sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0)), -sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0)), -sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0)),
	-sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0)), -sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0)),  -sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0)),
	-sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0)) , -sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0)) , sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0)) ,
	sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0)) , sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0)) , sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0)),
	sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0)), sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0)) , sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0)) ,
	sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0)) };
	double pcEtaFor4PC[16] = { -sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0)), -sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0)), sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0)),
		sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0)), -sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0)), -sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0)),
		sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0)), sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0)),-sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0)),
		-sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0)), sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0)), sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0)),
		-sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0)), -sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0)), sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0)),
		sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0)) };

	double** tabK;
	double** tabE;

	UniversalElement(int pc) {
		if (pc == 2) {
			tabK = new double* [4];
			tabE = new double* [4];
		}
		else if (pc == 3) {
			tabK = new double* [9];
			tabE = new double* [9];
		}
		else if (pc == 4) {
			tabK = new double* [16];
			tabE = new double* [16];
		}
		else {
			std::cout << "Incorrect amount of points. Program finished." << std::endl;
		}

		for (int i = 0; i < pc * pc; ++i) {
			tabK[i] = new double[4];
			tabE[i] = new double[4];
		}

		for (int i = 0; i < pc * pc; i++) {
			for (int j = 0; j < 4; j++) {
				if (pc == 2) {
					tabK[i][j] = dNdKsi(j + 1, pcEtaFor2PC[i]);
					tabE[i][j] = dNdEta(j + 1, pcKsiFor2PC[i]);
				}
				else if (pc == 3) {
					tabK[i][j] = dNdKsi(j + 1, pcEtaFor3PC[i]);
					tabE[i][j] = dNdEta(j + 1, pcKsiFor3PC[i]);
				}
				else if (pc == 4) {
					tabK[i][j] = dNdKsi(j + 1, pcEtaFor4PC[i]);
					tabE[i][j] = dNdEta(j + 1, pcKsiFor4PC[i]);
				}
				else {
					std::cout << "Incorrect amount of points. Program finished." << std::endl;
				}
			}
		}
	}

	void print(int pc) {
		std::cout << "dN/dKsi:" << std::endl;
		for (int i = 0; i < pc * pc; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << tabK[i][j] << "\t";
			}
			std::cout << std::endl;
		}

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "dN/dEta:" << std::endl;
		for (int i = 0; i < pc * pc; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << tabE[i][j] << "\t";
			}
			std::cout << std::endl;
		}
	}
};

struct Side1 {
	double** tabKsiEta;
	double** tabN;
	double weightsFor2PC[2] = { 1, 1 };
	double weightsFor3PC[3] = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };
	double weightsFor4PC[4] = { (18.0 - sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 - sqrt(30.0)) / 36.0 };

	Side1(int pc) {
		tabKsiEta = new double* [pc];
		tabN = new double* [pc];

		for (int i = 0; i < pc; i++) {
			tabKsiEta[i] = new double[2];
			tabN[i] = new double[4];
		}

		if (pc == 2) {
			tabKsiEta[0][0] = -(1 / sqrt(3));
			tabKsiEta[0][1] = -1;
			tabKsiEta[1][0] = 1 / sqrt(3);
			tabKsiEta[1][1] = -1;
		}
		else if (pc == 3) {
			tabKsiEta[0][0] = -sqrt(0.6);
			tabKsiEta[0][1] = -1;
			tabKsiEta[1][0] = 0;
			tabKsiEta[1][1] = -1;
			tabKsiEta[2][0] = sqrt(0.6);
			tabKsiEta[2][1] = -1;
		}
		else if (pc == 4) {
			tabKsiEta[0][0] = -sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0));
			tabKsiEta[0][1] = -1;
			tabKsiEta[1][0] = -sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0));
			tabKsiEta[1][1] = -1;
			tabKsiEta[2][0] = sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0));
			tabKsiEta[2][1] = -1;
			tabKsiEta[3][0] = sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0));
			tabKsiEta[3][1] = -1;
		}
		else {
			std::cout << "Incorrect amount of points. Program finished." << std::endl;
		}

		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < pc; k++) {
				tabN[k][j] = functionN(j + 1, tabKsiEta[k][0], tabKsiEta[k][1]);
			}
		}
	}

	void print(int pc) {
		for (int i = 0; i < pc; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << tabN[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
};

struct Side2 {
	double** tabKsiEta;
	double** tabN;
	double weightsFor2PC[2] = { 1, 1 };
	double weightsFor3PC[3] = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };
	double weightsFor4PC[4] = { (18.0 - sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 - sqrt(30.0)) / 36.0 };

	Side2(int pc) {
		tabKsiEta = new double* [pc];
		tabN = new double* [pc];

		for (int i = 0; i < pc; i++) {
			tabKsiEta[i] = new double[2];
			tabN[i] = new double[4];
		}

		if (pc == 2) {
			tabKsiEta[0][0] = 1;
			tabKsiEta[0][1] = -(1 / sqrt(3));
			tabKsiEta[1][0] = 1;
			tabKsiEta[1][1] = (1 / sqrt(3));
		}
		else if (pc == 3) {
			tabKsiEta[0][0] = 1;
			tabKsiEta[0][1] = -sqrt(0.6);
			tabKsiEta[1][0] = 1;
			tabKsiEta[1][1] = 0;
			tabKsiEta[2][0] = 1;
			tabKsiEta[2][1] = sqrt(0.6);
		}
		else if (pc == 4) {
			tabKsiEta[0][0] = 1;
			tabKsiEta[0][1] = -sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0));
			tabKsiEta[1][0] = 1;
			tabKsiEta[1][1] = -sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0));
			tabKsiEta[2][0] = 1;
			tabKsiEta[2][1] = sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0));
			tabKsiEta[3][0] = 1;
			tabKsiEta[3][1] = sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0));
		}
		else {
			std::cout << "Incorrect amount of points. Program finished." << std::endl;
		}

		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < pc; k++) {
				tabN[k][j] = functionN(j + 1, tabKsiEta[k][0], tabKsiEta[k][1]);
			}
		}
	}

	void print(int pc) {
		for (int i = 0; i < pc; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << tabN[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
};

struct Side3 {
	double** tabKsiEta;
	double** tabN;
	double weightsFor2PC[2] = { 1, 1 };
	double weightsFor3PC[3] = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };
	double weightsFor4PC[4] = { (18.0 - sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 - sqrt(30.0)) / 36.0 };

	Side3(int pc) {
		tabKsiEta = new double* [pc];
		tabN = new double* [pc];

		for (int i = 0; i < pc; i++) {
			tabKsiEta[i] = new double[2];
			tabN[i] = new double[4];
		}

		if (pc == 2) {
			tabKsiEta[0][0] = -(1 / sqrt(3));
			tabKsiEta[0][1] = 1;
			tabKsiEta[1][0] = (1 / sqrt(3));
			tabKsiEta[1][1] = 1;
		}
		else if (pc == 3) {
			tabKsiEta[0][0] = -sqrt(0.6);
			tabKsiEta[0][1] = 1;
			tabKsiEta[1][0] = 0;
			tabKsiEta[1][1] = 1;
			tabKsiEta[2][0] = sqrt(0.6);
			tabKsiEta[2][1] = 1;
		}
		else if (pc == 4) {
			tabKsiEta[0][0] = -sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0));
			tabKsiEta[0][1] = 1;
			tabKsiEta[1][0] = -sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0));
			tabKsiEta[1][1] = 1;
			tabKsiEta[2][0] = sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0));
			tabKsiEta[2][1] = 1;
			tabKsiEta[3][0] = sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0));
			tabKsiEta[3][1] = 1;
		}
		else {
			std::cout << "Incorrect amount of points. Program finished." << std::endl;
		}

		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < pc; k++) {
				tabN[k][j] = functionN(j + 1, tabKsiEta[k][0], tabKsiEta[k][1]);
			}
		}
	}

	void print(int pc) {
		for (int i = 0; i < pc; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << tabN[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
};

struct Side4 {
	double** tabKsiEta;
	double** tabN;
	double weightsFor2PC[2] = { 1, 1 };
	double weightsFor3PC[3] = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };
	double weightsFor4PC[4] = { (18.0 - sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 + sqrt(30.0)) / 36.0, (18.0 - sqrt(30.0)) / 36.0 };

	Side4(int pc) {
		tabKsiEta = new double* [pc];
		tabN = new double* [pc];

		for (int i = 0; i < pc; i++) {
			tabKsiEta[i] = new double[2];
			tabN[i] = new double[4];
		}

		if (pc == 2) {
			tabKsiEta[0][0] = -1;
			tabKsiEta[0][1] = -(1 / sqrt(3));
			tabKsiEta[1][0] = -1;
			tabKsiEta[1][1] = (1 / sqrt(3));
		}
		else if (pc == 3) {
			tabKsiEta[0][0] = -1;
			tabKsiEta[0][1] = -sqrt(0.6);
			tabKsiEta[1][0] = -1;
			tabKsiEta[1][1] = 0;
			tabKsiEta[2][0] = -1;
			tabKsiEta[2][1] = sqrt(0.6);
		}
		else if (pc == 4) {
			tabKsiEta[0][0] = -1;
			tabKsiEta[0][1] = -sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0));
			tabKsiEta[1][0] = -1;
			tabKsiEta[1][1] = -sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0));
			tabKsiEta[2][0] = -1;
			tabKsiEta[2][1] = sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0));
			tabKsiEta[3][0] = -1;
			tabKsiEta[3][1] = sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0));
		}
		else {
			std::cout << "Incorrect amount of points. Program finished." << std::endl;
		}

		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < pc; k++) {
				tabN[k][j] = functionN(j + 1, tabKsiEta[k][0], tabKsiEta[k][1]);
			}
		}
	}

	void print(int pc) {
		for (int i = 0; i < pc; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << tabN[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
};

void aggregation2D(double** globalMatrixH, double** localMatrixH, int* id) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			globalMatrixH[id[i] - 1][id[j] - 1] += localMatrixH[i][j];
		}
	}
}

double** countMatrixH(UniversalElement& elem, Grid& grid, int pc, double** globalMatrixH, int* id, double* x, double* y, GlobalData& globalData) {
	int size = pc * pc;

	double** tabK = elem.tabK;
	double** tabE = elem.tabE;

	double** jacobian = new double* [size];

	for (int i = 0; i < size; i++) {
		jacobian[i] = new double[4];
	}

	double dX_dKsi;
	double dX_dEta;
	double dY_dKsi;
	double dY_dEta;

	double* detJTab = new double[size];

	for (int i = 0; i < size; i++) {
		dX_dKsi = 0;
		dX_dEta = 0;
		dY_dKsi = 0;
		dY_dEta = 0;

		for (int j = 0; j < 4; j++) {
			dX_dKsi += tabK[i][j] * x[j];
			dX_dEta += tabE[i][j] * x[j];
			dY_dKsi += tabK[i][j] * y[j];
			dY_dEta += tabE[i][j] * y[j];
		}

		jacobian[i][0] = dX_dKsi;
		jacobian[i][1] = dY_dKsi;
		jacobian[i][2] = dX_dEta;
		jacobian[i][3] = dY_dEta;

		double detJ = jacobian[i][0] * jacobian[i][3] - jacobian[i][1] * jacobian[i][2];
		double detJInverse = 1 / detJ;

		detJTab[i] = detJ;

		for (int k = 0; k < 4; k++) {
			jacobian[i][k] *= detJInverse;
		}
	}

	double** derivativesTabX = new double* [size];
	double** derivativesTabY = new double* [size];

	for (int i = 0; i < size; i++) {
		derivativesTabX[i] = new double[4];
		derivativesTabY[i] = new double[4];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < 4; j++) {
			derivativesTabX[i][j] = jacobian[i][3] * tabK[i][j] + (-1) * jacobian[i][1] * tabE[i][j];
			derivativesTabY[i][j] = jacobian[i][0] * tabE[i][j] + (-1) * jacobian[i][2] * tabK[i][j];
		}
	}

	double** matrixH = new double* [4];
	for (int i = 0; i < 4; i++) {
		matrixH[i] = new double[4];
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrixH[i][j] = 0;
		}
	}

	for (int k = 0; k < size; k++) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (pc == 2) {
					matrixH[i][j] += (globalData.Conductivity * (derivativesTabX[k][i] * derivativesTabX[k][j] + derivativesTabY[k][i] * derivativesTabY[k][j]) * detJTab[k]) * w1For2Pc[k] * w2For2Pc[k];
				}
				else if (pc == 3) {
					matrixH[i][j] += (globalData.Conductivity * (derivativesTabX[k][i] * derivativesTabX[k][j] + derivativesTabY[k][i] * derivativesTabY[k][j]) * detJTab[k]) * w1For3Pc[k] * w2For3Pc[k];
				}
				else if (pc == 4) {
					matrixH[i][j] += (globalData.Conductivity * (derivativesTabX[k][i] * derivativesTabX[k][j] + derivativesTabY[k][i] * derivativesTabY[k][j]) * detJTab[k]) * w1For4Pc[k] * w2For4Pc[k];
				}
			}
		}
	}

	aggregation2D(globalMatrixH, matrixH, id);

	return matrixH;
}

double** countMatrixHBC(Side1 side1, Side2 side2, Side3 side3, Side4 side4, int* id, double* x, double* y, bool* tabBC, GlobalData& globalData, double** globalMatrixH, int pc) {
	double L, detJ;
	double** localHBC = new double* [4];
	for (int i = 0; i < 4; i++) {
		localHBC[i] = new double[4];
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			localHBC[i][j] = 0;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (i == 0) {
			if (tabBC[i] == true && tabBC[i + 1] == true) {
				L = sqrt(pow(x[i + 1] - x[i], 2) + pow(y[i + 1] - y[i], 2));
				detJ = L / 2.0;

				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						for (int k = 0; k < pc; k++) {
							if (pc == 2) {
								localHBC[i][j] += globalData.Alfa * (side1.weightsFor2PC[k] * side1.tabN[k][i] * side1.tabN[k][j]) * detJ;
							}
							else if (pc == 3) {
								localHBC[i][j] += globalData.Alfa * (side1.weightsFor3PC[k] * side1.tabN[k][i] * side1.tabN[k][j]) * detJ;
							}
							else if (pc == 4) {
								localHBC[i][j] += globalData.Alfa * (side1.weightsFor4PC[k] * side1.tabN[k][i] * side1.tabN[k][j]) * detJ;
							}
							else {
								return NULL;
							}
						}
					}
				}
			}
		}
		else if (i == 1) {
			if (tabBC[i] == true && tabBC[i + 1] == true) {
				L = sqrt(pow(x[i + 1] - x[i], 2) + pow(y[i + 1] - y[i], 2));
				detJ = L / 2.0;

				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						for (int k = 0; k < pc; k++) {
							if (pc == 2) {
								localHBC[i][j] += globalData.Alfa * (side2.weightsFor2PC[k] * side2.tabN[k][i] * side2.tabN[k][j]) * detJ;
							}
							else if (pc == 3) {
								localHBC[i][j] += globalData.Alfa * (side2.weightsFor3PC[k] * side2.tabN[k][i] * side2.tabN[k][j]) * detJ;
							}
							else if (pc == 4) {
								localHBC[i][j] += globalData.Alfa * (side2.weightsFor4PC[k] * side2.tabN[k][i] * side2.tabN[k][j]) * detJ;
							}
							else {
								return NULL;
							}
						}
					}
				}
			}
		}
		else if (i == 2) {
			if (tabBC[i] == true && tabBC[i + 1] == true) {
				L = sqrt(pow(x[i + 1] - x[i], 2) + pow(y[i + 1] - y[i], 2));
				detJ = L / 2.0;

				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						for (int k = 0; k < pc; k++) {
							if (pc == 2) {
								localHBC[i][j] += globalData.Alfa * (side3.weightsFor2PC[k] * side3.tabN[k][i] * side3.tabN[k][j]) * detJ;
							}
							else if (pc == 3) {
								localHBC[i][j] += globalData.Alfa * (side3.weightsFor3PC[k] * side3.tabN[k][i] * side3.tabN[k][j]) * detJ;
							}
							else if (pc == 4) {
								localHBC[i][j] += globalData.Alfa * (side3.weightsFor4PC[k] * side3.tabN[k][i] * side3.tabN[k][j]) * detJ;
							}
							else {
								return NULL;
							}
						}
					}
				}
			}
		}
		else if (i == 3) {
			if (tabBC[i] == true && tabBC[0] == true) {
				L = sqrt(pow(x[0] - x[i], 2) + pow(y[0] - y[i], 2));
				detJ = L / 2.0;

				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						for (int k = 0; k < pc; k++) {
							if (pc == 2) {
								localHBC[i][j] += globalData.Alfa * (side4.weightsFor2PC[k] * side4.tabN[k][i] * side4.tabN[k][j]) * detJ;
							}
							else if (pc == 3) {
								localHBC[i][j] += globalData.Alfa * (side4.weightsFor3PC[k] * side4.tabN[k][i] * side4.tabN[k][j]) * detJ;
							}
							else if (pc == 4) {
								localHBC[i][j] += globalData.Alfa * (side4.weightsFor4PC[k] * side4.tabN[k][i] * side4.tabN[k][j]) * detJ;
							}
							else {
								return NULL;
							}
						}
					}
				}
			}
		}
	}

	aggregation2D(globalMatrixH, localHBC, id);

	return localHBC;
}

void aggregation1D(double* globalVectorP, double* localVectorP, int* id) {
	for (int i = 0; i < 4; i++) {
		globalVectorP[id[i] - 1] += localVectorP[i];
	}
}

double* countVectorP(Grid grid, Side1 side1, Side2 side2, Side3 side3, Side4 side4, int* id, double* x, double* y, bool* tabBC, GlobalData& globalData, double* vectorPGlobal, int pc) {
	double L, detJ;
	double* localVectorP = new double[4];
	for (int i = 0; i < 4; i++) {
		localVectorP[i] = 0;
	}

	for (int i = 0; i < 4; i++) {
		if (i == 0) {
			if (tabBC[i] == true && tabBC[i + 1] == true) {
				L = sqrt(pow(x[i + 1] - x[i], 2) + pow(y[i + 1] - y[i], 2));
				detJ = L / 2.0;

				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < pc; k++) {
						if (pc == 2) {
							localVectorP[j] += globalData.Alfa * globalData.Tot * (side1.weightsFor2PC[k] * side1.tabN[k][j]) * detJ;
						}
						else if (pc == 3) {
							localVectorP[j] += globalData.Alfa * globalData.Tot * (side1.weightsFor3PC[k] * side1.tabN[k][j]) * detJ;
						}
						else if (pc == 4) {
							localVectorP[j] += globalData.Alfa * globalData.Tot * (side1.weightsFor4PC[k] * side1.tabN[k][j]) * detJ;
						}
						else {
							return NULL;
						}
					}
				}
			}
		}
		else if (i == 1) {
			if (tabBC[i] == true && tabBC[i + 1] == true) {
				L = sqrt(pow(x[i + 1] - x[i], 2) + pow(y[i + 1] - y[i], 2));
				detJ = L / 2.0;

				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < pc; k++) {
						if (pc == 2) {
							localVectorP[j] += globalData.Alfa * globalData.Tot * (side2.weightsFor2PC[k] * side2.tabN[k][j]) * detJ;
						}
						else if (pc == 3) {
							localVectorP[j] += globalData.Alfa * globalData.Tot * (side2.weightsFor3PC[k] * side2.tabN[k][j]) * detJ;
						}
						else if (pc == 4) {
							localVectorP[j] += globalData.Alfa * globalData.Tot * (side2.weightsFor4PC[k] * side2.tabN[k][j]) * detJ;
						}
						else {
							return NULL;
						}
					}
				}
			}
		}
		else if (i == 2) {
			if (tabBC[i] == true && tabBC[i + 1] == true) {
				L = sqrt(pow(x[i + 1] - x[i], 2) + pow(y[i + 1] - y[i], 2));
				detJ = L / 2.0;

				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < pc; k++) {
						if (pc == 2) {
							localVectorP[j] += globalData.Alfa * globalData.Tot * (side3.weightsFor2PC[k] * side3.tabN[k][j]) * detJ;
						}
						else if (pc == 3) {
							localVectorP[j] += globalData.Alfa * globalData.Tot * (side3.weightsFor3PC[k] * side3.tabN[k][j]) * detJ;
						}
						else if (pc == 4) {
							localVectorP[j] += globalData.Alfa * globalData.Tot * (side3.weightsFor4PC[k] * side3.tabN[k][j]) * detJ;
						}
						else {
							return NULL;
						}
					}
				}
			}
		}
		else if (i == 3) {
			if (tabBC[i] == true && tabBC[0] == true) {
				L = sqrt(pow(x[0] - x[i], 2) + pow(y[0] - y[i], 2));
				detJ = L / 2.0;

				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < pc; k++) {
						if (pc == 2) {
							localVectorP[j] += globalData.Alfa * globalData.Tot * (side4.weightsFor2PC[k] * side4.tabN[k][j]) * detJ;
						}
						else if (pc == 3) {
							localVectorP[j] += globalData.Alfa * globalData.Tot * (side4.weightsFor3PC[k] * side4.tabN[k][j]) * detJ;
						}
						else if (pc == 4) {
							localVectorP[j] += globalData.Alfa * globalData.Tot * (side4.weightsFor4PC[k] * side4.tabN[k][j]) * detJ;
						}
						else {
							return NULL;
						}
					}
				}
			}
		}
	}

	aggregation1D(vectorPGlobal, localVectorP, id);

	return localVectorP;
}

void gaussElimination(int N, double** AB, double* X) {
	for (int j = 0; j < N - 1; j++) {
		for (int i = j + 1; i < N; i++) {
			double temp = AB[i][j] / AB[j][j];
			for (int k = 0; k < N + 1; k++) {
				AB[i][k] -= AB[j][k] * temp;
			}
		}
	}

	for (int i = N - 1; i >= 0; i--) {
		double sum = 0;
		for (int j = i + 1; j < N; j++) {
			sum += AB[i][j] * X[j];
		}
		X[i] = (AB[i][N] - sum) / AB[i][i];
	}
}

double** countMatrixC(UniversalElement& elem, Grid& grid, int pc, double** globalMatrixC, int* id, double* x, double* y, GlobalData& globalData) {
	int size = pc * pc;

	double** tabK = elem.tabK;
	double** tabE = elem.tabE;

	double** jacobian = new double* [size];

	for (int i = 0; i < size; i++) {
		jacobian[i] = new double[4];
	}

	double dX_dKsi;
	double dX_dEta;
	double dY_dKsi;
	double dY_dEta;

	double* detJTab = new double[size];

	for (int i = 0; i < size; i++) {
		dX_dKsi = 0;
		dX_dEta = 0;
		dY_dKsi = 0;
		dY_dEta = 0;

		for (int j = 0; j < 4; j++) {
			dX_dKsi += tabK[i][j] * x[j];
			dX_dEta += tabE[i][j] * x[j];
			dY_dKsi += tabK[i][j] * y[j];
			dY_dEta += tabE[i][j] * y[j];
		}

		jacobian[i][0] = dX_dKsi;
		jacobian[i][1] = dY_dKsi;
		jacobian[i][2] = dX_dEta;
		jacobian[i][3] = dY_dEta;

		double detJ = jacobian[i][0] * jacobian[i][3] - jacobian[i][1] * jacobian[i][2];

		detJTab[i] = detJ;
	}

	double** N = new double* [4];

	for (int i = 0; i < 4; i++) {
		N[i] = new double[size];
	}

	for (int i = 0; i < 4; i++) {
		if (pc == 2) {
			for (int j = 0; j < size; j++) {
				N[i][j] = functionN(i + 1, elem.pcKsiFor2PC[j], elem.pcEtaFor2PC[j]);
			}
		}
		else if (pc == 3) {
			for (int j = 0; j < size; j++) {
				N[i][j] = functionN(i + 1, elem.pcKsiFor3PC[j], elem.pcEtaFor3PC[j]);
			}
		}
		else if (pc == 4) {
			for (int j = 0; j < size; j++) {
				N[i][j] = functionN(i + 1, elem.pcKsiFor4PC[j], elem.pcEtaFor4PC[j]);
			}
		}
		else {
			return NULL;
		}
	}

	double** matrixC = new double* [4];
	for (int i = 0; i < 4; i++) {
		matrixC[i] = new double[4];
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrixC[i][j] = 0;
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < size; k++) {
				if (pc == 2) {
					matrixC[i][j] += globalData.Density * globalData.SpecificHeat * N[i][k] * N[j][k] * detJTab[k] * w1For2Pc[k] * w2For2Pc[k];
				}
				else if (pc == 3) {
					matrixC[i][j] += globalData.Density * globalData.SpecificHeat * N[i][k] * N[j][k] * detJTab[k] * w1For3Pc[k] * w2For3Pc[k];
				}
				else if (pc == 4) {
					matrixC[i][j] += globalData.Density * globalData.SpecificHeat * N[i][k] * N[j][k] * detJTab[k] * w1For4Pc[k] * w2For4Pc[k];
				}
			}
		}
	}

	aggregation2D(globalMatrixC, matrixC, id);

	return matrixC;
}

int main() {
	Grid grid;
	GlobalData globalData;

	int choice = 0;

	while (choice != 1 && choice != 2 && choice != 3) {
		std::cout << "Available grids:" << std::endl;
		std::cout << "1. Test1_4_4" << std::endl;
		std::cout << "2. Test2_4_4_MixGrid" << std::endl;
		std::cout << "3. Test3_31_31_kwadrat" << std::endl;
		std::cout << "\nYour choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			readFile("Test1_4_4.txt", grid, globalData);
			break;
		case 2:
			readFile("Test2_4_4_MixGrid.txt", grid, globalData);
			break;
		case 3:
			readFile("Test3_31_31_kwadrat.txt", grid, globalData);
			break;
		default:
			std::cout << "Grid does not exist. Choose again: " << std::endl;
		}
	}

	int pcInside, pcOutside;

	std::cout << "\nChoose amount of points inside the element: ";
	std::cin >> pcInside;

	if (pcInside != 2 && pcInside != 3 && pcInside != 4) {
		std::cout << "\nIncorrect amount of points. Program finished." << std::endl;
		return -1;
	}

	std::cout << "\nChoose amount of points on the side surface of the element: ";
	std::cin >> pcOutside;

	if (pcOutside != 2 && pcOutside != 3 && pcOutside != 4) {
		std::cout << "\nIncorrect amount of points. Program finished." << std::endl;
		return -1;
	}

	UniversalElement elem(pcInside);

	Side1 side1(pcOutside);
	Side2 side2(pcOutside);
	Side3 side3(pcOutside);
	Side4 side4(pcOutside);

	int globalSize = grid.nND;
	int elementVertices = 4;

	double** globalMatrixH = new double* [globalSize];
	double** globalMatrixC = new double* [globalSize];
	double** globalMatrixHandC = new double* [globalSize];
	for (int i = 0; i < globalSize; i++) {
		globalMatrixH[i] = new double[globalSize];
		globalMatrixC[i] = new double[globalSize];
		globalMatrixHandC[i] = new double[globalSize];
	}

	for (int i = 0; i < globalSize; i++) {
		for (int j = 0; j < globalSize; j++) {
			globalMatrixH[i][j] = 0;
			globalMatrixC[i][j] = 0;
			globalMatrixHandC[i][j] = 0;
		}
	}

	double* globalVectorP = new double[globalSize];
	double* globalVectorPandC = new double[globalSize];
	double* results = new double[globalSize];

	for (int i = 0; i < globalSize; i++) {
		globalVectorP[i] = 0;
		globalVectorPandC[i] = 0;
		results[i] = 0;
	}

	double* x = new double[elementVertices];
	double* y = new double[elementVertices];
	int* idTab = new int[elementVertices];
	bool* tabBC = new bool[elementVertices];

	double** matrixH;
	double** matrixHBC;
	double* vectorP;
	double** matrixC;

	for (int i = 0; i < grid.nEL; i++) {
		for (int j = 0; j < elementVertices; j++) {
			idTab[j] = grid.NE[i].id[j];
			int pom = idTab[j] - 1;
			x[j] = grid.ND[pom].x;
			y[j] = grid.ND[pom].y;
			tabBC[j] = grid.ND[pom].BC;
		}

		matrixH = countMatrixH(elem, grid, pcInside, globalMatrixH, idTab, x, y, globalData);
		matrixHBC = countMatrixHBC(side1, side2, side3, side4, idTab, x, y, tabBC, globalData, globalMatrixH, pcOutside);
		vectorP = countVectorP(grid, side1, side2, side3, side4, idTab, x, y, tabBC, globalData, globalVectorP, pcOutside);
		matrixC = countMatrixC(elem, grid, pcInside, globalMatrixC, idTab, x, y, globalData);
	}

	for (int i = 0; i < globalSize; i++) {
		for (int j = 0; j < globalSize; j++) {
			globalMatrixHandC[i][j] = globalMatrixH[i][j] + globalMatrixC[i][j] / globalData.SimulationStepTime;
		}
	}

	for (int time = globalData.SimulationStepTime; time < globalData.SimulationTime + 1; time += globalData.SimulationStepTime) {
		for (int i = 0; i < globalSize; i++) {
			globalVectorPandC[i] = globalVectorP[i];
			for (int j = 0; j < globalSize; j++) {
				if (time == globalData.SimulationStepTime)
					globalVectorPandC[i] += globalMatrixC[i][j] / globalData.SimulationStepTime * globalData.InitialTemp;
				else
					globalVectorPandC[i] += globalMatrixC[i][j] / globalData.SimulationStepTime * results[j];
			}
		}

		int size = globalSize + 1;

		double** matrixHCandP = new double* [globalSize];
		for (int i = 0; i < globalSize; i++) {
			matrixHCandP[i] = new double[size];
		}

		for (int i = 0; i < globalSize; i++) {
			for (int j = 0; j < globalSize; j++) {
				matrixHCandP[i][j] = globalMatrixHandC[i][j];
			}
			matrixHCandP[i][size - 1] = globalVectorPandC[i];
		}

		gaussElimination(globalSize, matrixHCandP, results);

		double min = results[0];
		double max = results[0];
		for (int i = 0; i < globalSize; i++) {
			if (results[i] > max)
				max = results[i];

			if (results[i] < min)
				min = results[i];
		}

		std::cout << "Time: " << time << "\t";
		std::cout << "Temperature min: " << min << " \t";
		std::cout << "Temperature max: " << max << std::endl;
	}

	delete[] globalMatrixH;
	delete[] globalVectorP;
	delete[] globalMatrixC;
	delete[] globalMatrixHandC;
	delete[] globalVectorPandC;
	delete[] results;
	delete[] x;
	delete[] y;
	delete[] idTab;
	delete[] tabBC;

	return 0;
}