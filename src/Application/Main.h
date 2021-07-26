#pragma once

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "../../glad/glad.h"
#include "../../lib/glfw-3.3.2.bin.WIN32/include/GLFW/glfw3.h"
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
#include "../shader/Shader.h"
#include "../camera/Camera.h"

#include "../Mesh/unitCube/UnitCube.h"
#include "../Mesh/unitLine/UnitLine.h"
#include "../Models/Axes/Axes.h"
#include "../Models/gridLines/Grid.h"
#include "../Models/modelBase/modelBase.h"
#include "../Models/modelElijah/modelElijah.h"

#include "../Models/WorldCube/WorldCube.h"
#include "../Models/Wall/Wall.h"
#include "../Scene/ObjectNode.h"

// window size
#define WIDTH 1024
#define HEIGHT 768