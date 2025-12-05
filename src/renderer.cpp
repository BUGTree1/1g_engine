#include "renderer.h"
#include "1g_assert.h"
#include "shaders.h"

using namespace std;
using namespace glm;

namespace e1g {

void glfw_error_cb(int err, const char* desc) {
    error(desc, err);
}

void glfw_window_size_cb(GLFWwindow* window, int width, int height) {
    Render_Data* data = (Render_Data*)glfwGetWindowUserPointer(window);
    data->width = width;
    data->height = height;

    glViewport(0, 0, width, height);
}

void validate_shader(GLuint shader) {
    int len = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    
    if(len > 0) {
        string info;
        info.resize(len);

        glGetShaderInfoLog(shader, len, NULL, &info[0]);
        
        error(info);
    }
}

void Renderer::init(Scene* scene) {
    this->scene = scene;

    data = new Render_Data;
    data->width = 800;
    data->height = 600;

    glfwSetErrorCallback(glfw_error_cb);
    errorz(glfwInit(), "Can't initialize GLFW!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    data->window = glfwCreateWindow(data->width, data->height, "1G Engine", NULL, NULL);
    errorz(data->window, "Can't initialize GLFW window!");

    glfwSetWindowUserPointer(data->window, data);
    glfwSetWindowSizeCallback(data->window, glfw_window_size_cb);

    glfwMakeContextCurrent(data->window);

    gladLoadGL();

    glGenBuffers(1, &data->vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, data->vertex_buffer);
    vec3 p1 = vec3( -100.0f , -100.0f , 0.0f);
    vec3 p2 = vec3( 0.0f    , 100.0f  , 0.0f);
    vec3 p3 = vec3( 100.0f  , -100.0f , 0.0f);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vertex), new Vertex[3]{
        {p1, {1.0f, 0.0f, 0.0f}},
        {p2, {0.0f, 1.0f, 0.0f}},
        {p3, {0.0f, 0.0f, 1.0f}}}, GL_DYNAMIC_DRAW);
 
    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);
    validate_shader(vertex_shader);
 
    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);
    validate_shader(fragment_shader);
    
 
    const GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
 
    const GLint vpos_location = glGetAttribLocation(program, "vPos");
    const GLint vcol_location = glGetAttribLocation(program, "vCol");

    glGenVertexArrays(1, &data->vertex_array);
    glBindVertexArray(data->vertex_array);
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, pos));
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, col));
}

void Renderer::update(){

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