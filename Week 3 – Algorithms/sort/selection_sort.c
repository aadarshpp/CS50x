void selection_sort(int* array, int size)
{
  for (int i = 0; i < size; i++)
  {
    int minIndex = i;
    
    // Find the index of the smallest element in the unsorted portion
    for (int j = i + 1; j < size; j++)
    {
      if (array[j] < array[minIndex])
          minIndex = j;
    }

    // Swap the smallest element with the first unsorted element
    int temp = array[i];
    array[i] = array[minIndex];
    array[minIndex] = temp;
  }
}
