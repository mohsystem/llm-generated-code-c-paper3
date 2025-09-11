#include<stdio.h>
#include<stdbool.h>
#define MAX 1000

int stack[MAX];
int top = -1;

bool push(int x) {
   if (top >= (MAX-1)) {
      printf("Stack Overflow");
      return false;
   } else {
      stack[++top] = x;
      return true;
   }
}

int pop() {
   if (top < 0) {
      printf("Stack Underflow");
      return 0;
   } else {
      int x = stack[top--];
      return x;
   }
}

int peek() {
   if (top < 0) {
      printf("Stack is Empty");
      return 0;
   } else {
      int x = stack[top];
      return x;
   }
}

int main() {
   push(10);
   push(20);
   push(30);
   printf("%d popped from stack\n", pop());
   printf("Top element is: %d\n", peek());
   return 0;
}