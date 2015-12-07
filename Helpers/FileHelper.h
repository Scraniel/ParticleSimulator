/*
 * FileHelper.h
 *
 *  Created on: Sep 24, 2015
 *      Author: dglewis
 */

#ifndef HELPERS_FILEHELPER_H_
#define HELPERS_FILEHELPER_H_

#include "../SceneObjects/Renderable.h"
class FileHelper{
public:
	static void loadCurveFromFile(const char *, Renderable &);
};

#endif /* HELPERS_FILEHELPER_H_ */
