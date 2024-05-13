#include <stdio.h>
#include <string.h>
#include <math.h>

#define N 50

// Function prototypes
char *fill_parity(char data1[], int p);
char *error(char data[]);
void receive(char data[]);
void reverseString(char *str);

int main() {
    char data[N];
    int choice;

    do {
        printf("1) Send data\n2) Receive data\n3) Check error\n4) Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Please enter the length of the Data Word: ");
                int data_length;
                scanf("%d", &data_length);

                // Consume the newline character
                getchar();

                printf("Please enter the Data Word one by one:\n");

                for (int i = 0; i < data_length; i++) {
                    scanf("%c", &data[i]);
                }
                data[data_length] = '\0';

                reverseString(data);

                int p = 1;
                while (pow(2, p) < data_length + p + 1) {
                    p++;
                }

                printf("Parity\n1) Even\n2) Odd\nEnter Parity: ");
                int parity_choice;
                scanf("%d", &parity_choice);

                printf("No. of parity bits are: %d\n", p);
                printf("Final data will contain %d bits\n", data_length + p);

                printf("Parity bits positions are:\n");
                for (int i = 1; i <= p; i++) {
                    printf("%d\n", (int)pow(2, i - 1));
                }
                break;

            case 2:
                printf("Data with parity bits: ");
                for (int i = 0; i < data_length + p; i++) {
                    printf("%c", data[i]);
                }
                printf("\n------------------------------------------------------------\n");
                fill_parity(data, p);
                printf("------------------------------------------------------------\n");
                receive(data);
                break;

            case 3:
                printf("1. Enter [a] to pass data without error.\n2. Enter [b] to pass data with error.\n");
                char ch;
                scanf(" %c", &ch);

                switch (ch) {
                    case 'a':
                        receive(data);
                        break;
                    case 'b':
                        error(data);
                        receive(data);
                        break;
                    default:
                        printf("Wrong Input.\n");
                }
                break;

            case 4:
                printf("\n-----------------------Thank You!---------------------------\n\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
 
    } while (choice !=4);

    return 0;
}

char *fill_parity(char data1[], int p) {
    char q[N];

    while (p > 0) {
        int count = 0, a = 0;
        int i = pow(2, p - 1);
        int z = i;

        for (i = z - 1; i < strlen(data1); i++) {
            if (count == z) {
                i = i + z - 1;
                count = 0;
            } else {
                q[a] = data1[i];
                a++;
                count++;
            }
        }

        q[a] = '\0';
        printf("For Parity at %dth: %s\n", z, q);
        count = 0;

        for (i = 0; i < strlen(q); i++) {
            if (q[i] == '1') {
                count++;
            }
        }

        if (count % 2 == 0) {
            data1[z - 1] = '0';
        } else {
            data1[z - 1] = '1';
        }

        printf("Data: %s\n", data1);
        p--;
    }

    return data1;
}

char *error(char data[]) {

    printf("Final data: ");
    for (int d = 0; d < strlen(data); d++) {
        printf("%c", data[d]);
    }

    printf("\n");

    printf("Enter position for switching a bit: ");
    int pos;
    scanf("%d", &pos);

    if (data[pos - 1] == '0') {
        data[pos - 1] = '1';
    } else {
        data[pos - 1] = '0';
    }

    printf("Data after flipping a bit: %s\n", data);

    return data;
}

void receive(char data[]) {
    int i = 0;
    char q[N];
    int arr[N];

    while (strlen(data) > pow(2, i)) {
        i++;
    }

    int y = i;

    while (i != 0) {
        int a = 0, count = 0;
        int s = pow(2, i - 1);

        for (int j = s - 1; j < strlen(data); j++) {
            if (count == s) {
                j = j + s - 1;
                count = 0;
            } else {
                q[a] = data[j];
                a++;
                count++;
            }
        }

        q[a] = '\0';
        printf("For Parity at %dth: %s\n", s, q);
        count = 0;

        for (int k = 0; k < strlen(q); k++) {
            if (q[k] == '1') {
                count++;
            }
        }

        if (count % 2 == 0 && q[0] == '0') {
            arr[i - 1] = 0;
        } else if (count % 2 != 0 && q[0] == '1') {
            arr[i - 1] = 0;
        } else {
            arr[i - 1] = 1;
        }

        i--;
    }

    int flag = 1;

    printf("Resultant Array: ");
    for (int e = y - 1; e >= 0; e--) {
        printf("%d", arr[e]);
        if (arr[e] == 1) {
            flag = 0;
        }
    }

    if (flag == 0) {
        printf("!!! Data Rejected !!!\n");
    } else {
        printf("!!! Data Accepted !!!\n");
    }
    
}

void reverseString(char *str) {
    int length = strlen(str);
    int start = 0;
    int end = length - 1;

    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }
}
