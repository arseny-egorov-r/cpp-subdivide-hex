#include "hexahedron_algo.h"
#include "constants.h"

Hexahedron::Hexahedron(int idx, int vertices[8])
{
    this->idx = idx;
    for (int i = 0; i < 8; i++)
    {
        this->vertices[i] = vertices[i];
    }
}

void Hexahedron::first_transposition_by_min_vertex()
{
    int min_vertex_id = 0;
    for (int i = 1; i < 8; i++)
    {
        if (this->vertices[i] < min_vertex_id)
            min_vertex_id = i;
    }
    this->transposition(TRANSPOSITION_1[min_vertex_id]);
}

void Hexahedron::second_transposition_by_faces()
{   
    bool is_6_1 = this->is_elem_in_diag(FACE_1, 6);
    bool is_6_2 = this->is_elem_in_diag(FACE_2, 6);
    bool is_6_3 = this->is_elem_in_diag(FACE_3, 6);
    int rotation_id = is_6_1*4 + is_6_2*2 + is_6_3*1;

    this->transposition(ROTATIONS[rotation_id]);
}

std::vector<int> Hexahedron::get_diagonals(int face[4])
{
    int v1 = this->vertices[face[0]];
    int v2 = this->vertices[face[1]];
    int v3 = this->vertices[face[2]];
    int v4 = this->vertices[face[3]];

    std::vector<int> result;

    if (std::min(v1, v3) < std::min(v2, v4)) result = {face[0], face[2]};
    else result = {face[1], face[3]};

    return result;
}

bool Hexahedron::is_elem_in_diag(int face[4], int elem)
{
    std::vector<int> diags = this->get_diagonals(face);
    return true ? (std::find(diags.begin(), diags.end(), elem) != diags.end()) : false;
}


int Hexahedron::transposition(int transposition[8])
{
    int new_vertices[8];
    for (int i = 0; i < 8; i++)
    {
        int rotation_idx = transposition[i];
        new_vertices[i] = this->vertices[rotation_idx];
    }
    std::copy(new_vertices, new_vertices + 8, this->vertices);
}

std::vector<std::vector<int>> Hexahedron::return_tetras()
{
    int count_of = this->is_elem_in_diag(FACE_1, 6) + \
        this->is_elem_in_diag(FACE_2, 6) + this->is_elem_in_diag(FACE_3, 6);
    
    std::vector<std::vector<int>> result;

    for (int i = 0; i < TETRAS_TO_RETURN_INDICES[count_of].size(); i++)
    {
        result.push_back({
            this->vertices[TETRAS_TO_RETURN_INDICES[count_of][i][0]],
            this->vertices[TETRAS_TO_RETURN_INDICES[count_of][i][1]],
            this->vertices[TETRAS_TO_RETURN_INDICES[count_of][i][2]],
            this->vertices[TETRAS_TO_RETURN_INDICES[count_of][i][3]],
        });
    }

    return result;
}
