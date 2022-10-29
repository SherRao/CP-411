/*
 * Description: SimpleView reference design
 * Author: HBF
 * Version: 2022-10-03
 */

#ifndef MENU_HPP_
#define MENU_HPP_

#include <GL/glut.h>

void menu();
void mainMenu(GLint option);
void ObjSubMenu(GLint objectOption);
void MCSTransMenu(GLint transOption);
void WCSTransMenu(GLint transOption);
void VCSTransMenu(GLint transOption);
void MCSTransform(GLint);
void WCSTransform(GLint);
void VCSTransform(GLint);

#endif
