#pragma once

#include <queue>
#include <vector>
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include <string>

class MazePathFinding
{

	int row, col;
	std::vector<std::vector<int>> grid;

public:
	MazePathFinding();
	void Initialize(int row, int column);

	void GenerateGrid(const std::string& path);

	bool isValid(int x, int y, std::vector<std::vector<int>>& grid, std::vector<std::vector<bool>>& visited);
    std::pair<int, std::vector<glm::vec2>> PathPoints(glm::vec2& start, glm::vec2& end);
    
};

