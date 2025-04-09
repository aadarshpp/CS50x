void bubble_sort(int* array, int size)
{
  int swapped;
  for (int i = 0; i < size; i++)
  {
    swapped = 0;
    for (int j = 1; j < size - i; j++)
    {
      if (array[j-1] > array[j])
      {
        // If two adjacent elements are out of order, 
        // we swap them to place them correctly
        int temp = array[j];
        array[j] = array[j-1];
        array[j-1] = temp;

        swapped = 1;
      }
    }

    // If no swaps were made during this pass, 
    // the array is already sorted, so we can exit early
    if (!swapped) break;
  }
}
