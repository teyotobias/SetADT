// Set <Project5.cpp>
// EE 312 Project 5 submission by
// <Teyo Turrubiates>
// <ttt2443>
// Slip days used: <1>
// Spring 2022
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way.
 * Please NOTE, you are responsible for ensuring that the functions work correctly in
 * your project solution. Just because the function works correctly in my solution does
 * NOT mean that the function will work correctly in yours.
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that
 * the amount of storage available in the elements[] array is equal to length
 */
/* done for you already */
void destroySet(Set* self) {
    free(self->elements);
}

bool binary_search(int arr[], int start, int end, int n){
    if (start > end){
        return false;
    }
    if(arr[0] == n){
        return true;
    }
    int mid = (start+end)/2;
    if (arr[mid] == n){
        return true;
    }
    else if(n < arr[mid]){
        return binary_search(arr, start, mid-1, n);
    }
    else {
        return binary_search(arr, mid+1,end,n);
    }
}



/* done for you already */
void createEmptySet(Set* self) {
    self->len = 0;
    self->elements = nullptr;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
    self->elements = (int*) malloc(sizeof(int));
    self->elements[0] = x;
    self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
    self->elements = (int*) malloc(other->len * sizeof(int));
    for (int k = 0; k < other->len; k++) {
        self->elements[k] = other->elements[k];
    }
    self->len = other->len;
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
    if (self == other) { return; }

    destroySet(self);
    createCopySet(self, other);
}

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {
    if(binary_search(self->elements, 0, self->len-1, x) == true){
        return true;
    }
    else{
        return false;
    }
    //for(int i = 0;i < self->len;i++){
    //if(self->elements[i]== x){
    //return true;
    // }
    // }
    // return false;
} //problem is that this function does not update (update needed from removeSet)
//does not update len or elements which messes w/removal

/*
 * add x as a new member to this set.
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) { //problem is that it does not stop at right place to insert
    if(isMemberSet(self, x)){ //checks if x is a member of self (a duplicate)
        return;
    }
    self->elements = (int*)realloc(self->elements,(self->len+2)*sizeof(int)); //making space
    if(self->len == 0){ //accounts for situations where there is 0 elements to start -> adds element and increments len
        self->elements[0] = x;
        self->elements[1] = 0; //added
        self->len++;
        return;
    }
    int b = 0;
    for(int i = 0; i<self->len;i++){//checking where x belongs in ordered set
        if(x<self->elements[i]){
            b = i;
            goto jump;
        }
        else {
            b = i + 1; //executed once found the right spot
        }
    }
    jump:
    if(b == 0){//must account for situations where x belongs in 0th place but is not only element -> must move everything up
        for (int z = self->len; z >= 0; z--){
            self->elements[z+1] = self->elements[z];
        }
        self->elements[0] = x;

    }
    else {

        if(b == self->len){
            self->elements[self->len+1] = 0;
            self->elements[self->len] = x;
        }
        else {
            for (int i = self->len; i >= b; i--) { //changed
                self->elements[i + 1] = self->elements[i];
            }
            self->elements[b] = x;
        }
    }
    self->len++;

}


/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
    int b = 0;
    for(int i = 0;self->elements[i] != x && i < self->len;i++){ //edited
        b++;
    }
    if(b == self->len){
        return;
    }

    if(self->elements[b]!= x){
        return;
    }
    for(int i = b+1;i<self->len;i++){
        self->elements[i-1]= self->elements[i];
    }
    self->elements[self->len-1] = 0; //place 0 at end of array CHANGED
    self->len--;

} //updates len and elements according to removal -> ALL SEEMS TO BEHAVE CORRECTLY WITH THIS FUNCTION

/* done for you already */
void displaySet(const Set* self) {
    int k;

    printf("{");

    if (self->len == 0) {
        printf("}");
    }
    else {
        for (k = 0; k < self->len; k += 1) {
            if (k < self->len - 1) {
                printf("%d,", self->elements[k]);
            } else {
                printf("%d}", self->elements[k]);
            }
        }
    }
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
    if(self->len != other->len){
        return false;
    }
    for(int i = 0; i<self->len;i++){
        if(self->elements[i]!=other->elements[i]){
            return false;
        }
    }
    return true;
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
    if(self->len == 0){
        return true;
    }
    if(other->len == 0){
        return false;
    }
    int x = self->len;
    for(int i = 0;i < x;i++){//edited
        if(!binary_search(other->elements, 0, other->len, self->elements[i])){
            return false;
        }
        //if(!isMemberSet(other, self->elements[i])){ //if element i of self is not in other
        //return false;
    }
    //}
    return true;
}

/* done for you */
bool isEmptySet(const Set* self) {
    return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
    if(self->len == 0){ //checks if there is nothing in self
        return;
    }
    if(other->len == 0){ //checks for empty set other, if so clear self
        for(int i = 0;i < self->len;i++){
            self->elements[i] = 0;
            self->len = 0;
        }
        return;
    }
    int f = self->len; //this for loop is changed ->counting from other->len to self->len
    for(int i = 0;i < self->len +1;i++){ //edited -> use x = other->len since self->len changes throughout
        if(!isMemberSet(other, self->elements[i])){
            int c = i;
            if(c == self->len){
                continue;
            }
            else {
                for(int d = c+1;d<self->len;d++){
                    self->elements[d-1]= self->elements[d]; //problem could be here
                }
                self->elements[self->len-1] = 0; //place 0 at end of array CHANGED
                self->len--;
                i--;
            }

            //removeSet(self, self->elements[i]);
        }
    }
}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
    int x = other->len; //added since len changes thru removeSet
    for(int i = 0;i < self->len;i++){ //edited so that it follows other instead of self counter
        if(isMemberSet(other, self->elements[i])){
            int b = i;
            //PROBLEM IS THAT THIS FUNCTION DOES NOT ACT ACCORDING TO REMOVESET UPDATES ->
            //checks to see if number is in set
            //must remove element at this point
            //removeSet(self, other->elements[i]); //REMOVES AN ELEMENT AND DECREMENTS LEN
            if(b == self->len){
                continue;
            }
            else {
                for(int c = b+1;c<self->len;c++){
                    self->elements[c-1]= self->elements[c];
                }
                self->elements[self->len-1] = 0; //place 0 at end of array CHANGED
                self->len--;
                i--;
            }



            //for(int c = i+1;i<self->len;i++){
            //self->elements[i-1]= self->elements[i];
            //}
            //self->elements[self->len-1] = NULL; //place 0 at end of array
            //self->len--;
        }
    }
} //current problem to fix

/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
    for(int i = 0; i < other->len;i++){
        if(!isMemberSet(self, other->elements[i])){ //if element i of other is not in self
            insertSet(self,other->elements[i]);
        }
    }
}