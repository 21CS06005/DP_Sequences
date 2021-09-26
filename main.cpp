#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int* generate_random_alternating_seq(int size) {
  int alt_seq[500];
  cout<<"Alternating sequence generated - "<<endl;
  for(int i = 0; i<size; i++) {
    alt_seq[i] = (rand() % 100 + 1);
    cout<<alt_seq[i]<<"\t";
  }
  cout<<endl;
  return alt_seq;
}

// Check if sub-string is palindrome - Yes or No
bool is_palindrome(char seq[], int start_index, int end_index) {
  // Single character is always a palindrome
  if(start_index == end_index)
    return true;
  
  while(start_index < end_index) {
    if(seq[start_index] == seq[end_index]) {
      start_index++;
      end_index--;
    }
    else
      return false; //If the characters are not same, we returns false
  }
  return true;
}

// Counting minimum number of cuts required to make each sub-string as palindrome
int count_palindrome_cut(char seq[], int size) {
  int table[size][size];

  // Initializing the table with length of the string.
  for(int m=0;m<size;m++) {
    for(int n=0;n<size;n++)
      table[m][n] = size;
  }

  // Iterating for each gap - gap being the length of sub-string under consideration
  for(int gap=0; gap<size; gap++) {
    for(int i=0, j=gap; j<size; j++,i++) {
      if(i==j)
        table[i][j] = 0;

      if(!is_palindrome(seq, i, j)) {
        for(int b=i; b<j; b++) {
          int sum = 1 + table[i][b] + table[b+1][j];
          if(table[i][j] > sum)
            table[i][j] = sum;
        }
      }
      else
          table[i][j] = 0;
    }
  }
  return table[0][size-1];
}

// Counting minimum number of insertions required to make string as palindrome
int count_palindrome_add(char seq[], int size) {
  int table[size][size];
  // Initializing table with 0.
  for(int l=0;l<size;l++)
    for(int k=0;k<size;k++)
      table[l][k] = 0;

  // Iterating for each length - length of sub-string under consideration
  for(int len = 1; len < size; len++) {
    int i = 0;
    for(int j=len; j<size; j++) {
      if(seq[i] == seq[j]) {
        table[i][j] = table[i+1][j-1];
      }
      else {
        table[i][j] = min(table[i][j-1], table[i+1][j]) + 1;
      }
      i++;
    }
  }
  return table[0][size-1];
}

// Counting number of alternate sequences
int count_alternate_seq(int seq[], int size) {
  int last_dif = 0, alternate_count=1;

  // Iterating over the input array of integers
  for(int i=1; i< size; i++) {
    //Checking if current difference is positive and last difference was negative
    if(seq[i] > seq[i-1] && last_dif == -1) {
      alternate_count++;
      last_dif = 1;
    }
    //Checking if current difference is positive and last difference was negative
    else if(seq[i] < seq[i-1] && last_dif == 1) {
      alternate_count++;
      last_dif = -1;
    }
    //Checking if upto now all numbers are equal
    else if(last_dif == 0){
      if(seq[i] < seq[i-1]) {
        alternate_count++;
        last_dif = -1;
      }
      else if(seq[i] > seq[i-1]) {
        alternate_count++;
        last_dif = 1;
      }
    }
  }
  return alternate_count;
}

int main() {
  char seq[500];
  int size_alternate_seq;
  srand(time(0));

  cout<<"Enter the string to be made a palindrome -"<<endl;
  cin>>seq;

  cout<<"Enter the size of the alternating sequence - "<<endl;
  cin>>size_alternate_seq;
  
  // Alternating sequence
  int* alternate_seq = generate_random_alternating_seq(size_alternate_seq);
  // Mininum number of insertions for making the string a palindrome
  int no_of_insertions = count_palindrome_add(seq, strlen(seq));
  // Mininum number of cuts for making each sub-string a palindrome
  int no_of_cut = count_palindrome_cut(seq, strlen(seq));
  // Number of alternating sequence
  int no_of_alternating_seq = count_alternate_seq(alternate_seq, size_alternate_seq);

  cout<<"Min number of insertions = "<<no_of_insertions<<endl;
  cout<<"Min number of cuts = "<<no_of_cut<<endl;
  cout<<"Count of alternating sequences = "<<no_of_alternating_seq<<endl;
}
