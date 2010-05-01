#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(1)
typedef struct BMPheader{

    //File header
    unsigned short type;
    unsigned int fileSize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset; //54bytes(if ncolours is 0)

    //Info header
    unsigned int infoheaderSize;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bits;
    unsigned int compression;
    unsigned int imageSize;
    unsigned int xresolution;
    unsigned int vresolution;
    unsigned int ncolours;
    unsigned int importantcolours;

}BMPheader;

#pragma pack(0)

typedef struct node{
	char w; //value of gray level = 0-255
	float rate; //count of the gray level
	struct node *left,*right;
}Node;

static int cmp(const void *p1, const void *p2)
{
	/* The actual arguments to this function are "pointers to
	   pointers to char", but strcmp(3) arguments are "pointers
	   to char", hence the following cast plus dereference */

	return ((unsigned int)p1 > (unsigned int)p2);
}

int main(){

	FILE *fp1, *fp2;
	char *picBuf1, *picBuf2; // 1 byte of pexil
	int picCount1[256];
	int picCount2[256];
	int ori_picCount1[256];
	BMPheader headerBuf;
	int i;
	long FileSize, ImgSize, ImgOffset;

	fp1 = fopen("test1.bmp","rb");
	fp2 = fopen("test2.bmp","rb");

	if( !fp1 )
		printf("Open test1.bmp is fault!\n");
	if( !fp2 )
		printf("Open test2.bmp is fault!\n");
	//get picture's filesize
	fseek(fp1, 0, SEEK_END);
	FileSize = ftell(fp1);
	//ImgSize = FileSize - sizeof(BMPheader);

	fseek(fp1, 0, SEEK_SET);
	fread(&headerBuf, sizeof(BMPheader), 1, fp1);
    //test=============================
	printf("offset = %d\n", headerBuf.offset);
	//test=============================
	ImgSize = headerBuf.imageSize;
	ImgOffset = headerBuf.offset;
	fseek(fp1, ImgOffset, SEEK_SET);
	fseek(fp2, ImgOffset, SEEK_SET);

	picBuf1 = (char*)malloc(ImgSize);
	picBuf2 = (char*)malloc(ImgSize);
	fread( picBuf1, ImgSize, 1, fp1);
	fread( picBuf2, ImgSize, 1, fp2);
	
	
	for( i=0 ; i<ImgSize ; i++){
		picCount1[ (int)picBuf1[i] ]++;
		picCount2[ (int)picBuf2[i] ]++;
	}

	memcpy(picCount1, ori_picCount1, sizeof(picCount1));

	qsort(picCount1, 256, sizeof(picCount1[1]), cmp);


	//Node *list;



	
	//printf("1   , %d\n", picCount1[1]);
	//printf("2 , %d\n", picCount1[2]);
	//printf("1 , %d\n", picCount2[1]);
	


	free(picBuf1);
	free(picBuf2);
	return 0;
}
