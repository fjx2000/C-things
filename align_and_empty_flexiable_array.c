/*********************************************************************************************************************************
This thing is to demonstrate different align options and empty array size.
**********************************************************************************************************************************/

/* size 4 */
struct line {
    int length;
    char contents[0];
};

/* size 5 */
struct line1 {
    int length;
    char contents[1];
} __attribute__((packed));


/* size 6 */
#pragma pack(2)
struct line2 {
    int length;
    char contents[1];
};

/* size 4 */
#pragma pack()
struct lineEmpty {
    int length;
    char contents[];
};

int main()
{
    struct line *thisline = (struct line *)
                            malloc (sizeof (struct line) + 10);
    thisline->length = 10;

    printf("size of line : %d \n", sizeof(struct line));
    printf("size of line1 : %d \n", sizeof(struct line1));
    printf("size of line2 : %d \n", sizeof(struct line2));
    printf("size of lineEmpty : %d \n", sizeof(struct lineEmpty));
    return 1;
}


/*************************************************************************************************************************************
esekilxxen2768: ~/test_c  > gcc -std=c11 align_and_empty_flexiable_array.c
align_and_empty_flexiable_array.c: In function 'main':
align_and_empty_flexiable_array.c:25:5: warning: implicit declaration of function 'printf' [-Wimplicit-function-declaration]
     printf("size of line : %d \n", sizeof(struct line));
     ^
align_and_empty_flexiable_array.c:25:5: warning: incompatible implicit declaration of built-in function 'printf' [enabled by default]
esekilxxen2768: ~/test_c  > ./a.out
size of line : 4 
size of line1 : 5 
size of line2 : 6 
size of lineEmpty : 4 
esekilxxen2768: ~/test_c  > 

**************************************************************************************************************************************/
