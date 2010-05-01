#include <stdio.h>
#include <stdlib.h>

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
	char w;
	float rate;
	struct node *left,*right;
}Node;

int main(){

	FILE *fp1, *fp2;
	char *picBuf1, *picBuf2; // 1 byte of pexil
	int picCount1[256];
	int picCount2[256];
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

	int total1,total2;
	for( i=0 ; i<256 ;i++){
		total1 += picCount1[i];
		total2 += picCount2[i];
	}
	printf("total1 = %d\n total2 = %d\n",ta

	
	//printf("1   , %d\n", picCount1[1]);
	//printf("2 , %d\n", picCount1[2]);
	//printf("1 , %d\n", picCount2[1]);
	


	free(picBuf1);
	free(picBuf2);
	return 0;
}
