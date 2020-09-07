#ifndef MESH_RECONSTRUCTOR_H
#define MESH_RECONSTRUCTOR_H

class MeshReconstructor {
public:
  MeshReconstructor(int tsdf_volume);
  void reconstructMesh();
  void tsdf_reprentation();
  void extract_isosurface();
};

#endif
