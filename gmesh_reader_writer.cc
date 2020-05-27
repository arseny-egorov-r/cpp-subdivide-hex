#include "gmesh_reader_writer.h"

GMeshReader::GMeshReader(char *path_to_mesh)
{
    this->mesh_file = std::ifstream(path_to_mesh);
    if (!this->mesh_file.is_open())
    {
        std::cerr << "No such file: " << path_to_mesh << std::endl;
        exit(122);
    }
}

GMeshReader::~GMeshReader()
{
    this->mesh_file.close();
    for (int i = 0; i < this->n_nodes; ++i)
        delete[] this->nodes_idx[i];
    delete[] this->nodes_idx;
}

float **GMeshReader::load_nodes()
{
    this->read_assert("$MeshFormat");
    float t;
    this->mesh_file >> t >> t >> t;
    this->read_assert("$EndMeshFormat");
    this->read_assert("$Nodes");

    this->mesh_file >> this->n_nodes;
    this->nodes_idx = new float *[this->n_nodes];

    int idx;
    float x, y, z;
    for (int i = 0; i < this->n_nodes; i++)
    {
        this->mesh_file >> idx >> x >> y >> z;
        nodes_idx[i] = new float[3];
        nodes_idx[i][0] = x;
        nodes_idx[i][1] = y;
        nodes_idx[i][2] = z;
    }
    this->read_assert("$EndNodes");
    this->read_assert("$Elements");

    return this->nodes_idx;
}

std::vector<Hexahedron> *GMeshReader::load_hexahedrons()
{
    this->mesh_file >> this->n_hexas;
    int idx, type, add_params;
    int vertices[8]; // v1, v2, v3, v4, v5, v6, v7, v8;
    for (int i = 0; i < this->n_hexas; i++)
    {
        this->mesh_file >> idx >> type >> add_params;
        if (type == 5)
        {
            this->mesh_file >> vertices[0] >> vertices[1] >> vertices[2];
            this->mesh_file >> vertices[3] >> vertices[4] >> vertices[5];
            this->mesh_file >> vertices[6] >> vertices[7];
            this->hexas_idx.push_back(Hexahedron(idx, vertices));
        }
    }
    this->read_assert("$EndElements");

    return &this->hexas_idx;
}

void GMeshReader::read_assert(std::string to_compare)
{
    std::string temp;
    this->mesh_file >> temp;
    assert(temp == to_compare);
}

GMeshWriter::GMeshWriter(char *path_to_mesh)
{
    this->mesh_file = std::ofstream(path_to_mesh);
}

GMeshWriter::~GMeshWriter()
{
    this->mesh_file.close();
}

void GMeshWriter::write_mesh(std::vector<std::vector<int>> *all_tetras, float **nodes_idx, int n_nodes)
{
    this->mesh_file << "$MeshFormat\n2.2 0 8\n$EndMeshFormat\n$Nodes\n";
    this->mesh_file << n_nodes << "\n";
    for (int i = 0; i < n_nodes; i++)
    {
        float x = nodes_idx[i][0];
        float y = nodes_idx[i][1];
        float z = nodes_idx[i][2];

        this->mesh_file << i + 1 << " " << x << " " << y << " " << z << "\n";
    }
    this->mesh_file << "$EndNodes\n$Elements\n";
    this->mesh_file << all_tetras->size() << "\n";
    for (int i = 0; i < all_tetras->size(); i++)
    {
        int v1 = all_tetras->at(i)[0];
        int v2 = all_tetras->at(i)[1];
        int v3 = all_tetras->at(i)[2];
        int v4 = all_tetras->at(i)[3];

        this->mesh_file << i + 1 << " 4 0 " << v1 << " " << v2 << " " << v3 << " " << v4 << "\n";
    }
    this->mesh_file << "$EndElements\n";
}