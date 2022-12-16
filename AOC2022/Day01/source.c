#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

void readFromFile(int numbers[], int *length);
void sort(int numbers[], int length);

int main()
{
    int numbers[1000];
    int length = 0;

    readFromFile(numbers, &length);
    sort(numbers, length);

    int part1 = numbers[0];
    int part2 = numbers[0] + numbers[1] + numbers[2];
    printf("Total of top 1 calories: %d\n", part1);
    printf("Total of top 3 calories: %d", part2);
    
    return 0;
}

void readFromFile(int numbers[], int *length)
{
    FILE *file = fopen("input.txt", "r");

  if(!file)
  {
    printf("Error: unable to open file.\n");
    exit(EXIT_FAILURE);
  }
  
  char line[256];
  int sum = 0;
  
  while(fgets(line, sizeof(line),file))
  {
    if(strcmp(line,"\n") == 0)
    {
        numbers[*length] = sum;
        sum = 0;
        *length += 1;
    }
    else
    {
        sum += atoi(line);
    }
  }

  fclose(file);
}

void sort(int numbers[], int length)
{
    for(int i = 0; i < length; i++)
    {
        for(int j = 1; j < length; j++)
        {
            if(numbers[j - 1] < numbers[j])
            {
                int temp = numbers[j - 1];
                numbers[j - 1] = numbers[j]; 
                numbers[j] = temp;
            }
        }
    }
}