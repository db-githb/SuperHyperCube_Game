#include "Level.h"

Level::Level(Shader& inShader)
{

	// Create two ObjectNodes with Model Components
	object = new ObjectNode(new Model(inShader));
	wall   = new ObjectNode(new Model(inShader));
	
	// Set the two created ObjectNodes as children of the level
	// "links" their Transform components such that any transformation on the Level will apply to the children
	// and any transformations on the children will occur relative to the parent
	AddChild(object);
	AddChild(wall);
	
	//Generate object first, wall second, so that the wall generation function can identify the correct "cutout" for the object
	generateObject();
	generateWall();

	// Set position of the wall and object relative to the Level's origin
	resetLevel();
}

/// <summary>
/// Called once per frame.
/// </summary>
/// <param name="ms"> Time in milliseconds between frames.</param>
void Level::Update(float ms)
{

	//object->AddPosition(glm::vec3(0, 0, -4 * ms));
	
}


/// <summary>
/// Validates the orientation of the object relative to the wall. \n
/// TODO: Needs further implementation to take up vector and symmetrical models into account - currently only considers the forward vector.
/// </summary>
/// <returns>Returns true if the object has the correct/"original" rotation</returns>
bool Level::validateOrientation()
{
	if (object->transform.GetForwardVector() == wall->transform.GetForwardVector())
	{
		std::cout << "\n forward vectors match";
		return true;
	}
	else
	{
		std::cout << "\n forward do not vectors match";
		return false;
	}
}

/// <summary>
/// Assigns values to the objectData array.
/// Generates an object by copying the values within objectData into the "object" child's cubePositions array.
/// </summary>
void Level::generateObject()
{
	clearObjectModel();
	for (int z = 1; z < 4; z++)
	{
		for (int x = 1; x < sizeX-1; x++)
		{
			// E
			objectData[x][1][z] = RED;
			objectData[x][4][z] = ORANGE;
			objectData[x][7][z] = BLUE;

		}
		for (int y = 1; y < sizeY-1; y++)
		{
			// E
			objectData[6][y][3] = GREEN;

		}
	}


	//transfer object data to ObjectNode child "object"
	for (int x = 1; x < sizeX-1; x++)
	{
		for (int y = 1; y < sizeY-1; y++)
		{
			for (int z = 0; z < sizeZ; z++)
				object->m_model->cubePositions[x][y][z] = objectData[x][y][z];
		}
	}
}

/// <summary>
/// Assigns values to the wallData array.
/// Generates the wall and places the hole into it according to the current objectData.
/// This should be called after the generateObject() method.
/// </summary>
void Level::generateWall()
{
	
	clearWallModel();
	// Set all walls to solid
	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			wallData[x][y][0] = WALL;
		}
	}

	//	Checks all XY values on all planes of the object
	//	if there is at least one cube on any plane that occupies that XY position
	//	a hole is placed on the wall on that XY position
	for (int x = 1; x < sizeX-1; x++)
	{
		for (int y = 1; y < sizeY-1; y++)
		{
			for (int z = 0; z < sizeZ; z++)
			{
				if(objectData[x][y][z] != NONE)
				{
					wallData[x][y][0] = NONE;
				}
			}
		}
	}


	//transfer wall data to ObjectNode child "wall"
	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			
			wall->m_model->cubePositions[x][y][0] = wallData[x][y][0];
		}
	}
	

}

/// <summary>
/// Sets all values within the objectData array to NONE
/// </summary>
void Level::clearObjectModel()
{
	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			for (int z = 0; z < sizeZ; z++)
			objectData[x][y][z] = NONE;
		}
	}
	
	object->m_model->resetObject();
}

/// <summary>
/// Sets all the values within the wallData array to NONE
/// </summary>
void Level::clearWallModel()
{

	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			for (int z = 0; z < sizeZ; z++)
				wallData[x][y][z] = NONE;
		}
	}
	wall->m_model->resetObject();
}


void Level::resetLevel()
{
	object->SetPosition(objectStartPosition);
	wall->	SetPosition(wallStartPosition);
	randomizeObjectOrientation();
}

void Level::randomizeObjectOrientation()
{
	int permutations = rand() % 10;
	for(int i = 0; i < permutations; i++)
	{
		int selection = rand() % 6;
		switch(selection)
		{
		case 0:
			object->AddRotation90(glm::vec3(1, 0, 0));
			break;
		case 1:
			object->AddRotation90(glm::vec3(-1, 0, 0));
			break;
		case 2:
			object->AddRotation90(glm::vec3(0, 1, 0));
			break;
		case 3:
			object->AddRotation90(glm::vec3(0, -1, 0));
			break;
		case 4:
			object->AddRotation90(glm::vec3(0, 0, 1));
			break;
		case 5:
			object->AddRotation90(glm::vec3(0, 0, -1));
			break;
		}
		
	}
}
