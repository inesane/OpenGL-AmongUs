#include "main.h"

using namespace std;

vector<pair<pair<int, int>, pair<int, int>>> walls, connected_blocks;

void maze_create()
{
    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            walls.push_back(make_pair(make_pair(i, j), make_pair(i + 1, j)));
            walls.push_back(make_pair(make_pair(i, j), make_pair(i, j + 1)));
        }
        walls.push_back(make_pair(make_pair(n, i), make_pair(n, i + 1)));
        walls.push_back(make_pair(make_pair(i, n), make_pair(i + 1, n)));
    }

    int blocks[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            blocks[i][j] = n * i + j;
        }
    }

    while (true)
    {
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (blocks[i][j] == blocks[0][0])
                {
                    count++;
                }
            }
        }
        if (count == n * n)
            break;

        int random = rand() % (2 * n * (n + 1));

        int x1, x2, y1, y2;
        x1 = walls[random].first.first;
        y1 = walls[random].first.second;
        x2 = walls[random].second.first;
        y2 = walls[random].second.second;
        if (x1 == x2)
        {
            if (x1 != 0 and x1 != n and blocks[x1][min(y1, y2)] != blocks[x1 - 1][min(y1, y2)])
            {
                int val = blocks[x1 - 1][min(y1, y2)];
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        if (blocks[i][j] == val)
                            blocks[i][j] = blocks[x1][min(y1, y2)];
                    }
                }
                connected_blocks.push_back(make_pair(make_pair(x1-1, min(y1,y2)), make_pair(x1, min(y1,y2))));
                connected_blocks.push_back(make_pair(make_pair(x1, min(y1,y2)), make_pair(x1-1, min(y1,y2))));
                auto it = walls.begin();
                advance(it, random);
                walls.erase(it);
            }
        }
        if (y1 == y2)
        {
            if (y1 != 0 and y1 != n and blocks[min(x1, x2)][y1] != blocks[min(x1, x2)][y1 - 1])
            {
                int val = blocks[min(x1, x2)][y1 - 1];
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        if (blocks[i][j] == val)
                            blocks[i][j] = blocks[min(x1, x2)][y1];
                    }
                }
                connected_blocks.push_back(make_pair(make_pair(min(x1,x2), y1-1), make_pair(min(x1,x2), y1)));
                connected_blocks.push_back(make_pair(make_pair(min(x1,x2), y1), make_pair(min(x1,x2), y1-1)));
                auto it = walls.begin();
                advance(it, random);
                walls.erase(it);
            }
        }
    }

    // auto it1 = walls.begin();
    // advance(it1, 0);
    // walls.erase(it1);
    // cout<<walls[0].first.first<<walls[0].first.second<<walls[0].second.first<<walls[0].second.second<<endl;
    // auto it2 = walls.begin();
    // int end = walls.size();
    // advance(it2, end - 1);
    // walls.erase(it2);

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         cout << blocks[i][j];
    //     }
    // }

    // cout << walls.size() << endl << endl;
    // for (int i = 0; i < walls.size(); i++)
    // {
    //     cout << (walls[i].first.first);
    //     cout << (walls[i].first.second) << endl;
    //     cout << (walls[i].second.first);
    //     cout << (walls[i].second.second) << endl << endl;
    // }
    // cout << connected_blocks.size() << endl << endl;
    // for (int i = 0; i < connected_blocks.size(); i++)
    // {
    //     cout << (connected_blocks[i].first.first);
    //     cout << (connected_blocks[i].first.second) << endl;
    //     cout << (connected_blocks[i].second.first);
    //     cout << (connected_blocks[i].second.second) << endl << endl;
    // }
}