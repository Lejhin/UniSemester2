/*
 * main.cpp
 *
 *  Created on: 29.09.2022
 *      Author: n2210657
 */

#include <iostream>
#include <fstream>

using namespace std;

int main(){

	//ifstream für input
	//ofstream für output
	ifstream file;
	file.open("Aufgabe5/zahlen.txt");
	int zahl;
	while(file >> zahl){
		cout << zahl << endl;
	};



	
	


}




