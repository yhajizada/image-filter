#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void grayscale(unsigned char* img, int w, int h, int c) {
    for (int i = 0; i < w * h * c; i += c) {
        unsigned char gray = 0.299*img[i] + 0.587*img[i+1] + 0.114*img[i+2];
        img[i] = img[i+1] = img[i+2] = gray;
    }
}

void invert(unsigned char* img, int w, int h, int c) {
    for (int i = 0; i < w * h * c; i++) img[i] = 255 - img[i];
}

void brightness(unsigned char* img, int w, int h, int c, int val) {
    for (int i = 0; i < w * h * c; i++) {
        int pixel = img[i] + val;
        if (pixel > 255) pixel = 255;
        if (pixel < 0) pixel = 0;
        img[i] = pixel;
    }
}

void blur(unsigned char* img, int w, int h, int c) {
    unsigned char* copy = malloc(w * h * c);
    memcpy(copy, img, w * h * c);
    for (int y = 1; y < h-1; y++) {
        for (int x = 1; x < w-1; x++) {
            for (int ch = 0; ch < 3; ch++) {
                int sum = 0;
                for (int ky = -1; ky <= 1; ky++) {
                    for (int kx = -1; kx <= 1; kx++) {
                        sum += copy[((y+ky)*w + (x+kx))*c + ch];
                    }
                }
                img[(y*w + x)*c + ch] = sum / 9;
            }
        }
    }
    free(copy);
}

void sepia(unsigned char* img, int w, int h, int c) {
    for (int i = 0; i < w * h * c; i += c) {
        unsigned char r = img[i];
        unsigned char g = img[i + 1];
        unsigned char b = img[i + 2];
        int tr = 0.393*r + 0.769*g + 0.189*b;
        int tg = 0.349*r + 0.686*g + 0.168*b;
        int tb = 0.272*r + 0.534*g + 0.131*b;
        img[i] = tr > 255? 255 : tr;
        img[i + 1] = tg > 255? 255 : tg;
        img[i + 2] = tb > 255? 255 : tb;
    }
}

void edge_detect(unsigned char* img, int w, int h, int c) {
    unsigned char* copy = malloc(w * h * c);
    memcpy(copy, img, w * h * c);
    int gx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int gy[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
    for (int y = 1; y < h-1; y++) {
        for (int x = 1; x < w-1; x++) {
            int sumX = 0, sumY = 0;
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    int pixel = copy[((y+ky)*w + (x+kx))*c];
                    sumX += gx[ky+1][kx+1] * pixel;
                    sumY += gy[ky+1][kx+1] * pixel;
                }
            }
            int val = sqrt(sumX*sumX + sumY*sumY);
            if (val > 255) val = 255;
            img[(y*w + x)*c] = img[(y*w + x)*c + 1] = img[(y*w + x)*c + 2] = val;
        }
    }
    free(copy);
}

int main(int argc, char** argv) {
    if (argc < 4) {
        printf("Usage:./filter input.jpg --filter output.jpg\n");
        printf("Filters: --grayscale --invert --blur --sepia --edge --bright 50\n");
        return 1;
    }
    int w, h, c;
    unsigned char* img = stbi_load(argv[1], &w, &h, &c, 0);
    if (!img) { printf("Error: Cannot load %s\n", argv[1]); return 1; }
    printf("Loaded %s: %dx%d %d channels\n", argv[1], w, h, c);

    if (strcmp(argv[2], "--grayscale") == 0) grayscale(img, w, h, c);
    else if (strcmp(argv[2], "--invert") == 0) invert(img, w, h, c);
    else if (strcmp(argv[2], "--blur") == 0) blur(img, w, h, c);
    else if (strcmp(argv[2], "--sepia") == 0) sepia(img, w, h, c);
    else if (strcmp(argv[2], "--edge") == 0) edge_detect(img, w, h, c);
    else if (strcmp(argv[2], "--bright") == 0 && argc == 5) {
        brightness(img, w, h, c, atoi(argv[3]));
        stbi_write_jpg(argv[4], w, h, c, img, 95);
        stbi_image_free(img);
        printf("Saved to %s\n", argv[4]);
        return 0;
    }
    else { printf("Unknown filter\n"); stbi_image_free(img); return 1; }

    stbi_write_jpg(argv[3], w, h, c, img, 95);
    stbi_image_free(img);
    printf("Saved to %s\n", argv[3]);
    return 0;
}
