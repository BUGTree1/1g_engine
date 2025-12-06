#include "renderer.h"
#include "1g_assert.h"
#include "shaders.h"

using namespace std;
using namespace glm;

namespace e1g {

GLFWmonitor* glfw_get_monitor_from_window(GLFWwindow* window) {
    ivec2 window_pos = ivec2(0);
    glfwGetWindowPos(window, &window_pos.x, &window_pos.y);

    int monitor_count = 0;
    GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
    for (int i = 0; i < monitor_count; i++) {
        ivec2 monitor_pos = ivec2();
        ivec2 monitor_size = ivec2();
        glfwGetMonitorWorkarea(monitors[i], &monitor_pos.x, &monitor_pos.y, &monitor_size.x, &monitor_size.y);
        if(monitor_pos.x <= window_pos.x &&
           monitor_pos.y <= window_pos.y &&
           window_pos.x - monitor_pos.x <= monitor_size.x &&
           window_pos.y - monitor_pos.y <= monitor_size.y){
            return monitors[i];
        }
    }

    int approx_level = 0;
    GLFWmonitor* approx_monitor = NULL;
    for (int i = 0; i < monitor_count; i++) {
        ivec2 monitor_pos = ivec2();
        ivec2 monitor_size = ivec2();
        glfwGetMonitorWorkarea(monitors[i], &monitor_pos.x, &monitor_pos.y, &monitor_size.x, &monitor_size.y);
        if(monitor_pos.x <= window_pos.x) {
            if(monitor_pos.y <= window_pos.y) {
                if(window_pos.x - monitor_pos.x <= monitor_size.x) {
                    if(window_pos.y - monitor_pos.y <= monitor_size.y){
                        return monitors[i];
                    }else{
                        if(approx_level <= 3) {approx_monitor = monitors[i]; approx_level = 3;}
                    }
                }else{
                    if(approx_level <= 2) {approx_monitor = monitors[i]; approx_level = 2;}
                }
            }else{
                if(approx_level <= 1) {approx_monitor = monitors[i]; approx_level = 1;}
            }
        }else{
            if(approx_level <= 0) {approx_monitor = monitors[i]; approx_level = 0;}
        }
    }
    return approx_monitor;
}

void glfw_error_cb(int err, const char* desc) {
    error(desc, err);
}

void glfw_window_pos_cb(GLFWwindow* window, int xpos, int ypos) {
    Render_Data* data = (Render_Data*)glfwGetWindowUserPointer(window);
    GLFWmonitor* monitor = glfw_get_monitor_from_window(window);
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    glfwGetMonitorPos(monitor, &data->monitor_pos.x, &data->monitor_pos.y);
    
    data->monitor_size = ivec2(mode->width, mode->height);
    data->monitor_aspect_ratio = (float)mode->width / (float)mode->height;

    data->window_pos = ivec2(xpos, ypos);
}

void glfw_window_size_cb(GLFWwindow* window, int width, int height) {
    Render_Data* data = (Render_Data*)glfwGetWindowUserPointer(window);
    data->window_size.x = width;
    data->window_size.y = height;

    data->window_aspect_ratio = (float)width / (float)height;

    glViewport(0, 0, width, height);
}

void glfw_window_scale_cb(GLFWwindow* window, float xscale, float yscale) {
    Render_Data* data = (Render_Data*)glfwGetWindowUserPointer(window);
    data->window_scale.x = xscale;
    data->window_scale.y = yscale;
}

void validate_shader(GLuint shader) {
    int len = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        string info;
        info.resize(len);

        glGetShaderInfoLog(shader, len, NULL, &info[0]);
        
        error("SHADER: " + info);
    }
}

void validate_program(GLuint program) {
    int len = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
    int success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success) {
        string info;
        info.resize(len);

        glGetProgramInfoLog(program, len, NULL, &info[0]);
        
        error("SHADER PROGRAM: " + info);
    }
}

void Renderer::init(Scene* scene) {
    this->scene = scene;

    data = new Render_Data;
    data->window_size.x = 800;
    data->window_size.y = 600;

    #if defined(__linux__)
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
    #endif

    glfwSetErrorCallback(glfw_error_cb);
    errorz(glfwInit(), "Can't initialize GLFW!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
    glfwWindowHint(GLFW_DOUBLEBUFFER, true);
    glfwWindowHint(GLFW_SCALE_FRAMEBUFFER, true);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, true);
    glfwWindowHint(GLFW_RESIZABLE, true);
    
    data->window = glfwCreateWindow(data->window_size.x, data->window_size.y, "1G Engine", NULL, NULL);
    errorz(data->window, "Can't initialize GLFW window!");

    glfwMakeContextCurrent(data->window);
    
    errorz(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Can't initialize GLAD!");

    glfwSwapInterval(0);

    glfwSetWindowUserPointer(data->window, data);
    glfwSetWindowPosCallback(data->window, glfw_window_pos_cb);
    glfwSetWindowContentScaleCallback(data->window, glfw_window_scale_cb);
    glfwSetWindowSizeCallback(data->window, glfw_window_size_cb);

    glfwGetWindowPos(data->window, &data->window_pos.x, &data->window_pos.y);
    glfwGetWindowContentScale(data->window, &data->window_scale.x, &data->window_scale.y);
    glfwGetWindowSize(data->window, &data->window_size.x, &data->window_size.y);

    glfw_window_pos_cb(data->window, data->window_pos.x, data->window_pos.y);
    glfw_window_scale_cb(data->window, data->window_scale.x, data->window_scale.y);
    glfw_window_size_cb(data->window, data->window_size.x, data->window_size.y);

    glfwSetInputMode(data->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
 
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);
    validate_shader(vertex_shader);
 
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);
    validate_shader(fragment_shader);
    
    data->program = glCreateProgram();
    glAttachShader(data->program, vertex_shader);
    glAttachShader(data->program, fragment_shader);
    glLinkProgram(data->program);
    validate_program(data->program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glUseProgram(data->program);
 
    GLint vpos_location = glGetAttribLocation(data->program, "vPos");
    GLint vcol_location = glGetAttribLocation(data->program, "vCol");
    data->proj_loc = glGetUniformLocation(data->program, "proj");
    data->view_loc = glGetUniformLocation(data->program, "view");
    data->model_loc = glGetUniformLocation(data->program, "model");

    glGenVertexArrays(1, &data->vao);
    glBindVertexArray(data->vao);

    glGenBuffers(1, &data->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, data->vbo);
    GLuint indices[] = {
		0, 1, 2
	};
    
    glGenBuffers(1, &data->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(vpos_location);
    glBindBuffer( GL_ARRAY_BUFFER, data->vbo );
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, pos));
    glEnableVertexAttribArray(vcol_location);
    glBindBuffer( GL_ARRAY_BUFFER, data->vbo );
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, col));
}

void Renderer::update(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < scene->gameobjects.size(); i++) {
        for (int j = 0; j < scene->gameobjects[i]->components.size(); j++) {
            scene->gameobjects[i]->components[j]->render(data);
        }
    }

    glfwSwapBuffers(data->window);
}

void Renderer::end(){
    glfwDestroyWindow(data->window);
    glfwTerminate();
}

}