release:
	cmake -Hpathfinding_backend -Bpathfinding_backend/build
	cmake --build pathfinding_backend/build --config Release --target all
	pathfinding_backend/build/PathfindingAPI

test:
	cmake -Hpathfinding_backend -Bpathfinding_backend/build -DCMAKE_BUILD_TYPE=Debug
	cmake --build pathfinding_backend/build --config Release --target all
	gdb pathfinding_backend/build/PathfindingAPI