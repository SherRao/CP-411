#ifndef MENU_HPP_
#define MENU_HPP_

#include <GL/glut.h>

void clear();

void createContextMenu();

void processMenu(GLint menuOption);

void processDrawSubMenu(GLint typeOption);

void processFileSubMenu(GLint fileOption);

void processEditSubMenu(GLint editOption);

void processStyleSubMenu(GLint styleOption);

void processStyleFillColorSubMenu(GLint colorOption);

void processStyleStrokeColorSubMenu(GLint colorOption);

void processStyleStrokeWidthSubMenu(GLint width);

void dataviewSubMenu(GLint option);

#endif /* MENU_HPP_ */
