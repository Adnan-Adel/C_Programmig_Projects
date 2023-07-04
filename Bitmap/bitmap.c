#include <stdio.h>
#include <string.h>

#define MAX_WIDTH   1920
#define MAX_HEIGHT  1276

#pragma pack(1)

struct Header
{
    char signature[2];
    int size;
    int reserved;
    int offset;
};

struct DIPHeader
{
    int dip_header_size;
    int width;
    int height;
    short int nr_planes;
    short int bitcount;
    int compression;
    int img_size;
    int x_px_pm;
    int y_px_pm;
    int used_colors;
    int important_colors;
};

struct Pixel
{
    // in bitmap format, these pixels are represented in reverse order
    // that's why I started with blue.
    char b;
    char g;
    char r;
};

struct BMPFile
{
    struct Header header;
    struct DIPHeader dheader;
    struct Pixel pixels[MAX_HEIGHT * MAX_WIDTH];
};

enum Color
{
    WHITE,
    BLACK,
    BLUE,
    RED,
    GREEN
};

struct BMPFile bmp;

void draw_point(int x, int y, enum Color color);
void set_contrast(float perc);

int main()
{
    unsigned int index_i= 0;
    struct Header* headerp= &bmp.header;
    struct DIPHeader* dheaderp= &bmp.dheader;
    struct Pixel* pixelp= bmp.pixels;

    strcpy(headerp->signature, "BM");
    headerp->offset= 54;

    dheaderp->width= 8;
    dheaderp->height= 8;
    dheaderp->img_size= 8 * 8 * 3;
    dheaderp->bitcount= 24;
    dheaderp->dip_header_size= 40;

    headerp->size=sizeof(struct Header) + sizeof(struct DIPHeader) + dheaderp->img_size;
    
    unsigned int j= 0;
    
    for(index_i= 8*0; index_i < 8*2; index_i++)
    {
        draw_point(index_i, index_i - j, BLACK);   
        j++;
    }
    for(index_i= 8*2; index_i < 8*4; index_i++)
    {
        draw_point(index_i, index_i - j, WHITE);   
        j++;
    }
    for(index_i= 8*4; index_i < 8*6; index_i++)
    {
        draw_point(index_i, index_i - j, RED);   
        j++;
    }
    for(index_i= 8*6; index_i < 8*8; index_i++)
    {
        draw_point(index_i, index_i - j, RED);   
        j++;
    }

    /* -------------------------------------- write the information of the struct in a file -------------------------------------- */
    FILE* fileptr= fopen("test.bmp", "w");
    fwrite(&bmp, headerp->size, 1, fileptr);
    fclose(fileptr);

    return 0;
}

void draw_point(int x, int y, enum Color color)
{
    int index= y * bmp.dheader.width + x;
    switch(color)
    {
        case WHITE:
            bmp.pixels[index].r = bmp.pixels[index].g = bmp.pixels[index].b = 255;
            break;
        case BLACK:
            bmp.pixels[index].r = bmp.pixels[index].g = bmp.pixels[index].b = 0;
            break;
        case RED:
            bmp.pixels[index].r = 255;
            bmp.pixels[index].g = bmp.pixels[index].b = 0;
        break;
        case BLUE:
            bmp.pixels[index].b = 255;
            bmp.pixels[index].r = bmp.pixels[index].g = 0;
        break;
        case GREEN:
            bmp.pixels[index].g = 255;
            bmp.pixels[index].r = bmp.pixels[index].b = 0;
        break;
    }
}

void set_contrast(float perc)
{
  for (int i = 0; i < bmp.dheader.width * bmp.dheader.height; i++) {
    bmp.pixels[i].b = (unsigned char)bmp.pixels[i].b * perc;
    bmp.pixels[i].g = (unsigned char)bmp.pixels[i].g * perc;
    bmp.pixels[i].r = (unsigned char)bmp.pixels[i].r * perc;
  }
}