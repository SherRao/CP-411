#ifndef MENU_HPP_
#define MENU_HPP_

#include <GL/glut.h>

/**
 * Clears the screen when Menu -> Clear is clicked.
 */
void clear();

/**
 *
 * Creates a new right-click menu to be attached to the window.
 *
 */
void createContextMenu();

/**
 * Process options for Menu.
 */
void processMenu(GLint menuOption);

/**
 * Process options for Menu -> Draw.
 */
void processDrawSubMenu(GLint typeOption);

/**
 * Process options for Menu -> File.
 */
void processFileSubMenu(GLint fileOption);

/**
 * Process options for Menu -> Edit.
 */
void processEditSubMenu(GLint editOption);

/**
 * Process options for Menu -> Style.
 */
void processStyleSubMenu(GLint styleOption);

/*
 * Process options for Menu -> Style -> Fill Color.
 */
void processStyleFillColorSubMenu(GLint colorOption);

/*
 * Process options for Menu -> Style -> Strok Colore.
 */
void processStyleStrokeColorSubMenu(GLint colorOption);

/**
 * Process options for Menu -> Style -> Stroke Width.
 */
void processStyleStrokeWidthSubMenu(GLint width);

#endif /* MENU_HPP_ */
