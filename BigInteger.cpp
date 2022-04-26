/****************************************************************************************
*  Darong Li, dli97
*  2022 Winter CSE101 PA6
*  BigInteger.cpp
*  BigInteger ADT
*****************************************************************************************/

#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <cstring>
#include <ctype.h>

#include "List.h"
#include "BigInteger.h"

const int power = 9;
const long base = 1000000000;

using namespace std;

BigInteger::BigInteger(){
	signum = 0;
}

BigInteger::BigInteger(std::string s){
	// use length to check if the string is empty
	int len = s.length();
	// if the string is empty, throw exception
	if(len == 0){
		throw std::invalid_argument("BigInteger: Constructor: empty string");
	}

	// init char array to hold the string
	char numbers[len];
	strcpy(numbers,s.c_str());
	
	// default signum to 1 since empty string cant pass the pre-condition
	signum = 1;

	// check if numbers[0] is +/-
	// if yes, set the sign and delete numbers[0]
	if(numbers[0] == '+'){
		signum = 1;
		s.erase(s.begin());
		strcpy(numbers,s.c_str());
		len = s.length();
	}
	else if(numbers[0] == '-'){
		signum = -1;
		s.erase(s.begin());
		strcpy(numbers,s.c_str());
		len = s.length();
	}

	// if after delete, the length is 0, throw exception
	if(s.length() == 0){
		throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
	}

	// check if the string has any other non-number character inside of the string
	bool digitFlag = false;
	for(int i = 0; i < len; i++){
		if( !isdigit(numbers[i]) && i!=0){
			digitFlag = true;
			break;
		}
	}
	if(digitFlag == true){
		throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
	}

	/*
	 * init i to length if the string -1;
	 * for every (power)  of number, create a new char[] to store it
	 * after the for loop, convert it back to long
	 * when reach to number[0], check if the number[0] is + or - ?
	 * when reach to number[0], check if the char.length = power
	 * if not fill in 0
	 */
	long x; // hold the conevtion from string to long, insert it into digits list
	int i = s.length()-1; // while loop condition, makesure to run the whole string
	
	digits.moveFront();
	while(i>=0){
		string node; 
		for(int j = 0; j<power; j++){
			string temp;
			if(i>=0){
				temp = numbers[i];
				temp += node;
				node = temp;
				i--;
			}
		}
		x = stol(node,nullptr,10);
		digits.insertAfter(x);
	}

	// if there is 0 at the front of the digits list
	// delete the 0s
	digits.moveFront();
	while(digits.front() == 0){
		digits.eraseAfter();
	}
}

BigInteger::BigInteger(const BigInteger& N){
	this->digits = N.digits;
	this->signum = N.signum;
}

int BigInteger::sign() const{
	return signum;
}

int BigInteger::compare(const BigInteger& N) const{
	// if sign of these 2 are not the same
	// compare with sign
	if(sign() != N.sign()){
		if(sign() == 1 && N.sign() <=0){
			return 1;
		}
		else{
			return -1;
		}
	}
	else{
		// if both of them are empty
		// return 0
		if(sign() == 0 && N.sign() == 0){
			return 0;
		}
		// check with length
		// if this length > N, return 1
		if(digits.length() > N.digits.length()){
			return 1;
		}
		// if this length < N, return -1
		if(digits.length() < N.digits.length()){
			return -1;
		}

		List A = digits;
		List B = N.digits;
		A.moveFront();
		B.moveFront();
		// loop the whiole list
		while(A.position()!= A.length()){
			ListElement x = A.moveNext(); // ListElement in this
			ListElement y = B.moveNext(); // ListELement in N
			// compare x and y
			if(x!=y){
				if(x>y){
					return 1;
				}
				else{
					return -1;
				}
			}
		}	
		return 0;
	}
}

void BigInteger::makeZero(){
	digits.moveFront();
	// while length is not 0, keep delete
	while(digits.length()!=0){
		digits.eraseAfter();
	}
	signum = 0;
}

void BigInteger::negate(){
	if(sign() == 0){
		return;
	}
	else{
		if(sign() == 1){
			signum = -1;
		}
		else{
			signum = 1;
		}
	}
}

// return the sign of the BigInteger
int normalize(List &A){

	A.moveBack();
	int carry = 0;
	int sig = 1;

	// start normalize from the back of the List
	while(A.position()!=0){
		// store the element
		long x = A.movePrev();

		// if x < 0 && current List position is not 0
		// x += carry from the prev element
		// d is the divisor
		// q is the quotient
		if(x<0){
			x += carry;
		
			long q = x%base;
			long d = x/base;
			carry = -1 * d;
			// since x < 0, set the carry to negative
			if(A.position() != 0){
				carry = -1;
				x = base + q;
			}
		}
		else{
			x += carry;
			long d = x/base;
			long q = x%base;
			// set current element to the quotient
			// set the carry to d
			x = q;
			carry = d;
		}

		A.setAfter(x);
	
		// insert 0 at the front of the List to hold the space for 0
		if((carry != 0) && A.position() == 0){
			A.insertBefore(0);
		}
	}
	if(A.length()!=0){
		// check if the  front is 0
		// if there is 0 at the front
		// keep delete till no more 0
		while(A.length()!=0){
			if(A.front() == 0){
				A.eraseAfter();
			}
			else{
				break;
			}
		}
		// if length() after delete 0s is 0
		// set the sig to 0
		if(A.length() == 0){
			sig = 0;
			return sig;
		}
		// if front is negative
		if(A.front() < 0){
			A.moveFront();
			// flip the sign of the elements in the List
			for(int i = 0; i<A.length(); i++){
				long x = A.moveNext();
				x = -1 * x;
				A.setBefore(x);
			}
			// recursion call to fix the List
			normalize(A);
			// since the front is negative, return -1
			return -1;
		}

		if(A.length() != 0){
			if(A.front() < 0){
				sig = -1;
			}
		}
		
	}
	return sig;
}

BigInteger BigInteger::add(const BigInteger& N) const{
	BigInteger A;

	List a = digits;
	List b = N.digits;

	// check the sign
	// if sign() is -1 and N.sign() is not -1
	// set the elements to positive
	if(sign() == -1 && N.sign() != -1){
		a.moveFront();
		for(int i = 1; i<=a.length();i++){
			long x = a.moveNext();
			x = -1 * x;
			a.setBefore(x);
		}
	}

	// check the sign
	// if N.sign() is -1 and sign() is not -1
	// set the elements to positive
	if(N.sign() == -1 && sign() != -1){
		b.moveFront();
		for(int i = 1; i<=b.length();i++){
			long x = b.moveNext();
			x = -1 * x;
			b.setBefore(x);
		}
	}

	int lenA = a.length();
	int lenB = b.length();

	// if both of the list is empty, return empty A
	if(lenA == 0 && lenB == 0){
		A.signum = 0;
		return A;
	}

	// if length of this list is empty
	// set BigInteger A's digits list to b
	if(lenA == 0){
		A.digits = b;
		return A;
	}

	// if length of N list is empty
	// set BigInteger A's digits list to a
	if(lenB == 0){
		A.digits == a;
		/*
		cout << "b list is empty" <<endl;
		cout << "return this list" <<endl;
		*/
		return A;
	}

	// len is the inner while loop condition
	// if len reach to the shortest length in the 2 list
	// just insert the rest element
	int len = lenA;
	if(lenA > lenB){
		len = lenB;
	}

	a.moveBack();
	b.moveBack();

	int posA = a.position();
	int posB = b.position();

	int sig = 1;
	// if both is < 0, break
	while(posA >= 0 || posB >= 0){
		long dataA = 0;
		long dataB = 0; 
		long data = 0;
		posA = a.position();
		posB = b.position();

		// if list a not reach to the front, get the ListElement
		// else, set posA to -1
		if(posA > 0){
			dataA = a.movePrev();
		}
		else{
			posA = -1;
		}

		// if list a not reach to the front, get the ListElement
		// else, set posB to -1
		if(posB > 0){
			dataB = b.movePrev();
		}
		else{
			posB = -1;
		}

		// if both reaches to its front
		// break the loop
		if(posB == -1 && posA == -1 ){
			break;
		}

		// if the shortest list is not reach to the front. add both data
		// else insert the remaining rest data
		if(len > 0){
			data = dataA + dataB;
			len--;
			A.digits.insertAfter(data);
		}
		else{
			if(posA > 0){
				data = dataA;
			}
			if(posB > 0){
				data = dataB;
			}
			A.digits.insertAfter(data);
		}
	}

	// normalize the BigInteger A's digits list, and set the signum
	sig = normalize(A.digits);
	A.signum = sig;

	// if both of is -1, set signum to -1
	if(N.sign() == -1 && sign() == -1){
		A.signum = -1;
	}

	return A;
}

BigInteger BigInteger::sub(const BigInteger& N) const{
	BigInteger S;
	
	List a = digits;
	List b = N.digits;
	
	// check the sign
	// if sign() is -1 and N.sign() is not -1
	// set the elements to positive
	if(sign() == -1){
		a.moveFront();
		for(int i = 1; i<=a.length();i++){
			long x = a.moveNext();
			x = -1 * x;
			a.setBefore(x);
		}
	}

	// check the sign
	// if N.sign() is -1 and sign() is not -1
	// set the elements to positive
	if(N.sign() == -1){
		b.moveFront();
		for(int i = 1; i<=b.length(); i++){
			long x = b.moveNext();
			x = -1 * x;
			b.setBefore(x);
		}
	}

	int lenA = a.length();
	int lenB = b.length();

	// len is the inner while loop condition
	// if len reach to the shortest length in the 2 list
	// just insert the rest element
	int len = lenA;
	if(lenA > lenB){
		len = lenB;
	}

	a.moveBack();
	b.moveBack();

	int posA = a.position();
	int posB = b.position();

	while(posA >= 0 || posB >= 0){
		long dataA, dataB,data;

		posA = a.position();
		posB = b.position();

		// setting dataA and dataB
		if(posA>0){
			dataA = a.movePrev();
		}
		else{
			posA = -1;
		}
		if(posB>0){
			dataB = b.movePrev();
		}
		else{
			posB = -1;
		}
		
		// if list a not reach to the front, get the ListElement
		// else, set posA to -1
		if(len>0){
			data = dataA - dataB;
			len--;
			S.digits.insertAfter(data);
		}
		else{
			// if A is has the longer length, which means is bigger
			// set data to dataA
			if(posA>0){
				data = dataA;
			}
			if(posB>0){
				data = -1 * dataB;
			}
			if(posA < 0 && posB < 0){
				break;
			}
			S.digits.insertAfter(data);
		}	
	}
	// normalize BigInteger S's list, and set the sign()
	int n = normalize(S.digits);
	S.signum = n;

	return S;
}

// Helper Funtion use to add two List
List addition(List L, List &add){
	List result;

	// normalize the List first
	normalize(L);

	int lenA = L.length();
	int lenB = add.length();
	if(lenB == 0){
		return L;
	}
	int len = lenA;
	if(lenA > lenB){
		len = lenB;
	}

	L.moveBack();
	add.moveBack();
	int posA = L.position();
	int posB = add.position();

	while(posA >= 0 || posB >= 0){
		long dataA, dataB, data;
		posA = L.position();
		posB = add.position();

		if(posA>0){
			dataA = L.movePrev();
		}
		else{
			posA = -1;
		}
		
		if(posB>0){
			dataB = add.movePrev();
		}
		else{
			posB = -1;
		}

		if(len>0){
			data = dataA+dataB;
			len--;
			result.insertAfter(data);
		}
		else{
			if(posA > 0){
				data = dataA;
			}
			if(posB > 0){
				data = dataB;
			}
			if(posB < 0 && posA < 0){
				break;
			}
			result.insertAfter(data);
		}
	}

	normalize(result);

	return result;
}

// Helper funtion uses to multply the list with a scalar
List scalar(List A, long x){
	List result;

	if(A.length() == 0 || x == 0){
		return result;
	}

	A.moveBack();
	while(A.position()!=0){
		long y = A.movePrev();
		long data = x*y;
		result.insertAfter(data);
	}
	return result;
}

BigInteger BigInteger::mult(const BigInteger& N) const{
	BigInteger M;
	List add;
	List top,bot;
	if(N.digits.length() >= digits.length()){
		top = N.digits;
		bot = digits;
	}
	else{
		top = digits;
		bot = N.digits;
	}

	int count = 0;
	
	if(top.length() == 0 || bot.length() == 0){
		return M;
	}

	bot.moveBack();
	
	while(bot.position()!=0){
		long x = bot.movePrev();
		List L = scalar(top,x);
		L.moveBack();
		for(int i = 0; i<count; i++){
			L.insertAfter(0);
		}
		List temp = addition(L,add);
		
		normalize(temp);
		add = temp;
		count++;
		M.digits = add;
	}
	

	normalize(M.digits);
	if(sign() == -1 && N.sign() == -1){
		M.signum = 1;
	}
	else if(sign() == -1 || N.sign() == -1){
		M.signum = -1;
	}
	else{
		M.signum = 1;
	}

	return M;
}


std::string BigInteger::to_string(){

	string s = "";

	if(sign() == -1){
		s = '-';
	}
	if(sign() == 0){
		s = "0";
		return s;
	}

	digits.moveFront();

	for(int i = 1; i<=digits.length(); i++){
		long x = digits.moveNext();

		string z = std::to_string(x);

		if(z.length() != power && i != 1){
			int n = power - z.length();
			for(int i = 0; i < n; i++){
				s += '0';
			}
		}
		s += z;
	}
	return s;
}

std::ostream& operator<<(std::ostream& stream, BigInteger N){
	string s = N.to_string();
	return stream << s;
}

bool operator==( const BigInteger& A, const BigInteger& B){
	int n = A.BigInteger::compare(B);
	if(n == 0){
		return true;
	}
	else{
		return false;
	}

}

bool operator<( const BigInteger& A, const BigInteger& B){
	int n = A.BigInteger::compare(B);
	if(n < 0 ){
		return true;
	}
	else{
		return false;
	}
}

bool operator<=( const BigInteger& A, const BigInteger& B){
	int n = A.BigInteger::compare(B);
	if(n <= 0){
		return true;
	}
	else{
		return false;
	}
}

bool operator>( const BigInteger& A, const BigInteger& B){
	int n = A.BigInteger::compare(B);
	if(n > 0){
		return true;
	}
	else{
		return false;
	}
}

bool operator>=( const BigInteger& A, const BigInteger& B){
	int n = A.BigInteger::compare(B);
	if(n >= 0){
		return true;
	}
	else{
		return false;
	}
}

BigInteger operator+( const BigInteger& A, const BigInteger& B){
	return A.BigInteger::add(B);
}

BigInteger operator+=(BigInteger& A, const BigInteger& B){
	BigInteger temp = A.BigInteger::add(B);
	A.BigInteger::makeZero();
	A = temp;
	return A;
}

BigInteger operator-( const BigInteger& A, const BigInteger& B){
	return A.BigInteger::sub(B);
}

BigInteger operator-=( BigInteger& A, const BigInteger& B){
	A = A.BigInteger::sub(B);
	return A;
}

BigInteger operator*( const BigInteger& A, const BigInteger& B){
	return A.BigInteger::mult(B);
}

BigInteger operator*=( BigInteger& A, const BigInteger& B){
	BigInteger temp = A.BigInteger::mult(B);
	A.BigInteger::makeZero();
	A = temp;
	return A;
}

