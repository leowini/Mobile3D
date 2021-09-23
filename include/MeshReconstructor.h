#ifndef MESH_RECONSTRUCTOR_H
#define MESH_RECONSTRUCTOR_H

class MeshReconstructor {
public:
  MeshReconstructor(int tsdf_volume);
private:
  void reconstructMesh();
  void tsdf_representation();
  void extract_isosurface();
};

#endif
