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


	fstream file;
	file.open("Aufgabe5/zahlen.txt", ios::in);
	int zahl;
	while(file >> zahl){

		cout << zahl << endl;
	};



	
	


}




