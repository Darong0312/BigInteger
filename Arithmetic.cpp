/****************************************************************************************
*  Darong Li, dli97
*  2022 Winter CSE101 PA6
*  Arithmetic.cpp
*  Main program for pa6
*****************************************************************************************/

#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <cstring>
#include <ctype.h>

#include "List.h"
#include "BigInteger.h"

using namespace std;

int main(int argc, char* argv[]){
	ifstream in;
	ofstream out;
	if( argc != 3 ){
		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
		return(EXIT_FAILURE);
	}

	// open files for reading and writing 
   
	in.open(argv[1]);
	if( !in.is_open() ){
		cerr << "Unable to open file " << argv[1] << " for reading" << endl;
		return(EXIT_FAILURE);
	}

	out.open(argv[2]);
	if( !out.is_open() ){
		cerr << "Unable to open file " << argv[2] << " for writing" << endl;
		return(EXIT_FAILURE);
	}

	BigInteger A,B;

	// hold the number string
	string line;
	
	// get the first number string in the file
	getline(in,line);
	A = BigInteger(line);
	out << A << endl << endl;

	// skip the blank line
	getline(in,line);

	// get the second number string in the file
	getline(in,line);
//	cout << "B = " << line << endl;
	B = BigInteger(line);
	out << B << endl << endl;

	// A+B
	BigInteger sum = A+B;
	out << sum << endl << endl;
	
	// A-B
	BigInteger sub = A-B;
	out << sub << endl << endl;
	
	// A-A
	BigInteger subA;
	out << subA << endl << endl;

	// set the scalar to 2
	BigInteger scalar = BigInteger("2");
	
	// sub = A-B
	// 2*sub = 2(A-B) = 2A - 2B
	// subMult = 3A-2B = 2A - 2B + A
	BigInteger subMult = scalar * sub;
	subMult += A;
	out << subMult << endl << endl;

	// A*B
	BigInteger mult = A*B;
	out << mult << endl << endl;

	// A*A = A^2
	BigInteger multA = A*A;
	out << multA << endl<< endl;

	// B*B = B^2
	BigInteger multB = B*B;
	out << multB << endl<< endl;

	// multA_4 = multA*multA = A^2*A^2 = A^4
	// multB_5 = multB*multB = B^2*B^2 = B^4
	// B^5 = B^4 * b
	BigInteger multA_4 = multA * multA;
	BigInteger multB_5 = multB * multB;
	multB_5 *= B;

	// set scalar to 9
	// multA_4 = 9 * A^4
	scalar = BigInteger("9");
	multA_4 *= scalar;
	
	// set scalar to 16
	// multA_4 = 16 * B^5
	scalar = BigInteger("16");
	multB_5 *= scalar;

	// mult_add = 9A^4 + 16B^5
	BigInteger mult_add = multA_4 + multB_5;
	out << mult_add << endl;

	in.close();
	out.close();

	return 0;
}
