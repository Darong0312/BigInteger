/****************************************************************************************
*  Darong Li, dli97
*  2022 Winter CSE101 PA5
*  List.cpp
*  List ADT
*****************************************************************************************/

#include <iostream>
#include <string>
#include <stdexcept>

#include "List.h"

using namespace std;

//Node constructor
List::Node::Node(ListElement x){
	data = x;
	next = nullptr;
	prev = nullptr;
}

List::List(){
	frontDummy = new Node(-1);
	backDummy = new Node(-1);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	frontDummy->prev = nullptr;
	backDummy->next = nullptr;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
}


List::List(const List& L){
	this->frontDummy = new Node(-1);
	this->backDummy = new Node(-1);
	this->frontDummy->next = this->backDummy;
	this->backDummy->prev = this->frontDummy;
	this->pos_cursor = 0;
	this->num_elements = 0;

	if(L.length()!=0){
		Node *N = L.frontDummy->next;

		int j = 0;

		while(j != L.length()){
			ListElement x = N->data;
			this->insertBefore(x);
			N = N->next;
			j++;
		}

	}
}

List::~List(){
	this->moveFront();
	while(length() != 0){
		this->eraseAfter();
	}
	
	delete this->frontDummy;
	delete this->backDummy;

}

int List::length() const{
	return (num_elements);
}

ListElement List::front() const{
	if(length()==0){
		throw std::length_error("List : front(): empty List");
	}
	return (frontDummy->next->data);
}

ListElement List::back() const{
	if(length()==0){
		throw std::length_error("List : back(): empty List");
	}
	return (backDummy->prev->data);
}

int List::position() const{
	return (pos_cursor);
}

ListElement List::peekNext() const{
	if(position() >= length()){
		throw std::range_error("List : peekNext(): pos >= length");
	}
	return (afterCursor->data);
}

ListElement List::peekPrev() const{
	if(position() <= 0){
		throw std::range_error("List : peekPrev(): pos <= 0");
	}
	return (beforeCursor->data);
}

void List::clear(){
	moveFront();
	while(length()!=0){
		eraseAfter();
	}
}

void List::moveFront(){
	if(length()==0){
		beforeCursor = frontDummy;
		afterCursor = backDummy;
	}
	else{
		beforeCursor = frontDummy;
		afterCursor = frontDummy->next;
		afterCursor->prev = beforeCursor;
		beforeCursor->next = afterCursor;
	}
	pos_cursor = 0;
}

void List::moveBack(){
	if(this->length()==0){
		beforeCursor = frontDummy;
		afterCursor = backDummy;
	}
	else{
		beforeCursor = backDummy->prev;
		afterCursor = backDummy;
		
		afterCursor->prev = beforeCursor;
		beforeCursor->next = afterCursor;
	}
	pos_cursor = length();
}

ListElement List::moveNext(){
	if(position() >= length()){
		throw std::range_error("List : moveNext(): pos_cursor >= length");
	}
	ListElement x = afterCursor->data;

	Node* N = afterCursor;
	beforeCursor = N;
	afterCursor = N->next;

	pos_cursor++;
	return x;
}

ListElement List::movePrev(){
	if(position() <= 0){
		throw std::range_error("List : movePrev(): pos_cursor <= 0");
	}
	ListElement x = beforeCursor->data;

	Node* N = beforeCursor;
	beforeCursor = N->prev;
	afterCursor = N;

	pos_cursor--;
	return x;
}

void List::insertBefore(ListElement x){
	Node* N = new Node(x);

	if(length() == 0){
		frontDummy->next = N;
	
		backDummy->prev = N;
	
		N->prev = frontDummy;

		N->next = backDummy;

		beforeCursor = N;
	
		afterCursor = backDummy;
	}
	else{
		beforeCursor->next = N;
		afterCursor->prev = N;
		N->prev = beforeCursor;
		N->next = afterCursor;
		beforeCursor = N;
	}
	pos_cursor++;
	num_elements++;
}

void List::insertAfter(ListElement x){
	Node* N = new Node(x);

	if(length() == 0){
		frontDummy->next = N;
		backDummy->prev = N;
		N->prev = frontDummy;
		N->next = backDummy;
		beforeCursor = frontDummy;
		afterCursor = N;
	}
	else{
		beforeCursor->next = N;
		afterCursor->prev = N;
		N->prev = beforeCursor;
		N->next = afterCursor;
		afterCursor = N;
	}
	num_elements++;
	N = frontDummy->next;
}

void List::setAfter(ListElement x){
	if(position() >= length()){
		throw std::range_error("List : setAfter(): pos_cursor >= length");
	}
	afterCursor->data = x;
}

void List::setBefore(ListElement x){
	if(position() <= 0){
		throw std::range_error("List : setBefore(): pos_cursor <= 0");
	}
	beforeCursor->data = x;
}

void List::eraseAfter(){
	if(position() >= length()){
		throw std::range_error("List : eraseAfter(): pos_cursor >= length");
	}

	Node* N = afterCursor;

	N->next->prev = N->prev;
	N->prev->next = N->next;
	beforeCursor->next = N->next;
	afterCursor = N->next;
	afterCursor->prev = beforeCursor;
	delete N;
	num_elements--;
}

void List::eraseBefore(){
	if(position() <= 0){
		throw std::range_error("List : eraseAfter(): pos_cursor <= 0");
	}
	Node* N = beforeCursor;
	afterCursor->prev = N->prev;
	beforeCursor = N->prev;
	beforeCursor->next = afterCursor;
	delete N;
	num_elements--;
	pos_cursor--;
}

int List::findNext(ListElement x){
	if(length() == 0){
		return -1;
	}
	Node* N = afterCursor;
	int j = position();
	while(N != backDummy){
		ListElement cmp = N->data;
		j++;
		if(cmp == x){
			beforeCursor = N;
			afterCursor = N->next;
			pos_cursor = j;
			return j;
		}
		N = N->next;
	}
	pos_cursor = length();
	beforeCursor = backDummy->prev;
	afterCursor = backDummy;
	return -1;
}

int List::findPrev(ListElement x){
	if(length() == 0){
		return -1;
	}

	Node* N = beforeCursor;

	int j = position();
	while(N != frontDummy){
		ListElement cmp = N->data;
		j--;
		if(cmp == x){
			beforeCursor = N->prev;
	
			afterCursor = N;

			pos_cursor = j;
			return j;
		}
		N = N->prev;
	}

	pos_cursor = 0;
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;

	return -1;
}

void List::cleanup(){
	Node* N = frontDummy->next;
	int pos = 1;
	int len = length();
	while(pos != len){
		int j = pos;
		
		Node* cmp = N->next;
		ListElement x = N->data;
		int len1 = length();

		while(j <= len1){
			ListElement y = cmp->data;
			
			if(x==y){
				Node* temp = cmp;

				cmp->prev->next = cmp->next;
				cmp->next->prev = cmp->prev;
				cmp = cmp->next;

				delete temp;

				if(j<=position()){
					if(j == position()){
						beforeCursor = cmp->prev;
					}
					pos_cursor--;
				}
				else if(j == position()+1){
					afterCursor = cmp;
				}

				len1--;
				num_elements--;
			}
			else{
				cmp = cmp->next;
			}
			j++;
		}
		pos++;
		len = length();

		if(pos!=len){
			N = N->next;
		}
		else{
			break;
		}
	}
}

List List::concat(const List& L) const{
	List cc;
	cc.moveFront();
	cc.num_elements = 0;
	if(this->length()!=0){
		Node* N = frontDummy->next;
		int j = 0;
		while(j!=length() && N != backDummy){
			cc.insertAfter(N->data);
			cc.moveNext();
			N = N->next;
			j++;
		}
	}
	if(L.length()!=0){
		Node* E = L.frontDummy->next;
		int j = 0;
		while(j != L.length() && E!= L.backDummy){
			cc.insertAfter(E->data);
			cc.moveNext();
			E = E->next;
			j++;
		}
	}
	cc.pos_cursor = 0;
	
	cc.beforeCursor = cc.frontDummy;
	
	cc.afterCursor = cc.frontDummy->next;

	return cc;
}

std::string List::to_string() const{
	Node* N = frontDummy->next;
	std::string s = "";

	for(int i = 0; i<length(); i++){
		s += std::to_string(N->data) + " ";
		N = N->next;
	}
	return s;
}

bool List::equals(const List& R) const{
	if(length() != R.length()){
		return false;
	}
	Node* A = frontDummy->next;
	Node* B = R.frontDummy->next;

	while(A != backDummy){
		ListElement x = A->data;
		ListElement y = B->data;
		if(x!=y){
			return false;
		}
		A = A->next;
		B = B->next;
	}
	return true;
}

std::ostream& operator<<(std::ostream& stream, const List& L){
	return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
	return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
	if(this != &L){
		List temp = L;
		std::swap(frontDummy,temp.frontDummy);
		std::swap(backDummy,temp.backDummy);
		std::swap(beforeCursor,temp.beforeCursor);
		std::swap(afterCursor,temp.afterCursor);
		std::swap(pos_cursor,temp.pos_cursor);
		std::swap(num_elements,temp.num_elements);
	}
	return *this;
}

// add append(), prepend()?, deleteFront(), deleteback()?
