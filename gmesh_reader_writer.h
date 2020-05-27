#pragma once

#include <iostream>
#include <fstream>

#include "hexahedron_algo.h"

class GMeshReader
{
public:
    char file_name;

    int n_nodes, n_hexas;
    float **nodes_idx;
    std::vector<Hexahedron> hexas_idx;

    std::ifstream mesh_file;

    GMeshReader(char *path_to_mesh);
    ~GMeshReader();

    float **load_nodes();
    std::vector<Hexahedron> *load_hexahedrons();

    void read_assert(std::string to_compare);
};

class GMeshWriter
{
public:
    char file_name;

    std::ofstream mesh_file;

    GMeshWriter(char *path_to_mesh);
    ~GMeshWriter();

    void write_mesh(std::vector<std::vector<int>> *all_tetras,
                    float **nodes_idx, int n_nodes);
};