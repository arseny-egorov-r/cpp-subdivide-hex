#include <iostream>
#include <vector>
#include <chrono>

#include "hexahedron_algo.h"
#include "gmesh_reader_writer.h"

int main(int argc, char **argv)
{
    // Define parameters
    assert(argc == 3);

    char *mesh_path_in = argv[1];
    char *mesh_path_out = argv[2];

    // Read nodes and hexas from gmsh file
    GMeshReader gmsh_reader(mesh_path_in);
    float **nodes_idx = gmsh_reader.load_nodes();

    /*
     * THE MAIN PART OF ALGO
     * Prepare `std::vector` of `class Hexahedron` from "hexahedron_algo.h"
     */
    std::vector<Hexahedron> *hexas = gmsh_reader.load_hexahedrons();

    std::cout << "Number of hexas: " << gmsh_reader.n_hexas << std::endl;
    // Get tetras
    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> all_tetras;
    for (int i = 0; i < hexas->size(); i++)
    {
        hexas->at(i).first_transposition_by_min_vertex();

        hexas->at(i).second_transposition_by_faces();

        std::vector<std::vector<int>> tetras = hexas->at(i).return_tetras();
        for (int j = 0; j < tetras.size(); j++)
        {
            all_tetras.push_back(tetras[j]);
        }
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    std::cout << "Running time in ms: " << duration << std::endl;

    // Write everything to output file
    GMeshWriter gmsh_writer(mesh_path_out);
    gmsh_writer.write_mesh(&all_tetras, nodes_idx, gmsh_reader.n_nodes);

    return 0;
}