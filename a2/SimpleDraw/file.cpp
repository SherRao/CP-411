#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "file.hpp"
#include "object.hpp"
#include "edit.hpp"

#define MaxNumObj 100
#define GL_BGR_EXT 0x80E0
#define GL_BGR 0x80E0
#define GL_BGRA 0x80E1

extern List objects;

int saveBitmap(const char *ptrcFileName, int nX, int nY, int nWidth, int nHeight)
{
	FILE *file = fopen(ptrcFileName, "wb");
	if (file == NULL)
		return 0;

	int bitsize = nWidth * nHeight * 3 + ((3 * nWidth) % 4 == 0 ? 0 : (4 - (3 * nWidth) % 4) * nHeight);
	unsigned char *pointerImage = (unsigned char *)malloc(bitsize);
	if (pointerImage == NULL)
	{
		printf("Error while trying to save a bitmap image!\n");
		fclose(file);
		return EXIT_FAILURE;
	}

	glReadPixels(nX, nY, nWidth, nHeight, GL_BGR, GL_UNSIGNED_BYTE, pointerImage);

	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	memset(&fileHeader, 0, sizeof(fileHeader));
	memset(&infoHeader, 0, sizeof(infoHeader));

	fileHeader.bfType = 0x4d42;
	fileHeader.bfSize = sizeof(fileHeader) + sizeof(infoHeader) + bitsize;
	fileHeader.bfOffBits = sizeof(fileHeader) + sizeof(infoHeader);
	infoHeader.biSize = sizeof(infoHeader);
	infoHeader.biSizeImage = bitsize;
	infoHeader.biWidth = nWidth + nWidth % 4;
	infoHeader.biHeight = nHeight;
	infoHeader.biBitCount = 24;
	infoHeader.biPlanes = 1;

	if (fwrite(&fileHeader, sizeof(fileHeader), 1, file) < 1)
	{
		free(pointerImage);
		fclose(file);
		return EXIT_SUCCESS;
	}

	if (fwrite(&infoHeader, sizeof(infoHeader), 1, file) < 1)
	{
		free(pointerImage);
		fclose(file);
		return EXIT_SUCCESS;
	}

	if (fwrite(pointerImage, 1, bitsize, file) < bitsize)
	{
		free(pointerImage);
		fclose(file);
		return EXIT_SUCCESS;
	}

	fclose(file);
	free(pointerImage);
	return EXIT_SUCCESS;
}

int saveSVG(const char *filename, int winWidth, int winHeight)
{
	FILE *file = fopen(filename, "w");
	if (file == NULL)
		return EXIT_FAILURE;

	char line[255];
	int width;
	int height;

	sprintf(line, "<?xml version=\"1.0\" standalone=\"no\"?>\n");
	fputs(line, file);
	sprintf(line, "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n");
	fputs(line, file);
	sprintf(line, "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
	fputs(line, file);
	sprintf(line, "<svg width=\"%d\" height=\"%d\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n", winWidth, winHeight);
	fputs(line, file);

	Node *curr = objects.start;
	int fillRed, fillBlue, fillGreen, strokeRed, strokeBlue, strokeGreen;
	while (curr != NULL)
	{
		Shape *currObject = curr->object;
		fillRed = (int)(255 * curr->object->fillR);
		fillGreen = (int)(255 * curr->object->fillG);
		fillBlue = (int)(255 * curr->object->fillB);
		strokeRed = (int)(255 * curr->object->strokeR);
		strokeGreen = (int)(255 * curr->object->strokeG);
		strokeBlue = (int)(255 * curr->object->strokeB);

		if (currObject->type == 1)
		{
			int minX = min(currObject->x1, currObject->x2);
			int minY = min(currObject->y1, currObject->y2);
			int absX = abs(currObject->x1 - currObject->x2);
			int absY = abs(currObject->y1 - currObject->y2);
			sprintf(line, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"rgb(%d,%d,%d)\" stroke=\"rgb(%d,%d,%d)\" stroke-width=\"%d\" />\n", minX, minY, absX, absY, fillRed, fillGreen, fillBlue, strokeRed, strokeGreen, strokeBlue, currObject->strokeW);
		}
		else if (currObject->type == 2)
		{
			int centreX = currObject->x1;
			int centreY = currObject->y1;
			int r = sqrt(pow(currObject->x2 - currObject->x1, 2) + pow(currObject->y2 - currObject->y1, 2));

			sprintf(line, "<circle cx=\"%d\" cy=\"%d\" r=\"%d\" fill=\"rgb(%d,%d,%d)\" stroke=\"rgb(%d,%d,%d)\" stroke-width=\"%d\" />\n", centreX, centreY, r, fillRed, fillGreen, fillBlue, strokeRed, strokeGreen, strokeBlue, currObject->strokeW);
		}

		fputs(line, file);
		curr = curr->next;
	}

	sprintf(line, "</svg>\n");
	fputs(line, file);
	fclose(file);
	return EXIT_SUCCESS;
}

int openSVG(const char *filename)
{
	FILE *file = fopen(filename, "r");
	if (file == NULL)
		return EXIT_FAILURE;

	int lineLength = 255;
	char line[lineLength];
	int x1;
	int y1;
	int w;
	int h;
	int fillR;
	int fillG;
	int fillB;
	int strokeR;
	int strokeG;
	int strokeB;
	int strokeW;
	int r;

	while (fgets(line, lineLength, file))
	{
		Shape *shapeObj;
		if (line[0] == '<' && line[1] == 'r')
		{
			sscanf(line, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"rgb(%d,%d,%d)\" stroke=\"rgb(%d,%d,%d)\" stroke-width=\"%d\"/>",
				   &x1, &y1, &w, &h, &fillR, &fillG, &fillB, &strokeR, &strokeG, &strokeB, &strokeW);

			shapeObj = (Shape *)malloc(sizeof(Shape));
			shapeObj->type = RECTANGLE;
			shapeObj->x1 = x1;
			shapeObj->y1 = y1;
			shapeObj->x2 = x1 + w;
			shapeObj->y2 = y1 + h;
			shapeObj->fillR = fillR / 255;
			shapeObj->fillG = fillG / 255;
			shapeObj->fillB = fillB / 255;
			shapeObj->strokeR = strokeR / 255;
			shapeObj->strokeG = strokeG / 255;
			shapeObj->strokeB = strokeB / 255;
			shapeObj->strokeW = strokeW;
			insert(&objects, shapeObj);
		}
		else if (line[0] == '<' && line[1] == 'c')
		{
			sscanf(line, "<circle cx=\"%d\" cy=\"%d\" r=\"%d\" fill=\"rgb(%d,%d,%d)\" stroke=\"rgb(%d,%d,%d)\" stroke-width=\"%d\" />\n",
				   &x1, &y1, &r, &fillR, &fillG, &fillB, &strokeR, &strokeG, &strokeB, &strokeW);

			shapeObj = (Shape *)malloc(sizeof(Shape));
			shapeObj->type = CIRCLE;
			shapeObj->x1 = x1;
			shapeObj->y1 = y1;
			shapeObj->x2 = x1 + r;
			shapeObj->y2 = y1;
			shapeObj->fillR = fillR / 255;
			shapeObj->fillB = fillG / 255;
			shapeObj->fillB = fillB / 255;
			shapeObj->strokeR = strokeR / 255;
			shapeObj->strokeG = strokeG / 255;
			shapeObj->strokeB = strokeB / 255;
			shapeObj->strokeW = strokeW;
			insert(&objects, shapeObj);
		}
	}

	fclose(file);
	return EXIT_SUCCESS;
}
