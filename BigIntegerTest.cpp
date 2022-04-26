/****************************************************************************************
*  Darong Li, dli97
*  2022 Winter CSE101 PA6
*  BigIntegerTest.cpp
*  Test Client BigInteger ADT
*****************************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){
	BigInteger A,B,C,D;
	cout << "A before init: " << A << endl;
	cout << "B before init: " << B << endl;
	cout << "C before init: " << C << endl;
	cout << "D before init: " << D << endl;

	string s1 = "123456789";
	string s2 = "123456789100000000";
	string s3 = "1234567891000000000";

	A = BigInteger(s1);
	B = BigInteger(s2);
	C = A+B;
	cout << "A: " << A << endl;
	cout << "B: " << B << endl;
	cout << "C = A+B: " << C << endl;

	cout << endl;

	D = A;
	cout << "D: " << D << endl;
	D.makeZero();
	cout << "D after makezero(): " << D << endl;
	cout << "A at D after makezero(): " << A << endl;

	cout << endl;

	D = BigInteger(s3);
	cout << "D before negate(): " << D << endl;
	D.negate();
	cout << "D after negate(): " << D << endl;

	C = D - A;
	cout << "Testing neg - pos:" << endl;
	cout << "A: " << A << endl;
	cout << "D: " << D << endl;
	cout << "C = D-A: " << C << endl;
	
	cout << endl;
	
	C = A-D;
	cout << "Testing pos - neg:" << endl;
	cout << "A: " << A << endl;
	cout << "D: " << D << endl;
	cout << "C = D-A: " << C << endl;

	cout << endl;
	
	C = A+D;
	cout << "Testing pos + neg:" << endl;
	cout << "A: " << A << endl;
	cout << "D: " << D << endl;
	cout << "C = D-A: " << C << endl;
	
	cout << endl;

	A.negate();
	C = A+D;
	cout << "Testing neg + neg:" << endl;
	cout << "A: " << A << endl;
	cout << "D: " << D << endl;
	cout << "C = D-A: " << C << endl;

	cout << endl;

	A.negate();
	A += A;
	cout << "Testing +=" << endl;
	cout << "A: " << A << endl;
	
	cout << endl;
	
	A = BigInteger(s1);
	A -= A;
	cout << "Testing -=" << endl;
	cout << "A: " << A << endl;

	cout << endl;

	A = BigInteger(s1);
	C = A*B;
	cout << "Testing pos * pos:" << endl;
	cout << "A: " << A << endl;
	cout << "B: " << B << endl;
	cout << "C = AB: " << C << endl;

	cout << endl;

	C = A*B;
	cout << "Testing pos * pos:" << endl;
	cout << "A: " << A << endl;
	cout << "B: " << B << endl;
	cout << "C = AB: " << C << endl;

	cout << endl;

	C = A*D;
	cout << "Testing pos * pos:" << endl;
	cout << "A: " << A << endl;
	cout << "D: " << D << endl;
	cout << "C = AD: " << D << endl;

	cout << endl;

	A.negate();
	cout << "Testing neg * neg" << endl;
	cout << "A: " << A << endl;
	cout << "D: " << D << endl;
	cout << "C = AD: " << D << endl;
	
	cout << endl;

	A *= A;
	cout << "Test *=" << endl;
	cout << "A = " << A << endl;

	cout << endl;
	return 0;
}
