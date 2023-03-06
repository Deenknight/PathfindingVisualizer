#pragma once

#include "IResourceFactory.h"

#include <tuple>
#include <string>



class PathfinderResourceFactory : public IResourceFactory {

public:

  PathfinderResourceFactory();
  shared_ptr<Resource> get_resource() const final;

private:
  string to_json(const bool* walls, const int* dimensions);
  bool* generate_maze(int start, int end, const int* dimensions);
  tuple<int, int, int*> get_path_parameters(const shared_ptr<Session> session);
  void get_handler(const shared_ptr<Session> session);

  shared_ptr<Resource> _resource;

};