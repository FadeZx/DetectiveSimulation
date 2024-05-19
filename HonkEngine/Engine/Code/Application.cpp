#include "Application.h"


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void Application::ToggleFullscreen(GLFWwindow* window) {
    static int windowedWidth = 1920;  // Desired windowed mode width
    static int windowedHeight = 1080; // Desired windowed mode height
    static int windowedPosX = 0;   // Default position x
    static int windowedPosY = 50;   // Default position y

    if (!glfwGetWindowMonitor(window)) { // If currently windowed
        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

        // Store windowed mode position and size
        glfwGetWindowPos(window, &windowedPosX, &windowedPosY);
        glfwGetWindowSize(window, &windowedWidth, &windowedHeight);

        // Switch to fullscreen
        glfwSetWindowMonitor(window, primaryMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    else { // If currently fullscreen
        // Switch back to windowed mode
        glfwSetWindowMonitor(window, NULL, windowedPosX, windowedPosY, windowedWidth, windowedHeight, 0);

        // Ensure the window decoration and size are restored properly
        glfwSetWindowSize(window, windowedWidth, windowedHeight);
        glfwSetWindowPos(window, windowedPosX, windowedPosY);
    }
}



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        Application::Get().exitGame();
        //glfwSetWindowShouldClose(window, true);

    static bool fsTogglePressedLastFrame = true;
    bool fsToggle = glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS;

    if (fsToggle && !fsTogglePressedLastFrame) {
        Application::Get().ToggleFullscreen(window); // Adjusted to call the standalone function
        fsTogglePressedLastFrame = true;
    }
    else if (!fsToggle) {
        fsTogglePressedLastFrame = false;
    }

    Camera& camera = Application::GetCamera();

    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
    {
        // Assuming you have a static GetCamera method in Application
        camera.ZoomIn(0.01f);  // Zoom in by 0.1 units
    }
    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
    {
        // Assuming you have a static GetCamera method in Application
        camera.ZoomOut(0.01f);  // Zoom in by 0.1 units
    }

    static bool mousePressed = false;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !mousePressed) {
        Application::Get().SetClickedCursor();  // Change to clicked cursor
        mousePressed = true;
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && mousePressed) {
        Application::Get().SetNormalCursor();  // Revert to normal cursor
        mousePressed = false;
    }

}

Application* Application::s_instance = nullptr;

Application::~Application() {
    if (m_currentScene) {
        m_currentScene->OnExit();
    }
    for (auto& scene : m_sceneMap) {
        delete scene.second;
    }

    if (normalCursor) {
        glfwDestroyCursor(normalCursor);
        normalCursor = nullptr;
    }
    if (clickedCursor) {
        glfwDestroyCursor(clickedCursor);
        clickedCursor = nullptr;
    }

    glfwTerminate();
}

int Application::SetTimer(long long duration, std::function<void()> callback, bool repeat) {
    auto timer = std::make_unique<GlobalTimer>();
    timer->duration = duration;
    timer->callback = callback;
    timer->endTime = std::chrono::steady_clock::now() + std::chrono::milliseconds(duration);
    timer->repeat = repeat;
    int timerId = nextTimerId++;  // Increment and assign a unique ID
    activeTimers[timerId] = std::move(timer);
    return timerId;  // Return this ID
}

void Application::CancelTimer(int timerId) {
    auto it = activeTimers.find(timerId);
    if (it != activeTimers.end()) {
        activeTimers.erase(it);
    }
}

void Application::processTimers() {
    auto now = std::chrono::steady_clock::now();
    for (auto it = activeTimers.begin(); it != activeTimers.end(); ) {
        auto& timer = it->second;
        if (now >= timer->endTime) {
            timer->callback();
            if (timer->repeat) {
                timer->endTime = now + std::chrono::milliseconds(timer->duration);  // Re-set the timer
                ++it;
            }
            else {
                it = activeTimers.erase(it);  // Remove non-repeating timers
            }
        }
        else {
            ++it;
        }
    }
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

    // glfw window creation
    // --------------------

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

    m_window = glfwCreateWindow(mode->width, mode->height, title, primaryMonitor, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;

    }
    glfwMakeContextCurrent(m_window);

    LoadCursors();

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


    while (!glfwWindowShouldClose(m_window)) {
        double currentTime = glfwGetTime();
        double dt = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        // Input handling
        processInput(m_window);

        // Scene management
        if (m_currentScene) {
            m_currentScene->Update(dt, frameCount);
            m_currentScene->Render();
        }

        // Buffer swapping and event polling
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
        processTimers();
    }

    if (m_currentScene) {
        m_currentScene->OnExit();
    }

}