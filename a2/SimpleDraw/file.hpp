#ifndef FILE_HPP_
#define FILE_HPP_

#include "object.hpp"

/**
 * Saves the current drawing to a vector file with the given file name.
 */
int saveSVG(const char *filename, int winWidth, int winHeight);

/**
 * Loads a drawing from a vector file into the active drawing with the given file name.
 */
int openSVG(const char *filename);

/**
 * Saves the current drawing to a bitmap file with the given file name.
 */
int saveBitmap(const char *ptrcFileName, int nX, int nY, int nWidth, int nHeight);

#endif /* FILE_HPP_ */
