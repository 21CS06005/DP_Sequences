#include <iostream>
#include <bits/stdc++.h>
using namespace std;

bool is_palindrome(char seq[], int start_index, int end_index) {
  
  if(start_index == end_index)
    return true;
  
  while(start_index < end_index) {
    if(seq[start_index] == seq[end_index]) {
      start_index++;
      end_index--;
    }
    else
      return false;
  }
  return true;
}

int count_palindrome_cut(char seq[], int size) {
  int table[size][size];

  for(int m=0;m<size;m++) {
    for(int n=0;n<size;n++)
      table[m][n] = size;
  }

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

int count_palindrome_add(char seq[], int size) {
  int table[size][size];
  for(int l=0;l<size;l++)
    for(int k=0;k<size;k++)
      table[l][k] = 0;

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

int count_alternate_seq(int seq[], int size) {
  int last_dif = 0, alternate_count=1;
  for(int i=1; i< size; i++) {
    if(seq[i] > seq[i-1] && last_dif == -1) {
      alternate_count++;
      last_dif = 1;
    }
    else if(seq[i] < seq[i-1] && last_dif == 1) {
      alternate_count++;
      last_dif = -1;
    }
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
  char seq[] = "atyytamngerttreh";
  int alternate_seq[] = {1,7,4,9,2,5};

  int no_of_insertions = count_palindrome_add(seq, strlen(seq));
  int no_of_cut = count_palindrome_cut(seq, strlen(seq));
  int no_of_alternating_seq = count_alternate_seq(alternate_seq, sizeof(alternate_seq)/sizeof(int));

  cout<<"Min number of insertions = "<<no_of_insertions<<endl;
  cout<<"Min number of cuts = "<<no_of_cut<<endl;
  cout<<"Count of alternating sequences = "<<no_of_alternating_seq<<endl;
}
