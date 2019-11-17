#include "pch.h"
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <iostream>

using namespace std;

int index1, index2 = 0;

int Array[36] = { 1,4 ,1, 2, 64, 4, 2, 3, 25, 8, 49, 2, 9, 1, 3, 16, 2, 3, 3, 10, 2, 16, 24, 2, 3, 9, 2, 3, 4, 2, 3, 8, 2, 9, 1, 3 };

int main()
{
	setlocale(LC_ALL, "Russian");
	setlocale(LC_ALL, "rus");

	MPI_Init(0, 0); //инициализация MPI
	int rank, size; //узнаем ранг каждого процесса и их общее число
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int result_array_1[36];
	int result_array_2[36];
	int i = 1;
	memset(result_array_1, 0, sizeof(result_array_1));
	memset(result_array_2, 0, sizeof(result_array_2));
	if (rank != 0)
	{
		if (rank == 1)
		{
			int p = (rank - 1) * 18;

			for (int j = p; j < p + 18; j++)
			{

				for (int i = 0; i < 36; i++)
				{

					if (Array[j] == (Array[i] * Array[i]))
					{
						result_array_1[index1] = Array[j];

						index1++;
						printf("%d ", result_array_1[index1 - 1]);
						break;
					}
				}
			}
		}
		else
		{
			int p = (rank - 1) * 18;

			for (int j = p; j < p + 18; j++)
			{

				for (int i = 0; i < 36; i++)
				{

					if (Array[j] == (Array[i] * Array[i]))
					{
						result_array_2[index2] = Array[j];

						index2++;
						printf("%d ", result_array_2[index2 - 1]);
						break;
					}
				}
			}
		}

	}

	if (rank != 0)
	{
		if (rank == 1)
			MPI_Send(&result_array_1, 36, MPI_INT, 0, 0, MPI_COMM_WORLD);
		if (rank == 2)
			MPI_Send(&result_array_2, 36, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	//нулевой процесс принимает все сообщения и выводит общую сумму
	if (rank == 0)
	{
		int buf[36]; //для приема
		MPI_Status status;
		for (i = 0; i < size - 1; i++)
		{
			MPI_Recv(&buf, 36, MPI_INT, MPI_ANY_SOURCE,
				MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			printf("\n Kvadraty proizvol'nih prostih chisel: ");
			for (int i = 0; i < 36; i++)
			{
				if (buf[i] != 0)
				{
					printf("%d ", buf[i]);
				}
			}
		}

	}

	MPI_Finalize();
	return 1;
}

