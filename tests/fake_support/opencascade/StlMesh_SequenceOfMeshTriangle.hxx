#ifndef _StlMesh_SequenceOfMeshTriangle_HeaderFile
#define _StlMesh_SequenceOfMeshTriangle_HeaderFile

#include <Handle_StlMesh_MeshTriangle.hxx>

class StlMesh_SequenceOfMeshTriangle
{
public:
    const Handle_StlMesh_MeshTriangle& Value(const int /*Index*/) const
    {
        static Handle_StlMesh_MeshTriangle meshTri;
        return meshTri;
    }
};

#endif // _StlMesh_SequenceOfMeshTriangle_HeaderFile