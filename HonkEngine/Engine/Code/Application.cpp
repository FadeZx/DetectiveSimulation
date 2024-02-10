#include "Application.h"

Application* Application::s_instance = nullptr;

Application& Application::Get() {
    assert(s_instance != nullptr); // Ensure s_instance is not null
    return *s_instance;
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// Global variable to track the window mode
bool isWindowBordered = true;

void Application::toggleWindowBorder(GLFWwindow* window) {
    // Toggle the window mode
    isWindowBordered = !isWindowBordered;

    // Store current window size and position
    int width, height, xPos, yPos;
    glfwGetWindowSize(window, &width, &height);
    glfwGetWindowPos(window, &xPos, &yPos);

    // Destroy the current window
    glfwDestroyWindow(window);

    // Set window hints for the new window
    glfwWindowHint(GLFW_DECORATED, isWindowBordered ? GL_TRUE : GL_FALSE);

    // Recreate the window
    GLFWwindow* newWindow = glfwCreateWindow(width, height, "Your Window Title", NULL, NULL);
    glfwSetWindowPos(newWindow, xPos, yPos);

    // Make the new window current and reinitialize OpenGL context
    glfwMakeContextCurrent(newWindow);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // TODO: Restore any other necessary context or settings

    // Update the global window pointer
    m_window = newWindow;

    // Reapply the framebuffer size callback (and any other callbacks)
    glfwSetFramebufferSizeCallback(newWindow, framebuffer_size_callback);

    // TODO: You may need to reinitialize any OpenGL resources (textures, buffers, etc.)
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    Camera& camera = Application::GetCamera();

    // Toggle bordered/borderless on Alt+Enter
    static bool togglePressedLastFrame = false;
    bool alt = glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS;
    bool enter = glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS;

    if (alt && enter && !togglePressedLastFrame) {
        //toggleWindowBorder(window);
        isWindowBordered = !isWindowBordered;
        std::cout<< "Toggle\n";
        togglePressedLastFrame = true;
    }
    else if (!enter) {
        togglePressedLastFrame = false;
    }

}






Application::~Application()
{
    std::cout << "Application Desctructor\n";

   

    for (auto& scene : m_sceneMap)
    {
        delete scene.second;
    }

    glfwTerminate();
}

Application::Application(int win_width, int win_height, const char* title)
    : baseTitle(title)
{

    std::cout << "Application Constructor\n";

    s_instance = this;
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_DECORATED, GL_FALSE);

    // glfw window creation
    // --------------------
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

    m_window = glfwCreateWindow(win_width,win_height,title, NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        
    }
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(isWindowBordered);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    

     //Initialize(SCR_WIDTH, SCR_HEIGHT);

    m_input.Initialize(m_window);
    m_renderer.Initialize(win_width, win_height);
    m_camera.Init(win_width, win_height);


}



void Application::Run()
{
    
    std::cout << "Application Run\n";

    double lastFrameTime = glfwGetTime();
    double frameRateUpdateInterval = 1.0; // Update frame rate every 1 second
    double frameRateTimer = 0.0;
    int frameCount = 0;


    while (!glfwWindowShouldClose(m_window))
    {

        double currentTime = glfwGetTime();
        double dt = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        frameRateTimer += dt;
        frameCount++;

        // input
        // -----
        processInput(m_window);
 


        if (m_currentScene) {
            m_currentScene->Update(dt,frameCount);
            m_currentScene->Render();
            

        }
            
        glGetError();
        glfwSwapBuffers(m_window);
        glfwPollEvents();

        if (frameRateTimer >= frameRateUpdateInterval)
        {
            double frameRate = frameCount / frameRateTimer; //fps == frame per sec

            std::string newTitle = std::string(baseTitle) + " - FPS: " + std::to_string(static_cast<int>(frameRate));
            // Set the new window title
            glfwSetWindowTitle(m_window, newTitle.c_str());
           
            frameRateTimer = 0.0;
            frameCount = 0;
        }
    }

}


