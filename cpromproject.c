#include <stdio.h>
#include <stdlib.h>

#define ROWS 25
#define COLS 50

char picture[ROWS][COLS];

/* Function Prototypes */

void initializePicture();
void displayPicture();

void drawRectangle(int row, int col, int width, int height);
void drawLine(int row1, int col1, int row2, int col2);
void drawTriangle(int row1, int col1,
                  int row2, int col2,
                  int row3, int col3);
void drawCircle(int centerRow, int centerCol, int radius);

void deleteRectangle(int row, int col, int width, int height);
void deleteLine(int row1, int col1, int row2, int col2);
void deleteTriangle(int row1, int col1,
                    int row2, int col2,
                    int row3, int col3);
void deleteCircle(int centerRow, int centerCol, int radius);

void setPixel(int row, int col, char ch);

/* Main Function */

int main()
{
    int choice;

    initializePicture();

    do
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Draw Rectangle\n");
        printf("2. Draw Line\n");
        printf("3. Draw Triangle\n");
        printf("4. Draw Circle\n");
        printf("5. Delete Rectangle\n");
        printf("6. Delete Line\n");
        printf("7. Delete Triangle\n");
        printf("8. Delete Circle\n");
        printf("9. Display Picture\n");
        printf("10. Clear Picture\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            {
                int row, col, width, height;

                printf("Enter Row and Column: ");
                scanf("%d%d", &row, &col);

                printf("Enter Width and Height: ");
                scanf("%d%d", &width, &height);

                drawRectangle(row, col, width, height);
                break;
            }

            case 2:
            {
                int row1, col1, row2, col2;

                printf("Enter Starting Point: ");
                scanf("%d%d", &row1, &col1);

                printf("Enter Ending Point: ");
                scanf("%d%d", &row2, &col2);

                drawLine(row1, col1, row2, col2);
                break;
            }

            case 3:
            {
                int row1, col1, row2, col2, row3, col3;

                printf("Enter First Vertex: ");
                scanf("%d%d", &row1, &col1);

                printf("Enter Second Vertex: ");
                scanf("%d%d", &row2, &col2);

                printf("Enter Third Vertex: ");
                scanf("%d%d", &row3, &col3);

                drawTriangle(row1, col1, row2, col2, row3, col3);
                break;
            }

            case 4:
            {
                int centerRow, centerCol, radius;

                printf("Enter Center Coordinates: ");
                scanf("%d%d", &centerRow, &centerCol);

                printf("Enter Radius: ");
                scanf("%d", &radius);

                drawCircle(centerRow, centerCol, radius);
                break;
            }

            case 5:
            {
                int row, col, width, height;

                printf("Enter Row and Column: ");
                scanf("%d%d", &row, &col);

                printf("Enter Width and Height: ");
                scanf("%d%d", &width, &height);

                deleteRectangle(row, col, width, height);
                break;
            }

            case 6:
            {
                int row1, col1, row2, col2;

                printf("Enter Starting Point: ");
                scanf("%d%d", &row1, &col1);

                printf("Enter Ending Point: ");
                scanf("%d%d", &row2, &col2);

                deleteLine(row1, col1, row2, col2);
                break;
            }

            case 7:
            {
                int row1, col1, row2, col2, row3, col3;

                printf("Enter First Vertex: ");
                scanf("%d%d", &row1, &col1);

                printf("Enter Second Vertex: ");
                scanf("%d%d", &row2, &col2);

                printf("Enter Third Vertex: ");
                scanf("%d%d", &row3, &col3);

                deleteTriangle(row1, col1, row2, col2, row3, col3);
                break;
            }

            case 8:
            {
                int centerRow, centerCol, radius;

                printf("Enter Center Coordinates: ");
                scanf("%d%d", &centerRow, &centerCol);

                printf("Enter Radius: ");
                scanf("%d", &radius);

                deleteCircle(centerRow, centerCol, radius);
                break;
            }

            case 9:
                displayPicture();
                break;

            case 10:
                initializePicture();
                printf("Picture Cleared Successfully\n");
                break;

            case 0:
                printf("Program Terminated\n");
                break;

            default:
                printf("Invalid Choice\n");
        }

    } while(choice != 0);

    return 0;
}

/* Function Definitions */

void initializePicture()
{
    int i, j;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            picture[i][j] = '_';
        }
    }
}

void displayPicture()
{
    int i, j;

    printf("\n");

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            printf("%c ", picture[i][j]);
        }
        printf("\n");
    }
}

void setPixel(int row, int col, char ch)
{
    if(row >= 0 && row < ROWS &&
       col >= 0 && col < COLS)
    {
        picture[row][col] = ch;
    }
}

void drawRectangle(int row, int col, int width, int height)
{
    int i;

    for(i = 0; i < width; i++)
    {
        setPixel(row, col + i, '*');
        setPixel(row + height - 1, col + i, '*');
    }

    for(i = 0; i < height; i++)
    {
        setPixel(row + i, col, '*');
        setPixel(row + i, col + width - 1, '*');
    }
}

void drawLine(int row1, int col1, int row2, int col2)
{
    int i;

    if(row1 == row2)
    {
        if(col1 > col2)
        {
            int temp = col1;
            col1 = col2;
            col2 = temp;
        }

        for(i = col1; i <= col2; i++)
        {
            setPixel(row1, i, '*');
        }
    }
    else if(col1 == col2)
    {
        if(row1 > row2)
        {
            int temp = row1;
            row1 = row2;
            row2 = temp;
        }

        for(i = row1; i <= row2; i++)
        {
            setPixel(i, col1, '*');
        }
    }
}

void drawTriangle(int row1, int col1,
                  int row2, int col2,
                  int row3, int col3)
{
    drawLine(row1, col1, row2, col2);
    drawLine(row2, col2, row3, col3);
    drawLine(row3, col3, row1, col1);
}

void drawCircle(int centerRow, int centerCol, int radius)
{
    int row, col;

    for(row = 0; row < ROWS; row++)
    {
        for(col = 0; col < COLS; col++)
        {
            int distance;

            distance =
                (row - centerRow) * (row - centerRow) +
                (col - centerCol) * (col - centerCol);

            if(distance >= radius * radius - radius &&
               distance <= radius * radius + radius)
            {
                picture[row][col] = '*';
            }
        }
    }
}

void deleteRectangle(int row, int col, int width, int height)
{
    int i;

    for(i = 0; i < width; i++)
    {
        setPixel(row, col + i, '_');
        setPixel(row + height - 1, col + i, '_');
    }

    for(i = 0; i < height; i++)
    {
        setPixel(row + i, col, '_');
        setPixel(row + i, col + width - 1, '_');
    }
}

void deleteLine(int row1, int col1, int row2, int col2)
{
    int i;

    if(row1 == row2)
    {
        if(col1 > col2)
        {
            int temp = col1;
            col1 = col2;
            col2 = temp;
        }

        for(i = col1; i <= col2; i++)
        {
            setPixel(row1, i, '_');
        }
    }
    else if(col1 == col2)
    {
        if(row1 > row2)
        {
            int temp = row1;
            row1 = row2;
            row2 = temp;
        }

        for(i = row1; i <= row2; i++)
        {
            setPixel(i, col1, '_');
        }
    }
}

void deleteTriangle(int row1, int col1,
                    int row2, int col2,
                    int row3, int col3)
{
    deleteLine(row1, col1, row2, col2);
    deleteLine(row2, col2, row3, col3);
    deleteLine(row3, col3, row1, col1);
}

void deleteCircle(int centerRow, int centerCol, int radius)
{
    int row, col;

    for(row = 0; row < ROWS; row++)
    {
        for(col = 0; col < COLS; col++)
        {
            int distance;

            distance =
                (row - centerRow) * (row - centerRow) +
                (col - centerCol) * (col - centerCol);

            if(distance >= radius * radius - radius &&
               distance <= radius * radius + radius)
            {
                picture[row][col] = '_';
            }
        }
    }
}