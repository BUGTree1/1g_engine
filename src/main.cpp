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

	dvec2 last_mouse_pos = dvec2(0.0f);
	glfwGetCursorPos(rend.data->window, &last_mouse_pos.x, &last_mouse_pos.y);
	rend.data->cam_pos = vec3(0.0f,0.0f,-5.0f);
    
    while (!glfwWindowShouldClose(rend.data->window)) {
        current_time = glfwGetTime();
		rend.data->time = current_time;
		rend.data->delta_time = current_time - last_time;
		rend.data->fps = 1.0 / rend.data->delta_time;
		last_time = current_time;

		glfwPollEvents();

		//cout << "FPS: " << to_string(rend.data->fps) << endl;

		if(glfwGetKey(rend.data->window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
			glfwSetWindowShouldClose(rend.data->window, true);
		}

    	glfwGetCursorPos(rend.data->window, &rend.data->mouse_pos.x, &rend.data->mouse_pos.y);
		rend.data->mouse_vel = rend.data->mouse_pos - last_mouse_pos;
		last_mouse_pos = rend.data->mouse_pos;

		rend.update();
    }

	rend.end();
	return 0;
}