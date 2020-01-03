#define _CRT_SECURE_NO_WARNINGS // ��� ���������� ������ scanf()
#include <stdio.h>
// ������� ���������� ������ �������
void selectionSort(int *num, int size)
{
  int min, temp; // ��� ������ ������������ �������� � ��� ������
  for (int i = 0; i < size - 1; i++) 
  {
    min = i; // ���������� ������ �������� ��������
    // ���� ����������� ������� ����� ��������� �� ����� i-���
    for (int j = i + 1; j < size; j++)  // ��� ��������� ��������� ����� i-���
    {
      if (num[j] < num[min]) // ���� ������� ������ ������������,
        min = j;       // ���������� ��� ������ � min
    }
    temp = num[i];      // ������ ������� i-�� � ����������� ��������
    num[i] = num[min];
    num[min] = temp;
  }
}
int main() 
{
  int a[10]; // ��������� ������ �� 10 ���������
  // ������ �������� ��������� �������
  for (int i = 0; i < 10; i++) 
  {
    printf("a[%d] = ", i);
    scanf("%d", &a[i]);
  }
  selectionSort(a, 10);  // �������� ������� ����������
  // ������� ��������������� �������� �������
  for (int i = 0; i<10; i++)
    printf("%d ", a[i]);
  getchar(); getchar();
  return 0;
}
