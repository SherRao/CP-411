/*
 * Description: SimpleView - Menu.hpp
 * Author: Nausher Rao
 * Version: 2022-10-27
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
