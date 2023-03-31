#include "GameController.h"
#include <iostream>
#include "StandardIncludes.h"

static void AddVectors()
{
	glm::vec2 a = { 3, 5 };
	glm::vec2 b = { 2, -1 };
	glm::vec2 c = a + b;
	std::cout << glm::to_string(c) << std::endl;

	glm::vec3 d = { 3, 5, 1 };
	glm::vec3 e = { 2, -1, -1 };
	glm::vec3 f = d + e;
	std::cout << glm::to_string(f) << std::endl;
}

static void SubtractVectors()
{
	glm::vec2 a = { 3, 5 };
	glm::vec2 b = { 2, -1 };
	glm::vec2 c = b - a;
	glm::vec2 d = a - b;

	std::cout << glm::to_string(c) << " Magnitude: " <<
		glm::length(c) << std::endl;
	std::cout << glm::to_string(d) << " Magnitude: " <<
		glm::length(d) << std::endl;
}


static glm::vec3 pos = { 2, 2, 2 };
static void MultiplyVectors()
{
	//glm::vec3 pos = { 0, 0, 0 };
	glm::vec3 dest = { 1, 0, 0 };
	glm::vec3 dir = dest - pos;
	dir = glm::normalize(dir);
	pos += (dir * 0.1f);
	std::cout << glm::to_string(pos) << std::endl;
}

static void Distance()
{
	glm::vec3 p1 = { 1, 1, 0 };
	glm::vec3 p2 = { 2, 1, 2 };
	float distance = glm::distance(p1, p2);
	std::cout << "Distance = " << distance << std::endl;
}

static void DotProduct()
{
	glm::vec3 source = { 0, 0, 0 };
	glm::vec3 a = { 0 ,2, 0 };
	glm::vec3 b = { 1 ,1, 0 };
	glm::vec3 aVec = a - source;
	glm::vec3 bVec = b - source;
	aVec = glm::normalize(aVec);
	bVec = glm::normalize(bVec);
	float dot = glm::dot(aVec, bVec);
	std::cout << "Dot = " << dot << std::endl;
}

static void CrossProduct()
{
	glm::vec3 source = { 0, 0, 0 };
	glm::vec3 a = { 0 ,2, 0 };
	glm::vec3 b = { 1 ,1, 0 };
	glm::vec3 aVec = a - source;
	glm::vec3 bVec = b - source;
	glm::vec3 cross = glm::cross(aVec, bVec);
	cross = glm::normalize(cross);
	std::cout << "Cross = " << glm::to_string(cross) << std::endl;
}

static int numberOfSteps(glm::vec3 a, glm::vec3 b, float x)
{

	float distance = glm::distance(a, b);
	//std::cout << "Distance: " << distance << std::endl;
	int steps = static_cast<int> (distance / x);

	return steps;
}

static float perimeter(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	float ab, ac, cb;
	ab = glm::distance(a, b);
	cb = glm::distance(c, b);
	ac = glm::distance(a, c);

	return ab + cb + ac;
}

static float area(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	float ac;

	ac = glm::distance(a, c);
	float height = glm::distance(b, a + ac / 2);


	return ac * height / 2;
}



int main()
{
	//GameController::Instance().RunGame();

//AddVectors();
	//SubtractVectors();
	/*for(int count = 0; count <10; count++)
		MultiplyVectors();*/
		//Distance();
		//DotProduct();
		//CrossProduct();


		//Task1
		/*float x, y, z, speed;
		std::cout << "Enter the source position: " << std::endl;
		std::cout << "X: ";    std::cin >> x;
		std::cout << "Y: ";    std::cin >> y;
		std::cout << "Z: ";    std::cin >> z;
		glm::vec3 source = { x, y, z };

		std::cout << "Enter the destination position: " << std::endl;
		std::cout << "X: ";    std::cin >> x;
		std::cout << "Y: ";    std::cin >> y;
		std::cout << "Z: ";    std::cin >> z;
		glm::vec3 destination = { x, y, z };

		std::cout << "What speed you will use to go to destination? "; std::cin >> speed;
		std::cout << " You will need " << numberOfSteps(source, destination, speed) << " steps to arrive" << std::endl;*/


		//Task2
		/*float x, y, z, speed;
		std::cout << "Enter the first 3D vector: " << std::endl;
		std::cout << "X: ";    std::cin >> x;
		std::cout << "Y: ";    std::cin >> y;
		std::cout << "Z: ";    std::cin >> z;
		glm::vec3 a = { x, y, z };

		std::cout << "Enter the second 3D vector: " << std::endl;
		std::cout << "X: ";    std::cin >> x;
		std::cout << "Y: ";    std::cin >> y;
		std::cout << "Z: ";    std::cin >> z;
		glm::vec3 b = { x, y, z };

		std::cout << "Enter the third 3D vector: " << std::endl;
		std::cout << "X: ";    std::cin >> x;
		std::cout << "Y: ";    std::cin >> y;
		std::cout << "Z: ";    std::cin >> z;
		glm::vec3 c = { x, y, z };

		std::cout << " Perimeter:  " << perimeter(a, b, c) << std::endl;
		std::cout << " Area:  " << area(a, b, c) << std::endl;*/


		//Matrix Out 1
		/*glm::mat4 matrix = glm::mat4(1.0);

		std::cout << glm::to_string(matrix) << std::endl;*/

		//Matrix Out 2,3,4,5

	glm::mat4 matrix1 = {
		{ 1, 1, 1, 1}, { 2, 2, 2, 2},
		{ 3, 3, 3, 3}, { 4, 4, 4, 4} };

	glm::mat4 matrix2 = {
		{ 5, 5, 5, 5}, { 6, 6, 6, 6},
		{ 7, 7, 7, 7}, { 8, 8, 8, 8} };

	//std::cout << "Matrix1: " << glm::to_string(matrix1) << std::endl;
	//std::cout << "Matrix2: " << glm::to_string(matrix2) << std::endl;
	// 
	//std::cout << "Add M1 to M2: " << glm::to_string(matrix1 + matrix2) << std::endl;
	//std::cout << "Substract M1 to M2: " << glm::to_string(matrix1 - matrix2) << std::endl;
	//std::cout << "Multiply M1 and M2: " << glm::to_string(matrix1 * matrix2) << std::endl;
	//std::cout << "Multiply M2 and M1 " << glm::to_string(matrix2 * matrix1) << std::endl;

	//Matrix Out 5
	/*glm::mat4 matrix3 = glm::mat4(1.0f);
	glm::mat4 matrix4 = {
		{ 5, 5, 5, 5}, { 6, 6, 6, 6},
		{ 7, 7, 7, 7}, { 8, 8, 8, 8} };
	std::cout << "Matrix1: " << glm::to_string(matrix3) << std::endl;
	std::cout << "Matrix2: " << glm::to_string(matrix4) << std::endl;
	std::cout << "Multiply M1 and M2: " << glm::to_string(matrix3 * matrix4) << std::endl;
	std::cout << "Multiply M2 and M1 " << glm::to_string(matrix4 * matrix3) << std::endl;*/

	//Matrix Out 6
	/*glm::mat4 matrix3 = glm::mat4(1.0f);
	glm::vec3 pos1 = { 0, 0, 0 };
	matrix3 = glm::translate(matrix3, pos1);
	std::cout << "Translation Matrix 1: " << glm::to_string(matrix3) << std::endl;

	glm::mat4 matrix4 = glm::mat4(1.0f);
	glm::vec3 pos2 = { 1, 2, 3 };
	matrix4 = glm::translate(matrix4, pos2);
	std::cout << "Translation Matrix 2: " << glm::to_string(matrix4) << std::endl;*/

	//Matrix Out 7
	/*glm::mat4 matrix = glm::mat4(1.0f);
	glm::vec3 scale = { 2, 2, 2 };
	matrix = glm::scale(matrix, scale);
	std::cout << "Scale Matrix: " << glm::to_string(matrix) << std::endl;*/

	//Matrix Out 8
	glm::mat4 matrix = glm::mat4(1.0f);
	float angle = 0.1f;
	glm::vec3 axis = { 0, 1, 0 };
	matrix = glm::rotate(matrix, angle, axis);
	std::cout << "Rotation Matrix: " << glm::to_string(matrix) << std::endl;
}

