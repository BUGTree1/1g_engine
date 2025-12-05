#include "renderer.h"
#include "common.h"

using namespace std;
using namespace glm;
using namespace e1g;

int main(int argc, char** argv) {
	Scene* scene = new Scene({new GameObject({new Transform(),new Mesh_Renderer()})});

	Renderer rend = Renderer();
	rend.init(scene);

    double last_time = 0;
    double current_time = 0;
	int running = 1;
    
    while (!glfwWindowShouldClose(rend.data->window)) {
        current_time = glfwGetTime();
		rend.data->time = current_time;
		rend.data->delta_time = current_time - last_time;
		rend.data->fps = 1.0 / rend.data->delta_time;
		last_time = current_time;

		glfwPollEvents();

		if(glfwGetKey(rend.data->window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
			glfwSetWindowShouldClose(rend.data->window, true);
		}

		rend.update();
    }

	rend.end();
	return 0;
}