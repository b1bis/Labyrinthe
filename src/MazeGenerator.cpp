#include "MazeGenerator.hpp"

Maze MazeGenerator::Generate(std::size_t width, std::size_t height, unsigned seed)
{
    static std::default_random_engine engine(seed);

    std::uniform_int_distribution<std::size_t> widthDis(1, width - 2);
    std::uniform_int_distribution<std::size_t> heightDis(1, height - 2);
    std::bernoulli_distribution orientationDis;

    std::vector<std::vector<int>> durtyMaze = GenerateGrid(width, height);

    std::size_t startX = 0, startY = 1,
        endX = width - 1, endY = height - 2;

    durtyMaze[startX][startY] = 0;
    durtyMaze[endX][endY] = 0;

    while (!IsComplete(durtyMaze))
    {
        std::size_t x = widthDis(engine);
        std::size_t y = heightDis(engine);

        int &c = durtyMaze[x][y],
            &c1 = durtyMaze[x - 1][y],
            &c2 = durtyMaze[x + 1][y],
            &c3 = durtyMaze[x][y - 1],
            &c4 = durtyMaze[x][y + 1];

        int e1 = 0, e2 = 0;

        if (c != -1)
            continue;

        if (c1 == -1 || c2 == -1)
        {
            if (c3 == -1 || c4 == -1)
                continue;
            e1 = c3;
            e2 = c4;
        }
        else
        {
            e1 = c1;
            e2 = c2;
        }

        if (e1 != e2)
        {
            c = e1;
            for (std::size_t x = 0; x < width; ++x)
            {
                for (std::size_t y = 0; y < height; ++y)
                {
                    if (durtyMaze[x][y] == e2)
                    {
                        durtyMaze[x][y] = e1;
                    }
                }
            }
        }

    }

    durtyMaze[startX][startY] = -2;

    return ToMaze(durtyMaze);
}

Maze MazeGenerator::ToMaze(const std::vector<std::vector<int>>& durtyMaze)
{ 
    Maze maze(durtyMaze.size(), durtyMaze[0].size());
    for (std::size_t x = 0; x < maze.GetWidth(); ++x)
    {
        for (std::size_t y = 0; y < maze.GetHeight(); ++y)
        {
            switch (durtyMaze[x][y])
            {
            case -2:
                maze.SetState(x, y, Maze::Start);
                break;
            case -1:
                maze.SetState(x, y, Maze::Wall);
                break;
            default:
                maze.SetState(x, y, Maze::Empty);
            }
        }
    }
    return maze;
}

std::vector<std::vector<int>> MazeGenerator::GenerateGrid(std::size_t width, std::size_t height)
{
    std::vector<std::vector<int>> durtyMaze;
    std::vector<int> wall(height, -1);
    std::vector<int> semiWall(height);

    for (std::size_t i = 0; i < height; ++i)
    {
        if (i % 2 == 0)
            semiWall[i] = -1;
        else
            semiWall[i] = 0;
    }
    semiWall[height - 2] = 0;
    semiWall[height - 1] = -1;

    for (std::size_t i = 0; i < width; ++i)
    {
        if (i % 2 == 0)
            durtyMaze.push_back(wall);
        else
            durtyMaze.push_back(semiWall);
    }
    durtyMaze[width - 2] = semiWall;
    durtyMaze[width - 1] = wall;

    unsigned int ensemble = 1;

    for (std::size_t x = 0; x < width - 1; ++x)
    {
        for (std::size_t y = 0; y < height - 1; ++y)
        {
            if (durtyMaze[x][y] == 0)
            {
                durtyMaze[x][y] = ensemble;
                ++ensemble;
            }
            if (durtyMaze[x][y] > 0)
            {
                if (durtyMaze[x][y + 1] == 0)
                    durtyMaze[x][y + 1] = durtyMaze[x][y];
                if (durtyMaze[x + 1][y] == 0)
                    durtyMaze[x + 1][y] = durtyMaze[x][y];
            }
        }
    }

    return durtyMaze;
}

bool MazeGenerator::IsComplete(const std::vector<std::vector<int>>& durtyMaze)
{
    int ensemble = 0;
    for (const auto& line : durtyMaze)
    {
        for (const auto& e : line)
        {
            if (e > 0 && e != ensemble)
            {
                if (ensemble == 0)
                {
                    ensemble = e;
                }
                else
                {
                    return false;
                }
            }
        }
    }
    return true;
}
