#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

class Hexahedron
{
private:
    int idx;
    int vertices[8];

public:
    Hexahedron(int idx, int vertices[8]);
    void first_transposition_by_min_vertex();
    void second_transposition_by_faces();
    std::vector<std::vector<int>> return_tetras();

    int transposition(int transposition[8]);
    std::vector<int> get_diagonals(int face[4]);
    bool is_elem_in_diag(int face[4], int elem);
};
