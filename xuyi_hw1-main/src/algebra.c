#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    if (a.rows != b.rows || a.cols != b.cols)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    Matrix c = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            c.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return c;
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    if (a.rows != b.rows || a.cols != b.cols)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    Matrix c = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            c.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }
    return c;
}
Matrix mul_matrix(Matrix a, Matrix b)
{
    if (a.cols != b.rows)
    {
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        return create_matrix(0, 0);
    }
    Matrix c = create_matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < b.cols; j++)
        {
            c.data[i][j] = 0;
            for (int k = 0; k < a.cols; k++)
            {
                c.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return c;
}
Matrix scale_matrix(Matrix a, double k)
{
    Matrix c = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            c.data[i][j] = a.data[i][j] * k;
        }
    }
    return c;
}

Matrix transpose_matrix(Matrix a)
{   
    Matrix c = create_matrix(a.cols, a.rows);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            c.data[j][i] = a.data[i][j];
        }
    }
    return c;
}
double det_matrix(Matrix a)
{
    if (a.rows != a.cols)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    if (a.rows == 1)
    {
        return a.data[0][0];
    }
    if (a.rows == 2)
    {
        return a.data[0][0] * a.data[1][1] - a.data[0][1] * a.data[1][0];
    }
    if (a.rows == 3)
    {
        return a.data[0][0] * (a.data[1][1] * a.data[2][2] - a.data[1][2] * a.data[2][1]) -
               a.data[0][1] * (a.data[1][0] * a.data[2][2] - a.data[1][2] * a.data[2][0]) +
               a.data[0][2] * (a.data[1][0] * a.data[2][1] - a.data[1][1] * a.data[2][0]);
    }
    // 计算行列式的递归方法
    double det = 0;
    for (int i = 0; i < a.cols; i++)
    {
        Matrix sub_matrix = create_matrix(a.rows - 1, a.cols - 1);
        for (int j = 1; j < a.rows; j++)
        {
            for (int k = 0; k < a.cols; k++)
            {
                if (k < i)
                {
                    sub_matrix.data[j - 1][k] = a.data[j][k];
                }
                else if (k > i)
                {
                    sub_matrix.data[j - 1][k - 1] = a.data[j][k];
                }
            }
        }
        det += pow(-1, i) * a.data[0][i] * det_matrix(sub_matrix);
    }
    return det;
}

Matrix inv_matrix(Matrix a)
{
    if (a.rows != a.cols)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return create_matrix(0, 0);
    }
    double det = det_matrix(a);
    if (det == 0)
    {
        printf("Error: The matrix is singular.\n");
        return create_matrix(0, 0);
    }
    Matrix inv = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            Matrix sub_matrix = create_matrix(a.rows - 1, a.cols - 1);
            for (int k = 0; k < a.rows; k++)
            {
                for (int l = 0; l < a.cols; l++)
                {
                    if (k != i && l != j)
                    {
                        sub_matrix.data[k - (k > i)][l - (l > j)] = a.data[k][l];
                    }
                }
            }
            inv.data[j][i] = pow(-1, i + j) * det_matrix(sub_matrix) / det;
        }
    }
    return inv;
}

int rank_matrix(Matrix a) {
    int rank = 0;
    for (int i = 0; i < a.rows; i++) {
        if (a.data[i][rank] == 0) {
            int c;
            for (c = i + 1; c < a.rows; c++) {
                if (a.data[c][rank] != 0) {
                    for (int j = 0; j < a.cols; j++) {
                        double temp = a.data[i][j];
                        a.data[i][j] = a.data[c][j];
                        a.data[c][j] = temp;
                    }
                    break;
                }
            }
            if (c == a.rows) {
                continue;
            }
        }
        for (int c = i + 1; c < a.rows; c++) {
            double factor = a.data[c][rank] / a.data[i][rank];
            for (int j = rank; j < a.cols; j++) {
                a.data[c][j] -= factor * a.data[i][j];
            }
        }
        rank++;
        if (rank == a.cols) {
            break;
        }
    }
    return rank;
}


double trace_matrix(Matrix a)
{
    if (a.rows != a.cols)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    double trace = 0;
    for (int i = 0; i < a.rows && i < a.cols; i++)
    {
        trace += a.data[i][i];
    }
    return trace;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}